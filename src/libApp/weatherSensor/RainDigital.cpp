// -----------------------------------------------------------------------------------------------------------------
// Gets rain sensor info. 1 is Rain and 3 is Dry
// For rain sensors that switch a relay. The digital input is switched against ground.
// Tested rain sensors:
// Kemo M152K:
// https://www.kemo-electronic.de/en/House/M152K-Rain-Sensor-Capacitive.php
// Hydreon RG-9:
// https://rainsensors.com/products/rg-9/

#include "RainDigital.h"
#include "../../lib/sense/Sense.h"

#if defined(WEATHER_SENSOR_RAIN_DIGITAL) && WEATHER_SENSOR_RAIN_DIGITAL != OFF

#include "../../lib/tasks/OnTask.h"
#include "../analog/Analog.h"

extern float _rainSense;
extern bool _rainSenseAssigned;
extern char _rainSenseName[40];

void rainDigitalWrapper() { rainDigital.poll(); }

// setup rain sensor digital
bool RainDigital::init() {
  if (active) return true;

  if (_rainSenseAssigned) return false;

  VF("MSG: RainDigital, start monitor task (default rate priority 7)... ");
  if (tasks.add(WEATHER_SENSOR_SAMPLE_PERIOD, 0, true, 7, rainDigitalWrapper,"weaRain")) {
    VLF("success");
    _rainSenseAssigned = true;
    strcpy(_rainSenseName, "Digital Rain Sensor on Digital Input");
    active = true;
  } else { VLF("FAILED!"); }

  return active;
}

// update
void RainDigital::poll() {
  if (!active) return;
  
   if (sense.isOn(WEATHER_SENSOR_RAIN_DIGITAL)) _rainSense = 1.0F; else _rainSense = 3.0F;
 }

RainDigital rainDigital;

#endif