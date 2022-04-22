// -----------------------------------------------------------------------------------
// Validate current configuration
#pragma once

// Pinmap
#if PINMAP != OFF && (PINMAP < PINMAP_FIRST || PINMAP > PINMAP_LAST)
  #error "Configuration (Config.h): Unrecognized PINMAP must OFF or set to a known pinmap."
#endif

// Ethernet setup
#if RESPONSE_INTERVAL < 500 || RESPONSE_INTERVAL > 10000
  #error "Configuration (Config.h): RESPONSE_INTERVAL must be a number between 500 and 10000 (milliseconds.)"
#endif

#if (ETHERNET_RESET_PIN < 0 || ETHERNET_RESET_PIN > 54) && ETHERNET_RESET_PIN != OFF
  #error "Configuration (Config.h): ETHERNET_RESET_PIN must OFF or a number between 0 and 54 (Pin#.)"
#endif

#if WATCHDOG != OFF && WATCHDOG != ON
  #error "Configuration (Config.h): WATCHDOG must be either ON or OFF."
#endif

#if (CONNECT_CHECK_HOURS < 1 || CONNECT_CHECK_HOURS > 48) && CONNECT_CHECK_HOURS != OFF && DEBUG_CONNECT_CHECK == OFF
  #error "Configuration (Config.h): CONNECT_CHECK_HOURS must OFF or a number between 1 and 48 (Hours.)"
#endif

#if CONNECT_FAIL_WATCHDOG != OFF && CONNECT_FAIL_WATCHDOG != ON
  #error "Configuration (Config.h): CONNECT_FAIL_WATCHDOG must be either ON or OFF."
#endif

#if CONNECT_FAIL_WATCHDOG == ON && WATCHDOG != ON
  #error "Configuration (Config.h): CONNECT_FAIL_WATCHDOG ON requires WATCHDOG ON."
#endif

// Time setup
#if TIME_ZONE<-12 || TIME_ZONE>14
  #error "Configuration (Config.h): TIME_ZONE must be a number between -12 and 13 (hours.)"
#endif

#if (TIME_DISPLAY != STD) && (TIME_DISPLAY != UT1) && (TIME_DISPLAY != DST)
  #error "Configuration (Config.h): TIME_DISPLAY must be either STD, UT1, or DST"
#endif

// Status
#if (STAT_UNITS != METRIC) && (STAT_UNITS != IMPERIAL)
  #error "Configuration (Config.h): STAT_UNITS must be either METRIC or IMPERIAL"
#endif

#if (TIME_LOCATION_SOURCE != NTP) && (TIME_LOCATION_SOURCE != DS3231) && (TIME_LOCATION_SOURCE != DS3234) && (TIME_LOCATION_SOURCE != GPS)
  #error "Configuration (Config.h): TIME_LOCATION_SOURCE must be either NTP, GPS, DS3231, or DS3234"
#endif

#if TIME_LOCATION_SOURCE == DS3234_INIT
  //#warning "Configuration (Config.h): TIME_LOCATION_SOURCE set to DS3234_INIT, remember to revert to DS3234_RTC after uploading once"
#endif

#if (STAT_MAINS_SENSE < 1 || STAT_MAINS_SENSE > 8) && STAT_MAINS_SENSE != OFF
  #error "Configuration (Config.h): STAT_MAINS_SENSE must OFF or a number between 1 and 8 (SENSE#.)"
#endif

#if (STAT_MAINS_CURRENT_ANALOG < 1 || STAT_MAINS_CURRENT_ANALOG > 16) && STAT_MAINS_CURRENT_ANALOG != OFF
  #error "Configuration (Config.h): STAT_MAINS_CURRENT_ANALOG must OFF or between 1 and 16 (ASENSE#.)"
#endif

#if (STAT_MAINS_AUX_CURRENT_ANALOG < 1 || STAT_MAINS_AUX_CURRENT_ANALOG > 16) && STAT_MAINS_AUX_CURRENT_ANALOG != OFF
  #error "Configuration (Config.h): STAT_MAINS_AUX_CURRENT_ANALOG must OFF or between 1 and 16 (ASENSE#.)"
