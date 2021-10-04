// -----------------------------------------------------------------------------------------------------------------
// Handle analog inputs
#include "Analog.h"

float Analog::read(int n) {
  if (n < 1 || n > 16) return NAN;
  if (pins[n - 1] != OFF) return analogRead(pins[n - 1])/1023.0F; else return NAN;
}

Analog analog;
