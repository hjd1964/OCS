// -----------------------------------------------------------------------------------------------------------------
// Roof control functions

#include "Roof.h"

#ifdef ROOF_PRESENT

#include "../../lib/tasks/OnTask.h"
#include "../../libApp/relay/Relay.h"
#include "../../lib/sense/Sense.h"

void roofWrapper() { roof.poll(); }
void parkCheckWrapper() { roof.parkCheckPoll(); }

// this gets called once on startup to initialize roof operation
void Roof::init() {
  // start polling task
  VF("MSG: Roof, start monitor task (rate 10ms priority 0)... ");
  if (tasks.add(10, 0, true, 0, roofWrapper, "Roof")) { VLF("success"); } else { VLF("FAILED!"); }
}

// Start opening the roof, returns true if successful or false otherwise
bool Roof::open() {
  if (state != 'i' || relay.isOn(ROOF_MOTOR_OPEN_RELAY) || relay.isOn(ROOF_MOTOR_CLOSE_RELAY) || relay.isOn(ROOF_MOTOR_STOP_RELAY)) {
    lastError = RERR_OPEN_EXCEPT_IN_MOTION;
    return false;
  }

  // Handle case of Garage door opener where we're not sure which way it'll move
  if (!safetyOverride && ROOF_SINGLE_OPEN_CLOSE_RELAY == ON && !sense.isOn(ROOF_LIMIT_OPENED_SENSE) && !sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    lastError = RERR_DIRECTION_UNKNOWN;
    return false;
  }
  
  // Figure out where the roof is right now best as we can tell...
  // Check for limit switch and reset times
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    nv.write(NV_ROOF_TIME_TO_OPEN, (int32_t)timeAvg);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (int32_t)0);
  }
  if (sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    nv.write(NV_ROOF_TIME_TO_OPEN, (int32_t)0);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (int32_t)timeAvg);
  }
  timeLeftToOpenAtStart = nv.readL(NV_ROOF_TIME_TO_OPEN);
  timeLeftToCloseAtStart = nv.readL(NV_ROOF_TIME_TO_CLOSE);

  // Check for validity of roof position timers before starting (they need to be within +/- 2 seconds)
  if (!safetyOverride && (abs((timeLeftToOpenAtStart + timeLeftToCloseAtStart) - timeAvg) > 2000)) {
    lastError = RERR_OPEN_LOCATION_UNKNOWN;
    return false;
  }

  // Check to see if the roof is already opened
  if (sense.isOn(ROOF_LIMIT_OPENED_SENSE) && !sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    lastError = RERR_OPEN_EXCEPT_OPENED;
    return false;
  }

  // Just one last sanity check before we start moving the roof
  if (sense.isOn(ROOF_LIMIT_OPENED_SENSE) && sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    lastError = RERR_OPEN_EXCEPT_CLOSED_LIMIT_SW_ON;
    return false;
  }

  #if ROOF_POWER_PWM_SOFTSTART == ON
    currentPower = 0;
  #else
    currentPower = ROOF_POWER_PWM_POWER;
  #endif

  // Flag status, no errors
  state = 'o';
  clearStatus(false);

  delay(ROOF_TIME_PRE_MOTION*1000);
  if (!safetyOverride && ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
    state = 'i';
    lastError = RERR_OPEN_SAFETY_INTERLOCK;
    return false;
  }

  // Set relay/MOSFET
  if (ROOF_MOTOR_RELAY_MOMENTARY == ON) {
    relay.onDelayedOff(ROOF_MOTOR_OPEN_RELAY, ROOF_TIME_BUTTON_PRESS);
  } else {
    relay.off(ROOF_MOTOR_CLOSE_RELAY);
    relay.on(ROOF_MOTOR_OPEN_RELAY);
  }

  // Log start time
  openStartTime = millis();

  lastError = RERR_NONE;
  return true;
}

