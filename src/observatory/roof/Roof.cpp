// -----------------------------------------------------------------------------------------------------------------
// Roof control functions

#include "Roof.h"

#ifdef ROOF_PRESENT

#include "../../lib/tasks/OnTask.h"
#include "../../libApp/relay/Relay.h"
#include "../../lib/sense/Sense.h"

void roofWrapper() { roof.poll(); }

// this gets called once on startup to initialize roof operation (required)
void Roof::init() {
  // start polling task
  VF("MSG: Roof, start monitor task (rate 10ms priority 0)... ");
  if (tasks.add(10, 0, true, 0, roofWrapper, "Roof")) { VLF("success"); } else { VLF("FAILED!"); }
}

// Start opening the roof, returns true if successful or false otherwise (required)
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

  delay(ROOF_PRE_MOTION_TIME*1000);
  if (ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
    state = 'i';
    lastError = RERR_OPEN_SAFETY_INTERLOCK;
    return false;
  }

  // Set relay/MOSFET
  if (ROOF_MOTOR_RELAY_MOMENTARY == ON) {
    relay.onDelayedOff(ROOF_MOTOR_OPEN_RELAY, ROOF_MOMENTARY_BUTTON_PRESS_TIME);
  } else {
    relay.off(ROOF_MOTOR_CLOSE_RELAY);
    relay.on(ROOF_MOTOR_OPEN_RELAY);
  }

  // Log start time
  openStartTime = millis();

  lastError = RERR_NONE;
  return true;
}

// Start closing the roof, returns true if successful or false otherwise (required)
bool Roof::close() {
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

  // Check to see if the roof is already closed
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE) && !sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    lastError = RERR_CLOSE_EXCEPT_CLOSED;
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

  delay(ROOF_PRE_MOTION_TIME*1000);
  if (ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
    state = 'i';
    lastError = RERR_CLOSE_SAFETY_INTERLOCK;
    return false;
  }

  // Set relay/MOSFET
  if (ROOF_MOTOR_RELAY_MOMENTARY == ON) {
    relay.onDelayedOff(ROOF_MOTOR_CLOSE_RELAY, ROOF_MOMENTARY_BUTTON_PRESS_TIME);
  } else {
    relay.off(ROOF_MOTOR_OPEN_RELAY);
    relay.on(ROOF_MOTOR_CLOSE_RELAY);
  }

  // Log start time
  closeStartTime = (long)millis();

  lastError = RERR_NONE;
  return true;
}

// stop the roof, this must be ISR safe! (required)
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
  if (wasActive) delay(ROOF_POST_MOTION_TIME*1000);

  // Stop any DC motor
  relay.off(ROOF_MOTOR_OPEN_RELAY);
  relay.off(ROOF_MOTOR_CLOSE_RELAY);

  // And press the stop button if this roof has one
  if (ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY != OFF) {
    // make sure any 2 second button press is finished before pressing again
    relay.onDelayedOff(ROOF_MOTOR_STOP_RELAY, ROOF_MOMENTARY_BUTTON_PRESS_TIME);
  }
}

// clear errors (required)
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
  if (last) lastError = RERR_NONE;
}

// returns an error description string if an error has occured, otherwise must return "Travel: n%" or "No Error" (required)
const char * Roof::getStatus() {
  const char *strErr = getLastError();
  if (strlen(strErr) == 0 && isMoving()) {
    static char travelMessage[20];
    sprintf(travelMessage, "Travel: %ld%%", travel);
    return travelMessage;
  }
  if (strlen(strErr) == 0) return "No Error";
  return strErr;
}

// returns an error description string if an error has occured, "" if no error (required)
const char * Roof::getLastError() {
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
  if (fault.closeUnderTime) err = RERR_CLOSE_MIN_TIME;
  if (err == RERR_NONE) {
    if (state == 'i') {
      if (lastError == RERR_NONE) {
        if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE) && sense.isOn(ROOF_LIMIT_OPENED_SENSE)) err = RERR_LIMIT_SW;
      } else err = lastError;
    }
  }
  return ErrorMessage[err];
}

// true if the roof is closed (required)
bool Roof::isClosed() {
  return (sense.isOn(ROOF_LIMIT_CLOSED_SENSE) && !sense.isOn(ROOF_LIMIT_OPENED_SENSE));
}

// true if the roof is opened (required)
bool Roof::isOpen() {
  return (sense.isOn(ROOF_LIMIT_OPENED_SENSE) && !sense.isOn(ROOF_LIMIT_CLOSED_SENSE));
}

// true if the roof is moving (required)
bool Roof::isMoving() {
  return (state != 'i');
}

// true if the roof is moving (closing, required)
bool Roof::isClosing() {
  return (state == 'c');
}

// true if the roof is moving (opening, required)
bool Roof::isOpening() {
  return (state == 'o');
}

// safety override, ignores stuck limit switch and timeout (required)
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

// for soft start etc, pwm power level (required)
int Roof::powerLevel() {
  return currentPower;
}

// called repeatedly if roof is moving (required)
void Roof::poll() {
  if (!roof.isMoving()) return;

  // Open the roof, keeping track of time limit and sensor status
  if (isOpening()) continueOpening();

  // Close the roof, keeping track of time limit and sensor status
  if (isClosing()) continueClosing();
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
  if (ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
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
    if (ROOF_MOTOR_RELAY_MOMENTARY == ON) tasks.yield(ROOF_POST_MOTION_TIME*1000);
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
  if (ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
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
    if (ROOF_MOTOR_RELAY_MOMENTARY == ON) tasks.yield(ROOF_POST_MOTION_TIME*1000);
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

Roof roof;

#endif
