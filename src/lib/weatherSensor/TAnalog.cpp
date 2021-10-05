// -----------------------------------------------------------------------------------------------------------------------------
// Analog for Temperature (TMP36, LM35, etc.)
#include "TAnalog.h"

#if WEATHER_SENSOR_T_ANALOG != OFF

#include "../../tasks/OnTask.h"

#include "../analog/Analog.h"

extern float _temperature;
extern bool _temperatureAssigned;

bool AnalogTemperaturew::init() {
  if (_temperatureAssigned) return false;
  _temperatureAssigned = true;
  active = true;
  return active;
}

// update
void AnalogTemperaturew::poll() {
  if (!active) return;

  _temperature = WEATHER_SENSOR_T_ANALOG2DEGC(analog.read(WEATHER_SENSOR_T_ANALOG));
}

AnalogTemperaturew analogTemperaturew;

#endif
