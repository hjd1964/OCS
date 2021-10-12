// Dome default settings
#pragma once

#ifndef DOME_DRIVER_MODEL
#define DOME_DRIVER_MODEL            OFF                         // specify a driver to enable
#endif
#ifndef DOME_STEPS_PER_DEGREE
#define DOME_STEPS_PER_DEGREE        100.0
#endif
#ifndef DOME_REVERSE
#define DOME_REVERSE                 OFF
#endif
#ifndef DOME_POWER_DOWN
#define DOME_POWER_DOWN              OFF                         // motor power off if at standstill > 30 sec
#endif
#ifndef DOME_WRAP
#define DOME_WRAP                    OFF                         // wrap for unlimited range
#endif
#ifndef DOME_LIMIT_MIN
#define DOME_LIMIT_MIN               -180                        // in degrees
#endif
#ifndef DOME_LIMIT_MAX
#define DOME_LIMIT_MAX               180                         // in degrees
#endif
#ifndef DOME_SENSE_HOME
#define DOME_SENSE_HOME              OFF                         // HIGH/LOW to activate home sensing and set direction
#endif
#ifndef DOME_SENSE_HOME_INIT
#define DOME_SENSE_HOME_INIT         INPUT_PULLUP                // pin mode for home sensing
#endif
#ifndef DOME_SENSE_LIMIT_MIN
#define DOME_SENSE_LIMIT_MIN         LIMIT_SENSE                 // HIGH/LOW to activate min limit
#endif
#ifndef DOME_SENSE_LIMIT_MAX
#define DOME_SENSE_LIMIT_MAX         LIMIT_SENSE                 // HIGH/LOW to activate max limit
#endif
#ifndef LIMIT_SENSE_INIT
#define LIMIT_SENSE_INIT              OFF
#endif
#ifndef DOME_SENSE_LIMIT_INIT
#define DOME_SENSE_LIMIT_INIT        LIMIT_SENSE_INIT            // pin mode for limit sensing
#endif
#ifndef DOME_ENABLE_STATE
#define DOME_ENABLE_STATE            LOW                         // default state for motor power on
#endif
#ifndef DOME_BACKLASH_RATE
#define DOME_BACKLASH_RATE           0.1                         // in degrees/second
#endif

// check/flag SD stepper drivers
#if DOME_DRIVER_MODEL >= DRIVER_FIRST && DOME_DRIVER_MODEL <= DRIVER_LAST
  #define DOME_DRIVER_SD
#endif

#if defined(DOME_DRIVER_SD)
  #define SD_DRIVER_PRESENT
#endif

// check/flag TMC stepper drivers
#if DOME_DRIVER_MODEL == TMC2130 || DOME_DRIVER_MODEL == TMC5160
  #define DOME_DRIVER_TMC_SPI
#endif

#if defined(DOME_DRIVER_TMC_SPI)
  #define TMC_DRIVER_PRESENT
#endif

// common axis driver settings, RA/AZM
#ifndef DOME_DRIVER_MICROSTEPS
#define DOME_DRIVER_MICROSTEPS       OFF  // normal microstep mode 
#endif
#ifndef DOME_DRIVER_MICROSTEPS_GOTO
#define DOME_DRIVER_MICROSTEPS_GOTO  OFF  // microstep mode to use during slews
#endif
#ifndef DOME_DRIVER_DECAY
#define DOME_DRIVER_DECAY            OFF  // OFF for default
#endif
#ifndef DOME_DRIVER_DECAY_GOTO
#define DOME_DRIVER_DECAY_GOTO       OFF  // OFF for default
#endif
#ifndef DOME_DRIVER_STATUS
#define DOME_DRIVER_STATUS           OFF  // driver status reporting (ON for TMC SPI or HIGH/LOW for fault pin)
#endif
#ifndef DOME_PARAMETER1      
#define DOME_PARAMETER1              DOME_DRIVER_MICROSTEPS
#endif
#ifndef DOME_PARAMETER2 
#define DOME_PARAMETER2              OFF
#endif
#ifndef DOME_ENABLE_STATE
#define DOME_ENABLE_STATE            LOW  // default state of ENable pin for motor power on
#endif
#ifndef DOME_STEP_STATE
#define DOME_STEP_STATE              HIGH // default signal transition state for a step
#endif

#define DRIVER_STEP_DEFAULTS

// assign DRIVER_TYPE
#if DOME_DRIVER_MODEL >= SERVO_DRIVER_FIRST
  #define DOME_SERVO
#endif

#if defined(DOME_SERVO)
  #define SERVO_DRIVER_PRESENT
#endif

// common axis driver settings, RA/AZM
#ifndef DOME_SERVO_P
#define DOME_SERVO_P                 2.0    // P = proportional
#endif
#ifndef DOME_SERVO_I
#define DOME_SERVO_I                 5.0    // I = integral
#endif
#ifndef DOME_SERVO_D
#define DOME_SERVO_D                 1.0    // D = derivative
#endif
#ifndef DOME_SERVO_ENCODER
#define DOME_SERVO_ENCODER           ENC_AB
#endif
#ifndef DOME_SERVO_ENCODER_TRIGGER
#define DOME_SERVO_ENCODER_TRIGGER   CHANGE // ignored for ENC_AB
#endif
#ifndef DOME_SERVO_PH1_STATE
#define DOME_SERVO_PH1_STATE         LOW    // default state motor driver IN1 (SERVO_II) or PHASE (SERVO_PD) pin
#endif
#ifndef DOME_SERVO_PH2_STATE
#define DOME_SERVO_PH2_STATE         LOW    // default state motor driver IN2 or DIR pin
#endif
#ifndef DOME_DRIVER_STATUS
#define DOME_DRIVER_STATUS           OFF    // driver status reporting (ON for TMC SPI or HIGH/LOW for fault pin)
#endif
#ifndef DOME_PARAMETER1      
#define DOME_PARAMETER1              1      // subdivisions always 1
#endif
#ifndef DOME_PARAMETER2 
#define DOME_PARAMETER2              0      // not used
#endif
#ifndef DOME_ENABLE_STATE
#define DOME_ENABLE_STATE            LOW    // default state of ENable pin for motor power on
#endif
