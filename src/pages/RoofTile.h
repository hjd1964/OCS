// roll-off roof -------------------------------------------------------------------------------------------------------------
#pragma once

#include "../Common.h"

#if ROOF == ON

  #include "../pages/Pages.h"

  extern void roofTile();
  extern void roofContents();

  const char htmlRoof1[] PROGMEM =
  "<div id=\"Roof\" class=\"obsControl\">"
  "<b>Roof or Shutter</b><br />"
  "<div id=\"RoofStatus\" style=\"overflow:hidden;\">";

  const char htmlRoof2[] PROGMEM =
  "</div>"
  "<div style=\"text-align: center\">"
  #if !(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)
    #if ROOF_SINGLE_OPEN_CLOSE_STOP_RELAY == ON
      "<input type=\"button\" style=\"width:6em;height:2.5em;border-color:#ff2222;margin-bottom:5px;margin-top:5px;\" onclick='SetVar(\"press\",\"roof_stop\")' value=\"Press!\" />&nbsp;&nbsp;&nbsp;"
    #else
      "<input type=\"button\" style=\"width:5em;height:2.5em;border-color:#ff2222;margin-bottom:5px;margin-top:5px;\" onclick='SetVar(\"press\",\"roof_stop\")' value=\"Stop!\" />&nbsp;&nbsp;&nbsp;"
    #endif
  #endif
  #if ROOF_USER_SAFETY_OVERRIDE == ON
    "<input type=\"button\" onclick='SetVar(\"press\",\"roof_override\")' value=\"Safety Override\" />"
  #endif
  "<br />";

  const char htmlRoof3[] PROGMEM =
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
  "<div style=\"text-align:center\"><div style=\"color: %s;\">%s</div></div>";

#endif
