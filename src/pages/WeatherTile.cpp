// -----------------------------------------------------------------------------------
// Weather info
#include "WeatherTile.h"

#if WEATHER == ON
  #include "htmlHeaders.h"
  #include "htmlScripts.h"
  #include "htmlTabs.h"

  #include "../libApp/weatherSensor/WeatherSensor.h"
  #include "../observatory/weather/Weather.h"
  #include "../observatory/safety/Safety.h"

  void weatherTile() {
    char temp[128] = "";

    strcpy_P(temp, htmlWeather1);
    sendHtmlC(temp);

    weatherContents();

    strcpy_P(temp,htmlWeather3);
    sendHtmlC(temp);
  }

  void weatherContents() {
    char temp[128] = "";
    char ws1[30] = "";
    float f;

    strcpy_P(temp, htmlInnerWeather1);
    sendHtmlC(temp);

    #if WEATHER_TEMPERATURE == ON
      f = weatherSensor.temperature();
      if (isnan(f)) {
        strcpy(ws1, "Invalid");
      } else {
        #if STAT_UNITS == IMPERIAL
          sprintF(ws1, "%5.1f &deg;F", f*1.8F + 32.0F);
        #else
          sprintF(ws1, "%5.1f &deg;C", f);
        #endif
      }
      sprintf_P(temp, htmlInnerWeatherTemp, ws1);
      sendHtmlC(temp);
    #endif

    #if WEATHER_PRESSURE == ON
      f = weatherSensor.pressureSeaLevel();
      if (isnan(f)) {
        strcpy(ws1, "Invalid");
      } else {
      #if STAT_UNITS == IMPERIAL
        sprintF(ws1, "%6.2f in", f*0.02953);
      #else
        sprintF(ws1, "%6.0f mb", f);
      #endif
      }
      sprintf_P(temp, htmlInnerWeatherPres, ws1);
      sendHtmlC(temp);
    #endif

    #if WEATHER_HUMIDITY == ON
      f = weatherSensor.humidity();
      if (isnan(f)) {
        strcpy(ws1, "Invalid");
      } else {
        sprintF(ws1, "%6.1f %", f);
      } 
      sprintf_P(temp, htmlInnerWeatherHumd, ws1);
      sendHtmlC(temp);
    #endif

    #if WEATHER_WIND_SPD == ON
      f = weatherSensor.windspeed();
      if (isnan(f)) {
        strcpy(ws1, "Invalid");
      } else {
        #if STAT_UNITS == IMPERIAL
          sprintF(ws1, "%6.0f mph", f*0.621371);
        #else
          sprintF(ws1, "%6.0f kph", f);
        #endif
      }
      sprintf_P(temp, htmlInnerWeatherWind, ws1);
      sendHtmlC(temp);
    #endif

    #if WEATHER_RAIN == ON
      const char * rainSensorStr[4] = {"Invalid", "Rain", "Warn", "Dry"};
      int i = lroundf(weatherSensor.rain());
      if (i < 0 || i > 3) i = 0;
      sprintf_P(temp, htmlInnerWeatherRain, rainSensorStr[i]);
      sendHtmlC(temp);
    #endif

    #if WEATHER_SKY_QUAL == ON
      f = weatherSensor.skyQuality();
      if (isnan(f)) {
        strcpy(ws1, "Invalid");
      } else {
        sprintF(ws1, "%4.1fmpsas", f);
      }
      sprintf_P(temp, htmlInnerWeatherSq, ws1);
      sendHtmlC(temp);
    #endif

    #if WEATHER_CLOUD_CVR == ON
      strcpy(ws1, weather.cloudCoverDescription());
      sprintf_P(temp, htmlInnerWeatherCloud, ws1);
      sendHtmlC(temp);
    #endif

    #if WEATHER_RAIN == ON || WEATHER_CLOUD_CVR == ON
      if (safety.isSafe()) {
        strcpy_P(temp, htmlInnerWeatherSafe);
        sendHtmlC(temp);
        strcpy_P(temp, htmlInnerWeatherSafe1);
        sendHtmlC(temp);
      } else {
        strcpy_P(temp, htmlInnerWeatherUnSafe);
        sendHtmlC(temp);
        strcpy_P(temp, htmlInnerWeatherUnSafe1);
        sendHtmlC(temp);
      }
    #endif

  }
#endif

