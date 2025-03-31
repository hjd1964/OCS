/* ---------------------------------------------------------------------------------------------------------------------------------
 * Configuration for the Observatory Control System (OCS)
 *
 *
 *          For more information on setting the OCS up see http://www.stellarjourney.com/index.php?r=site/observatory_control
 *                      and join the OCS Groups.io at https://onstep.groups.io/g/onstep-ocs
 *
 *
 *         ***   _RELAY and _SENSE numbers are mapped to pins in a platform specific pinmap, see: /src/pinmaps      ***
 *         ***                            Additional settings are present in /src/Config.defaults.h                 ***
 *
 * ---------------------------------------------------------------------------------------------------------------------------------
 * ADJUST THE FOLLOWING TO CONFIGURE YOUR CONTROLLER FEATURES ----------------------------------------------------------------------
 * <-Req'd = always must set, <-Often = usually must set, Option = optional, Adjust = adjust as req'd, Infreq = infrequently changed
*/
//      Parameter Name              Value   Default  Notes                                                                      Hint

// =================================================================================================================================
// CONTROLLER ======================================================================================================================

#define HOST_NAME                   "OCS" //  "OCS", This devices name up to 16 chars.                                        Adjust

// PINMAP --------------------------------------------------------------------------------------------------------------------------
#define PINMAP                        OFF //    OFF, Choose from: LEGACY, OCS1, OCS2, OCS3, OCS4, OCS_ESP1, OCS_ESP2.        <-Req'd
                                          //         Other boards/more info. in /src/Constants.h

// SERIAL PORT COMMAND CHANNELS ----------------------------------------------------------------------------------------------------
#define SERIAL_A_BAUD_DEFAULT        9600 //   9600, n. Where n=9600,19200,57600,115200 (common baud rates.)                  Infreq
#define SERIAL_B_BAUD_DEFAULT         OFF //    OFF, n. Where n=9600,19200,57600,115200 (common baud rates.)                  Option
#define SERIAL_C_BAUD_DEFAULT         OFF //    OFF, n. Where n=9600,19200,57600,115200 (common baud rates.)                  Option

// DISPLAY -------------------------------------------------------------------------------------------------------------------------
#define DISPLAY_LANGUAGE             L_en //   L_en, English. L_en, L_us (for IMPERIAL units) two letter country code.        Adjust
#define CAMERA_WEBPAGE                 "" //     "", To enable add string with web address to camera image display page.      Adjust

// WATCHDOG SETTINGS ---------------------------------------------------------------------------------------------------------------
#define WATCHDOG                      OFF //    OFF, ON resets OCS after 8 sec. if it hangs for (nearly) any reason.          Option

// NETWORK SETTINGS ----------------------------------------------------------------------------------------------------------------
#define ASCOM_ALPACA_SERVER           OFF //    OFF, ON enables ASCOM Alpaca server on port 10000, requires W5500 Ethernet.   Option
                                          //         Note: this disables the IP command servers on ports 9998, 9999 and
                                          //         works best w/my Ethernet library from: https://github.com/hjd1964/Ethernet
#define CONNECT_CHECK_HOURS           OFF //    OFF, n. Where n=1 to 48 (hours.)  Connection check time.                      Option
#define CONNECT_IP_ADDR    {13,226,22,41} //         Default is Arduino.cc. Needs ETHERNET_RESET_PIN and/or WATCHDOG to reset.
#define CONNECT_FAIL_WATCHDOG         OFF //    OFF, ON to stop all processing and trigger the watchdog reset.                Option

// TIME SETTINGS -------------------------------------------------------------------------------------------------------------------
#define TIME_LOCATION_SOURCE          NTP //    NTP, Network Time Protocol w/IP address settings below, or DS3231 (I2C),      Adjust
                                          //         SD3031 (I2C), DS3234 (SPI), TEENSY.
