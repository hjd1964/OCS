// -----------------------------------------------------------------------------------------------------------------------------
// BMP085 (I2C) for Temperature and Pressure
#include "TpBmp085.h"

#if defined(WEATHER_SENSOR_TP_BMP085) && WEATHER_SENSOR_TP_BMP085 != OFF

#include "../../lib/tasks/OnTask.h"

#include <Adafruit_BMP085.h>          // https://github.com/adafruit/Adafruit-BMP085-Library
                                      // and https://github.com/adafruit/Adafruit_Sensor
Adafruit_BMP085 bmp085SensorW;

extern float _inside_temperature;
extern bool _inside_temperatureAssigned;

extern float _inside_pressure;
extern bool _inside_pressureAssigned;

void bmp085Wrapper() { bmp085w.poll(); }

bool Bmp085w::init() {
  if (active) return true;

  if (_inside_temperatureAssigned || _inside_pressureAssigned) return false;

  if (bmp085SensorW.begin()) {
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      Wire.end();
      Wire.begin();
    #endif
    Wire.setClock(HAL_WIRE_CLOCK);

    VF("MSG: Bmp085w, start monitor task (rate 30s priority 7)... ");
    if (tasks.add(30000, 0, true, 7, bmp085Wrapper, "wea085")) {
      VLF("success");
      _inside_temperatureAssigned = true;
      _inside_pressureAssigned = true;
      active = true;
    } else { VLF("FAILED!"); }
  } else { DF("WRN: Bmp085w.init(), BMP085 (I2C 0x"); SERIAL_DEBUG.print(THERMOSTAT_SENSOR_TP_BMP085, HEX); DLF(") not found"); }

  return active;
}

// update
void Bmp085w::poll() {
  if (!active) return;

  _inside_temperature = bmp085SensorW.readTemperature();
  tasks.yield(1000);
  _inside_pressure = bmp085SensorW.readPressure()/100.0;
}

Bmp085w bmp085w;

#endif
