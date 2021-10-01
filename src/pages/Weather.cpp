// -----------------------------------------------------------------------------------
// Weather charts
#include "Weather.h"

#if WEATHER == ON && WEATHER_CHARTS == ON
  #include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

  #include <SD.h>

  #include "htmlHeaders.h"
  #include "htmlScripts.h"
  #include "htmlTabs.h"

  void makeChartCanvas(EthernetClient *client, const char *chartId);
  void makeChartJs(EthernetClient *client, const char chartId[], String chartName, int logColumn, int colWidth, int rangeMin, int rangeMax, int rangeStep, long hours);

  #if OPERATIONAL_MODE != WIFI
  void weatherPage(EthernetClient *client) {
  #else
  void weatherPage() {
  #endif
    char temp[512] = "";
    String a = www.arg("chart");

    sendHtmlStart();

    // send a standard http response header with some css
    strcpy_P(temp, html_head1); sendHtml(temp);
    strcpy_P(temp, html_main_css1); sendHtml(temp); 
    strcpy_P(temp, html_main_css2); sendHtml(temp);
    strcpy_P(temp, html_main_css4); sendHtml(temp);
    strcpy_P(temp, html_main_css6); sendHtml(temp);
    strcpy_P(temp, html_main_css7); sendHtml(temp);
    strcpy_P(temp, html_main_css8); sendHtml(temp);
    strcpy_P(temp, html_main_css10); sendHtml(temp);
    strcpy_P(temp, html_main_css11); sendHtml(temp);

    strcpy_P(temp, html_head3); sendHtml(temp);

    strcpy_P(temp, html_pageHeader1); sendHtml(temp);
    strcpy_P(temp, html_pageHeader2); sendHtml(temp);
    strcpy_P(temp, html_links1); sendHtml(temp);
    strcpy_P(temp, html_links2s); sendHtml(temp);
    #if WEATHER_SKY_QUAL == ON || WEATHER_CLOUD_CVR == ON
      strcpy_P(temp, html_links3); sendHtml(temp);
    #endif
    strcpy_P(temp, html_pageHeader3); sendHtml(temp);

    int period = 1;
    String periodStr = "";
    if (a.equals("recent") || a.equals(EmptyStr)) { period = 1; periodStr = "60 minutes"; }
    if (a.equals("last24")) { period = 24; periodStr = "24 hours"; }
    if (a.equals("last48")) { period = 48; periodStr = "48 hours"; }
    
    sendHtml(F("<script type=\"text/javascript\" src=\"Chart.js\"></script>\r\n"));
    sendHtml(F("<script>\r\n"));
    sendHtml(F("window.onload = function(){\r\n"));
    #if WEATHER_TEMPERATURE == ON
      #if STAT_UNITS == IMPERIAL
        // a negative column# means this is a temperature and needs conversion to degrees F
        makeChartJs(client,"ambientT","Outside Temperature F (last "+periodStr+")",-8,5,-40,120,20,period);
      #else
        makeChartJs(client,"ambientT","Outside Temperature C (last "+periodStr+")",8,5,-40,50,10,period);
      #endif
    #endif
    #if WEATHER_WIND_SPD == ON
      #if STAT_UNITS == IMPERIAL
        makeChartJs(client,"WS","Wind Speed mph (last "+periodStr+")",-39,5,0,50,10,period);
      #else
        makeChartJs(client,"WS","Wind Speed kph (last "+periodStr+")",39,5,0,80,10,period);
      #endif
    #endif
    #if WEATHER_PRESSURE == ON
      #if STAT_UNITS == IMPERIAL
        makeChartJs(client,"BP","Barometric Pressure inches Hg (last "+periodStr+")",-26,6,floor((WEATHER_NOMINAL_PRESSURE_SEA_LEVEL-50)*0.02953),ceil((WEATHER_NOMINAL_PRESSURE_SEA_LEVEL+40)*0.02953),1,period);
      #else
        makeChartJs(client,"BP","Barometric Pressure mb (last "+periodStr+")",26,6,WEATHER_NOMINAL_PRESSURE_SEA_LEVEL-50,WEATHER_NOMINAL_PRESSURE_SEA_LEVEL+40,10,period);
      #endif
    #endif
    #if WEATHER_HUMIDITY == ON
      makeChartJs(client,"RH","Relative Humidity % (last "+periodStr+")",33,5,0,100,10,period);
    #endif
    sendHtml(F("}\r\n"));
    sendHtml(F("</script>\r\n"));

    strcpy_P(temp,ChartOptions1a); sendHtml(temp);
    strcpy_P(temp,ChartOptions2); sendHtml(temp);
    
    #if WEATHER_TEMPERATURE == ON
      makeChartCanvas(client, "ambientT");
    #endif
    #if WEATHER_WIND_SPD == ON
      makeChartCanvas(client, "WS");
    #endif
    #if WEATHER_PRESSURE == ON
      makeChartCanvas(client, "BP");
    #endif
    #if WEATHER_HUMIDITY == ON
      makeChartCanvas(client, "RH");
    #endif

    sendHtmlDone("</div></body></html>\r\n");
  }

  #if WEATHER_SKY_QUAL == ON || WEATHER_CLOUD_CVR == ON
    #if OPERATIONAL_MODE != WIFI
    void skyPage(EthernetClient *client) {
    #else
    void skyPage() {
    #endif
      char temp[512] = "";
      String a = www.arg("chart");

      sendHtmlStart();
      
      // send a standard http response header with some css
      strcpy_P(temp, html_head1); sendHtml(temp);
      strcpy_P(temp, html_main_css1); sendHtml(temp); 
      strcpy_P(temp, html_main_css2); sendHtml(temp);
      strcpy_P(temp, html_main_css4); sendHtml(temp);
      strcpy_P(temp, html_main_css6); sendHtml(temp);
      strcpy_P(temp, html_main_css7); sendHtml(temp);
      strcpy_P(temp, html_main_css8); sendHtml(temp);
      strcpy_P(temp, html_main_css10); sendHtml(temp);
      strcpy_P(temp, html_main_css11); sendHtml(temp);

      strcpy_P(temp, html_head3); sendHtml(temp);

      strcpy_P(temp, html_pageHeader1); sendHtml(temp);
      strcpy_P(temp, html_pageHeader2); sendHtml(temp);
      strcpy_P(temp, html_links1);  sendHtml(temp);
      strcpy_P(temp, html_links2);  sendHtml(temp);
      strcpy_P(temp, html_links3s); sendHtml(temp);
      strcpy_P(temp, html_pageHeader3); sendHtml(temp);

      int period = 1;
      String periodStr = "";
      if (a.equals("recent") || a.equals(EmptyStr)) { period = 1; periodStr = "60 minutes"; }
      if (a.equals("last24")) { period = 24; periodStr = "24 hours"; }
      if (a.equals("last48")) { period = 48; periodStr = "48 hours"; }
      
      sendHtml(F("<script type=\"text/javascript\" src=\"Chart.js\"></script>\r\n"));
      sendHtml(F("<script>\r\n"));
      sendHtml(F("window.onload = function(){\r\n"));

      #if WEATHER_SKY_QUAL == ON
        makeChartJs(client, "SQ", "Sky Quality mag/sq arc-sec (last "+periodStr+")", 45, 5, 1, 22, 5, period);
      #endif

      #if WEATHER_CLOUD_CVR == ON
        makeChartJs(client, "skyT", "Sky IR Temperature C (last "+periodStr+")", 14, 5, -40, 5, 5, period);
      #endif

      sendHtml("}\r\n");

      sendHtml("</script>\r\n");

      strcpy_P(temp,ChartOptions1b);
      sendHtml(temp);

      strcpy_P(temp,ChartOptions2);
      sendHtml(temp);

      #if WEATHER_SKY_QUAL == ON
        makeChartCanvas(client,"SQ");
      #endif

      #if WEATHER_CLOUD_CVR == ON
        makeChartCanvas(client,"skyT");
      #endif

      sendHtmlDone("</div></body></html>\r\n");
    }
  #endif

  void makeChartJs(EthernetClient *client, const char chartId[], String chartName, int logColumn, int colWidth, int rangeMin, int rangeMax, int rangeStep, long hours) {
    char temp[256] = "";
    char temp1[256] = "";
    char ws1[90] = "";
    char ws2[90] = "";
    long rec = 0;
    long k = 0;

    strcpy_P(temp1, ChartJs1);

    sprintf(temp, temp1, chartId, chartId, chartId);
    sendHtml(temp);

    sendHtml(chartName);

    strcpy_P(temp, ChartJs3);
    sendHtml(temp);

    time_t t = now();

    rec = logRecordLocation(t) - 120L*hours;
    while (rec<0) { rec += 2880; t -= 24L*60L*60L; }
    int y = year(t);
    y -= 2000;
    sprintf(temp, "%02d%02d%02d", y, month(t), day(t));
    String fn = "L" + String(temp) + ".TXT";

    //Serial.print("Primary log="); Serial.println(fn);
    //Serial.print("Reading "); Serial.print(120); Serial.print(" records from rec#"); Serial.println(rec);

    if (WATCHDOG_DURING_SD == OFF) { WDT_DISABLE; }
    File dataFile = SD.open(fn, FILE_READ);
    if (dataFile) {
      for (long i = 0; i < 120; i++) {
        if (((rec + i*hours) - k) >= 2880L) {
          dataFile.close();
          k = rec + i*hours;
          t += 24L*60L*60L;
          y = year(t);
          y -= 2000;
          sprintf(temp, "%02d%02d%02d", y, month(t), day(t));
          fn = "L" + String(temp) + ".TXT";
          dataFile = SD.open(fn, FILE_READ);
          if (!dataFile) break;

          //Serial.print("Secondary log="); Serial.println(fn);
          //Serial.print("Reading "); Serial.print(120-i); Serial.print(" records from rec#"); Serial.println(0);
        }
        dataFile.seek(((rec+i*hours)-k)*80L);

        //if (chartId[0]=='B') Serial.println(((rec+i*step)-k));

        dataFile.read(ws1, 80); ws1[abs(logColumn) + colWidth] = 0;
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
          sendHtml(temp);
        }
      }
      dataFile.close();
    }
    if (WATCHDOG_DURING_SD == OFF) { WDT_ENABLE; }
    
    strcpy_P(temp1,ChartJs4); sprintf(temp,temp1,rangeMax,rangeMin,rangeStep);
    sendHtml(temp);
  }

  void makeChartCanvas(EthernetClient *client, const char *chartId) {
    sendHtml(F("<div style=\"font-size: 14px;  float:left; padding: 10px; margin: 10px; background-color: #EEEEEE; border-style: solid; border-width: 3px; border-color: red;\">\r\n"));
    sendHtml(F("<canvas id=\"")); sendHtml(chartId); sendHtml(F("\" width=\"600\" height=\"200\"></canvas>\r\n"));
    sendHtml(F("</div>\r\n"));
  }

#endif
