// -----------------------------------------------------------------------------------------------------------------------------
// Analog for inside Temperature (TMP36, LM35, etc.)
#include "TAnalog.h"

#if defined(THERMOSTAT_SENSOR_T_ANALOG) && THERMOSTAT_SENSOR_T_ANALOG != OFF

#include "../../lib/tasks/OnTask.h"

#include "../analog/Analog.h"

extern float _inside_temperature;
extern bool _inside_temperatureAssigned;

void AnalogtWrapper() { analogTemperaturet.poll(); }

bool AnalogTemperaturet::init() {
  if (_inside_temperatureAssigned) return false;

  VF("MSG: Analogt, start monitor task (default rate priority 7)... ");
  if (tasks.add(WEATHER_SENSOR_SAMPLE_PERIOD, 0, true, 7, AnalogtWrapper)) {
    VLF("success");
    _inside_temperatureAssigned = true;
    active = true;
  } else { VLF("FAILED!"); }

  return active;
}

// update
void AnalogTemperaturet::poll() {
  if (!active) return;

  _inside_temperature = THERMOSTAT_SENSOR_T_ANALOG2DEGC(analog.read(THERMOSTAT_SENSOR_T_ANALOG));
}

AnalogTemperaturet analogTemperaturet;

#endif
