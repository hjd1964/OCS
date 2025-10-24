// weather --------------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if WEATHER == ON
  #include "../Pages.common.h"

  void weatherTile();
  void weatherTileAjax();

  const char htmlWeatherBeg[] PROGMEM = "<div class='obsControl' >";

  const char htmlWeatherEnd[] PROGMEM = "</div>\r\n";

  const char htmlInnerWeatherTitle[] PROGMEM = "<b>" L_WEATHER "</b><br />";

  #if WEATHER_TEMPERATURE == ON
    const char htmlInnerWeatherTemp[] PROGMEM =
    "&nbsp;&nbsp;" L_TEMPERATURE "<div id='wea_temp' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_PRESSURE == ON
    const char htmlInnerWeatherPres[] PROGMEM =
    "&nbsp;&nbsp;" L_PRESSURE "<div id='wea_pres' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_HUMIDITY == ON
    const char htmlInnerWeatherHumd[] PROGMEM =
    "&nbsp;&nbsp;" L_HUMIDITY "<div id='wea_humd' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_WIND_SPD == ON
    const char htmlInnerWeatherWind[] PROGMEM =
    "&nbsp;&nbsp;" L_WIND_SPEED "<div id='wea_wind' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_WIND_ACCUMULATE != OFF
    const char htmlInnerWeatherGust[] PROGMEM =
    "&nbsp;&nbsp;" L_WIND_ACCUM "<div id='wea_gust' class='aStatus'>&s</div><br />";
  #endif

  #if WEATHER_RAIN == ON
    const char htmlInnerWeatherRain[] PROGMEM =
    "&nbsp;&nbsp;" L_RAIN_SENSE "<div id='wea_rain' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_SKY_QUAL == ON
    const char htmlInnerWeatherSq[] PROGMEM =
    "&nbsp;&nbsp;" L_SKY_QUALITY "<div id='wea_sq' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_CLOUD_CVR == ON
    const char htmlInnerWeatherCloud[] PROGMEM =
    "&nbsp;&nbsp;" L_SKY_CONDITIONS "<div id='wea_cloud' class='aStatus'>%s</div><br />";
  #endif

#endif