#define TIME_IP_ADDR        {129,6,15,28} // ...6,15,28}, time-a-g.nist.gov at 129,6,15,28 or 129,6,15,29, 129,6,15,30, etc.  Option
#define TIME_ZONE                      -5 //     -5, Time Zone (US Eastern Standard Time in this case.)                      <-Req'd
#define TIME_DISPLAY                  STD //    STD, Display Standard Time, UT1 to display Universal Time.                    Adjust

// STATUS PANEL FEATURES -----------------------------------------------------------------------------------------------------------
#define STAT                          OFF //    OFF, ON to enable the OCS website status panel display.                       Option

#define STAT_MAINS_SENSE              OFF //    OFF, n. Where n=1..8 (Sense#) mains power good, OFF (power failure) is UNSAFE Option
#define STAT_MAINS_CURRENT_ANALOG     OFF //    OFF, n. Where n=1..16 (Analog#) measure/display current mains.                Option
#define STAT_MAINS_AUX_CURRENT_ANALOG OFF //    OFF, n. Where n=1..16 (Analog#) measure/display current mains (aux.)          Option
#define STAT_MAINS_SAFETY_DELAY       OFF //    OFF, n. Where n=1..600 (s). Mains safety sense delay time.                    Option

// Converts the analog measure (range 0 to 1.0) to Amps
#define STAT_MAINS_ANALOG_TO_CURRENT(x) (x*NAN)

#define STAT_DC_VOLTAGE_ANALOG        OFF //    OFF, n. Where n=1..16 (Analog#) measure/display 12VDC power supply voltage.   Option
#define STAT_DC_CURRENT_ANALOG        OFF //    OFF, n. Where n=1..16 (Analog#) measure/display 12VDC power supply current.   Option

#define STAT_BATTERY_VOLTAGE_ANALOG   OFF //    OFF, n. Where n=1..16 (Analog#) measure/display 12V roof battery voltage.     Option
#define STAT_BATTERY_CURRENT_ANALOG   OFF //    OFF, n. Where n=1..16 (Analog#) measure/display 12V roof battery current.     Option

// Converts the analog measure (range 0 to 1.0) to Volts
#define STAT_DC_ANALOG_TO_VOLTAGE(x) (x*NAN)

// Converts the analog measure (range 0 to 1.0) to Amps
#define STAT_DC_ANALOG_TO_CURRENT(x) (x*NAN)

#define STAT_PROCESSOR_RAM            OFF //    OFF, ON for display of Processor free RAM resources. Mega2560 only.           Option

// POWER PANEL ---------------------------------------------------------------------------------------------------------------------
#define POWER                         OFF //    OFF, ON to enable the OCS website power panel display.                        Option

#define POWER_DEVICE1_RELAY           OFF //    OFF, n. Where n=1..18 (Relay#) with _NAME below.                              Option
#define POWER_DEVICE1_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE1_NAME ""

#define POWER_DEVICE2_RELAY           OFF //    OFF, n. Where n=1..18 (Relay#) with _NAME below.                              Option
#define POWER_DEVICE2_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE2_NAME ""

#define POWER_DEVICE3_RELAY           OFF //    OFF, n. Where n=1..18 (Relay#) with _NAME below.                              Option
#define POWER_DEVICE3_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE3_NAME ""

#define POWER_DEVICE4_RELAY           OFF //    OFF, n. Where n=1..18 (Relay#) with _NAME below.                              Option
#define POWER_DEVICE4_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE4_NAME ""

#define POWER_DEVICE5_RELAY           OFF //    OFF, n. Where n=1..18 (Relay#) with _NAME below.                              Option
#define POWER_DEVICE5_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE5_NAME ""

#define POWER_DEVICE6_RELAY           OFF //    OFF, n. Where n=1..18 (Relay#) with _NAME below                               Option
#define POWER_DEVICE6_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE6_NAME ""

