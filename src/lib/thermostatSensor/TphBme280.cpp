// -----------------------------------------------------------------------------------------------------------------------------
// BME280 (I2C) for Temperature, Pressure, and Humidity
#include "TphBme280.h"

#if THERMOSTAT_SENSOR_TPH_BME280 != OFF

#include "../../tasks/OnTask.h"

#include <Adafruit_BME280.h>          // https://github.com/adafruit/Adafruit_BME280_Library/tree/156a0537d6b21aaab1d1f104a7001a38ca1ffce3
                                      // and https://github.com/adafruit/Adafruit_Sensor
Adafruit_BME280 bme280;

extern float _inside_temperature;
extern bool _inside_temperatureAssigned;

extern float _inside_pressure;
extern bool _inside_pressureAssigned;

extern float _inside_humidity;
extern bool _inside_humidityAssigned;

void thermostatBme280Wrapper() { bme280t.poll(); }

bool Bme280t::init() {
  if (active) return true;

  if (_inside_temperatureAssigned || _inside_pressureAssigned || _inside_humidityAssigned) return false;

  if (bme280.begin(THERMOSTAT_SENSOR_TPH_BME280)) {
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      Wire.end();
      Wire.begin();
    #endif
    Wire.setClock(HAL_WIRE_CLOCK);

    VF("MSG: Bme280t, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, thermostatBme280Wrapper, "weaBme")) {
      VL("success");
      _inside_temperatureAssigned = true;
      _inside_pressureAssigned = true;
      _inside_humidityAssigned = true;
      active = true;
    } else { VL("FAILED!"); }
  } else { DF("WRN: Bme280t.init(), BME280 (I2C 0x"); SERIAL_DEBUG.print(THERMOSTAT_SENSOR_TPH_BME280, HEX); DLF(") not found"); }

  return active;
}

// update
void Bme280t::poll() {
  if (!active) return;

  _inside_temperature = bme280.readTemperature();
  tasks.yield(1000);
  _inside_pressure = bme280.readPressure()/100.0;
  tasks.yield(1000);
  _inside_humidity = bme280.readHumidity();
}

Bme280t bme280t;

#endif
