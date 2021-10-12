// -----------------------------------------------------------------------------------------------------------------------------
// BME280 (I2C) for inside Temperature, Pressure, and Humidity
#pragma once

#include "../../Common.h"

#if defined(THERMOSTAT_SENSOR_TPH_BME280) && THERMOSTAT_SENSOR_TPH_BME280 != OFF

class Bme280t {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern Bme280t bme280t;

#endif
