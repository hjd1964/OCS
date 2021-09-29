// -----------------------------------------------------------------------------------------------------------------------------
// Weather related functions
#pragma once

#include "../../Common.h"

#if WEATHER_SENSOR_TH_SI7021 != OFF

class Si7021w {
  public:
    bool init();
    void poll();

    bool getT = false;
    bool getH = false;

  private:
    bool active = false;

    float temperature = NAN;
    float averageTemperature = NAN;
    float pressure = NAN;
};

extern Si7021w si7021w;

#endif
