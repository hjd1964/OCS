// -----------------------------------------------------------------------------------------------------------------
// Handle analog inputs
#include "Analog.h"

float Analog::read(int n) {
  if (n < 1 || n > 16) return NAN;
  if (pins[n - 1] != OFF) {
    #if ESP32
      return analogReadMilliVolts(pins[n - 1])/3300.0F;
    #else
      return analogRead(pins[n - 1])/1023.0F;
    #endif
  } else return NAN;
}

Analog analog;
