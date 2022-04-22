// -------------------------------------------------------------------------------------------------
// Null pin map, assigns OFF to all values not already assigned
#pragma once

// SerialA command channel is manidatory
#ifndef SERIAL_A
#define SERIAL_A                    Serial
#endif

// SerialB, SerialC command channels don't exist by default

// Hardware SPI interface pins
#ifndef SDCARD_CS_PIN
  #define SDCARD_CS_PIN             OFF
#endif

#if WEATHER_CHARTS == ON && SDCARD_CS_PIN != OFF
  #define SD_CARD ON
#endif

#ifndef AUX_CS_PIN
  #define AUX_CS_PIN                OFF
#endif

#ifndef DS3234_CS_PIN
  #define DS3234_CS_PIN             AUX_CS_PIN
#endif

#ifndef BMx280_CS_PIN
  #define BMx280_CS_PIN             AUX_CS_PIN
#endif

#ifndef ETHERNET_CS_PIN
  #define ETHERNET_CS_PIN           OFF
#endif

#ifndef ETHERNET_RESET_PIN
  #define ETHERNET_RESET_PIN       OFF
#endif

// Dome control
#ifndef AXIS1_ENABLE_PIN
#define AXIS1_ENABLE_PIN            OFF
#endif
#ifndef AXIS1_M0_PIN
#define AXIS1_M0_PIN                OFF
#endif
#ifndef AXIS1_M1_PIN
#define AXIS1_M1_PIN                OFF
#endif
#ifndef AXIS1_M2_PIN
#define AXIS1_M2_PIN                OFF
#endif
#ifndef AXIS1_M3_PIN
#define AXIS1_M3_PIN                OFF
#endif
#ifndef AXIS1_STEP_PIN
#define AXIS1_STEP_PIN              OFF
#endif
#ifndef AXIS1_DIR_PIN
#define AXIS1_DIR_PIN               OFF
#endif
#ifndef AXIS1_DECAY_PIN
#define AXIS1_DECAY_PIN             OFF
#endif
#ifndef AXIS1_SERVO_PH1_PIN
#define AXIS1_SERVO_PH1_PIN         OFF
#endif
#ifndef AXIS1_SERVO_PH2_PIN
#define AXIS1_SERVO_PH2_PIN         OFF
#endif
#ifndef AXIS1_SERVO_ENC1_PIN
#define AXIS1_SERVO_ENC1_PIN        OFF
#endif
#ifndef AXIS1_SERVO_ENC2_PIN
#define AXIS1_SERVO_ENC2_PIN        OFF
#endif
#ifndef AXIS1_FAULT_PIN
#define AXIS1_FAULT_PIN             OFF
#endif
#ifndef AXIS1_SENSE_HOME_PIN
#define AXIS1_SENSE_HOME_PIN        OFF
#endif
#ifndef AXIS1_SENSE_LIMIT_MIN_PIN
#define AXIS1_SENSE_LIMIT_MIN_PIN   OFF
#endif
#ifndef AXIS1_SENSE_LIMIT_MAX_PIN
#define AXIS1_SENSE_LIMIT_MAX_PIN   OFF
#endif

#ifndef AXIS2_ENABLE_PIN
#define AXIS2_ENABLE_PIN            OFF
#endif
#ifndef AXIS2_M0_PIN
#define AXIS2_M0_PIN                OFF
#endif
#ifndef AXIS2_M1_PIN
#define AXIS2_M1_PIN                OFF
#endif
#ifndef AXIS2_M2_PIN
#define AXIS2_M2_PIN                OFF
#endif
#ifndef AXIS2_M3_PIN
#define AXIS2_M3_PIN                OFF
#endif
#ifndef AXIS2_STEP_PIN
#define AXIS2_STEP_PIN              OFF
#endif
#ifndef AXIS2_DIR_PIN
#define AXIS2_DIR_PIN               OFF
#endif
#ifndef AXIS2_DECAY_PIN
#define AXIS2_DECAY_PIN             OFF
#endif
#ifndef AXIS2_SERVO_PH1_PIN
#define AXIS2_SERVO_PH1_PIN         OFF
#endif
#ifndef AXIS2_SERVO_PH2_PIN
#define AXIS2_SERVO_PH2_PIN         OFF
#endif
#ifndef AXIS2_SERVO_ENC1_PIN
#define AXIS2_SERVO_ENC1_PIN        OFF
#endif
#ifndef AXIS2_SERVO_ENC2_PIN
#define AXIS2_SERVO_ENC2_PIN        OFF
#endif
#ifndef AXIS2_FAULT_PIN
#define AXIS2_FAULT_PIN             OFF
#endif
#ifndef AXIS2_SENSE_HOME_PIN
#define AXIS2_SENSE_HOME_PIN        OFF
#endif
#ifndef AXIS2_SENSE_LIMIT_MIN_PIN
#define AXIS2_SENSE_LIMIT_MIN_PIN   OFF
#endif
#ifndef AXIS2_SENSE_LIMIT_MAX_PIN
#define AXIS2_SENSE_LIMIT_MAX_PIN   OFF
#endif

