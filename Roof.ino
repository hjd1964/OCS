// -----------------------------------------------------------------------------------------------------------------
// Roof control functions

#ifdef ROR_ON
// keep track of what the roof is doing
const long roofTimeAvg        = (long)(ROR_TIME_AVG)*1000L;
const long roofTimeErrorLimit = (long)(ROR_TIME_TOL)*1000L;
int  roofPower;
long secondsOfTravel,lastSecondsOfTravel,lastMillis,msOfTravel,roofOpenStartTime,roofCloseStartTime,
     timeLeftToOpenNow,timeLeftToOpenAtStart,timeLeftToCloseNow,timeLeftToCloseAtStart;
long roofTravel=0;
     
// open the roof
void openRoof() {
    cli(); msOfTravel=((long)millis()-roofOpenStartTime); sei();

#ifdef ROR_SOFTSTART_ON
    if (roofCurrentPower<ROR_PWM_POWER_PERCENT) {
      cli(); roofCurrentPower=msOfTravel/200; if (roofCurrentPower>ROR_PWM_POWER_PERCENT) roofCurrentPower=ROR_PWM_POWER_PERCENT; sei();
    }
#endif

    // calculate how far we are from opening and closing the roof right now
    timeLeftToOpenNow=timeLeftToOpenAtStart-msOfTravel;
    if (timeLeftToOpenNow<0) { timeLeftToOpenNow=0; }
    timeLeftToCloseNow=roofTimeAvg-timeLeftToOpenNow;

    // keep track of where we are (to the nearest five seconds)
    secondsOfTravel=round(msOfTravel/5000)*5000;
    if (lastSecondsOfTravel!=secondsOfTravel) {
      lastSecondsOfTravel=secondsOfTravel;
      EEPROM_writeLong(EE_timeLeftToOpen,timeLeftToOpenNow);
      EEPROM_writeLong(EE_timeLeftToClose,timeLeftToCloseNow);
    }

    // Or a stuck limit switch
    if ((!roofSafetyOverride) && (((roofTimeAvg-timeLeftToOpenNow)>ROR_TIME_LIMIT_FAIL*1000) && (digitalRead(sensePin[ROR_CLOSED_LIMIT_SENSE])==HIGH))) {
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
    senseState[ROR_OPENED_LIMIT_SENSE]=digitalRead(sensePin[ROR_OPENED_LIMIT_SENSE]);
    if (senseState[ROR_OPENED_LIMIT_SENSE]==HIGH) {
      // reset position timers
      EEPROM_writeLong(EE_timeLeftToOpen,0);
      EEPROM_writeLong(EE_timeLeftToClose,roofTimeAvg);
      // Go idle
      roofState='i';
    }

    // Finished opening? stop the motion and clear state
    if (roofState=='i') {
      // Stop the winch
      digitalWrite(relayPin[ROR_DIR_RELAY_A], LOW);
      relayState[ROR_DIR_RELAY_A]=0;
      // Reset the status register
      // roofStatusRegister=0;
      // Reset possible override of roof timer
      roofSafetyOverride=false;
      // Reset roof power to normal level
      roofMaxPower=false;
    }
}

// close the roof
void closeRoof() {
    cli(); msOfTravel=(long)millis()-roofCloseStartTime; sei();

#ifdef ROR_SOFTSTART_ON
    if (roofCurrentPower<ROR_PWM_POWER_PERCENT) {
      cli(); roofCurrentPower=msOfTravel/200; if (roofCurrentPower>ROR_PWM_POWER_PERCENT) roofCurrentPower=ROR_PWM_POWER_PERCENT; sei();
    }
#endif
    
    // calculate how far we are from opening and closing the roof right now
    timeLeftToCloseNow=timeLeftToCloseAtStart-msOfTravel;
    if (timeLeftToCloseNow<0) { timeLeftToCloseNow=0; }
    timeLeftToOpenNow=roofTimeAvg-timeLeftToCloseNow;

    // keep track of where we are, if power goes out, for example
    secondsOfTravel=round(msOfTravel/5000)*5000;
    if (lastSecondsOfTravel!=secondsOfTravel) {
      lastSecondsOfTravel=secondsOfTravel;
      EEPROM_writeLong(EE_timeLeftToOpen,timeLeftToOpenNow);
      EEPROM_writeLong(EE_timeLeftToClose,timeLeftToCloseNow);
    }

    // Or a stuck limit switch
    if ((!roofSafetyOverride) && (((roofTimeAvg-timeLeftToCloseNow)>ROR_TIME_LIMIT_FAIL*1000) && (digitalRead(sensePin[ROR_OPENED_LIMIT_SENSE])==HIGH))) {
      // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
      roofStatusRegister=roofStatusRegister|0b00000100; // 4
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
    senseState[ROR_CLOSED_LIMIT_SENSE]=digitalRead(sensePin[ROR_CLOSED_LIMIT_SENSE]);
    if (senseState[ROR_CLOSED_LIMIT_SENSE]==HIGH) {
      // reset position timers
      EEPROM_writeLong(EE_timeLeftToOpen,roofTimeAvg);
      EEPROM_writeLong(EE_timeLeftToClose,0);
      // Go idle
      roofState='i';
    }
    
    // Finished closing? stop the motion and clear state
    if (roofState=='i') {
      // Stop the winch
      digitalWrite(relayPin[ROR_DIR_RELAY_B],LOW);
      relayState[ROR_DIR_RELAY_B]=0;
      // Reset the status register
      // roofStatusRegister=0;
      // Reset possible override of roof timer
      roofSafetyOverride=false;
      // Reset roof power to normal level
      roofMaxPower=false;
    }
}

// Check for command to open the roof
bool startRoofOpen() {
  if ((roofState=='i') && (relayState[ROR_DIR_RELAY_B]!=1)) {
    // Figure out where the roof is right now best as we can tell...
    // Check for limit switch and reset times
    senseState[ROR_CLOSED_LIMIT_SENSE]=digitalRead(sensePin[ROR_CLOSED_LIMIT_SENSE]);
    if (senseState[ROR_CLOSED_LIMIT_SENSE]==HIGH) { EEPROM_writeLong(EE_timeLeftToOpen,roofTimeAvg); EEPROM_writeLong(EE_timeLeftToClose,0); }
    senseState[ROR_OPENED_LIMIT_SENSE]=digitalRead(sensePin[ROR_OPENED_LIMIT_SENSE]);
    if (senseState[ROR_OPENED_LIMIT_SENSE]==HIGH) { EEPROM_writeLong(EE_timeLeftToOpen,0); EEPROM_writeLong(EE_timeLeftToClose,roofTimeAvg); }
    timeLeftToOpenAtStart =EEPROM_readLong(EE_timeLeftToOpen);
    timeLeftToCloseAtStart=EEPROM_readLong(EE_timeLeftToClose);
//    Serial.println(sense1);
//    Serial.println(sense2);
//    Serial.println(roofTimeAvg);

    // Check for validity of roof position timers before starting (they need to be within +/- 2 seconds)
    if ((!roofSafetyOverride) && (abs((timeLeftToOpenAtStart+timeLeftToCloseAtStart)-roofTimeAvg)>2000)) {
      roofLastError="Open Error: Location unknown";
    } else {
      // Check to see if the roof is already opened
      if ((senseState[1]==LOW) && (senseState[2]==HIGH)) {
        roofLastError="Open Warning: Already open";
      } else {
        // Just one last sanity check before we start moving the roof
        if ((senseState[1]==HIGH) && (senseState[2]==HIGH)) {
          roofLastError="Open Error: Limit switch malfunction";
        } else {
          // Set relay/MOSFET
          relayState[ROR_DIR_RELAY_B]=0; digitalWrite(relayPin[ROR_DIR_RELAY_B],LOW);
          relayState[ROR_DIR_RELAY_A]=1; digitalWrite(relayPin[ROR_DIR_RELAY_A],HIGH);

          // Flag status, no errors
          roofState='o';
          roofStatusRegister=0;

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
    roofLastError="Open Error: Already in motion";
  }
  return false;
}

// Check for command to close the roof
bool startRoofClose() {
  if ((roofState=='i') && (relayState[ROR_DIR_RELAY_A]!=1)) {
    // Figure out where the roof is right now best as we can tell...
    // Check for limit switch and reset times
    senseState[ROR_CLOSED_LIMIT_SENSE]=digitalRead(sensePin[ROR_CLOSED_LIMIT_SENSE]);
    if (senseState[ROR_CLOSED_LIMIT_SENSE]==HIGH) { EEPROM_writeLong(EE_timeLeftToOpen,roofTimeAvg); EEPROM_writeLong(EE_timeLeftToClose,0); }
    senseState[ROR_OPENED_LIMIT_SENSE]=digitalRead(sensePin[ROR_OPENED_LIMIT_SENSE]);
    if (senseState[ROR_OPENED_LIMIT_SENSE]==HIGH) { EEPROM_writeLong(EE_timeLeftToOpen,0); EEPROM_writeLong(EE_timeLeftToClose,roofTimeAvg); }
    timeLeftToOpenAtStart =EEPROM_readLong(EE_timeLeftToOpen);
    timeLeftToCloseAtStart=EEPROM_readLong(EE_timeLeftToClose);
//    Serial.println(timeLeftToOpenAtStart);
//    Serial.println(timeLeftToCloseAtStart);
//    Serial.println(roofTimeAvg);

    // Check for validity of roof position timers before starting (they need to be within +/- 2 seconds)
    if ((!roofSafetyOverride) && (abs((timeLeftToOpenAtStart+timeLeftToCloseAtStart)-roofTimeAvg)>2000)) {
      roofLastError="Close Error: Location unknown";
    } else {
      // Check to see if the roof is already closed
      if ((senseState[ROR_CLOSED_LIMIT_SENSE]==HIGH) && (senseState[ROR_OPENED_LIMIT_SENSE]==LOW)) {
        roofLastError="Close Warning: Already closed";
      } else {
        // Just one last sanity check before we start moving the roof
        if ((senseState[ROR_CLOSED_LIMIT_SENSE]==HIGH) && (senseState[ROR_OPENED_LIMIT_SENSE]==HIGH)) {
          Serial.println("Close Error: Limit switch malfunction");
        } else {
          // Set relay/MOSFET
          relayState[ROR_DIR_RELAY_A]=0; digitalWrite(relayPin[ROR_DIR_RELAY_A],LOW);
          relayState[ROR_DIR_RELAY_B]=1; digitalWrite(relayPin[ROR_DIR_RELAY_B],HIGH);

          // Flag status, no errors
          roofState='c';
          roofStatusRegister=0;

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
  } else {
    roofLastError="Close Error: Already in motion";
  }
  return false;
}

void stopRoof() {
  // Reset the status register
  roofStatusRegister=0;
  roofLastError="";
  // Reset possible override of roof timer
  roofSafetyOverride=false;
  // Reset roof power to normal level
  roofMaxPower=false;
  // Set the state to idle
  roofState='i';
  // Stop the winch
  relayState[ROR_DIR_RELAY_A]=0; digitalWrite(relayPin[ROR_DIR_RELAY_A], LOW);
  relayState[ROR_DIR_RELAY_B]=0; digitalWrite(relayPin[ROR_DIR_RELAY_B], LOW);
}

String getRoofStatus() {
  String s="";
  if (roofStatusRegister&128) s="Open Error: Unknown error"; else
  if (roofStatusRegister&64) s="Open Error: Closed limit sw fail"; else
  if (roofStatusRegister&32) s="Open Error: Over time"; else
  if (roofStatusRegister&16) s="Open Error: Under time"; else
  if (roofStatusRegister&8) s="Close Error: Unknown error"; else
  if (roofStatusRegister&4) s="Close Error: Open limit sw fail"; else
  if (roofStatusRegister&2) s="Close Error: Over time"; else
  if (roofStatusRegister&1) s="Close Error: Under time";
  if (s=="") {
    if (roofState=='i') {
      if (roofLastError=="") {
        // one final check for any wierd relay stuff going on
        senseState[ROR_CLOSED_LIMIT_SENSE]=digitalRead(sensePin[ROR_CLOSED_LIMIT_SENSE]);
        senseState[ROR_OPENED_LIMIT_SENSE]=digitalRead(sensePin[ROR_OPENED_LIMIT_SENSE]);
        if ((senseState[ROR_CLOSED_LIMIT_SENSE]==HIGH) && (senseState[ROR_OPENED_LIMIT_SENSE]==HIGH)) { s="Error: Limit switch malfunction"; } else s="No Error";
      } else s=roofLastError;
    } else { s="Travel: "+String(roofTravel)+"%"; }
  }
  return s;
}

bool isRoofClosed() {
  senseState[ROR_CLOSED_LIMIT_SENSE]=digitalRead(sensePin[ROR_CLOSED_LIMIT_SENSE]);
  return senseState[ROR_CLOSED_LIMIT_SENSE];
}

bool isRoofOpened() {
  senseState[ROR_OPENED_LIMIT_SENSE]=digitalRead(sensePin[ROR_OPENED_LIMIT_SENSE]);
  return senseState[ROR_OPENED_LIMIT_SENSE];
}

bool isRoofMoving() {
  return (roofState!='i');
}

#endif

