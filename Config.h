// ---------------------------------------------------------------------------------------------------------------------------------
// Configuration for the Observatory Control System (OCS)

/*
 *          For more information on setting the OCS up see http://www.stellarjourney.com/index.php?r=site/observatory_control
 *                      and join the OCS Groups.io at https://onstep.groups.io/g/onstep-ocs
*/

// Relay's are mapped to digital output pins: 23,25,27,29,31,33,35,37,39,41,43,45,47,49  (ON == HIGH, OFF = LOW, see OCS.ino)
//                                    Relay#:  1  2  3  4  5  6  7* 8* 9*10*11*12*13*14* (* = has PWM support if Solid State Relays)

// Sense's are mapped to digital input pins: 22,24,26,28,30,32 (HIGH == ON, LOW = OFF, internal PULLUP off, see OCS.ino to change)
//                                   Sense#:  1  2  3  4  5  6

// Analog inputs are not mapped (they are at their Arduino defined pin#'s)
//                                   Analog: A0, A1, A2, A3, A4, A5

// Note: pins 4, 10, 50, 51, 52, 53 are used for the W5100 Ethernet (SPI & 10), SD card (SPI & 4), and DS3234 RTC (SPI & 53)

// ---------------------------------------------------------------------------------------------------------------------------------
// ADJUST THE FOLLOWING TO CONFIGURE YOUR CONTROLLER FEATURES ----------------------------------------------------------------------
// <-Req'd = always must set, <-Often = usually must set, Option = optional, Adjust = adjust as req'd, Infreq = infrequently changed

// NETWORK SETTINGS ----------------------------------------------------------------------------------------------------------------
//      Parameter Name              Value   Default  Notes                                                                      Hint
#define RESPONSE_INTERVAL            1000 //   1000, n. Where n=500..10000 (ms.) Default for LAN latency, Internet use 5000.  Option
#define ETHERNET_RESET                OFF //    OFF, n. Where n=unused Mega2560 pin #, activates feature and allows the OCS   Infreq
                                          //         to force an reset of the W5100 Ethernet Shield at startup using this pin.
                                          //         W5100 reset pin must be connected to the pin# specified here and no other.
byte m[]={0xDE,0xAD,0xBE,0xEF,0xFE,0xEF}; // ..0xEF, The unique MAC address for your OCS.                                    <-Req'd
IPAddress ip(192, 168, 1, 50);            // ..1.50, The unique IP address for your OCS.                                     <-Req'd
IPAddress myDns(192,168, 1, 1);           //  ..1.1, DNS server address for network name resolution, usually an access-point.<-Req'd
IPAddress gateway(192, 168, 1, 1);        //  ..1.1, Gateway to wider internet, usually an access-point.                     <-Req'd
IPAddress subnet(255, 255, 255, 0);       //..255.0, Network bit-mask, determines which addresses are local.                  Infreq
IPAddress timeServer(216, 239, 35, 0);    // ..35.0, time.google.com (216.239.35.0) or time-a.timefreq.bldrdoc.gov at         Option
                                          //         132.163.4.101, 132.163.4.102, 132.163.4.103, etc.

// TIME SETTINGS -------------------------------------------------------------------------------------------------------------------
#define TIME_ZONE                      -5 //     -5, Time Zone (US Eastern Standard Time in this case.)                      <-Req'd
#define TIME_DISPLAY                  LST //    LST, Display Standard Time, DST Daylight Time, UTC Universal Time.            Adjust

// STATUS PANEL FEATURES -----------------------------------------------------------------------------------------------------------
// See Misc.ino for user voltage and current conversion functions.
#define STAT_UNITS                 METRIC // METRIC, For metric units, or IMPERIAL for imperial units.                        Adjust

#define STAT_TIME_SOURCE              NTP //    NTP, Network Time Protocol per IPAddress settings above or use DS3234 RTC on  Adjust
                                          //         default SPI interface (CS=53.) Upload once w/DS3234INIT to set date/time.