#endif

#if (STAT_DC_VOLTAGE_ANALOG < 1 || STAT_DC_VOLTAGE_ANALOG > 16) && STAT_DC_VOLTAGE_ANALOG != OFF
  #error "Configuration (Config.h): STAT_DC_VOLTAGE_ANALOG must OFF or between 1 and 16 (ASENSE#.)"
#endif

#if (STAT_DC_CURRENT_ANALOG < 1 || STAT_DC_CURRENT_ANALOG > 16) && STAT_DC_CURRENT_ANALOG != OFF
  #error "Configuration (Config.h): STAT_DC_CURRENT_ANALOG must OFF or between 1 and 16 (ASENSE#.)"
#endif

#if (STAT_BATTERY_VOLTAGE_ANALOG < 1 || STAT_BATTERY_VOLTAGE_ANALOG > 16) && STAT_BATTERY_VOLTAGE_ANALOG != OFF
  #error "Configuration (Config.h): STAT_BATTERY_VOLTAGE_ANALOG must OFF or between 1 and 16 (ASENSE#.)"
#endif

#if (STAT_BATTERY_CURRENT_ANALOG < 1 || STAT_BATTERY_CURRENT_ANALOG > 16) && STAT_BATTERY_CURRENT_ANALOG != OFF
  #error "Configuration (Config.h): STAT_BATTERY_CURRENT_ANALOG must OFF or between 1 and 16 (ASENSE#.)"
#endif

#if STAT_PROCESSOR_RAM != OFF && !defined(__AVR_ATmega2560__)
  #error "Configuration (Config.h): STAT_PROCESSOR_RAM ON is only supported on the Mega2560."
#endif

// Weather
#if WEATHER != OFF && WEATHER != ON
  #error "Configuration (Config.h): WEATHER, OCS website weather panel display, must OFF or ON."
#endif

#if WEATHER == ON && !defined(WEATHER_PRESENT)
  #error "Configuration (Config.h): WEATHER, OCS website weather panel display enabled but not setup."
#endif

#if WEATHER_CHARTS != OFF && WEATHER_CHARTS != ON
  #error "Configuration (Config.h): WEATHER_CHARTS, OCS website weather graphic charts, must OFF or ON."
#endif

#if WEATHER_CHARTS != OFF && WEATHER_CHARTS != ON
  #error "Configuration (Config.h): WEATHER, OCS website weather charts option, must OFF or ON."
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

#if POWER == ON && !defined(POWER_PRESENT)
  #error "Configuration (Config.h): POWER, OCS website power panel display enabled but not setup."
#endif

#if (POWER_DEVICE1_RELAY < 1 || POWER_DEVICE1_RELAY > 18) && POWER_DEVICE1_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE1_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if POWER_DEVICE1_MEMORY != OFF && POWER_DEVICE1_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE1_MEMORY must OFF or ON."
#endif

#if (POWER_DEVICE2_RELAY < 1 || POWER_DEVICE2_RELAY > 18) && POWER_DEVICE2_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE2_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if POWER_DEVICE2_MEMORY != OFF && POWER_DEVICE2_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE2_MEMORY must OFF or ON."
#endif

#if (POWER_DEVICE3_RELAY < 1 || POWER_DEVICE3_RELAY > 18) && POWER_DEVICE3_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE3_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if POWER_DEVICE3_MEMORY != OFF && POWER_DEVICE3_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE3_MEMORY must OFF or ON."
#endif

#if (POWER_DEVICE4_RELAY < 1 || POWER_DEVICE4_RELAY > 18) && POWER_DEVICE4_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE4_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if POWER_DEVICE4_MEMORY != OFF && POWER_DEVICE4_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE4_MEMORY must OFF or ON."
#endif

#if (POWER_DEVICE5_RELAY < 1 || POWER_DEVICE5_RELAY > 18) && POWER_DEVICE5_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE5_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if POWER_DEVICE5_MEMORY != OFF && POWER_DEVICE5_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE5_MEMORY must OFF or ON."
#endif

