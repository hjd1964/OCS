// -----------------------------------------------------------------------------------
// Weather charts
#pragma once

#include "../Common.h"

#if WEATHER == ON && WEATHER_CHARTS == ON
  extern void weatherPage();

  #define WEATHER_NOMINAL_PRESSURE_SEA_LEVEL 1013.25  // in mb

  const char ChartOptions1a[] PROGMEM = 
  "<form method=\"get\" action=\"/weatherpage.htm\">";

  const char ChartOptions1b[] PROGMEM = 
  "<form method=\"get\" action=\"/skypage.htm\">";

  const char ChartOptions2[] PROGMEM = 
  "<button name=\"chart\" value=\"recent\" type=\"submit\">Recent</button>"
  "<button name=\"chart\" value=\"last24\" type=\"submit\">Last 24 Hours</button>"
  "<button name=\"chart\" value=\"last48\" type=\"submit\">Last 48 Hours</button>"
  "</form>";

#endif
