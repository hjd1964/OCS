// -----------------------------------------------------------------------------------------------------------------
// Roof control functions
// ======= add your roof support code here =======

#ifdef ROR_ON

// roof status and errors
volatile char roofState = 'i';
// bit 7 = not used, reserved
// bit 6 = open roof failed with closed limit switch failure to disengage
// bit 5 = open roof failed with over time
// bit 4 = open roof failed with under time
// bit 3 = not used, reserved
// bit 2 = close roof failed with open limit switch failure to disengage
// bit 1 = close roof failed with over time
// bit 0 = close roof failed with under time
uint16_t roofStatusRegister=0;
String roofLastError="";

// roof power and safety
volatile boolean roofSafetyOverride = false;
volatile boolean roofMaxPower = false;
volatile int     roofCurrentPower = 0;

// roof timing and travel
const long roofTimeAvg        = (long)(ROR_TIME_AVG)*1000L;
const long roofTimeErrorLimit = (long)(ROR_TIME_TOL)*1000L;
long lastSecondsOfTravel,roofOpenStartTime,timeLeftToOpenAtStart,roofCloseStartTime,timeLeftToCloseAtStart;
long roofTravel=0;

// this gets called once on startup to initialize roof operation (required)
void roofInit() {
}

// called repeatedly if roof is moving (required)
void moveRoof() {
  // Open the roof, keeping track of time limit and sensor status
  if (roofIsOpening()) continueOpeningRoof();

  // Close the roof, keeping track of time limit and sensor status
  if (roofIsClosing()) continueClosingRoof();
}

// called repeatedly to open the roof
void continueOpeningRoof() {
    cli(); long msOfTravel=((long)millis()-roofOpenStartTime); sei();

#ifdef ROR_SOFTSTART_ON
    if (roofCurrentPower<ROR_PWM_POWER_PERCENT) {
      cli(); roofCurrentPower=msOfTravel/200; if (roofCurrentPower>ROR_PWM_POWER_PERCENT) roofCurrentPower=ROR_PWM_POWER_PERCENT; sei();
    }
#endif

    // calculate how far we are from opening and closing the roof right now
    long timeLeftToOpenNow=timeLeftToOpenAtStart-msOfTravel;
    if (timeLeftToOpenNow<0) { timeLeftToOpenNow=0; }
    long timeLeftToCloseNow=roofTimeAvg-timeLeftToOpenNow;

    // keep track of where we are (to the nearest five seconds)
    long secondsOfTravel=round(msOfTravel/5000)*5000;
    if (lastSecondsOfTravel!=secondsOfTravel) {
      lastSecondsOfTravel=secondsOfTravel;
      EEPROM_writeLong(EE_timeLeftToOpen,timeLeftToOpenNow);
      EEPROM_writeLong(EE_timeLeftToClose,timeLeftToCloseNow);
    }

    // Or a stuck limit switch
    if ((!roofSafetyOverride) && (((roofTimeAvg-timeLeftToOpenNow)>ROR_TIME_LIMIT_FAIL*1000) && senseIsOn(ROR_CLOSED_LIMIT_SENSE))) {
      // Set the error in the status register, the user can resume the opening operation by checking for any malfunction then using the safety override if required
      roofStatusRegister=roofStatusRegister|0b01000000; // 64
      // Go idle
      roofState='i';
    }

    // Or the whole process taking too long
    if ((!roofSafetyOverride) && ((timeLeftToOpenAtStart-msOfTravel)<-roofTimeErrorLimit)) {
      // Set the error in the status register, the user can resume the opening operation by checking for any malfunction then using the safety override if required
      roofStatusRegister=roofStatusRegister|0b00100000; // 32
      // Go idle
      roofState='i';
    }

    // Calculate a percentage of roof travel
    roofTravel=((double)(roofTimeAvg-(timeLeftToOpenAtStart-msOfTravel))/(double)roofTimeAvg)*100;

    // Detect that the roof has finished opening
    if (senseIsOn(ROR_OPENED_LIMIT_SENSE)) {
      // wait for two seconds before powering off the roof motor (for garage door opener)
      if (ROR_OPEN_CLOSE_MOMENTARY > 0) delay(2000);
      // reset position timers
      EEPROM_writeLong(EE_timeLeftToOpen,0);
      EEPROM_writeLong(EE_timeLeftToClose,roofTimeAvg);
      // Go idle
      roofState='i';
    }

    // Finished opening? stop the motion and clear state
    if (roofState=='i') {
      // Stop the roof motor
      setRelayOff(ROR_DIR_RELAY_A);
      // Reset possible override of roof timer
      roofSafetyOverride=false;
      // Reset roof power to normal level
      roofMaxPower=false;
    }
}

