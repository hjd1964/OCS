// -----------------------------------------------------------------------------------------------------------------------------
// BMP280 (I2C) for Temperature and Pressure
#pragma once

#include "../../Common.h"

#if defined(WEATHER_SENSOR_TP_BMP280) && WEATHER_SENSOR_TP_BMP280 != OFF

class Bmp280w {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern Bmp280w bmp280w;

#endif
