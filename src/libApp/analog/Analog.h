// -----------------------------------------------------------------------------------------------------------------
// Handle analog inputs
#pragma once

#include "../../Common.h"

#define ANALOG_MAX 16

#ifndef ASENSE1_PIN
#define ASENSE1_PIN OFF
#endif
#ifndef ASENSE2_PIN
#define ASENSE2_PIN OFF
#endif
#ifndef ASENSE3_PIN
#define ASENSE3_PIN OFF
#endif
#ifndef ASENSE4_PIN
#define ASENSE4_PIN OFF
#endif
#ifndef ASENSE5_PIN
#define ASENSE5_PIN OFF
#endif
#ifndef ASENSE6_PIN
#define ASENSE6_PIN OFF
#endif
#ifndef ASENSE7_PIN
#define ASENSE7_PIN OFF
#endif
#ifndef ASENSE8_PIN
#define ASENSE8_PIN OFF
#endif
#ifndef ASENSE9_PIN
#define ASENSE9_PIN OFF
#endif
#ifndef ASENSE10_PIN
#define ASENSE10_PIN OFF
#endif
#ifndef ASENSE11_PIN
#define ASENSE11_PIN OFF
#endif
#ifndef ASENSE12_PIN
#define ASENSE12_PIN OFF
#endif
#ifndef ASENSE13_PIN
#define ASENSE13_PIN OFF
#endif
#ifndef ASENSE14_PIN
#define ASENSE14_PIN OFF
#endif
#ifndef ASENSE15_PIN
#define ASENSE15_PIN OFF
#endif
#ifndef ASENSE16_PIN
#define ASENSE16_PIN OFF
#endif

class Analog {
  public:
    float read(int n);

  private:
    volatile int pins[ANALOG_MAX] {
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