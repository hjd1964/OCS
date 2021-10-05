// Platform setup ------------------------------------------------------------------------------------
// Teensy3.5
#pragma once

// We define a more generic symbol, in case more Teensy boards based on different lines are supported
#define __TEENSYDUINO__

// This platform has digitalReadFast, digitalWriteFast, etc.
#define HAL_HAS_DIGITAL_FAST

// 1/500 second sidereal timer
#define HAL_SIDEREAL_FRAC 500.0

// This platform has 16 bit PWM
#ifndef HAL_ANALOG_WRITE_BITS
  #define HAL_ANALOG_WRITE_BITS 8
#endif

// Lower limit (fastest) step rate in uS for this platform (in SQW mode) and width of step pulse
#define HAL_MAXRATE_LOWER_LIMIT 12
#define HAL_PULSE_WIDTH 750
#define HAL_FAST_PROCESSOR

// New symbol for the default I2C port -------------------------------------------------------------
#include <Wire.h>
#define HAL_Wire Wire
#define HAL_WIRE_CLOCK 20000

// Non-volatile storage ------------------------------------------------------------------------------
#ifdef NV_DEFAULT
  #include "EEPROM.h"
  #include "../lib/nv/NV_EEPROM.h"
#endif

//--------------------------------------------------------------------------------------------------
// General purpose initialize for HAL

#include "../lib/watchdog/Watchdog.h"
#include "../lib/serial/Serial_IP_Ethernet.h"

#if defined(SERIAL_IP)
  #define SERIAL_IP_BEGIN() SERIAL_IP.begin(9999);
#else
  #define SERIAL_IP_BEGIN()
#endif
#if defined(SERIAL_PIP)
  #define SERIAL_PIP_BEGIN() SERIAL_PIP.begin(9998);
#else
  #define SERIAL_PIP_BEGIN()
#endif

#define HAL_INIT() { \
  analogReadResolution(10); \
  analogWriteResolution(HAL_ANALOG_WRITE_BITS); \
  nv.init(E2END + 1, true, 0, false); \
  analogReference(DEFAULT); \
  watchdog.init(8); \
}

#define HAL_RESET() { \
  SCB_AIRCR = 0x05FA0004; \
  asm volatile ("dsb"); \
}

//--------------------------------------------------------------------------------------------------
// Internal MCU temperature (in degrees C)
#define _Tpin 70
#define HAL_TEMP() ( (-((analogRead(_Tpin)/1024.0)*3.3-0.719)/0.001715)+25.0 )

// Watchdog control macros --------------------------------------------------------------------------
#if WATCHDOG != OFF
  #define WDT_ENABLE watchdog.enable();
  #define WDT_RESET watchdog.reset();
  #define WDT_DISABLE watchdog.disable();
#else
  #define WDT_ENABLE
  #define WDT_RESET
  #define WDT_DISABLE
#endif
