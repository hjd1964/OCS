// light ----------------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if LIGHT == ON
  void lightTile();
  void lightTileAjax();
  void lightTileGet();

  const char htmlLightingBeg[] PROGMEM = "<div class='obsControl' >";

  const char htmlLightingEnd[] PROGMEM = "</div>\r\n";

  const char htmlLighting1[] PROGMEM =
  "<b>Lighting</b><br />"
  "<form><div>"
  "&nbsp;&nbsp;"
  #if LIGHT_WRR_RELAY != OFF
  "<input id='light_WRR' type='checkbox' onclick='s(\"light_WRR\",this.checked)' %___WRR />&nbsp;Red "
  #endif
  #if LIGHT_WRW_RELAY != OFF
  "<input id='light_WRW' type='checkbox' onclick='s(\"light_WRW\",this.checked)' %___WRW />&nbsp;White"
  #endif
  #if LIGHT_WRR_RELAY != OFF || LIGHT_WRW_RELAY != OFF
  " Warm Rm Lights<br />&nbsp;&nbsp;"
  #endif
  ;
  const char htmlLighting2[] PROGMEM =
  #if LIGHT_ORR_RELAY != OFF
  "<input id='light_ORR' type='checkbox' onclick='s(\"light_ORR\",this.checked)' %___ORR />&nbsp;Red "
  #endif
  #if LIGHT_ORW_RELAY != OFF
  "<input id='light_ORW' type='checkbox' onclick='s(\"light_ORW\",this.checked)' %___ORW />&nbsp;White"
  #endif
  #if LIGHT_ORR_RELAY != OFF || LIGHT_ORW_RELAY != OFF
  " Obs Rm Lights<br />&nbsp;&nbsp;"
  #endif
  "<br />"
  ;
  const char htmlLighting3[] PROGMEM =
  #if LIGHT_OUTSIDE_RELAY != OFF
  "<br />"
  "&nbsp;&nbsp;<input type='button' onclick='s(\"light_EXIT\",\"true\")' value='Exit' />&nbsp;&nbsp;Outside Light Timer<br />"
  #endif
  "</div></form>";

#endif
