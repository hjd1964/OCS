// -----------------------------------------------------------------------------------
// Constants

#pragma once
// Configuration options -----------------------------------------------------------------------------------------------------------

// On/Off, etc.
#define OFF                        -1
#define ON                         -2
#define ON_PULLUP                  -3
#define ON_PULLDOWN                -4

// Time
#define LST                         1
#define DST                         2
#define UTC                         3

#define NTP                         1
#define DS3234                      2

// Units
#define METRIC                      1
#define IMPERIAL                    2

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
