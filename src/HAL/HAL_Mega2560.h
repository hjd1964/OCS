// Platform setup ------------------------------------------------------------------------------------
// Mega2560
#pragma once

// We define a more generic symbol, in case more Teensy boards based on different lines are supported
// __AVR__

// 1/100 second resolution
#define HAL_FRACTIONAL_SEC 100.0F

// volatage for ADC conversions
#define HAL_VCC 5.0F

// This platform has 8 bit PWM
#ifndef ANALOG_WRITE_PWM_BITS
  #define ANALOG_WRITE_PWM_BITS 8
#endif
#ifndef ANALOG_WRITE_PWM_RANGE
  #define ANALOG_WRITE_PWM_RANGE 255
#endif

// This platform doesn't support true double precision math
#define HAL_NO_DOUBLE_PRECISION

// This is for ~16MHz AVR processors or similar.
#define HAL_SLOW_PROCESSOR

// Lower limit (fastest) step rate in uS for this platform (in SQW mode) and width of step pulse
#define HAL_MAXRATE_LOWER_LIMIT   76.8
#define HAL_PULSE_WIDTH          10000

// New symbol for the default I2C port -------------------------------------------------------------
#include <Wire.h>
#define HAL_Wire Wire
#ifndef HAL_WIRE_CLOCK
  #define HAL_WIRE_CLOCK 20000
#endif

// Non-volatile storage ----------------------------------------------------------------------------
#if NV_DRIVER == NV_DEFAULT
  #include "../lib/nv/NV_EEPROM.h"
  #define HAL_NV_INIT() nv.init(4096, false, 0, false);
#endif

//--------------------------------------------------------------------------------------------------
// General purpose initialize for HAL

#define HAL_INIT() { \
  analogReference(DEFAULT); \
}

//--------------------------------------------------------------------------------------------------
// Internal MCU temperature (in degrees C)
#define HAL_TEMP() ( NAN )

//---------------------------------------------------------------------------------------------------
// Misc.
#define strtof strtod // there is no strtof defined for the AVR platform

// Allow MCU reset ----------------------------------------------------------------------------------
#define HAL_RESET() mega2560restart();
#define HAL_RESET_FUNC void (*mega2560restart) (void) = 0;

// Watchdog control macros --------------------------------------------------------------------------
#if WATCHDOG != OFF
  #include <avr/wdt.h>
  #define WDT_ENABLE wdt_enable(WDTO_8S)
  #define WDT_RESET wdt_reset()
  #define WDT_DISABLE wdt_disable()
#else
  #define WDT_ENABLE
  #define WDT_RESET
  #define WDT_DISABLE
#endif
