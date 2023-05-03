// -----------------------------------------------------------------------------------
// Web server, Index page
#include "Index.h"

#if WEB_SERVER == ON

#include "../htmlHeaders.h"
#include "../htmlScripts.h"
#include "../Page.h"

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
    char temp[250] = "";

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
    char temp[400] = "";

    www.sendContent(F("</div>\r\n"));

    // javascript for ajax relay control
    strcpy_P(temp, html_ajax_activeA);
    www.sendContent(temp);

    strcpy_P(temp, html_ajax_activeB);
    www.sendContent(temp);

    strcpy_P(temp, html_ajax_setRelay);
    www.sendContent(temp);

    strcpy_P(temp, html_ajax_setVar);
    www.sendContent(temp);

    www.sendContent(F("</body></html>\r\n"));
    www.sendContent("");
  }
}

void indexAjax() {
  String press = www.arg("press");
  
  // lights
  #if LIGHT == ON
    #if LIGHT_OUTSIDE_RELAY != OFF
      if (press.equals("light_exit")) { 
        relay.onDelayedOff(LIGHT_OUTSIDE_RELAY, 4*60); // turn off after about 4 minutes
      }
    #endif
  #endif

  // roof
  #if ROOF == ON
    if (press.equals("roof_open")) roof.open();
    if (press.equals("roof_close")) roof.close();
    if (press.equals("roof_override")) roof.setSafetyOverride(true);
    if (press.equals("roof_stop")) { roof.stop(); roof.clearStatus(); }
    String autoclose = www.arg("auto_close");
    if (autoclose.equals("true")) safety.roofAutoClose = true;
    if (autoclose.equals("false")) safety.roofAutoClose = false;
  #endif

  // dome
  #if DOME == ON
    String azm = www.arg("dome_azm");
    if (!azm.equals(EmptyStr)) {
      int z = azm.toInt();
      if (z >= 0 && z <= 360) dome.setTargetAzimuth(z);
    }

    #if AXIS2_DRIVER_MODEL != OFF
      String alt = www.arg("dome_alt");
      if (!alt.equals(EmptyStr)) {
        int a = alt.toInt();
        if (a >= 0 && a <= 90) dome.setTargetAltitude(a);
      }
    #endif

    if (press.equals("dome_goto")) {
      dome.gotoAzimuthTarget();
      #if AXIS2_DRIVER_MODEL != OFF
        dome.gotoAltitudeTarget();
      #endif
    }
    if (press.equals("dome_sync")) {
      dome.syncAzimuthTarget();
    }
    if (press.equals("dome_stop")) dome.stop();
    if (press.equals("dome_home")) dome.findHome();
    if (press.equals("dome_reset")) dome.reset();
    if (press.equals("dome_park")) dome.park();
    if (press.equals("dome_unpark")) dome.unpark();
    if (press.equals("dome_setpark")) dome.setpark();
  #endif

  // thermostat
  #if THERMOSTAT == ON
    #if HEAT_RELAY != OFF
      String heat = www.arg("thermostat_heat");
      if (!heat.equals(EmptyStr)) {
        #if STAT_UNITS == IMPERIAL
          float f = 0;
          if (heat.toInt() != 0) f = (heat.toInt() - 32.0)*(5.0/9.0);
        #else
          float f = heat.toFloat();
        #endif
      if (f >= 0.0 && f <= 37.0) thermostat.setHeatSetpoint(f);
    }
    #endif
    #if COOL_RELAY != OFF
      String cool = www.arg("thermostat_cool");
      if (!cool.equals(EmptyStr)) {
        #if STAT_UNITS == IMPERIAL
          float f = 0;
          if (cool.toInt() != 0) f = (cool.toInt() - 32.0)*(5.0/9.0);
        #else
          float f = atoi(cool.c_str());
        #endif
        if (f >= 0.0 && f <= 37.0) thermostat.setCoolSetpoint(f);
      }
    #endif
    #if HUMIDITY_RELAY != OFF
      String humidity = www.arg("thermostat_humidity");
      if (!humidity.equals(EmptyStr)) {
        float f = atoi(humidity.c_str());
        if (f >= 0.0 && f <= 75.0) thermostat.setHumiditySetpoint(f);
      }
    #endif
  #endif
}

#endif
