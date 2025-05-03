// -----------------------------------------------------------------------------------------------------------------------------
// BMP085 (I2C) for Temperature and Pressure
#include "TpBmp085.h"

#if defined(WEATHER_SENSOR_TP_BMP085) && WEATHER_SENSOR_TP_BMP085 != OFF

#include "../../lib/tasks/OnTask.h"

#include <Adafruit_BMP085.h>          // https://github.com/adafruit/Adafruit-BMP085-Library
                                      // and https://github.com/adafruit/Adafruit_Sensor
Adafruit_BMP085 bmp085SensorW;

extern float _temperature;
extern bool _temperatureAssigned;
extern char _temperatureName[40];

extern float _pressure;
extern bool _pressureAssigned;
extern char _pressureName[40];

void bmp085Wrapper() { bmp085w.poll(); }

bool Bmp085w::init() {
  if (active) return true;

  if (_temperatureAssigned || _pressureAssigned) return false;

  if (bmp085SensorW.begin()) {
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      HAL_WIRE.end();
      HAL_WIRE.begin();
    #endif
    HAL_WIRE_SET_CLOCK();

    VF("MSG: Bmp085w, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, bmp085Wrapper, "wea085")) {
      VLF("success");
      if (!_temperatureAssigned) {
        _temperatureAssigned = true;
        strcpy(_temperatureName, "Bosch BMP085/BMP180 Temperature Sensor on I2C");
      }
      if (!_pressureAssigned) {
        _pressureAssigned = true;
        strcpy(_pressureName, "Bosch BMP085/BMP180 Pressure Sensor on I2C");
      }
      active = true;
    } else { VLF("FAILED!"); }
  } else { DF("WRN: Bmp085w.init(), BMP085/BMP180 (I2C 0x"); if (DEBUG != OFF) SERIAL_DEBUG.print(WEATHER_SENSOR_TP_BMP085, HEX); DLF(") not found"); }

  return active;
}

// update
void Bmp085w::poll() {
  if (!active) return;

  _temperature = bmp085SensorW.readTemperature();
  tasks.yield(1000);
  _pressure = bmp085SensorW.readPressure()/100.0;
}

Bmp085w bmp085w;

#endif
