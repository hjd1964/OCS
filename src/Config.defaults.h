#pragma once

// serial ports
#ifndef SERIAL_A_BAUD_DEFAULT
#define SERIAL_A_BAUD_DEFAULT         9600
#endif
#ifndef SERIAL_B_BAUD_DEFAULT
#define SERIAL_B_BAUD_DEFAULT         OFF
#endif
#ifndef SERIAL_C_BAUD_DEFAULT
#define SERIAL_C_BAUD_DEFAULT         OFF
#endif

// enable IP functionality

// optional Arduino Serial class work-alike IP channels 9996 to 9999 as a server (listens to clients)
// OFF or STANDARD (port 9999), or PERSISTENT (ports 9996 to 9998), or BOTH
#define SERIAL_SERVER BOTH                       // for SERIAL_SIP, SERIAL_PIP1, etc.

// optional web-server
#define WEB_SERVER ON                            // for website at port 80
#define SD_CARD ON                               // enable the webserver SD_CARD support

// VIRTUAL SERIAL IP COMMAND CHANNELS

// in milliseconds
#ifndef WEATHER_SENSOR_SAMPLE_PERIOD
#define WEATHER_SENSOR_SAMPLE_PERIOD 5000
#endif

#if DEBUG_CONNECT_CHECK == ON
  #define CHECK_FAST 3600.0
#else
  #define CHECK_FAST 1UL
#endif

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

// Relays
#ifndef RELAY1_DEFAULT_STATE
#define RELAY1_DEFAULT_STATE OFF
#endif
#ifndef RELAY1_ACTIVE_STATE
#define RELAY1_ACTIVE_STATE HIGH
#endif
#ifndef RELAY2_DEFAULT_STATE
#define RELAY2_DEFAULT_STATE OFF
#endif
#ifndef RELAY2_ACTIVE_STATE
#define RELAY2_ACTIVE_STATE HIGH
#endif
#ifndef RELAY3_DEFAULT_STATE
#define RELAY3_DEFAULT_STATE OFF
#endif
#ifndef RELAY3_ACTIVE_STATE
#define RELAY3_ACTIVE_STATE HIGH
#endif
#ifndef RELAY4_DEFAULT_STATE
#define RELAY4_DEFAULT_STATE OFF
#endif
#ifndef RELAY4_ACTIVE_STATE
#define RELAY4_ACTIVE_STATE HIGH
#endif
#ifndef RELAY5_DEFAULT_STATE
#define RELAY5_DEFAULT_STATE OFF
#endif
#ifndef RELAY5_ACTIVE_STATE
#define RELAY5_ACTIVE_STATE HIGH
#endif
#ifndef RELAY6_DEFAULT_STATE
#define RELAY6_DEFAULT_STATE HIGH
#endif
#ifndef RELAY6_ACTIVE_STATE
#define RELAY6_ACTIVE_STATE HIGH
#endif
#ifndef RELAY7_DEFAULT_STATE
#define RELAY7_DEFAULT_STATE OFF
#endif
#ifndef RELAY7_ACTIVE_STATE
#define RELAY7_ACTIVE_STATE HIGH
#endif
#ifndef RELAY8_DEFAULT_STATE
#define RELAY8_DEFAULT_STATE OFF
#endif
#ifndef RELAY8_ACTIVE_STATE
#define RELAY8_ACTIVE_STATE HIGH
#endif
#ifndef RELAY9_DEFAULT_STATE
#define RELAY9_DEFAULT_STATE OFF
#endif
#ifndef RELAY9_ACTIVE_STATE
#define RELAY9_ACTIVE_STATE HIGH
#endif
#ifndef RELAY10_DEFAULT_STATE
#define RELAY10_DEFAULT_STATE OFF
#endif
#ifndef RELAY10_ACTIVE_STATE
#define RELAY10_ACTIVE_STATE HIGH
#endif
#ifndef RELAY11_DEFAULT_STATE
#define RELAY11_DEFAULT_STATE OFF
#endif
#ifndef RELAY11_ACTIVE_STATE
#define RELAY11_ACTIVE_STATE HIGH
#endif
#ifndef RELAY12_DEFAULT_STATE
#define RELAY12_DEFAULT_STATE OFF
#endif
#ifndef RELAY12_ACTIVE_STATE
#define RELAY12_ACTIVE_STATE HIGH
#endif
#ifndef RELAY13_DEFAULT_STATE
#define RELAY13_DEFAULT_STATE OFF
#endif
#ifndef RELAY13_ACTIVE_STATE
#define RELAY13_ACTIVE_STATE HIGH
#endif
#ifndef RELAY14_DEFAULT_STATE
#define RELAY14_DEFAULT_STATE OFF
#endif
#ifndef RELAY14_ACTIVE_STATE
#define RELAY14_ACTIVE_STATE HIGH
#endif
#ifndef RELAY15_DEFAULT_STATE
#define RELAY15_DEFAULT_STATE OFF
#endif
#ifndef RELAY15_ACTIVE_STATE
#define RELAY15_ACTIVE_STATE HIGH
#endif
#ifndef RELAY16_DEFAULT_STATE
#define RELAY16_DEFAULT_STATE OFF
#endif
#ifndef RELAY16_ACTIVE_STATE
#define RELAY16_ACTIVE_STATE HIGH
#endif
#ifndef RELAY17_DEFAULT_STATE
#define RELAY17_DEFAULT_STATE OFF
#endif
#ifndef RELAY17_ACTIVE_STATE
#define RELAY17_ACTIVE_STATE HIGH
#endif
#ifndef RELAY18_DEFAULT_STATE
#define RELAY18_DEFAULT_STATE OFF
#endif
#ifndef RELAY18_ACTIVE_STATE
#define RELAY18_ACTIVE_STATE HIGH
#endif

