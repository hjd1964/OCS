// Weather sensors
#pragma once

#include "../../Common.h"

// set default altitude to 100 meters if not specified
#ifndef WEATHER_ALTITUDE
  #define WEATHER_ALTITUDE 100
#endif

class WeatherSensor {
  public:
    void init();

    // gets outside temperature in deg. C
    float temperature();
    char* temperatureName();

    // gets sky IR temperature in deg. C
    float skyTemperature();
    char* skyTemperatureName();

    // gets windspeed in kph
    float windspeed();
    char* windspeedName();

    // gets barometric pressure in mb (absolute)
    float pressure();
    char* pressureName();

    // gets barometric pressure in mb (sea level relative)
    float pressureSeaLevel();

    // gets relative humidity in %
    float humidity();
    char* humidityName();

    // gets rain sensor info. 1 is Rain, 2 is Warn, and 3 is Dry
    float rain();
    char* rainSenseName();

    // gets sky brightness in mag/arc-sec^2
    float skyQuality();
    char* skyQualityName();

  private:
};

extern WeatherSensor weatherSensor;
