// -----------------------------------------------------------------------------------------------------------------
// gets sky IR (Cloud detection) temperature in deg. C

#include "CloudMlx90614.h"

#if defined(WEATHER_SENSOR_CLOUD_MLX90614) && WEATHER_SENSOR_CLOUD_MLX90614 != OFF

#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlxSensor = Adafruit_MLX90614();  // I2C address 0x5A

#include "../../lib/tasks/OnTask.h"

// in degrees Celsius
extern float _skyTemperature;
extern bool _skyTemperatureAssigned;
extern char _skyTemperatureName[40];

void mlx90614Wrapper() { mlx90614w.poll(); }

// setup cloud sensor
bool Mlx90614w::init() {
  if (active) return true;

  if (_skyTemperatureAssigned) return false;

  if (mlxSensor.begin(WEATHER_SENSOR_CLOUD_MLX90614)) {
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
      Wire.end();
      Wire.begin();
    #endif
    Wire.setClock(HAL_WIRE_CLOCK);

    VF("MSG: Mlx90614w, start monitor task (default rate priority 7)... ");
    if (tasks.add(WEATHER_SENSOR_SAMPLE_PERIOD, 0, true, 7, mlx90614Wrapper, "m90614")) {
      VLF("success");
      _skyTemperatureAssigned = true;
      sprintf(_skyTemperatureName, "Melexis MLX90614 IR Sensor on I2C");
      active = true;
    } else { VLF("FAILED!"); }
  } else { DF("WRN: Mlx90614w.init(), MLX90614 (I2C 0x"); if (DEBUG != OFF) SERIAL_DEBUG.print(WEATHER_SENSOR_CLOUD_MLX90614, HEX); DLF(") not found"); }

  return active;
}

// update
void Mlx90614w::poll() {
  if (!active) return;

  _skyTemperature = mlxSensor.readObjectTempC(); 
  if (_skyTemperature < -100.0 || _skyTemperature > 100.0) _skyTemperature = NAN;
}

Mlx90614w mlx90614w;

#endif