#define STAT_MAINS_SENSE              OFF //    OFF, n. Where n=1..6 (Sense#) mains power good, OFF (power failure) is UNSAFE Option
#define STAT_MAINS_CURRENT_ANALOG     OFF //    OFF, n. Where n=A0..A5 (Analog#) measure/display current mains.               Option
#define STAT_MAINS_AUX_CURRENT_ANALOG OFF //    OFF, n. Where n=A0..A5 (Analog#) measure/display current mains (aux.)         Option

#define STAT_DC_VOLTAGE_ANALOG        OFF //    OFF, n. Where n=A0..A5 (Analog#) measure/display 12VDC power supply voltage.  Option
#define STAT_DC_CURRENT_ANALOG        OFF //    OFF, n. Where n=A0..A5 (Analog#) measure/display 12VDC power supply current.  Option

#define STAT_BATTERY_VOLTAGE_ANALOG   OFF //    OFF, n. Where n=A0..A5 (Analog#) measure/display 12V roof battery voltage.    Option
#define STAT_BATTERY_CURRENT_ANALOG   OFF //    OFF, n. Where n=A0..A5 (Analog#) measure/display 12V roof battery current.    Option

// WEATHER PANEL -------------------------------------------------------------------------------------------------------------------
// Weather and Sky Conditions web page charts use "Chart.js" http://www.chartjs.org/. Specifically, version 2.5 of "Chart.min.js" 
//   renamed to "Chart.js" and placed in the Micro SD card root directory (Fat32 formatted) and inserted into the W5100 Ethernet
//   adapter.  Downloaded from here https://github.com/chartjs/Chart.js/releases/tag/v2.5.0 (page bottom for download links.)
// See Weather.ino for user weather sensor functions.
#define WEATHER                       OFF //    OFF, ON to enable the OCS website weather panel display.                      Option
#define WEATHER_CHARTS                OFF //    OFF, ON for logging and display of weather data graphic charts.               Option

#define WEATHER_TEMPERATURE           OFF //    OFF, ON for measuring outside temperature.                                    Option

#define WEATHER_PRESSURE              OFF //    OFF, ON for measuring barometric pressure.                                    Option
#define WEATHER_NOMINAL_PRESSURE     1010 //   1010, n. Where n=500..1050 (in mb) site nominal pressure for Chart.            Adjust
#define WEATHER_ALTITUDE              100 //    100, n. Where n=-86..5000 (meters) site altitude.                             Adjust

#define WEATHER_HUMIDITY              OFF //    OFF, ON for measuring outside humidity.                                       Option

#define WEATHER_WIND_SPD              OFF //    OFF, ON for measuring wind speed.                                             Option
#define WEATHER_WIND_SPD_THRESHOLD     20 //     20, n. Where n=0..100 (in kph) wind speed above this is considered UNSAFE.   Adjust

#define WEATHER_SKY_QUAL              OFF //    OFF, ON for measuring sky quality (darkness in magnitudes per sq arc-sec.)    Option

#define WEATHER_RAIN                  OFF //    OFF, ON to enable rain sensor, a "wet" condition is considered to be UNSAFE.  Option

#define WEATHER_CLOUD_CVR             OFF //    OFF, ON to enable the cloud sensor, above WEATHER_SAFE_THRESHOLD is UNSAFE.   Option
#define WEATHER_SAFE_THRESHOLD        -14 //    -14, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_VCLR_THRESHOLD        -19 //    -19, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_CLER_THRESHOLD        -17 //    -17, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_HAZE_THRESHOLD        -14 //    -14, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_OVRC_THRESHOLD        -11 //    -11, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_CLDY_THRESHOLD         -8 //     -8, n. Where n=-25..0 (in Deg. C)                                            Adjust
#define WEATHER_VCLD_THRESHOLD         -5 //     -5, n. Where n=-25..0 (in Deg. C)                                            Adjust

