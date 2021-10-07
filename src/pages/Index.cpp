// -----------------------------------------------------------------------------------
// Web server, Index page
#include "Index.h"

#include "htmlHeaders.h"
#include "htmlScripts.h"
#include "htmlTabs.h"

#include "StatusTile.h"
#include "WeatherTile.h"
#include "PowerTile.h"
#include "ThermostatTile.h"
#include "LightTile.h"
#include "RoofTile.h"

#include "../lib/relay/Relay.h"
#include "../observatory/roof/Roof.h"
#include "../observatory/safety/Safety.h"
#include "../observatory/thermostat/Thermostat.h"

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

void index() {
  {
    char temp[250] = "";

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
    sprintf(temp, PROD_ABV " %s</b>", ocsVersion); sendHtml(temp);
    strcpy_P(temp, html_pageHeader2); sendHtml(temp);
    strcpy_P(temp, html_links1s); sendHtml(temp);
    #if WEATHER == ON && WEATHER_CHARTS == ON
      strcpy_P(temp, html_links2); sendHtml(temp);
      #if WEATHER_SKY_QUAL == ON || WEATHER_CLOUD_CVR == ON
        strcpy_P(temp, html_links3); sendHtml(temp);
      #endif
    #endif
    strcpy_P(temp, html_pageHeader3); sendHtml(temp);
  }

  statusTile();
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

  {
    char temp[350] = "";

    sendHtml(F("</div>\r\n"));

    // javascript for ajax relay control
    strcpy_P(temp, html_ajax_activeA);
    sendHtml(temp);

    strcpy_P(temp, html_ajax_activeB);
    sendHtml(temp);

    strcpy_P(temp, html_ajax_setRelay);
    sendHtml(temp);

    strcpy_P(temp, html_ajax_setVar);
    sendHtml(temp);

    sendHtmlDone(F("</body></html>\r\n"));
  }
}

void indexAjax() {
  String a = www.arg("press");

  // lights
  #if LIGHT == ON
    #if LIGHT_OUTSIDE_RELAY != OFF
      if (a.equals("light_exit")) { 
        relay.onDelayedOff(LIGHT_OUTSIDE_RELAY, 4*60); // turn off after about 4 minutes
      }
    #endif
  #endif

  // roof
  #if ROOF == ON
    if (a.equals("roof_open")) roof.open();
    if (a.equals("roof_close")) roof.close();
    if (a.equals("roof_override")) roof.setSafetyOverride(true);
    if (a.equals("roof_stop")) { roof.stop(); roof.clearStatus(); }
    a = www.arg("auto_close");
    if (a.equals("true")) safety.setRoofAutoClose(true);
    if (a.equals("false")) safety.setRoofAutoClose(false);
  #endif

  // thermostat
  #if THERMOSTAT == ON
    #if HEAT_RELAY != OFF
      a = www.arg("thermostat_heat");
      if (!a.equals(EmptyStr)) {
        #if STAT_UNITS == IMPERIAL
          float f = 0;
          if (a.toInt() != 0) f = (a.toInt() - 32.0)*(5.0/9.0);
        #else
          float f = a.toFloat();
        #endif
      if (f >= 0.0 && f <= 37.0) thermostat.setHeatSetpoint(f);
    }
  #endif
    #if COOL_RELAY != OFF
      a = www.arg("thermostat_cool");
      if (!a.equals(EmptyStr)) {
        #if STAT_UNITS == IMPERIAL
          float f = 0;
          if (a.toInt() != 0) f = (a.toInt() - 32.0)*(5.0/9.0);
        #else
          float f = atoi(a.c_str());
        #endif
        if (f >= 0.0 && f <= 37.0) thermostat.setCoolSetpoint(f);
      }
    #endif
  #endif
}
