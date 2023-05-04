// weather --------------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if WEATHER == ON
  void weatherTile();
  void weatherTileAjax();

  const char htmlWeatherBeg[] PROGMEM = "<div class='obsControl' >";

  const char htmlWeatherEnd[] PROGMEM = "</div>\r\n";

  const char htmlInnerWeatherTitle[] PROGMEM = "<b>Weather</b><br />";

  #if WEATHER_TEMPERATURE == ON
    const char htmlInnerWeatherTemp[] PROGMEM =
    "&nbsp;&nbsp;Temperature<div id='wea_temp' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_PRESSURE == ON
    const char htmlInnerWeatherPres[] PROGMEM =
    "&nbsp;&nbsp;Barometric Pressure<div id='wea_pres' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_HUMIDITY == ON
    const char htmlInnerWeatherHumd[] PROGMEM =
    "&nbsp;&nbsp;Relative Humidity<div id='wea_humd' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_WIND_SPD == ON
    const char htmlInnerWeatherWind[] PROGMEM =
    "&nbsp;&nbsp;Wind Speed<div id='wea_wind' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_RAIN == ON
    const char htmlInnerWeatherRain[] PROGMEM =
    "&nbsp;&nbsp;Rain Sense<div id='wea_rain' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_SKY_QUAL == ON
    const char htmlInnerWeatherSq[] PROGMEM =
    "&nbsp;&nbsp;Sky Quality<div id='wea_sq' class='aStatus'>%s</div><br />";
  #endif

  #if WEATHER_CLOUD_CVR == ON
    const char htmlInnerWeatherCloud[] PROGMEM =
    "&nbsp;&nbsp;Sky Conditions<div id='wea_cloud' class='aStatus'>%s</div><br />";
  #endif

#endif
