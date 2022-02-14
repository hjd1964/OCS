// Dome control

#include "Dome.h"

#if DOME_DRIVER_MODEL != OFF

#include "../../lib/axis/motor/stepDir/StepDir.h"

void Dome::init() {
  axis3.init(&motor3, pollAxis3);
  if (!motor3.init(moveAxis3)) {
    DLF("ERR: Dome, no motor exiting!");
    return;
  }
}

Dome dome;

#endif
