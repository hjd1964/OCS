#pragma once

// use the HAL specified default NV driver
#ifndef NV_DRIVER
#define NV_DRIVER                     NV_DEFAULT
#endif

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
#define SERIAL_SERVER                 STANDARD

// optional web-server
#define WEB_SERVER                    ON         // for website at port 80
#define SD_CARD                       ON         // enable the webserver SD_CARD support

// VIRTUAL SERIAL IP COMMAND CHANNELS

// in milliseconds
#ifndef WEATHER_SENSOR_SAMPLE_PERIOD
#define WEATHER_SENSOR_SAMPLE_PERIOD  5000
#endif

#if DEBUG_CONNECT_CHECK == ON
  #define CHECK_FAST                  3600.0
#else
  #define CHECK_FAST                  1UL
#endif

// Relays
#ifndef RELAY1_DEFAULT_STATE
#define RELAY1_DEFAULT_STATE          OFF
#endif
#ifndef RELAY1_ACTIVE_STATE
#define RELAY1_ACTIVE_STATE           HIGH
#endif
#ifndef RELAY2_DEFAULT_STATE
#define RELAY2_DEFAULT_STATE          OFF
#endif
#ifndef RELAY2_ACTIVE_STATE
#define RELAY2_ACTIVE_STATE           HIGH
#endif
#ifndef RELAY3_DEFAULT_STATE
#define RELAY3_DEFAULT_STATE          OFF
#endif
#ifndef RELAY3_ACTIVE_STATE
#define RELAY3_ACTIVE_STATE           HIGH
#endif
#ifndef RELAY4_DEFAULT_STATE
#define RELAY4_DEFAULT_STATE          OFF
#endif
#ifndef RELAY4_ACTIVE_STATE
#define RELAY4_ACTIVE_STATE           HIGH
#endif
#ifndef RELAY5_DEFAULT_STATE
#define RELAY5_DEFAULT_STATE          OFF
#endif
#ifndef RELAY5_ACTIVE_STATE
#define RELAY5_ACTIVE_STATE           HIGH
#endif
#ifndef RELAY6_DEFAULT_STATE
#define RELAY6_DEFAULT_STATE          HIGH
#endif
#ifndef RELAY6_ACTIVE_STATE
#define RELAY6_ACTIVE_STATE           HIGH
#endif
#ifndef RELAY7_DEFAULT_STATE
#define RELAY7_DEFAULT_STATE          OFF
#endif
#ifndef RELAY7_ACTIVE_STATE
#define RELAY7_ACTIVE_STATE           HIGH
#endif
#ifndef RELAY8_DEFAULT_STATE
#define RELAY8_DEFAULT_STATE          OFF
#endif
#ifndef RELAY8_ACTIVE_STATE
#define RELAY8_ACTIVE_STATE           HIGH
#endif
#ifndef RELAY9_DEFAULT_STATE
#define RELAY9_DEFAULT_STATE          OFF
#endif
#ifndef RELAY9_ACTIVE_STATE
#define RELAY9_ACTIVE_STATE           HIGH
#endif
#ifndef RELAY10_DEFAULT_STATE
#define RELAY10_DEFAULT_STATE         OFF
#endif
#ifndef RELAY10_ACTIVE_STATE
#define RELAY10_ACTIVE_STATE          HIGH
#endif
#ifndef RELAY11_DEFAULT_STATE
#define RELAY11_DEFAULT_STATE         OFF
#endif
#ifndef RELAY11_ACTIVE_STATE
#define RELAY11_ACTIVE_STATE          HIGH
#endif
#ifndef RELAY12_DEFAULT_STATE
#define RELAY12_DEFAULT_STATE         OFF
#endif
#ifndef RELAY12_ACTIVE_STATE
#define RELAY12_ACTIVE_STATE          HIGH
#endif
#ifndef RELAY13_DEFAULT_STATE
#define RELAY13_DEFAULT_STATE         OFF
#endif
#ifndef RELAY13_ACTIVE_STATE
#define RELAY13_ACTIVE_STATE          HIGH
#endif
#ifndef RELAY14_DEFAULT_STATE
#define RELAY14_DEFAULT_STATE         OFF
#endif
#ifndef RELAY14_ACTIVE_STATE
#define RELAY14_ACTIVE_STATE          HIGH
#endif
#ifndef RELAY15_DEFAULT_STATE
#define RELAY15_DEFAULT_STATE         OFF
#endif
#ifndef RELAY15_ACTIVE_STATE
#define RELAY15_ACTIVE_STATE          HIGH
#endif
#ifndef RELAY16_DEFAULT_STATE
#define RELAY16_DEFAULT_STATE         OFF
#endif
#ifndef RELAY16_ACTIVE_STATE
#define RELAY16_ACTIVE_STATE          HIGH
#endif
#ifndef RELAY17_DEFAULT_STATE
#define RELAY17_DEFAULT_STATE         OFF
#endif
#ifndef RELAY17_ACTIVE_STATE
#define RELAY17_ACTIVE_STATE          HIGH
#endif
#ifndef RELAY18_DEFAULT_STATE
#define RELAY18_DEFAULT_STATE         OFF
#endif
#ifndef RELAY18_ACTIVE_STATE
#define RELAY18_ACTIVE_STATE          HIGH
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

