#pragma once

// host name for this microcontroller, by default used for the following if enabled/supported:
// PRODUCT_DESCRIPTION    the user friendly name for this device, appears on websites etc.
// HOST_NAME              the name ESP WiFi provides to any DHCP server (Ethernet doesn't support this)
// MDNS_NAME              the name mDNS (Multicast DNS) clients see for IP address resolution
// AP_SSID                the SSID WiFi clients see when the ESP WiFi Soft Access Point is enabled
#ifndef HOST_NAME
#define HOST_NAME                      "OCS"
#endif

// settings identification
#ifndef PRODUCT_DESCRIPTION
#define PRODUCT_DESCRIPTION            HOST_NAME
#endif

// use the HAL specified default NV driver
#ifndef NV_DRIVER
#define NV_DRIVER                      NV_DEFAULT
#endif

// pinmap
#ifndef PINMAP
#define PINMAP                         OFF   // specify the board you're using here
#endif

// display
#ifndef DISPLAY_LANGUAGE
#define DISPLAY_LANGUAGE               L_en  // currently english (en and us) are the only options
#endif

// watchdog
#ifndef WATCHDOG
#define WATCHDOG                       OFF   // ON resets if OCS hangs for >8 seconds
#endif

// log files
#ifdef ESP32
#ifndef LOG_PERIOD_SECONDS
#define LOG_PERIOD_SECONDS             120   // 120 seconds between log enteries
#endif
#ifndef LOG_CLEANUP_DAYS_AGO
#define LOG_CLEANUP_DAYS_AGO           30   // retain one month of files (80 bytes * 0.5 * 60 * 24 = 57600 bytes per day * 30 = 1728000 bytes)
#endif
#else
#ifndef LOG_PERIOD_SECONDS
#define LOG_PERIOD_SECONDS             30   // 30 seconds between log enteries
#endif
#endif

// network settings
#ifndef ASCOM_ALPACA_SERVER
#define ASCOM_ALPACA_SERVER            OFF   // enables ASCOM Alpaca server on port 10000, requires W5500 Ethernet
#endif
#ifndef CONNECT_CHECK_HOURS
#define CONNECT_CHECK_HOURS            OFF   // connection check time
#endif
#ifndef CONNECT_IP_ADDR
#define CONNECT_IP_ADDR   {100,24,172,113}   // default is arduino.cc. Needs ETHERNET_RESET_PIN and/or WATCHDOG to reset
#endif
#ifndef CONNECT_FAIL_WATCHDOG
#define CONNECT_FAIL_WATCHDOG          OFF   // ON to stop all processing and trigger the watchdog reset
#endif

// time settings
#ifndef TIME_LOCATION_SOURCE
#define TIME_LOCATION_SOURCE           NTP   // using Network Time Protocol is the default
#endif
#ifndef TIME_IP_ADDR
#define TIME_IP_ADDR         {129,6,15,28}   // time-a-g.nist.gov at 129,6,15,28 or 129,6,15,29, 129,6,15,30, etc.
#endif
#ifndef TIME_ZONE
#define TIME_ZONE                      -5   // Time Zone (US Eastern Standard Time in this case)
#endif
#ifndef TIME_DISPLAY
#define TIME_DISPLAY                   STD   // display Standard Time, UT1 to display Universal Time
#endif

// serial ports
#ifndef SERIAL_A_BAUD_DEFAULT
#define SERIAL_A_BAUD_DEFAULT          9600
#endif
#ifndef SERIAL_B_BAUD_DEFAULT
#define SERIAL_B_BAUD_DEFAULT          OFF
#endif
#ifndef SERIAL_C_BAUD_DEFAULT
#define SERIAL_C_BAUD_DEFAULT          OFF
#endif

// enable and customize WiFi/Ethernet functionality
// for other default IP settings see the file:
// src/lib/wifi/WifiManager.defaults.h

#ifndef MDNS_SERVER
#define MDNS_SERVER                    ON
#endif

#ifndef MDNS_NAME
#define MDNS_NAME                      HOST_NAME
#endif

