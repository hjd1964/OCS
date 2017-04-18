// -----------------------------------------------------------------------------------
// Cloud/Safety monitor

#ifdef SD_CARD_ON
#include <SD.h>
#endif

#ifdef WEATHER_CLOUD_CVR_ON
// Adjust the log resolution here, must be in 2's 2,4,6,8...120,122
// keep in mind that EEPROM is spec'd to last for 100,000 writes
// since a given location gets written to once in 64 readings that amounts to
// a write of a given location once every 2 hours (64 * 120 seconds) * 100,000 which is 22 years
// at 60 it's 11 years, at 30 5 years life.  These are minimums according to the spec.
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

void clouds(void) {
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
    double p = weatherPressure();

    // Humidity ----------------------------------------------------------------
    double h = weatherHumidity();

#ifdef SD_CARD_ON
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
          Serial.println("Data file doesn't exist...");

          // create the empty file
          dataFile=SD.open(fn, FILE_WRITE); dataFile.close(); // create the file

          // fill the datafile 2 per minute * 60 * 24 = 2880 records per day
          // each record is as follows (80 bytes):
          // size=250400/day

          dataFile=SD.open(fn, FILE_WRITE);
          if (dataFile) {
            Serial.print("Writing file...");
            for (int i=0; i<2880; i++) {
              Serial.print("Writing record#"); Serial.println(i);
              //               time   sa    sad   lad   p      h     wind  sq
              //             "hhmmss: ttt.t ttt.t ttt.t mmmm.m fff.f kkk.k mm.mm                                "
              dataFile.write("                                                                              \r\n");
            }
            dataFile.close();
          } else { Serial.println("Failed to create file"); }
        }

        // write to the sdcard file
        dataFile=SD.open(fn, FILE_WRITE);
        if (dataFile) {
          dataFile.seek(logRecordLocation(t)*80L);
          sprintf(temp,"%02d%02d%02d",hour(t),minute(t),second(t));
          dataFile.write(temp);  dataFile.write(":");                         //00, 8
          dtostrf2(sa,5,1,temp);  dataFile.write(" ");  dataFile.write(temp); //08, 6
          dtostrf2(sad,5,1,temp); dataFile.write(" ");  dataFile.write(temp); //14, 6
          dtostrf2(lad,5,1,temp); dataFile.write(" ");  dataFile.write(temp); //20, 6
          dtostrf2(p,6,1,temp);   dataFile.write(" ");  dataFile.write(temp); //26, 7
          dtostrf2(h,5,1,temp);   dataFile.write(" ");  dataFile.write(temp); //33, 6
          dtostrf2(weatherWindspeed(),5,1,temp); dataFile.write(temp);        //39, 5
          dtostrf2(weatherSkyQuality(),5,2,temp); dataFile.write(temp);       //45, 5
          for (int i=0; i<29; i++) dataFile.write(" ");                       //    29
          dataFile.write("\r\n");                                             //    2
          dataFile.close();
        }

//        int n;
//        dataFile=SD.open(fn, FILE_READ);
//        if (dataFile) {
//          dataFile.seek(logRecordLocation(t)*80L);
//          n=dataFile.read(temp,80); //Serial.write(temp,n);
//          dataFile.close();
//        }
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

#ifdef STAT_MAINS_SENSE
  // check for mains power out
  if (digitalRead(sensePin[STAT_MAINS_SENSE])!=HIGH) safe=false;
#endif

#ifdef WEATHER_ON
#ifdef WEATHER_RAIN_ON
  // check for invalid or wet (1=Wet, 2=Warn, 3=Dry)
  if ((weatherRain()==invalid) || (weatherRain()==1)) safe=false;
#endif

#ifdef WEATHER_CLOUD_CVR_ON
  // check for invalid or above WEATHER_SAFE_THRESHOLD
  if ((avgSkyDiffTemp<-200) || (avgSkyDiffTemp>WEATHER_SAFE_THRESHOLD)) safe=false;
  mainDeviceCount++;
#endif

#ifdef WEATHER_WIND_SPD_ON
  // check for invalid or wind speed too high
  if ((weatherWindspeed()<0) || (weatherWindspeed()>WEATHER_WIND_SPD_THRESHOLD)) safe=false;
  mainDeviceCount++;
#endif
#endif

  if (mainDeviceCount==0) return false; else return safe;
}

void dtostrf2(double d, int i, int i1, char result[]) {
  if (d==invalid) 
    for (int j=0; j<i; j++) { result[j]=' '; result[j+1]=0; }
  else
    dtostrf(d,i,i1,result);
}

