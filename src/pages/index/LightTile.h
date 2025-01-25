// light ----------------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if LIGHT == ON
  #include "../Pages.common.h"
  
  void lightTile();
  void lightTileAjax();
  void lightTileGet();

  const char htmlLightingBeg[] PROGMEM =
  "<div class='obsControl' >"
  "<b>" L_LIGHTING "</b><br />"
  "<form><div>"
  "&nbsp;&nbsp;";

  const char htmlLightingEnd[] PROGMEM = "</div>\r\n";

  const char htmlLighting1[] PROGMEM =
  #if LIGHT_WRR_RELAY != OFF
  "<input id='light_WRR' type='checkbox' onclick='s(\"light_WRR\",this.checked)' %___WRR />&nbsp;" L_RED " "
  #endif
  #if LIGHT_WRW_RELAY != OFF
  "<input id='light_WRW' type='checkbox' onclick='s(\"light_WRW\",this.checked)' %___WRW />&nbsp;" L_WHITE
  #endif
  #if LIGHT_WRR_RELAY != OFF || LIGHT_WRW_RELAY != OFF
  " " L_WARM_ROOM_LIGHTS "<br />&nbsp;&nbsp;"
  #endif
  "";

  const char htmlLighting2[] PROGMEM =
  #if LIGHT_ORR_RELAY != OFF
  "<input id='light_ORR' type='checkbox' onclick='s(\"light_ORR\",this.checked)' %___ORR />&nbsp;" L_RED " "
  #endif
  #if LIGHT_ORW_RELAY != OFF
  "<input id='light_ORW' type='checkbox' onclick='s(\"light_ORW\",this.checked)' %___ORW />&nbsp;" L_WHITE
  #endif
  #if LIGHT_ORR_RELAY != OFF || LIGHT_ORW_RELAY != OFF
  " " L_OBSERVING_ROOM_LIGHTS "<br />&nbsp;&nbsp;"
  #endif
  "<br />"
  "";

  const char htmlLightingExit[] PROGMEM =
  #if LIGHT_OUTSIDE_RELAY != OFF
  "<br />"
  "&nbsp;&nbsp;<input type='button' onclick='s(\"light_EXIT\",\"true\")' value='" L_EXIT "' />&nbsp;&nbsp;" L_OUTSIDE_LIGHTS "<br />"
  #endif
  "</div></form>";

#endif
