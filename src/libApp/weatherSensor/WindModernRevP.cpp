// -----------------------------------------------------------------------------------------------------------------
// gets windspeed in kph
// this is for a Modern Devices Wind Sensor Rev. P
// see https://moderndevice.com/product/wind-sensor-rev-p/

#include "WindModernRevP.h"

#if defined(WEATHER_SENSOR_WIND_REV_P) && WEATHER_SENSOR_WIND_REV_P != OFF

#include "../../lib/tasks/OnTask.h"
#include "../analog/Analog.h"

extern float _windspeed;
extern bool _windSpeedAssigned;
extern char _windSpeedName[40];

void windRevPWrapper() { windRevP.poll(); }

// setup anemometer
bool WindRevP::init() {
  if (active) return true;

  if (_windSpeedAssigned) return false;

  VF("MSG: WindRevP, start monitor task (default rate priority 7)... ");
  if (tasks.add(WEATHER_SENSOR_SAMPLE_PERIOD, 0, true, 7, windRevPWrapper, "weaRevP")) {
    VLF("success");
    _windSpeedAssigned = true;
    strcpy(_windSpeedName, "Modern Devices Rev.P Hot Wire Anemometer on Analog Input");
    active = true;
  } else { VLF("FAILED!"); }

  return active;
}

// update
void WindRevP::poll() {
  if (!active) return;

  int adu = round(analog.read(WEATHER_SENSOR_WIND_REV_P)*1023.0F*(HAL_VCC/5.0F));
  _windspeed = powf((((float)adu - 264.0F) / 85.6814F), 3.36814F)*1.60934F;

  // Temperature compensation isn't implemented
  // const int TempPin = A7;   // temp sensor analog pin hooked up to Wind P sensor "TMP" pin
  // int tempRawAD = analogRead(TempPin);
  // float tempC = ((((float)tempRawAD * 5.0) / 1024.0) - 0.400) / .0195;
}

WindRevP windRevP;

#endif
