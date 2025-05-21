// -----------------------------------------------------------------------------------
// Constants
#pragma once

// Settings ------------------------------------------------------------------------------------------------------------------------

// Pinmaps
#define PINMAP_FIRST                1
// Mega2560 based:
#define OCS1                        1      // OCS V1 board (6 SSR + 6 MECH RELAY + 6 DIN + 6 AIN)
#define OCS2                        1      // OCS V2 board (as above with onboard 5V switching regulator)
#define LEGACY                      1      // Generic Mega2560 board (for builds using eBay relay boards, etc.)
// Teensy3.5/3.6/4.1 based:
#define OCS3                        2      // OCS V3 board (4 SSR + 2 MOSFET + 4 MECH RELAY (+ 8 optional RELAYS) + 6 DIN + 6 AIN)
#define OCS4                        3      // OCS V4 board (5 SSR + 2 MOSFET + 5 MECH RELAY (+ 6 optional RELAYS) + 6 DIN + 6 AIN)
// ESP32 based:
#define OCS_ESP1                    5      // OCS ESP32-S DevKit-C basic pinmap (10 RELAYS + 6 DIN + 6 AIN)
#define OCS_ESP2                    6      // OCS ESP32-S2 DevKitM-1 basic pinmap (16 RELAYS + 6 DIN + 6 AIN)
#define PINMAP_LAST                 6

// TIME LOCATION SOURCE devices supported
#define TLS_FIRST                   1
#define DS3231                      1      // DS3231 RTC on I2C
#define DS3234                      2      // DS3234 RTC on SPI (DS3234_CS_PIN) Makuna library
#define SD3031                      3      // SD3031 RTC
#define TEENSY                      4      // TEENSY3.2 RTC (Built-in)
#define GPS                         5      // GPS device
#define NTP                         6      // NTP network time protocol
#define TLS_LAST                    6

#define DEFAULT_AJAX_RATE           "5"    // normally 5 seconds between updates
#define DEFAULT_FAST_AJAX_RATE      "1"    // fast update is 1 second/update
#define DEFAULT_AJAX_SHED_TIME      "15"   // time before return to normal update rate

// Time
#define STD                         1
#define DST                         2
#define UT1                         3

// Units
#define METRIC                      1
#define IMPERIAL                    2

// DOME
// STEP WAVE FORM
#define STEP_WAVE_FORM_FIRST        1
#define SQUARE                      1
#define PULSE                       2
#define STEP_WAVE_FORM_LAST         2

// background ajax page update timing (in milliseconds, 50ms minimum)
#define AJAX_PAGE_UPDATE_RATE_MS      1000    // normal ajax page update update rate

// Misc ----------------------------------------------------------------------------------------------------------------------------

// unused ajax page update feature
#define AJAX_PAGE_UPDATE_RATE_FAST_MS 500     // fast update rate
#define AJAX_PAGE_UPDATE_FAST_SHED_MS 5000    // time before return to normal update rate

// we don't use BT in the OCS
#define SERIAL_BT_MODE              OFF

// IP modes are directly selected in the OCS pinmaps
#define SERIAL_IP_MODE              OFF

// a constant to trigger setting up a WiFi or Ethernet station connection to OnStep
// that connection currently supports parking the mount before closing any roof/shutter
// and detecting if OnStep thinks the mount has been parked (as a safety interlock)
#define NETWORK_STATION             -3

// use timeLib for internal clock
#define TLS_TIMELIB

// task manager
#define TASKS_MAX                   32     // up to 32 tasks
#define TASKS_SKIP_MISSED                  // just skip missed tasks if too late
#define TASKS_HWTIMERS              4      // up to 4 hardware timers

// default start of axis class hardware timers
#define AXIS_HARDWARE_TIMER_BASE    3      // in the OCS timer#1 is the watchdog and timer#2 is for relays

#ifndef RESPONSE_INTERVAL
  #define RESPONSE_INTERVAL         1000
#endif

// NV addresses
#define INIT_NV_KEY                 3062703969UL

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
#define NV_DOME_SETTINGS_BASE       26     // bytes: 21  , addr:  26.. 46
#define NV_HUMIDITY_SETPOINT        47     // bytes: 4   , addr:  47.. 47
