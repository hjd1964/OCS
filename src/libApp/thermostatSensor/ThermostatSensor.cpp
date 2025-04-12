// Thermostat sensors

#include "ThermostatSensor.h"

#include "TphBme280.h"
#include "TpBmp280.h"
#include "TpBmp085.h"
#include "ThDht.h"
#include "ThSi7021.h"
#include "TpBmp280.h"
#include "TAnalog.h"

float _inside_temperature = NAN;
bool _inside_temperatureAssigned = false;

float _inside_pressure = NAN;
bool _inside_pressureAssigned = false;

float _inside_humidity = NAN;
bool _inside_humidityAssigned = false;

void ThermostatSensor::init(){
  // slow down i2c so long distances work, still plenty fast for our little data being moved around
  HAL_WIRE.setClock(HAL_WIRE_CLOCK);

  #if defined(THERMOSTAT_SENSOR_TPH_BME280) && THERMOSTAT_SENSOR_TPH_BME280 != OFF
    bme280t.init();
  #endif

  #if defined(THERMOSTAT_SENSOR_TP_BMP280) && THERMOSTAT_SENSOR_TP_BMP280 != OFF
    bmp280t.init();
  #endif

  #if defined(THERMOSTAT_SENSOR_TP_BMP085) && THERMOSTAT_SENSOR_TP_BMP085 != OFF
    bmp085t.init();
  #endif

  #if defined(THERMOSTAT_SENSOR_TH_SI7021) && THERMOSTAT_SENSOR_TH_SI7021 != OFF
    si7021t.init();
  #endif

  #if defined(THERMOSTAT_SENSOR_TH_DHT) && THERMOSTAT_SENSOR_TH_DHT != OFF
    dhtt.init();
  #endif

  #if defined(THERMOSTAT_SENSOR_T_ANALOG) && THERMOSTAT_SENSOR_T_ANALOG != OFF
    analogTemperaturet.init();
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

ThermostatSensor thermostatSensor;