#if ASCOM_ALPACA_SERVER == OFF
// optional Arduino Serial class work-alike IP channels 9996 to 9999 as a server (listens to clients)
// OFF or STANDARD (port 9999), or PERSISTENT (ports 9996 to 9998), or BOTH
#define SERIAL_SERVER                  BOTH
#else
#define SERIAL_SERVER                  OFF
#define WEB_HANDLER_COUNT_MAX          200        // for Ethernet webserver
#endif

// VIRTUAL SERIAL IP COMMAND CHANNELS

// in milliseconds
#ifndef WEATHER_SENSOR_SAMPLE_PERIOD
#define WEATHER_SENSOR_SAMPLE_PERIOD   5000       // recommended <= 30 seconds
#endif

#if DEBUG_CONNECT_CHECK == ON
#define CHECK_FAST                     3600.0
#else
#define CHECK_FAST                     1UL
#endif

// Relays
#ifndef RELAY1_DEFAULT_STATE
#define RELAY1_DEFAULT_STATE           OFF
#endif
#ifndef RELAY1_ON_STATE
#define RELAY1_ON_STATE                HIGH
#endif
#ifndef RELAY2_DEFAULT_STATE
#define RELAY2_DEFAULT_STATE           OFF
#endif
#ifndef RELAY2_ON_STATE
#define RELAY2_ON_STATE                HIGH
#endif
#ifndef RELAY3_DEFAULT_STATE
#define RELAY3_DEFAULT_STATE           OFF
#endif
#ifndef RELAY3_ON_STATE
#define RELAY3_ON_STATE                HIGH
#endif
#ifndef RELAY4_DEFAULT_STATE
#define RELAY4_DEFAULT_STATE           OFF
#endif
#ifndef RELAY4_ON_STATE
#define RELAY4_ON_STATE                HIGH
#endif
#ifndef RELAY5_DEFAULT_STATE
#define RELAY5_DEFAULT_STATE           OFF
#endif
#ifndef RELAY5_ON_STATE
#define RELAY5_ON_STATE                HIGH
#endif
#ifndef RELAY6_DEFAULT_STATE
#define RELAY6_DEFAULT_STATE           HIGH
#endif
#ifndef RELAY6_ON_STATE
#define RELAY6_ON_STATE                HIGH
#endif
#ifndef RELAY7_DEFAULT_STATE
#define RELAY7_DEFAULT_STATE           OFF
#endif
#ifndef RELAY7_ON_STATE
#define RELAY7_ON_STATE                HIGH
#endif
#ifndef RELAY8_DEFAULT_STATE
#define RELAY8_DEFAULT_STATE           OFF
#endif
#ifndef RELAY8_ON_STATE
#define RELAY8_ON_STATE                HIGH
#endif
#ifndef RELAY9_DEFAULT_STATE
#define RELAY9_DEFAULT_STATE           OFF
#endif
#ifndef RELAY9_ON_STATE
#define RELAY9_ON_STATE                HIGH
#endif
#ifndef RELAY10_DEFAULT_STATE
#define RELAY10_DEFAULT_STATE          OFF
#endif
#ifndef RELAY10_ON_STATE
#define RELAY10_ON_STATE               HIGH
#endif
#ifndef RELAY11_DEFAULT_STATE
#define RELAY11_DEFAULT_STATE          OFF
#endif
#ifndef RELAY11_ON_STATE
#define RELAY11_ON_STATE               HIGH
#endif
#ifndef RELAY12_DEFAULT_STATE
#define RELAY12_DEFAULT_STATE          OFF
#endif
#ifndef RELAY12_ON_STATE
#define RELAY12_ON_STATE               HIGH
#endif
#ifndef RELAY13_DEFAULT_STATE
#define RELAY13_DEFAULT_STATE          OFF
#endif
#ifndef RELAY13_ON_STATE
#define RELAY13_ON_STATE               HIGH
#endif
#ifndef RELAY14_DEFAULT_STATE
#define RELAY14_DEFAULT_STATE          OFF
#endif
#ifndef RELAY14_ON_STATE
#define RELAY14_ON_STATE               HIGH
#endif
#ifndef RELAY15_DEFAULT_STATE
#define RELAY15_DEFAULT_STATE          OFF
#endif
#ifndef RELAY15_ON_STATE
#define RELAY15_ON_STATE               HIGH
#endif
#ifndef RELAY16_DEFAULT_STATE
#define RELAY16_DEFAULT_STATE          OFF
#endif
#ifndef RELAY16_ON_STATE
#define RELAY16_ON_STATE               HIGH
#endif
#ifndef RELAY17_DEFAULT_STATE
#define RELAY17_DEFAULT_STATE          OFF
#endif
#ifndef RELAY17_ON_STATE
#define RELAY17_ON_STATE               HIGH
#endif
#ifndef RELAY18_DEFAULT_STATE
#define RELAY18_DEFAULT_STATE          OFF
#endif
#ifndef RELAY18_ON_STATE
#define RELAY18_ON_STATE               HIGH
#endif

