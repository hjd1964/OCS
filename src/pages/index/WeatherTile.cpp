// weather --------------------------------------------------------------------
#include "WeatherTile.h"

#if WEATHER == ON
  #include "../../libApp/weatherSensor/WeatherSensor.h"
  #include "../../observatory/weather/Weather.h"
  #include "../../observatory/safety/Safety.h"

  #if WEATHER_TEMPERATURE == ON
    void getWeatherTemperatureStr(char *temp);
  #endif
  #if WEATHER_PRESSURE == ON
    void getWeatherPressureStr(char *temp);
  #endif
  #if WEATHER_HUMIDITY == ON
    void getWeatherHumidityStr(char *temp);
  #endif
  #if WEATHER_WIND_SPD == ON
    void getWeatherWindSpeedStr(char *temp);
  #endif
  #if WEATHER_WIND_ACCUMULATE != OFF
    void getWeatherWindAccumStr(char *temp);
  #endif
  #if WEATHER_RAIN == ON
    void getWeatherRainStr(char *temp);
  #endif
  #if WEATHER_SKY_QUAL == ON
    void getWeatherSkyQualityStr(char *temp);
  #endif

  void weatherTile() {
    char temp[128];
    char temp1[32];
    UNUSED(temp1);

    strcpy_P(temp, htmlWeatherBeg);
    www.sendContent(temp);

    strcpy_P(temp, htmlInnerWeatherTitle);
    www.sendContent(temp);

    #if WEATHER_TEMPERATURE == ON
      getWeatherTemperatureStr(temp1);
      sprintf_P(temp, htmlInnerWeatherTemp, temp1);
      www.sendContent(temp);
    #endif

    #if WEATHER_PRESSURE == ON
      getWeatherPressureStr(temp1);
      sprintf_P(temp, htmlInnerWeatherPres, temp1);
      www.sendContent(temp);
    #endif

    #if WEATHER_HUMIDITY == ON
      getWeatherHumidityStr(temp1);
      sprintf_P(temp, htmlInnerWeatherHumd, temp1);
      www.sendContent(temp);
    #endif

    #if WEATHER_WIND_SPD == ON
      getWeatherWindSpeedStr(temp1);
      sprintf_P(temp, htmlInnerWeatherWind, temp1);
      www.sendContent(temp);
    #endif

    #if WEATHER_WIND_ACCUMULATE != OFF
      getWeatherWindAccumStr(temp1);
      sprintf_P(temp, htmlInnerWeatherGust, temp1);
      www.sendContent(temp);
    #endif

    #if WEATHER_RAIN == ON
      getWeatherRainStr(temp1);
      sprintf_P(temp, htmlInnerWeatherRain, temp1);
      www.sendContent(temp);
    #endif

    #if WEATHER_SKY_QUAL == ON
      getWeatherSkyQualityStr(temp1);
      sprintf_P(temp, htmlInnerWeatherSq, temp1);
      www.sendContent(temp);
    #endif

    #if WEATHER_CLOUD_CVR == ON
      strcpy(temp1, weather.cloudCoverDescription());
      sprintf_P(temp, htmlInnerWeatherCloud, temp1);
      www.sendContent(temp);
    #endif

    strcpy_P(temp,htmlWeatherEnd);
    www.sendContent(temp);
  }

  void weatherTileAjax() {
    char temp[30];

    #if WEATHER_TEMPERATURE == ON
      getWeatherTemperatureStr(temp);
      www.sendContent("wea_temp|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if WEATHER_PRESSURE == ON
      getWeatherPressureStr(temp);
      www.sendContent("wea_pres|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if WEATHER_HUMIDITY == ON
      getWeatherHumidityStr(temp);
      www.sendContent("wea_humd|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if WEATHER_WIND_ACCUMULATE != OFF
      getWeatherWindAccumStr(temp);
      www.sendContent("wea_gust|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if WEATHER_WIND_SPD == ON
      getWeatherWindSpeedStr(temp);
      www.sendContent("wea_wind|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if WEATHER_RAIN == ON
      getWeatherRainStr(temp);
      www.sendContent("wea_rain|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if WEATHER_SKY_QUAL == ON
      getWeatherSkyQualityStr(temp);
      www.sendContent("wea_sq|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if WEATHER_CLOUD_CVR == ON
      strcpy(temp, weather.cloudCoverDescription());
      www.sendContent("wea_cloud|"); www.sendContent(temp); www.sendContent("\n");
    #endif
  }

  #if WEATHER_TEMPERATURE == ON
    void getWeatherTemperatureStr(char *temp) {
      float f = weatherSensor.temperature();
      if (isnan(f)) {
        strcpy_P(temp, htmlStringInvalid);
      } else {
        #if DISPLAY_UNITS == IMPERIAL
          sprintF(temp, "%5.1f &deg;F", f*1.8F + 32.0F);
        #else
          sprintF(temp, "%5.1f &deg;C", f);
        #endif
      }
    }
  #endif

  #if WEATHER_PRESSURE == ON
    void getWeatherPressureStr(char *temp) {
      float f = weatherSensor.pressureSeaLevel();
      if (isnan(f)) {
        strcpy_P(temp, htmlStringInvalid);
      } else {
      #if DISPLAY_UNITS == IMPERIAL
        sprintF(temp, "%6.2f in", f*0.02953);
      #else
        sprintF(temp, "%6.0f mb", f);
      #endif
      }
    }
  #endif

  #if WEATHER_HUMIDITY == ON
    void getWeatherHumidityStr(char *temp) {
      float f = weatherSensor.humidity();
      if (isnan(f)) {
        strcpy_P(temp, htmlStringInvalid);
      } else {
        sprintF(temp, "%6.1f %%", f);
      }
    }
  #endif

  #if WEATHER_WIND_SPD == ON
    void getWeatherWindSpeedStr(char *temp) {
      float f = weatherSensor.windspeed();
      if (isnan(f)) {
        strcpy_P(temp, htmlStringInvalid);
      } else {
        #if DISPLAY_UNITS == IMPERIAL || DISPLAY_UNITS == BRITISH
          sprintF(temp, "%6.0f mph", f*0.621371);
        #else
          sprintF(temp, "%6.0f kph", f);
        #endif
      }
    }
  #endif

  #if WEATHER_WIND_ACCUMULATE != OFF
    void getWeatherWindAccumStr(char *temp) {
      float f = safety.gustCount();
      if (isnan(f)) {
        strcpy_P(temp, htmlStringInvalid);
      } else {
        #if DISPLAY_UNITS == IMPERIAL || DISPLAY_UNITS == BRITISH
          sprintF(temp, "%6.0f mph", f*0.621371);
        #else
          sprintF(temp, "%6.0f kph", f);
        #endif
      }
    }
  #endif

  #if WEATHER_RAIN == ON
    void getWeatherRainStr(char *temp) {
      const char *rainSensorStr[4] = {L_INVALID, L_RAIN, L_WARN, L_DRY};
      int i = lroundf(weatherSensor.rain());
      if (i < 0 || i > 3) i = 0;
      strcpy(temp, rainSensorStr[i]);
    }
  #endif

  #if WEATHER_SKY_QUAL == ON
    void getWeatherSkyQualityStr(char *temp) {
      float f = weatherSensor.skyQuality();
      if (isnan(f)) {
        strcpy_P(temp, htmlStringInvalid);
      } else {
        sprintF(temp, "%4.1f mpsas", f);
      }
    }
  #endif

#endif
