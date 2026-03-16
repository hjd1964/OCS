// -----------------------------------------------------------------------------------
// Weather charts
#include "Weather.h"

#if WEATHER == ON && WEATHER_CHARTS == ON
  #include "../../lib/tasks/OnTask.h"
  #include "../ChartHelp.h"

  void makeChartCanvas(const char *chartId);
  void makeChartJs(const char chartId[], String chartName, int logColumn, int colWidth, int rangeMin, int rangeMax, int rangeStep, long hours);
  void makeChartJs2(const char chartId[], String chartName, int logColumn, int colWidth, int rangeMin, int rangeMax, int rangeStep, long hours, float thresholdValue, String thresholdLabel);

  void weatherPage() {
    char temp[384] = "";
    String a = www.arg("chart");

    // send the header
    www.setContentLength(CONTENT_LENGTH_UNKNOWN);
    www.sendHeader("Cache-Control", "no-cache");
    www.send(200, "text/html", String());

    // send a standard http response header with some css
    strcpy_P(temp, html_head_begin); www.sendContent(temp);
    strcpy_P(temp, html_main_css_begin); www.sendContent(temp); 
    strcpy_P(temp, html_main_css_a); www.sendContent(temp);
    strcpy_P(temp, html_main_css_b); www.sendContent(temp);
    strcpy_P(temp, html_main_css_misc); www.sendContent(temp);
    strcpy_P(temp, html_main_css_a1); www.sendContent(temp);
    strcpy_P(temp, html_main_css_a2); www.sendContent(temp);
    strcpy_P(temp, html_main_css_obsControl); www.sendContent(temp);
    strcpy_P(temp, html_main_css_end); www.sendContent(temp);
    strcpy_P(temp, html_head_end); www.sendContent(temp);

    pageHeader(PAGE_WEATHER);

    int period = 1;
    String periodStr = "";
    if (a.equals(F("recent")) || a.equals(EmptyStr)) { period = 1; periodStr = F("60 minutes"); }
    if (a.equals(F("last24"))) { period = 24; periodStr = F("24 hours"); }
    if (a.equals(F("last48"))) { period = 48; periodStr = F("48 hours"); }
    
    www.sendContent(F("<script type=\"text/javascript\" src=\"Chart.js\"></script>\r\n"));
    www.sendContent(F("<script>\r\n"));
    www.sendContent(F("window.onload = function(){\r\n"));
    #if WEATHER_TEMPERATURE == ON
      #if DISPLAY_UNITS == IMPERIAL
        // a negative column# means this is a temperature and needs conversion to degrees F
        makeChartJs("ambientT", "Outside Temperature F (last "+periodStr+")", -8, 5, -40, 120, 20, period);
      #else
        makeChartJs("ambientT", "Outside Temperature C (last "+periodStr+")", 8, 5, -40, 50, 10, period);
      #endif
    #endif
    #if WEATHER_WIND_SPD == ON
      #if DISPLAY_UNITS == IMPERIAL || DISPLAY_UNITS == BRITISH
        float threshold = WEATHER_WIND_SPD_THRESHOLD * 0.621371; // Convert kph to mph
        makeChartJs2("WS", "Wind Speed mph (last "+periodStr+")", -39, 5, 0, 50, 10, period, threshold, "Safety Threshold");
      #else
        makeChartJs2("WS", "Wind Speed kph (last "+periodStr+")", 39, 5, 0, 80, 10, period, (float)WEATHER_WIND_SPD_THRESHOLD, "Safety Threshold");
      #endif
    #endif
    #if WEATHER_PRESSURE == ON
      #if DISPLAY_UNITS == IMPERIAL
        makeChartJs("BP", "Barometric Pressure inches Hg (last "+periodStr+")", -26, 6, floor((WEATHER_NOMINAL_PRESSURE_SEA_LEVEL - 50)*0.02953), ceil((WEATHER_NOMINAL_PRESSURE_SEA_LEVEL + 40)*0.02953), 1, period);
      #else
        makeChartJs("BP", "Barometric Pressure mb (last "+periodStr+")", 26, 6, WEATHER_NOMINAL_PRESSURE_SEA_LEVEL - 50, WEATHER_NOMINAL_PRESSURE_SEA_LEVEL + 40, 10, period);
      #endif
    #endif
    #if WEATHER_HUMIDITY == ON
      makeChartJs("RH", "Relative Humidity % (last "+periodStr+")", 33, 5, 0, 100, 10, period);
    #endif
    www.sendContent(F("}\r\n"));
    www.sendContent(F("</script>\r\n"));

    strcpy_P(temp, ChartOptions1a); www.sendContent(temp);
    strcpy_P(temp, ChartOptions2); www.sendContent(temp);
    
    #if WEATHER_TEMPERATURE == ON
      makeChartCanvas("ambientT");
    #endif
    #if WEATHER_WIND_SPD == ON
      makeChartCanvas("WS");
    #endif
    #if WEATHER_PRESSURE == ON
      makeChartCanvas("BP");
    #endif
    #if WEATHER_HUMIDITY == ON
      makeChartCanvas("RH");
    #endif

    www.sendContent(F("</div></body></html>\r\n"));
    www.sendContent("");
  }

#endif
