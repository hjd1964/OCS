// Weather sensors

#include "WeatherSensor.h"
#include <Wire.h>

#include "TpBmp280.h"
#include "TphBme280.h"
#include "ThDht.h"
#include "ThSi7021.h"
#include "TAnalog.h"
#include "CloudMlx90614.h"
#include "RainGeneric.h"
#include "SkyQTsl2591.h"
#include "WindCupAnem.h"
#include "WindModernRevP.h"

// in degrees Celsius
float _temperature = NAN;
bool _temperatureAssigned = false;

// in degrees Celsius
float _skyTemperature = NAN;
bool _skyTemperatureAssigned = false;

// in kph
float _windspeed = NAN;
bool _windSpeedAssigned = false;

// in mb
float _pressure = NAN;
bool _pressureAssigned = false;

// 1 is Rain, 2 is Warn, and 3 is Dry
float _humidity = NAN;
bool _humidityAssigned = false;

// 1, 2, 3
float _rainSense = NAN;
bool _rainSenseAssigned = false;

// in mag/arc-sec^2
float _skyQuality = NAN;
bool _skyQualityAssigned = false;

void WeatherSensor::init() {
  // slow down i2c so long distances work, still plenty fast for our little data being moved around
  Wire.setClock(HAL_WIRE_CLOCK);

  #if WEATHER_SENSOR_TPH_BME280 != OFF
    bme280w.init();
  #endif

  #if WEATHER_SENSOR_TP_BMP280 != OFF
    bmp280w.init();
  #endif

  #if WEATHER_SENSOR_TH_SI7021 != OFF
    si7021w.init();
  #endif

  #if WEATHER_SENSOR_T_ANALOG != OFF
    analogTemperaturew.init();
  #endif

  #if WEATHER_SENSOR_TH_DHT != OFF
    dhtw.init();
  #endif

  #if WEATHER_SENSOR_WIND_CUP != OFF
    cupAnem.init();
  #endif

  #if WEATHER_SENSOR_WIND_REV_P != OFF
    windRevP.init();
  #endif

  #if WEATHER_SENSOR_RAIN_GENERIC != OFF
    rainGeneric.init();
  #endif

  #if WEATHER_SENSOR_CLOUD_MLX90614 != OFF
    mlx90614w.init();
  #endif

  #if WEATHER_SENSOR_SKYQ_TSL2591 != OFF
    tsl2591w.init();
  #endif
}

// -----------------------------------------------------------------------------------------------------------------
// gets outside temperature in deg. C
// returns NAN if not implemented or if there's an error
float WeatherSensor::temperature() {
  if (!isnan(_temperature) && (_temperature < -60.0F || _temperature > 60.0F)) _temperature = NAN;
  return _temperature;
}

// -----------------------------------------------------------------------------------------------------------------
// gets sky IR temperature in deg. C
// returns NAN if not implemented or if there's an error
float WeatherSensor::skyTemperature() {
  if (!isnan(_skyTemperature) && (_skyTemperature < -60.0F || _skyTemperature > 60.0F)) _skyTemperature = NAN;
  return _skyTemperature;
}

// -----------------------------------------------------------------------------------------------------------------
// gets windspeed in kph
// returns NAN if not implemented or if there's an error
float WeatherSensor::windspeed() {
  if (!isnan(_windspeed) && (_windspeed < 0.0F || _windspeed > 250.0F)) _windspeed = NAN;
  return _windspeed;
}

// -----------------------------------------------------------------------------------------------------------------
// gets barometric pressure in mb
// returns NAN if not implemented or if there's an error; absolute pressure
float WeatherSensor::pressure() {
  if (!isnan(_pressure) && (_pressure < 100.0F || _pressure > 1100.0F)) _pressure = NAN;
  return _pressure;
}

float WeatherSensor::pressureSeaLevel() {
  return (pressure()/powf(1.0-((float)(WEATHER_ALTITUDE))/44330.0F, 5.255F));
}

// -----------------------------------------------------------------------------------------------------------------
// gets relative humidity in %
// returns NAN if not implemented or if there's an error
float WeatherSensor::humidity() {
  if (_humidity > 100.0) _humidity = 100.0;
  if (_humidity < 0.0) _humidity = NAN;
  return _humidity;
}

// -----------------------------------------------------------------------------------------------------------------
// gets rain sensor info. 1 is Rain, 2 is Warn, and 3 is Dry
// return NAN if not implemented or if there's an error
float WeatherSensor::rain() {
  if (_rainSense != 1.0F && _rainSense != 2.0F && _rainSense != 3.0F) _rainSense = NAN;
  return _rainSense;
}

// -----------------------------------------------------------------------------------------------------------------
// gets sky brightness in mag/arc-sec^2
// returns NAN if not implemented or if there's an error
float WeatherSensor::skyQuality() {
  return _skyQuality;
}

WeatherSensor weatherSensor;
