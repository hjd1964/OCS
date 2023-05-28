// -----------------------------------------------------------------------------------------------------------------
// Gets rain sensor info. 1 is Rain and 3 is Dry
// For rain sensors that switch a relay. The digital input is switched against ground.
// Tested rain sensors:
// Kemo M152K:
// https://www.kemo-electronic.de/en/House/M152K-Rain-Sensor-Capacitive.php
// Hydreon RG-9:
// https://rainsensors.com/products/rg-9/

#pragma once

#include "../../Common.h"

#if defined(WEATHER_SENSOR_RAIN_DIGITAL) && WEATHER_SENSOR_RAIN_DIGITAL != OFF

// setup Digital Rain Sensor
class RainDigital {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern RainDigital rainDigital;

#endif