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

#include "../observatory/roof/Roof.h"
#include "../observatory/safety/Safety.h"

#if OPERATIONAL_MODE != WIFI
void index(EthernetClient *client) {
#else
void index() {
#endif
  char temp[800] = "";

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

  strcpy_P(temp, html_head3); sendHtml(temp);

  strcpy_P(temp, html_pageHeader1); sendHtml(temp);
  sprintf(temp, "%s</b>", ocsVersion); sendHtml(temp);
  strcpy_P(temp, html_pageHeader2); sendHtml(temp);
  strcpy_P(temp, html_links1s); sendHtml(temp);
  #if WEATHER == ON && WEATHER_CHARTS == ON
    strcpy_P(temp, html_links2); sendHtml(temp);
    #if WEATHER_SKY_QUAL == ON || WEATHER_CLOUD_CVR == ON
      strcpy_P(temp, html_links3); sendHtml(temp);
    #endif
  #endif
  strcpy_P(temp, html_pageHeader3); sendHtml(temp);

  statusTile(client);

  #if WEATHER == ON
    weatherTile(client);
  #endif

  #if POWER == ON
    powerTile(client);
  #endif

  #if THERMOSTAT == ON
    thermostatTile(client);
  #endif

  #if LIGHT == ON
    lightTile(client);
  #endif

  #if ROOF == ON
    roofTile(client);
  #endif

  strcpy_P(temp,"</div>\r\n");
  sendHtml(temp);
  
  // javascript for ajax relay control
  strcpy_P(temp, html_ajax_active);
  sendHtml(temp);

  strcpy_P(temp, html_ajax_setRelay);
  sendHtml(temp);

  strcpy_P(temp, html_ajax_setVar);
  sendHtml(temp);

  strcpy_P(temp,"</body></html>\r\n");
  sendHtmlDone(temp);
}

#if OPERATIONAL_MODE != WIFI
void indexAjax(EthernetClient *client) {
#else
void indexAjax() {
#endif
  String a = www.arg("press");

  // lights
  #if LIGHT == ON
    #if LIGHT_OUTSIDE_RELAY != OFF
      if (a=="light_exit") { 
        setRelayOnDelayedOff(atoi(LIGHT_OUTSIDE_RELAY),4*60); // turn off after about 4 minutes
      }
    #endif
  #endif

  // roll-off roof
  #if ROOF == ON
    if (a == "roof_open") roof.open();
    if (a == "roof_close") roof.close();
    if (a == "roof_override") roof.setSafetyOverride(true);
    if (a == "roof_stop") { roof.stop(); roof.clearStatus(); }
    a = www.arg("auto_close");
    if (a == "true") safety.setRoofAutoClose(true);
    if (a == "false") safety.setRoofAutoClose(false);
  #endif

  // thermostat
  #if THERMOSTAT == ON
    #if HEAT_RELAY != OFF
      a=www.arg("thermostat_heat");
      if (a!="") {
        #if STAT_UNITS == IMPERIAL
          float f = 0;
          if (atoi(a.c_str())!=0) f=(float(atoi(a.c_str()))-32.0)*(5.0/9.0);
        #else
          float f=atoi(a.c_str());
        #endif
      if (f >= 0.0 && f <= 37.0) setHeatSetpoint(f);
    }
  #endif
    #if COOL_RELAY != OFF
      a = www.arg("thermostat_cool");
      if (a!="") {
        #if STAT_UNITS == IMPERIAL
            float f=0; if (atoi(a.c_str())!=0) f=(float(atoi(a.c_str()))-32.0)*(5.0/9.0);
        #else
            float f=atoi(a.c_str());
        #endif
        if (f >= 0.0 && f <= 37.0) setCoolSetpoint(f);
      }
    #endif
  #endif
}