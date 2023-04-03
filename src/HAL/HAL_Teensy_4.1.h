// Platform setup ------------------------------------------------------------------------------------
#pragma once
extern float tempmonGetTemp(void);

// We define a more generic symbol, in case more Teensy boards based on different lines are supported
#define __TEENSYDUINO__

// 1/100 second resolution
#define HAL_FRACTIONAL_SEC 100.0F

// volatage for ADC conversions
#define HAL_VCC 3.3F

// Analog read and write
#ifndef ANALOG_READ_RANGE
  #define ANALOG_READ_RANGE 1023
#endif
#ifndef ANALOG_WRITE_RANGE
  #define ANALOG_WRITE_RANGE 8191
#endif
#ifndef ANALOG_WRITE_PWM_BITS
  #define ANALOG_WRITE_PWM_BITS 13 // up to 15 bits
#endif
#ifndef ANALOG_WRITE_PWM_FREQUENCY
  #define ANALOG_WRITE_PWM_FREQUENCY 18310.55
#endif

#define HAL_FAST_PROCESSOR

// Lower limit (fastest) step rate in uS for this platform (in SQW mode) and width of step pulse
#define HAL_MAXRATE_LOWER_LIMIT 1.5
#define HAL_PULSE_WIDTH 0  // effectively disable pulse mode since the pulse width is unknown at this time

// New symbol for the default I2C port -------------------------------------------------------------
#include <Wire.h>
#define HAL_Wire Wire
#ifndef HAL_WIRE_CLOCK
  #define HAL_WIRE_CLOCK 20000
#endif

// Non-volatile storage ------------------------------------------------------------------------------
#if NV_DRIVER == NV_DEFAULT
  #include "EEPROM.h"
  #include "../lib/nv/NV_EEPROM.h"
  #define HAL_NV_INIT() nv.init(E2END + 1, true, 0, false);
#endif

//--------------------------------------------------------------------------------------------------
// General purpose initialize for HAL

#include "../lib/watchdog/Watchdog.h"

#include "imxrt.h"

#ifdef EmptyStr
  #undef EmptyStr
#endif
#define EmptyStr "\1"

#define HAL_INIT() { \
  analogReadResolution(10); \
  analogWriteResolution(ANALOG_WRITE_PWM_BITS); \
}

#define HAL_RESET() { \
  SCB_AIRCR = 0x05FA0004; \
  asm volatile ("dsb"); \
}

//--------------------------------------------------------------------------------------------------
// Internal MCU temperature (in degrees C)
#define HAL_TEMP() ( tempmonGetTemp() )

// Watchdog control macros --------------------------------------------------------------------------
#if WATCHDOG != OFF
  #define WDT_ENABLE watchdog.enable(14);
  #define WDT_RESET watchdog.reset();
  #define WDT_DISABLE watchdog.disable();
#else
  #define WDT_ENABLE
  #define WDT_RESET
  #define WDT_DISABLE
#endif