#if (POWER_DEVICE6_RELAY < 1 || POWER_DEVICE6_RELAY > 18) && POWER_DEVICE6_RELAY != OFF
  #error "Configuration (Config.h): POWER_DEVICE6_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if POWER_DEVICE6_MEMORY != OFF && POWER_DEVICE6_MEMORY != ON
  #error "Configuration (Config.h): POWER_DEVICE6_MEMORY must OFF or ON."
#endif

// Thermostat
#if THERMOSTAT != OFF && THERMOSTAT != ON
  #error "Configuration (Config.h): THERMOSTAT, OCS website thermostat panel display, must OFF or ON."
#endif

#if THERMOSTAT == ON && !defined(THERMOSTAT_PRESENT)
  #error "Configuration (Config.h): THERMOSTAT, OCS website thermostat display enabled but not setup."
#endif

#if (HEAT_RELAY < 1 || HEAT_RELAY > 18) && HEAT_RELAY != OFF
  #error "Configuration (Config.h): HEAT_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if (COOL_RELAY < 1 || COOL_RELAY > 18) && COOL_RELAY != OFF
  #error "Configuration (Config.h): COOL_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if THERMOSTAT_HUMIDITY != OFF && THERMOSTAT_HUMIDITY != ON
  #error "Configuration (Config.h): THERMOSTAT_HUMIDITY, OCS website thermostat humidity display, must OFF or ON."
#endif

// Lighting
#if LIGHT != OFF && LIGHT != ON
  #error "Configuration (Config.h): LIGHT, OCS website lighting panel display, must OFF or ON."
#endif

#if LIGHT == ON && !defined(LIGHT_PRESENT)
  #error "Configuration (Config.h): LIGHT, OCS website light display enabled but not setup."
#endif

#if (LIGHT_WRW_RELAY < 1 || LIGHT_WRW_RELAY > 18) && LIGHT_WRW_RELAY != OFF
  #error "Configuration (Config.h): LIGHT_WRW_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if (LIGHT_WRR_RELAY < 1 || LIGHT_WRR_RELAY > 18) && LIGHT_WRR_RELAY != OFF
  #error "Configuration (Config.h): LIGHT_WRR_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if (LIGHT_ORW_RELAY < 1 || LIGHT_ORW_RELAY > 18) && LIGHT_ORW_RELAY != OFF
  #error "Configuration (Config.h): LIGHT_ORW_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if (LIGHT_ORR_RELAY < 1 || LIGHT_ORR_RELAY > 18) && LIGHT_ORR_RELAY != OFF
  #error "Configuration (Config.h): LIGHT_ORR_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if (LIGHT_OUTSIDE_RELAY < 1 || LIGHT_OUTSIDE_RELAY > 18) && LIGHT_OUTSIDE_RELAY != OFF
  #error "Configuration (Config.h): LIGHT_OUTSIDE_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if (LIGHT_SW_SENSE < 1 || LIGHT_SW_SENSE > 8) && LIGHT_SW_SENSE != OFF
  #error "Configuration (Config.h): LIGHT_SW_SENSE must OFF or a number between 1 and 8 (SENSE#.)"
#endif

// ROOF
#if ROOF != OFF && ROOF != ON
  #error "Configuration (Config.h): ROOF, OCS website roll off roof control display, must OFF or ON."
#endif

#if ROOF == ON && !defined(ROOF_PRESENT)
  #error "Configuration (Config.h): ROOF, OCS website roof/shutter control display enabled but not setup."
#endif

#if ROOF_USER_SAFETY_OVERRIDE != OFF && ROOF_USER_SAFETY_OVERRIDE != ON
  #error "Configuration (Config.h): ROOF_USER_SAFETY_OVERRIDE, OCS website ROOF safety override control display, must OFF or ON."
#endif

#if ROOF_AUTOCLOSE_DAWN != OFF && ROOF_AUTOCLOSE_DAWN != ON
  #error "Configuration (Config.h): ROOF_AUTOCLOSE_DAWN, OCS website ROOF automatic close at dawn control display, must OFF or ON."
