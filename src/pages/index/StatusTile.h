// status ---------------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if STAT == ON
  #include "../Pages.common.h"

  void statusTile();
  void statusTileAjax();

  const char htmlStatusBeg[] PROGMEM = "<div id='MiscStatus' class='obsControl'>";
  
  const char htmlStatusEnd[] PROGMEM = "</div>\r\n";
  
  const char htmlInnerStatusTitle[] PROGMEM = "<b>" L_STATUS "</b><br />";

  const char htmlInnerStatusDate[] PROGMEM =
  "&nbsp;&nbsp;" L_DATE " (%s)<div id='stat_date' class='aStatus'>%s</div><br />";

  const char htmlInnerStatusTime[] PROGMEM =
  "&nbsp;&nbsp;" L_TIME " (%s)<div id='stat_time' class='aStatus'>%s</div><br />";

  const char htmlInnerStatusUpTime[] PROGMEM =
  "&nbsp;&nbsp;" L_UP_TIME " (" L_MINUTES ")<div id='stat_upTime' class='aStatus'>%s</div><br /><br />";

  #if STAT_MAINS_SENSE != OFF
  const char htmlInnerStatusMains[] PROGMEM =
  "&nbsp;&nbsp;" L_MAINS_POWER "<div id='stat_mains' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_MAINS_CURRENT_ANALOG != OFF
  const char htmlInnerStatusMainsA[] PROGMEM =
  "&nbsp;&nbsp;" L_MAINS_CURRENT "<div id='stat_mains_A' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
  const char htmlInnerStatusAuxA[] PROGMEM =
  "&nbsp;&nbsp;" L_MAINS_AUX_CURRENT "<div id='stat_aux_A' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_DC_VOLTAGE_ANALOG != OFF
  const char htmlInnerStatusDC[] PROGMEM =
  "&nbsp;&nbsp;" L_DC_POWER_VOLTS "<div id='stat_dc_v' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_DC_CURRENT_ANALOG != OFF
  const char htmlInnerStatusDCA[] PROGMEM =
  "&nbsp;&nbsp;" L_DC_POWER_AMPS "<div  id='stat_dc_A' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_BATTERY_VOLTAGE_ANALOG != OFF
  const char htmlInnerStatusBat[] PROGMEM =
  "&nbsp;&nbsp;" L_BATTERY_VOLTS "<div id='stat_bat_V' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_BATTERY_CURRENT_ANALOG != OFF
  const char htmlInnerStatusBatA[] PROGMEM =
  "&nbsp;&nbsp;" L_BATTERY_AMPS "<div id='stat_bat_A' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_PROCESSOR_RAM != OFF
  const char htmlInnerStatusMemory[] PROGMEM =
  "&nbsp;&nbsp;" L_FREE_MEMORY "<div id='stat_mem' class='aStatus'>%d</div><br />";
  #endif

  #if WEATHER_RAIN != OFF || WEATHER_CLOUD_CVR != OFF || WEATHER_WIND_SPD != OFF || STAT_MAINS_SENSE != OFF
    const char htmlInnerSafe[] PROGMEM =
    "<br />&nbsp;&nbsp;" L_SAFETY "<div id='stat_safe' class='aStatus'>" L_SAFE "</div><br />";
    const char htmlInnerUnSafe[] PROGMEM =
    "<br />&nbsp;&nbsp;" L_SAFETY "<div id='stat_safe' class='aStatus'><span style='color:#ff0000;'>" L_UNSAFE "</span></div><br />";
    const char htmlStringUnSafe[] PROGMEM =
    "<span style='color:#ff0000;'>" L_UNSAFE "</span>";
  #endif

#endif
