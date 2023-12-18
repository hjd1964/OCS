// -------------------------------------------------------------------------------------------------
// Pin map for the ESP32-S2 DevKitM-1
#pragma once

#if defined(ESP32)

#define OPERATIONAL_MODE        WIFI

// Serial ports (see Pins.defaults.h for SERIAL_A)
// Serial0: RX Pin GPIO44, TX Pin GPIO43 (to USB serial adapter)
// Serial1: RX1 Pin GPIO18, TX1 Pin GPIO17
// I2C: SDA Pin GPIO8, SCL Pin GPIO9

#if SERIAL_B_BAUD_DEFAULT != OFF
  #define SERIAL_B              Serial1
#endif

// Digital outputs for switching relays
#define RELAY1_PIN              15  // RE1, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY2_PIN              16  // RE2, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY3_PIN              19  // RE3, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY4_PIN              20  // RE4, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY5_PIN              21  // RE5, SSR with 12V out option (32VAC/VDC 2A*)
                                    // * = 3A total combined for built-in 12V option
#define RELAY6_PIN              26  // RE6, high current n-channel power MOSFET (30VDC 30A)
#define RELAY7_PIN              33  // RE7, high current n-channel power MOSFET (30VDC 30A)
#define RELAY8_PIN              34  // RE8, mechanical relay (110/220VAC 16A)
#define RELAY9_PIN              35  // RE9, mechanical relay (110/220VAC 16A)
#define RELAY10_PIN             36  // RE10, mechanical relay (110/220VAC 16A)
#define RELAY11_PIN             37  // RE11, mechanical relay (110/220VAC 16A)
#define RELAY12_PIN             38  // RE12, mechanical relay (110/220VAC 16A)
#define RELAY13_PIN             39  // RE13, optional 4-channel ebay relay board
#define RELAY14_PIN             40  // RE14, optional 4-channel ebay relay board
#define RELAY15_PIN             41  // RE15, optional 4-channel ebay relay board
#define RELAY16_PIN             42  // RE16, optional 4-channel ebay relay board

// Digital inputs for sensing events
#define SENSE1_PIN              11  // DIN1 (ESD proteted, current limited, with pullup to 3.3V)
#define SENSE2_PIN              12  // DIN2 (ESD proteted, current limited, with pullup to 3.3V)
#define SENSE3_PIN              13  // DIN3 (ESD proteted, current limited, with pullup to 3.3V)
#define SENSE4_PIN              14  // DIN4 (ESD proteted, current limited, with pullup to 3.3V)
#define SENSE5_PIN               5  // ADIN1, shared analog or digital not both (ESD protected, current limited)
#define SENSE6_PIN               6  // ADIN2, shared analog or digital not both (ESD protected, current limited)
#define SENSE7_PIN               7  // ADIN3, shared analog or digital not both (ESD protected, current limited)
#define SENSE8_PIN              10  // ADIN4, shared analog or digital not both (ESD protected, current limited)

// Analog inputs
#define ASENSE1_PIN              1  // AIN1 (ESD proteted, current limited)
#define ASENSE2_PIN              2  // AIN2 (ESD proteted, current limited)
#define ASENSE3_PIN              3  // AIN3 (ESD proteted, current limited)
#define ASENSE4_PIN              4  // AIN4 (ESD proteted, current limited)
#define ASENSE5_PIN              5  // ADIN1, shared analog or digital not both (ESD protected, current limited)
#define ASENSE6_PIN              6  // ADIN2, shared analog or digital not both (ESD protected, current limited)
#define ASENSE7_PIN              7  // ADIN3, shared analog or digital not both (ESD protected, current limited)
#define ASENSE8_PIN             10  // ADIN4, shared analog or digital not both (ESD protected, current limited)

#else
#error "Wrong processor for this configuration!"

#endif
