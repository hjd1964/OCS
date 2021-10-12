// -----------------------------------------------------------------------------------------------------------------------------
// BMP280 (I2C) for inside Temperature and Pressure
#pragma once

#include "../../Common.h"

#if defined(THERMOSTAT_SENSOR_TP_BMP280) && THERMOSTAT_SENSOR_TP_BMP280 != OFF

class Bmp280t {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern Bmp280t bmp280t;

#endif
