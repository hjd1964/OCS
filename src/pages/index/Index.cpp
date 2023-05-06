// index ----------------------------------------------------------------------
#include "Index.h"
#define WEB_SERVER ON
#if WEB_SERVER == ON
  #include "StatusTile.h"
  #include "WeatherTile.h"
  #include "PowerTile.h"
  #include "ThermostatTile.h"
  #include "LightTile.h"
  #include "RoofTile.h"
  #include "DomeTile.h"

  #include "../../libApp/relay/Relay.h"
  #include "../../observatory/roof/Roof.h"
  #include "../../observatory/dome/Dome.h"
  #include "../../observatory/safety/Safety.h"
  #include "../../observatory/thermostat/Thermostat.h"

  extern unsigned int __bss_end;
  extern unsigned int __heap_start;
  extern void *__brkval;

  void indexPage() {
    {
      char temp[256];

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

      pageHeader(PAGE_INDEX);
    }

    #if STAT == ON
      statusTile();
    #endif
    #if WEATHER == ON
      weatherTile();
    #endif
    #if POWER == ON
      powerTile();
    #endif
    #if THERMOSTAT == ON
      thermostatTile();
    #endif
    #if LIGHT == ON
      lightTile();
    #endif
    #if ROOF == ON
      roofTile();
    #endif
    #if DOME == ON
      domeTile();
    #endif

    {
      char temp[340] = "";

      www.sendContent(F("</div>\r\n"));

      www.sendContent(F("<script>var ajaxPage='index.txt';</script>\n"));

      strcpy_P(temp, html_script_ajax_A);
      www.sendContent(temp);

      strcpy_P(temp, html_script_ajax_B);
      www.sendContent(temp);

      strcpy_P(temp, html_script_ajax_C);
      www.sendContent(temp);

      strcpy_P(temp, html_script_ajax_D);
      www.sendContent(temp);

      strcpy_P(temp, html_script_ajax_E);
      www.sendContent(temp);

      strcpy_P(temp, html_script_ajax_F);
      www.sendContent(temp);

      sprintf_P(temp, html_script_ajax_get, "index-ajax-get.txt");
      www.sendContent(temp);

      www.sendContent(F("</body></html>\r\n"));
      www.sendContent("");
    }
  }

  void indexAjax() {
    www.setContentLength(CONTENT_LENGTH_UNKNOWN);
    www.sendHeader("Cache-Control", "no-cache");
    www.send(200, "text/plain", String());

    #if STAT == ON
      statusTileAjax();
    #endif
    #if WEATHER == ON
      weatherTileAjax();
    #endif
    #if POWER == ON
      powerTileAjax();
    #endif
    #if THERMOSTAT == ON
      thermostatTileAjax();
    #endif
    #if LIGHT == ON
      lightTileAjax();
    #endif
    #if ROOF == ON
      roofTileAjax();
    #endif
    #if DOME == ON
      domeTileAjax();
    #endif

    www.sendContent("");
  }

  void indexAjaxGet() {
    www.setContentLength(CONTENT_LENGTH_UNKNOWN);
    www.sendHeader("Cache-Control", "no-cache");
    www.send(200, "text/plain", String());

    #if POWER == ON
      powerTileGet();
    #endif
    #if THERMOSTAT == ON
      thermostatTileGet();
    #endif
    #if LIGHT == ON
      lightTileGet();
    #endif
    #if ROOF == ON
      roofTileGet();
    #endif
    #if DOME == ON
      domeTileGet();
    #endif

    www.sendContent("");
  }

#endif
