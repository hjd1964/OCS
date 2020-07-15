// -----------------------------------------------------------------------------------
// Validate current configuration

#pragma once

// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// Config.h file validation

// Ethernet setup

#if RESPONSE_INTERVAL < 500 || RESPONSE_INTERVAL > 10000
  #error "Configuration (Config.h): RESPONSE_INTERVAL must be a number between 500 and 10000 (milliseconds.)"
#endif

#if (ETHERNET_RESET_PIN < 0 || ETHERNET_RESET_PIN > 54) && ETHERNET_RESET_PIN != OFF
  #error "Configuration (Config.h): ETHERNET_RESET_PIN must OFF or a number between 0 and 54 (Pin#.)"
#endif

#if WATCHDOG != OFF && WATCHDOG != ON && WATCHDOG != ON_CC
  #error "Configuration (Config.h): WATCHDOG must be either ON, ON_CC, or OFF."
#endif

#if (CONNECTION_CHECK_HOURS < 1 || CONNECTION_CHECK_HOURS > 48) && CONNECTION_CHECK_HOURS != OFF && DEBUG_CONNECT_CHECK == OFF
  #error "Configuration (Config.h): CONNECTION_CHECK_HOURS must OFF or a number between 1 and 48 (Hours.)"
#endif

#if DEBUG_CONNECT_CHECK == ON
  #define CHECK_FAST 3600.0
#else
  #define CHECK_FAST 1UL
#endif

// Time setup

#if TIME_ZONE<-12 || TIME_ZONE>14
  #error "Configuration (Config.h): TIME_ZONE must be a number between -12 and 13 (hours.)"
#endif

#if (TIME_DISPLAY != LST) && (TIME_DISPLAY != UTC) && (TIME_DISPLAY != DST)
  #error "Configuration (Config.h): TIME_DISPLAY must be either LST, UTC, or DST"
#endif

// Status

#if (STAT_UNITS != METRIC) && (STAT_UNITS != IMPERIAL)
  #error "Configuration (Config.h): STAT_UNITS must be either METRIC or IMPERIAL"
#endif

#if (STAT_TIME_SOURCE != NTP) && (STAT_TIME_SOURCE != DS3234_RTC) && (STAT_TIME_SOURCE != DS3234_INIT)
  #error "Configuration (Config.h): STAT_TIME_SOURCE must be either NTP, DS3234_RTC, or DS3234_INIT"
#endif

#if STAT_TIME_SOURCE == DS3234_INIT
  #warning "Configuration (Config.h): STAT_TIME_SOURCE set to DS3234_INIT, remember to revert to DS3234_RTC after uploading once"
#endif

#if (STAT_MAINS_SENSE < 1 || STAT_MAINS_SENSE > 6) && STAT_MAINS_SENSE != OFF
  #error "Configuration (Config.h): STAT_MAINS_SENSE must OFF or a number between 1 and 6 (Sense#.)"
#endif

#if (STAT_MAINS_CURRENT_ANALOG < A0 || STAT_MAINS_CURRENT_ANALOG > A15) && STAT_MAINS_CURRENT_ANALOG != OFF
  #error "Configuration (Config.h): STAT_MAINS_CURRENT_ANALOG must OFF or between A0 and A15 (Analog Pin#.)"
#endif

#if (STAT_MAINS_AUX_CURRENT_ANALOG < A0 || STAT_MAINS_AUX_CURRENT_ANALOG > A15) && STAT_MAINS_AUX_CURRENT_ANALOG != OFF
  #error "Configuration (Config.h): STAT_MAINS_AUX_CURRENT_ANALOG must OFF or between A0 and A15 (Analog Pin#.)"
#endif

#if (STAT_DC_VOLTAGE_ANALOG < A0 || STAT_DC_VOLTAGE_ANALOG > A15) && STAT_DC_VOLTAGE_ANALOG != OFF
  #error "Configuration (Config.h): STAT_DC_VOLTAGE_ANALOG must OFF or between A0 and A15 (Analog Pin#.)"
#endif

#if (STAT_DC_CURRENT_ANALOG < A0 || STAT_DC_CURRENT_ANALOG > A15) && STAT_DC_CURRENT_ANALOG != OFF
  #error "Configuration (Config.h): STAT_DC_CURRENT_ANALOG must OFF or between A0 and A15 (Analog Pin#.)"