// LIGHTING PANEL ------------------------------------------------------------------------------------------------------------------
#define LIGHT                         OFF //    OFF, ON to enable the OCS website lighting panel display.                     Option

#define LIGHT_WRW_RELAY               OFF //    OFF, n. Where n=1..18 (Relay#) for Warm room white lights.                    Option
#define LIGHT_WRR_RELAY               OFF //    OFF, n. Where n=1..18 (Relay#) for Warm room red lights.                      Option
#define LIGHT_ORW_RELAY               OFF //    OFF, n. Where n=1..18 (Relay#) for Observing room white lights.               Option
#define LIGHT_ORR_RELAY               OFF //    OFF, n. Where n=1..18 (Relay#) for Observing room red lights.                 Option
#define LIGHT_OUTSIDE_RELAY           OFF //    OFF, n. Where n=1..18 (Relay#) for Outside flood.                             Option

#define LIGHT_STRIP_DATA_PIN          OFF //    OFF, n. GPIO pin to LED controller chips (default WS2811GRB)                  Option
#define LIGHT_STRIP_COUNT              16 //     16, n. Where n=1..1000 LED controller chip count                             Option
#define LIGHT_STRIP_WR_RANGE        {0,7} //  {0,7}, n,n. Where n=0..LIGHT_STRIP_COUNT-1 ID range for Warm room               Option
#define LIGHT_STRIP_OR_RANGE       {8,15} // {8,15}, n,n. Where n=0..LIGHT_STRIP_COUNT-1 LED ID for Observing room            Option

#define LIGHT_SW_SENSE                OFF //    OFF, n. Where n=1..8 (Sense#) for switch to turn warm room lights on/off.     Option

// WEATHER PANEL -------------------------------------------------------------------------------------------------------------------
// Weather and Sky Conditions web page charts use "Chart.js" http://www.chartjs.org/. Specifically, version 2.5 of "Chart.min.js"
//   renamed to "Chart.js" and placed in the Micro SD card root directory (Fat32 formatted) and inserted into the W5100 Ethernet
//   adapter.  Downloaded from here https://github.com/chartjs/Chart.js/releases/tag/v2.5.0 (page bottom for download links.)
#define WEATHER                       OFF //    OFF, ON to enable the OCS website weather panel display.                      Option
#define WEATHER_CHARTS                OFF //    OFF, ON for logging and display of weather data graphic charts.               Option

#define WEATHER_TEMPERATURE           OFF //    OFF, ON for measuring outside temperature.                                    Option

#define WEATHER_PRESSURE              OFF //    OFF, ON for measuring barometric pressure.                                    Option
#define WEATHER_NOMINAL_PRESSURE     1010 //   1010, n. Where n=500..1050 (in mb) site nominal pressure for Chart.            Adjust
#define WEATHER_ALTITUDE              100 //    100, n. Where n=-86..5000 (meters) site altitude.                             Adjust

#define WEATHER_HUMIDITY              OFF //    OFF, ON for measuring outside humidity.                                       Option

#define WEATHER_WIND_SPD              OFF //    OFF, ON for measuring wind speed.                                             Option
#define WEATHER_WIND_SPD_THRESHOLD     20 //     20, n. Where n=0..100 (in kph) wind speed above this is considered UNSAFE.   Adjust

#define WEATHER_RAIN                  OFF //    OFF, ON to enable rain sensor, a "wet" condition is considered to be UNSAFE.  Option

#define WEATHER_CLOUD_CVR             OFF //    OFF, ON to enable the cloud sensor, above WEATHER_SAFE_THRESHOLD is UNSAFE.   Option
#define WEATHER_SAFE_THRESHOLD        -14 //    -14, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_VCLR_THRESHOLD        -19 //    -19, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_CLER_THRESHOLD        -17 //    -17, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_HAZE_THRESHOLD        -14 //    -14, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_OVRC_THRESHOLD        -11 //    -11, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_CLDY_THRESHOLD         -8 //     -8, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_VCLD_THRESHOLD         -5 //     -5, n. Where n=-25..0 (in Deg. C)                                            Adjust

