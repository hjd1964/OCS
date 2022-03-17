// -----------------------------------------------------------------------------------
// Constants
#pragma once

// Settings ------------------------------------------------------------------------------------------------------------------------

// TIME LOCATION SOURCE devices supported
#define TLS_FIRST                   1
#define DS3231                      1      // DS3231 RTC on I2C
#define DS3234                      2      // DS3234 RTC on SPI (DS3234_CS_PIN) Makuna library
#define TEENSY                      3      // TEENSY3.2 RTC (Built-in)
#define GPS                         4      // GPS device
#define NTP                         5      // NTP network time protocol
#define TLS_LAST                    5

#define DEFAULT_AJAX_RATE           "5"    // normally 5 seconds between updates
#define DEFAULT_FAST_AJAX_RATE      "1"    // fast update is 1 second/update
#define DEFAULT_AJAX_SHED_TIME      "15"   // time before return to normal update rate

// Time
#define LST                         1
#define DST                         2
#define UTC                         3

// Units
#define METRIC                      1
#define IMPERIAL                    2

// Roof
#define ROOF_PRE_MOTION_TIME        1.5    // as above
#define ROOF_POST_MOTION_TIME       2.0    // as above
// in seconds, this blocks the main-loop so <= ~2 seconds!
#define ROOF_MOMENTARY_BUTTON_PRESS_TIME 1.0

// DOME
// STEP WAVE FORM
#define STEP_WAVE_FORM_FIRST        1
#define SQUARE                      1
#define PULSE                       2
#define STEP_WAVE_FORM_LAST         2

// Misc ----------------------------------------------------------------------------------------------------------------------------

// use timeLib for internal clock
#define TLS_TIMELIB

// task manager
#define TASKS_MAX                   20     // up to 20 tasks
#define TASKS_SKIP_MISSED
#define TASKS_HWTIMER1_ENABLE
#ifdef TEENSYDUINO
  #define TASKS_HWTIMER2_ENABLE
  #define TASKS_HWTIMER3_ENABLE
#endif

#ifndef RESPONSE_INTERVAL
  #define RESPONSE_INTERVAL 1000
#endif

#define PROD_ABV "OCS"

#define logRecordLocation(t) (round(hour(t)*3600L+minute(t)*60L+second(t))/30L)

// NV addresses
#define INIT_NV_KEY                 3062703967UL

#define NV_KEY                      0      // bytes: 4   , addr:   0..  3
#define NV_HEAT_SETPOINT            4      // bytes: 4   , addr:   4..  7
#define NV_COOL_SETPOINT            8      // bytes: 4   , addr:   8.. 11
#define NV_ROOF_TIME_TO_OPEN        12     // bytes: 4   , addr:  12.. 15
#define NV_ROOF_TIME_TO_CLOSE       16     // bytes: 4   , addr:  16.. 19
#define NV_POWER_DEVICE1            20     // bytes: 1   , addr:  20.. 20
#define NV_POWER_DEVICE2            21     // bytes: 1   , addr:  21.. 21
#define NV_POWER_DEVICE3            22     // bytes: 1   , addr:  22.. 22
#define NV_POWER_DEVICE4            23     // bytes: 1   , addr:  23.. 23
#define NV_POWER_DEVICE5            24     // bytes: 1   , addr:  24.. 24
#define NV_POWER_DEVICE6            25     // bytes: 1   , addr:  25.. 25
