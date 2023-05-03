// status --------------------------------------------------------------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if STAT == ON
  void statusTile();
  void statusContents();

  const char htmlStatus1[] PROGMEM = "<div id=\"MiscStatus\" class=\"obsControl\">";

  const char htmlStatus3[] PROGMEM = "</div>\r\n";

  const char htmlInnerStatus1[] PROGMEM = "<b>Status</b><br />";

  const char htmlInnerStatus2[] PROGMEM =
  "&nbsp;&nbsp;Date (%s Time)<div class=\"aStatus\">%s</div><br />";

  const char htmlInnerStatus3[] PROGMEM =
  "&nbsp;&nbsp;Time (%s Time)<div class=\"aStatus\">%s</div><br />";

  const char htmlInnerStatus4[] PROGMEM =
  "&nbsp;&nbsp;Up Time (Minutes)<div class=\"aStatus\">%s</div><br /><br />";

  #if STAT_MAINS_SENSE != OFF
  const char htmlInnerStatusMains[] PROGMEM =
  "&nbsp;&nbsp;Mains Power<div class=\"aStatus\">%s</div><br />";
  #endif

  #if STAT_MAINS_CURRENT_ANALOG != OFF
  const char htmlInnerStatusMainsA[] PROGMEM =
  "&nbsp;&nbsp;Mains Current<div class=\"aStatus\">%s</div><br />";
  #endif

  #if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
  const char htmlInnerStatusMainsAA[] PROGMEM =
  "&nbsp;&nbsp;Mains Aux Current<div class=\"aStatus\">%s</div><br />";
  #endif

  #if STAT_DC_VOLTAGE_ANALOG != OFF
  const char htmlInnerStatusDC[] PROGMEM =
  "&nbsp;&nbsp;DC Power Supply<div class=\"aStatus\">%s</div><br />";
  #endif

  #if STAT_DC_CURRENT_ANALOG != OFF
  const char htmlInnerStatusDCA[] PROGMEM =
  "&nbsp;&nbsp;DC Current<div class=\"aStatus\">%s</div><br />";
  #endif

  #if STAT_BATTERY_VOLTAGE_ANALOG != OFF
  const char htmlInnerStatusBat[] PROGMEM =
  "&nbsp;&nbsp;Battery<div class=\"aStatus\">%s</div><br />";
  #endif

  #if STAT_BATTERY_CURRENT_ANALOG != OFF
  const char htmlInnerStatusBatA[] PROGMEM =
  "&nbsp;&nbsp;Battery Current<div class=\"aStatus\">%s</div><br />";
  #endif

  #if STAT_PROCESSOR_RAM != OFF
  const char htmlInnerStatusMemory[] PROGMEM =
  "&nbsp;&nbsp;Free Memory (Bytes)<div class=\"aStatus\">%d</div><br />";
  #endif

  #if WEATHER_RAIN != OFF || WEATHER_CLOUD_CVR != OFF || WEATHER_WIND_SPD != OFF || STAT_MAINS_SENSE != OFF
    const char htmlInnerSafe[] PROGMEM =
    "<br />&nbsp;&nbsp;Safety<div class=\"aStatus\">Safe</div><br />";
    const char htmlInnerUnSafe[] PROGMEM =
    "<br />&nbsp;&nbsp;Safety<div class=\"aStatus\" style=\"color:#ff0000;\">UNSAFE</div><br />";
  #endif

#endif
