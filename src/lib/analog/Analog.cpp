// -----------------------------------------------------------------------------------------------------------------
// Handle analog inputs
#include "Analog.h"

float Analog::read(int n) {
  if (settings[n].pin != OFF) return analogRead(settings[n].pin)/1023.0F; else return NAN;
}

Analog analog;
