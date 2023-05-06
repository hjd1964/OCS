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
  "<form><div>";

  const char htmlPowerEnd[] PROGMEM =
  "<br />"
  "</div></form>"
  "</div>\r\n";

  const char htmlPower1[] PROGMEM =
  #if POWER_DEVICE1_RELAY != OFF
  "&nbsp;&nbsp;<input id='power1' type='checkbox' onclick='s(\"pwr1\",this.checked)' %___PD1 />&nbsp;&nbsp;" POWER_DEVICE1_NAME "<br />"
  #endif
  "";
  const char htmlPower2[] PROGMEM =
  #if POWER_DEVICE2_RELAY != OFF
  "&nbsp;&nbsp;<input id='power2' type='checkbox' onclick='s(\"pwr2\",this.checked)' %___PD2 />&nbsp;&nbsp;" POWER_DEVICE2_NAME "<br />"
  #endif
  "";
  const char htmlPower3[] PROGMEM =
  #if POWER_DEVICE3_RELAY != OFF
  "&nbsp;&nbsp;<input id='power3' type='checkbox' onclick='s(\"pwr3\",this.checked)' %___PD3 />&nbsp;&nbsp;" POWER_DEVICE3_NAME "<br />"
  #endif
  "";
  const char htmlPower4[] PROGMEM =
  #if POWER_DEVICE4_RELAY != OFF
  "&nbsp;&nbsp;<input id='power4' type='checkbox' onclick='s(\"pwr4\",this.checked)' %___PD4 />&nbsp;&nbsp;" POWER_DEVICE4_NAME "<br />"
  #endif
  "";
  const char htmlPower5[] PROGMEM =
  #if POWER_DEVICE5_RELAY != OFF
  "&nbsp;&nbsp;<input id='power5' type='checkbox' onclick='s(\"pwr5\",this.checked)' %___PD5 />&nbsp;&nbsp;" POWER_DEVICE5_NAME "<br />"
  #endif
  "";
  const char htmlPower6[] PROGMEM =
  #if POWER_DEVICE6_RELAY != OFF
  "&nbsp;&nbsp;<input id='power6' type='checkbox' onclick='s(\"pwr6\",this.checked)' %___PD6 />&nbsp;&nbsp;" POWER_DEVICE6_NAME "<br />"
  #endif
  "";
#endif
