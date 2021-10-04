// thermostat ----------------------------------------------------------------------------------------------------------------
#pragma once

#include "../Common.h"

#if THERMOSTAT == ON
  extern void thermostatTile();
  extern void thermostatContents();

  const char htmlThermostatBegin[] PROGMEM =
  "<div class=\"obsControl\">"
  "<b>Thermostat</b><br />"
  "&nbsp;&nbsp;Temperature (Inside)<div id=\"Thermostat\" class=\"aStatus\"></div><br />";

  #if THERMOSTAT_HUMIDITY == ON
    const char htmlThermostatHumidity[] PROGMEM =
    "&nbsp;&nbsp;Relative Humidity (Inside)<div id=\"ThermostatH\" class=\"aStatus\"></div><br />";
  #endif

  const char htmlThermostatHeat1[] PROGMEM =
  "<form name=\"thermostat\" >"
  "<div>"
  "&nbsp;&nbsp;&nbsp;Heat <span id=\"HeatStatus\"></span>"
  "<select style=\"float:right; margin-right:20px\" onchange='SetVar(\"thermostat_heat\",value)' >";

  const char htmlThermostatHeat2[] PROGMEM = "</select></div><br />";

  const char htmlThermostatCool1[] PROGMEM =
  "<div>"
  "&nbsp;&nbsp;&nbsp;Cool/Venting"
  "<select style=\"float:right; margin-right:20px\" onchange='SetVar(\"thermostat_cool\",value)' >";

  const char htmlThermostatCool2[] PROGMEM = "</select>&nbsp;&nbsp;&nbsp;&nbsp;</div>";

  const char htmlThermostatEnd[] PROGMEM = "</form></div>\r\n";
  const char htmlThermostatOption[] PROGMEM = "<option value=\"%d\" %s>%d&deg;%c</option>";
  const char htmlThermostatOptionZero[] PROGMEM = "<option value=\"0\" %s>OFF</option>";
#endif
