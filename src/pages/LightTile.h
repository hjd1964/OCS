// light ---------------------------------------------------------------------------------------------------------------------
#pragma once

#include "../Common.h"

#if LIGHT == ON
  #include "../lib/ethernet/webServer/WebServer.h"

  extern void lightTile(EthernetClient *client);
  extern void lightContents(EthernetClient *client);

  const char htmlLight1[] PROGMEM = "<div id=\"Light\" class=\"obsControl\" >";
  const char htmlLight3[] PROGMEM = "</div>\r\n";

  const char htmlLighting1[] PROGMEM =
  "<b>Lighting</b><br />"
  "<form><div>"
  "&nbsp;&nbsp;"
  #if LIGHT_WRR_RELAY != OFF
  "<input type=\"checkbox\" onclick='SetRelay(\"" STR(LIGHT_WRR_RELAY) "\",this.checked)' %___WRR />&nbsp;Red "
  #endif
  #if LIGHT_WRW_RELAY != OFF
  "<input type=\"checkbox\" onclick='SetRelay(\"" STR(LIGHT_WRW_RELAY) "\",this.checked)' %___WRW />&nbsp;White"
  #endif
  #if LIGHT_WRR_RELAY != OFF || LIGHT_WRW_RELAY != OFF
  " Warm Rm Lights<br />&nbsp;&nbsp;"
  #endif
  ;
  const char htmlLighting2[] PROGMEM =
  #if LIGHT_ORR_RELAY != OFF
  "<input type=\"checkbox\" onclick='SetRelay(\"" STR(LIGHT_ORR_RELAY) "\",this.checked)' %___ORR />&nbsp;Red "
  #endif
  #if LIGHT_ORW_RELAY != OFF
  "<input type=\"checkbox\" onclick='SetRelay(\"" STR(LIGHT_ORW_RELAY) "\",this.checked)' %___ORW />&nbsp;White"
  #endif
  #if LIGHT_ORR_RELAY != OFF || LIGHT_ORW_RELAY != OFF
  " Obs Rm Lights<br />&nbsp;&nbsp;"
  #endif
  "<br />"
  ;
  const char htmlLighting3[] PROGMEM =
  #if LIGHT_OUTSIDE_RELAY != OFF
  "<br />"
  "&nbsp;&nbsp;<input type=\"button\" onclick='SetVar(\"press\",\"light_exit\")' value=\"Exit\" />&nbsp;&nbsp;Outside Light Timer<br />"
  #endif
  "</div></form>";

#endif