// LED lighting (for FastLED library)
#ifndef LIGHT_STRIP_INIT
#define LIGHT_STRIP_INIT <WS2811, LIGHT_STRIP_DATA_PIN, BRG>
#endif

#ifndef LIGHT_STRIP_WHITE
#define LIGHT_STRIP_WHITE 0xFFFFFF
#endif

#ifndef LIGHT_STRIP_RED
#define LIGHT_STRIP_RED 0x800000
#endif

// Roof
#if ROOF_MOTOR_OPEN_RELAY == OFF || ROOF_MOTOR_OPEN_RELAY != ROOF_MOTOR_CLOSE_RELAY
  #define ROOF_SINGLE_OPEN_CLOSE_RELAY OFF
#endif

#if ROOF_MOTOR_OPEN_RELAY != OFF && ROOF_MOTOR_OPEN_RELAY == ROOF_MOTOR_CLOSE_RELAY
  #if ROOF_MOTOR_RELAY_MOMENTARY == ON
    #define ROOF_SINGLE_OPEN_CLOSE_RELAY ON
    #if ROOF_MOTOR_STOP_RELAY == ROOF_MOTOR_OPEN_RELAY
      #define ROOF_SINGLE_OPEN_CLOSE_STOP_RELAY ON
    #endif
  #endif
#endif

// Digital, optionally add: |HYST(n) Where n=0..1023 stability time in ms.
#ifndef SENSE1_ON_STATE
#define SENSE1_ON_STATE                LOW
#endif
#ifndef SENSE1_INIT
#define SENSE1_INIT                    INPUT_PULLUP
#endif
#ifndef SENSE2_ON_STATE
#define SENSE2_ON_STATE                LOW
#endif
#ifndef SENSE2_INIT
#define SENSE2_INIT                    INPUT_PULLUP
#endif
#ifndef SENSE3_ON_STATE
#define SENSE3_ON_STATE                LOW
#endif
#ifndef SENSE3_INIT
#define SENSE3_INIT                    INPUT_PULLUP
#endif
#ifndef SENSE4_ON_STATE
#define SENSE4_ON_STATE                LOW
#endif
#ifndef SENSE4_INIT
#define SENSE4_INIT                    INPUT_PULLUP
#endif
#ifndef SENSE5_ON_STATE
#define SENSE5_ON_STATE                LOW
#endif
#ifndef SENSE5_INIT
#define SENSE5_INIT                    INPUT_PULLUP
#endif
#ifndef SENSE6_ON_STATE
#define SENSE6_ON_STATE                LOW
#endif
#ifndef SENSE6_INIT
#define SENSE6_INIT                    INPUT_PULLUP
#endif
#ifndef SENSE7_ON_STATE
#define SENSE7_ON_STATE                LOW
#endif
#ifndef SENSE7_INIT
#define SENSE7_INIT                    INPUT_PULLUP
#endif
#ifndef SENSE8_ON_STATE
#define SENSE8_ON_STATE                LOW
#endif
#ifndef SENSE8_INIT
#define SENSE8_INIT                    INPUT_PULLUP
#endif

