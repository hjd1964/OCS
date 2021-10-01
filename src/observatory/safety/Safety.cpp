// Observatory safety monitoring

#include "Safety.h"

#include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

#include "../../tasks/OnTask.h"
#include "../../lib/weatherSensor/WeatherSensor.h"
#include "../../lib/sense/Sense.h"
#include "../weather/Weather.h"
#include "../roof/Roof.h"

void safetyWrapper() { safety.poll(); }

bool validTime() { return (now() < 315360000); }

void Safety::init() {
  // start polling task
  VF("MSG: Safety, start monitor task (rate 1s priority 3)... ");
  if (tasks.add(1000, 0, true, 3, safetyWrapper, "Safety")) { VLF("success"); } else { VLF("FAILED!"); }
}

bool Safety::isSafe() {
  bool safe = true;
  int safetyDeviceCount = 0;

  #if STAT_MAINS_SENSE != OFF
    // check for mains power out
    if (!sense.isOn(STAT_MAINS_SENSE)) safe = false;
    safetyDeviceCount++;
  #endif

  #if WEATHER == ON
    float f;
    #if WEATHER_RAIN == ON
      // check for invalid or wet (1=Wet, 2=Warn, 3=Dry)
      f = weatherSensor.rain();
      if (isnan(f) || f < 2.0F) safe = false;
      safetyDeviceCount++;
    #endif
    
    #if WEATHER_CLOUD_CVR == ON
      // check for invalid or above WEATHER_SAFE_THRESHOLD
      f = weather.getAvgSkyDiffTemp();
      if (isnan(f) || f < -200 || f > WEATHER_SAFE_THRESHOLD) safe = false;
      safetyDeviceCount++;
    #endif
    
    #if WEATHER_WIND_SPD == ON
      // check for invalid or wind speed too high
      f = weatherSensor.windspeed();
      if (isnan(f) || f < 0 || f > WEATHER_WIND_SPD_THRESHOLD) safe = false;
      safetyDeviceCount++;
    #endif
  #endif

  if (safetyDeviceCount == 0) return false; else return safe;
}

void Safety::poll() {
  #if ROOF == ON
    // auto close the roof at 8am if requested
    if (roofAutoClose && validTime()) {
      if (hour() == 8 && !roofAutoCloseInitiated) {
        // if motion is idle
        if (!roof.isMoving()) {
          // and the roof isn't closed, close it
          if (!roof.isClosed()) roof.close();
          roofAutoCloseInitiated = true;
        }
      }
      if (hour() == 9) roofAutoCloseInitiated = false;
    }

    #if ROOF_AUTOCLOSE_SAFETY == ON
      // close the roof if safety status calls for it
      if (!isSafe()) {
        // if the roof isn't closed, and motion is idle, close it
        if (!roof.isClosed() && !roof.isMoving()) roof.close();
      }
    #endif
  #endif
}

Safety safety;
