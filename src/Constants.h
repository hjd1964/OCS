// -----------------------------------------------------------------------------------
// Constants
#pragma once

// Settings ------------------------------------------------------------------------------------------------------------------------

// On/Off, etc.
#define OFF                         -1
#define ON                          -2
#define ON_PULLUP                   -3
#define ON_PULLDOWN                 -4
#define ON_CC                       -5
#define SLAVE                       -8
#define VERBOSE                     -9
#define REMOTE                      -10
#define WIFI                        -11
#define ETHERNET_W5100              -12
#define ETHERNET_W5500              -13
#define DEFAULT_AJAX_RATE           "5"    // normally 5 seconds between updates
#define DEFAULT_FAST_AJAX_RATE      "1"    // fast update is 1 second/update
#define DEFAULT_AJAX_SHED_TIME      "15"   // time before return to normal update rate

// Time
#define LST                         1
#define DST                         2
#define UTC                         3

// various Time and Location sources supported
#define DS3231                      1      // DS3231 RTC on I2C
#define DS3234                      2      // DS3234 RTC on SPI (DS3234_CS_PIN) Makuna library
#define TEENSY                      4      // TEENSY3.2 RTC (Built-in)
#define GPS                         5      // GPS device
#define NTP                         6      // Network Time Protocol

#define SoftSerial                  7      // placeholder for a software serial port object
#define HardSerial                  8      // placeholder for a hardware serial port object

// Units
#define METRIC                      1
#define IMPERIAL                    2

// Misc ----------------------------------------------------------------------------------------------------------------------------
#define invalid -1000
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// various Weather sensors supported
#define BME280                      1      // BME280 on I2C (at default address 0x77)
#define BME280_0x77                 1      // BME280 on I2C (at address 0x77)
#define BME280_0x76                 2      // BME280 on I2C (at address 0x76)
#define BME280_SPI                  3      // BME280 on SPI (default CS)
#define BMP280                      4      // BMP280 on I2C (at default address 0x77)
#define BMP280_0x77                 4      // BMP280 on I2C (at address 0x77)
#define BMP280_0x76                 5      // BMP280 on I2C (at address 0x76)
#define BMP280_SPI                  6      // BMP280 on SPI (default CS)
#define THLD(v)                     ((v)<<1)  // 10 bit analog threshold, bits 1 through 10
#define HYST(v)                     ((v)<<11) // 10 bit hysteresis, bits 11 through 20
#ifndef INPUT_PULLDOWN
  #define INPUT_PULLDOWN INPUT
#endif

// task manager
#define TASKS_SKIP_MISSED
#define TASKS_HWTIMER1_ENABLE
#define TASKS_HWTIMER2_ENABLE
#define TASKS_HWTIMER3_ENABLE

#define pinModeEx pinMode
#define digitalReadEx digitalRead
#define digitalWriteEx digitalWrite

// NV write endurance constants
// low (< 100K writes)
#define NVE_LOW 0
// mid (~ 100K writes)
#define NVE_MID 1
// high (~ 1M writes)
#define NVE_HIGH 2
// very high (> 1M writes)
#define NVE_VHIGH 3
#define NV_ENDURANCE NVE_MID

#ifndef RESPONSE_INTERVAL
  #define RESPONSE_INTERVAL 1000
#endif

// Misc ----------------------------------------------------------------------------------------------------------------------------
#define invalid -1000

#ifdef EmptyStr
  #undef EmptyStr
#endif
#define EmptyStr ""

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define PROD_ABV "OCS"

#define NV_DEFAULT

#define logRecordLocation(t) (round(hour(t)*3600L+minute(t)*60L+second(t))/30L)

// Roof
#define ROOF_MOMENTARY_BUTTON_PRESS_TIME 1.0  // in seconds, this blocks the main-loop so <= ~2 seconds!
#define ROOF_PRE_MOTION_TIME             1.5  // as above
#define ROOF_POST_MOTION_TIME            2.0  // as above

// NV addresses
#define INIT_NV_KEY                 3062703966UL

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

