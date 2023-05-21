// -----------------------------------------------------------------------------------------------------------------
// gets rain sensor info. 1 is Rain, 2 is Warn, and 3 is Dry
// this is for the typical eBay rain sensor like this one:
// http://www.ebay.com/itm/Raindrops-Detection-sensor-modue-rain-module-weather-module-Humidity-For-Arduino-/400439668701
#pragma once

#include "../../Common.h"

#if defined(WEATHER_SENSOR_RAIN_GENERIC) && WEATHER_SENSOR_RAIN_GENERIC != OFF

// set default low/high thresholds if not specified
#ifndef WEATHER_SENSOR_RAIN_LOW
  #define WEATHER_SENSOR_RAIN_LOW 0.25
#endif
#ifndef WEATHER_SENSOR_RAIN_HIGH
  #define WEATHER_SENSOR_RAIN_HIGH 0.75
#endif

// setup anemometer
class RainGeneric {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern RainGeneric rainGeneric;

#endif
