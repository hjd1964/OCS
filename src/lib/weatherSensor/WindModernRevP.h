// -----------------------------------------------------------------------------------------------------------------
// gets windspeed in kph
// this is for a Modern Devices Wind Sensor Rev. P
#pragma once

#include "../../Common.h"

#if WEATHER_SENSOR_WIND_REV_P != OFF

// setup anemometer
class WindRevP {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern WindRevP windRevP;

#endif
