// -----------------------------------------------------------------------------------------------------------------
// gets outside temperature in deg. C
// gets relative humidity in %
#pragma once

#include "../../Common.h"

#if WEATHER_SENSOR_TH_DHT != OFF

#include <DHT.h> // DHT temperature/humidity sensors https://github.com/adafruit/DHT-sensor-library

// DHT device type
#ifndef WEATHER_SENSOR_TH_DHT_TYPE
#define WEATHER_SENSOR_TH_DHT_TYPE DHT11
#endif

// setup DHT device
class Dhtw {
  public:
    bool init();
    void poll();

    DHT *dhtSensor;
    bool getT = false;
    bool getH = false;

  private:
    bool active = false;

    int sensePin[8] = {SENSE1_PIN, SENSE2_PIN, SENSE3_PIN, SENSE4_PIN, SENSE5_PIN, SENSE6_PIN, SENSE7_PIN, SENSE8_PIN};
};

extern Dhtw dhtw;

#endif