// Start closing the roof, returns true if successful or false otherwise
bool Roof::close() {
  // Check to see if the roof is already closed
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE) && !sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    lastError = RERR_CLOSE_EXCEPT_CLOSED;
    return false;
  }

  // If mount must be parked for roof to close, issue a park signal and start park timer
  if (!safetyOverride && ROOF_CLOSE_PARKS_MOUNT != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE) && waitingForPark == 0) {
    VF("MSG: Start park monitor task (rate 1000ms priority 7)... ");
    if (tasks.add(1000, 0, true, 7, parkCheckWrapper, "pkPoll")) { VLF("success"); waitingForPark ++;} else { VLF("FAILED!"); }
    relay.on(ROOF_CLOSE_PARKS_MOUNT);
    return true;
  }

  // Park request has been issued, waiting for interlock to clear or timeout error
  if (waitingForPark > 0) {
    return true;
  }

  if (state != 'i' || relay.isOn(ROOF_MOTOR_OPEN_RELAY) || relay.isOn(ROOF_MOTOR_CLOSE_RELAY) || relay.isOn(ROOF_MOTOR_STOP_RELAY)) {
    lastError = RERR_CLOSE_EXCEPT_IN_MOTION;
    return false;
  }

  // Handle case of Garage door opener where we're not sure which way it'll move
  if (!safetyOverride && ROOF_SINGLE_OPEN_CLOSE_RELAY == ON && !sense.isOn(ROOF_LIMIT_OPENED_SENSE) && !sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    lastError = RERR_DIRECTION_UNKNOWN;
    return false;
  }

  // Figure out where the roof is right now best as we can tell...
  // Check for limit switch and reset times
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    nv.write(NV_ROOF_TIME_TO_OPEN, (int32_t)timeAvg);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (int32_t)0);
  }
  if (sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    nv.write(NV_ROOF_TIME_TO_OPEN, (int32_t)0);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (int32_t)timeAvg);
  }
  timeLeftToOpenAtStart = nv.readL(NV_ROOF_TIME_TO_OPEN);
  timeLeftToCloseAtStart = nv.readL(NV_ROOF_TIME_TO_CLOSE);

  // Check for validity of roof position timers before starting (they need to be within +/- 2 seconds)
  if (!safetyOverride && abs((timeLeftToOpenAtStart + timeLeftToCloseAtStart) - timeAvg) > 2000) {
    lastError = RERR_CLOSE_LOCATION_UNKNOWN;
    return false;
  }

    // Just one last sanity check before we start moving the roof
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE) && sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    lastError = RERR_CLOSE_EXCEPT_OPENED_LIMIT_SW_ON;
    return false;
  }

  #if ROOF_POWER_PWM_SOFTSTART == ON
    currentPower = 0;
  #else
    currentPower = ROOF_POWER_PWM_POWER;
  #endif

  // Flag status, no errors
  state = 'c';
  clearStatus(false);

  delay(ROOF_TIME_PRE_MOTION*1000);
  if (!safetyOverride && ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
    state = 'i';
    lastError = RERR_CLOSE_SAFETY_INTERLOCK;
    return false;
  }

  // Set relay/MOSFET
  if (ROOF_MOTOR_RELAY_MOMENTARY == ON) {
    relay.onDelayedOff(ROOF_MOTOR_CLOSE_RELAY, ROOF_TIME_BUTTON_PRESS);
  } else {
    relay.off(ROOF_MOTOR_OPEN_RELAY);
    relay.on(ROOF_MOTOR_CLOSE_RELAY);
  }

  // Log start time
  closeStartTime = (long)millis();

  lastError = RERR_NONE;
  return true;
}