#endif

#if (STAT_BATTERY_VOLTAGE_ANALOG < A0 || STAT_BATTERY_VOLTAGE_ANALOG > A15) && STAT_BATTERY_VOLTAGE_ANALOG != OFF
  #error "Configuration (Config.h): STAT_BATTERY_VOLTAGE_ANALOG must OFF or between A0 and A15 (Analog Pin#.)"
#endif

#if (STAT_BATTERY_CURRENT_ANALOG < A0 || STAT_BATTERY_CURRENT_ANALOG > A15) && STAT_BATTERY_CURRENT_ANALOG != OFF
  #error "Configuration (Config.h): STAT_BATTERY_CURRENT_ANALOG must OFF or between A0 and A15 (Analog Pin#.)"
#endif

// Weather

#if WEATHER != OFF && WEATHER != ON
  #error "Configuration (Config.h): WEATHER, OCS website weather panel display, must OFF or ON."
#endif

#if WEATHER_CHARTS != OFF && WEATHER_CHARTS != ON
  #error "Configuration (Config.h): WEATHER_CHARTS, OCS website weather graphic charts, must OFF or ON."
#endif

#if WEATHER_CHARTS == ON
  #warning "Configuration (Config.h): WEATHER_CHARTS enabled, be sure you have the micro SD card w/Chart.js installed."
#endif

#if WEATHER_TEMPERATURE != OFF && WEATHER_TEMPERATURE != ON
  #error "Configuration (Config.h): WEATHER_TEMPERATURE, OCS temperature input, must OFF or ON."
#endif

#if WEATHER_PRESSURE != OFF && WEATHER_PRESSURE != ON
  #error "Configuration (Config.h): WEATHER_PRESSURE, OCS temperature input, must OFF or ON."
#endif

#if WEATHER_NOMINAL_PRESSURE<500 || WEATHER_NOMINAL_PRESSURE>1050
  #error "Configuration (Config.h): WEATHER_NOMINAL_PRESSURE must be a number between 500 and 1050 (mb.)"
#endif

#if WEATHER_ALTITUDE<-86 || WEATHER_ALTITUDE>5000
  #error "Configuration (Config.h): WEATHER_ALTITUDE must be a number between -86 and 5000 (meters.)"
#endif

#if WEATHER_HUMIDITY != OFF && WEATHER_HUMIDITY != ON
  #error "Configuration (Config.h): WEATHER_HUMIDITY, OCS temperature input, must OFF or ON."
#endif

#if WEATHER_WIND_SPD != OFF && WEATHER_WIND_SPD != ON
  #error "Configuration (Config.h): WEATHER_WIND_SPD, OCS temperature input, must OFF or ON."
#endif

#if WEATHER_WIND_SPD_THRESHOLD<0 || WEATHER_WIND_SPD_THRESHOLD>100
  #error "Configuration (Config.h): WEATHER_WIND_SPD_THRESHOLD must be a number between 0 and 100 (kph.)"
#endif

#if WEATHER_SKY_QUAL != OFF && WEATHER_SKY_QUAL != ON
  #error "Configuration (Config.h): WEATHER_SKY_QUAL, OCS temperature input, must OFF or ON."
#endif

#if WEATHER_RAIN != OFF && WEATHER_RAIN != ON
  #error "Configuration (Config.h): WEATHER_RAIN, OCS temperature input, must OFF or ON."
#endif

#if WEATHER_CLOUD_CVR != OFF && WEATHER_CLOUD_CVR != ON
  #error "Configuration (Config.h): WEATHER_RAIN, OCS temperature input, must OFF or ON."
#endif

#if WEATHER_SAFE_THRESHOLD<-25 || WEATHER_SAFE_THRESHOLD>0
  #error "Configuration (Config.h): WEATHER_SAFE_THRESHOLD must be a number between -25 and 0 (Deg. C.)"
#endif

#if WEATHER_VCLR_THRESHOLD<-25 || WEATHER_VCLR_THRESHOLD>0
  #error "Configuration (Config.h): WEATHER_VCLR_THRESHOLD must be a number between -25 and 0 (Deg. C.)"
#endif

