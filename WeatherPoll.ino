// -----------------------------------------------------------------------------------
// Weather/Safety monitor and logging

#if WEATHER_CHARTS == ON
  #include <SD.h>
#endif

#if WEATHER == ON

#define SecondsBetweenLogEntries 30

// this is the response time required to cover approximately 2/3 of a change in cloud temperature
// adjust higher for less sensitivity to passing clouds/changing conditions, lower for more sensitivity
#define AvgTimeSeconds 600.0

long TimeSeconds=0;
unsigned long last=10000;
double skyDiffTemp=invalid;
double avgSkyDiffTemp=invalid;
double sa=invalid;
double ss=invalid;
double sad=invalid;
double lad=invalid;
double wa=invalid;

void weatherPoll(void) {
  unsigned long m = millis();
  if ((m-last)>2000L) {
    last=m;
    
    // Cloud sensor ------------------------------------------------------------
    // it might be a good idea to add some error checking and force the values to invalid if something is wrong
    double ambientTemp = weatherOutsideTemp();
    double skyTemp = weatherSkyTemp();
    if ((ambientTemp==invalid) || (skyTemp==invalid)) skyDiffTemp=invalid; else skyDiffTemp = skyTemp-ambientTemp;
    if (skyDiffTemp==invalid) avgSkyDiffTemp=skyDiffTemp; else
      if (avgSkyDiffTemp==invalid) avgSkyDiffTemp=skyDiffTemp; else
        avgSkyDiffTemp = ((avgSkyDiffTemp*(AvgTimeSeconds/2.0-1.0)) + skyDiffTemp)/(AvgTimeSeconds/2.0);
    
    // short-term average ambient temp
    if (sa==invalid) sa=ambientTemp;
    if (sa!=invalid) sa = ((sa*((double)SecondsBetweenLogEntries/2.0-1.0)) + ambientTemp)/((double)SecondsBetweenLogEntries/2.0);
    // short-term sky temp
    if (ss==invalid) ss=skyTemp;
    if (ss!=invalid) ss = ((ss*((double)SecondsBetweenLogEntries/2.0-1.0)) + skyTemp)/((double)SecondsBetweenLogEntries/2.0);
    // short-term average diff temp
    if (sad==invalid) sad=skyDiffTemp;
    if (sad!=invalid) sad = ((sad*((double)SecondsBetweenLogEntries/2.0-1.0)) + skyDiffTemp)/((double)SecondsBetweenLogEntries/2.0);
    // long-term average diff temp
    lad=avgSkyDiffTemp;
    // End cloud sensor

    // Pressure ----------------------------------------------------------------
    double p = weatherPressureSeaLevel();

    // Humidity ----------------------------------------------------------------
    double h = weatherHumidity();

    // Wind speed --------------------------------------------------------------
    double w = weatherWindspeed();
    if (wa==invalid) wa=w;
    if (wa!=invalid) wa = ((wa*((double)SecondsBetweenLogEntries/2.0-1.0)) + w)/((double)SecondsBetweenLogEntries/2.0);

    // short-term sky temp

#if WEATHER_CHARTS == ON
    // Logging ------------------------------------------------------------------
    // two minutes between writing values
    // the log is perpetual with 80 chars written twice a minute (about 82MB a year)
    TimeSeconds+=2;
    if (TimeSeconds%SecondsBetweenLogEntries==0) { // x seconds
      TimeSeconds=0;

      // only log if the time is set and we have an SD card
      if ((timeStatus()!=timeNotSet) && (www.SDfound)) {
        char temp[256] = "";

        time_t t = now();
        int y=year(t); y-=2000;
        sprintf(temp,"%02d%02d%02d",y,month(t),day(t));
        String fn="L"+String(temp)+".TXT";

        File dataFile;
        if (!SD.exists(fn)) {
#if DEBUG_SD == ON
          Serial.println("Data file doesn't exist...");
#endif
          // create the empty file
          dataFile=SD.open(fn, FILE_WRITE); dataFile.close(); // create the file

          // fill the datafile 2 per minute * 60 * 24 = 2880 records per day
          // each record is as follows (80 bytes):
          // size=250400/day

          dataFile=SD.open(fn, FILE_WRITE);
          if (dataFile) {
#if DEBUG_SD == ON
            Serial.print("Writing file...");
#endif
            for (int i=0; i<2880; i++) {
#if DEBUG_SD == ON
              Serial.print("Writing record#"); Serial.println(i);
#endif
              //               time   sa    sad   lad   p      h     wind  sq
              //             "hhmmss: ttt.t ttt.t ttt.t mmmm.m fff.f kkk.k mm.mm                                "
              //              01234567890123456789012345678901234567890123456789
              //              0         1         2         3         4
              dataFile.write("                                                                              \r\n");
#if WATCHDOG == ON
              wdt_reset();
#endif
            }
            dataFile.close();
          } else { 
#if DEBUG_SD == ON
            Serial.println("Failed to create file"); 
#endif
          }
        }

        // write to the sdcard file
        dataFile=SD.open(fn, O_READ | O_WRITE);
        if (dataFile) {
          dataFile.seek(logRecordLocation(t)*80L);
          sprintf(temp,"%02d%02d%02d",hour(t),minute(t),second(t));
          dataFile.write(temp); dataFile.write(":");                                                      //00, 8 (time)
          dtostrf2(sa,5,1,-99.9,999.9,temp);                   dataFile.write(" "); dataFile.write(temp); //07, 6 (short term average ambient temperature)
          dtostrf2(sad,5,1,-99.9,999.9,temp);                  dataFile.write(" "); dataFile.write(temp); //13, 6 (short term average dif (sky) temperature)
          dtostrf2(lad,5,1,-99.9,999.9,temp);                  dataFile.write(" "); dataFile.write(temp); //19, 6 (long term average dif (sky) temperature)
          dtostrf2(p,6,1,-999.9,9999.9,temp);                  dataFile.write(" "); dataFile.write(temp); //25, 7 (pressure)
          dtostrf2(h,5,1,-99.9,999.9,temp);                    dataFile.write(" "); dataFile.write(temp); //32, 6 (humidity)
          dtostrf2(wa,5,1,-99.9,999.9,temp);                   dataFile.write(" "); dataFile.write(temp); //38, 6 (short term average windspeed)
          dtostrf2(weatherSkyQuality(),5,2,-9.99,99.99,temp);  dataFile.write(" "); dataFile.write(temp); //44, 6 (sky quality)
          for (int i=0; i<29; i++) dataFile.write(" ");                                                   //  ,29
          dataFile.write("\r\n");                                                                         //  , 2
          dataFile.close();
        }

#if DEBUG_SD == ON
        int n;
        dataFile=SD.open(fn, FILE_READ);
        if (dataFile) {
          dataFile.seek(logRecordLocation(t)*80L);
          n=dataFile.read(temp,80); Serial.write(temp,n); Serial.write(temp,"\r\n");
          dataFile.close();
        }
#endif
      }

      sa=ambientTemp;
      ss=skyTemp;
      sad=skyDiffTemp;
    }
#endif
  }
}

