// -----------------------------------------------------------------------------------------------------------------------------
// Si7021 for Temperature and Relative Humidity
#pragma once

#include "../../Common.h"

#if defined(WEATHER_SENSOR_TH_SI7021) && WEATHER_SENSOR_TH_SI7021 != OFF

class Si7021w {
  public:
    bool init();
    void poll();

    bool getT = false;
    bool getH = false;

  private:
    bool active = false;
};

extern Si7021w si7021w;

#endif