#define WEATHER_SKY_QUAL              OFF //    OFF, ON for measuring sky quality (darkness in magnitudes per sq arc-sec.)    Option

// WEATHER SENSORS ----------------------
#define WEATHER_SENSOR_TPH_BME280     OFF //    OFF, 0x76 or 0x77 (I2C Address) to enable. Temperature, pressure, humidity.   Option

#define WEATHER_SENSOR_TP_BMP280      OFF //    OFF, 0x76 or 0x77 (I2C Address) to enable. Temperature, pressure.             Option

#define WEATHER_SENSOR_TP_BMP085      OFF //    OFF, 0x77 (I2C Address) to enable. Temperature, pressure. For BMP180 also.    Option

#define WEATHER_SENSOR_TH_DHT         OFF //    OFF, n. Where n=1..8 (Sense#) to enable. Temperature, humidity.               Option
// DHT device type DHT11, or DHT21, DHT22
#define WEATHER_SENSOR_TH_DHT_TYPE  DHT11

#define WEATHER_SENSOR_TH_SI7021      OFF //    OFF, 0x40 (I2C Address) to enable. Temperature, humidity.                     Option

#define WEATHER_SENSOR_T_ANALOG       OFF //    OFF, n. Where n=1..16 (Analog#) to enable.                                    Option
// Conversion factor, analog range 0 to 1.0 (x) to Deg. C; example TMP36 device 0.1V (-40°C) to 2.0V (150°C) w/3.3V MCU
#define WEATHER_SENSOR_T_ANALOG2DEGC(x) (((x*3.3)-0.1)*100.0-40.0)

#define WEATHER_SENSOR_WIND_CUP       OFF //    OFF, n. Where n=1..8 (Sense#) to enable. Wind speed, cup anemometer.          Option
// Conversion factor, pulses per minute (x) to wind speed in KPH
#define WEATHER_SENSOR_WIND_CUP2KPH(x) (x*0.087)
#define WEATHER_SENSOR_WIND_EDGE  FALLING //    RISING or FALLING. Pulse edge to detect.                                      Adjust
#define WEATHER_SENSOR_WIND_CUP_DB    OFF //    OFF, n. Where n=1..100 (ms) Wind Cup input debounce time.                     Option

#define WEATHER_SENSOR_WIND_REV_P     OFF //    OFF, n. Where n=1..16 (Analog#) to enable. Wind speed.                        Option

#define WEATHER_SENSOR_RAIN_GENERIC   OFF //    OFF, n. Where n=1..16 (Analog#) to enable.                                    Option
#define WEATHER_SENSOR_RAIN_LOW      0.25 //   0.25, n. Where n=0.0 to 1.0 for lower range below which is dry.                Option
#define WEATHER_SENSOR_RAIN_HIGH     0.75 //   0.75, n. Where n=0.0 to 1.0 for lower range below which is wet.                Option

#define WEATHER_SENSOR_RAIN_DIGITAL   OFF //    OFF, n. Where n=1..8 (Sense#) to enable.  e.g. Kemo M152K or Hydreon RG-9     Option

#define WEATHER_SENSOR_CLOUD_MLX90614 OFF //    OFF, 0x5A (I2C Address) to enable. Gets IR sky IR temp. for cloud detection.  Adjust

#define WEATHER_SENSOR_SKYQ_TSL2591   OFF //    OFF, 0x28 (I2C Address) to enable. Sky brightness for sky quality estimate.   Option

