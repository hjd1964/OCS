// ---------------------------------------------------------------------------------------------------------------------------------
// Configuration for the Observatory Control System (OCS)

/*
 *          For more information on setting the OCS up see http://www.stellarjourney.com/index.php?r=site/observatory_control
 *                      and join the OCS Groups.io at https://onstep.groups.io/g/onstep-ocs
*/

// For the Mega2560...

// Relay's are mapped to digital output pins: 23,25,27,29,31,33,35,37,39,41,43,45,47,49,xx,xx,xx,xx          (ON == HIGH, OFF = LOW)
//                                    Relay#:  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18

// Sense's are mapped to digital input pins:  22,24,26,28,30,32,xx,xx                   (HIGH == ON, LOW = OFF, internal PULLUP off)
//                                   Sense#:   1  2  3  4  5  6  7  8

// Analog inputs are mapped to pins:          A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15
//                                   Analog#:  1  2  3  4  5  6  7  8  9 10  11  12  13  14  15  16

// ---------------------------------------------------------------------------------------------------------------------------------
// ADJUST THE FOLLOWING TO CONFIGURE YOUR CONTROLLER FEATURES ----------------------------------------------------------------------
// <-Req'd = always must set, <-Often = usually must set, Option = optional, Adjust = adjust as req'd, Infreq = infrequently changed

// WATCHDOG SETTINGS ---------------------------------------------------------------------------------------------------------------
#define WATCHDOG                      OFF //    OFF, ON, ON_CC.  ON resets Mega2560 after 8 sec. if it hangs for any reason.  Option
                                          //         ON_CC as above and resets the Mega2560 if the connection check fails.

// TIME SETTINGS -------------------------------------------------------------------------------------------------------------------
#define TIME_LOCATION_SOURCE          NTP //    NTP, Network Time Protocol per IPAddress settings in Extended.config.h or use Adjust
                                          //          DS3234_RTC on default SPI interface (CS=53.) Upload once w/DS3234_INIT to set date/time.
#define TIME_ZONE                      -5 //     -5, Time Zone (US Eastern Standard Time in this case.)                      <-Req'd
#define TIME_DISPLAY                  LST //    LST, Display Standard Time, DST Daylight Time, UTC Universal Time.            Adjust

// STATUS PANEL FEATURES -----------------------------------------------------------------------------------------------------------
// See Misc.ino for user voltage and current conversion functions.
#define STAT_UNITS                 METRIC // METRIC, For metric units, or IMPERIAL for imperial units.                        Adjust

#define STAT_MAINS_SENSE              OFF //    OFF, n. Where n=1..8 (Sense#) mains power good, OFF (power failure) is UNSAFE Option
#define STAT_MAINS_CURRENT_ANALOG     OFF //    OFF, n. Where n=1..16 (Analog#) measure/display current mains.                Option
#define STAT_MAINS_AUX_CURRENT_ANALOG OFF //    OFF, n. Where n=1..16 (Analog#) measure/display current mains (aux.)          Option

// Converts the analog measure (range 0 to 1.0) to Amps
#define STAT_MAINS_ANALOG_TO_CURRENT(x) (x*NAN)

#define STAT_DC_VOLTAGE_ANALOG          1 //    OFF, n. Where n=1..16 (Analog#) measure/display 12VDC power supply voltage.   Option
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

#define WEATHER_SENSOR_WIND_REV_P     OFF //    OFF, n. Where n=1..16 (Analog#) to enable. Wind speed.                        Option

#define WEATHER_SENSOR_RAIN_GENERIC   OFF //    OFF, n. Where n=1..16 (Analog#) to enable.                                    Option
#define WEATHER_SENSOR_RAIN_LOW      0.25 //    OFF, n. Where n=0.0 to 1.0 for lower range below which is dry.                Option
#define WEATHER_SENSOR_RAIN_HIGH     0.75 //    OFF, n. Where n=0.0 to 1.0 for lower range below which is wet.                Option

#define WEATHER_SENSOR_CLOUD_MLX90614 OFF //    OFF, 0x5A (I2C Address) to enable. Gets IR sky IR temp. for cloud detection.  Adjust

