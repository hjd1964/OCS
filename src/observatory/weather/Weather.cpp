// -----------------------------------------------------------------------------------
// Weather/Safety monitor and logging
#include "Weather.h"

#if WEATHER == ON

#include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

#if WEATHER_CHARTS == ON
  #include <SD.h>
#endif

#include "../../lib/ethernet/Ethernet.h"
#include "../../lib/ethernet/webServer/WebServer.h"
#include "../../lib/weatherSensor/WeatherSensor.h"

File dataFile;

void Weather::init() {
  weatherSensor.init();
}

void Weather::poll(void) {
  unsigned long m = millis();
  if ((long)(m - last) > 2000) {
    last = m;

    // Cloud sensor ------------------------------------------------------------
    // it might be a good idea to add some error checking and force the values to invalid if something is wrong
    float ambientTemp = weatherSensor.temperature();
    float skyTemp = weatherSensor.skyTemperature();
    if (isnan(ambientTemp) || isnan(skyTemp)) {
      skyDiffTemp = NAN;
    } else {
       skyDiffTemp = skyTemp - ambientTemp;
    }
    if (isnan(skyDiffTemp)) {
      avgSkyDiffTemp = skyDiffTemp;
    } else {
      if (isnan(avgSkyDiffTemp)) {
        avgSkyDiffTemp = skyDiffTemp;
      } else {
        avgSkyDiffTemp = ((avgSkyDiffTemp*(AvgTimeSeconds/2.0 - 1.0)) + skyDiffTemp)/(AvgTimeSeconds/2.0);
      }
    }

    // short-term average ambient temp
    if (isnan(sa)) sa = ambientTemp;
    if (!isnan(sa)) sa = ((sa*((double)SecondsBetweenLogEntries/2.0 - 1.0)) + ambientTemp)/((double)SecondsBetweenLogEntries/2.0);
    // short-term sky temp
    if (isnan(ss)) ss = skyTemp;
    if (!isnan(ss)) ss = ((ss*((double)SecondsBetweenLogEntries/2.0 - 1.0)) + skyTemp)/((double)SecondsBetweenLogEntries/2.0);
    // short-term average diff temp
    if (isnan(sad)) sad = skyDiffTemp;
    if (!isnan(sad)) sad = ((sad*((double)SecondsBetweenLogEntries/2.0 - 1.0)) + skyDiffTemp)/((float)SecondsBetweenLogEntries/2.0);
    // long-term average diff temp
    lad = avgSkyDiffTemp;
    // End cloud sensor

    // Pressure ----------------------------------------------------------------
    float p = weatherSensor.pressureSeaLevel();

    // Humidity ----------------------------------------------------------------
    float h = weatherSensor.humidity();

    // Wind speed --------------------------------------------------------------
    float w = weatherSensor.windspeed();
    if (wa == invalid) wa = w;
    if (wa != invalid) wa = ((wa*((float)SecondsBetweenLogEntries/2.0 - 1.0)) + w)/((float)SecondsBetweenLogEntries/2.0);

    // Sky quality -------------------------------------------------------------
    float q = weatherSensor.skyQuality();

    // short-term sky temp

    #if WEATHER_CHARTS == ON
      if (WATCHDOG_DURING_SD == OFF) { WDT_DISABLE; }

      // Logging ------------------------------------------------------------------
      // two minutes between writing values
      // the log is perpetual with 80 chars written twice a minute (about 82MB a year)
      TimeSeconds += 2;
      if (TimeSeconds >= SecondsBetweenLogEntries) {
        TimeSeconds = 0;

        // only log if the time is set and we have an SD card
        if (timeStatus() != timeNotSet && www.SDfound) {

          char temp[256] = "";

          time_t t = now();
          int y = year(t);
          y -= 2000;
          sprintf(temp, "%02d%02d%02d", y, month(t), day(t));
          String fn = "L" + String(temp) + ".TXT";

          if (!SD.exists(fn)) {
            #if DEBUG_SD == ON
              VL("MSG: Data file doesn't exist...");
            #endif
            // create the empty file
            dataFile = SD.open(fn, FILE_WRITE);
            dataFile.close();

            // fill the datafile 2 per minute * 60 * 24 = 2880 records per day
            // each record is as follows (80 bytes):
            // size=250400/day
           
            dataFile = SD.open(fn, FILE_WRITE);
            if (dataFile) {
              #if DEBUG_SD == ON
                VL("MSG: Writing file...");
              #endif
              for (int i = 0; i < 2880; i++) {
                #if DEBUG_SD == ON
                  V("MSG: Writing record#"); VL(i);
                #endif
                //               time   sa    sad   lad   p      h     wind  sq
                //             "hhmmss: ttt.t ttt.t ttt.t mmmm.m fff.f kkk.k mm.mm                                "
                //              01234567890123456789012345678901234567890123456789
                //              0         1         2         3         4
                dataFile.write("                                                                              \r\n");
              }
              dataFile.close();
            } else { 
              #if DEBUG_SD == ON
                VL("MSG: Failed to create file"); 
              #endif
            }
          }

          // write to the sdcard file
          dataFile = SD.open(fn, O_READ | O_WRITE);
          if (dataFile) {
            dataFile.seek(logRecordLocation(t)*80L);
            sprintf(temp,"%02d%02d%02d",hour(t),minute(t),second(t));
            dataFile.write(temp); dataFile.write(":");                                     //00, 8 (time)
            dtostrf2(sa,5,1,-99.9,999.9,temp);  dataFile.write(" "); dataFile.write(temp); //07, 6 (short term average ambient temperature)
            dtostrf2(sad,5,1,-99.9,999.9,temp); dataFile.write(" "); dataFile.write(temp); //13, 6 (short term average dif (sky) temperature)
            dtostrf2(lad,5,1,-99.9,999.9,temp); dataFile.write(" "); dataFile.write(temp); //19, 6 (long term average dif (sky) temperature)
            dtostrf2(p,6,1,-999.9,9999.9,temp); dataFile.write(" "); dataFile.write(temp); //25, 7 (pressure)
            dtostrf2(h,5,1,-99.9,999.9,temp);   dataFile.write(" "); dataFile.write(temp); //32, 6 (humidity)
            dtostrf2(wa,5,1,-99.9,999.9,temp);  dataFile.write(" "); dataFile.write(temp); //38, 6 (short term average windspeed)
            dtostrf2(q,5,2,-9.99,99.99,temp);   dataFile.write(" "); dataFile.write(temp); //44, 6 (sky quality)
            for (int i = 0; i < 29; i++) dataFile.write(" ");                              //  ,29
            dataFile.write("\r\n");                                                        //  , 2
            dataFile.close();
          }

          #if DEBUG_SD == ON
            int n;
            dataFile = SD.open(fn, FILE_READ);
            if (dataFile) {
              dataFile.seek(logRecordLocation(t)*80L);
              n = dataFile.read(temp, 80);
              Serial.write(temp, n);
              Serial.write(temp,"\r\n");
              dataFile.close();
            }
          #endif
        }

        sa = ambientTemp;
        ss = skyTemp;
        sad = skyDiffTemp;
      }
      
      if (WATCHDOG_DURING_SD == OFF) { WDT_ENABLE; }
    #endif
  }
}

float Weather::getSkyDiffTemp() {
  return skyDiffTemp;
}

float Weather::getAvgSkyDiffTemp() {
  return avgSkyDiffTemp;
}
#endif

void Weather::dtostrf2(float d, int i, int i1, float l, float h, char result[]) {
  if (d == invalid)
    for (int j = 0; j < i; j++) { result[j] = ' '; result[j + 1] = 0; }
  else {
    if (d <= l) d = l;
    if (d >= h) d = h;
    dtostrf(d, i, i1, result);
  }
}

Weather weather;
