// -----------------------------------------------------------------------------------------------------------------------------
// Analog for Temperature (TMP36, LM35, etc.)
#include "TAnalog.h"

#if defined(WEATHER_SENSOR_T_ANALOG) && WEATHER_SENSOR_T_ANALOG != OFF

#include "../../lib/tasks/OnTask.h"

#include "../analog/Analog.h"

extern float _temperature;
extern bool _temperatureAssigned;
extern char _temperatureName[40];

void AnalogwWrapper() { analogTemperaturew.poll(); }

bool AnalogTemperaturew::init() {
  if (_temperatureAssigned) return false;

  VF("MSG: TAnalogw, start monitor task (default rate priority 7)... ");
  if (tasks.add(WEATHER_SENSOR_SAMPLE_PERIOD, 0, true, 7, AnalogwWrapper)) {
    VLF("success");
    _temperatureAssigned = true;
    strcpy(_temperatureName, "Generic Temperature Sensor on Analog Input");
    active = true;
  } else { VLF("FAILED!"); }

  return active;
}

// update
void AnalogTemperaturew::poll() {
  if (!active) return;

  _temperature = WEATHER_SENSOR_T_ANALOG2DEGC(analog.read(WEATHER_SENSOR_T_ANALOG));
}

AnalogTemperaturew analogTemperaturew;

#endif
