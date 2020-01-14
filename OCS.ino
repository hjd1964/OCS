/*
 * Title       Observatory-Control-System
 * by          Howard Dutton
 *
 * Copyright (C) 2012 to 2019 Howard Dutton
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 
 *
 * Revision History, see GitHub
 *
 *
 * Author: Howard Dutton
 * http://www.stellarjourney.com
 * hjd1964@gmail.com
 *
 * Description
 *
 * General Purpose Observatory Control
 * with LX200 derived command set.
 *
 */

// firmware info
#define ONCUE_OCS
#define FirmwareDate   __DATE__
#define FirmwareNumber "1.5a"
#define FirmwareName   "OnCue OCS"
#define FirmwareTime   __TIME__

#define invalid -1000

#include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time
#include <SPI.h>
#include <Ethernet.h>
#include "Config.h"
#ifdef NTP_ON
#include <EthernetUdp.h>
#endif
#ifdef WATCHDOG_ON
#include <avr/wdt.h>
#endif
#include "string.h"
#include "EEPROM.h"
#include "TimerOne.h"
#include "WebServer.h"
#include "CmdServer.h"
#include "Command.h"

const int timeZone = TimeZone;

WebServer www;
CmdServer Cmd;
CmdServer Cmd1;

#if defined(STAT_TIME_NTP_ON)
EthernetUDP Udp;
// local port to listen for UDP packets
unsigned int localPort = 8888;
time_t startupTime = 0;
bool fastNTPSync=false;
#elif defined(STAT_TIME_DS3234_ON) || defined(STAT_TIME_DS3234_INIT)
#include <SparkFunDS3234RTC.h>  // https://github.com/sparkfun/SparkFun_DS3234_RTC_Arduino_Library/archive/master.zip
#define DS3234_CS_PIN 53
time_t startupTime = 0;
#endif

// Pin assignments
// Note that pins 4, 10, 50, 51, 52, 53 are used for SD card and W5100 Ethernet (SPI interface on pins 50-53)

