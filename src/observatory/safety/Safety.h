// Observatory safety monitoring

#pragma once

#include "../../Common.h"

class Safety {
  public:
    void init();

    bool isSafe();
    inline void setRoofAutoClose(bool value) { roofAutoClose = value; }

    void poll();

  private:
    bool roofAutoClose = false;
    bool roofAutoCloseInitiated = false;
};

extern Safety safety;