// Digital outputs for switching relays
#ifndef RELAY1_PIN
#define RELAY1_PIN                  OFF
#endif
#ifndef RELAY2_PIN
#define RELAY2_PIN                  OFF
#endif
#ifndef RELAY3_PIN
#define RELAY3_PIN                  OFF
#endif
#ifndef RELAY4_PIN
#define RELAY4_PIN                  OFF
#endif
#ifndef RELAY5_PIN
#define RELAY5_PIN                  OFF
#endif
#ifndef RELAY6_PIN
#define RELAY6_PIN                  OFF
#endif
#ifndef RELAY7_PIN
#define RELAY7_PIN                  OFF
#endif
#ifndef RELAY8_PIN
#define RELAY8_PIN                  OFF
#endif
#ifndef RELAY9_PIN
#define RELAY9_PIN                  OFF
#endif
#ifndef RELAY10_PIN
#define RELAY10_PIN                 OFF
#endif
#ifndef RELAY11_PIN
#define RELAY11_PIN                 OFF
#endif
#ifndef RELAY12_PIN
#define RELAY12_PIN                 OFF
#endif
#ifndef RELAY13_PIN
#define RELAY13_PIN                 OFF
#endif
#ifndef RELAY14_PIN
#define RELAY14_PIN                 OFF
#endif
#ifndef RELAY15_PIN
#define RELAY15_PIN                 OFF
#endif
#ifndef RELAY16_PIN
#define RELAY16_PIN                 OFF
#endif
#ifndef RELAY17_PIN
#define RELAY17_PIN                 OFF
#endif
#ifndef RELAY18_PIN
#define RELAY18_PIN                 OFF
#endif

// Digital inputs for sensing events
#ifndef SENSE1_PIN
#define SENSE1_PIN                  OFF
#endif
#ifndef SENSE2_PIN
#define SENSE2_PIN                  OFF
#endif
#ifndef SENSE3_PIN
#define SENSE3_PIN                  OFF
#endif
#ifndef SENSE4_PIN
#define SENSE4_PIN                  OFF
#endif
#ifndef SENSE5_PIN
#define SENSE5_PIN                  OFF
#endif
#ifndef SENSE6_PIN
#define SENSE6_PIN                  OFF
#endif
#ifndef SENSE7_PIN
#define SENSE7_PIN                  OFF
#endif
#ifndef SENSE8_PIN
#define SENSE8_PIN                  OFF
#endif

// Analog inputs
#ifndef ASENSE1_PIN
#define ASENSE1_PIN                 OFF
#endif
#ifndef ASENSE2_PIN
#define ASENSE2_PIN                 OFF
#endif
#ifndef ASENSE3_PIN
#define ASENSE3_PIN                 OFF
#endif
#ifndef ASENSE4_PIN
#define ASENSE4_PIN                 OFF
#endif
#ifndef ASENSE5_PIN
#define ASENSE5_PIN                 OFF
#endif
#ifndef ASENSE6_PIN
#define ASENSE6_PIN                 OFF
#endif
#ifndef ASENSE7_PIN
#define ASENSE7_PIN                 OFF
#endif
#ifndef ASENSE8_PIN
#define ASENSE8_PIN                 OFF
#endif
#ifndef ASENSE9_PIN
#define ASENSE9_PIN                 OFF
#endif
#ifndef ASENSE10_PIN
#define ASENSE10_PIN                OFF
#endif
#ifndef ASENSE11_PIN
#define ASENSE11_PIN                OFF
#endif
#ifndef ASENSE12_PIN
#define ASENSE12_PIN                OFF
#endif
#ifndef ASENSE13_PIN
#define ASENSE13_PIN                OFF
#endif
#ifndef ASENSE14_PIN
#define ASENSE14_PIN                OFF
#endif
#ifndef ASENSE15_PIN
#define ASENSE15_PIN                OFF
#endif
#ifndef ASENSE16_PIN
#define ASENSE16_PIN                OFF
#endif