#if WEATHER_CLER_THRESHOLD<-25 || WEATHER_CLER_THRESHOLD>0
  #error "Configuration (Config.h): WEATHER_CLER_THRESHOLD must be a number between -25 and 0 (Deg. C.)"
#endif

#if WEATHER_HAZE_THRESHOLD<-25 || WEATHER_HAZE_THRESHOLD>0
  #error "Configuration (Config.h): WEATHER_HAZE_THRESHOLD must be a number between -25 and 0 (Deg. C.)"
#endif

#if WEATHER_OVRC_THRESHOLD<-25 || WEATHER_OVRC_THRESHOLD>0
  #error "Configuration (Config.h): WEATHER_OVRC_THRESHOLD must be a number between -25 and 0 (Deg. C.)"
#endif

#if WEATHER_CLDY_THRESHOLD<-25 || WEATHER_CLDY_THRESHOLD>0
  #error "Configuration (Config.h): WEATHER_CLDY_THRESHOLD must be a number between -25 and 0 (Deg. C.)"
#endif

#if WEATHER_VCLD_THRESHOLD<-25 || WEATHER_VCLD_THRESHOLD>0
  #error "Configuration (Config.h): WEATHER_VCLD_THRESHOLD must be a number between -25 and 0 (Deg. C.)"
#endif

// Power control

#if POWER != OFF && POWER != ON
  #error "Configuration (Config.h): POWER, OCS website power panel display, must OFF or ON."
#endif

#if (POWER_DEVICE1_RELAY < 1 || POWER_DEVICE1_RELAY > 14) && POWER_DEVICE1_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE1_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if POWER_DEVICE1_MEMORY != OFF && POWER_DEVICE1_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE1_MEMORY must OFF or ON."
#endif

#if (POWER_DEVICE2_RELAY < 1 || POWER_DEVICE2_RELAY > 14) && POWER_DEVICE2_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE2_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if POWER_DEVICE2_MEMORY != OFF && POWER_DEVICE2_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE2_MEMORY must OFF or ON."
#endif

#if (POWER_DEVICE3_RELAY < 1 || POWER_DEVICE3_RELAY > 14) && POWER_DEVICE3_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE3_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if POWER_DEVICE3_MEMORY != OFF && POWER_DEVICE3_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE3_MEMORY must OFF or ON."
#endif

#if (POWER_DEVICE4_RELAY < 1 || POWER_DEVICE4_RELAY > 14) && POWER_DEVICE4_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE4_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if POWER_DEVICE4_MEMORY != OFF && POWER_DEVICE4_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE4_MEMORY must OFF or ON."
#endif

#if (POWER_DEVICE5_RELAY < 1 || POWER_DEVICE5_RELAY > 14) && POWER_DEVICE5_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE5_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if POWER_DEVICE5_MEMORY != OFF && POWER_DEVICE5_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE5_MEMORY must OFF or ON."
#endif

#if (POWER_DEVICE6_RELAY < 1 || POWER_DEVICE6_RELAY > 14) && POWER_DEVICE6_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE6_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if POWER_DEVICE6_MEMORY != OFF && POWER_DEVICE6_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE6_MEMORY must OFF or ON."
#endif

// Thermostat

#if THERMOSTAT != OFF && THERMOSTAT != ON
  #error "Configuration (Config.h): THERMOSTAT, OCS website thermostat panel display, must OFF or ON."
#endif

#if (HEAT_RELAY < 1 || HEAT_RELAY > 14) && HEAT_RELAY != OFF
  #error "Configuration (Config.h): HEAT_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if (COOL_RELAY < 1 || COOL_RELAY > 14) && COOL_RELAY != OFF
  #error "Configuration (Config.h): COOL_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if THERMOSTAT_HUMIDITY != OFF && THERMOSTAT_HUMIDITY != ON
  #error "Configuration (Config.h): THERMOSTAT_HUMIDITY, OCS website thermostat humidity display, must OFF or ON."
#endif

// Lighting

#if LIGHT != OFF && LIGHT != ON
  #error "Configuration (Config.h): LIGHT, OCS website lighting panel display, must OFF or ON."
#endif