// stop the roof, this must be ISR safe!
void Roof::stop() {
  // Reset possible override of roof timer
  safetyOverride = false;
  // Reset roof power to normal level
  maxPower = false;
  // Set the state to idle
  state = 'i';

  // Wait for any momentary relay to finish press
  bool wasActive = false;
  while (relay.isOnDelayedOff(ROOF_MOTOR_OPEN_RELAY) || relay.isOnDelayedOff(ROOF_MOTOR_CLOSE_RELAY) || relay.isOnDelayedOff(ROOF_MOTOR_STOP_RELAY)) {
    wasActive = true;
    delay(100);
  }
  if (wasActive) delay(ROOF_TIME_POST_MOTION*1000);

  // Stop any DC motor
  relay.off(ROOF_MOTOR_OPEN_RELAY);
  relay.off(ROOF_MOTOR_CLOSE_RELAY);

  // And press the stop button if this roof has one
  if (ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY != OFF) {
    // make sure any button press is finished before pressing again
    relay.onDelayedOff(ROOF_MOTOR_STOP_RELAY, ROOF_TIME_BUTTON_PRESS);
  }

  // If there is a close waiting for mount to park, cancel it
  stopWaitingForPark();
}

// clear errors
void Roof::clearStatus(bool last) {
  fault.closeInterlock = false;
  fault.closeLimitSW = false;
  fault.closeOverTime = false;
  fault.closeUnderTime = false;
  fault.closeUnknown = false;
  fault.openInterlock = false;
  fault.openLimitSW = false;
  fault.openOverTime = false;
  fault.openUnderTime = false;
  fault.openUnknown = false;
  fault.closeNotParked = false;
  if (last) lastError = RERR_NONE;
}

// returns an description string of the roof state
const char * Roof::statusMessage() {
  if (!roof.isMoving()) {
    if (roof.isClosed()) return L_CLOSED; else { if (roof.isOpen()) return L_OPEN; else return L_STOPPED; }
  } else {
    if (roof.isOpening()) return L_OPENING; else { if (roof.isClosing()) return L_CLOSING; }
  }
  return L_UNKNOWN;
}

// returns an error description string if an error has occured, otherwise must return "Travel: n%" or "No Error"
const char * Roof::errorMessage() {
  const char *strErr = getLastError();
  if (strlen(strErr) == 0 && isMoving()) {
    static char travelMessage[20];
    sprintf(travelMessage, L_TRAVEL ": %ld%%", travel);
    return travelMessage;
  }
  if (strlen(strErr) == 0 && waitingForPark > 0) {
    return L_WAIT_FOR_PARK;
  } else if (strlen(strErr) == 0) return L_NO_ERROR;
  return strErr;
}

const char roofErrorMessage1[] PROGMEM = L_ROOF_ERR1;
const char roofErrorMessage2[] PROGMEM = L_ROOF_ERR2;
const char roofErrorMessage3[] PROGMEM = L_ROOF_ERR3;
const char roofErrorMessage4[] PROGMEM = L_ROOF_ERR4;
const char roofErrorMessage5[] PROGMEM = L_ROOF_ERR5;
const char roofErrorMessage6[] PROGMEM = L_ROOF_ERR6;
const char roofErrorMessage7[] PROGMEM = L_ROOF_ERR7;
const char roofErrorMessage8[] PROGMEM = L_ROOF_ERR8;
const char roofErrorMessage9[] PROGMEM = L_ROOF_ERR9;
const char roofErrorMessage10[] PROGMEM = L_ROOF_ERR10;
const char roofErrorMessage11[] PROGMEM = L_ROOF_ERR11;
const char roofErrorMessage12[] PROGMEM = L_ROOF_ERR12;
const char roofErrorMessage13[] PROGMEM = L_ROOF_ERR13;
const char roofErrorMessage14[] PROGMEM = L_ROOF_ERR14;
const char roofErrorMessage15[] PROGMEM = L_ROOF_ERR15;
const char roofErrorMessage16[] PROGMEM = L_ROOF_ERR16;
const char roofErrorMessage17[] PROGMEM = L_ROOF_ERR17;
const char roofErrorMessage18[] PROGMEM = L_ROOF_ERR18;
const char roofErrorMessage19[] PROGMEM = L_ROOF_ERR19;
const char roofErrorMessage20[] PROGMEM = L_ROOF_ERR20;
const char roofErrorMessage21[] PROGMEM = L_ROOF_ERR21;

