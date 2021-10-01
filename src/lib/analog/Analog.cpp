// -----------------------------------------------------------------------------------------------------------------
// Handle analog inputs
#include "Analog.h"

float Analog::read(int n) {
  if (n < 1 || n > 16) return NAN;
  if (settings[n - 1].pin != OFF) return analogRead(settings[n - 1].pin)/1023.0F; else return NAN;
}

Analog analog;
