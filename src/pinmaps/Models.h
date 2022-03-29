// -------------------------------------------------------------------------------------------------
// Loads pinmap model for current configuration
#pragma once

#if PINMAP == LEGACY
  #define PINMAP_STR "Legacy Mega2560"
  #include "Pins.OCS12.h"
#elif PINMAP == OCS1
  #define PINMAP_STR "Hardware Version 1"
  #include "Pins.OCS12.h"
#elif PINMAP == OCS2
  #define PINMAP_STR "Hardware Version 2"
  #include "Pins.OCS12.h"
#elif PINMAP == OCS3
  #define PINMAP_STR "Hardware Version 3"
  #include "Pins.OCS3.h"
#elif PINMAP == OCS4
  #define PINMAP_STR "Hardware Version 4"
  #include "Pins.OCS4.h"
#else
  #define PINMAP_STR "Unknown"
#endif

// all unassigned pins OFF
#include "Pins.defaults.h"

#include "Validate.h"
