// -----------------------------------------------------------------------------------
// Common includes
#pragma once

#include <Arduino.h>
#include "Constants.h"
#include "lib/Constants.h"
#include "lib/Macros.h"
#include "Config.common.h"
#include "HAL/HAL.h"
#include "pinmaps/Models.h"

#if DEBUG != OFF
  #define D(x)       SERIAL_DEBUG.print(x)
  #define DF(x)      SERIAL_DEBUG.print(F(x))
  #define DL(x)      SERIAL_DEBUG.println(x)
  #define DLF(x)     SERIAL_DEBUG.println(F(x))
#else
  #define D(x)
  #define DF(x)
  #define DL(x)
  #define DLF(x)
#endif

#if DEBUG == VERBOSE
  #define V(x)       SERIAL_DEBUG.print(x)
  #define VF(x)      SERIAL_DEBUG.print(F(x))
  #define VL(x)      SERIAL_DEBUG.println(x)
  #define VLF(x)     SERIAL_DEBUG.println(F(x))
  #define VLCCHK(P)  { VF("Constant? "); VL(__builtin_constant_p(P)); }
#else
  #define V(x)
  #define VF(x)
  #define VL(x)
  #define VLF(x)
#endif

#include "lib/nv/NV.h"
#include "lib/convert/Convert.h"

extern NVS nv;
extern char ocsVersion[10];

#if DOME_DRIVER_MODEL != OFF
  #define AXIS_PRESENT
#endif

#if DOME_DRIVER_MODEL != OFF
  #define DOME_PRESENT
#endif