// THERMOSTAT PANEL ----------------------------------------------------------------------------------------------------------------
#define THERMOSTAT                    OFF //    OFF, ON to enable the OCS website thermostat panel display.                   Option
#define HUMIDITY_RELAY                OFF //    OFF, n. Where n=1..18 (Relay#) for dehumidifying.                             Option
#define HEAT_RELAY                    OFF //    OFF, n. Where n=1..18 (Relay#) for indoor heat.                               Option
#define COOL_RELAY                    OFF //    OFF, n. Where n=1..18 (Relay#) for cooling/venting.                           Option
#define THERMOSTAT_HUMIDITY           OFF //    OFF, ON displays indoor humidity.                                             Option
#define CONTROL_WITH_ROOF_OPEN        OFF //    OFF, ON Heat/cool/dehumidify control whilst roof is open                      Option

// THERMOSTAT SENSORS -------------------
#define THERMOSTAT_SENSOR_TPH_BME280  OFF //    OFF, 0x76 or 0x77 (I2C Address) to enable. Temperature, pressure, humidity.   Option

#define THERMOSTAT_SENSOR_TP_BMP280   OFF //    OFF, 0x76 or 0x77 (I2C Address) to enable. Temperature, pressure.             Option

#define THERMOSTAT_SENSOR_TP_BMP085   OFF //    OFF, 0x77 (I2C Address) to enable. Temperature, pressure. For BMP180 also.    Option

#define THERMOSTAT_SENSOR_TH_DHT      OFF //    OFF, n. Where n=1..8 (Sense#) to enable. Temperature, humidity.               Option
// DHT device type DHT11, or DHT21, DHT22
#define THERMOSTAT_SENSOR_TH_DHT_TYPE DHT11

#define THERMOSTAT_SENSOR_TH_SI7021   OFF //    OFF, 0x40 (I2C Address) to enable. Temperature, humidity.                     Option

#define THERMOSTAT_SENSOR_T_ANALOG    OFF //    OFF, n. Where n=1..16 (Analog#) to enable.                                    Option
// Conversion factor, analog (x ranges from 0 to 1.0) to Deg. C; example TMP36 0.1V (-40°C) to 2.0V (150°C) w/3.3V MCU
#define THERMOSTAT_SENSOR_T_ANALOG2DEGC(x) (((x*3.3)-0.1)*100.0-40.0)

// ROOF/SHUTTER CONTROL PANEL ------------------------------------------------------------------------------------------------------
#define ROOF                          OFF //    OFF, ON to enable the OCS website roof/dome shutter panel display.            Option
#define ROOF_USER_SAFETY_OVERRIDE     OFF //    OFF, ON displays safety override button.                                      Option

#define ROOF_AUTOCLOSE_DAWN           OFF //    OFF, ON displays option to automatically close roof at dawn.                  Option
#define ROOF_AUTOCLOSE_DAWN_DEFAULT   OFF //    OFF, ON enables AUTOCLOSE_DAWN option at startup, disabled otherwise.         Option
#define ROOF_AUTOCLOSE_SAFETY         OFF //    OFF, ON closes the roof automatically if an UNSAFE condition is detected.     Option
#define ROOF_CLOSE_PARKS_MOUNT        OFF //    OFF, n. Where n=1..18 (Relay#) momentarily engages this relay to park mount.  Option

#define ROOF_MOTOR_OPEN_RELAY         OFF //    OFF, n. Where n=1..18 (Relay#) engages this relay to open roof.               Option
#define ROOF_MOTOR_CLOSE_RELAY        OFF //    OFF, n. Where n=1..18 (Relay#) engages this relay to close roof.              Option
#define ROOF_MOTOR_PRESS_TIME         1.5 //    1.5, n. Where n=1..10 (seconds) For garage door openers.                      Infreq
#define ROOF_MOTOR_RELAY_MOMENTARY    OFF //    OFF, ON engage momentarily (_PRESS_TIME) to start an automatic open or close. Option
#define ROOF_MOTOR_STOP_RELAY         OFF //    OFF, n. Where n=1..18 (Relay#) momentarily engages this relay to stop roof.   Option