#define WEATHER_SENSOR_SKYQ_TSL2591   OFF //    OFF, 0x28 (I2C Address) to enable. Sky brightness for sky quality estimate.   Option

// THERMOSTAT PANEL ----------------------------------------------------------------------------------------------------------------
#define THERMOSTAT                    OFF //    OFF, ON to enable the OCS website thermostat panel display.                   Option
#define HEAT_RELAY                    OFF //    OFF, n. Where n=1..18 (Relay#) for indoor heat.                               Option
#define COOL_RELAY                    OFF //    OFF, n. Where n=1..18 (Relay#) for cooling/venting.                           Option
#define THERMOSTAT_HUMIDITY           OFF //    OFF, ON displays indoor humidity.                                             Option

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

// LIGHTING PANEL ------------------------------------------------------------------------------------------------------------------
#define LIGHT                         OFF //    OFF, ON to enable the OCS website lighting panel display.                     Option
#define LIGHT_WRW_RELAY               OFF //    OFF, n. Where n=1..18 (Relay#) for Warm room white lights.                    Option
#define LIGHT_WRR_RELAY               OFF //    OFF, n. Where n=1..18 (Relay#) for Warm room red lights.                      Option
#define LIGHT_ORW_RELAY               OFF //    OFF, n. Where n=1..18 (Relay#) for Observing room white lights.               Option
#define LIGHT_ORR_RELAY               OFF //    OFF, n. Where n=1..18 (Relay#) for Observing room red lights.                 Option
#define LIGHT_OUTSIDE_RELAY           OFF //    OFF, n. Where n=1..18 (Relay#) for Outside flood.                             Option
#define LIGHT_SW_SENSE                OFF //    OFF, n. Where n=1..8 (Sense#) for switch to turn WRW lights on/off.           Option

// ROOF/SHUTTER CONTROL PANEL ------------------------------------------------------------------------------------------------------
#define ROOF_USER_SAFETY_OVERRIDE     OFF //    OFF, ON displays safety override button.                                      Option
#define ROOF                          OFF //    OFF, ON to enable the OCS website roof/shutter panel display.                 Option

#define ROOF_AUTOCLOSE_DAWN           OFF //    OFF, ON displays option to automatically close roof at dawn.                  Option
#define ROOF_AUTOCLOSE_DAWN_DEFAULT   OFF //    OFF, ON enables AUTOCLOSE_DAWN option at startup, disabled otherwise.         Option
#define ROOF_AUTOCLOSE_SAFETY         OFF //    OFF, ON closes the roof automatically if an UNSAFE condition is detected.     Option

#define ROOF_MOTOR_OPEN_RELAY         OFF //    OFF, n. Where n=1..18 (Relay#) engages this relay to open roof.               Option
#define ROOF_MOTOR_CLOSE_RELAY        OFF //    OFF, n. Where n=1..18 (Relay#) engages this relay to close roof.              Option
#define ROOF_MOTOR_RELAY_MOMENTARY    OFF //    OFF, ON engage above momentarily (~1.5s) to start an automatic open or close. Option
#define ROOF_MOTOR_STOP_RELAY         OFF //    OFF, n. Where n=1..18 (Relay#) momentarily engages this relay to stop roof.   Option

#define ROOF_POWER_RELAY              OFF //    OFF, n. Where n=1..18 (Relay#) This controls roof motor power. For DC motors  Option
                                          //         SSR/MOSFET PWM controls speed. For garage door openers etc SW on/off only.
#define ROOF_POWER_PWM_FREQUENCY      OFF //    OFF, n. Where n=1..100 (Hz) PWM frequency for roof motor DC control.          Option
#define ROOF_POWER_PWM_POWER          OFF //    OFF, n. Where n=10..100 (%) PWM power level for roof motor DC control.        Option
#define ROOF_POWER_PWM_SOFTSTART      OFF //    OFF, ON For PWM soft start, start 0% adds 5%/sec until ROOF_POWER_PWM_POWER.  Option

