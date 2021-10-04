// power ---------------------------------------------------------------------------------------------
#pragma once

#include "../Common.h"

#if POWER == ON
  extern void powerTile();
  extern void powerContents();

  const char htmlPowerBegin[] PROGMEM = "<div id=\"Power\" class=\"obsControl\" >";
  const char htmlPowerEnd[] PROGMEM = "</div>\r\n";

  const char htmlPowerA[] PROGMEM =
  "<b>Power</b><br />"
  "<form><div>"
  #if POWER_DEVICE1_RELAY != OFF
  "&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE1_RELAY) "\",this.checked)' %___PD1 />&nbsp;&nbsp;" POWER_DEVICE1_NAME "<br />"
  #endif
  #if POWER_DEVICE2_RELAY != OFF
  "&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE2_RELAY) "\",this.checked)' %___PD2 />&nbsp;&nbsp;" POWER_DEVICE2_NAME "<br />"
  #endif
  ;
  const char htmlPowerB[] PROGMEM =
  #if POWER_DEVICE3_RELAY != OFF
  "&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE3_RELAY) "\",this.checked)' %___PD3 />&nbsp;&nbsp;" POWER_DEVICE3_NAME "<br />"
  #endif
  #if POWER_DEVICE4_RELAY != OFF
  "&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE4_RELAY) "\",this.checked)' %___PD4 />&nbsp;&nbsp;" POWER_DEVICE4_NAME "<br />"
  #endif
  "";
  const char htmlPowerC[] PROGMEM =
  #if POWER_DEVICE5_RELAY != OFF
  "&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE5_RELAY) "\",this.checked)' %___PD5 />&nbsp;&nbsp;" POWER_DEVICE5_NAME "<br />"
  #endif
  #if POWER_DEVICE6_RELAY != OFF
  "&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE6_RELAY) "\",this.checked)' %___PD6 />&nbsp;&nbsp;" POWER_DEVICE6_NAME "<br />"
  #endif
  "<br />"
  "</div></form>";
#endif