#endif

#if ROOF_AUTOCLOSE_DAWN_DEFAULT != OFF && ROOF_AUTOCLOSE_DAWN_DEFAULT != ON
  #error "Configuration (Config.h): ROOF_AUTOCLOSE_DAWN_DEFAULT, OCS website ROOF automatic close at dawn default state, must OFF or ON."
#endif

#if ROOF_AUTOCLOSE_SAFETY != OFF && ROOF_AUTOCLOSE_SAFETY != ON
  #error "Configuration (Config.h): ROOF_AUTOCLOSE_SAFETY, OCS website ROOF automatic close safety, must OFF or ON."
#endif

#if (ROOF_MOTOR_OPEN_RELAY < 1 || ROOF_MOTOR_OPEN_RELAY > 18) && ROOF_MOTOR_OPEN_RELAY != OFF
  #error "Configuration (Config.h): ROOF_MOTOR_OPEN_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if (ROOF_MOTOR_CLOSE_RELAY < 1 || ROOF_MOTOR_CLOSE_RELAY > 18) && ROOF_MOTOR_CLOSE_RELAY != OFF
  #error "Configuration (Config.h): ROOF_MOTOR_CLOSE_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if ROOF_MOTOR_OPEN_RELAY != OFF && ROOF_MOTOR_OPEN_RELAY == ROOF_MOTOR_CLOSE_RELAY
  #if ROOF_MOTOR_RELAY_MOMENTARY != ON
    #error "Configuration (Config.h): ROOF_MOTOR_OPEN_RELAY and ROOF_MOTOR_CLOSE_RELAY on the same RELAY# is only allowed if ROOF_MOTOR_RELAY_MOMENTARY is used."
  #endif
#endif

#if ROOF == ON && (ROOF_MOTOR_OPEN_RELAY == OFF || ROOF_MOTOR_CLOSE_RELAY == OFF)
  #error "Configuration (Config.h): Roof control requires relays that either press button(s) on an automatic opener or operate a motor to move the roof."
#endif

#if (ROOF_MOTOR_OPEN_RELAY != OFF && ROOF_MOTOR_CLOSE_RELAY == OFF) || (ROOF_MOTOR_OPEN_RELAY == OFF && ROOF_MOTOR_CLOSE_RELAY != OFF)
  #error "Configuration (Config.h): Roof operation requires both ROOF_MOTOR_OPEN_RELAY and ROOF_MOTOR_CLOSE_RELAY (even if both are on the same RELAY.)"
#endif

#if (ROOF_POWER_RELAY < 1 || ROOF_POWER_RELAY > 18) && ROOF_POWER_RELAY != OFF
  #error "Configuration (Config.h): ROOF_POWER_RELAY must OFF or a number between 1 and 18 (RELAY#.)"
#endif

#if (ROOF_POWER_PWM_FREQUENCY<1 || ROOF_POWER_PWM_FREQUENCY>100) && ROOF_POWER_PWM_FREQUENCY != OFF
  #error "Configuration (Config.h): ROOF_POWER_PWM_FREQUENCY must be OFF or a number between 1 and 100 (Hz.)"
#endif

#if (ROOF_POWER_PWM_POWER<10 || ROOF_POWER_PWM_POWER>100) && ROOF_POWER_PWM_POWER != OFF
  #error "Configuration (Config.h): ROOF_POWER_PWM_POWER must be OFF or a number between 10 and 100 (%.)"
#endif

#if ROOF_POWER_PWM_SOFTSTART != OFF && ROOF_POWER_PWM_SOFTSTART != ON
  #error "Configuration (Config.h): ROOF_POWER_PWM_SOFTSTART must OFF or ON."
#endif

