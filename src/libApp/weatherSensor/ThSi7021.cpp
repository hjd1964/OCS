// -----------------------------------------------------------------------------------------------------------------------------
// Si7021 for Temperature and Relative Humidity
#include "ThSi7021.h"

#if defined(WEATHER_SENSOR_TH_SI7021) && WEATHER_SENSOR_TH_SI7021 != OFF

#include "../../lib/tasks/OnTask.h"

#ifndef USE_SI7021_LIBRARY
  #include <Adafruit_HTU21DF.h> // https://github.com/adafruit/Adafruit_HTU21DF_Library/tree/master
  Adafruit_HTU21DF siSensorW = Adafruit_HTU21DF();
#else
  #include <Adafruit_Si7021.h> // https://github.com/adafruit/Adafruit_Si7021
  Adafruit_Si7021 siSensorW = Adafruit_Si7021();
#endif


extern float _temperature;
extern bool _temperatureAssigned;
extern char _temperatureName[40];

extern float _humidity;
extern bool _humidityAssigned;
extern char _humidityName[40];

void si7021Wrapper() { si7021w.poll(); }

bool Si7021w::init() {
  if (active) return true;

  if (_temperatureAssigned && _humidityAssigned) return false;

  if (!_temperatureAssigned) getT = true;
  if (!_humidityAssigned) getH = true;

  if (siSensorW.begin()) {
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      HAL_WIRE.end();
      HAL_WIRE.begin();
    #endif
    HAL_WIRE_SET_CLOCK();

    VF("MSG: Si7021w, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, si7021Wrapper, "weaSi7")) {
      VLF("success");
      if (!_temperatureAssigned) {
        _temperatureAssigned = true;
        strcpy(_temperatureName, "Silicon Labs SI7021 Temperature Sensor");
      }
      if (!_humidityAssigned) {
        _humidityAssigned = true;
        strcpy(_humidityName, "Silicon Labs SI7021 Humidity Sensor");
      }
      active = true;
    } else { VLF("FAILED!"); }
  } else { DLF("WRN: Si7021w.init(), SI7021 (I2C 0x40) not found"); }

  return active;
}

// update
void Si7021w::poll() {
  if (!active) return;

  if (getT) _temperature = siSensorW.readTemperature();
  tasks.yield(500);
  if (getH) _humidity = siSensorW.readHumidity();
}

Si7021w si7021w;

#endif
