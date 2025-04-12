// -----------------------------------------------------------------------------------------------------------------
// gets sky brightness in mag/arc-sec^2

#include "SkyQTsl2591.h"

#if defined(WEATHER_SENSOR_SKYQ_TSL2591) && WEATHER_SENSOR_SKYQ_TSL2591 != OFF

#define WEATHER_SKY_QUAL_ZERO         0.0 //    0.0, n. Where n=-2.0 to 2.0 (in mpsas) offset
#define WEATHER_SKY_QUAL_SCALE        1.0 //    1.0, n. Where n=-0.5 to 1.5 (x) sensitivity scale factor

// I2C addresses 0x28 and 0x29
// using my customized library from https://github.com/hjd1964/Adafruit_TSL2591_Library
#include <Adafruit_TSL2591.h>
Adafruit_TSL2591 tlsSensor = Adafruit_TSL2591(2591);

#include "../../lib/tasks/OnTask.h"

extern float _temperature;
extern float _skyQuality;
extern bool _skyQualityAssigned;
extern char _skyQualityName[40];

void tsl2591Wrapper() { tsl2591w.poll(); }

// setup cloud sensor
bool Tsl2591w::init() {
  if (_skyQualityAssigned) return false;

  if (tlsSensor.begin()) {
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      HAL_WIRE.end();
      HAL_WIRE.begin();
    #endif
    HAL_WIRE.setClock(HAL_WIRE_CLOCK);

    VF("MSG: Tsl2591w, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, tsl2591Wrapper, "weaTsl")) {
      VLF("success");
      _skyQualityAssigned = true;
      strcpy(_skyQualityName, "AMS TSL2591 Ambient Light Sensor on I2C");
      tlsSensor.setGain(TSL2591_GAIN_MED);                   // 1x _LOW, 25x _MED, 428x _HIGH, 9876x _MAX (higher gain = more sensitivity)
      tlsSensor.setTiming(TSL2591_INTEGRATIONTIME_300MS);    // _100MS, _200MS, _300MS, _400MS, _500MS, _600MS (higher integration time = more sensitivity)
      active = true;
    } else { VLF("FAILED!"); }
  } else { DLF("WRN: Tsl2591w.init(), TSL2591 (I2C 0x28) not found"); }

  return active;
}

// update
void Tsl2591w::poll() {
  if (!active) return;

  // safe-guard to invalidate stale readings after 30 seconds
  if ((long)((last_mag_per_sq_arcsec_time + 30000UL) - millis()) < 0) last_mag_per_sq_arcsec = NAN;

  // read data from TSL2591 (non-blocking)
  uint32_t lum;

  tlsSensor.getFullLuminosity(TSL2591_GFL_INIT);
  tasks.yield(500);

  while (tlsSensor.getFullLuminosity(TSL2591_GFL_WAIT)) tasks.yield(500);

  tasks.yield(500);
  lum = tlsSensor.getFullLuminosity(TSL2591_GFL_DONE);

  uint16_t ir = lum >> 16;
  uint16_t full = lum & 0xFFFF;

  // automatically adapt gain and integration time
  if (!tlsSensor.autoscale(full, ir)) { _skyQuality = NAN; return; }
  
  // correct for sensor temperature sensitivity
  float t = _temperature;
  if (!isnan(t)) {
    full = tlsSensor.temperatureCorrectCh0(t, full);
    ir = tlsSensor.temperatureCorrectCh1(t, ir);
  }

  // finally get the visible brightness in Lux
  float lux = tlsSensor.calculateLux(full, ir);

  // Lux = Candela at 1 meter.
  // At 1 meter a 1 meter^2 surface has an approximately 60 deg fov so this TSL2591 effectively measures in Candela given a 60 deg TFOV lens.
  // Its sensitivity spread across the 180 deg FOV seems to be about right for 1 Candela with no lens, but I'm not an expert on this!
  // If using a 30 deg TFOV lens, for example, set WEATHER_SKY_QUAL_SCALE 4.0 since light from a smaller surface area is projected onto the sensor.
  float mag_per_sq_arcsec = WEATHER_SKY_QUAL_ZERO + log10((lux * WEATHER_SKY_QUAL_SCALE)/108000.0)/-0.4;
  last_mag_per_sq_arcsec = mag_per_sq_arcsec;
  last_mag_per_sq_arcsec_time = millis();

  _skyQuality = last_mag_per_sq_arcsec;
}

Tsl2591w tsl2591w;

#endif
