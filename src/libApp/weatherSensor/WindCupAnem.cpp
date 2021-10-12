// -----------------------------------------------------------------------------------------------------------------
// gets windspeed in kph
// this is for a cup anemometer where each rotation causes switch (or hall effect) open/close event(s)
// the pin below counts the number of logic LOW to HIGH events in a given amount of time to calculate the RPM etc.

#include "WindCupAnem.h"

#if defined(WEATHER_SENSOR_WIND_CUP) && WEATHER_SENSOR_WIND_CUP != OFF

#include "../../lib/tasks/OnTask.h"

extern float _windspeed;
extern bool _windSpeedAssigned;

volatile unsigned long _cupAnemometerPulseCount = 0;
void cupAnemISR() { _cupAnemometerPulseCount++; }

void cupAnemWrapper() { cupAnem.poll(); }

// setup anemometer
bool CupAnem::init() {
  if (active) return true;

  if (_windSpeedAssigned) return false;

  int index = WEATHER_SENSOR_WIND_CUP - 1;
  if (index < 0 || index > 7) return false;

  VF("MSG: CupAnem, start monitor task (default rate priority 1)... ");
  if (tasks.add(WEATHER_SENSOR_SAMPLE_PERIOD, 0, true, 1, cupAnemTask, "cupAnem")) {
    VLF("success");
    _windSpeedAssigned = true;
    attachInterrupt(digitalPinToInterrupt(sensePin[index]), cupAnemISR, RISING);
    active = true;
  } else { VLF("FAILED!"); }

  return active;
}

// update
void CupAnem::poll() {
  if (!active) return;

  static unsigned long checkTime = 0;
  long timeElapsed = (long)(millis() - checkTime);
  checkTime = millis();

  cli();
  long pulseCountThisElapsed = _cupAnemometerPulseCount;
  _cupAnemometerPulseCount = 0;
  sei();

  // convert pulses per sample period to PPM
  long PPM = pulseCountThisElapsed * (60000L/timeElapsed);
  _windspeed = WEATHER_SENSOR_WIND_CUP2KPH(PPM);
}

CupAnem cupAnem;

#endif