#if (LIGHT_WRW_RELAY < 1 || LIGHT_WRW_RELAY > 14) && LIGHT_WRW_RELAY != OFF
  #error "Configuration (Config.h): LIGHT_WRW_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if (LIGHT_WRR_RELAY < 1 || LIGHT_WRR_RELAY > 14) && LIGHT_WRR_RELAY != OFF
  #error "Configuration (Config.h): LIGHT_WRR_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if (LIGHT_ORW_RELAY < 1 || LIGHT_ORW_RELAY > 14) && LIGHT_ORW_RELAY != OFF
  #error "Configuration (Config.h): LIGHT_ORW_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if (LIGHT_ORR_RELAY < 1 || LIGHT_ORR_RELAY > 14) && LIGHT_ORR_RELAY != OFF
  #error "Configuration (Config.h): LIGHT_ORR_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if (LIGHT_OUTSIDE_RELAY < 1 || LIGHT_OUTSIDE_RELAY > 14) && LIGHT_OUTSIDE_RELAY != OFF
  #error "Configuration (Config.h): LIGHT_OUTSIDE_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if (LIGHT_SW_SENSE < 1 || LIGHT_SW_SENSE > 6) && LIGHT_SW_SENSE != OFF
  #error "Configuration (Config.h): LIGHT_SW_SENSE must OFF or a number between 1 and 6 (Sense#.)"
#endif

// ROR

#if ROR != OFF && ROR != ON
  #error "Configuration (Config.h): ROR, OCS website roll off roof control display, must OFF or ON."
#endif

#if ROR_USER_SAFETY_OVERRIDE != OFF && ROR_USER_SAFETY_OVERRIDE != ON
  #error "Configuration (Config.h): ROR_USER_SAFETY_OVERRIDE, OCS website ROR safety override control display, must OFF or ON."
#endif

#if ROR_AUTOCLOSE_DAWN != OFF && ROR_AUTOCLOSE_DAWN != ON
  #error "Configuration (Config.h): ROR_AUTOCLOSE_DAWN, OCS website ROR automatic close at dawn control display, must OFF or ON."
#endif

#if ROR_AUTOCLOSE_DAWN_DEFAULT != OFF && ROR_AUTOCLOSE_DAWN_DEFAULT != ON
  #error "Configuration (Config.h): ROR_AUTOCLOSE_DAWN_DEFAULT, OCS website ROR automatic close at dawn default state, must OFF or ON."
#endif

#if ROR_AUTOCLOSE_SAFETY != OFF && ROR_AUTOCLOSE_SAFETY != ON
  #error "Configuration (Config.h): ROR_AUTOCLOSE_SAFETY, OCS website ROR automatic close safety, must OFF or ON."
#endif

#if (ROR_MOTOR_OPEN_RELAY < 1 || ROR_MOTOR_OPEN_RELAY > 14) && ROR_MOTOR_OPEN_RELAY != OFF
  #error "Configuration (Config.h): ROR_MOTOR_OPEN_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if (ROR_MOTOR_CLOSE_RELAY < 1 || ROR_MOTOR_CLOSE_RELAY > 14) && ROR_MOTOR_CLOSE_RELAY != OFF
  #error "Configuration (Config.h): ROR_MOTOR_CLOSE_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if ROR_MOTOR_OPEN_RELAY != OFF && ROR_MOTOR_OPEN_RELAY == ROR_MOTOR_CLOSE_RELAY
  #if ROR_MOTOR_RELAY_MOMENTARY == ON
    #define ROR_SINGLE_OPEN_CLOSE_RELAY ON
    #if ROR_MOTOR_STOP_RELAY == ROR_MOTOR_OPEN_RELAY
      #define ROR_SINGLE_OPEN_CLOSE_STOP_RELAY ON
    #endif
  #else
    #error "Configuration (Config.h): ROR_MOTOR_OPEN_RELAY and ROR_MOTOR_CLOSE_RELAY on the same RELAY# is only allowed if ROR_MOTOR_RELAY_MOMENTARY is used."
  #endif
#else
  #define ROR_SINGLE_OPEN_CLOSE_RELAY OFF
#endif

#if ROR == ON && (ROR_MOTOR_OPEN_RELAY == OFF || ROR_MOTOR_CLOSE_RELAY == OFF)
  #error "Configuration (Config.h): Roof control requires relays that either press button(s) on an automatic opener or operate a motor to move the roof."
#endif

