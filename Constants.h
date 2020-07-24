// -----------------------------------------------------------------------------------
// Constants

#pragma once
// Configuration options -----------------------------------------------------------------------------------------------------------

// On/Off, etc.
#define OFF                               -1
#define ON                                -2
#define ON_PULLUP                         -3
#define ON_PULLDOWN                       -4
#define ON_CC                             -5

// Time
#define LST                                1
#define DST                                2
#define UTC                                3

#define NTP                                1
#define DS3234_RTC                         2
#define DS3234_INIT                        3

// Units
#define METRIC                             1
#define IMPERIAL                           2

// Connectivity check --------------------------------------------------------------------------------------------------------------

#define CONNECT_RECHECK_TIME               60  // in seconds
#define CONNECT_RESET_TRIES                 5  // connection attempts before Ethernet shield is reset (if available,) must be >= 1
#define CONNECT_REBOOT_TRIES               10  // connection attempts before Watchdog reboot is forced, must be > CONNECT_RESET_TRIES

// Watchdog ------------------------------------------------------------------------------------------------------------------------
#define WATCHDOG_DURING_SD                OFF  // set to ON to keep watchdog enabled at all times

// Roof ----------------------------------------------------------------------------------------------------------------------------

#define ROOF_MOMENTARY_BUTTON_PRESS_TIME 1.0  // in seconds, this blocks the main-loop so <= ~2 seconds!
#define ROOF_PRE_MOTION_TIME             1.5  // as above
#define ROOF_POST_MOTION_TIME            2.0  // as above

// Misc ----------------------------------------------------------------------------------------------------------------------------

#define invalid -1000
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// EEPROM addresses ----------------------------------------------------------------------------------------------------------------
#define EE_key             0
// control heat & cooling/vent
#define EE_heatSetpoint    120
#define EE_coolSetpoint    124
// roof motion timing
#define EE_timeLeftToOpen  129
#define EE_timeLeftToClose 133
// power status device memory
#define EE_powerDevice_1   200
#define EE_powerDevice_2   201
#define EE_powerDevice_3   202
#define EE_powerDevice_4   203
#define EE_powerDevice_5   204
#define EE_powerDevice_6   205
