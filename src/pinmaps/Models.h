// -------------------------------------------------------------------------------------------------
// Loads pinmap model for current configuration
#pragma once

#if PINMAP == LEGACY
  #define PINMAP_STR "Legacy pinmap"
  #include "Pins.OCS12.h"
#elif PINMAP == OCS1
  #define PINMAP_STR "OCS1 board pinmap"
  #include "Pins.OCS12.h"
#elif PINMAP == OCS2
  #define PINMAP_STR "OCS2 board pinmap"
  #include "Pins.OCS12.h"
#elif PINMAP == OCS3
  #define PINMAP_STR "OCS3 board pinmap"
  #include "Pins.OCS3.h"
#elif PINMAP == OCS4
  #define PINMAP_STR "OCS4 board pinmap"
  #include "Pins.OCS4.h"
#elif PINMAP == OCS_ESP1
  #define PINMAP_STR "OCS_ESP1 board pinmap for ESP32-S DevKit-C"
  #include "Pins.OCSE.h"
#elif PINMAP == OCS_ESP2
  #define PINMAP_STR "OCS_ESP2 board pinmap for ESP32-S2 DevKitM-1"
  #include "Pins.OCSES2.h"
#else
  #define PINMAP_STR "Unknown"
#endif

// all unassigned pins OFF
#include "Pins.defaults.h"

#include "Validate.h"
