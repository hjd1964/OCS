// -----------------------------------------------------------------------------------
// Weather charts
#include "SkyConditions.h"

#if WEATHER == ON && WEATHER_CHARTS == ON
  #include "../htmlHeaders.h"
  #include "../htmlScripts.h"
  #include "../Page.h"

  #include "../../lib/tasks/OnTask.h"
  #include "../ChartHelp.h"

  void makeChartCanvas(const char *chartId);
  void makeChartJs(const char chartId[], String chartName, int logColumn, int colWidth, int rangeMin, int rangeMax, int rangeStep, long hours);

  #if WEATHER_SKY_QUAL == ON || WEATHER_CLOUD_CVR == ON
    void skyPage() {
      char temp[256] = "";
      String a = www.arg("chart");

      // send the header
      www.setContentLength(CONTENT_LENGTH_UNKNOWN);
      www.sendHeader("Cache-Control", "no-cache");
      www.send(200, "text/html", String());

      // send a standard http response header with some css
      strcpy_P(temp, html_head_begin); www.sendContent(temp);
      strcpy_P(temp, html_main_css1); www.sendContent(temp); 
      strcpy_P(temp, html_main_css2); www.sendContent(temp);
      strcpy_P(temp, html_main_css4); www.sendContent(temp);
      strcpy_P(temp, html_main_css6); www.sendContent(temp);
      strcpy_P(temp, html_main_css7); www.sendContent(temp);
      strcpy_P(temp, html_main_css8); www.sendContent(temp);
      strcpy_P(temp, html_main_css10); www.sendContent(temp);
      strcpy_P(temp, html_main_css11); www.sendContent(temp);
      strcpy_P(temp, html_head_end); www.sendContent(temp);
    
      pageHeader(PAGE_SKY_CONDITIONS);

      int period = 1;
      String periodStr = "";
      if (a.equals(F("recent")) || a.equals(EmptyStr)) { period = 1; periodStr = F("60 minutes"); }
      if (a.equals(F("last24"))) { period = 24; periodStr = F("24 hours"); }
      if (a.equals(F("last48"))) { period = 48; periodStr = F("48 hours"); }
      
      www.sendContent(F("<script type=\"text/javascript\" src=\"Chart.js\"></script>\r\n"));
      www.sendContent(F("<script>\r\n"));
      www.sendContent(F("window.onload = function(){\r\n"));

      #if WEATHER_SKY_QUAL == ON
        makeChartJs("SQ", "Sky Quality mag/sq arc-sec (last "+periodStr+")", 45, 5, 1, 22, 5, period);
      #endif

      #if WEATHER_CLOUD_CVR == ON
        makeChartJs("skyT", "Sky IR Temperature C (last "+periodStr+")", 14, 5, -40, 5, 5, period);
      #endif

      www.sendContent(F("}\r\n"));

      www.sendContent(F("</script>\r\n"));

      strcpy_P(temp,ChartOptions1b);
      www.sendContent(temp);

      strcpy_P(temp,ChartOptions2);
      www.sendContent(temp);

      #if WEATHER_SKY_QUAL == ON
        makeChartCanvas("SQ");
      #endif

      #if WEATHER_CLOUD_CVR == ON
        makeChartCanvas("skyT");
      #endif

      www.sendContent(F("</div></body></html>\r\n"));
      www.sendContent("");
    }
  #endif

#endif
