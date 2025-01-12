/* ---------------------------------------------------------------------------------------------------------------------------------
 * Extended configuration for OCS options
 *
 *                        For more information join the OnStep Groups.io at https://groups.io/g/onstep
 * 
 *           *** Read the compiler warnings and errors, they are there to help guard against invalid configurations ***
 *
 * ---------------------------------------------------------------------------------------------------------------------------------
 * ADJUST THE FOLLOWING TO CONFIGURE YOUR CONTROLLER FEATURES ----------------------------------------------------------------------
 * <-Req'd = always must set, <-Often = usually must set, Option = optional, Adjust = adjust as req'd, Infreq = infrequently changed
*/
//      Parameter Name              Value   Default  Notes                                                                      Hint

// DEBUG ----------------------------------------------------------------------------------------------------------------------------
// Enable additional debugging and/or status messages on the specified SERIAL_DEBUG port
// Note that the SERIAL_DEBUG port cannot be used for normal communication with OnStep
#define DEBUG                         OFF //    OFF, Use ON for background error messages only, use VERBOSE for all           Infreq
                                          //         error and status messages, use CONSOLE for VT100 debug console,
                                          //         or use PROFILER for VT100 task profiler.

#define DEBUG_SERVO                   OFF //    OFF, n. Where n=1 to 9 as the designated axis for logging servo activity.     Option
#define DEBUG_ECHO_COMMANDS           OFF //    OFF, Use ON to log command/responses to the debug serial port.                Option
#define DEBUG_CONNECT_CHECK           OFF //    OFF, ON to enable debug code for connection checks.                           Infreq
#define DEBUG_SD                      OFF //    OFF, ON to enable debug code for the SD card support, use VERBOSE for all.    Infreq
#define DEBUG_WEBSERVER               OFF //    OFF, ON to enable debug code for the webserver.                               Infreq
#define DEBUG_CMDSERVER               OFF //    OFF, ON to enable debug code for the command server on port 9999.             Infreq

#define SERIAL_DEBUG               Serial // Serial, Use any h/w serial port. Serial1 or Serial2, etc. as supported.          Option
#define SERIAL_DEBUG_BAUD            9600 //   9600, n. Where n=9600,19200,57600,115200 (common baud rates.)                  Option

// NON-VOLATILE STORAGE ------------------------------------------------------------------------------------------------------------
#define NV_WIPE                       OFF //    OFF, Causes the defaults to be written back into NV (FLASH,EEPROM,etc.)       Infreq
                                          //         ***     IMPORTANT: ENABLE THIS OPTION THEN UPLOAD, WAIT A MINUTE  ***
// Warning --->                           //         ***     OR TWO THEN SET THIS OPTION TO OFF AND UPLOAD AGAIN.      ***
                                          //         ***     LEAVING THIS OPTION ENABLED CAN CAUSE EXCESSIVE NV        ***
                                          //         ***     WEAR AND DAMAGE THE MICROCONTROLLER NV SUBSYSTEM !!!      ***

// NETWORK SETTINGS ----------------------------------------------------------------------------------------------------------------

#define CONNECT_RECHECK_TIME           60 //     60, n. Where n=1 to 60 seconds.                                              Infreq
#define CONNECT_RESET_TRIES             5 //      5, n. Where n=1 to 60. Ethernet shield reset after connection attempts.     Infreq
#define CONNECT_REBOOT_TRIES           10 //     10, n. Where n=CONNECT_RESET_TRIES to 60 before watchdog reboot is forced.   Infreq

#define AP_ENABLED                  false //       false, Wifi Access Point Enabled.                                          Adjust
#define AP_PASSWORD            "password" //  "password", Wifi Access Point password.                                         Adjust
#define AP_CHANNEL                      7 //           7, Wifi Access Point channel.                                          Adjust
#define AP_IP_ADDR          {192,168,1,1} // ..,168,1,1}, Wifi Access Point IP Address.                                       Adjust
#define AP_GW_ADDR          {192,168,1,1} // ..,168,1,1}, Wifi Access Point GATEWAY Address.                                  Adjust
#define AP_SN_MASK        {255,255,255,0} // ..55,255,0}, Wifi Access Point SUBNET Mask.                                      Adjust

#define STA_ENABLED                  true //        true, Wifi Station Enabled.                                               Adjust
#define STA_DHCP_ENABLED            false //       false, Ethernet/Wifi Station DHCP Enabled.                                 Adjust
#define STA_SSID                   "Home" //      "Home", Wifi Station SSID to connnect to.                                   Adjust
#define STA_PASSWORD           "password" //  "password", Wifi Station mode password.                                         Adjust
#define STA_IP_ADDR        {192,168,1,50} // ..168,1,50}, Ethernet/Wifi Station IP Address.                                   Adjust
#define STA_GW_ADDR         {192,168,1,1} // ..,168,1,1}, Ethernet/Wifi Station GATEWAY Address.                              Adjust
#define STA_SN_MASK       {255,255,255,0} // ..55,255,0}, Ethernet/Wifi Station SUBNET Mask.                                  Adjust

#define MAC {0xDE,0xAD,0xBE,0xEF,0xFE,0xEF} // ..E,0xEF}, Ethernet unique MAC address.                                        Adjust

// VISUAL --------------------------------------------------------------------------------------------------------------------------
#define REVERSE_WEATHER_CHART_X_AXIS  OFF //    OFF, ON reverses the weather charts x-axis so new data is to the left.        Adjust
#define FAV_ICON                      OFF //    OFF, ON and place favicon.ico file SD card root directory for website icon.   Adjust

// WATCHDOG ------------------------------------------------------------------------------------------------------------------------
#define WATCHDOG_DURING_SD            OFF //    OFF, ON keeps the watchdog enabled at all times.                              Infreq


// EXTERNAL GPIO SUPPORT -----------------------------------------------------------------------------------------------------------
#define GPIO_DEVICE                   OFF //    OFF, MCP23008: for 8-ch I2C gpio.                                             Option
                                          //         MCP23017, X9555, or X8575: for 16-ch I2C gpio.
                                          //         SSR74HC595: for up to 32-ch gpio (serial shift register, output only.)
                                          //         Works w/OCS sense and relays, channels assigned in order pin# 512 and up.
