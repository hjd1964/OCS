// help for charting sensor readings
#include "ChartHelp.h"

#if WEATHER == ON && WEATHER_CHARTS == ON
  #include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

  #include "../lib/watchdog/Watchdog.h"
  #include "htmlHeaders.h"
  #include "htmlScripts.h"

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
    char fileName[40];
    char temp[256] = "";
    char logText[84] = "";
    char logItemText[84] = "";
    char xAxisText[12] = "";
    long rec;
    long recOffset = 0;
    float unitsDivisor;
    float sign;

    sprintf_P(temp, html_script_chartJs_A, chartId, chartId, chartId);
    www.sendContent(temp);

    www.sendContent(chartName);

    strcpy_P(temp, html_script_chartJs_B);
    www.sendContent(temp);

    time_t t = now();

    rec = logRecordLocation(t) - LOG_RECORDS_PER_HOUR*hours;
    while (rec < 0) {
      rec += LOG_RECORDS_PER_DAY;
      t -= 24L*60L*60L;
    }
    sprintf(fileName, FS_PREFIX "L%02d%02d%02d.TXT", year(t) - 2000, month(t), day(t));

    if (WATCHDOG_DURING_SD == OFF) { watchdog.disable(); }
    File dataFile = FS.open(fileName, FILE_READ);
    if (dataFile) {
      V("MSG: makeChartJs, open log file "); V(fileName); V(" for "); V(chartId); V(" at record "); V(rec); V(" of "); VL(LOG_RECORDS_PER_DAY);
      //                            12
      for (long i = 0; i < LOG_RECORDS_PER_HOUR; i++) {
        if (((rec + i*hours) - recOffset) >= LOG_RECORDS_PER_DAY) {
          dataFile.close();
          recOffset = rec + i*hours;
          t += 24L*60L*60L;
          sprintf(fileName, FS_PREFIX "L%02d%02d%02d.TXT", year(t) - 2000, month(t), day(t));
          dataFile = FS.open(fileName, FILE_READ);
          if (!dataFile) break;

          V("MSG: makeChartJs, next log file "); V(fileName); V(" for "); V(chartId); V(" at record "); V(rec); V(" of "); VL(LOG_RECORDS_PER_DAY);
        }
        dataFile.seek(((rec + i*hours) - recOffset)*80L);

        dataFile.read((unsigned char*)logText, 80);

        logText[abs(logColumn) + colWidth] = 0;
        int j = abs(logColumn);
        while (logText[j] == ' ' && logText[j] != 0) j++;
        strcpy(logItemText, (char*)&(logText[j]));
        if (logItemText[0] != 0) {
          float f = atof(logItemText);
          if (logColumn == -8)  f = f*(9.0/5.0) + 32.0; // temperature C to F
          if (logColumn == -39) f = f*0.621371;         // wind kph to mph
          if (logColumn == -26) f = f*0.02953;          // pressure in inches
          if (isnan(f))         f = rangeMax;           // handle bad/no data
          if (logColumn == -26) dtostrf(f, 1, 3, logItemText); else dtostrf(f, 1, 1, logItemText);

          if (hours >= 4) unitsDivisor = 3600.0F; else unitsDivisor = 60.0F;
          if (REVERSE_WEATHER_CHART_X_AXIS == ON) sign = -1.0F; else sign = 1.0F;
          dtostrf(sign*((LOG_RECORDS_PER_HOUR - i)*hours)*((LOG_PERIOD_SECONDS)/unitsDivisor), 1, 1, xAxisText);

          sprintf(temp, "{x:%s,y:%s},", xAxisText, logItemText);
          www.sendContent(temp);
        }
      }
      dataFile.close();
    } else {
      V("MSG: makeChartJs, opening log file "); V(fileName); VLF(" failed!");
    }
    if (WATCHDOG_DURING_SD == OFF) { watchdog.enable(8); }
    
    sprintf_P(temp, html_script_chartJs_C, rangeMax, rangeMin, rangeStep);
    www.sendContent(temp);
  }

  // transmits an Chart.js chart with two data series to the html client
  // \param chartId: the html id tag for the chart to dispay
  // \param chartName: the name to display on the chart
  // \param logColumn: the column position (in chars) of the data being charted
  // \param colWidth: the width (in chars) of the data being charted
  // \param rangeMin: the low value on the chart
  // \param rangeMax: the high value on the chart
  // \param rangeStep: the step size on the chart
  // \param hours: the number of hours of data to display
  // \param thresholdValue: the constant value to plot as a second series
  // \param thresholdLabel: the label for the threshold line
  void makeChartJs2(const char chartId[], String chartName, int logColumn, int colWidth, int rangeMin, int rangeMax, int rangeStep, long hours, float thresholdValue, String thresholdLabel) {
    char fileName[40];
    char temp[256] = "";
    char logText[84] = "";
    char logItemText[84] = "";
    char xAxisText[12] = "";
    char thresholdText[12] = "";
    long rec;
    long recOffset = 0;
    float unitsDivisor;
    float sign;

    sprintf_P(temp, html_script_chartJs_A, chartId, chartId, chartId);
    www.sendContent(temp);

    www.sendContent(chartName);

    strcpy_P(temp, html_script_chartJs_B);
    www.sendContent(temp);

    time_t t = now();

    rec = logRecordLocation(t) - LOG_RECORDS_PER_HOUR*hours;
    while (rec < 0) {
      rec += LOG_RECORDS_PER_DAY;
      t -= 24L*60L*60L;
    }
    sprintf(fileName, FS_PREFIX "L%02d%02d%02d.TXT", year(t) - 2000, month(t), day(t));

    if (WATCHDOG_DURING_SD == OFF) { watchdog.disable(); }
    File dataFile = FS.open(fileName, FILE_READ);
    if (dataFile) {
      V("MSG: makeChartJs2, open log file "); V(fileName); V(" for "); V(chartId); V(" at record "); V(rec); V(" of "); VL(LOG_RECORDS_PER_DAY);
      
      for (long i = 0; i < LOG_RECORDS_PER_HOUR; i++) {
        if (((rec + i*hours) - recOffset) >= LOG_RECORDS_PER_DAY) {
          dataFile.close();
          recOffset = rec + i*hours;
          t += 24L*60L*60L;
          sprintf(fileName, FS_PREFIX "L%02d%02d%02d.TXT", year(t) - 2000, month(t), day(t));
          dataFile = FS.open(fileName, FILE_READ);
          if (!dataFile) break;

          V("MSG: makeChartJs2, next log file "); V(fileName); V(" for "); V(chartId); V(" at record "); V(rec); V(" of "); VL(LOG_RECORDS_PER_DAY);
        }
        dataFile.seek(((rec + i*hours) - recOffset)*80L);

        dataFile.read((unsigned char*)logText, 80);

        logText[abs(logColumn) + colWidth] = 0;
        int j = abs(logColumn);
        while (logText[j] == ' ' && logText[j] != 0) j++;
        strcpy(logItemText, (char*)&(logText[j]));
        if (logItemText[0] != 0) {
          float f = atof(logItemText);
          if (logColumn == -8)  f = f*(9.0/5.0) + 32.0; // temperature C to F
          if (logColumn == -39) f = f*0.621371;         // wind kph to mph
          if (logColumn == -26) f = f*0.02953;          // pressure in inches
          if (isnan(f))         f = rangeMax;           // handle bad/no data
          if (logColumn == -26) dtostrf(f, 1, 3, logItemText); else dtostrf(f, 1, 1, logItemText);

          if (hours >= 4) unitsDivisor = 3600.0F; else unitsDivisor = 60.0F;
          if (REVERSE_WEATHER_CHART_X_AXIS == ON) sign = -1.0F; else sign = 1.0F;
          dtostrf(sign*((LOG_RECORDS_PER_HOUR - i)*hours)*((LOG_PERIOD_SECONDS)/unitsDivisor), 1, 1, xAxisText);

          sprintf(temp, "{x:%s,y:%s},", xAxisText, logItemText);
          www.sendContent(temp);
        }
      }
      dataFile.close();
    } else {
      V("MSG: makeChartJs2, opening log file "); V(fileName); VLF(" failed!");
    }
    if (WATCHDOG_DURING_SD == OFF) { watchdog.enable(8); }
    
    // Send the closing for first dataset and open second dataset for threshold
    www.sendContent(F("]},{label:'"));
    www.sendContent(thresholdLabel);
    www.sendContent(F("',borderColor: \"" COLOR_CHART_THRESHOLD "\",borderWidth:2,borderDash:[5,5],fill:false,pointRadius:0,data:["));
    
    // Generate threshold data points
    dtostrf(thresholdValue, 1, 1, thresholdText);
    for (long i = 0; i < LOG_RECORDS_PER_HOUR; i++) {
      if (hours >= 4) unitsDivisor = 3600.0F; else unitsDivisor = 60.0F;
      if (REVERSE_WEATHER_CHART_X_AXIS == ON) sign = -1.0F; else sign = 1.0F;
      dtostrf(sign*((LOG_RECORDS_PER_HOUR - i)*hours)*((LOG_PERIOD_SECONDS)/unitsDivisor), 1, 1, xAxisText);
      
      sprintf(temp, "{x:%s,y:%s},", xAxisText, thresholdText);
      www.sendContent(temp);
    }
    
    sprintf_P(temp, html_script_chartJs_C, rangeMax, rangeMin, rangeStep);
    www.sendContent(temp);
  }

  void makeChartCanvas(const char *chartId) {
    www.sendContent(F("<div style=\"font-size: 14px;  float:left; padding: 10px; margin: 10px; background-color: " COLOR_CHART_CANVAS "; border-style: solid; border-width: 3px; border-color: red;\">\r\n"));
    www.sendContent(F("<canvas id=\"")); www.sendContent(chartId); www.sendContent(F("\" width=\"600\" height=\"200\"></canvas>\r\n"));
    www.sendContent(F("</div>\r\n"));
  }
#endif
