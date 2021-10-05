// -----------------------------------------------------------------------------------------------------------------------------
// Si7021 for inside Temperature and Relative Humidity
#pragma once

#include "../../Common.h"

#if THERMOSTAT_SENSOR_TH_SI7021 != OFF

class Si7021t {
  public:
    bool init();
    void poll();

    bool getT = false;
    bool getH = false;

  private:
    bool active = false;
};

extern Si7021t si7021t;

#endif
