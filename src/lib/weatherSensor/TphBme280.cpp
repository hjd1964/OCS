// -----------------------------------------------------------------------------------------------------------------------------
// BME280 (I2C) for Temperature, Pressure, and Humidity
#include "TphBme280.h"

#if WEATHER_SENSOR_TPH_BME280 != OFF

#include "../../tasks/OnTask.h"

#include <Adafruit_BME280.h>          // https://github.com/adafruit/Adafruit_BME280_Library/tree/156a0537d6b21aaab1d1f104a7001a38ca1ffce3
                                      // and https://github.com/adafruit/Adafruit_Sensor
Adafruit_BME280 bmeSensor;

extern float _temperature;
extern bool _temperatureAssigned;

extern float _pressure;
extern bool _pressureAssigned;

extern float _humidity;
extern bool _humidityAssigned;

void bme280Wrapper() { bme280w.poll(); }

bool Bme280w::init() {
  if (active) return true;

  if (_temperatureAssigned || _pressureAssigned || _humidityAssigned) return false;

  if (bmeSensor.begin(WEATHER_SENSOR_TPH_BME280)) {
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      Wire.end();
      Wire.begin();
    #endif
    Wire.setClock(HAL_WIRE_CLOCK);

    VF("MSG: Bme280w, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, bme280Wrapper, "weaBme")) {
      VLF("success");
      _temperatureAssigned = true;
      _pressureAssigned = true;
      _humidityAssigned = true;
      active = true;
    } else { VLF("FAILED!"); }
  } else { DF("WRN: Bme280w.init(), BME280 (I2C 0x"); SERIAL_DEBUG.print(WEATHER_SENSOR_TPH_BME280, HEX); DLF(") not found"); }

  return active;
}

// update
void Bme280w::poll() {
  if (!active) return;

  _temperature = bmeSensor.readTemperature();
  tasks.yield(1000);
  _pressure = bmeSensor.readPressure()/100.0;
  tasks.yield(1000);
  _humidity = bmeSensor.readHumidity();
}

Bme280w bme280w;

#endif