#define ROOF_POWER_RELAY              OFF //    OFF, n. Where n=1..18 (Relay#) This controls roof motor power. For DC motors  Option
                                          //         SSR/MOSFET PWM controls speed. For garage door openers etc SW on/off only.
#define ROOF_POWER_PWM_FREQUENCY      OFF //    OFF, n. Where n=1..100 (Hz) PWM frequency for roof motor DC control.          Option
#define ROOF_POWER_PWM_POWER          OFF //    OFF, n. Where n=10..100 (%) PWM power level for roof motor DC control.        Option
#define ROOF_POWER_PWM_SOFTSTART      OFF //    OFF, ON For PWM soft start, start 0% adds 5%/sec until ROOF_POWER_PWM_POWER.  Option

#define ROOF_LIMIT_OPENED_SENSE       OFF //    OFF, n. Where n=1..8 (Sense#) Roof open switch (OPEN when ON.)                Option
#define ROOF_LIMIT_CLOSED_SENSE       OFF //    OFF, n. Where n=1..8 (Sense#) Roof closed switch (CLOSED when ON.)            Option
#define ROOF_LIMIT_SENSE_FAIL_TIME      6 //      6, n. Where n=1..60 (seconds) Time to limit switch disengage failure error. Infreq
#define ROOF_INTERLOCK_SENSE          OFF //    OFF, n. Where n=1..8 (Sense#) Roof safety interlock, motion allowed when ON.  Option
#define ROOF_INTERLOCK_PRE_MOVE_TIME  1.5 //    1.5, n. Where n=1..10 (seconds) For roof open interlock sense.                Infreq
#define ROOF_INTERLOCK_POST_MOVE_TIME 2.0 //    2.0, n. Where n=1..10 (seconds) For roof close interlock sense.               Infreq

#define ROOF_TIME_AVG                 300 //    300, n. Where n=30..1200 (seconds) Average time to open or close roof.        Adjust
#define ROOF_TIME_TOL                  30 //     30, n. Where n=0..120 (seconds) Additional time before stop & error thrown.  Adjust
#define MOUNT_PARK_TIMEOUT             30 //     30, n. Where n=20..480 (seconds) Maximum time to park mount before error.    Adjust

// DOME CONTROL PANEL --------------------------------------------------------------------------------------------------------------
#define DOME                          OFF //    OFF, ON to enable the OCS website dome panel display.                         Option

#define DOME_SHUTTER_LOCK             OFF //    OFF, ON to disable dome motion unless shutter is open.                        Option

// Usually this will be a GENERIC stepper driver or a servo SERVO_PE (Phase/Enable) or SERVO_EE (Enable/Enable)
#define AXIS1_DRIVER_MODEL            OFF //    OFF, Enter driver model (above) to activate the dome Azimuth axis.            Option
#define AXIS1_DRIVER_MICROSTEPS       OFF //    OFF, n. Microstep mode when tracking.                                         Option
#define AXIS1_DRIVER_STATUS           OFF //    OFF, ON, HIGH, or LOW.  For driver status info/fault detection.               Option

// for SERVO_PE and SERVO_EE driver models, encoder and PID settings:
#define AXIS1_ENCODER                 OFF //    OFF, AB, CW_CCW, PULSE_DIR, PULSE_ONLY, SERIAL_BRIDGE.                        Option
#define AXIS1_PID_P                   2.0 //    2.0, Proportional; scale of immediate response to position error.             Adjust
#define AXIS1_PID_I                   5.0 //    5.0, Integral; rate of increasing response to position error over time.       Adjust
#define AXIS1_PID_D                   1.0 //    1.0, Derivative; overshoot supression.                                        Adjust

#define AXIS1_SLEW_RATE_DESIRED       1.0 //    1.0, n, (degrees/second) Maximum speed depends on processor.                  Adjust

