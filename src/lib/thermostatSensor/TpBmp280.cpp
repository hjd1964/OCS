// -----------------------------------------------------------------------------------------------------------------------------
// BMP280 (I2C) for inside Temperature and Pressure
#include "TpBmp280.h"

#if THERMOSTAT_SENSOR_TP_BMP280 != OFF

#include "../../tasks/OnTask.h"

#include <Adafruit_BMP280.h>          // https://github.com/adafruit/Adafruit_BME280_Library/tree/156a0537d6b21aaab1d1f104a7001a38ca1ffce3
                                      // and https://github.com/adafruit/Adafruit_Sensor
Adafruit_BMP280 bmpSensor;

extern float _inside_temperature;
extern bool _inside_temperatureAssigned;

extern float _inside_pressure;
extern bool _inside_pressureAssigned;

void thermostatBmp280Wrapper() { bmp280t.poll(); }

bool Bmp280t::init() {
  if (active) return true;

  if (_inside_temperatureAssigned || _inside_pressureAssigned) return false;

  if (bmpSensor.begin(THERMOSTAT_SENSOR_TP_BMP280)) {
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      Wire.end();
      Wire.begin();
    #endif
    Wire.setClock(HAL_WIRE_CLOCK);

    VF("MSG: Bmp280t, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, thermostatBmp280Wrapper, "thsBmp")) {
      VLF("success");
      _inside_temperatureAssigned = true;
      _inside_pressureAssigned = true;
      active = true;
    } else { VLF("FAILED!"); }
  } else { DF("WRN: Bmp280t.init(), BMP280 (I2C 0x"); SERIAL_DEBUG.print(THERMOSTAT_SENSOR_TP_BMP280, HEX); DLF(") not found"); }

  return active;
}

// update
void Bmp280t::poll() {
  if (!active) return;

  _inside_temperature = bmpSensor.readTemperature();
  tasks.yield(1000);
  _inside_pressure = bmpSensor.readPressure()/100.0;
}

Bmp280t bmp280t;

#endif
