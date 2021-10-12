// -----------------------------------------------------------------------------------------------------------------
// DHT11, 22, etc. for inside Temperature and Relative Humidity
#include "ThDht.h"

#if defined(THERMOSTAT_SENSOR_TH_DHT) && THERMOSTAT_SENSOR_TH_DHT != OFF

#include "../../lib/tasks/OnTask.h"

extern float _inside_temperature;
extern bool _inside_temperatureAssigned;

extern float _inside_humidity;
extern bool _inside_humidityAssigned;

void thermostatDhtWrapper() { dhtt.poll(); }

// setup anemometer
bool Dhtt::init() {
  if (active) return true;

  if (_inside_temperatureAssigned && _inside_humidityAssigned) return false;

  if (!_inside_temperatureAssigned) getT = true;
  if (!_inside_humidityAssigned) getH = true;

  int index = WEATHER_SENSOR_TH_DHT - 1;
  if (index < 0 || index > 7) return false;

  dhtSensor = new DHT(sensePin[index], WEATHER_SENSOR_TH_DHT_TYPE);
  dhtSensor->begin();

  VF("MSG: Dhtt, start monitor task (default rate priority 7)... ");
  if (tasks.add(WEATHER_SENSOR_SAMPLE_PERIOD, 0, true, 7, thermostatDhtWrapper)) {
    VLF("success");
    _inside_temperatureAssigned = true;
    _inside_humidityAssigned = true;
    active = true;
  } else { VLF("FAILED!"); }

  return active;
}

// update
void Dhtt::poll() {
  if (!active) return;

  if (getT) _inside_temperature = dhtSensor->readTemperature();
  tasks.yield(500);
  if (getH) _inside_humidity = dhtSensor->readHumidity();
}

Dhtt dhtt;

#endif