// -----------------------------------------------------------------------------------
// dome settings
#ifndef DOME
#define DOME                           OFF
#endif
#ifndef DOME_SHUTTER_LOCK
#define DOME_SHUTTER_LOCK              OFF
#endif
#ifndef DEFAULT_POWER_DOWN_TIME
#define DEFAULT_POWER_DOWN_TIME        30000                       // motor power down time, in milliseconds
#endif
#ifndef AXIS1_DRIVER_MODEL
#define AXIS1_DRIVER_MODEL             OFF                         // specify a driver to enable
#endif
#ifndef AXIS1_STEPS_PER_DEGREE
#define AXIS1_STEPS_PER_DEGREE         64.0
#endif
#ifndef AXIS1_REVERSE
#define AXIS1_REVERSE                  OFF
#endif
#ifndef AXIS1_POWER_DOWN
#define AXIS1_POWER_DOWN               OFF
#endif
#ifndef AXIS1_ENABLE_STATE
#define AXIS1_ENABLE_STATE             LOW
#endif
#ifndef AXIS1_SLEW_RATE_DESIRED
#define AXIS1_SLEW_RATE_DESIRED        5.0                         // in degrees/sec
#endif
#ifndef AXIS1_ACCELERATION_TIME
#define AXIS1_ACCELERATION_TIME        5                           // in seconds, to selected rate
#endif
#ifndef AXIS1_RAPID_STOP_TIME
#define AXIS1_RAPID_STOP_TIME          3                           // in seconds, to stop
#endif
#ifndef AXIS1_BACKLASH_RATE
#define AXIS1_BACKLASH_RATE            (AXIS1_SLEW_RATE_DESIRED/4) // in degrees/sec
#endif
#ifndef AXIS1_LIMIT_MIN
#define AXIS1_LIMIT_MIN                -180                        // in degrees
#endif
#ifndef AXIS1_LIMIT_MAX
#define AXIS1_LIMIT_MAX                180                         // in degrees
#endif
#ifndef AXIS1_SYNC_THRESHOLD
#define AXIS1_SYNC_THRESHOLD           OFF                         // sync threshold in counts (required for absolute encoders) or OFF
#endif
#ifndef AXIS1_SENSE_HOME
#define AXIS1_SENSE_HOME               OFF
#endif
#ifndef AXIS1_SENSE_HOME_INIT
#define AXIS1_SENSE_HOME_INIT          INPUT_PULLUP
#endif
#ifndef AXIS1_SENSE_HOME_DIST_LIMIT
#define AXIS1_SENSE_HOME_DIST_LIMIT    180.0                       // max distance in degrees
#endif
#ifndef AXIS1_SENSE_LIMIT_MIN
#define AXIS1_SENSE_LIMIT_MIN          OFF
#endif
#ifndef AXIS1_SENSE_LIMIT_MAX
#define AXIS1_SENSE_LIMIT_MAX          OFF
#endif
#ifndef AXIS1_SENSE_LIMIT_INIT
#define AXIS1_SENSE_LIMIT_INIT         INPUT_PULLUP
#endif
#if AXIS1_DRIVER_MODEL >= STEP_DIR_DRIVER_FIRST && AXIS1_DRIVER_MODEL <= STEP_DIR_DRIVER_LAST
  #define AXIS1_DRIVER_PRESENT
  #if AXIS1_DRIVER_MODEL >= TMC_DRIVER_FIRST
    #error "Config.h: TMC Drivers are not supported!"
  #else
    #define AXIS1_STEP_DIR_LEGACY
  #endif

  #ifndef AXIS1_STEP_STATE
  #define AXIS1_STEP_STATE             HIGH
  #endif
  #ifndef AXIS1_M2_ON_STATE
  #define AXIS1_M2_ON_STATE            HIGH
  #endif
  #ifndef AXIS1_DRIVER_MICROSTEPS
  #define AXIS1_DRIVER_MICROSTEPS      OFF
  #endif
  #ifndef AXIS1_DRIVER_MICROSTEPS_GOTO
  #define AXIS1_DRIVER_MICROSTEPS_GOTO OFF
  #endif
  #ifndef AXIS1_DRIVER_DECAY
  #define AXIS1_DRIVER_DECAY           OFF
  #endif
  #ifndef AXIS1_DRIVER_DECAY_GOTO
  #define AXIS1_DRIVER_DECAY_GOTO      OFF
  #endif
  #ifndef AXIS1_DRIVER_IHOLD
  #define AXIS1_DRIVER_IHOLD           OFF
  #endif
  #ifndef AXIS1_DRIVER_IRUN
  #define AXIS1_DRIVER_IRUN            OFF
  #endif
  #ifndef AXIS1_DRIVER_IGOTO
  #define AXIS1_DRIVER_IGOTO           OFF
  #endif
  #ifndef AXIS1_DRIVER_STATUS
  #define AXIS1_DRIVER_STATUS          OFF
  #endif
  #define AXIS1_PARAMETER1             AXIS1_DRIVER_MICROSTEPS
  #define AXIS1_PARAMETER2             AXIS1_DRIVER_MICROSTEPS_GOTO
  #define AXIS1_PARAMETER3             AXIS1_DRIVER_IHOLD
  #define AXIS1_PARAMETER4             AXIS1_DRIVER_IRUN
  #define AXIS1_PARAMETER5             AXIS1_DRIVER_IGOTO
  #define AXIS1_PARAMETER6             OFF