typedef struct {
  uint8_t pin;
  uint8_t onState;
} relay_t;
const volatile relay_t relay[] {
  { 0, HIGH},               // not used
  {23, HIGH},               // Pin output to Relay 1  (Outlets for computer)
  {25, HIGH},               // Pin output to Relay 2  (12V Power supply)
  {27, HIGH},               // Pin output to Relay 3  (Outlets for telescope)
  {29, HIGH},               // Pin output to Relay 4  (Heater)
  {31, HIGH},               // Pin output to Relay 5  (Outside flood lights)
  {33, HIGH},               // Pin output to Relay 6  (Fan/AC, not used)
// solid state relays (PWM is enabled on these)
  {35, HIGH},               // Pin output to Relay 7  (Roof direction relay, open)
  {37, HIGH},               // Pin output to Relay 8  (Roof direction relay, close)
  {39, HIGH},               // Pin output to Relay 9  (Warm room Red lights)
  {41, HIGH},               // Pin output to Relay 10 (Observing room Red lights)
  {43, HIGH},               // Pin output to Relay 11 (Warm room White lights)
  {45, HIGH},               // Pin output to Relay 12 (Observing room White lights)
  {47, HIGH},               // Pin output to Relay 13 (Aux - no relay on my setup)
  {49, HIGH}                // Pin output to Relay 14 (Roof MOSFET - no relay on my setup)
};
volatile uint8_t relayState[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

typedef struct {
  uint8_t pin;
  uint8_t mode;
  uint8_t onState;
} sense_t;
const volatile sense_t sense[] {
  { 0, INPUT, HIGH},        // not used
  {22, INPUT, HIGH},        // Pin input from Sense 1 (roof closed limit switch)
  {24, INPUT, HIGH},        // Pin input from Sense 2 (roof open   limit switch)
  {26, INPUT, HIGH},        // Pin input from Sense 3 (wall switch)
  {28, INPUT, HIGH},        // Pin input from Sense 4 (power good)
  {30, INPUT, HIGH},        // Pin input from Sense 5 (not used)
  {32, INPUT, HIGH}         // Pin input from Sense 6 (not used)
};
volatile uint8_t senseState[] = {0,0,0,0,0,0,0};

// Analog0                   Analog input from A0   (12V battery)
// Analog1                   Analog input from A1   (12V power supply)
// Analog2                   Analog input from A2   (not used)
// Analog3                   Analog input from A3   (inside temperature LM35)
// Analog4                   Analog input from A4   (not used)
// Analog5                   Analog input from A5   (not used)
volatile int analogState[] = {0,0,0,0,0,0};

// EEPROM addresses for settings
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

// roof
#ifdef ROR_AUTOCLOSE_DAWN_DEFAULT_ON
boolean roofAutoClose = true;
#else
boolean roofAutoClose = false;
#endif
boolean roofAutoCloseInitiated = false;

// relay control timer
unsigned long tst;

unsigned long msFiveMinuteCounter;
float insideTemperature;

void setup()   {
#ifdef NexDomeSetup
  // Get dome ready
  NexDomeSetup();
#endif

  // Initialize serial communications
  Serial.begin(9600);
  
#ifdef WATCHDOG_ON
  wdt_enable(WDTO_8S);
#endif

  // Set pins for direct relay control
  for (int i=1; i<=14; i++) { pinMode(relay[i].pin,OUTPUT); setRelayOff(i); }

  // Set pins for input
  for (int i=1; i<=6; i++) pinMode(sense[i].pin,sense[i].mode);

  // Initialize EEPROM if necessary
  if (EEPROM_readLong(EE_key)!=19653291L) {
    EEPROM_writeLong(EE_key,19653291L);
    for (int l=4; l<1024; l++) EEPROM.write(l,0);
    // These are the default for the roof
    EEPROM_writeLong(EE_timeLeftToOpen,120000); // two minutes
    EEPROM_writeLong(EE_timeLeftToClose,0);
  }

  // Restore relay state
  #if defined(POWER_DEVICE1_RELAY) && defined(POWER_DEVICE1_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_1)) { setRelayOn(atoi(POWER_DEVICE1_RELAY)); }
  #endif
  #if defined(POWER_DEVICE2_RELAY) && defined(POWER_DEVICE2_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_2)) { setRelayOn(atoi(POWER_DEVICE2_RELAY)); }
  #endif
  #if defined(POWER_DEVICE3_RELAY) && defined(POWER_DEVICE3_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_3)) { setRelayOn(atoi(POWER_DEVICE3_RELAY)); }
  #endif
  #if defined(POWER_DEVICE4_RELAY) && defined(POWER_DEVICE4_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_4)) { setRelayOn(atoi(POWER_DEVICE4_RELAY)); }
  #endif
  #if defined(POWER_DEVICE5_RELAY) && defined(POWER_DEVICE5_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_5)) { setRelayOn(atoi(POWER_DEVICE5_RELAY)); }
  #endif
  #if defined(POWER_DEVICE6_RELAY) && defined(POWER_DEVICE6_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_6)) { setRelayOn(atoi(POWER_DEVICE6_RELAY)); }
  #endif

  // get ready to go
  weatherInit();
#ifdef ROOF_ON
  roofInit();
#endif
#ifdef THERMOSTAT_ON
  thermostatInit();
#endif

#ifdef ETHERNET_RESET
  // hold ethernet shield in reset
  pinMode(ETHERNET_RESET,OUTPUT);
  digitalWrite(ETHERNET_RESET,LOW);

  for (int l=0; l<2; l++) {
    delay(1000);
  #ifdef WATCHDOG_ON
    wdt_reset();
  #endif
  }

  // let ethernet shield run
  digitalWrite(ETHERNET_RESET,HIGH);
#endif

  // wait for a bit just to be sure ethernet, etc. is up
  for (int l=0; l<3; l++) {
    delay(1000);
#ifdef WATCHDOG_ON
    wdt_reset();
#endif
  }

  // Initialize the webserver
  www.setResponseHeader(http_defaultHeader);
  www.init();
  www.on("index.htm",index);
#if defined(WEATHER_ON) && defined(SD_CARD_ON)
  www.on("weatherpage.htm",weatherPage);
#if defined(WEATHER_SKY_QUAL_ON) || defined(WEATHER_CLOUD_CVR_ON)
  www.on("skypage.htm",skyPage);
#endif
#endif
  www.on("relay",relays);
  www.on("setvar",setvar);
  www.on("miscstatus",miscstatus);
#ifdef WEATHER_ON
  www.on("weather",weather);
#endif
#ifdef THERMOSTAT_ON
  www.on("thermostat",thermostat);
#ifdef THERMOSTAT_HUMIDITY_ON
  www.on("thermostath",thermostath);
#endif
#endif
#ifdef ROR_ON
  www.on("roofstatus",roofstatus);
#endif
#ifdef SD_CARD_ON
  www.on("Chart.js");
#endif
  www.on("/",index);

  // Initialize the cmd server, timeout after 500ms
  Cmd.init(9999,500);
  Cmd1.init(9998,500);

  // Set variables
  msFiveMinuteCounter=millis()+5000UL;
  tst                =millis()+30000UL;
  insideTemperature  =-999.0;

  // for dimming the led's etc, 1 millisecond period
  Timer1.initialize(1000);
  Timer1.attachInterrupt(RelayPwmISR);

#ifdef STAT_TIME_NTP_ON
  delay(3000);
  Udp.begin(localPort);
#ifdef NTP_DEBUG_ON
  Serial.println("waiting for sync");
#endif
  setSyncProvider(getNtpTime);
  setSyncInterval(24L*60L*60L); // sync time once a day
  if (now()>365UL*24UL*60UL*60UL) startupTime=now();
#endif

#if defined(STAT_TIME_DS3234_ON) || defined(STAT_TIME_DS3234_INIT)
  setSyncProvider(getDs3234Time);
  setSyncInterval(24L*60L*60L); // sync time once a day
  startupTime=now();
#endif

}

void loop()                     
{
#ifdef NexDomeLoop
  // keep NexDome alive
  NexDomeLoop();
#endif
  
#ifdef WATCHDOG_ON
  wdt_reset();
#endif

#ifdef STAT_TIME_NTP_ON
  // double check time if it looks like it's not set go back and ask for it again every 10 minutes
if (now()<365UL*24UL*60UL*60UL) {
  if (!fastNTPSync) { setSyncInterval(10L*60L); fastNTPSync=true; }
} else {
  if (startupTime==0) startupTime=now();
  if (fastNTPSync) { setSyncInterval(24L*60L*60L); fastNTPSync=false; }
}
#endif
  // ------------------------------------------------------------------------------------------
  // Handle comms

  // serve web-pages
  www.handleClient();

  // handle cmd-channel
  Cmd.handleClient();
  Cmd1.handleClient();

  // process commands
  processCommands();

#ifdef LIGHT_SW_SENSE
  // The wall switch controls LED lights
  if (senseChanged(LIGHT_SW_SENSE)) {
    if (senseIsOn(LIGHT_SW_SENSE)) setRelayOn(atoi(LIGHT_WRW_RELAY)); else setRelayOff(atoi(LIGHT_WRW_RELAY));
  }
#endif

  // ------------------------------------------------------------------------------------------
  // Process events

  // update relays
  RelayTimedOff();

  #ifdef THERMOSTAT_ON
  thermostat();
  #endif

#ifdef ROR_ON
  // Auto close the roof at 8am if requested
  if ((roofAutoClose) && (validTime())) {
    if ((hour()==8) && (!roofAutoCloseInitiated)) {
      // if motion is idle
      if (!roofIsMoving()) {
        // and the roof isn't closed, close it
        if (!roofIsClosed()) startRoofClose();
        roofAutoCloseInitiated=true;
      }
    }
    if (hour()==9) roofAutoCloseInitiated=false;
  }

#ifdef ROR_AUTOCLOSE_SAFETY_ON
  // close the roof if safety status calls for it
  if (!isSafe()) {
    // if the roof isn't closed, and motion is idle, close it
    if ((!roofIsClosed()) && (!roofIsMoving()) startRoofClose();
  }
#endif

  if (roofIsMoving()) moveRoof();
#endif

  // Watch clouds
#ifdef WEATHER_ON
  weatherPoll();
#endif
}

bool validTime() {
  return (now()<315360000);
}
