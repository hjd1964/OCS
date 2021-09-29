// Thermostat sensors

#include "ThermostatSensor.h"
#include <Wire.h>

#if THERMOSTAT_SENSOR_TPH_BME280 != OFF
  #include "TphBme280.h"
#endif

float _inside_temperature;
bool _inside_temperatureAssigned;

float _inside_pressure;
bool _inside_pressureAssigned;

float _inside_humidity;
bool _inside_humidityAssigned;

void ThermostatSensor::init(){
  // slow down i2c so long distances work, still plenty fast for our little data being moved around
  Wire.setClock(HAL_WIRE_CLOCK);
  analogReference(DEFAULT);

  #if WEATHER_SENSOR_TPH_BME280 != OFF
    bme280t.init();
  #endif
}

// gets inside temperature in deg. C
float ThermostatSensor::temperature() {
  if (!isnan(_inside_temperature) && (_inside_temperature < -60.0F || _inside_temperature > 60.0F)) _inside_temperature = NAN;
  return _inside_temperature;
}

// gets inside barometric pressure in mb (absolute)
float ThermostatSensor::pressure() {
  if (!isnan(_inside_pressure) && (_inside_pressure < 100.0F || _inside_pressure > 1100.0F)) _inside_pressure = NAN;
  return _inside_pressure;
}

// gets inside barometric pressure in mb (sea level relative)
float ThermostatSensor::pressureSeaLevel() {
  return (pressure()/powf(1.0-((float)(WEATHER_ALTITUDE))/44330.0F, 5.255F));
}

// gets inside relative humidity in %
float ThermostatSensor::humidity() {
  if (_inside_humidity > 100.0) _inside_humidity = 100.0;
  if (_inside_humidity < 0.0) _inside_humidity = NAN;
  return _inside_humidity;
}