// POWER PANEL ---------------------------------------------------------------------------------------------------------------------
#define POWER                         OFF //    OFF, ON to enable the OCS website power panel display.                        Option

#define POWER_DEVICE1_RELAY           OFF //    OFF, n. Where n=1..14 (Relay#) with _NAME below.                              Option
#define POWER_DEVICE1_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE1_NAME ""

#define POWER_DEVICE2_RELAY           OFF //    OFF, n. Where n=1..14 (Relay#) with _NAME below.                              Option
#define POWER_DEVICE2_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE2_NAME ""

#define POWER_DEVICE3_RELAY           OFF //    OFF, n. Where n=1..14 (Relay#) with _NAME below.                              Option
#define POWER_DEVICE3_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE3_NAME ""

#define POWER_DEVICE4_RELAY           OFF //    OFF, n. Where n=1..14 (Relay#) with _NAME below.                              Option
#define POWER_DEVICE4_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE4_NAME ""

#define POWER_DEVICE5_RELAY           OFF //    OFF, n. Where n=1..14 (Relay#) with _NAME below.                              Option
#define POWER_DEVICE5_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE5_NAME ""

#define POWER_DEVICE6_RELAY           OFF //    OFF, n. Where n=1..14 (Relay#) with _NAME below                               Option
#define POWER_DEVICE6_MEMORY          OFF //    OFF, ON to enable memory (across power cycles) for this relay state.          Option
#define POWER_DEVICE6_NAME ""

// THERMOSTAT PANEL ----------------------------------------------------------------------------------------------------------------
// See Thermostat.ino for user inside temperature and humidity sensor functions
#define THERMOSTAT                    OFF //    OFF, ON to enable the OCS website thermostat panel display.                   Option
#define HEAT_RELAY                    OFF //    OFF, n. Where n=1..14 (Relay#) for indoor heat.                               Option
#define COOL_RELAY                    OFF //    OFF, n. Where n=1..14 (Relay#) for cooling/venting.                           Option
#define THERMOSTAT_HUMIDITY           OFF //    OFF, ON displays indoor humidity.                                             Option

// LIGHTING PANEL ------------------------------------------------------------------------------------------------------------------
#define LIGHT                         OFF //    OFF, ON to enable the OCS website lighting panel display.                     Option
#define LIGHT_WRW_RELAY               OFF //    OFF, n. Where n=1..14 (Relay#) for Warm room white lights.                    Option
#define LIGHT_WRR_RELAY               OFF //    OFF, n. Where n=1..14 (Relay#) for Warm room red lights.                      Option
#define LIGHT_ORW_RELAY               OFF //    OFF, n. Where n=1..14 (Relay#) for Observing room white lights.               Option
#define LIGHT_ORR_RELAY               OFF //    OFF, n. Where n=1..14 (Relay#) for Observing room red lights.                 Option
#define LIGHT_OUTSIDE_RELAY           OFF //    OFF, n. Where n=1..14 (Relay#) for Outside flood.                             Option
#define LIGHT_SW_SENSE                OFF //    OFF, n. Where n=1..6 (Sense#) for switch to turn WRW lights on/off.           Option

// ROLL-OFF ROOF CONTROL PANEL -----------------------------------------------------------------------------------------------------
#define ROR                           OFF //    OFF, ON to enable the OCS website roll-off roof panel display.                Option
#define ROR_USER_SAFETY_OVERRIDE      OFF //    OFF, ON allows user safety override showing the "Safety Override" button.     Option

#define ROR_AUTOCLOSE_DAWN            OFF //    OFF, ON allow option of closing roof automatically at dawn.                   Option
#define ROR_AUTOCLOSE_DAWN_DEFAULT    OFF //    OFF, ON enables autoclose at power on.  Disabled at startup otherwise.        Option
#define ROR_AUTOCLOSE_SAFETY          OFF //    OFF, ON closes the roof automatically if UNSAFE condition is detected.        Option

