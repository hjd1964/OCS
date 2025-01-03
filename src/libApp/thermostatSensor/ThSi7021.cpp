// -----------------------------------------------------------------------------------------------------------------------------
// Si7021 for inside Temperature and Relative Humidity
#include "ThSi7021.h"

#if defined(THERMOSTAT_SENSOR_TH_SI7021) && THERMOSTAT_SENSOR_TH_SI7021 != OFF

#include "../../lib/tasks/OnTask.h"

#ifndef USE_SI7021_LIBRARY
  #include <Adafruit_HTU21DF.h> // https://github.com/adafruit/Adafruit_HTU21DF_Library/tree/master
  Adafruit_HTU21DF siSensorT = Adafruit_HTU21DF();
#else
  #include <Adafruit_Si7021.h> // https://github.com/adafruit/Adafruit_Si7021
  Adafruit_Si7021 siSensorT = Adafruit_Si7021();
#endif

extern float _inside_temperature;
extern bool _inside_temperatureAssigned;

extern float _inside_humidity;
extern bool _inside_humidityAssigned;

void thermostatSi7021Wrapper() { si7021t.poll(); }

bool Si7021t::init() {
  if (active) return true;

  if (_inside_temperatureAssigned && _inside_humidityAssigned) return false;

  if (!_inside_temperatureAssigned) getT = true;
  if (!_inside_humidityAssigned) getH = true;

  if (siSensorT.begin()) {
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      Wire.end();
      Wire.begin();
    #endif
    Wire.setClock(HAL_WIRE_CLOCK);

    VF("MSG: Si7021t, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, thermostatSi7021Wrapper, "thsSi7")) {
      VLF("success");
      _inside_temperatureAssigned = true;
      _inside_humidityAssigned = true;
      active = true;
    } else { VLF("FAILED!"); }
  } else { DLF("WRN: Si7021t.init(), SI7021 (I2C 0x40) not found"); }

  return active;
}

// update
void Si7021t::poll() {
  if (!active) return;

  if (getT) _inside_temperature = siSensorT.readTemperature();
  tasks.yield(500);
  if (getH) _inside_humidity = siSensorT.readHumidity();
}

Si7021t si7021t;

#endif
