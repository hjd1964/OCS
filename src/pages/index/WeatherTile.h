// -----------------------------------------------------------------------------------
// Weather info.
#pragma once

#include "../../Common.h"

#if WEATHER == ON
  extern void weatherTile();
  extern void weatherContents();

  const char htmlWeather1[] PROGMEM = "<div id=\"Weather\" class=\"obsControl\" >";
  const char htmlWeather3[] PROGMEM = "</div>\r\n";

  const char htmlInnerWeather1[] PROGMEM =
  "<b>Weather</b><br />";

  #if WEATHER_TEMPERATURE == ON
    const char htmlInnerWeatherTemp[] PROGMEM =
    "&nbsp;&nbsp;Temperature<div class=\"aStatus\">%s</div><br />";
  #endif

  #if WEATHER_PRESSURE == ON
    const char htmlInnerWeatherPres[] PROGMEM =
    "&nbsp;&nbsp;Barometric Pressure<div class=\"aStatus\">%s</div><br />";
  #endif

  #if WEATHER_HUMIDITY == ON
    const char htmlInnerWeatherHumd[] PROGMEM =
    "&nbsp;&nbsp;Relative Humidity<div class=\"aStatus\">%s</div><br />";
  #endif

  #if WEATHER_WIND_SPD == ON
    const char htmlInnerWeatherWind[] PROGMEM =
    "&nbsp;&nbsp;Wind Speed<div class=\"aStatus\">%s</div><br />";
  #endif

  #if WEATHER_RAIN == ON
    const char htmlInnerWeatherRain[] PROGMEM =
    "&nbsp;&nbsp;Rain sensor<div class=\"aStatus\">%s</div><br />";
  #endif

  #if WEATHER_SKY_QUAL == ON
    const char htmlInnerWeatherSq[] PROGMEM =
    "&nbsp;&nbsp;Sky Quality<div class=\"aStatus\">%s</div><br />";
  #endif

  #if WEATHER_CLOUD_CVR == ON
    const char htmlInnerWeatherCloud[] PROGMEM =
    "&nbsp;&nbsp;Sky Conditions<div class=\"aStatus\">%s</div><br />";
  #endif

#endif
