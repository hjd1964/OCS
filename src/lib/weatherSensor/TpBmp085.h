// -----------------------------------------------------------------------------------------------------------------------------
// BMP085 (I2C) for Temperature and Pressure
#pragma once

#include "../../Common.h"

#if WEATHER_SENSOR_TP_BMP085 != OFF

class Bmp085w {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern Bmp085w bmp085w;

#endif