#endif
#if AXIS1_DRIVER_MODEL >= SERVO_DRIVER_FIRST
  #define AXIS1_SERVO_PRESENT

  #ifndef AXIS1_SERVO_VELOCITY_MAX
  #define AXIS1_SERVO_VELOCITY_MAX      100                       // max velocity, in % for DC, in steps/s for SERVO_TMC2209
  #endif
  #ifndef AXIS1_SERVO_VELOCITY_FACTOR
  #define AXIS1_SERVO_VELOCITY_FACTOR   frequency*0               // converts frequency (counts per second) to velocity (in steps per second or DC motor PWM ADU range)
  #endif
  #ifndef AXIS1_SERVO_ACCELERATION
  #define AXIS1_SERVO_ACCELERATION      20                        // acceleration, in %/s
  #endif
  #ifndef AXIS1_SERVO_FEEDBACK
  #define AXIS1_SERVO_FEEDBACK          FB_PID                    // type of feedback: FB_PID
  #endif

  #ifndef AXIS1_SERVO_FLTR
  #define AXIS1_SERVO_FLTR              OFF
  #endif

  #ifndef AXIS1_PID_P
  #define AXIS1_PID_P                  2.0
  #endif
  #ifndef AXIS1_PID_I
  #define AXIS1_PID_I                  5.0
  #endif
  #ifndef AXIS1_PID_D
  #define AXIS1_PID_D                  1.0
  #endif
  #ifndef AXIS1_PID_P_GOTO
  #define AXIS1_PID_P_GOTO             AXIS1_PID_P
  #endif
  #ifndef AXIS1_PID_I_GOTO
  #define AXIS1_PID_I_GOTO             AXIS1_PID_I
  #endif
  #ifndef AXIS1_PID_D_GOTO
  #define AXIS1_PID_D_GOTO             AXIS1_PID_D
  #endif
  #ifndef AXIS1_ENCODER
  #define AXIS1_ENCODER                AB
  #endif
  #ifndef AXIS1_ENCODER_ORIGIN
  #define AXIS1_ENCODER_ORIGIN         0
  #endif
  #ifndef AXIS1_ENCODER_REVERSE
  #define AXIS1_ENCODER_REVERSE        OFF
  #endif
  #ifndef AXIS1_SERVO_FEEDBACK
  #define AXIS1_SERVO_FEEDBACK         FB_PID
  #endif
  #ifndef AXIS1_SERVO_PH1_STATE
  #define AXIS1_SERVO_PH1_STATE        LOW
  #endif
  #ifndef AXIS1_SERVO_PH2_STATE
  #define AXIS1_SERVO_PH2_STATE        LOW
  #endif
  #define AXIS1_PARAMETER1             AXIS1_PID_P
  #define AXIS1_PARAMETER2             AXIS1_PID_I
  #define AXIS1_PARAMETER3             AXIS1_PID_D
  #define AXIS1_PARAMETER4             AXIS1_PID_P_GOTO
  #define AXIS1_PARAMETER5             AXIS1_PID_I_GOTO
  #define AXIS1_PARAMETER6             AXIS1_PID_D_GOTO
#endif

