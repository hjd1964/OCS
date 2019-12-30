// -----------------------------------------------------------------------------------------------------------------
// Weather functions

#include <Wire.h>
bool outsideTempGood=false, skyTempGood=false, windspeedGood=false, pressureGood=false, humidityGood=false, rainGood=false, skyQualityGood=false;

// =================================================================================================================
// =================================== add your weather sensor support below =======================================

//#include <Adafruit_Sensor.h>

// -----------------------------------------------------------------------------------------------------------------
// gets outside temperature in deg. C

// return (invalid) if not implemented or if there's an error
double weatherOutsideTemp() {
  if (!outsideTempGood) return invalid;
  return invalid;
}

bool initOutsideTemp() {
  return false;
}

// -----------------------------------------------------------------------------------------------------------------
// gets sky IR temperature in deg. C

// return (invalid) if not implemented or if there's an error
double weatherSkyTemp() {
  if (!skyTempGood) return invalid;
  return invalid;
}

bool initSkyTemp() {
  return false;
}

// -----------------------------------------------------------------------------------------------------------------
// gets windspeed in kph

// return (invalid) if not implemented or if there's an error
double weatherWindspeed() {
  if (!windspeedGood) return invalid;
  return invalid;
}

bool initWindspeed() {
  return false;
}

// -----------------------------------------------------------------------------------------------------------------
// gets barometric pressure in mb

// return (invalid) if not implemented or if there's an error, absolute pressure
double weatherPressure() {
  if (!pressureGood) return invalid;
  return invalid;
}

// return (invalid) if not implemented or if there's an error, sea-level adjusted
double weatherPressureSeaLevel() {
  if (!pressureGood) return invalid;
  return invalid;
}

bool initPressure() {
  return false;
}

// -----------------------------------------------------------------------------------------------------------------
// gets relative humidity in %

// return (invalid) if not implemented or if there's an error
double weatherHumidity() {
  if (!humidityGood) return invalid;
  return invalid;
}

bool initHumidity() {
  return false;
}

// -----------------------------------------------------------------------------------------------------------------
// gets rain sensor info. 1 is Rain, 2 is Warn, and 3 is Dry

// return (invalid) if not implemented or if there's an error
int weatherRain() {
  if (!rainGood) return invalid;
  return invalid;
}

bool initRain() {
  return false;
}

// -----------------------------------------------------------------------------------------------------------------
// gets sky brightness in mag/arc-sec^2

// return (invalid) if not implemented or if there's an error
double weatherSkyQuality() {
  if (!rainGood) return invalid;
  return invalid;
}

bool initSkyQuality() {
  return false;
}

// ============================== no user changes are required beyond this point ===================================
// =================================================================================================================

// -----------------------------------------------------------------------------------------------------------------
// this gets called once on startup to initialize any weather sensors
void weatherInit() {
  // slow down i2c so long distances work, still plenty fast for our little data being moved around
  Wire.setClock(20000);
  analogReference(DEFAULT);

  // wiring has pullups enabled, for a 3.3V I2C device this isn't a good thing even this hack isn't 100% perfect 
  // since 5V is applied for an instant at startup use a level converter if this causes you to loose sleep

#ifdef DEBUG_WEATHER_ON
  Serial.println("Debug weather start");
#endif

  outsideTempGood=initOutsideTemp();
  pinMode(20,INPUT); pinMode(21,INPUT);
#ifdef DEBUG_WEATHER_ON
  if (outsideTempGood) Serial.println("OUTSIDE TEMP sense up"); else Serial.println("OUTSIDE TEMP sense fail");
#endif

  skyTempGood=initSkyTemp();
  pinMode(20,INPUT); pinMode(21,INPUT);
#ifdef DEBUG_WEATHER_ON
  if (skyTempGood) Serial.println("SKY IR sense up"); else Serial.println("SKY IR sense fail");
#endif

  windspeedGood=initWindspeed();
  pinMode(20,INPUT); pinMode(21,INPUT);
#ifdef DEBUG_WEATHER_ON
  if (windspeedGood) Serial.println("WINDSPEED sense up"); else Serial.println("WINDSPEED sense fail");
#endif

  pressureGood=initPressure();
  pinMode(20,INPUT); pinMode(21,INPUT);
#ifdef DEBUG_WEATHER_ON
  if (pressureGood) Serial.println("PRESSURE sense up"); else Serial.println("PRESSURE sense fail");
#endif

  humidityGood=initHumidity();
  pinMode(20,INPUT); pinMode(21,INPUT);
#ifdef DEBUG_WEATHER_ON
  if (humidityGood) Serial.println("HUMIDITY sense up"); else Serial.println("HUMIDITY sense fail");
#endif

  rainGood=initRain();
  pinMode(20,INPUT); pinMode(21,INPUT);
#ifdef DEBUG_WEATHER_ON
  if (rainGood) Serial.println("RAIN sense up"); else Serial.println("RAIN sense fail");
#endif

  skyQualityGood=initSkyQuality();
  pinMode(20,INPUT); pinMode(21,INPUT);
#ifdef DEBUG_WEATHER_ON
  if (skyQualityGood) Serial.println("SKY QUAL up"); else Serial.println("SKY QUAL fail");
#endif
}
