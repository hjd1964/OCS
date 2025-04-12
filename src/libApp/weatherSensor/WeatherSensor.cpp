// Weather sensors

#include "WeatherSensor.h"

#include "TphBme280.h"
#include "TpBmp280.h"
#include "TpBmp085.h"
#include "ThDht.h"
#include "ThSi7021.h"
#include "TAnalog.h"
#include "CloudMlx90614.h"
#include "RainGeneric.h"
#include "RainDigital.h"
#include "SkyQTsl2591.h"
#include "WindCupAnem.h"
#include "WindModernRevP.h"

// in degrees Celsius
float _temperature = NAN;
bool _temperatureAssigned = false;
char _temperatureName[40] = "None";

// in degrees Celsius
float _skyTemperature = NAN;
bool _skyTemperatureAssigned = false;
char _skyTemperatureName[40] = "None";

// in kph
float _windspeed = NAN;
bool _windSpeedAssigned = false;
char _windSpeedName[40] = "None";

// in mb
float _pressure = NAN;
bool _pressureAssigned = false;
char _pressureName[40] = "None";

// 1 is Rain, 2 is Warn, and 3 is Dry
float _humidity = NAN;
bool _humidityAssigned = false;
char _humidityName[40] = "None";

// 1, 2, 3
float _rainSense = NAN;
bool _rainSenseAssigned = false;
char _rainSenseName[40] = "None";

// in mag/arc-sec^2
float _skyQuality = NAN;
bool _skyQualityAssigned = false;
char _skyQualityName[40] = "None";

void WeatherSensor::init() {
  // slow down i2c so long distances work, still plenty fast for our little data being moved around
  HAL_WIRE.setClock(HAL_WIRE_CLOCK);

  #if defined(WEATHER_SENSOR_TPH_BME280) && WEATHER_SENSOR_TPH_BME280 != OFF
    bme280w.init();
  #endif

  #if defined(WEATHER_SENSOR_TP_BMP280) && WEATHER_SENSOR_TP_BMP280 != OFF
    bmp280w.init();
  #endif

  #if defined(WEATHER_SENSOR_TP_BMP085) && WEATHER_SENSOR_TP_BMP085 != OFF
    bmp085w.init();
  #endif

  #if defined(WEATHER_SENSOR_TH_SI7021) && WEATHER_SENSOR_TH_SI7021 != OFF
    si7021w.init();
  #endif

  #if defined(WEATHER_SENSOR_T_ANALOG) && WEATHER_SENSOR_T_ANALOG != OFF
    analogTemperaturew.init();
  #endif

  #if defined(WEATHER_SENSOR_TH_DHT) && WEATHER_SENSOR_TH_DHT != OFF
    dhtw.init();
  #endif

  #if defined(WEATHER_SENSOR_WIND_CUP) && WEATHER_SENSOR_WIND_CUP != OFF
    cupAnem.init();
  #endif

  #if defined(WEATHER_SENSOR_WIND_REV_P) && WEATHER_SENSOR_WIND_REV_P != OFF
    windRevP.init();
  #endif

  #if defined(WEATHER_SENSOR_RAIN_GENERIC) && WEATHER_SENSOR_RAIN_GENERIC != OFF
    rainGeneric.init();
  #endif

  #if defined(WEATHER_SENSOR_RAIN_DIGITAL) && WEATHER_SENSOR_RAIN_DIGITAL != OFF
    rainDigital.init();
  #endif

  #if defined(WEATHER_SENSOR_CLOUD_MLX90614) && WEATHER_SENSOR_CLOUD_MLX90614 != OFF
    mlx90614w.init();
  #endif

  #if defined(WEATHER_SENSOR_SKYQ_TSL2591) && WEATHER_SENSOR_SKYQ_TSL2591 != OFF
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
char* WeatherSensor::temperatureName() { return _temperatureName; }

// -----------------------------------------------------------------------------------------------------------------
// gets sky IR temperature in deg. C
// returns NAN if not implemented or if there's an error
float WeatherSensor::skyTemperature() {
  if (!isnan(_skyTemperature) && (_skyTemperature < -60.0F || _skyTemperature > 60.0F)) _skyTemperature = NAN;
  return _skyTemperature;
}
char* WeatherSensor::skyTemperatureName() { return _skyTemperatureName; }

// -----------------------------------------------------------------------------------------------------------------
// gets windspeed in kph
// returns NAN if not implemented or if there's an error
float WeatherSensor::windspeed() {
  if (!isnan(_windspeed) && (_windspeed < 0.0F || _windspeed > 250.0F)) _windspeed = NAN;
  return _windspeed;
}
char* WeatherSensor::windspeedName() { return _windSpeedName; }

// -----------------------------------------------------------------------------------------------------------------
// gets barometric pressure in mb
// returns NAN if not implemented or if there's an error; absolute pressure
float WeatherSensor::pressure() {
  if (!isnan(_pressure) && (_pressure < 100.0F || _pressure > 1100.0F)) _pressure = NAN;
  return _pressure;
}
char* WeatherSensor::pressureName() { return _pressureName; }

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
char* WeatherSensor::humidityName() { return _humidityName; }

// -----------------------------------------------------------------------------------------------------------------
// gets rain sensor info. 1 is Rain, 2 is Warn, and 3 is Dry
// return NAN if not implemented or if there's an error
float WeatherSensor::rain() {
  if (_rainSense != 1.0F && _rainSense != 2.0F && _rainSense != 3.0F) _rainSense = NAN;
  return _rainSense;
}
char* WeatherSensor::rainSenseName() { return _rainSenseName; }

// -----------------------------------------------------------------------------------------------------------------
// gets sky brightness in mag/arc-sec^2
// returns NAN if not implemented or if there's an error
float WeatherSensor::skyQuality() {
  return _skyQuality;
}
char* WeatherSensor::skyQualityName() { return _skyQualityName; }

WeatherSensor weatherSensor;
