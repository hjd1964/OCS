// Observatory safety monitoring

#pragma once

#include "../../Common.h"

class Safety {
  public:
    void init();

    bool isSafe();

    void poll();

    bool roofAutoClose = ROOF_AUTOCLOSE_DAWN_DEFAULT == ON;

  private:
    bool roofAutoCloseInitiated = false;
    int delayForMains = 0; // counter for delay period
    float wa = 0; // Wind speed accumulator
    float waMax = 600; // Maximum of 10minutes wind speed safety accumulator
};

extern Safety safety;