// returns an error description string if an error has occured, "" if no error
const char * Roof::getLastError() {
  static char errorMessage[36];

  RoofError err = RERR_NONE;
  if (fault.openInterlock)  err = RERR_OPEN_SAFETY_INTERLOCK; else
  if (fault.closeInterlock) err = RERR_CLOSE_SAFETY_INTERLOCK; else
  if (fault.openUnknown)    err = RERR_OPEN_UNKNOWN; else
  if (fault.openLimitSW)    err = RERR_OPEN_LIMIT_SW; else
  if (fault.openOverTime)   err = RERR_OPEN_MAX_TIME; else
  if (fault.openUnderTime)  err = RERR_OPEN_MIN_TIME; else
  if (fault.closeUnknown)   err = RERR_CLOSE_UNKNOWN; else
  if (fault.closeLimitSW)   err = RERR_CLOSE_LIMIT_SW; else
  if (fault.closeOverTime)  err = RERR_CLOSE_MAX_TIME; else
  if (fault.closeUnderTime) err = RERR_CLOSE_MIN_TIME; else
  if (fault.closeNotParked) err = RERR_CLOSE_EXCEPT_MOUNT_NOT_PARKED;
  if (err == RERR_NONE) {
    if (state == 'i') {
      if (lastError == RERR_NONE) {
        if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE) && sense.isOn(ROOF_LIMIT_OPENED_SENSE)) err = RERR_LIMIT_SW;
      } else err = lastError;
    }
  }

  switch (err) {
    case 0: strcpy(errorMessage, ""); break;
    case 1: strcpy_P(errorMessage, roofErrorMessage1); break;
    case 2: strcpy_P(errorMessage, roofErrorMessage2); break;
    case 3: strcpy_P(errorMessage, roofErrorMessage3); break;
    case 4: strcpy_P(errorMessage, roofErrorMessage4); break;
    case 5: strcpy_P(errorMessage, roofErrorMessage5); break;
    case 6: strcpy_P(errorMessage, roofErrorMessage6); break;
    case 7: strcpy_P(errorMessage, roofErrorMessage7); break;
    case 8: strcpy_P(errorMessage, roofErrorMessage8); break;
    case 9: strcpy_P(errorMessage, roofErrorMessage9); break;
    case 10: strcpy_P(errorMessage, roofErrorMessage10); break;
    case 11: strcpy_P(errorMessage, roofErrorMessage11); break;
    case 12: strcpy_P(errorMessage, roofErrorMessage12); break;
    case 13: strcpy_P(errorMessage, roofErrorMessage13); break;
    case 14: strcpy_P(errorMessage, roofErrorMessage14); break;
    case 15: strcpy_P(errorMessage, roofErrorMessage15); break;
    case 16: strcpy_P(errorMessage, roofErrorMessage16); break;
    case 17: strcpy_P(errorMessage, roofErrorMessage17); break;
    case 18: strcpy_P(errorMessage, roofErrorMessage18); break;
    case 19: strcpy_P(errorMessage, roofErrorMessage19); break;
    case 20: strcpy_P(errorMessage, roofErrorMessage20); break;
    case 21: strcpy_P(errorMessage, roofErrorMessage21); break;
  }

  return errorMessage;
}

// true if the roof is closed
bool Roof::isClosed() {
  return (sense.isOn(ROOF_LIMIT_CLOSED_SENSE) && !sense.isOn(ROOF_LIMIT_OPENED_SENSE));
}

// true if the roof is opened
bool Roof::isOpen() {
  return (sense.isOn(ROOF_LIMIT_OPENED_SENSE) && !sense.isOn(ROOF_LIMIT_CLOSED_SENSE));
}

// true if the roof is moving
bool Roof::isMoving() {
  return (state != 'i');
}

// true if the roof is moving (closing)
bool Roof::isClosing() {
  return (state == 'c');
}

