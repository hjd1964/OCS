// -----------------------------------------------------------------------------------------------------------------
// Handle analog inputs
#pragma once

#include "../../Common.h"

#define ANALOG_MAX 16

typedef struct AnalogSettings {
  int pin;
} AnalogSettings;

class Analog {
  public:
    float read(int n);

  private:
    volatile AnalogSettings settings[ANALOG_MAX] {
      ASENSE1_PIN,
      ASENSE2_PIN,
      ASENSE3_PIN,
      ASENSE4_PIN,
      ASENSE5_PIN,
      ASENSE6_PIN,
      ASENSE7_PIN,
      ASENSE8_PIN,
      ASENSE9_PIN,
      ASENSE10_PIN,
      ASENSE11_PIN,
      ASENSE12_PIN,
      ASENSE13_PIN,
      ASENSE14_PIN,
      ASENSE15_PIN,
      ASENSE16_PIN
    };
};

extern Analog analog;