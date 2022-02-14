// Dome control
#pragma once

#include "../../Common.h"

#if DOME_DRIVER_MODEL != OFF
#include "../../lib/axis/Axis.h"

class Dome {
  public:
    void init();

  private:
};

#ifdef DOME_DRIVER_PRESENT
  extern StepDirMotor motor3;
#elif defined(DOME_SERVO_PRESENT)
  extern ServoMotor motor3;
#endif
extern IRAM_ATTR void moveAxis3();
extern IRAM_ATTR void pollAxis3();
extern Axis axis3;

extern Dome dome;

#endif