#define ROR_DC_MOTOR_RELAY_A          OFF //    OFF, n. Where n=1..14 (Relay#) Sets relays to cause roof to open or close.    Option
#define ROR_DC_MOTOR_RELAY_B          OFF //    OFF, n. Where n=1..14 (Relay#) A=HIGH/B=LOW to OPEN, A=LOW/B=HIGH to CLOSE.   Option
                                          //         Default state both A and B LOW stops the DC roof motor (for example.)

#define ROR_OPEN_CLOSE_MOMENTARY      OFF //    OFF, n. Where n=1..14 (Relay#) A momentary switch closure (~1.5 seconds.)     Option
                                          //         To trigger a garage door opener (for example) to either open or close.

#define ROR_POWER_RELAY               OFF //    OFF, n. Where n=1..14 (Relay#) This controls roof motor pwr. For DC motor.    Option
                                          //         SSR/MOSFET PWM controls speed. For garage door openers, SW on/off only.

#define ROR_PWM_SPEED_HZ              OFF //    OFF, n. Where n=1..100 (Hz) PWM frequency for roof motor DC control.          Option
#define ROR_PWM_POWER_PERCENT         OFF //    OFF, n. Where n=10..100 (%) PWM power level for roof motor DC control.        Option
#define ROR_PWM_SOFTSTART             OFF //    OFF, ON For PWM soft start, start 0% adds 5%/sec until ROR_PWM_POWER_PERCENT. Option

#define ROR_CLOSE_OK                  OFF //    OFF, n. Where n=1..6 (Sense#) Roof safety interlock, close allowed when ON.   Option
#define ROR_LIMIT_SENSE_CLOSED        OFF //    OFF, n. Where n=1..6 (Sense#) Roof closed switch (CLOSED when ON.)            Option
#define ROR_LIMIT_SENSE_OPENED        OFF //    OFF, n. Where n=1..6 (Sense#) Roof open switch (OPEN when ON.)                Option

#define ROR_TIME_AVG                  300 //    300, n. Where n=30..1200 (seconds) Average time to open or close roof.        Adjust
#define ROR_TIME_TOL                   30 //     30, n. Where n=0..120 (seconds) Additional time before stop & error thrown.  Adjust
#define ROR_TIME_LIMIT_SENSE_FAIL       6 //      6, n. Where n=1..60 (seconds) Time for limit switch fail to disengage error Adjust

// MISC. SETTINGS ------------------------------------------------------------------------------------------------------------------
#define WATCHDOG                      OFF //    OFF, ON to reset the Mega2560 after 8 seconds if it hangs for any reason.     Infreq

// THAT'S IT FOR USER CONFIGURATION!
// -------------------------------------------------------------------------------------------------------------------------

// DEBUGGING -----------------------------------------------------------------------------------------------------------------------
#define DEBUG_NPT                     OFF //    OFF, ON to enable debug code for network time protocol.                       Infreq
#define DEBUG_DS3234                  OFF //    OFF, ON to enable debug code for the DS3234 real time clock.                  Infreq
#define DEBUG_SD                      OFF //    OFF, ON to enable debug code for the SD card support.                         Infreq
#define DEBUG_WEBSERVER               OFF //    OFF, ON to enable debug code for the webserver.                               Infreq
#define DEBUG_CMDSERVER               OFF //    OFF, ON to enable debug code for the command server on port 9999.             Infreq
#define DEBUG_WEATHER                 OFF //    OFF, ON to enable debug code for the weather sensors.                         Infreq
#define DEBUG_AJAX_RELAY              OFF //    OFF, ON to enable debug code for webserver AJAX.                              Infreq

// -------------------------------------------------------------------------------------------------------------------------
#define FileVersionConfig 1
