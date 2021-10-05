// -------------------------------------------------------------------------------------------------
// Pin map for OCS running on 3.6
#pragma once

#if defined(__MK66FX1M0__)

// Serial ports (see Pins.defaults.h for SERIAL_A)
// Serial1: RX1 Pin 0, TX1 Pin 1
// Serial2: RX2 Pin 7, TX2 Pin 8

#if SERIAL_B_BAUD_DEFAULT != OFF
  #define SERIAL_B              Serial1
#endif
#if SERIAL_C_BAUD_DEFAULT != OFF
  #define SERIAL_C              Serial2
#endif
#if defined(USB_DUAL_SERIAL) || defined(USB_TRIPLE_SERIAL)
  #define SERIAL_D              SerialUSB1
  #define SERIAL_D_BAUD_DEFAULT 9600
#endif
#if defined(USB_TRIPLE_SERIAL)
  #define SERIAL_E              SerialUSB2
  #define SERIAL_E_BAUD_DEFAULT 9600
#endif

#define DAC_AS_DIGITAL                          // turn on support for using DACs to output digital signals using Arduino standard commands

// Hardware SPI interface is on pins 11, 12, 13
#ifndef SDCARD_CS_PIN
  #define SDCARD_CS_PIN         OFF
#endif
#ifndef ETHERNET_CS_PIN
  #define ETHERNET_CS_PIN       10
#endif
#ifndef DS3234_CS_PIN
  #define DS3234_CS_PIN         9               // Default CS Pin for DS3234 on SPI
#endif
#ifndef BMx280_CS_PIN
  #define BMx280_CS_PIN         9               // Default CS Pin for BME280 or BMP280 on SPI
#endif

// Ethernet Adapter reset pin
#if ETHERNET_RESET_PIN != OFF
  #if ETHERNET_RESET_PIN != 6
    #error "The Teensy3.6 supports the W5500 Ethernet only and ETHERNET_RESET_PIN must be OFF or 6 only"
  #endif
#endif
#define ETH_RESET_PIN           6

// Digital outputs for switching relays
#define RELAY1_PIN             24
#define RELAY2_PIN             25
#define RELAY3_PIN             26
#define RELAY4_PIN             27
#define RELAY5_PIN             28
#define RELAY6_PIN             29
#define RELAY7_PIN             30
#define RELAY8_PIN             31
#define RELAY9_PIN             32
#define RELAY10_PIN            33
#define RELAY11_PIN            34
#define RELAY12_PIN            35
#define RELAY13_PIN            36
#define RELAY14_PIN            37
#define RELAY15_PIN            38
#define RELAY16_PIN            39
#define RELAY17_PIN            A21
#define RELAY18_PIN            A22

// Digital inputs for sensing events
#define SENSE1_PIN              2
#define SENSE2_PIN              3
#define SENSE3_PIN              4
#define SENSE4_PIN              5
#define SENSE5_PIN              20  // shared, general purpose 1
#define SENSE6_PIN              21  // shared, general purpose 2
#define SENSE7_PIN              22  // shared, general purpose 3
#define SENSE8_PIN              23  // shared, general purpose 4

// Analog inputs
#define ASENSE1_PIN            14
#define ASENSE2_PIN            15
#define ASENSE3_PIN            16
#define ASENSE4_PIN            17
#define ASENSE5_PIN            20  // shared, general purpose 1
#define ASENSE6_PIN            21  // shared, general purpose 2
#define ASENSE7_PIN            22  // shared, general purpose 3
#define ASENSE8_PIN            23  // shared, general purpose 4
#define ASENSE9_PIN            OFF
#define ASENSE10_PIN           OFF
#define ASENSE11_PIN           OFF
#define ASENSE12_PIN           OFF
#define ASENSE13_PIN           OFF
#define ASENSE14_PIN           OFF
#define ASENSE15_PIN           OFF
#define ASENSE16_PIN           OFF

#else
#error "Wrong processor for this configuration!"

#endif
