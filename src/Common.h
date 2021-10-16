// -----------------------------------------------------------------------------------
// Common includes
#pragma once

#define SERIAL_IP_MODE ON
#define WEB_SERVER ON
#define STANDARD_IPSERIAL_CHANNEL ON
#define PERSISTENT_IPSERIAL_CHANNEL ON

#include <Arduino.h>
#include "Constants.h"
#include "lib/Constants.h"
#include "Config.common.h"
#include "HAL/HAL.h"
#include "lib/Macros.h"
#include "pinmaps/Models.h"
#include "lib/debug/Debug.h"
#include "lib/nv/NV.h"
extern NVS nv;

#include "lib/convert/Convert.h"

extern char ocsVersion[10];

#if DOME_DRIVER_MODEL != OFF
  #define AXIS_PRESENT
#endif

#if DOME_DRIVER_MODEL != OFF
  #define DOME_PRESENT
#endif