#if (ROR_MOTOR_OPEN_RELAY != OFF && ROR_MOTOR_CLOSE_RELAY == OFF) || (ROR_MOTOR_OPEN_RELAY == OFF && ROR_MOTOR_CLOSE_RELAY != OFF)
  #error "Configuration (Config.h): Roof operation requires both ROR_MOTOR_OPEN_RELAY and ROR_MOTOR_CLOSE_RELAY (even if both are on the same RELAY.)"
#endif

#if (ROR_POWER_RELAY < 1 || ROR_POWER_RELAY > 14) && ROR_POWER_RELAY != OFF
  #error "Configuration (Config.h): ROR_POWER_RELAY must OFF or a number between 1 and 14 (Relay#.)"
#endif

#if (ROR_POWER_PWM_FREQUENCY<1 || ROR_POWER_PWM_FREQUENCY>100) && ROR_POWER_PWM_FREQUENCY != OFF
  #error "Configuration (Config.h): ROR_POWER_PWM_FREQUENCY must be OFF or a number between 1 and 100 (Hz.)"
#endif

#if (ROR_POWER_PWM_POWER<10 || ROR_POWER_PWM_POWER>100) && ROR_POWER_PWM_POWER != OFF
  #error "Configuration (Config.h): ROR_POWER_PWM_POWER must be OFF or a number between 10 and 100 (%.)"
#endif

#if ROR_POWER_PWM_SOFTSTART != OFF && ROR_POWER_PWM_SOFTSTART != ON
  #error "Configuration (Config.h): ROR_POWER_PWM_SOFTSTART must OFF or ON."
#endif

#if ROR_MOTOR_RELAY_MOMENTARY == ON
  #if ROR_POWER_RELAY != OFF
    #if ROR_POWER_PWM_FREQUENCY != OFF
      #error "Configuration (Config.h): For ROR_MOTOR_RELAY_MOMENTARY the setting ROR_POWER_PWM_FREQUENCY must be OFF."
    #endif
    #if ROR_POWER_PWM_POWER != OFF
      #error "Configuration (Config.h): For ROR_MOTOR_RELAY_MOMENTARY the setting ROR_POWER_PWM_POWER must be OFF."
    #endif
    #if ROR_POWER_PWM_SOFTSTART != OFF
      #error "Configuration (Config.h): For ROR_MOTOR_RELAY_MOMENTARY the setting ROR_POWER_PWM_SOFTSTART must be OFF."
    #endif
  #endif
#endif

#if (ROR_SENSE_INTERLOCK < 1 || ROR_SENSE_INTERLOCK > 6) && ROR_SENSE_INTERLOCK != OFF
  #error "Configuration (Config.h): ROR_SENSE_INTERLOCK must be OFF or a number between 1 and 6 (Sense#.)"
#endif

#if ROR == ON && (ROR_SENSE_LIMIT_CLOSED == OFF || ROR_SENSE_LIMIT_OPENED == OFF)
  #error "Configuration (Config.h): Roof open and close limit sensors are both required if ROR control is enabled."
#endif

#if (ROR_SENSE_LIMIT_CLOSED < 1 || ROR_SENSE_LIMIT_CLOSED > 6) && ROR_SENSE_LIMIT_CLOSED != OFF
  #error "Configuration (Config.h): ROR_SENSE_LIMIT_CLOSED must OFF or a number between 1 and 6 (Sense#.)"
#endif

#if (ROR_SENSE_LIMIT_OPENED < 1 || ROR_SENSE_LIMIT_OPENED > 6) && ROR_SENSE_LIMIT_OPENED != OFF
  #error "Configuration (Config.h): ROR_SENSE_LIMIT_OPENED must OFF or a number between 1 and 6 (Sense#.)"
#endif

#if ROR_TIME_AVG<30 || ROR_TIME_AVG>1200
  #error "Configuration (Config.h): ROR_TIME_AVG must be a number between 30 and 1200 (seconds.)"
#endif

#if ROR_TIME_TOL<0 || ROR_TIME_TOL>120
  #error "Configuration (Config.h): ROR_TIME_TOL must be a number between 0 and 120 (seconds.)"
#endif

#if ROR_TIME_LIMIT_SENSE_FAIL<1 || ROR_TIME_LIMIT_SENSE_FAIL>60
  #error "Configuration (Config.h): ROR_TIME_LIMIT_SENSE_FAIL must be a number between 1 and 60 (seconds.)"
#endif
