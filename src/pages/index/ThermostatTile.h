// thermostat -----------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if THERMOSTAT == ON
  void thermostatTile();
  void thermostatTileAjax();
  void thermostatTileGet();

  const char htmlThermostatBegin[] PROGMEM =
  "<div class='obsControl'>"
  "<b>Thermostat</b><br />";

  const char htmlThermostatEnd[] PROGMEM = "</form></div>\r\n";

  const char htmlThermostatTemperatureBeg[] PROGMEM =
  "&nbsp;&nbsp;Temperature (Inside)<div id='tstat_T' class='aStatus'>";
  const char htmlThermostatTemperatureEnd[] PROGMEM =
  "</div><br />";

  #if THERMOSTAT_HUMIDITY == ON
    const char htmlThermostatHumidityBeg[] PROGMEM =
    "&nbsp;&nbsp;Relative Humidity (Inside)<div id='tstat_H' class='aStatus'>";
    const char htmlThermostatHumidityEnd[] PROGMEM =
    "</div><br />";
  #endif

  const char htmlThermostatHeatBeg[] PROGMEM =
  "<form name='thermostat' >"
  "<div>"
  "&nbsp;&nbsp;&nbsp;Heat <span id='HeatStatus'></span>"
  "<select style='float:right; margin-right:20px' onchange='s(\"tstat_heat\",value)' >";

  const char htmlThermostatHeatEnd[] PROGMEM = "</select></div><br />";

  const char htmlThermostatCoolBeg[] PROGMEM =
  "<div>"
  "&nbsp;&nbsp;&nbsp;Cool/Vent"
  "<select style='float:right; margin-right:20px' onchange='s(\"tstat_cool\",value)' >";

  const char htmlThermostatCoolEnd[] PROGMEM = "</select>&nbsp;&nbsp;&nbsp;&nbsp;</div><br />";

  const char htmlThermostatHumidityControlBeg[] PROGMEM =
  "<div>"
  "&nbsp;&nbsp;&nbsp;Relative Humidity (Inside)"
  "<select style='float:right; margin-right:20px' onchange='s(\"tstat_humidity\",value)' >";

  const char htmlThermostatHumidityControlEnd[] PROGMEM = "</select>&nbsp;&nbsp;&nbsp;&nbsp;</div>";

  const char htmlThermostatOption[] PROGMEM = "<option value='%d' %s>%d&deg;%c</option>";
  const char htmlThermostatOptionZero[] PROGMEM = "<option value='0' %s>OFF</option>";
  const char htmlThermostatHumidityOption[] PROGMEM = "<option value='%d' %s>%d%c</option>";
#endif
