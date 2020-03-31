// -----------------------------------------------------------------------------------------------------------------
// Roof control functions
// ======= add your roof support code here =======

#if ROR == ON

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

#if ROR_PWM_SOFTSTART == ON
    if (roofCurrentPower < ROR_PWM_POWER_PERCENT) {
      cli(); roofCurrentPower=msOfTravel/200; if (roofCurrentPower > ROR_PWM_POWER_PERCENT) roofCurrentPower=ROR_PWM_POWER_PERCENT; sei();
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
    if ((!roofSafetyOverride) && (((roofTimeAvg-timeLeftToOpenNow)>ROR_TIME_LIMIT_SENSE_FAIL*1000) && senseIsOn(ROR_LIMIT_SENSE_CLOSED))) {
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
    if (senseIsOn(ROR_LIMIT_SENSE_OPENED)) {
      // wait for two seconds before powering off the roof drive (for automatic opener that stops itself)
      if (ROR_MOTOR_RELAY_MOMENTARY != OFF) delay(2000);
      // reset position timers
      EEPROM_writeLong(EE_timeLeftToOpen,0);
      EEPROM_writeLong(EE_timeLeftToClose,roofTimeAvg);
      // Go idle
      roofState='i';
    }

    // Finished opening? stop the motion and clear state
    if (roofState=='i') {
      // Stop the roof motor (redundant for momentary control)
      setRelayOff(ROR_MOTOR_OPEN_RELAY);
      // Reset possible override of roof timer
      roofSafetyOverride=false;
      // Reset roof power to normal level
      roofMaxPower=false;
    }
}

// called repeatedly to close the roof
void continueClosingRoof() {
    cli(); long msOfTravel=(long)millis()-roofCloseStartTime; sei();

#if ROR_PWM_SOFTSTART == ON
    if (roofCurrentPower < ROR_PWM_POWER_PERCENT) {
      cli(); roofCurrentPower=msOfTravel/200; if (roofCurrentPower > ROR_PWM_POWER_PERCENT) roofCurrentPower=ROR_PWM_POWER_PERCENT; sei();
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
    if ((!roofSafetyOverride) && (((roofTimeAvg-timeLeftToCloseNow)>ROR_TIME_LIMIT_SENSE_FAIL*1000) && senseIsOn(ROR_LIMIT_SENSE_OPENED))) {
      // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
      roofStatusRegister=roofStatusRegister|0b00000100; // 4
      // Go idle
      roofState='i';
    }

    // Or interlock was triggered
    if (ROR_CLOSE_INTERLOCK != 0 && !senseIsOn(ROR_CLOSE_INTERLOCK)) {
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
    if (senseIsOn(ROR_LIMIT_SENSE_CLOSED)) {
      // wait for two seconds before powering off the roof drive (for automatic opener that stops itself)
      if (ROR_MOTOR_RELAY_MOMENTARY != OFF) delay(2000);
      // reset position timers
      EEPROM_writeLong(EE_timeLeftToOpen,roofTimeAvg);
      EEPROM_writeLong(EE_timeLeftToClose,0);
      // Go idle
      roofState='i';
    }
    
    // Finished closing? stop the motion and clear state
    if (roofState=='i') {
      // Stop the roof motor (redundant for momentary control)
      setRelayOff(ROR_MOTOR_CLOSE_RELAY);
      // Reset possible override of roof timer
      roofSafetyOverride=false;
      // Reset roof power to normal level
      roofMaxPower=false;
    }
}

// Start opening the roof, returns true if successful or false otherwise (required)
bool startRoofOpen() {
  if (roofState != 'i' || relayIsOn(ROR_MOTOR_OPEN_RELAY) || relayIsOn(ROR_MOTOR_CLOSE_RELAY)) { roofLastError="Error: Open already in motion"; return false; }

  // Handle case of Garage door opener where we're not sure which way it'll move
  if (!roofSafetyOverride && ROR_SINGLE_OPEN_CLOSE_RELAY == ON && !senseIsOn(ROR_LIMIT_SENSE_OPENED) && !senseIsOn(ROR_LIMIT_SENSE_CLOSED)) { roofLastError="Error: Motion direction unknown"; return false; }
  
  // Figure out where the roof is right now best as we can tell...
  // Check for limit switch and reset times
  if (senseIsOn(ROR_LIMIT_SENSE_CLOSED)) { EEPROM_writeLong(EE_timeLeftToOpen,roofTimeAvg); EEPROM_writeLong(EE_timeLeftToClose,0); }
  if (senseIsOn(ROR_LIMIT_SENSE_OPENED)) { EEPROM_writeLong(EE_timeLeftToOpen,0); EEPROM_writeLong(EE_timeLeftToClose,roofTimeAvg); }
  timeLeftToOpenAtStart =EEPROM_readLong(EE_timeLeftToOpen);
  timeLeftToCloseAtStart=EEPROM_readLong(EE_timeLeftToClose);

  // Check for validity of roof position timers before starting (they need to be within +/- 2 seconds)
  if (!roofSafetyOverride && (abs((timeLeftToOpenAtStart+timeLeftToCloseAtStart)-roofTimeAvg)>2000)) { roofLastError="Error: Open location unknown"; return false; }

  // Check to see if the roof is already opened
  if (senseIsOn(ROR_LIMIT_SENSE_OPENED) && !senseIsOn(ROR_LIMIT_SENSE_CLOSED)) { roofLastError="Warning: Already open"; return false; }

  // Just one last sanity check before we start moving the roof
  if (senseIsOn(ROR_LIMIT_SENSE_OPENED) && senseIsOn(ROR_LIMIT_SENSE_CLOSED)) { roofLastError="Error: Opened/closed limit sw on"; return false; }

  // Flag status, no errors
  roofState='o';
  roofStatusRegister=0;

  // Set relay/MOSFET
  if (ROR_MOTOR_RELAY_MOMENTARY != OFF) {
    delay(2000); 
    setRelayOnDelayedOff(ROR_MOTOR_OPEN_RELAY,2);
  } else {
    setRelayOff(ROR_MOTOR_CLOSE_RELAY);
    setRelayOn(ROR_MOTOR_OPEN_RELAY);
  }

  // Log start time
  roofOpenStartTime=(long)millis();

#if ROR_PWM_SOFTSTART == ON
  roofCurrentPower=0;
#else
  roofCurrentPower=ROR_PWM_POWER_PERCENT;
#endif

  roofLastError="";
  return true;
}

// Start closing the roof, returns true if successful or false otherwise (required)
bool startRoofClose() {
  if (roofState != 'i' || relayIsOn(ROR_MOTOR_OPEN_RELAY) || relayIsOn(ROR_MOTOR_CLOSE_RELAY)) { roofLastError="Error: Close already in motion"; return false; }

  // Handle case of Garage door opener where we're not sure which way it'll move
  if (!roofSafetyOverride && ROR_SINGLE_OPEN_CLOSE_RELAY == ON && !senseIsOn(ROR_LIMIT_SENSE_OPENED) && !senseIsOn(ROR_LIMIT_SENSE_CLOSED)) { roofLastError="Error: Motion direction unknown"; return false; }

  // Figure out where the roof is right now best as we can tell...
  // Check for limit switch and reset times
  if (senseIsOn(ROR_LIMIT_SENSE_CLOSED)) { EEPROM_writeLong(EE_timeLeftToOpen,roofTimeAvg); EEPROM_writeLong(EE_timeLeftToClose,0); }
  if (senseIsOn(ROR_LIMIT_SENSE_OPENED)) { EEPROM_writeLong(EE_timeLeftToOpen,0); EEPROM_writeLong(EE_timeLeftToClose,roofTimeAvg); }
  timeLeftToOpenAtStart =EEPROM_readLong(EE_timeLeftToOpen);
  timeLeftToCloseAtStart=EEPROM_readLong(EE_timeLeftToClose);

  // Check for validity of roof position timers before starting (they need to be within +/- 2 seconds)
  if (!roofSafetyOverride && abs((timeLeftToOpenAtStart+timeLeftToCloseAtStart)-roofTimeAvg) > 2000) { roofLastError="Error: Close location unknown"; return false; }

  // Check to see if the roof is already closed
  if (senseIsOn(ROR_LIMIT_SENSE_CLOSED) && (!senseIsOn(ROR_LIMIT_SENSE_OPENED))) { roofLastError="Warning: Already closed"; return false; }

  // Just one last sanity check before we start moving the roof
  if (senseIsOn(ROR_LIMIT_SENSE_CLOSED) && senseIsOn(ROR_LIMIT_SENSE_OPENED)) { roofLastError="Error: Closed/opened limit sw on"; return false; }

  // Flag status, no errors
  roofState='c';
  roofStatusRegister=0;

  // Set relay/MOSFET
  if (ROR_MOTOR_RELAY_MOMENTARY != OFF) {
    delay(2000);
    setRelayOnDelayedOff(ROR_MOTOR_CLOSE_RELAY,2);
  } else {
    setRelayOff(ROR_MOTOR_OPEN_RELAY);
    setRelayOn(ROR_MOTOR_CLOSE_RELAY);
  }

  // Log start time
  roofCloseStartTime=(long)millis();

#if ROR_PWM_SOFTSTART == ON
  roofCurrentPower=0;
#else
  roofCurrentPower=ROR_PWM_POWER_PERCENT;
#endif

  roofLastError="";
  return true;
}

// stop the roof, this must be ISR safe! (required)
void stopRoof() {
  // Reset possible override of roof timer
  roofSafetyOverride=false;
  // Reset roof power to normal level
  roofMaxPower=false;
  // Set the state to idle
  roofState='i';
  // Stop any DC motor
  setRelayOff(ROR_MOTOR_OPEN_RELAY);
  setRelayOff(ROR_MOTOR_CLOSE_RELAY);
  // And press the stop button if this roof has one
  if (ROR_MOTOR_RELAY_MOMENTARY != OFF && ROR_MOTOR_STOP_RELAY != OFF) setRelayOnDelayedOff(ROR_MOTOR_STOP_RELAY,2);
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
        if (senseIsOn(ROR_LIMIT_SENSE_CLOSED) && senseIsOn(ROR_LIMIT_SENSE_OPENED)) s="Error: Limit switch malfunction";
      } else s=roofLastError;
    }
  }
  return s;
}

// true if the roof is closed (required)
bool roofIsClosed() {
  return senseIsOn(ROR_LIMIT_SENSE_CLOSED) && (!senseIsOn(ROR_LIMIT_SENSE_OPENED));
}

// true if the roof is opened (required)
bool roofIsOpened() {
  return senseIsOn(ROR_LIMIT_SENSE_OPENED) && (!senseIsOn(ROR_LIMIT_SENSE_CLOSED));
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
