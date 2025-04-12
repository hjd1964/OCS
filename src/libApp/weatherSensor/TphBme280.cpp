// -----------------------------------------------------------------------------------------------------------------------------
// BME280 (I2C) for Temperature, Pressure, and Humidity
#include "TphBme280.h"

#if defined(WEATHER_SENSOR_TPH_BME280) && WEATHER_SENSOR_TPH_BME280 != OFF

#include "../../lib/tasks/OnTask.h"

#include <Adafruit_BME280.h>          // https://github.com/adafruit/Adafruit_BME280_Library
                                      // and https://github.com/adafruit/Adafruit_Sensor
Adafruit_BME280 bme280SensorW;

extern float _temperature;
extern bool _temperatureAssigned;
extern char _temperatureName[40];

extern float _pressure;
extern bool _pressureAssigned;
extern char _pressureName[40];

extern float _humidity;
extern bool _humidityAssigned;
extern char _humidityName[40];

void bme280Wrapper() { bme280w.poll(); }

bool Bme280w::init() {
  if (active) return true;

  if (_temperatureAssigned || _pressureAssigned || _humidityAssigned) return false;

  if (bme280SensorW.begin(WEATHER_SENSOR_TPH_BME280)) {
    bme280SensorW.setSampling(Adafruit_BME280::MODE_FORCED, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::SAMPLING_X1,
                              Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_OFF);
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      HAL_WIRE.end();
      HAL_WIRE.begin();
    #endif
    HAL_WIRE.setClock(HAL_WIRE_CLOCK);

    VF("MSG: Bme280w, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, bme280Wrapper, "weaBme")) {
      VLF("success");
      if (!_temperatureAssigned) {
        _temperatureAssigned = true;
        strcpy(_temperatureName, "Bosch BME280 Temperature Sensor on I2C");
      }
      if (!_pressureAssigned) {
        _pressureAssigned = true;
        strcpy(_pressureName, "Bosch BME280 Pressure Sensor on I2C");
      }
      if (!_humidityAssigned) {
        _humidityAssigned = true;
        strcpy(_humidityName, "Bosch BME280 Humidity Sensor on I2C");
      }
      active = true;
    } else { VLF("FAILED!"); }
  } else { DF("WRN: Bme280w.init(), BME280 (I2C 0x"); if (DEBUG != OFF) SERIAL_DEBUG.print(WEATHER_SENSOR_TPH_BME280, HEX); DLF(") not found"); }

  return active;
}

// update
void Bme280w::poll() {
  if (!active) return;

  _temperature = bme280SensorW.readTemperature();
  tasks.yield(1000);
  _pressure = bme280SensorW.readPressure()/100.0;
  tasks.yield(1000);
  _humidity = bme280SensorW.readHumidity();
  bme280SensorW.takeForcedMeasurement();
}

Bme280w bme280w;

#endif
