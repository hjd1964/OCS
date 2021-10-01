// -----------------------------------------------------------------------------------
// Weather info
#include "WeatherTile.h"

#if WEATHER == ON
  #include "htmlHeaders.h"
  #include "htmlScripts.h"
  #include "htmlTabs.h"

  #include "../lib/weatherSensor/WeatherSensor.h"
  #include "../observatory/weather/Weather.h"
  #include "../observatory/safety/Safety.h"

  #if OPERATIONAL_MODE != WIFI
  void weatherTile(EthernetClient *client) {
  #else
  void weatherTile() {
  #endif
    char temp[128] = "";

    strcpy_P(temp, htmlWeather1);
    sendHtml(temp);

    weatherContents(client);

    strcpy_P(temp,htmlWeather3);
    sendHtml(temp);
  }

  #if OPERATIONAL_MODE != WIFI
  void weatherContents(EthernetClient *client) {
  #else
  void weatherContents() {
  #endif
    char temp[128] = "";
    char temp1[128] = "";
    char ws1[30] = "";
    char ws2[30] = "";
    float f;

    strcpy_P(temp, htmlInnerWeather1);
    sendHtml(temp);

    #if WEATHER_TEMPERATURE == ON
      f = weatherSensor.temperature();
      strcpy(ws2," &deg;C");
      #if STAT_UNITS == IMPERIAL
        f = f*(9.0/5.0) + 32.0;
        strcpy(ws2, " &deg;F");
      #endif
      if (isnan(f)) {
        strcpy(ws1, "Invalid");
        strcpy(ws2, "");
      } else sprintF(ws1, "%5.1f", f);
      strcpy_P(temp1, htmlInnerWeatherTemp);
      sprintf(temp, temp1, ws1, ws2);
      sendHtml(temp);
    #endif

    #if WEATHER_PRESSURE == ON
      #if STAT_UNITS == IMPERIAL
        f = weatherPressureSeaLevel()*0.02953;
        strcpy(ws2," in");
        if (isnan(f)) {
          strcpy(ws1, "Invalid");
          strcpy(ws2, "");
        } else sprintF(ws1, "%6.2f", f);
      #else
        f = weatherSensor.pressureSeaLevel();
        strcpy(ws2," mb");
        if (isnan(f)) {
          strcpy(ws1, "Invalid");
          strcpy(ws2,"");
        } else sprintF(ws1, "%6.0f", f);
      #endif
      strcpy_P(temp1, htmlInnerWeatherPres);
      sprintf(temp, temp1, ws1, ws2);
      sendHtml(temp);
    #endif

    #if WEATHER_HUMIDITY == ON
      f = weatherSensor.humidity();
      strcpy(ws2, " %");
      if (isnan(f)) {
        strcpy(ws1, "Invalid");
        strcpy(ws2,"");
      } else sprintF(ws1, "%6.1f", f); 
      strcpy_P(temp1, htmlInnerWeatherHumd);
      sprintf(temp, temp1, ws1, ws2);
      sendHtml(temp);
    #endif

    #if WEATHER_WIND_SPD == ON
      f = weatherSensor.windspeed();
      strcpy(ws2," kph");
      #if STAT_UNITS == IMPERIAL
        f *= 0.621371;
        strcpy(ws2, " mph");
      #endif
      if (isnan(f)) {
        strcpy(ws2, "");
        strcpy(ws1, "Invalid");
      } else sprintF(ws1, "%6.0f", f);
      strcpy_P(temp1, htmlInnerWeatherWind);
      sprintf(temp, temp1, ws1, ws2);
      sendHtml(temp);
    #endif

    #if WEATHER_RAIN == ON
      char rainSensorStr[4][8] = {"Invalid", "Rain", "Warn", "Dry"};
      int i = lroundf(weatherSensor.rain());
      if (i < 0 || i > 3) i = 0;
      strcpy_P(temp1, htmlInnerWeatherRain);
      sprintf(temp, temp1, rainSensorStr[i]);
      sendHtml(temp);
    #endif

    #if WEATHER_SKY_QUAL == ON
      f = weatherSensor.skyQuality();
      if (isnan(f)) {
        strcpy(ws1, "Invalid");
        strcpy(ws2, "");
      } else {
        sprintF(ws1, "%4.1f", f);
        strcpy(ws2, " mpsas"); 
      }
      strcpy_P(temp1, htmlInnerWeatherSq);
      sprintf(temp, temp1, ws1, ws2);
      sendHtml(temp);
    #endif

    #if WEATHER_CLOUD_CVR == ON
      strcpy_P(temp1, htmlInnerWeatherCloud);
      strcpy(ws1, weather.cloudCoverDescription());
      sprintf(temp, temp1, ws1);
      sendHtml(temp);
    #endif

    #if WEATHER_RAIN == ON || WEATHER_CLOUD_CVR == ON
      if (safety.isSafe()) {
        strcpy_P(temp, htmlInnerWeatherSafe);
        sendHtml(temp);
        strcpy_P(temp, htmlInnerWeatherSafe1);
        sendHtml(temp);
      } else {
        strcpy_P(temp, htmlInnerWeatherUnSafe);
        sendHtml(temp);
        strcpy_P(temp, htmlInnerWeatherUnSafe1);
        sendHtml(temp);
      }
    #endif

  }
#endif