// true if the roof is moving (opening)
bool Roof::isOpening() {
  return (state == 'o');
}

// safety override, ignores stuck limit switch and timeout
void Roof::setSafetyOverride() {
  safetyOverride = true;
}

// required
bool Roof::setSafetyOverride(bool value) {
  return safetyOverride = value;
}

// forces pwm power to 100%
void Roof::setMaxPower() {
  maxPower = true;
}

// required
bool Roof::isMaxPower() {
  return maxPower;
}

// for soft start etc, pwm power level
int Roof::powerLevel() {
  return currentPower;
}

// called repeatedly to open the roof
void Roof::continueOpening() {
  cli();
  long msOfTravel = (long)(millis() - openStartTime);
  sei();

  #if ROOF_POWER_PWM_SOFTSTART == ON
    if (currentPower < ROOF_POWER_PWM_POWER) {
      cli();
      currentPower = msOfTravel/200;
      if (currentPower > ROOF_POWER_PWM_POWER) currentPower = ROOF_POWER_PWM_POWER;
      sei();
    }
  #endif

  // calculate how far we are from opening and closing the roof right now
  long timeLeftToOpenNow = timeLeftToOpenAtStart - msOfTravel;
  if (timeLeftToOpenNow < 0) timeLeftToOpenNow = 0;
  long timeLeftToCloseNow = timeAvg - timeLeftToOpenNow;

  // keep track of where we are (to the nearest five seconds)
  long secondsOfTravel = round(msOfTravel/5000)*5000;
  if (lastSecondsOfTravel != secondsOfTravel) {
    lastSecondsOfTravel = secondsOfTravel;
    nv.write(NV_ROOF_TIME_TO_OPEN, (int32_t)timeLeftToOpenNow);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (int32_t)timeLeftToCloseNow);
  }

  // Or a stuck limit switch
  if (!safetyOverride && (timeAvg - timeLeftToOpenNow) > ROOF_TIME_LIMIT_SENSE_FAIL*1000 && sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    // Set the error in the status register, the user can resume the opening operation by checking for any malfunction then using the safety override if required
    fault.openLimitSW = true;
    // Go idle (assume the roof is still moving where we can't cut the power)
    if (!(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)) state = 'i';
  }

  // Or interlock was triggered
  if (!safetyOverride && ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
    // Set the error in the status register, the user can resume the opening operation by checking for any malfunction then using the safety override if required
    fault.openInterlock = true;
    // Go idle (assume the roof is still moving where we can't cut the power)
    if (!(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)) state = 'i';
  }

  // Or the whole process taking too long
  if (!safetyOverride && (timeLeftToOpenAtStart - msOfTravel) < -timeErrorLimit) {
    // Set the error in the status register, the user can resume the opening operation by checking for any malfunction then using the safety override if required
    fault.openOverTime = true;
    // Go idle (assume the roof has stopped where we can't cut the power)
    state = 'i';
  }

  // Calculate a percentage of roof travel
  travel = ((float)(timeAvg - (timeLeftToOpenAtStart - msOfTravel))/(float)timeAvg)*100;

  // Detect that the roof has finished opening
  if (sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    // wait for a bit before powering off the roof drive (for automatic opener that stops itself)
    if (ROOF_MOTOR_RELAY_MOMENTARY == ON) tasks.yield(ROOF_TIME_POST_MOTION*1000);
    // reset position timers
    nv.write(NV_ROOF_TIME_TO_OPEN, (int32_t)0);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (int32_t)timeAvg);
    // Go idle
    state = 'i';
  }

  // Finished opening? stop the motion and clear state
  if (state == 'i') {
    // Stop the roof motor (redundant for momentary control)
    relay.off(ROOF_MOTOR_OPEN_RELAY);
    // Reset possible override of roof timer
    safetyOverride = false;
    // Reset roof power to normal level
    maxPower = false;
  }
}

