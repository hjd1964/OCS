// -----------------------------------------------------------------------------------------------------------------------------
// Analog for Temperature (TMP36, LM35, etc.)
#pragma once

#include "../../Common.h"

#if defined(WEATHER_SENSOR_T_ANALOG) && WEATHER_SENSOR_T_ANALOG != OFF

class AnalogTemperaturew {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern AnalogTemperaturew analogTemperaturew;

#endif
