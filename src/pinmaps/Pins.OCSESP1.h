// -------------------------------------------------------------------------------------------------
// Pin map for OCSESP hardware version 1 using the ESP32
#pragma once

#if defined(ESP32)

#define OPERATIONAL_MODE        WIFI

// Serial ports (see Pins.defaults.h for SERIAL_A)
// Serial0: RX Pin GPIO3, TX Pin GPIO1 (to USB serial adapter)
// Serial1: RX1 Pin GPIO10, TX1 Pin GPIO9 (on SPI Flash pins, must be moved to be used)
// Serial2: RX2 Pin GPIO16, TX2 Pin GPIO17

#if SERIAL_B_BAUD_DEFAULT != OFF
  #define SERIAL_B              Serial1
  #define SERIAL_B_RX           23
  #define SERIAL_B_TX           15
#endif

// Digital outputs for switching relays
#define RELAY1_PIN              4   // RE1, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY2_PIN              16  // RE2, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY3_PIN              17  // RE3, SSR with 12V out option (32VAC/VDC 2A*)
                                    // * = 3A total combined for built-in 12V option
#define RELAY4_PIN              18  // RE6, high current n-channel power MOSFET (30VDC 30A)
#define RELAY5_PIN              19  // RE8, mechanical relay (110/220VAC 16A)
#define RELAY6_PIN              13  // RE9, mechanical relay (110/220VAC 16A)
#define RELAY7_PIN              12  // RE10, mechanical relay (110/220VAC 16A)
#define RELAY8_PIN              14  // RE11, mechanical relay (110/220VAC 16A)

// Digital inputs for sensing events
#define SENSE1_PIN              36  // DIN1 (ESD proteted, current limited, with pullup to 3.3V)
#define SENSE2_PIN              39  // DIN2 (ESD proteted, current limited, with pullup to 3.3V)
#define SENSE3_PIN              34  // DIN3 (ESD proteted, current limited, with pullup to 3.3V)
#define SENSE4_PIN              35  // ADIN1, shared analog or digital not both (current limited)
#define SENSE5_PIN              32  // ADIN2, shared analog or digital not both (current limited)
#define SENSE6_PIN              33  // ADIN3, shared analog or digital not both (ESD protected, current limited)

// Analog inputs
#define ASENSE1_PIN             25  // AIN1 (ESD proteted, current limited)
#define ASENSE2_PIN             26  // AIN2 (ESD proteted, current limited)
#define ASENSE3_PIN             27  // AIN3 (ESD proteted, current limited)
#define ASENSE4_PIN             35  // ADIN1, shared analog or digital not both
#define ASENSE5_PIN             32  // ADIN2, shared analog or digital not both
#define ASENSE6_PIN             33  // ADIN3, shared analog or digital not both

#else
#error "Wrong processor for this configuration!"

#endif
