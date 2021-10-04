// -------------------------------------------------------------------------------------------------
// Loads pinmap model for current configuration
#pragma once

#if defined(ESP32)
  #include "Pins.ESP32.h"
#endif

#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)
  #include "Pins.Mega2560.h"
#endif

#if defined(__MK64FX512__)
  #include "Pins.Teensy3.5.h"
#endif

#if defined(__MK66FX1M0__)
  #include "Pins.Teensy3.6.h"
#endif

#if defined(ARDUINO_TEENSY41)
  #include "Pins.Teensy4.1.h"
#endif

// all unassigned pins OFF
#include "Pins.defaults.h"

#include "Validate.h"
