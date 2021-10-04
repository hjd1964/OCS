// ---------------------------------------------------------------------------------------------------------------------------------
// Extended configuration for OnStep SmartWebServer infrequently used options

//                                 *** Most users will not change anything in this file! ***

// ---------------------------------------------------------------------------------------------------------------------------------
// ADJUST THE FOLLOWING TO CONFIGURE YOUR CONTROLLER FEATURES ----------------------------------------------------------------------
// <-Req'd = always must set, <-Often = usually must set, Option = optional, Adjust = adjust as req'd, Infreq = infrequently changed

// DEBUG ------------------------------------------------------------ see https://onstep.groups.io/g/main/wiki/6-Configuration#DEBUG
// Enable additional debugging and/or status messages on the specified SERIAL_DEBUG port
// Note that the SERIAL_DEBUG port cannot be used for normal communication with OnStep
#define DEBUG                         OFF //    OFF, Use ON for background error messages only, use VERBOSE for all           Infreq
                                          //         error and status messages, use CONSOLE for VT100 debug console,
                                          //         or use PROFILER for VT100 task profiler.

#define DEBUG_ECHO_COMMANDS           OFF //    OFF, Use ON to log command/responses to the debug serial port.                Option
#define DEBUG_CONNECT_CHECK           OFF //    OFF, ON to enable debug code for connection checks.                           Infreq
#define DEBUG_SD                      OFF //    OFF, ON to enable debug code for the SD card support.                         Infreq
#define DEBUG_WEBSERVER               OFF //    OFF, ON to enable debug code for the webserver.                               Infreq
#define DEBUG_CMDSERVER               OFF //    OFF, ON to enable debug code for the command server on port 9999.             Infreq

#define SERIAL_DEBUG               Serial // Serial, Use any h/w serial port. Serial1 or Serial2, etc. as supported.          Option
#define SERIAL_DEBUG_BAUD            9600 //   9600, n. Where n=9600,19200,57600,115200 (common baud rates.)                  Option


// SERIAL PORT COMMAND CHANNELS ------------------------------------ see https://onstep.groups.io/g/main/wiki/6-Configuration#SERIAL
#define SERIAL_A_BAUD_DEFAULT        9600 //   9600, n. Where n=9600,19200,57600,115200 (common baud rates.)                  Infreq

// NETWORK SETTINGS ----------------------------------------------------------------------------------------------------------------
#define OPERATIONAL_MODE   ETHERNET_W5100 // ..5100, Default ETHERNET_W5100 or ETHERNET_W5500.                               <-Req'd

#define RESPONSE_INTERVAL            1000 //   1000, n. Where n=500..10000 (ms.) Default for LAN latency, Internet use 5000.  Option

#define ETHERNET_RESET_PIN            OFF //    OFF, n. Where n is an unused pin, activates feature and allows the OCS to     Option
                                          //         force a reset of the Ethernet adapter using this pin.  For a W5100 be
                                          //         sure its reset pin is only connected to the pin specified here!

#define CONNECTION_CHECK_HOURS        OFF //    OFF, n. Where n=1 to 48 (hours.)  Connection check time.                      Option

// IP ADDRESS SETTINGS -------------------------------------------------------------------------------------------------------------
// These settings are stored in NV (EEPROM) and will not revert to the defaults once first set from the values below unless
// NV is wiped, these settings (where applicable) can be changed at runtime however.

// The unique MAC address for your OCS
#define MAC {0xDE,0xAD,0xBE,0xEF,0xFE,0xEF}

#define TIME_IP_ADDR       (216,239,35,0) // ..35.0, time.google.com (216.239.35.0) or time-a.timefreq.bldrdoc.gov at         Option
                                          //         132.163.4.101, 132.163.4.102, 132.163.4.103, etc.
#define CHECK_IP_ADDR    (100,24,172,113) //
                                          //         default is arduino.cc.  Needs ETHERNET_RESET_PIN and/or WATCHDOG to reset.

#define AP_ENABLED                   true //        true, Wifi Access Point Enabled.                                          Adjust
#define AP_SSID                     "OCS" //       "OCS", Wifi Access Point SSID.                                             Adjust
#define AP_PASSWORD            "password" //  "password", Wifi Access Point password.                                         Adjust
#define AP_CHANNEL                      7 //           7, Wifi Access Point channel.                                          Adjust
#define AP_IP_ADDR          (192,168,0,1) // ..,168,0,1), Wifi Access Point IP Address.                                       Adjust
#define AP_GW_ADDR          (192,168,0,1) // ..,168,0,1), Wifi Access Point GATEWAY Address.                                  Adjust
#define AP_SN_MASK        (255,255,255,0) // ..55,255,0), Wifi Access Point SUBNET Mask.                                      Adjust

#define STA_ENABLED                 false //       false, Wifi Station Enabled.                                               Adjust
#define STA_SSID                   "Home" //      "Home", Wifi Station SSID to connnect to.                                   Adjust
#define STA_PASSWORD           "password" //  "password", Wifi Station mode password.                                         Adjust
#define STA_DHCP_ENABLED            false //       false, Ethernet/Wifi Station DHCP Enabled.                                 Adjust
#define STA_IP_ADDR        (192,168,1,50) // ..168,1,50), Ethernet/Wifi Station IP Address.                                   Adjust
#define STA_GW_ADDR         (192,168,1,1) // ..,168,1,1), Ethernet/Wifi Station GATEWAY Address.                              Adjust
#define STA_SN_MASK       (255,255,255,0) // ..55,255,0), Ethernet/Wifi Station SUBNET Mask.                                  Adjust

// Visual --------------------------------------------------------------------------------------------------------------------------
#define REVERSE_WEATHER_CHART_X_AXIS  OFF // ON reverses the xaxis of weather charts so new data is to the left
#define FAV_ICON                      OFF // ON enables website icon in browsers, place favicon.ico file SD card root directory

// Connectivity check --------------------------------------------------------------------------------------------------------------
#define CONNECT_RECHECK_TIME           60 // in seconds
#define CONNECT_RESET_TRIES             5 // connection attempts before Ethernet shield is reset (if available,) must be >= 1
#define CONNECT_REBOOT_TRIES           10 // connection attempts before Watchdog reboot is forced, must be > CONNECT_RESET_TRIES

// Watchdog ------------------------------------------------------------------------------------------------------------------------
#define WATCHDOG_DURING_SD            OFF // ON keeps watchdog enabled at all times

// Roof ----------------------------------------------------------------------------------------------------------------------------
#define ROOF_MOMENTARY_BUTTON_PRESS_TIME 1.0  // in seconds, this blocks the main-loop so <= ~2 seconds!
#define ROOF_PRE_MOTION_TIME          1.5 // as above
#define ROOF_POST_MOTION_TIME         2.0 // as above