// Digital, optionally add: |HYST(n) Where n=0..1023 stability time in ms.
#ifndef SENSE1_ON_STATE
#define SENSE1_ON_STATE LOW
#endif
#ifndef SENSE1_INIT_STATE
#define SENSE1_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE2_ON_STATE
#define SENSE2_ON_STATE LOW
#endif
#ifndef SENSE2_INIT_STATE
#define SENSE2_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE3_ON_STATE
#define SENSE3_ON_STATE LOW
#endif
#ifndef SENSE3_INIT_STATE
#define SENSE3_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE4_ON_STATE
#define SENSE4_ON_STATE LOW
#endif
#ifndef SENSE4_INIT_STATE
#define SENSE4_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE5_ON_STATE
#define SENSE5_ON_STATE LOW
#endif
#ifndef SENSE5_INIT_STATE
#define SENSE5_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE6_ON_STATE
#define SENSE6_ON_STATE LOW
#endif
#ifndef SENSE6_INIT_STATE
#define SENSE6_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE7_ON_STATE
#define SENSE7_ON_STATE LOW
#endif
#ifndef SENSE7_INIT_STATE
#define SENSE7_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE8_ON_STATE
#define SENSE8_ON_STATE LOW
#endif
#ifndef SENSE8_INIT_STATE
#define SENSE8_INIT_STATE INPUT_PULLUP
#endif

// use the HAL specified default NV driver
#ifndef NV_DRIVER
  #define NV_DRIVER NV_DEFAULT
#endif

