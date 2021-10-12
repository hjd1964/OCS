// Dome control

#include "Dome.h"

#if DOME != OFF

#include "../../lib/axis/motor/stepDir/StepDir.h"

void Dome::init() {
  #if DOME_DRIVER_MODEL != OFF && (defined(DOME_DRIVER_SD) || defined(DOME_SERVO))
    axis3.init(&motor3, pollAxis3);
    if (!motor3.init(moveAxis3)) {
      DLF("ERR: Dome, no motor exiting!");
      return;
    }
  #endif
}

Dome dome;

#endif
