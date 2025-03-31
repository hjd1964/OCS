// -----------------------------------------------------------------------------------
// Common includes
#pragma once

#include <Arduino.h>
#include "Constants.h"
#include "lib/Constants.h"
#include "../Config.h"
#include "Config.defaults.h"
#include "HAL/HAL.h"
#include "lib/Macros.h"
#include "pinmaps/Models.h"
#include "lib/debug/Debug.h"

#include "lib/convert/Convert.h"

#if OPERATIONAL_MODE != OFF
  // optional (but expected to be present) web-server
  #define WEB_SERVER                    ON         // for website at port 80
  #define SD_CARD                       ON         // enable the webserver SD_CARD support
#endif

#include "lib/ethernet/EthernetManager.h"
#include "lib/wifi/WifiManager.h"

#if SD_CARD == ON
  #ifdef ESP32
    #include <FS.h>
    #include <FFat.h>
    #define FS FFat
    #define FS_PREFIX "/"
  #else
    #include <SD.h>
    #define FS SD
    #define FS_PREFIX ""
  #endif
#endif

extern bool hasFileSystem;

extern char ocsVersion[10];

#if STAT != OFF || POWER != OFF || LIGHT != OFF || WEATHER != OFF || THERMOSTAT != OFF || ROOF != OFF || DOME != OFF
  #define WWW_SERVER ON
#endif

#if STAT_MAINS_SENSE != OFF || STAT_MAINS_CURRENT_ANALOG != OFF || STAT_MAINS_AUX_CURRENT_ANALOG || \
    STAT_DC_VOLTAGE_ANALOG != OFF || STAT_DC_CURRENT_ANALOG != OFF || STAT_BATTERY_VOLTAGE_ANALOG || \
    STAT_BATTERY_CURRENT_ANALOG != OFF || STAT_PROCESSOR_RAM != OFF
  #define STAT_PRESENT
#endif

#if POWER_DEVICE1_RELAY != OFF || POWER_DEVICE2_RELAY != OFF || POWER_DEVICE3_RELAY != OFF || \
    POWER_DEVICE4_RELAY != OFF || POWER_DEVICE5_RELAY != OFF  || POWER_DEVICE6_RELAY != OFF 
  #define POWER_PRESENT
#endif

#if HEAT_RELAY != OFF || COOL_RELAY != OFF || HUMIDITY_RELAY != OFF
  #define THERMOSTAT_PRESENT
#endif

#if LIGHT_WRW_RELAY != OFF || LIGHT_WRR_RELAY != OFF || LIGHT_ORW_RELAY != OFF || \
    LIGHT_ORR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF || LIGHT_OUTSIDE_RELAY != OFF 
  #define LIGHT_PRESENT
#endif

#if WEATHER_TEMPERATURE != OFF || WEATHER_PRESSURE != OFF || WEATHER_HUMIDITY != OFF || \
    WEATHER_WIND_SPD != OFF || WEATHER_RAIN != OFF || WEATHER_CLOUD_CVR != OFF || WEATHER_SKY_QUAL != OFF
  #define WEATHER_PRESENT
#endif
#define LOG_RECORDS_PER_HOUR  (3600L/(LOG_PERIOD_SECONDS))
#define LOG_RECORDS_PER_DAY   (86400L/(LOG_PERIOD_SECONDS))
#define logRecordLocation(t)  ((long)round(hour(t)*3600L+minute(t)*60L+second(t))/(LOG_PERIOD_SECONDS))

#if AXIS1_DRIVER_MODEL != OFF
  #define AXIS_PRESENT
  #define DOME_PRESENT
#endif

#if ROOF_MOTOR_OPEN_RELAY != OFF && ROOF_MOTOR_CLOSE_RELAY != OFF
  #define ROOF_PRESENT
#endif