// Digital, optionally add: |HYST(n) Where n=0..1023 stability time in ms.
#ifndef SENSE1_ON_STATE
#define SENSE1_ON_STATE               LOW
#endif
#ifndef SENSE1_INIT_STATE
#define SENSE1_INIT_STATE             INPUT_PULLUP
#endif
#ifndef SENSE2_ON_STATE
#define SENSE2_ON_STATE               LOW
#endif
#ifndef SENSE2_INIT_STATE
#define SENSE2_INIT_STATE             INPUT_PULLUP
#endif
#ifndef SENSE3_ON_STATE
#define SENSE3_ON_STATE               LOW
#endif
#ifndef SENSE3_INIT_STATE
#define SENSE3_INIT_STATE             INPUT_PULLUP
#endif
#ifndef SENSE4_ON_STATE
#define SENSE4_ON_STATE               LOW
#endif
#ifndef SENSE4_INIT_STATE
#define SENSE4_INIT_STATE             INPUT_PULLUP
#endif
#ifndef SENSE5_ON_STATE
#define SENSE5_ON_STATE               LOW
#endif
#ifndef SENSE5_INIT_STATE
#define SENSE5_INIT_STATE             INPUT_PULLUP
#endif
#ifndef SENSE6_ON_STATE
#define SENSE6_ON_STATE               LOW
#endif
#ifndef SENSE6_INIT_STATE
#define SENSE6_INIT_STATE             INPUT_PULLUP
#endif
#ifndef SENSE7_ON_STATE
#define SENSE7_ON_STATE               LOW
#endif
#ifndef SENSE7_INIT_STATE
#define SENSE7_INIT_STATE             INPUT_PULLUP
#endif
#ifndef SENSE8_ON_STATE
#define SENSE8_ON_STATE               LOW
#endif
#ifndef SENSE8_INIT_STATE
#define SENSE8_INIT_STATE             INPUT_PULLUP
#endif

// -----------------------------------------------------------------------------------
// dome settings
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
#ifndef AXIS1_SENSE_HOME
#define AXIS1_SENSE_HOME               OFF
#endif
#ifndef AXIS1_SENSE_HOME_INIT
#define AXIS1_SENSE_HOME_INIT          INPUT_PULLUP
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
#if AXIS1_DRIVER_MODEL >= DRIVER_FIRST && AXIS1_DRIVER_MODEL <= DRIVER_LAST
  #define AXIS1_DRIVER_PRESENT
  #if AXIS1_DRIVER_MODEL == TMC2130 || AXIS1_DRIVER_MODEL == TMC5160
  #define AXIS1_DRIVER_TMC_SPI
  #endif
  #ifndef AXIS1_STEP_STATE
  #define AXIS1_STEP_STATE             HIGH
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
  #ifndef AXIS1_SERVO_P
  #define AXIS1_SERVO_P                2.0
  #endif
  #ifndef AXIS1_SERVO_I
  #define AXIS1_SERVO_I                5.0
  #endif
  #ifndef AXIS1_SERVO_D
  #define AXIS1_SERVO_D                1.0
  #endif
  #ifndef AXIS1_SERVO_P_GOTO
  #define AXIS1_SERVO_P_GOTO           AXIS1_SERVO_P
  #endif
  #ifndef AXIS1_SERVO_I_GOTO
  #define AXIS1_SERVO_I_GOTO           AXIS1_SERVO_I
  #endif
  #ifndef AXIS1_SERVO_D_GOTO
  #define AXIS1_SERVO_D_GOTO           AXIS1_SERVO_D
  #endif
  #ifndef AXIS1_SERVO_ENCODER
  #define AXIS1_SERVO_ENCODER          ENC_AB
  #endif
  #ifndef AXIS1_SERVO_ENCODER_TRIGGER
  #define AXIS1_SERVO_ENCODER_TRIGGER  CHANGE
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
  #define AXIS1_PARAMETER1             AXIS1_SERVO_P
  #define AXIS1_PARAMETER2             AXIS1_SERVO_I
  #define AXIS1_PARAMETER3             AXIS1_SERVO_D
  #define AXIS1_PARAMETER4             AXIS1_SERVO_P_GOTO
  #define AXIS1_PARAMETER5             AXIS1_SERVO_I_GOTO
  #define AXIS1_PARAMETER6             AXIS1_SERVO_D_GOTO
#endif