// called repeatedly to close the roof
void continueClosingRoof() {
    cli(); long msOfTravel=(long)millis()-roofCloseStartTime; sei();

#ifdef ROR_SOFTSTART_ON
    if (roofCurrentPower<ROR_PWM_POWER_PERCENT) {
      cli(); roofCurrentPower=msOfTravel/200; if (roofCurrentPower>ROR_PWM_POWER_PERCENT) roofCurrentPower=ROR_PWM_POWER_PERCENT; sei();
    }
#endif
    
    // calculate how far we are from opening and closing the roof right now
    long timeLeftToCloseNow=timeLeftToCloseAtStart-msOfTravel;
    if (timeLeftToCloseNow<0) { timeLeftToCloseNow=0; }
    long timeLeftToOpenNow=roofTimeAvg-timeLeftToCloseNow;

    // keep track of where we are, if power goes out, for example
    long secondsOfTravel=round(msOfTravel/5000)*5000;
    if (lastSecondsOfTravel!=secondsOfTravel) {
      lastSecondsOfTravel=secondsOfTravel;
      EEPROM_writeLong(EE_timeLeftToOpen,timeLeftToOpenNow);
      EEPROM_writeLong(EE_timeLeftToClose,timeLeftToCloseNow);
    }

    // Or a stuck limit switch
    if ((!roofSafetyOverride) && (((roofTimeAvg-timeLeftToCloseNow)>ROR_TIME_LIMIT_FAIL*1000) && senseIsOn(ROR_OPENED_LIMIT_SENSE))) {
      // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
      roofStatusRegister=roofStatusRegister|0b00000100; // 4
      // Go idle
      roofState='i';
    }

    // Or interlock was triggered
    if (ROR_CLOSE_OK != 0 && !senseIsOn(ROR_CLOSE_OK)) {
      // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
      roofStatusRegister=roofStatusRegister|0b100000000; // 256
      // Go idle
      roofState='i';
    }

    // Or the whole process is taking too long
    if ((!roofSafetyOverride) && ((timeLeftToCloseAtStart-msOfTravel)<-roofTimeErrorLimit)) {
      // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
      roofStatusRegister=roofStatusRegister|0b00000010; // 2
      // Go idle
      roofState='i';
    }

    // Calculate a percentage of roof travel
    roofTravel=((double)(roofTimeAvg-(timeLeftToCloseAtStart-msOfTravel))/(double)roofTimeAvg)*100;

    // Detect that the roof has finished closing
    if (senseIsOn(ROR_CLOSED_LIMIT_SENSE)) {
      // wait for two seconds before powering off the roof motor (for garage door opener)
      if (ROR_OPEN_CLOSE_MOMENTARY > 0) delay(2000);
      // reset position timers
      EEPROM_writeLong(EE_timeLeftToOpen,roofTimeAvg);
      EEPROM_writeLong(EE_timeLeftToClose,0);
      // Go idle
      roofState='i';
    }
    
    // Finished closing? stop the motion and clear state
    if (roofState=='i') {
      // Stop the winch
      setRelayOff(ROR_DIR_RELAY_B);
      // Reset possible override of roof timer
      roofSafetyOverride=false;
      // Reset roof power to normal level
      roofMaxPower=false;
    }
}