#if ROOF_MOTOR_RELAY_MOMENTARY == ON
  #if ROOF_POWER_RELAY != OFF
    #if ROOF_POWER_PWM_FREQUENCY != OFF
      #error "Configuration (Config.h): For ROOF_MOTOR_RELAY_MOMENTARY the setting ROOF_POWER_PWM_FREQUENCY must be OFF."
    #endif
    #if ROOF_POWER_PWM_POWER != OFF
      #error "Configuration (Config.h): For ROOF_MOTOR_RELAY_MOMENTARY the setting ROOF_POWER_PWM_POWER must be OFF."
    #endif
    #if ROOF_POWER_PWM_SOFTSTART != OFF
      #error "Configuration (Config.h): For ROOF_MOTOR_RELAY_MOMENTARY the setting ROOF_POWER_PWM_SOFTSTART must be OFF."
    #endif
  #endif
#endif

#if (ROOF_INTERLOCK_SENSE < 1 || ROOF_INTERLOCK_SENSE > 8) && ROOF_INTERLOCK_SENSE != OFF
  #error "Configuration (Config.h): ROOF_SENSE_INTERLOCK must be OFF or a number between 1 and 8 (SENSE#.)"
#endif

#if ROOF == ON && (ROOF_LIMIT_CLOSED_SENSE == OFF || ROOF_LIMIT_OPENED_SENSE == OFF)
  #error "Configuration (Config.h): Roof open and close limit sensors are both required if ROOF control is enabled."
#endif

#if (ROOF_LIMIT_CLOSED_SENSE < 1 || ROOF_LIMIT_CLOSED_SENSE > 8) && ROOF_LIMIT_CLOSED_SENSE != OFF
  #error "Configuration (Config.h): ROOF_SENSE_LIMIT_CLOSED must OFF or a number between 1 and 8 (SENSE#.)"
#endif

#if (ROOF_LIMIT_OPENED_SENSE < 1 || ROOF_LIMIT_OPENED_SENSE > 8) && ROOF_LIMIT_OPENED_SENSE != OFF
  #error "Configuration (Config.h): ROOF_SENSE_LIMIT_OPENED must OFF or a number between 1 and 8 (SENSE#.)"
#endif

#if ROOF_TIME_AVG < 30 || ROOF_TIME_AVG > 1200
  #error "Configuration (Config.h): ROOF_TIME_AVG must be a number between 30 and 1200 (seconds.)"
#endif

#if ROOF_TIME_TOL < 0 || ROOF_TIME_TOL > 120
  #error "Configuration (Config.h): ROOF_TIME_TOL must be a number between 0 and 120 (seconds.)"
#endif

#if ROOF_TIME_LIMIT_SENSE_FAIL < 1 || ROOF_TIME_LIMIT_SENSE_FAIL > 60
  #error "Configuration (Config.h): ROOF_TIME_LIMIT_SENSE_FAIL must be a number between 1 and 60 (seconds.)"
#endif

#if DOME == ON && AXIS1_DRIVER_MODEL == OFF
  #error "Configuration (Config.h): DOME ON requires an AXIS1_DRIVER_MODEL setting."
#endif

#if DOME == ON && !defined(DOME_PRESENT)
  #error "Configuration (Config.h): DOME, OCS website dome control display enabled but not setup."
#endif

#if DOME_SHUTTER_LOCK != OFF && DOME_SHUTTER_LOCK != ON
  #error "Configuration (Config.h): DOME_SHUTTER_LOCK must be either ON or OFF."
#endif

#if AXIS1_DRIVER_STATUS != OFF && AXIS1_DRIVER_STATUS != ON && AXIS1_DRIVER_STATUS != HIGH && AXIS1_DRIVER_STATUS != LOW
  #error "Configuration (Config.h): AXIS1_DRIVER_STATUS must be either ON, OFF, HIGH or LOW."
#endif

#if AXIS1_REVERSE != OFF && AXIS1_REVERSE != ON
  #error "Configuration (Config.h): AXIS1_REVERSE must be either ON or OFF."
#endif

#if AXIS1_SERVO_ENCODER != ENC_AB && AXIS1_SERVO_ENCODER != ENC_CW_CCW && \
    AXIS1_SERVO_ENCODER != ENC_PULSE_DIR && AXIS1_SERVO_ENCODER != ENC_PULSE_ONLY
  #error "Configuration (Config.h): AXIS1_SERVO_ENCODER must be either ENC_AB, ENC_CW_CCW, ENC_PULSE_DIR or ENC_PULSE_ONLY."
