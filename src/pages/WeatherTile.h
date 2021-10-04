// -----------------------------------------------------------------------------------
// Weather info.
#pragma once

#include "../Common.h"

#if WEATHER == ON
  #include "../lib/ethernet/webServer/WebServer.h"
  #include "../lib/wifi/Wifi.h"

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

  #if WEATHER_RAIN == ON || WEATHER_CLOUD_CVR == ON || WEATHER_WIND_SPD == ON || STAT_MAINS_SENSE != OFF
    const char htmlInnerWeatherSafe[] PROGMEM =
    "<div style=\"position: absolute; bottom: 5px; left: 120px; text-align:center\";><div style=\"display:inline-block; ";
    const char htmlInnerWeatherSafe1[] PROGMEM =
    "background-color: #bcccbc; color: green; border:1px solid green; padding: 4px 4px;\">SAFE</div></div><br />";
  #endif

  #if WEATHER_RAIN == ON || WEATHER_CLOUD_CVR == ON || WEATHER_WIND_SPD == ON || STAT_MAINS_SENSE != OFF
    const char htmlInnerWeatherUnSafe[] PROGMEM =
    "<div style=\"position: absolute; bottom: 5px; left: 110px; text-align:center\";><div style=\"display:inline-block; ";
    const char htmlInnerWeatherUnSafe1[] PROGMEM =
    "background-color: #ccbcbc; color: red; border:1px solid red; padding: 4px 4px;\">UNSAFE</div></div><br />";
  #endif

#endif
