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

// NON-VOLATILE STORAGE ------------------------------------------------------------------------------------------------------------
#define NV_WIPE                       OFF //         OFF, Causes the defaults to be written back into NV (FLASH,EEPROM,etc.)  Infreq
                                          //              ***     IMPORTANT: ENABLE THIS OPTION THEN UPLOAD, WAIT A MINUTE    ***
// Warning --->                           //              ***     OR TWO THEN SET THIS OPTION TO OFF AND UPLOAD AGAIN.        ***
                                          //              ***     LEAVING THIS OPTION ENABLED CAN CAUSE EXCESSIVE NV          ***
                                          //              ***     WEAR AND DAMAGE THE MICROCONTROLLER NV SUBSYSTEM !!!        ***

// SERIAL PORT COMMAND CHANNELS ------------------------------------ see https://onstep.groups.io/g/main/wiki/6-Configuration#SERIAL
#define SERIAL_A_BAUD_DEFAULT        9600 //   9600, n. Where n=9600,19200,57600,115200 (common baud rates.)                  Infreq
#define SERIAL_B_BAUD_DEFAULT         OFF //    OFF, n. Where n=9600,19200,57600,115200 (common baud rates.)                  Option
#define SERIAL_C_BAUD_DEFAULT         OFF //    OFF, n. Where n=9600,19200,57600,115200 (common baud rates.)                  Option

// NETWORK SETTINGS ----------------------------------------------------------------------------------------------------------------
#define CONNECTION_CHECK_HOURS        OFF //    OFF, n. Where n=1 to 48 (hours.)  Connection check time.                      Option
#define CONNECTION_FAIL_WATCHDOG      OFF //    OFF, ON to stop all processing and trigger the watchdog reset.                Option

// IP ADDRESS SETTINGS -------------------------------------------------------------------------------------------------------------

// The unique (Ethernet) MAC address for your OCS
#define MAC {0xDE,0xAD,0xBE,0xEF,0xFE,0xEF}

#define TIME_IP_ADDR        {129,6,15,28} // ...6,15,28}, time-a-g.nist.gov at 129,6,15,28 or 129,6,15,29, 129,6,15,30, etc.  Option
#define CHECK_IP_ADDR    {100,24,172,113} //              default is arduino.cc. Needs ETHERNET_RESET_PIN and/or WATCHDOG to reset.

#define STA_DHCP_ENABLED            false //       false, Ethernet DHCP Enabled.                                              Adjust
#define STA_IP_ADDR        {192,168,1,50} // ..168,1,50}, Ethernet IP Address.                                                Adjust
#define STA_GW_ADDR         {192,168,1,1} // ..,168,1,1}, Ethernet GATEWAY Address.                                           Adjust
#define STA_SN_MASK       {255,255,255,0} // ..55,255,0}, Ethernet SUBNET Mask.                                               Adjust

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