#endif

#if AXIS1_DRIVER_MODEL == OFF && AXIS2_DRIVER_MODEL != OFF
  #error "Configuration (Config.h): Enabling AXIS2_DRIVER_MODEL requires an AXIS1_DRIVER_MODEL setting."
#endif

#if AXIS1_POWER_DOWN != OFF && AXIS1_POWER_DOWN != ON
  #error "Configuration (Config.h): AXIS1_POWER_DOWN must be either ON or OFF."
#endif

#if AXIS1_WRAP != OFF && AXIS1_WRAP != ON
  #error "Configuration (Config.h): AXIS1_WRAP must be either ON or OFF."
#endif

#if AXIS1_LIMIT_MIN < -360 || AXIS1_LIMIT_MIN > 0
  #error "Configuration (Config.h): AXIS1_LIMIT_MIN must be between -360 and 0."
#endif

#if AXIS1_LIMIT_MAX < 0 || AXIS1_LIMIT_MAX > 360
  #error "Configuration (Config.h): AXIS1_LIMIT_MAX must be between 0 and 360."
#endif

#if AXIS1_SENSE_HOME != OFF && AXIS1_SENSE_HOME != HIGH && AXIS1_SENSE_HOME != LOW
  #error "Configuration (Config.h): AXIS1_SENSE_HOME must be either OFF, HIGH or LOW."
#endif

#if AXIS1_SENSE_LIMIT_MIN != OFF && AXIS1_SENSE_LIMIT_MIN != HIGH && AXIS1_SENSE_LIMIT_MIN != LOW
  #error "Configuration (Config.h): AXIS1_SENSE_LIMIT_MIN must be either OFF, HIGH or LOW."
#endif

#if AXIS1_SENSE_LIMIT_MAX != OFF && AXIS1_SENSE_LIMIT_MAX != HIGH && AXIS1_SENSE_LIMIT_MAX != LOW
  #error "Configuration (Config.h): AXIS1_SENSE_LIMIT_MAX must be either OFF, HIGH or LOW."
#endif

#if AXIS2_POWER_DOWN != OFF && AXIS2_POWER_DOWN != ON
  #error "Configuration (Config.h): AXIS2_POWER_DOWN must be either ON or OFF."
#endif

#if AXIS2_LIMIT_MIN < 0 || AXIS2_LIMIT_MIN > 90
  #error "Configuration (Config.h): AXIS2_LIMIT_MIN must be between 0 and 90."
#endif

#if AXIS2_LIMIT_MAX < 0 || AXIS2_LIMIT_MAX > 90
  #error "Configuration (Config.h): AXIS2_LIMIT_MAX must be between 0 and 90."
#endif

#if AXIS2_LIMIT_MIN >= AXIS2_LIMIT_MAX 
  #error "Configuration (Config.h): AXIS2_LIMIT_MIN must be < AXIS2_LIMIT_MAX."
#endif

#if AXIS2_SENSE_HOME != OFF && AXIS2_SENSE_HOME != HIGH && AXIS2_SENSE_HOME != LOW
  #error "Configuration (Config.h): AXIS2_SENSE_HOME must be either OFF, HIGH or LOW."
#endif

#if AXIS2_SENSE_LIMIT_MIN != OFF && AXIS2_SENSE_LIMIT_MIN != HIGH && AXIS2_SENSE_LIMIT_MIN != LOW
  #error "Configuration (Config.h): AXIS2_SENSE_LIMIT_MIN must be either OFF, HIGH or LOW."
#endif

#if AXIS2_SENSE_LIMIT_MAX != OFF && AXIS2_SENSE_LIMIT_MAX != HIGH && AXIS2_SENSE_LIMIT_MAX != LOW
  #error "Configuration (Config.h): AXIS2_SENSE_LIMIT_MAX must be either OFF, HIGH or LOW."
#endif