// called repeatedly to close the roof
void Roof::continueClosing() {
  cli();
  long msOfTravel = (long)(millis() - closeStartTime);
  sei();

  #if ROOF_POWER_PWM_SOFTSTART == ON
    if (currentPower < ROOF_POWER_PWM_POWER) {
      cli();
      currentPower = msOfTravel/200;
      if (currentPower > ROOF_POWER_PWM_POWER) currentPower = ROOF_POWER_PWM_POWER;
      sei();
    }
  #endif
  
  // calculate how far we are from opening and closing the roof right now
  long timeLeftToCloseNow = timeLeftToCloseAtStart - msOfTravel;
  if (timeLeftToCloseNow < 0) timeLeftToCloseNow = 0;
  long timeLeftToOpenNow = timeAvg - timeLeftToCloseNow;

  // keep track of where we are, if power goes out, for example
  long secondsOfTravel = round(msOfTravel/5000)*5000;
  if (lastSecondsOfTravel != secondsOfTravel) {
    lastSecondsOfTravel = secondsOfTravel;
    nv.write(NV_ROOF_TIME_TO_OPEN, (int32_t)timeLeftToOpenNow);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (int32_t)timeLeftToCloseNow);
  }

  // On a stuck limit switch
  if (!safetyOverride && (timeAvg-timeLeftToCloseNow) > ROOF_TIME_LIMIT_SENSE_FAIL*1000 && sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
    fault.closeLimitSW = true;
    // Go idle (assume the roof is still moving where we can't cut the power)
    if (!(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)) state = 'i';
  }

  // Or interlock was triggered
  if (!safetyOverride && ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
    // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
    fault.closeInterlock = true;
    // Go idle (assume the roof is still moving where we can't cut the power)
    if (!(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)) state = 'i';
  }

  // Or the whole process is taking too long
  if (!safetyOverride && (timeLeftToCloseAtStart - msOfTravel) < -timeErrorLimit) {
    // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
    fault.closeOverTime = true;
    // Go idle (assume the roof has stopped where we can't cut the power)
    state = 'i';
  }

  // Calculate a percentage of roof travel
  travel = ((float)(timeAvg - (timeLeftToCloseAtStart - msOfTravel))/(float)timeAvg)*100;

  // Detect that the roof has finished closing
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    // wait for a bit before powering off the roof drive (for automatic opener that stops itself)
    if (ROOF_MOTOR_RELAY_MOMENTARY == ON) tasks.yield(ROOF_TIME_POST_MOTION*1000);
    // reset position timers
    nv.write(NV_ROOF_TIME_TO_OPEN, (int32_t)timeAvg);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (int32_t)0);
    // Go idle
    state = 'i';
  }
  
  // Finished closing? stop the motion and clear state
  if (state == 'i') {
    // Stop the roof motor (redundant for momentary control)
    relay.off(ROOF_MOTOR_CLOSE_RELAY);
    // Reset possible override of roof timer
    safetyOverride = false;
    // Reset roof power to normal level
    maxPower = false;
  }
}

// cancel a waiting for park sequence
void Roof::stopWaitingForPark() {
  tasks.setDurationComplete(tasks.getHandleByName("pkPoll"));
  relay.off(ROOF_CLOSE_PARKS_MOUNT);
  waitingForPark = 0;
}

// called repeatedly to check if the mount is parked to trigger roof close
void Roof::parkCheckPoll() {
  if (sense.isOn(ROOF_INTERLOCK_SENSE) || waitingForPark >= MOUNT_PARK_TIMEOUT) {
    stopWaitingForPark();
    if (waitingForPark >= MOUNT_PARK_TIMEOUT) lastError = RERR_CLOSE_EXCEPT_MOUNT_NOT_PARKED; else close();
  } else waitingForPark ++;
}

// called repeatedly to control roof movement
void Roof::poll() {
  if (!roof.isMoving()) return;

  // Open the roof, keeping track of time limit and sensor status
  if (isOpening()) continueOpening();

  // Close the roof, keeping track of time limit and sensor status
  if (isClosing()) continueClosing();
}

Roof roof;

#endif