#ifndef AXIS2_DRIVER_MODEL
#define AXIS2_DRIVER_MODEL             OFF                         // specify a driver to enable
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
#define AXIS2_SLEW_RATE_DESIRED        5.0                         // in degrees/sec
#endif
#ifndef AXIS2_ACCELERATION_TIME
#define AXIS2_ACCELERATION_TIME        5                           // in seconds, to selected rate
#endif
#ifndef AXIS2_RAPID_STOP_TIME
#define AXIS2_RAPID_STOP_TIME          3                           // in seconds, to stop
#endif
#ifndef AXIS2_BACKLASH_RATE
#define AXIS2_BACKLASH_RATE            (AXIS2_SLEW_RATE_DESIRED/4) // in degrees/sec
#endif
#ifndef AXIS2_LIMIT_MIN
#define AXIS2_LIMIT_MIN                0                           // in degrees
#endif
#ifndef AXIS2_LIMIT_MAX
#define AXIS2_LIMIT_MAX                90                          // in degrees
#endif
#ifndef AXIS2_SENSE_HOME
#define AXIS2_SENSE_HOME               OFF
#endif
#ifndef AXIS2_SENSE_HOME_INIT
#define AXIS2_SENSE_HOME_INIT          INPUT_PULLUP
#endif
#ifndef AXIS2_SENSE_LIMIT_MIN
#define AXIS2_SENSE_LIMIT_MIN          OFF
#endif
#ifndef AXIS2_SENSE_LIMIT_MAX
#define AXIS2_SENSE_LIMIT_MAX          OFF
#endif
#ifndef AXIS2_SENSE_LIMIT_INIT
#define AXIS2_SENSE_LIMIT_INIT         INPUT_PULLUP
#endif
#if AXIS2_DRIVER_MODEL >= DRIVER_FIRST && AXIS2_DRIVER_MODEL <= DRIVER_LAST
  #define AXIS2_DRIVER_PRESENT
  #if AXIS2_DRIVER_MODEL == TMC2130 || AXIS2_DRIVER_MODEL == TMC5160
  #define AXIS2_DRIVER_TMC_SPI
  #endif
  #ifndef AXIS2_STEP_STATE
  #define AXIS2_STEP_STATE             HIGH
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
  #ifndef AXIS2_SERVO_P
  #define AXIS2_SERVO_P                2.0
  #endif
  #ifndef AXIS2_SERVO_I
  #define AXIS2_SERVO_I                5.0
  #endif
  #ifndef AXIS2_SERVO_D
  #define AXIS2_SERVO_D                1.0
  #endif
  #ifndef AXIS2_SERVO_P_GOTO
  #define AXIS2_SERVO_P_GOTO           AXIS2_SERVO_P
  #endif
  #ifndef AXIS2_SERVO_I_GOTO
  #define AXIS2_SERVO_I_GOTO           AXIS2_SERVO_I
  #endif
  #ifndef AXIS2_SERVO_D_GOTO
  #define AXIS2_SERVO_D_GOTO           AXIS2_SERVO_D
  #endif
  #ifndef AXIS2_SERVO_ENCODER
  #define AXIS2_SERVO_ENCODER          ENC_AB
  #endif
  #ifndef AXIS2_SERVO_ENCODER_TRIGGER
  #define AXIS2_SERVO_ENCODER_TRIGGER  CHANGE
  #endif
  #ifndef AXIS2_SERVO_FEEDBACK
  #define AXIS2_SERVO_FEEDBACK         FB_PID
  #endif
  #ifndef AXIS2_SERVO_PH1_STATE
  #define AXIS2_SERVO_PH1_STATE        LOW
  #endif
  #ifndef AXIS2_SERVO_PH2_STATE
  #define AXIS2_SERVO_PH2_STATE        LOW
  #endif
  #define AXIS2_PARAMETER1             AXIS2_SERVO_P
  #define AXIS2_PARAMETER2             AXIS2_SERVO_I
  #define AXIS2_PARAMETER3             AXIS2_SERVO_D
  #define AXIS2_PARAMETER4             AXIS2_SERVO_P_GOTO
  #define AXIS2_PARAMETER5             AXIS2_SERVO_I_GOTO
  #define AXIS2_PARAMETER6             AXIS2_SERVO_D_GOTO
#endif

#if defined(AXIS1_DRIVER_PRESENT) || defined(AXIS2_DRIVER_PRESENT)
  #define STEP_DIR_MOTOR_PRESENT
#endif

#if defined(AXIS1_DRIVER_TMC_SPI) || defined(AXIS2_DRIVER_TMC_SPI)
  #define TMC_DRIVER_PRESENT
#endif

#if defined(AXIS1_SERVO_PRESENT) || defined(AXIS2_SERVO_PRESENT)
  #define SERVO_MOTOR_PRESENT
#endif

#if defined(SERVO_MOTOR_PRESENT) || defined(STEP_DIR_MOTOR_PRESENT)
  #define MOTOR_PRESENT
#endif