// -----------------------------------------------------------------------------------
// dome settings
#ifndef DOME_DRIVER_MODEL
#define DOME_DRIVER_MODEL             OFF                         // specify a driver to enable
#endif
#ifndef DOME_STEPS_PER_DEGREE
#define DOME_STEPS_PER_DEGREE         64.0
#endif
#ifndef DOME_REVERSE
#define DOME_REVERSE                  OFF
#endif
#ifndef DOME_POWER_DOWN
#define DOME_POWER_DOWN               OFF
#endif
#ifndef DOME_ENABLE_STATE
#define DOME_ENABLE_STATE             LOW
#endif
#ifndef DOME_SLEW_RATE_DESIRED
#define DOME_SLEW_RATE_DESIRED        3.0                         // in degrees/sec
#endif
#ifndef DOME_ACCELERATION_TIME
#define DOME_ACCELERATION_TIME        2                           // in seconds, to selected rate
#endif
#ifndef DOME_RAPID_STOP_TIME
#define DOME_RAPID_STOP_TIME          1                           // in seconds, to stop
#endif
#ifndef DOME_BACKLASH_RATE
#define DOME_BACKLASH_RATE            (DOME_SLEW_RATE_DESIRED/4) // in degrees/sec
#endif
#ifndef DOME_LIMIT_MIN
#define DOME_LIMIT_MIN                -180                        // in degrees
#endif
#ifndef DOME_LIMIT_MAX
#define DOME_LIMIT_MAX                180                         // in degrees
#endif
#ifndef DOME_SENSE_HOME
#define DOME_SENSE_HOME               OFF
#endif
#ifndef DOME_SENSE_HOME_INIT
#define DOME_SENSE_HOME_INIT          INPUT_PULLUP
#endif
#ifndef DOME_SENSE_LIMIT_MIN
#define DOME_SENSE_LIMIT_MIN          OFF
#endif
#ifndef DOME_SENSE_LIMIT_MAX
#define DOME_SENSE_LIMIT_MAX          OFF
#endif
#ifndef DOME_SENSE_LIMIT_INIT
#define DOME_SENSE_LIMIT_INIT         INPUT_PULLUP
#endif
#if DOME_DRIVER_MODEL >= DRIVER_FIRST && DOME_DRIVER_MODEL <= DRIVER_LAST
  #define DOME_DRIVER_PRESENT
  #if DOME_DRIVER_MODEL == TMC2130 || DOME_DRIVER_MODEL == TMC5160
  #define DOME_DRIVER_TMC_SPI
  #endif
  #ifndef DOME_STEP_STATE
  #define DOME_STEP_STATE               HIGH
  #endif
  #ifndef DOME_DRIVER_MICROSTEPS
  #define DOME_DRIVER_MICROSTEPS        OFF
  #endif
  #ifndef DOME_DRIVER_MICROSTEPS_GOTO
  #define DOME_DRIVER_MICROSTEPS_GOTO   OFF
  #endif
  #ifndef DOME_DRIVER_DECAY
  #define DOME_DRIVER_DECAY             OFF
  #endif
  #ifndef DOME_DRIVER_DECAY_GOTO
  #define DOME_DRIVER_DECAY_GOTO        OFF
  #endif
  #ifndef DOME_DRIVER_IHOLD
  #define DOME_DRIVER_IHOLD             OFF
  #endif
  #ifndef DOME_DRIVER_IRUN
  #define DOME_DRIVER_IRUN              OFF
  #endif
  #ifndef DOME_DRIVER_IGOTO
  #define DOME_DRIVER_IGOTO             OFF
  #endif
  #ifndef DOME_DRIVER_STATUS
  #define DOME_DRIVER_STATUS            OFF
  #endif
  #define DOME_PARAMETER1               DOME_DRIVER_MICROSTEPS
  #define DOME_PARAMETER2               DOME_DRIVER_MICROSTEPS_GOTO
  #define DOME_PARAMETER3               DOME_DRIVER_IHOLD
  #define DOME_PARAMETER4               DOME_DRIVER_IRUN
  #define DOME_PARAMETER5               DOME_DRIVER_IGOTO
  #define DOME_PARAMETER6               OFF
#endif
#if DOME_DRIVER_MODEL >= SERVO_DRIVER_FIRST
  #define DOME_SERVO_PRESENT
  #ifndef DOME_SERVO_P
  #define DOME_SERVO_P                  2.0
  #endif
  #ifndef DOME_SERVO_I
  #define DOME_SERVO_I                  5.0
  #endif
  #ifndef DOME_SERVO_D
  #define DOME_SERVO_D                  1.0
  #endif
  #ifndef DOME_SERVO_P_GOTO
  #define DOME_SERVO_P_GOTO             DOME_SERVO_P
  #endif
  #ifndef DOME_SERVO_I_GOTO
  #define DOME_SERVO_I_GOTO             DOME_SERVO_I
  #endif
  #ifndef DOME_SERVO_D_GOTO
  #define DOME_SERVO_D_GOTO             DOME_SERVO_D
  #endif
  #ifndef DOME_SERVO_ENCODER
  #define DOME_SERVO_ENCODER            ENC_AB
  #endif
  #ifndef DOME_SERVO_ENCODER_TRIGGER
  #define DOME_SERVO_ENCODER_TRIGGER    CHANGE
  #endif
  #ifndef DOME_SERVO_FEEDBACK
  #define DOME_SERVO_FEEDBACK           FB_PID
  #endif
  #ifndef DOME_SERVO_PH1_STATE
  #define DOME_SERVO_PH1_STATE          LOW
  #endif
  #ifndef DOME_SERVO_PH2_STATE
  #define DOME_SERVO_PH2_STATE          LOW
  #endif
  #define DOME_PARAMETER1               DOME_SERVO_P
  #define DOME_PARAMETER2               DOME_SERVO_I
  #define DOME_PARAMETER3               DOME_SERVO_D
  #define DOME_PARAMETER4               DOME_SERVO_P_GOTO
  #define DOME_PARAMETER5               DOME_SERVO_I_GOTO
  #define DOME_PARAMETER6               DOME_SERVO_D_GOTO
#endif

#if defined(DOME_DRIVER_PRESENT)
  #define STEP_DIR_MOTOR_PRESENT
#endif

#if defined(DOME_DRIVER_TMC_SPI)
  #define TMC_DRIVER_PRESENT
#endif

#if defined(DOME_SERVO_PRESENT)
  #define SERVO_MOTOR_PRESENT
#endif

#if defined(SERVO_MOTOR_PRESENT) || defined(STEP_DIR_MOTOR_PRESENT)
  #define MOTOR_PRESENT
#endif
