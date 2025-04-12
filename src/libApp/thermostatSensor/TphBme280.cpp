// -----------------------------------------------------------------------------------------------------------------------------
// BME280 (I2C) for inside Temperature, Pressure, and Humidity
#include "TphBme280.h"

#if defined(THERMOSTAT_SENSOR_TPH_BME280) && THERMOSTAT_SENSOR_TPH_BME280 != OFF

#include "../../lib/tasks/OnTask.h"

#include <Adafruit_BME280.h>          // https://github.com/adafruit/Adafruit_BME280_Library
                                      // and https://github.com/adafruit/Adafruit_Sensor
Adafruit_BME280 bme280SensorT;

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

  if (bme280SensorT.begin(THERMOSTAT_SENSOR_TPH_BME280)) {
    bme280SensorT.setSampling(Adafruit_BME280::MODE_FORCED, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::SAMPLING_X1,
                              Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_OFF);
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      HAL_WIRE.end();
      HAL_WIRE.begin();
    #endif
    HAL_WIRE.setClock(HAL_WIRE_CLOCK);

    VF("MSG: Bme280t, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, thermostatBme280Wrapper, "thsBme")) {
      VLF("success");
      _inside_temperatureAssigned = true;
      _inside_pressureAssigned = true;
      _inside_humidityAssigned = true;
      active = true;
    } else { VLF("FAILED!"); }
  } else { DF("WRN: Bme280t.init(), BME280 (I2C 0x"); if (DEBUG != OFF) SERIAL_DEBUG.print(THERMOSTAT_SENSOR_TPH_BME280, HEX); DLF(") not found"); }

  return active;
}

// update
void Bme280t::poll() {
  if (!active) return;
  _inside_temperature = bme280SensorT.readTemperature();
  tasks.yield(1000);
  _inside_pressure = bme280SensorT.readPressure()/100.0;
  tasks.yield(1000);
  _inside_humidity = bme280SensorT.readHumidity();
  bme280SensorT.takeForcedMeasurement();
}

Bme280t bme280t;

#endif
