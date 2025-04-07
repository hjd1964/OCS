// power ----------------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if POWER == ON
  #include "../Pages.common.h"

  void powerTile();
  void powerTileAjax();
  void powerTileGet();

  const char htmlPowerBegin[] PROGMEM =
  "<div class='obsControl' >"
  "<b>" L_POWER "</b><br />"
  "<div>";

  const char html_powerControl[] PROGMEM =
  "<button id='pwr%s_%s' class='btns_%s' style='float: right;' onpointerdown=\"s('pwr%s','%s')\" type='button'>%s</button>";

  const char htmlPowerEnd[] PROGMEM =
  "<br />"
  "</div>"
  "</div>\r\n";

#endif
