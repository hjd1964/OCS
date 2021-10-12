// -----------------------------------------------------------------------------------------------------------------
// gets sky IR (Cloud detection) temperature in deg. C
#pragma once

#include "../../Common.h"

#if defined(WEATHER_SENSOR_CLOUD_MLX90614) && WEATHER_SENSOR_CLOUD_MLX90614 != OFF

class Mlx90614w {
  public:
    bool init();
    void poll();

  private:
    bool active = false;
};

extern Mlx90614w mlx90614w;

#endif
