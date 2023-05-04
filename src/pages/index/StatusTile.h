// status ---------------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if STAT == ON
  void statusTile();
  void statusTileAjax();

  const char htmlStatusBeg[] PROGMEM = "<div id='MiscStatus' class='obsControl'>";
  
  const char htmlStatusEnd[] PROGMEM = "</div>\r\n";
  
  const char htmlInnerStatusTitle[] PROGMEM = "<b>Status</b><br />";

  const char htmlInnerStatusDate[] PROGMEM =
  "&nbsp;&nbsp;Date (%s Time)<div id='stat_date' class='aStatus'>%s</div><br />";

  const char htmlInnerStatusTime[] PROGMEM =
  "&nbsp;&nbsp;Time (%s Time)<div id='stat_time' class='aStatus'>%s</div><br />";

  const char htmlInnerStatusUpTime[] PROGMEM =
  "&nbsp;&nbsp;Up Time (Minutes)<div id='stat_upTime' class='aStatus'>%s</div><br /><br />";

  #if STAT_MAINS_SENSE != OFF
  const char htmlInnerStatusMains[] PROGMEM =
  "&nbsp;&nbsp;Mains Power<div  id='stat_mains' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_MAINS_CURRENT_ANALOG != OFF
  const char htmlInnerStatusMainsA[] PROGMEM =
  "&nbsp;&nbsp;Mains Current<div  id='stat_mains_A' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
  const char htmlInnerStatusAuxA[] PROGMEM =
  "&nbsp;&nbsp;Mains Aux Current<div id='stat_aux_A' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_DC_VOLTAGE_ANALOG != OFF
  const char htmlInnerStatusDC[] PROGMEM =
  "&nbsp;&nbsp;DC Power Supply<div id='stat_dc_v' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_DC_CURRENT_ANALOG != OFF
  const char htmlInnerStatusDCA[] PROGMEM =
  "&nbsp;&nbsp;DC Current<div  id='stat_dc_A' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_BATTERY_VOLTAGE_ANALOG != OFF
  const char htmlInnerStatusBat[] PROGMEM =
  "&nbsp;&nbsp;Battery<div id='stat_bat_V' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_BATTERY_CURRENT_ANALOG != OFF
  const char htmlInnerStatusBatA[] PROGMEM =
  "&nbsp;&nbsp;Battery Current<div id='stat_bat_A' class='aStatus'>%s</div><br />";
  #endif

  #if STAT_PROCESSOR_RAM != OFF
  const char htmlInnerStatusMemory[] PROGMEM =
  "&nbsp;&nbsp;Free Memory (Bytes)<div id='stat_mem' class='aStatus'>%d</div><br />";
  #endif

  #if WEATHER_RAIN != OFF || WEATHER_CLOUD_CVR != OFF || WEATHER_WIND_SPD != OFF || STAT_MAINS_SENSE != OFF
    const char htmlInnerSafe[] PROGMEM =
    "<br />&nbsp;&nbsp;Safety<div id='stat_safe' class='aStatus'>Safe</div><br />";
    const char htmlInnerUnSafe[] PROGMEM =
    "<br />&nbsp;&nbsp;Safety<div id='stat_safe' class='aStatus'><span style='color:#ff0000;'>UNSAFE</span></div><br />";
  #endif

#endif
