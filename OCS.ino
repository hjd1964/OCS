/*
 * Title       Observatory-Control-System
 * by          Howard Dutton
 *
 * Copyright (C) 2012 to 2017 Howard Dutton
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
#define FirmwareDate   "06 06 17"
#define FirmwareNumber "1.0a"
#define FirmwareName   "OnCue OCS"
#define FirmwareTime   "12:00:00"

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
#include "string.h";
#include "EEPROM.h";
#include "TimerOne.h";
#include "WebServer.h";
#include "CmdServer.h";
#include "Command.h";

const int timeZone = TimeZone;

WebServer www;
CmdServer Cmd;
CmdServer Cmd1;

#ifdef STAT_TIME_NTP_ON
EthernetUDP Udp;
// local port to listen for UDP packets
unsigned int localPort = 8888;
time_t startupTime;
bool fastNTPSync=false;
#endif

// pin assignments
// Note that pins 4, 10, 50, 51, 52, 53 are used for SD card and W5100 Ethernet (SPI interface on pins 50-53)

// high current mechanical relays (PWM isn't enabled on these)
// relayPin[1]               Pin output to Relay 1  (Outside flood lights)
// relayPin[2]               Pin output to Relay 2  (12V Power supply)
// relayPin[3]               Pin output to Relay 3  (Outlets for computer)
// relayPin[4]               Pin output to Relay 4  (Heater)
// relayPin[5]               Pin output to Relay 5  (Outlets for telescope)
// relayPin[6]               Pin output to Relay 6  (Fan/AC, not used)
// lower current solid state relays (PWM is enabled on these)
// relayPin[7]               Pin output to Relay 7  (Roof direction relay, open)
// relayPin[8]               Pin output to Relay 8  (Roof direction relay, close)
// relayPin[9]               Pin output to Relay 9  (Warm room Red lights)
// relayPin[10]              Pin output to Relay 10 (Observing room Red lights)
// relayPin[11]              Pin output to Relay 11 (Warm room White lights)
// relayPin[12]              Pin output to Relay 12 (Observing room White lights)
// relayPin[13]              Pin output to Relay 13 (Aux - no relay on my setup)
// relayPin[14]              Pin output to Relay 14 (Roof MOSFET - no relay on my setup)
volatile int relayPin[] = {-1,23,25,27,29,31,33,35,37,39,41,43,45,47,49};
volatile byte relayState[] = {-1,0,0,0,0,0,0,0,0,0,0,0,0};

// sensePin[1]               Pin input from Sense 1 (roof closed limit switch)
// sensePin[2]               Pin input from Sense 2 (roof open   limit switch)
// sensePin[3]               Pin input from Sense 3 (wall switch)
// sensePin[4]               Pin input from Sense 4 (power good)
// sensePin[5]               Pin input from Sense 5 (not used)
// sensePin[6]               Pin input from Sense 6 (not used)
volatile int sensePin[] = {-1,22,24,26,28,30,32};
volatile byte senseState[] = {-1,0,0,0,0,0,0};

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

// Roof Status and Errors
// bit 7 = not used, reserved
// bit 6 = open roof failed with closed limit switch failure to disengage
// bit 5 = open roof failed with over time
// bit 4 = open roof failed with under time
// bit 3 = not used, reserved
// bit 2 = close roof failed with open limit switch failure to disengage
// bit 1 = close roof failed with over time
// bit 0 = close roof failed with under time
byte roofStatusRegister;
String roofLastError="";

// Global Roof state
volatile char    roofState = 'i';
volatile boolean roofSafetyOverride = false;
volatile boolean roofMaxPower = false;
volatile int     roofCurrentPower = 0;
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

// etc
#define invalid -1000
  
void setup()   {

  // Initialize serial communications
  Serial.begin(9600);
  
  #ifdef WATCHDOG_ON
  wdt_enable(WDTO_8S);
  #endif

  // Set pins for direct relay control
  for (int i=1; i<=14; i++) pinMode(relayPin[i],OUTPUT);

  // Set pins for input
  for (int i=1; i<=6; i++) pinMode(sensePin[i],INPUT);

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
  if ((bool)EEPROM.read(EE_powerDevice_1)) { relayState[atoi(POWER_DEVICE1_RELAY)]=1; digitalWrite(relayPin[atoi(POWER_DEVICE1_RELAY)],HIGH); }
  #endif
  #if defined(POWER_DEVICE2_RELAY) && defined(POWER_DEVICE2_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_2)) { relayState[atoi(POWER_DEVICE2_RELAY)]=1; digitalWrite(relayPin[atoi(POWER_DEVICE2_RELAY)],HIGH); }
  #endif
  #if defined(POWER_DEVICE3_RELAY) && defined(POWER_DEVICE3_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_3)) { relayState[atoi(POWER_DEVICE3_RELAY)]=1; digitalWrite(relayPin[atoi(POWER_DEVICE3_RELAY)],HIGH); }
  #endif
  #if defined(POWER_DEVICE4_RELAY) && defined(POWER_DEVICE4_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_4)) { relayState[atoi(POWER_DEVICE4_RELAY)]=1; digitalWrite(relayPin[atoi(POWER_DEVICE4_RELAY)],HIGH); }
  #endif
  #if defined(POWER_DEVICE5_RELAY) && defined(POWER_DEVICE5_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_5)) { relayState[atoi(POWER_DEVICE5_RELAY)]=1; digitalWrite(relayPin[atoi(POWER_DEVICE5_RELAY)],HIGH); }
  #endif
  #if defined(POWER_DEVICE6_RELAY) && defined(POWER_DEVICE6_MEMORY_ON)
  if ((bool)EEPROM.read(EE_powerDevice_6)) { relayState[atoi(POWER_DEVICE6_RELAY)]=1; digitalWrite(relayPin[atoi(POWER_DEVICE6_RELAY)],HIGH); }
  #endif

  // get any weather sensors ready to go
  weatherInit();

  // hold ethernet shield in reset
#ifdef ETHERNET_RESET
  pinMode(ETHERNET_RESET,OUTPUT);
  digitalWrite(ETHERNET_RESET,LOW);
#endif

  // wait for a bit just to be sure ethernet, etc. is up
  for (int l=0; l<5; l++) {
    delay(1000);
#ifdef WATCHDOG_ON
    wdt_reset();
#endif
  }

  // let ethernet shield run
#ifdef ETHERNET_RESET
  digitalWrite(ETHERNET_RESET,HIGH);
#endif

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
  www.on("relay",relay);
  www.on("setvar",setvar);
  www.on("status",ocsstatus);
#ifdef WEATHER_ON
  www.on("weather",weather);
#endif
#ifdef THERMOSTAT_ON
  www.on("thermostat",thermostat);
#endif
#ifdef ROR_ON
  www.on("roof_stat",roof_stat);
#endif
#ifdef SD_CARD_ON
  www.on("Chart.js");
#endif
  www.on("/",index);

  // Initialize the cmd server, timeout after 500ms
  Cmd.init(9999,500);
  Cmd1.init(9998,500);

  // Set variables
  roofState          ='i';
  msFiveMinuteCounter=millis()+5000UL;
  tst                =millis()+30000UL;
  insideTemperature  =-999.0;

  // for dimming the led's etc, 1 millisecond period
  Timer1.initialize(1000);
  Timer1.attachInterrupt(RelayPwmISR);

#ifdef STAT_TIME_NTP_ON
  Udp.begin(localPort);
#ifdef NTP_DEBUG_ON
  Serial.println("waiting for sync");
#endif
  setSyncProvider(getNtpTime);
  setSyncInterval(24*60*60); // sync time once a day
  startupTime=now();
#endif

}

void loop()                     
{
#ifdef WATCHDOG_ON
  wdt_reset();
#endif

#ifdef STAT_TIME_NTP_ON
  // double check time if it looks like it's not set go back and ask for it again every 10 minutes
if (now()<365UL*24UL*60UL*60UL) {
  if (!fastNTPSync) { setSyncInterval(10*60); fastNTPSync=true; }
} else {
  if (fastNTPSync) { setSyncInterval(24*60*60); fastNTPSync=false; }
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
  if (digitalRead(sensePin[LIGHT_SW_SENSE])!=senseState[LIGHT_SW_SENSE]) {
    senseState[LIGHT_SW_SENSE]=digitalRead(sensePin[LIGHT_SW_SENSE]);
    digitalWrite(relayPin[atoi(LIGHT_WRW_RELAY)], senseState[LIGHT_SW_SENSE]);
    if (senseState[LIGHT_SW_SENSE]==HIGH) relayState[atoi(LIGHT_WRW_RELAY)]=1; else relayState[atoi(LIGHT_WRW_RELAY)]=0;
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
      if (!isRoofMoving()) {
        // and the roof isn't closed, close it
        if (!isRoofClosed()) startRoofClose();
        roofAutoCloseInitiated=true;
      }
    }
    if (hour()==9) roofAutoCloseInitiated=false;
  }

#ifdef ROR_AUTOCLOSE_SAFETY_ON
  // close the roof if safety status calls for it
  if (!isSafe()) {
    // if the roof isn't closed, and motion is idle, close it
    if ((!isRoofClosed()) && (!isRoofMoving()) startRoofClose();
  }
#endif

  // Open the roof, keeping track of time limit and sensor status
  if (roofState=='o') openRoof();

  // Close the roof, keeping track of time limit and sensor status
  if (roofState=='c') closeRoof();
#endif

  // Watch clouds
  clouds();
}

bool validTime() {
  return (now()<315360000);
}

