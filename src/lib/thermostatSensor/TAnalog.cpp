// -----------------------------------------------------------------------------------------------------------------------------
// Analog for inside Temperature (TMP36, LM35, etc.)
#include "TAnalog.h"

#if THERMOSTAT_SENSOR_T_ANALOG != OFF

#include "../../tasks/OnTask.h"

#include "../analog/Analog.h"

extern float _inside_temperature;
extern bool _inside_temperatureAssigned;

bool AnalogTemperaturet::init() {
  if (_inside_temperatureAssigned) return false;
  _inside_temperatureAssigned = true;
  active = true;
  return active;
}

// update
void AnalogTemperaturet::poll() {
  if (!active) return;

  _inside_temperature = THERMOSTAT_SENSOR_T_ANALOG2DEGC(analog.read(THERMOSTAT_SENSOR_T_ANALOG));
}

AnalogTemperaturet analogTemperaturet;

#endif
