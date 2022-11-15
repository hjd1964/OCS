// -------------------------------------------------------------------------------------------------
// Pin map for OCS4E hardware version 1 for the ESP32S2 SAOLA
#pragma once

#if defined(ESP32)

#define OPERATIONAL_MODE        WIFI

// Serial ports (see Pins.defaults.h for SERIAL_A)
// Serial0: RX Pin GPIO3, TX Pin GPIO1 (to USB serial adapter)
// Serial1: RX1 Pin GPIO23, TX1 Pin GPIO15

#if SERIAL_B_BAUD_DEFAULT != OFF
  #define SERIAL_B              Serial1
  #define SERIAL_B_RX           23
  #define SERIAL_B_TX           15
#endif

// Digital outputs for switching relays
#define RELAY1_PIN              4   // RE1
#define RELAY2_PIN              16  // RE2
#define RELAY3_PIN              17  // RE3
#define RELAY4_PIN              18  // RE4
#define RELAY5_PIN              19  // RE5
#define RELAY6_PIN              13  // RE6
#define RELAY7_PIN              12  // RE7
#define RELAY8_PIN              14  // RE8

// Digital inputs for sensing events
#define SENSE1_PIN              36  // DIN1
#define SENSE2_PIN              39  // DIN2
#define SENSE3_PIN              34  // DIN3
#define SENSE4_PIN              35  // ADIN1, shared analog or digital not both
#define SENSE5_PIN              32  // ADIN2, shared analog or digital not both
#define SENSE6_PIN              33  // ADIN3, shared analog or digital not both

// Analog inputs
#define ASENSE1_PIN             25  // AIN1 (ESD proteted, current limited)
#define ASENSE2_PIN             26  // AIN2 (ESD proteted, current limited)
#define ASENSE3_PIN             27  // AIN3 (ESD proteted, current limited)

#else
#error "Wrong processor for this configuration!"

#endif