#ifndef AXIS2_DRIVER_MODEL
#define AXIS2_DRIVER_MODEL             OFF
#endif
#ifndef AXIS2_STEPS_PER_DEGREE
#define AXIS2_STEPS_PER_DEGREE         64.0
#endif
#ifndef AXIS2_REVERSE
#define AXIS2_REVERSE                  OFF
#endif
#ifndef AXIS2_POWER_DOWN
#define AXIS2_POWER_DOWN               OFF
#endif
#ifndef AXIS2_ENABLE_STATE
#define AXIS2_ENABLE_STATE             LOW
#endif
#ifndef AXIS2_SLEW_RATE_DESIRED
#define AXIS2_SLEW_RATE_DESIRED        5.0
#endif
#ifndef AXIS2_ACCELERATION_TIME
#define AXIS2_ACCELERATION_TIME        5
#endif
#ifndef AXIS2_RAPID_STOP_TIME
#define AXIS2_RAPID_STOP_TIME          3
#endif
#ifndef AXIS2_BACKLASH_RATE
#define AXIS2_BACKLASH_RATE            (AXIS2_SLEW_RATE_DESIRED/4)
#endif
#ifndef AXIS2_LIMIT_MIN
#define AXIS2_LIMIT_MIN                0
#endif
#ifndef AXIS2_LIMIT_MAX
#define AXIS2_LIMIT_MAX                90
#endif
#ifndef AXIS2_SENSE_HOME
#define AXIS2_SENSE_HOME               OFF
#endif
#ifndef AXIS2_SENSE_HOME_INIT
#define AXIS2_SENSE_HOME_INIT          INPUT_PULLUP
#endif
#ifndef AXIS2_SENSE_HOME_DIST_LIMIT
#define AXIS2_SENSE_HOME_DIST_LIMIT    90.0
#endif
#ifndef AXIS2_SENSE_LIMIT_MIN
#define AXIS2_SENSE_LIMIT_MIN          OFF
#endif
#ifndef AXIS2_SENSE_LIMIT_MAX
#define AXIS2_SENSE_LIMIT_MAX          OFF
#endif
#ifndef AXIS2_SYNC_THRESHOLD
#define AXIS2_SYNC_THRESHOLD          OFF
#endif
#ifndef AXIS2_SENSE_LIMIT_INIT
#define AXIS2_SENSE_LIMIT_INIT        INPUT_PULLUP
#endif
#if AXIS2_DRIVER_MODEL >= STEP_DIR_DRIVER_FIRST && AXIS2_DRIVER_MODEL <= STEP_DIR_DRIVER_LAST
  #define AXIS2_DRIVER_PRESENT
  #if AXIS2_DRIVER_MODEL >= TMC_DRIVER_FIRST
    #error "Config.h: TMC Drivers are not supported!"
  #else
    #define AXIS2_STEP_DIR_LEGACY
  #endif

  #ifndef AXIS2_STEP_STATE
  #define AXIS2_STEP_STATE             HIGH
  #endif
  #ifndef AXIS2_M2_ON_STATE
  #define AXIS2_M2_ON_STATE            HIGH
  #endif
  #ifndef AXIS2_DRIVER_MICROSTEPS
  #define AXIS2_DRIVER_MICROSTEPS      OFF
  #endif
  #ifndef AXIS2_DRIVER_MICROSTEPS_GOTO
  #define AXIS2_DRIVER_MICROSTEPS_GOTO OFF
  #endif
  #ifndef AXIS2_DRIVER_DECAY
  #define AXIS2_DRIVER_DECAY           OFF
  #endif
  #ifndef AXIS2_DRIVER_DECAY_GOTO
  #define AXIS2_DRIVER_DECAY_GOTO      OFF
  #endif
  #ifndef AXIS2_DRIVER_IHOLD
  #define AXIS2_DRIVER_IHOLD           OFF
  #endif
  #ifndef AXIS2_DRIVER_IRUN
  #define AXIS2_DRIVER_IRUN            OFF
  #endif
  #ifndef AXIS2_DRIVER_IGOTO
  #define AXIS2_DRIVER_IGOTO           OFF
  #endif
  #ifndef AXIS2_DRIVER_STATUS
  #define AXIS2_DRIVER_STATUS          OFF
  #endif
  #define AXIS2_PARAMETER1             AXIS2_DRIVER_MICROSTEPS
  #define AXIS2_PARAMETER2             AXIS2_DRIVER_MICROSTEPS_GOTO
  #define AXIS2_PARAMETER3             AXIS2_DRIVER_IHOLD
  #define AXIS2_PARAMETER4             AXIS2_DRIVER_IRUN
  #define AXIS2_PARAMETER5             AXIS2_DRIVER_IGOTO
  #define AXIS2_PARAMETER6             OFF
