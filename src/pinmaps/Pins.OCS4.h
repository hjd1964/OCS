// -------------------------------------------------------------------------------------------------
// Pin map for OCS hardware version 4 using the Teensy3.5, 3.6, or 4.1
#pragma once

#if defined(ARDUINO_TEENSY41) || defined(__MK66FX1M0__) || defined(__MK64FX512__)

#ifndef OPERATIONAL_MODE
  #define OPERATIONAL_MODE      ETHERNET_W5500
#endif

// Serial ports (see Pins.defaults.h for SERIAL_A)
// Serial1: RX1 Pin 0, TX1 Pin 1
// Serial2: RX2 Pin 7, TX2 Pin 8 (Teensy3.5/3.6)
// Serial3: RX3 Pin 7, TX3 Pin 8 (Teensy4.1)

#if SERIAL_B_BAUD_DEFAULT != OFF
  #define SERIAL_B              Serial1
#endif
#if SERIAL_C_BAUD_DEFAULT != OFF
  #if defined(ARDUINO_TEENSY41)
    #define SERIAL_C            Serial3
  #else
    #define SERIAL_C            Serial2
  #endif
#endif
#if defined(USB_DUAL_SERIAL) || defined(USB_TRIPLE_SERIAL)
  #define SERIAL_D              SerialUSB1
  #define SERIAL_D_BAUD_DEFAULT 9600
#endif
#if defined(USB_TRIPLE_SERIAL)
  #define SERIAL_E              SerialUSB2
  #define SERIAL_E_BAUD_DEFAULT 9600
#endif

// Activates feature and allows the OCS to force a reset of the Ethernet adapter
// using this pin.  Required for the W5500 we use on this board.
#ifndef ETHERNET_RESET_PIN
  #define ETHERNET_RESET_PIN    6
#endif

// Hardware SPI interface is on pins 11, 12, 13
#ifndef ETHERNET_CS_PIN
  #define ETHERNET_CS_PIN       10
#endif
#ifndef SDCARD_CS_PIN
  #define SDCARD_CS_PIN         OFF
#endif
#ifndef DS3234_CS_PIN
  #define DS3234_CS_PIN         9   // Default CS Pin for DS3234 on SPI
#endif
#ifndef BMx280_CS_PIN
  #define BMx280_CS_PIN         9   // Default CS Pin for BME280 or BMP280 on SPI
#endif

// Digital outputs for switching relays
#define RELAY1_PIN              24  // RE1, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY2_PIN              25  // RE2, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY3_PIN              26  // RE3, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY4_PIN              27  // RE4, SSR with 12V out option (32VAC/VDC 2A*)
#define RELAY5_PIN              28  // RE5, SSR with 12V out option (32VAC/VDC 2A*)
                                    // * = 3A total combined for built-in 12V option
#define RELAY6_PIN              29  // RE6, high current n-channel power MOSFET (30VDC 30A)
#define RELAY7_PIN              30  // RE7, high current n-channel power MOSFET (30VDC 30A)
#define RELAY8_PIN              31  // RE8, mechanical relay (110/220VAC 16A)
#define RELAY9_PIN              32  // RE9, mechanical relay (110/220VAC 16A)
#define RELAY10_PIN             33  // RE10, mechanical relay (110/220VAC 16A)
#define RELAY11_PIN             34  // RE11, mechanical relay (110/220VAC 16A)
#define RELAY12_PIN             35  // RE12, mechanical relay (110/220VAC 16A)
#define RELAY13_PIN             36  // RE13, optional 4-channel ebay relay board
#define RELAY14_PIN             37  // RE14, optional 4-channel ebay relay board
#define RELAY15_PIN             38  // RE15, optional 4-channel ebay relay board
#define RELAY16_PIN             39  // RE16, optional 4-channel ebay relay board
#if defined(ARDUINO_TEENSY41)
  #define RELAY17_PIN           40  // RE17, on aux header
  #define RELAY18_PIN           41  // RE18, on aux header
#else
  #define RELAY17_PIN DAC_PIN(A21)  // RE17, on aux header
  #define RELAY18_PIN DAC_PIN(A22)  // RE18, on aux header
#endif

// Digital inputs for sensing events
#define SENSE1_PIN              2   // DIN1 (ESD protected, current limited, with pullup to 3.3V)
#define SENSE2_PIN              3   // DIN2 (ESD protected, current limited, with pullup to 3.3V)
#define SENSE3_PIN              4   // DIN3 (ESD protected, current limited, with pullup to 3.3V)
#define SENSE4_PIN              5   // DIN4 (ESD protected, current limited, with pullup to 3.3V)
#define SENSE5_PIN              20  // ADIN1, shared analog or digital not both (current limited)
#define SENSE6_PIN              21  // ADIN2, shared analog or digital not both (current limited)
#define SENSE7_PIN              22  // ADIN3, shared analog or digital not both (ESD protected, current limited)
#define SENSE8_PIN              23  // ADIN4, shared analog or digital not both (ESD protected, current limited)

// Analog inputs
#define ASENSE1_PIN             14  // AIN1 (ESD protected, current limited)
#define ASENSE2_PIN             15  // AIN2 (ESD protected, current limited)
#define ASENSE3_PIN             16  // AIN3 (ESD protected, current limited)
#define ASENSE4_PIN             17  // AIN4 (ESD protected, current limited)
#define ASENSE5_PIN             20  // ADIN1, shared analog or digital not both (current limited)
#define ASENSE6_PIN             21  // ADIN2, shared analog or digital not both (current limited)
#define ASENSE7_PIN             22  // ADIN3, shared analog or digital not both (ESD protected, current limited)
#define ASENSE8_PIN             23  // ADIN4, shared analog or digital not both (ESD protected, current limited)

#else
#error "Wrong processor for this configuration!"

#endif
