// -------------------------------------------------------------------------------------------------
// Pin map for OCS hardware 1 or 2 using the Mega1280 or Mega2560
#pragma once

#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)

#define OPERATIONAL_MODE       ETHERNET_W5100

// Serial ports (see Pins.defaults.h for SERIAL_A)
// Serial0: RX Pin 0, TX Pin 1 (to USB serial adapter)
// Serial1: RX1 Pin 19, TX1 Pin 17
// Serial2: RX2 Pin 17, TX2 Pin 16

#if SERIAL_B_BAUD_DEFAULT != OFF
  #define SERIAL_B             Serial1
#endif
#if SERIAL_C_BAUD_DEFAULT != OFF
  #define SERIAL_C             Serial2
#endif

// Activates feature and allows the OCS to force a reset of the Ethernet adapter
// using this pin.  For a W5100 be sure its reset pin is only connected to the pin specified here!
#ifndef ETHERNET_RESET_PIN
  #define ETHERNET_RESET_PIN   OFF
#endif

// Hardware SPI interface pins 50, 51, 52
#ifndef ETHERNET_CS_PIN
  #define ETHERNET_CS_PIN      10
#endif
#ifndef SDCARD_CS_PIN
  #define SDCARD_CS_PIN        4
#endif
#ifndef DS3234_CS_PIN
  #define DS3234_CS_PIN        53               // Default CS Pin for DS3234 on SPI
#endif
#ifndef BMx280_CS_PIN
  #define BMx280_CS_PIN        49               // Default CS Pin for BME280 or BMP280 on SPI
#endif

// Digital outputs for switching relays
#define RELAY1_PIN             23
#define RELAY2_PIN             25
#define RELAY3_PIN             27
#define RELAY4_PIN             29
#define RELAY5_PIN             31
#define RELAY6_PIN             33
#define RELAY7_PIN             35
#define RELAY8_PIN             37
#define RELAY9_PIN             39
#define RELAY10_PIN            41
#define RELAY11_PIN            43
#define RELAY12_PIN            45
#define RELAY13_PIN            47
#define RELAY14_PIN            49

// Digital inputs for sensing events
#define SENSE1_PIN             22
#define SENSE2_PIN             24
#define SENSE3_PIN             26
#define SENSE4_PIN             28
#define SENSE5_PIN             30
#define SENSE6_PIN             32
#define SENSE7_PIN             34
#define SENSE8_PIN             36

// Analog inputs
#define ASENSE1_PIN            A0
#define ASENSE2_PIN            A1
#define ASENSE3_PIN            A2
#define ASENSE4_PIN            A3
#define ASENSE5_PIN            A4
#define ASENSE6_PIN            A5
#define ASENSE7_PIN            A6
#define ASENSE8_PIN            A7
#define ASENSE9_PIN            A8
#define ASENSE10_PIN           A9
#define ASENSE11_PIN           A10
#define ASENSE12_PIN           A11
#define ASENSE13_PIN           A12
#define ASENSE14_PIN           A13
#define ASENSE15_PIN           A14
#define ASENSE16_PIN           A15

#else
#error "Wrong processor for this configuration!"

#endif
