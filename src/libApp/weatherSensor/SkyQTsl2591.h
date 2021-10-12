// -----------------------------------------------------------------------------------------------------------------
// gets sky brightness in mag/arc-sec^2
#pragma once

#include "../../Common.h"

#if defined(WEATHER_SENSOR_SKYQ_TSL2591) && WEATHER_SENSOR_SKYQ_TSL2591 != OFF

class Tsl2591w {
  public:
    bool init();
    void poll();

  private:
    bool active = false;

    float last_mag_per_sq_arcsec = NAN;
    unsigned long last_mag_per_sq_arcsec_time = 0;
};

extern Tsl2591w tsl2591w;

#endif
