// Thermostat sensors
#pragma once

#include "../../Common.h"

class ThermostatSensor {
  public:
    void init();

    // gets inside temperature in deg. C
    float temperature();

    // gets inside barometric pressure in mb (absolute)
    float pressure();

    // gets inside barometric pressure in mb (sea level relative)
    float pressureSeaLevel();

    // gets inside relative humidity in %
    float humidity();

  private:
};

extern ThermostatSensor thermostatSensor;
