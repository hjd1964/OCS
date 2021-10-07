// -----------------------------------------------------------------------------------------------------------------------------
// BMP085 (I2C) for inside Temperature and Pressure
#pragma once

#include "../../Common.h"

#if THERMOSTAT_SENSOR_TP_BMP085 != OFF

class Bmp085t {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern Bmp085t bmp085t;

#endif
