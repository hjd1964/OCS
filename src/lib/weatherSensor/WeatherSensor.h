// Weather sensors
#pragma once

#include "../../Common.h"

class WeatherSensor {
  public:
    void init();

    // gets outside temperature in deg. C
    float temperature();

    // gets sky IR temperature in deg. C
    float skyTemperature();

    // gets windspeed in kph
    float windspeed();

    // gets barometric pressure in mb (absolute)
    float pressure();

    // gets barometric pressure in mb (sea level relative)
    float pressureSeaLevel();

    // gets relative humidity in %
    float humidity();

    // gets rain sensor info. 1 is Rain, 2 is Warn, and 3 is Dry
    float rain();

    // gets sky brightness in mag/arc-sec^2
    float skyQuality();

  private:
};

extern WeatherSensor weatherSensor;
