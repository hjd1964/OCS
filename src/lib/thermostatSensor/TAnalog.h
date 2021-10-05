// -----------------------------------------------------------------------------------------------------------------------------
// Analog for inside Temperature (TMP36, LM35, etc.)
#pragma once

#include "../../Common.h"

#if THERMOSTAT_SENSOR_T_ANALOG != OFF

class AnalogTemperaturet {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern AnalogTemperaturet analogTemperaturet;

#endif
