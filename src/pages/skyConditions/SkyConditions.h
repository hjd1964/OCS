// -----------------------------------------------------------------------------------
// Weather charts
#pragma once

#include "../../Common.h"

#if WEATHER == ON && WEATHER_CHARTS == ON && (WEATHER_SKY_QUAL == ON || WEATHER_CLOUD_CVR == ON)
  #include "../Pages.common.h"

  extern void skyPage();

  const char ChartOptions1b[] PROGMEM = 
  "<form method=\"get\" action=\"/skypage.htm\">";

  const char ChartOptions2[] PROGMEM = 
  "<button name=\"chart\" value=\"recent\" type=\"submit\">Recent</button>"
  "<button name=\"chart\" value=\"last24\" type=\"submit\">Last 24 Hours</button>"
  "<button name=\"chart\" value=\"last48\" type=\"submit\">Last 48 Hours</button>"
  "</form>";

#endif