#endif
#if AXIS2_DRIVER_MODEL >= SERVO_DRIVER_FIRST
  #define AXIS2_SERVO_PRESENT

  #ifndef AXIS2_SERVO_VELOCITY_MAX
  #define AXIS2_SERVO_VELOCITY_MAX      100
  #endif
  #ifndef AXIS2_SERVO_VELOCITY_FACTOR
  #define AXIS2_SERVO_VELOCITY_FACTOR   frequency*0
  #endif
  #ifndef AXIS2_SERVO_ACCELERATION
  #define AXIS2_SERVO_ACCELERATION      20
  #endif
  #ifndef AXIS2_SERVO_FEEDBACK
  #define AXIS2_SERVO_FEEDBACK          FB_PID
  #endif

  #ifndef AXIS2_SERVO_FLTR
  #define AXIS2_SERVO_FLTR              OFF
  #endif

  #ifndef AXIS2_PID_P
  #define AXIS2_PID_P                   2.0
  #endif
  #ifndef AXIS2_PID_I
  #define AXIS2_PID_I                   5.0
  #endif
  #ifndef AXIS2_PID_D
  #define AXIS2_PID_D                   1.0
  #endif
  #ifndef AXIS2_PID_P_GOTO
  #define AXIS2_PID_P_GOTO              AXIS2_PID_P
  #endif
  #ifndef AXIS2_PID_I_GOTO
  #define AXIS2_PID_I_GOTO              AXIS2_PID_I
  #endif
  #ifndef AXIS2_PID_D_GOTO
  #define AXIS2_PID_D_GOTO              AXIS2_PID_D
  #endif
  #ifndef AXIS2_ENCODER
  #define AXIS2_ENCODER                 AB
  #endif
  #ifndef AXIS2_ENCODER_ORIGIN
  #define AXIS2_ENCODER_ORIGIN          0
  #endif
  #ifndef AXIS2_ENCODER_REVERSE
  #define AXIS2_ENCODER_REVERSE         OFF
  #endif
  #ifndef AXIS2_SERVO_FEEDBACK
  #define AXIS2_SERVO_FEEDBACK          FB_PID
  #endif
  #ifndef AXIS2_SERVO_PH1_STATE
  #define AXIS2_SERVO_PH1_STATE         LOW
  #endif
  #ifndef AXIS2_SERVO_PH2_STATE
  #define AXIS2_SERVO_PH2_STATE         LOW
  #endif
  #define AXIS2_PARAMETER1              AXIS2_PID_P
  #define AXIS2_PARAMETER2              AXIS2_PID_I
  #define AXIS2_PARAMETER3              AXIS2_PID_D
  #define AXIS2_PARAMETER4              AXIS2_PID_P_GOTO
  #define AXIS2_PARAMETER5              AXIS2_PID_I_GOTO
  #define AXIS2_PARAMETER6              AXIS2_PID_D_GOTO
#endif

#if defined(AXIS1_STEP_DIR_LEGACY) || defined(AXIS2_STEP_DIR_LEGACY)
  #define STEP_DIR_LEGACY_PRESENT
#endif

#if defined(STEP_DIR_LEGACY_PRESENT)
  #define STEP_DIR_MOTOR_PRESENT
#endif

// flag presence of servo motors
#if AXIS1_DRIVER_MODEL == SERVO_PE || AXIS1_DRIVER_MODEL == SERVO_EE || \
    AXIS2_DRIVER_MODEL == SERVO_PE || AXIS2_DRIVER_MODEL == SERVO_EE
  #define SERVO_DC_PRESENT
  #define SERVO_MOTOR_PRESENT
#endif

#if defined(STEP_DIR_MOTOR_PRESENT) || defined(SERVO_MOTOR_PRESENT)
  #define MOTOR_PRESENT
#endif