long logRecordLocation(time_t t) {
  return round(hour(t)*3600L+minute(t)*60L+second(t))/30L;
}

double getSkyDiffTemp() {
  return skyDiffTemp;
}

double getAvgSkyDiffTemp() {
  return avgSkyDiffTemp;
}
#endif

bool isSafe() {
  bool safe=true;
  int mainDeviceCount=0;

#if STAT_MAINS_SENSE != OFF
  // check for mains power out
  if (!senseIsOn(STAT_MAINS_SENSE)) safe=false;
#endif

#if WEATHER == ON
  #if WEATHER_RAIN == ON
    // check for invalid or wet (1=Wet, 2=Warn, 3=Dry)
    if ((weatherRain()==invalid) || (weatherRain()==1)) safe=false;
  #endif
  
  #if WEATHER_CLOUD_CVR == ON
    // check for invalid or above WEATHER_SAFE_THRESHOLD
    if ((avgSkyDiffTemp<-200) || (avgSkyDiffTemp>WEATHER_SAFE_THRESHOLD)) safe=false;
    mainDeviceCount++;
  #endif
  
  #if WEATHER_WIND_SPD == ON
    // check for invalid or wind speed too high
    if ((weatherWindspeed()<0) || (weatherWindspeed()>WEATHER_WIND_SPD_THRESHOLD)) safe=false;
    mainDeviceCount++;
  #endif
#endif

  if (mainDeviceCount==0) return false; else return safe;
}

void dtostrf2(double d, int i, int i1, double l, double h, char result[]) {
  if (d==invalid)
    for (int j=0; j<i; j++) { result[j]=' '; result[j+1]=0; }
  else {
    if (d<=l) d=l;
    if (d>=h) d=h;
    dtostrf(d,i,i1,result);
  }
}
