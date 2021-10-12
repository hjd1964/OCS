// -----------------------------------------------------------------------------------------------------------------------------
// BME280 (I2C) for Temperature, Pressure, and Humidity
#pragma once

#include "../../Common.h"

#if defined(WEATHER_SENSOR_TPH_BME280) && WEATHER_SENSOR_TPH_BME280 != OFF

class Bme280w {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern Bme280w bme280w;

#endif