#define ROOF_INTERLOCK_SENSE          OFF //    OFF, n. Where n=1..8 (Sense#) Roof safety interlock, close allowed when ON.   Option
#define ROOF_LIMIT_CLOSED_SENSE       OFF //    OFF, n. Where n=1..8 (Sense#) Roof closed switch (CLOSED when ON.)            Option
#define ROOF_LIMIT_OPENED_SENSE       OFF //    OFF, n. Where n=1..8 (Sense#) Roof open switch (OPEN when ON.)                Option

#define ROOF_TIME_AVG                 300 //    300, n. Where n=30..1200 (seconds) Average time to open or close roof.        Adjust
#define ROOF_TIME_TOL                  30 //     30, n. Where n=0..120 (seconds) Additional time before stop & error thrown.  Adjust
#define ROOF_TIME_LIMIT_SENSE_FAIL      6 //      6, n. Where n=1..60 (seconds) Time to limit switch disengage failure error. Adjust

// DOME CONTROL PANEL --------------------------------------------------------------------------------------------------------------

#define DOME                          OFF //    OFF, ON to enable the OCS website dome panel display.                         Option

// Driver models (Step/Dir and Servo) see "~/OCS/Constants.h" for a complete list.
// Usually this will be a GENERIC stepper driver or a servo SERVO_PD (pulse/direction) or SERVO_II (in/in.)

#define DOME_DRIVER_MODEL             OFF //    OFF, Enter driver model (above) to activate the dome.                         Option
#define DOME_DRIVER_STATUS            OFF //    OFF, ON, HIGH, or LOW.  For driver status info/fault detection.               Option

#define DOME_DRIVER_MICROSTEPS        OFF //    OFF, n. Microstep mode when tracking.                                         Option

#define DOME_STEPS_PER_DEGREE        64.0 //   64.0, n. Number of steps per degree for dome.                                  Adjust
#define DOME_SLEW_RATE_DESIRED        1.0 //    1.0, n, (degrees/second) Maximum speed depends on processor.                  Adjust
#define DOME_REVERSE                  OFF //    OFF, ON Reverses movement direction, or reverse wiring instead to correct.    Option

// for SERVO_II and SERVO_SD driver models, PID and encoder settings:
#define DOME_SERVO_P                  2.0 //    2.0, Proportional; scale of immediate response to position error.             Adjust 
#define DOME_SERVO_I                  5.0 //    5.0, Integral; rate of increasing response to position error over time.       Adjust
#define DOME_SERVO_D                  1.0 //    1.0, Derivative; overshoot supression.                                        Adjust
#define DOME_SERVO_ENCODER         ENC_AB // ..._AB, Encoder type, ENC_AB, ENC_CW_CCW, ENC_PULSE_DIR, ENC_PULSE_ONLY.         Adjust

#define DOME_POWER_DOWN               OFF //    OFF, ON Powers off 30sec after movement stops or 10min after last<=1x guide.  Option

#define DOME_WRAP                     OFF //    OFF, ON Allows unlimited Azm range and ignores min/max limits.                Option

#define DOME_LIMIT_MIN               -180 //   -180, n. Where n= -90..-360 (degrees.) Minimum Azimuth.                        Adjust
#define DOME_LIMIT_MAX                180 //    180, n. Where n=  90.. 360 (degrees.) Maximum Azimuth.                        Adjust

#define DOME_SENSE_HOME               OFF //    OFF, HIGH or LOW enables & state clockwise home position, as seen from front. Option
#define DOME_SENSE_LIMIT_MIN          OFF //    OFF, HIGH or LOW state on limit sense switch stops movement.                  Option
#define DOME_SENSE_LIMIT_MAX          OFF //    OFF, HIGH or LOW state on limit sense switch stops movement.                  Option
                                          //         Digital, optionally add: |HYST(n) Where n=0..1023 stability time in ms.
                                          //         Analog capable sense inputs also allow adding:
                                          //         |THLD(n) Where n=1..1023 (ADU) for Analog threshold.
                                          //         |HYST(n) Where n=0..1023 (ADU) for +/- Hystersis range.

#define FileVersionConfig 2