// Start opening the roof, returns true if successful or false otherwise (required)
bool startRoofOpen() {
  if ((roofState=='i') && (!relayIsOn(ROR_DIR_RELAY_A)) && (!relayIsOn(ROR_DIR_RELAY_B))) {
    // Figure out where the roof is right now best as we can tell...
    // Check for limit switch and reset times
    if (senseIsOn(ROR_CLOSED_LIMIT_SENSE)) { EEPROM_writeLong(EE_timeLeftToOpen,roofTimeAvg); EEPROM_writeLong(EE_timeLeftToClose,0); }
    if (senseIsOn(ROR_OPENED_LIMIT_SENSE)) { EEPROM_writeLong(EE_timeLeftToOpen,0); EEPROM_writeLong(EE_timeLeftToClose,roofTimeAvg); }
    timeLeftToOpenAtStart =EEPROM_readLong(EE_timeLeftToOpen);
    timeLeftToCloseAtStart=EEPROM_readLong(EE_timeLeftToClose);
//    Serial.println(sense1);
//    Serial.println(sense2);
//    Serial.println(roofTimeAvg);

    // Check for validity of roof position timers before starting (they need to be within +/- 2 seconds)
    if ((!roofSafetyOverride) && (abs((timeLeftToOpenAtStart+timeLeftToCloseAtStart)-roofTimeAvg)>2000)) {
      roofLastError="Error: Open location unknown";
    } else {
      // Check to see if the roof is already opened
      if (senseIsOn(ROR_OPENED_LIMIT_SENSE) && (!senseIsOn(ROR_CLOSED_LIMIT_SENSE))) {
        roofLastError="Warning: Already open";
      } else {
        // Just one last sanity check before we start moving the roof
        if (senseIsOn(ROR_OPENED_LIMIT_SENSE) && senseIsOn(ROR_CLOSED_LIMIT_SENSE)) {
          roofLastError="Error: Opened/closed limit sw on";
        } else {
          // Set relay/MOSFET
          setRelayOff(ROR_DIR_RELAY_B);
          setRelayOn(ROR_DIR_RELAY_A);

          // Flag status, no errors
          roofState='o';
          roofStatusRegister=0;

          // wait for two seconds after powering on the roof motor (for garage door opener)
          if (ROR_OPEN_CLOSE_MOMENTARY > 0) delay(2000); 
          setRelayOnDelayedOff(ROR_OPEN_CLOSE_MOMENTARY,2);

          // Log start time
          roofOpenStartTime=(long)millis();

#ifdef ROR_SOFTSTART_ON
          roofCurrentPower=0;
#else
          roofCurrentPower=ROR_PWM_POWER_PERCENT;
#endif

          roofLastError="";
          return true;
        }
      }
    }
  } else {
    roofLastError="Error: Open already in motion";
  }
  return false;
}

// Start closing the roof, returns true if successful or false otherwise (required)
bool startRoofClose() {
  if ((roofState=='i') && (!relayIsOn(ROR_DIR_RELAY_A)) && (!relayIsOn(ROR_DIR_RELAY_B))) {
    // Check roof interlock...
    if (ROR_CLOSE_OK != 0 && !senseIsOn(ROR_CLOSE_OK)) {
      roofLastError="Error: Close safety interlock";
    } else {
      // Figure out where the roof is right now best as we can tell...
      // Check for limit switch and reset times
      if (senseIsOn(ROR_CLOSED_LIMIT_SENSE)) { EEPROM_writeLong(EE_timeLeftToOpen,roofTimeAvg); EEPROM_writeLong(EE_timeLeftToClose,0); }
      if (senseIsOn(ROR_OPENED_LIMIT_SENSE)) { EEPROM_writeLong(EE_timeLeftToOpen,0); EEPROM_writeLong(EE_timeLeftToClose,roofTimeAvg); }
      timeLeftToOpenAtStart =EEPROM_readLong(EE_timeLeftToOpen);
      timeLeftToCloseAtStart=EEPROM_readLong(EE_timeLeftToClose);
  //    Serial.println(timeLeftToOpenAtStart);
  //    Serial.println(timeLeftToCloseAtStart);
  //    Serial.println(roofTimeAvg);
  
      // Check for validity of roof position timers before starting (they need to be within +/- 2 seconds)
      if ((!roofSafetyOverride) && (abs((timeLeftToOpenAtStart+timeLeftToCloseAtStart)-roofTimeAvg)>2000)) {
        roofLastError="Error: Close location unknown";
      } else {
        // Check to see if the roof is already closed
        if (senseIsOn(ROR_CLOSED_LIMIT_SENSE) && (!senseIsOn(ROR_OPENED_LIMIT_SENSE))) {
          roofLastError="Warning: Already closed";
        } else {
          // Just one last sanity check before we start moving the roof
          if (senseIsOn(ROR_CLOSED_LIMIT_SENSE) && senseIsOn(ROR_OPENED_LIMIT_SENSE)) {
            roofLastError="Error: Closed/opened limit sw on";
          } else {
            // Set relay/MOSFET
            setRelayOff(ROR_DIR_RELAY_A);
            setRelayOn(ROR_DIR_RELAY_B);
  
            // Flag status, no errors
            roofState='c';
            roofStatusRegister=0;

            // wait for two seconds after powering on the roof motor (for garage door opener)
            if (ROR_OPEN_CLOSE_MOMENTARY > 0) delay(2000); 
            setRelayOnDelayedOff(ROR_OPEN_CLOSE_MOMENTARY,2);
  
            // Log start time
            roofCloseStartTime=(long)millis();
  
#ifdef ROR_SOFTSTART_ON
            roofCurrentPower=0;
#else
            roofCurrentPower=ROR_PWM_POWER_PERCENT;
#endif
  
            roofLastError="";
            return true;
          }
        }
      }
    }
  } else {
    roofLastError="Error: Close already in motion";
  }
  return false;
}

