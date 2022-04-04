// -----------------------------------------------------------------------------------
// Common includes
#pragma once

#include <Arduino.h>
#include "Constants.h"
#include "lib/Constants.h"
#include "../Config.h"
#include "Config.defaults.h"
#include "HAL/HAL.h"
#include "lib/Macros.h"
#include "pinmaps/Models.h"
#include "lib/debug/Debug.h"
#include "lib/nv/NV.h"
extern NVS nv;

#include "lib/convert/Convert.h"

extern char ocsVersion[10];

#if AXIS1_DRIVER_MODEL != OFF
  #define AXIS_PRESENT
#endif

