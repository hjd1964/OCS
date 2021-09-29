// -----------------------------------------------------------------------------------------------------------------
// gets windspeed in kph
// this is for a cup anemometer where each rotation causes switch (or hall effect) open/close event(s)
// the pin below counts the number of logic LOW to HIGH events in a given amount of time to calculate the RPM etc.
#pragma once

#include "../../Common.h"

#if WEATHER_SENSOR_WIND_CUP != OFF

// converts from PPM (pulses per minute) to KPH
#ifndef WEATHER_SENSOR_WIND_PPM2KPH
#define WEATHER_SENSOR_WIND_PPM2KPH 0.086886F
#endif

// setup anemometer
class CupAnem {
  public:
    bool init();
    void poll();

  private:
    bool active = false;

    int sensePin[8] = {SENSE1_PIN, SENSE2_PIN, SENSE3_PIN, SENSE4_PIN, SENSE5_PIN, SENSE6_PIN, SENSE7_PIN, SENSE8_PIN};
};

extern CupAnem cupAnem;

#endif