// stop the roof, this must be ISR safe! (required)
void stopRoof() {
  // Reset possible override of roof timer
  roofSafetyOverride=false;
  // Reset roof power to normal level
  roofMaxPower=false;
  // Set the state to idle
  roofState='i';
  // Stop the motor
  setRelayOff(ROR_DIR_RELAY_A);
  setRelayOff(ROR_DIR_RELAY_B);
}

// clear errors (required)
void clearRoofStatus() {
  // Reset the status register
  roofStatusRegister=0;
  roofLastError="";
}

// returns an error description string if an error has occured, otherwise must return "Travel: n%" or "No Error" (required)
String getRoofStatus() {
  String s=getRoofLastError();
  if (s=="" && roofIsMoving()) { s="Travel: "+String(roofTravel)+"%"; return s; }
  if (s=="") s="No Error";
  return s;
}

// returns an error description string if an error has occured, "" if no error (required)
String getRoofLastError() {
  String s="";
  if (roofStatusRegister&256) s="Error: Close safety interlock";
  if (roofStatusRegister&128) s="Error: Open unknown error"; else
  if (roofStatusRegister&64) s="Error: Open limit sw fail"; else
  if (roofStatusRegister&32) s="Error: Open over time"; else
  if (roofStatusRegister&16) s="Error: Open under time"; else
  if (roofStatusRegister&8) s="Error: Close unknown error"; else
  if (roofStatusRegister&4) s="Error: Close limit sw fail"; else
  if (roofStatusRegister&2) s="Error: Close over time"; else
  if (roofStatusRegister&1) s="Error: Close under time";
  if (s=="") {
    if (roofState=='i') {
      if (roofLastError=="") {
        // one final check for any wierd relay stuff going on
        if (senseIsOn(ROR_CLOSED_LIMIT_SENSE) && senseIsOn(ROR_OPENED_LIMIT_SENSE)) { s="Error: Limit switch malfunction"; }
      } else s=roofLastError;
    }
  }
  return s;
}

// true if the roof is closed (required)
bool roofIsClosed() {
  return senseIsOn(ROR_CLOSED_LIMIT_SENSE) && (!senseIsOn(ROR_OPENED_LIMIT_SENSE));
}

// true if the roof is opened (required)
bool roofIsOpened() {
  return senseIsOn(ROR_OPENED_LIMIT_SENSE) && (!senseIsOn(ROR_CLOSED_LIMIT_SENSE));
}

// true if the roof is moving (required)
bool roofIsMoving() {
  return (roofState!='i');
}

// true if the roof is moving (closing, required)
bool roofIsClosing() {
  return (roofState=='c');
}

// true if the roof is moving (opening, required)
bool roofIsOpening() {
  return (roofState=='o');
}

// safety override, ignores stuck limit switch and timeout (required)
void setRoofSafetyOverride() {
  roofSafetyOverride=true;
}

// required
bool roofIsSafetyOverride() {
  return roofSafetyOverride;
}

// forces pwm power to 100%
void setRoofMaxPower() {
  roofMaxPower=true;
}

// required
bool roofMaxPowerOn() {
  return roofMaxPower;
}

// for soft start etc, pwm power level (required)
int roofPowerLevel() {
  return roofCurrentPower;
}
     
#endif
