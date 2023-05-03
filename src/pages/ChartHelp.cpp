// help for charting sensor readings
#include "ChartHelp.h"

#if WEATHER == ON && WEATHER_CHARTS == ON
  #include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

  // transmits an Chart.js chart to the html client
  // \param chartId: the html id tag for the chart to dispay
  // \param chartName: the name to display on the chart
  // \param logColumn: the column position (in chars) of the data being charted
  // \param colWidth: the width (in chars) of the data being charted
  // \param rangeMin: the low value on the chart
  // \param rangeMax: the high value on the chart
  // \param rangeStep: the step size on the chart
  // \param hours: the number of hours of data to display
  void makeChartJs(const char chartId[], String chartName, int logColumn, int colWidth, int rangeMin, int rangeMax, int rangeStep, long hours) {
    char fileName[32];
    char temp[256] = "";
    char ws1[90] = "";
    char ws2[90] = "";
    long rec = 0;
    long k = 0;

    sprintf_P(temp, ChartJs1, chartId, chartId, chartId);
    www.sendContent(temp);

    www.sendContent(chartName);

    strcpy_P(temp, ChartJs3);
    www.sendContent(temp);

    time_t t = now();

    rec = logRecordLocation(t) - LogRecordsPerHour*hours;
    while (rec < 0) { rec += LogRecordsPerDay; t -= 24L*60L*60L; }
    sprintf(fileName, "L%02d%02d%02d.TXT", year(t) - 2000, month(t), day(t));

    //Serial.print("Primary log="); Serial.println(fn);
    //Serial.print("Reading "); Serial.print(120); Serial.print(" records from rec#"); Serial.println(rec);

    if (WATCHDOG_DURING_SD == OFF) { WDT_DISABLE; }
    File dataFile = FS.open(fileName, FILE_READ);
    if (dataFile) {
      for (long i = 0; i < LogRecordsPerHour; i++) {
        if (((rec + i*hours) - k) >= LogRecordsPerDay) {
          dataFile.close();
          k = rec + i*hours;
          t += 24L*60L*60L;
          sprintf(fileName, "L%02d%02d%02d.TXT", year(t) - 2000, month(t), day(t));
          dataFile = FS.open(fileName, FILE_READ);
          if (!dataFile) break;

          //Serial.print("Secondary log="); Serial.println(fn);
          //Serial.print("Reading "); Serial.print(120-i); Serial.print(" records from rec#"); Serial.println(0);
        }
        dataFile.seek(((rec + i*hours) - k)*80L);

        //if (chartId[0]=='B') Serial.println(((rec+i*step)-k));

        dataFile.read((unsigned char*)ws1, 80);
        ws1[abs(logColumn) + colWidth] = 0;
        int j = abs(logColumn);
        while (ws1[j] == ' ' && ws1[j] != 0) j++;
        strcpy(ws2, (char*)&(ws1[j]));
        if (ws2[0] != 0) {
          float f = atof(ws2);
          if (logColumn == -8)  f = f*(9.0/5.0) + 32.0; // temperature C to F
          if (logColumn == -39) f = f*0.621371;         // wind kph to mph
          if (logColumn == -26) f = f*0.02953;          // pressure in inches
          if (isnan(f))         f = rangeMax;           // handle bad/no data
          if (logColumn == -26) dtostrf(f, 1, 3, ws2); else dtostrf(f, 1, 1, ws2);
          #if REVERSE_WEATHER_CHART_X_AXIS == ON
            if (hours == 1)  dtostrf(-(120-i)/2.0, 1, 1, ws1);
            if (hours == 24) dtostrf(-(120-i)/5.0, 1, 1, ws1);
            if (hours == 48) dtostrf(-(120-i)/2.5, 1, 1, ws1);
          #else
            if (hours == 1)  dtostrf((120-i)/2.0, 1, 1, ws1);
            if (hours == 24) dtostrf((120-i)/5.0, 1, 1, ws1);
            if (hours == 48) dtostrf((120-i)/2.5, 1, 1, ws1);
          #endif
          sprintf(temp, "{x:%s,y:%s},", ws1, ws2);
          www.sendContent(temp);
        }
      }
      dataFile.close();
    }
    if (WATCHDOG_DURING_SD == OFF) { WDT_ENABLE; }
    
    sprintf_P(temp, ChartJs4, rangeMax, rangeMin, rangeStep);
    www.sendContent(temp);
  }

  // transmits an Chart.js chart to the html client
  // \param chartId: the html id tag for the chart to dispay
  // \param chartName: the name to display on the chart
  // \param logColumn: the column position (in chars) of the data being charted
  // \param colWidth: the width (in chars) of the data being charted
  // \param rangeMin: the low value on the chart
  // \param rangeMax: the high value on the chart
  // \param rangeStep: the step size on the chart
  // \param hours: the number of hours of data to display
  void makeChartJs2(const char chartId[], String chartName, int logColumn, int colWidth, int rangeMin, int rangeMax, int rangeStep, long hours) {
    char fileName[32];
    char temp[256] = "";
    char ws1[90] = "";
    char ws2[90] = "";
    long startRecord = 0;
    long k = 0;

    sprintf_P(temp, ChartJs1, chartId, chartId, chartId);
    www.sendContent(temp);

    www.sendContent(chartName);

    strcpy_P(temp, ChartJs3);
    www.sendContent(temp);

    long spanInHours = LogRecordsPerHour*hours;

    time_t t = now();
    startRecord = logRecordLocation(t) - spanInHours;
    while (startRecord < 0) { startRecord += LogRecordsPerDay; t -= 24L*60L*60L; }
    sprintf(fileName, "L%02d%02d%02d.TXT", year(t) - 2000, month(t), day(t));

    //Serial.print("Primary log="); Serial.println(fn);
    //Serial.print("Reading "); Serial.print(120); Serial.print(" records from rec#"); Serial.println(rec);

    if (WATCHDOG_DURING_SD == OFF) { WDT_DISABLE; }
    File dataFile = FS.open(fileName, FILE_READ);
    if (dataFile) {
      for (long i = 0; i < LogRecordsPerHour; i++) {
        startRecord += hours;

        if (((startRecord + i*hours) - k) >= LogRecordsPerDay) {
          dataFile.close();
          k = startRecord + i*hours;
          t += 24L*60L*60L;
          sprintf(fileName, "%02d%02d%02d", year(t) - 2000, month(t), day(t));
          dataFile = FS.open(fileName, FILE_READ);
          if (!dataFile) break;

          //Serial.print("Secondary log="); Serial.println(fn);
          //Serial.print("Reading "); Serial.print(120-i); Serial.print(" records from rec#"); Serial.println(0);
        }
        dataFile.seek(((startRecord + i*hours) - k)*80L);

        //if (chartId[0]=='B') Serial.println(((rec+i*step)-k));

        dataFile.read((unsigned char*)ws1, 80);
        ws1[abs(logColumn) + colWidth] = 0;
        int j = abs(logColumn);
        while (ws1[j] == ' ' && ws1[j] != 0) j++;
        strcpy(ws2, (char*)&(ws1[j]));
        if (ws2[0] != 0) {
          float f = atof(ws2);
          if (logColumn == -8)  f = f*(9.0/5.0)+32.0; // temperature C to F
          if (logColumn == -39) f = f*0.621371;       // wind kph to mph
          if (logColumn == -26) f = f*0.02953;        // pressure in inches
          if (isnan(f))         f = rangeMax;         // handle bad/no data
          if (logColumn == -26) dtostrf(f, 1, 3, ws2); else dtostrf(f, 1, 1, ws2);
          #if REVERSE_WEATHER_CHART_X_AXIS == ON
            if (hours == 1)  dtostrf(-(120-i)/2.0, 1, 1, ws1);
            if (hours == 24) dtostrf(-(120-i)/5.0, 1, 1, ws1);
            if (hours == 48) dtostrf(-(120-i)/2.5, 1, 1, ws1);
          #else
            if (hours == 1)  dtostrf((120-i)/2.0, 1, 1, ws1);
            if (hours == 24) dtostrf((120-i)/5.0, 1, 1, ws1);
            if (hours == 48) dtostrf((120-i)/2.5, 1, 1, ws1);
          #endif
          sprintf(temp, "{x:%s,y:%s},", ws1, ws2);
          www.sendContent(temp);
        }
      }
      dataFile.close();
    }
    if (WATCHDOG_DURING_SD == OFF) { WDT_ENABLE; }
    
    sprintf_P(temp, ChartJs4, rangeMax, rangeMin, rangeStep);
    www.sendContent(temp);
  }

  void makeChartCanvas(const char *chartId) {
    www.sendContent(F("<div style=\"font-size: 14px;  float:left; padding: 10px; margin: 10px; background-color: #EEEEEE; border-style: solid; border-width: 3px; border-color: red;\">\r\n"));
    www.sendContent(F("<canvas id=\"")); www.sendContent(chartId); www.sendContent(F("\" width=\"600\" height=\"200\"></canvas>\r\n"));
    www.sendContent(F("</div>\r\n"));
  }
#endif
