// thermostat ----------------------------------------------------------------------------------------------------------------
#pragma once

#include "../Common.h"

#if THERMOSTAT == ON
  extern void thermostatTile();
  extern void thermostatTemperatureContents();
  extern void thermostatHumidityContents();

  const char htmlThermostatBegin[] PROGMEM =
  "<div class=\"obsControl\">"
  "<b>Thermostat</b><br />";

  const char htmlThermostatTemperature1[] PROGMEM =
  "&nbsp;&nbsp;Temperature (Inside)<div id=\"ThermostatT\" class=\"aStatus\">";
  const char htmlThermostatTemperature2[] PROGMEM =
  "</div><br />";

  #if THERMOSTAT_HUMIDITY == ON
    const char htmlThermostatHumidity1[] PROGMEM =
    "&nbsp;&nbsp;Relative Humidity (Inside)<div id=\"ThermostatH\" class=\"aStatus\">";
    const char htmlThermostatHumidity2[] PROGMEM =
    "</div><br />";
  #endif

  const char htmlThermostatHeat1[] PROGMEM =
  "<form name=\"thermostat\" >"
  "<div>"
  "&nbsp;&nbsp;&nbsp;Heat <span id=\"HeatStatus\"></span>"
  "<select style=\"float:right; margin-right:20px\" onchange='SetVar(\"thermostat_heat\",value)' >";

  const char htmlThermostatHeat2[] PROGMEM = "</select></div><br />";

  const char htmlThermostatCool1[] PROGMEM =
  "<div>"
  "&nbsp;&nbsp;&nbsp;Cool/Vent"
  "<select style=\"float:right; margin-right:20px\" onchange='SetVar(\"thermostat_cool\",value)' >";

  const char htmlThermostatCool2[] PROGMEM = "</select>&nbsp;&nbsp;&nbsp;&nbsp;</div><br />";

  const char htmlThermostatHumidity3[] PROGMEM =
  "<div>"
  "&nbsp;&nbsp;&nbsp;Relative Humidity (Inside)"
  "<select style=\"float:right; margin-right:20px\" onchange='SetVar(\"thermostat_humidity\",value)' >";

  const char htmlThermostatHumidity4[] PROGMEM = "</select>&nbsp;&nbsp;&nbsp;&nbsp;</div>";


  const char htmlThermostatEnd[] PROGMEM = "</form></div>\r\n";
  const char htmlThermostatOption[] PROGMEM = "<option value=\"%d\" %s>%d&deg;%c</option>";
  const char htmlThermostatOptionZero[] PROGMEM = "<option value=\"0\" %s>OFF</option>";
  const char htmlThermostatHumidityOption[] PROGMEM = "<option value=\"%d\" %s>%d%c</option>";
#endif
