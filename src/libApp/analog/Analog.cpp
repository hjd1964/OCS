// -----------------------------------------------------------------------------------------------------------------
// Handle analog inputs
#include "Analog.h"

float Analog::read(int aSense) {
  if (aSense < 1 || aSense > 16) return NAN;
  if (pins[aSense - 1] != OFF) {
    #if ESP32
      return analogReadMilliVolts(pins[aSense - 1])/3300.0F;
    #else
      return analogRead(pins[aSense - 1])/(float)ANALOG_READ_RANGE;
    #endif
  } else return NAN;
}

// based on code from https://github.com/openenergymonitor/EmonLib
float Analog::readSct013(int aSense, float freqHz, float sensitivity) {
  const int samples = 1024;

  // grab about one cycle per call
  unsigned long waitTimeNs = ((1.0/freqHz)*100000.0)/samples;

  static float sumI;
  static float offsetI = (ANALOG_READ_RANGE + 1)/2.0F;
  static float filteredI = (ANALOG_READ_RANGE + 1)/2.0F;

  if (aSense < 1 || aSense > 16) return NAN;
  if (pins[aSense - 1] == OFF) return NAN;
  int pin = pins[aSense - 1];

  sumI = 0.0F;

  for (unsigned int n = 0; n < samples; n++) {
    // get the analog reading
    #if ESP32
      float sampleI = (analogReadMilliVolts(pin)/3300.0F)*ANALOG_READ_RANGE;
    #else
      float sampleI = analogRead(pin);
    #endif

    // digital low pass filter extracts the 2.5V or 1.65V DC offset
    offsetI = (offsetI + (sampleI - offsetI)/1024);
    // then subtract and the signal is now centered on 0 counts
    filteredI = sampleI - offsetI;

    // root-mean-square
    sumI += filteredI*filteredI;

    // wait as needed so we get a full cycle
    delayNanoseconds(waitTimeNs);
  }

  float ratioI = sensitivity*(HAL_VCC/(ANALOG_READ_RANGE + 1));
  float rmsI = ratioI*sqrt(sumI/samples);

  return rmsI;
}

Analog analog;
