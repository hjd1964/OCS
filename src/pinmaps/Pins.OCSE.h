// -------------------------------------------------------------------------------------------------
// Pin map for the ESP32-S DevKitC
#pragma once

#if defined(ESP32)

#define OPERATIONAL_MODE        WIFI

// Serial ports (see Pins.defaults.h for SERIAL_A)
// Serial0: RX Pin GPIO3, TX Pin GPIO1 (to USB serial adapter)
// Serial1: RX1 Pin GPIO23, TX1 Pin GPIO15
// I2C: SDA Pin GPIO21, SCL Pin GPIO22

#if SERIAL_B_BAUD_DEFAULT != OFF
  #define SERIAL_B              Serial1
  #define SERIAL_B_RX           23
  #define SERIAL_B_TX           15
#endif

// Digital outputs for switching relays
#define RELAY1_PIN              4   // RE1, mechanical relay (110/220VAC 16A)
#define RELAY2_PIN              16  // RE2, mechanical relay (110/220VAC 16A)
#define RELAY3_PIN              17  // RE3, mechanical relay (110/220VAC 16A)
#define RELAY4_PIN              18  // RE4, mechanical relay (110/220VAC 16A)
#define RELAY5_PIN              19  // RE5, mechanical relay (110/220VAC 16A)
#define RELAY6_PIN              13  // RE6, high current n-channel power MOSFET (30VDC 30A)
#define RELAY7_PIN              12  // RE7, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY8_PIN              14  // RE8, SSR with 12V out option (32VAC/VDC 2A*)  [pwm at boot]
#define RELAY9_PIN              2   // RE9, SSR with 12V out option (32VAC/VDC 2A*)  [must float or be LOW at boot]
#define RELAY10_PIN             5   // RE10, SSR with 12V out option (32VAC/VDC 2A*) [must be logic HIGH at boot]
                                    // * = 3A total combined for built-in 12V option

// Digital inputs for sensing events
#define SENSE1_PIN              25  // DIN1 (ESD proteted, current limited, with pullup to 3.3V)
#define SENSE2_PIN              26  // DIN2 (ESD proteted, current limited, with pullup to 3.3V)
#define SENSE3_PIN              27  // DIN3 (ESD proteted, current limited, with pullup to 3.3V)
#define SENSE4_PIN              35  // ADIN1, shared analog or digital not both (ESD protected, current limited)
#define SENSE5_PIN              32  // ADIN2, shared analog or digital not both (ESD protected, current limited)
#define SENSE6_PIN              33  // ADIN3, shared analog or digital not both (ESD protected, current limited)

// Analog inputs
#define ASENSE1_PIN             36  // AIN1 analog (ESD proteted, current limited)
#define ASENSE2_PIN             39  // AIN2 analog (ESD proteted, current limited)
#define ASENSE3_PIN             34  // AIN3 analog (ESD proteted, current limited)
#define ASENSE4_PIN             35  // ADIN1, shared analog or digital not both (ESD protected, current limited)
#define ASENSE5_PIN             32  // ADIN2, shared analog or digital not both (ESD protected, current limited)
#define ASENSE6_PIN             33  // ADIN3, shared analog or digital not both (ESD protected, current limited)

#else
#error "Wrong processor for this configuration!"

#endif
