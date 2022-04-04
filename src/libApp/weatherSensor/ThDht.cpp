// -----------------------------------------------------------------------------------------------------------------
// DHT11, 22, etc. for Temperature and Relative Humidity
#include "ThDht.h"

#if defined(WEATHER_SENSOR_TH_DHT) && WEATHER_SENSOR_TH_DHT != OFF

#include "../../lib/tasks/OnTask.h"

extern float _temperature;
extern bool _temperatureAssigned;
extern char _temperatureName[40];

extern float _humidity;
extern bool _humidityAssigned;
extern char _humidityName[40];

void dhtWrapper() { dhtw.poll(); }

// setup anemometer
bool Dhtw::init() {
  if (active) return true;

  if (_temperatureAssigned && _humidityAssigned) return false;

  if (!_temperatureAssigned) getT = true;
  if (!_humidityAssigned) getH = true;

  int index = WEATHER_SENSOR_TH_DHT - 1;
  if (index < 0 || index > 7) return false;

  dhtSensor = new DHT(sensePin[index], WEATHER_SENSOR_TH_DHT_TYPE);
  dhtSensor->begin();

  VF("MSG: Dhtw, start monitor task (default rate priority 7)... ");
  if (tasks.add(WEATHER_SENSOR_SAMPLE_PERIOD, 0, true, 7, dhtWrapper, "weaDht")) {
    VLF("success");
    if (!_temperatureAssigned) {
      _temperatureAssigned = true;
      sprintf(_temperatureName, "Aosong DHT (type %d) Temperature Sensor", WEATHER_SENSOR_TH_DHT_TYPE);
    }
    if (!_humidityAssigned) {
      _humidityAssigned = true;
      sprintf(_humidityName, "Aosong DHT (type %d) Humidity Sensor", WEATHER_SENSOR_TH_DHT_TYPE);
    }
    active = true;
  } else { VLF("FAILED!"); }

  return active;
}

// update
void Dhtw::poll() {
  if (!active) return;

  if (getT) _temperature = dhtSensor->readTemperature();
  tasks.yield(500);
  if (getH) _humidity = dhtSensor->readHumidity();
}

Dhtw dhtw;

#endif
