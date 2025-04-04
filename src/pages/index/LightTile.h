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
  "<form><div>";

  const char htmlLightingEnd[] PROGMEM = "</div>\r\n";

  const char htmlLightControl[] PROGMEM =
  "<button id='light_%s_%s' class='btns_%s' onpointerdown=\"s('light_%s','%s')\" type='button'>%s</button>";

  const char htmlLightingExit[] PROGMEM =
  #if LIGHT_OUTSIDE_RELAY != OFF
  "<br />"
  "&nbsp;&nbsp;<input type='button' onclick='s(\"light_EXIT\",\"true\")' value='" L_EXIT "' />&nbsp;&nbsp;" L_OUTSIDE_LIGHTS "<br />"
  #endif
  "</div></form>";

#endif
