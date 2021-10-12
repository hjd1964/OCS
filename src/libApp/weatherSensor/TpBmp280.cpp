// -----------------------------------------------------------------------------------------------------------------------------
// BMP280 (I2C) for Temperature and Pressure
#include "TpBmp280.h"

#if defined(WEATHER_SENSOR_TP_BMP280) && WEATHER_SENSOR_TP_BMP280 != OFF

#include "../../lib/tasks/OnTask.h"

#include <Adafruit_BMP280.h>          // https://github.com/adafruit/Adafruit_BMP280_Library
                                      // and https://github.com/adafruit/Adafruit_Sensor
Adafruit_BMP280 bmp280SensorW;

extern float _temperature;
extern bool _temperatureAssigned;

extern float _pressure;
extern bool _pressureAssigned;

void bmp280Wrapper() { bmp280w.poll(); }

bool Bmp280w::init() {
  if (active) return true;

  if (_temperatureAssigned || _pressureAssigned) return false;

  if (bmp280SensorW.begin(WEATHER_SENSOR_TP_BMP280)) {
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      Wire.end();
      Wire.begin();
    #endif
    Wire.setClock(HAL_WIRE_CLOCK);

    VF("MSG: Bmp280w, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, bmp280Wrapper, "weaBmp")) {
      VLF("success");
      _temperatureAssigned = true;
      _pressureAssigned = true;
      active = true;
    } else { VLF("FAILED!"); }
  } else { DF("WRN: Bmp280w.init(), BMP280 (I2C 0x"); SERIAL_DEBUG.print(WEATHER_SENSOR_TP_BMP280, HEX); DLF(") not found"); }

  return active;
}

// update
void Bmp280w::poll() {
  if (!active) return;

  _temperature = bmp280SensorW.readTemperature();
  tasks.yield(1000);
  _pressure = bmp280SensorW.readPressure()/100.0;
}

Bmp280w bmp280w;

#endif