#define AXIS1_STEPS_PER_DEGREE       60.0 //   60.0, n. Number of steps per degree for dome.                                  Adjust
#define AXIS1_REVERSE                 OFF //    OFF, ON Reverses movement direction, or reverse wiring instead to correct.    Option
#define AXIS1_POWER_DOWN              OFF //    OFF, ON Powers off 30sec after movement stops or 10min after last<=1x guide.  Option

#define AXIS1_LIMIT_MIN              -180 //   -180, n. Where n= 0..-360 (degrees.) Minimum Azimuth.                          Adjust
#define AXIS1_LIMIT_MAX               180 //    180, n. Where n= 0.. 360 (degrees.) Maximum Azimuth.                          Adjust

#define AXIS1_SENSE_HOME              OFF //    OFF, HIGH or LOW enables & state clockwise home position, as seen from front. Option
#define AXIS1_SENSE_LIMIT_MIN         OFF //    OFF, HIGH or LOW state on limit sense switch stops movement.                  Option
#define AXIS1_SENSE_LIMIT_MAX         OFF //    OFF, HIGH or LOW state on limit sense switch stops movement.                  Option
                                          //         Digital, optionally add: |HYST(n) Where n=0..1023 stability time in ms.
                                          //         Analog capable sense inputs also allow adding:
                                          //         |THLD(n) Where n=1..1023 (ADU) for Analog threshold.
                                          //         |HYST(n) Where n=0..1023 (ADU) for +/- Hystersis range.

#define AXIS1_WRAP                    OFF //    OFF, ON Allows unlimited Azm range and ignores min/max limits.                Option

#define AXIS2_DRIVER_MODEL            OFF //    OFF, Enter driver model to activate the (optional) dome Altitude axis.        Option
#define AXIS2_DRIVER_MICROSTEPS       OFF //    OFF, n. Microstep mode when tracking.                                         Option
#define AXIS2_DRIVER_STATUS           OFF //    OFF, ON, HIGH, or LOW.  For driver status info/fault detection.               Option

// for SERVO_PE and SERVO_EE driver models, encoder and PID settings:
#define AXIS2_ENCODER                 OFF //    OFF, AB, CW_CCW, PULSE_DIR, PULSE_ONLY, SERIAL_BRIDGE.                        Option
#define AXIS2_PID_P                   2.0 //    2.0, Proportional; scale of immediate response to position error.             Adjust
#define AXIS2_PID_I                   5.0 //    5.0, Integral; rate of increasing response to position error over time.       Adjust
#define AXIS2_PID_D                   1.0 //    1.0, Derivative; overshoot supression.                                        Adjust

#define AXIS2_SLEW_RATE_DESIRED       1.0 //    1.0, n, (degrees/second) Maximum speed depends on processor.                  Adjust

#define AXIS2_STEPS_PER_DEGREE       60.0 //   60.0, n. Number of steps per degree for dome.                                  Adjust
#define AXIS2_REVERSE                 OFF //    OFF, ON Reverses movement direction, or reverse wiring instead to correct.    Option
#define AXIS2_POWER_DOWN              OFF //    OFF, ON Powers off 30sec after movement stops or 10min after last<=1x guide.  Option

#define AXIS2_LIMIT_MIN                 0 //      0, n. Where n=  0..90 (degrees.) Minimum Altitude.                          Adjust
#define AXIS2_LIMIT_MAX                90 //     90, n. Where n=  0..90 (degrees.) Maximum Altitude.                          Adjust

#define AXIS2_SENSE_HOME              OFF //    OFF, HIGH or LOW enables & state clockwise home position, as seen from front. Option
#define AXIS2_SENSE_LIMIT_MIN         OFF //    OFF, HIGH or LOW state on limit sense switch stops movement.                  Option
#define AXIS2_SENSE_LIMIT_MAX         OFF //    OFF, HIGH or LOW state on limit sense switch stops movement.                  Option

#define FileVersionConfig 2
#include "Extended.config.h"
