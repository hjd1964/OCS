// roll-off roof -------------------------------------------------------------------------------------------------------------
#pragma once

#include "../Common.h"

#if ROOF == ON
  #include "../lib/ethernet/webServer/WebServer.h"

  extern void roofTile(EthernetClient *client);
  extern void roofContents(EthernetClient *client);

  const char htmlRoof1[] PROGMEM =
  "<div id=\"Roof\" class=\"obsControl\">"
  "<b>Roof or Shutter</b><br />"
  "<div id=\"RoofStatus\" style=\"overflow:hidden;\">";

  const char htmlRoof2[] PROGMEM =
  "</div>"
  "<div style=\"text-align: center\">"
  "<br />"
  #if !(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)
    #if ROOF_SINGLE_OPEN_CLOSE_STOP_RELAY == ON
      "<input type=\"button\" onclick='SetVar(\"press\",\"roof_stop\")' value=\"Press!\" />&nbsp;&nbsp;&nbsp;"
    #else
      "<input type=\"button\" onclick='SetVar(\"press\",\"roof_stop\")' value=\"Stop!\" />&nbsp;&nbsp;&nbsp;"
    #endif
  #endif
  #if ROOF_USER_SAFETY_OVERRIDE == ON
    "<input type=\"button\" onclick='SetVar(\"press\",\"roof_override\")' value=\"Safety Override\" />"
  #endif
  "<br />"
  "<input type=\"button\" onclick='SetVar(\"press\",\"roof_open\")' value=\"Open Roof\" />&nbsp;&nbsp;&nbsp;"
  "<input type=\"button\" onclick='SetVar(\"press\",\"roof_close\")' value=\"Close Roof\" /><br />"
  "<br />"
  #if ROOF_AUTOCLOSE_DAWN == ON
    "<input type=\"checkbox\"  onclick='SetVar(\"auto_close\",this.checked)' %___ACL />&nbsp;Automatically close at dawn<br />"
  #endif
  "</div>"
  "</div>\r\n";

  const char htmlInnerRoofStat[] PROGMEM =
  "&nbsp;&nbsp;Status <div class=\"aStatus\">%s</div><br />"
  "<div style=\"text-align:center\">%s</div>";

#endif
