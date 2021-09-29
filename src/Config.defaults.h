#pragma once

// serial ports
#ifndef SERIAL_A_BAUD_DEFAULT
#define SERIAL_A_BAUD_DEFAULT         9600
#endif
#ifndef SERIAL_B_BAUD_DEFAULT
#define SERIAL_B_BAUD_DEFAULT         OFF
#endif
#ifndef SERIAL_B_ESP_FLASHING
#define SERIAL_B_ESP_FLASHING         OFF
#endif
#ifndef SERIAL_C_BAUD_DEFAULT
#define SERIAL_C_BAUD_DEFAULT         OFF
#endif

// ESP32 VIRTUAL SERIAL IP COMMAND CHANNEL (EXPERIMENTAL)
#ifndef SERIAL_IP_MODE
#define SERIAL_IP_MODE                 OFF //         OFF, Use ACCESS_POINT or STATION to enable the interface (ESP32 only.)
#endif

#ifndef STANDARD_COMMAND_CHANNEL
#define STANDARD_COMMAND_CHANNEL       ON //          ON, Wifi command channel for simultanious connections on port 9999.
#endif
#ifndef PERSISTENT_COMMAND_CHANNEL
#define PERSISTENT_COMMAND_CHANNEL     ON //          ON, Wifi command channel for a single connection on port 9998.
#endif

#ifndef AP_SSID
#define AP_SSID                 "ONSTEPX" //   "ONSTEPX", Wifi Access Point SSID.
#define AP_PASSWORD            "password" //  "password", Wifi Access Point password.
#define AP_CHANNEL                      7 //           7, Wifi Access Point channel.
#define AP_IP_ADDR          (192,168,0,1) // ..,168,0,1), Wifi Access Point IP Address.
#define AP_GW_ADDR          (192,168,0,1) // ..,168,0,1), Wifi Access Point GATEWAY Address.
#define AP_SN_MASK        (255,255,255,0) // ..55,255,0), Wifi Access Point SUBNET Mask.
#endif

#ifndef STA_SSID
#define STA_SSID                   "Home" //      "Home", Wifi Station SSID to connnect to.
#define STA_PASSWORD           "password" //  "password", Wifi Station mode password.
#define STA_IP_ADDR        (192,168,1,55) // ..168,1,55), Wifi Station IP Address.
#define STA_GW_ADDR         (192,168,1,1) // ..,168,1,1), Wifi Station GATEWAY Address.
#define STA_SN_MASK       (255,255,255,0) // ..55,255,0), Wifi Station SUBNET Mask.
#endif

// in milliseconds
#ifndef WEATHER_SENSOR_SAMPLE_PERIOD
#define WEATHER_SENSOR_SAMPLE_PERIOD 5000
#endif

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
#define RELAY6_DEFAULT_STATE OFF
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

#ifndef SENSE1_ON_STATE
#define SENSE1_ON_STATE HIGH
#endif
#ifndef SENSE1_INIT_STATE
#define SENSE1_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE2_ON_STATE
#define SENSE2_ON_STATE HIGH
#endif
#ifndef SENSE2_INIT_STATE
#define SENSE2_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE3_ON_STATE
#define SENSE3_ON_STATE HIGH
#endif
#ifndef SENSE3_INIT_STATE
#define SENSE3_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE4_ON_STATE
#define SENSE4_ON_STATE HIGH
#endif
#ifndef SENSE4_INIT_STATE
#define SENSE4_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE5_ON_STATE
#define SENSE5_ON_STATE HIGH
#endif
#ifndef SENSE5_INIT_STATE
#define SENSE5_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE6_ON_STATE
#define SENSE6_ON_STATE HIGH
#endif
#ifndef SENSE6_INIT_STATE
#define SENSE6_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE7_ON_STATE
#define SENSE7_ON_STATE HIGH
#endif
#ifndef SENSE7_INIT_STATE
#define SENSE7_INIT_STATE INPUT_PULLUP
#endif
#ifndef SENSE8_ON_STATE
#define SENSE8_ON_STATE HIGH
#endif
#ifndef SENSE8_INIT_STATE
#define SENSE8_INIT_STATE INPUT_PULLUP
#endif
