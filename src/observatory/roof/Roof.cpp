// -----------------------------------------------------------------------------------------------------------------
// Roof control functions

#include "Roof.h"

#if ROOF == ON

#include "../../lib/relay/Relay.h"
#include "../../lib/sense/Sense.h"

// this gets called once on startup to initialize roof operation (required)
void Roof::init() {
}

// Start opening the roof, returns true if successful or false otherwise (required)
bool Roof::open() {
  if (state != 'i' || relay.isOn(ROOF_MOTOR_OPEN_RELAY) || relay.isOn(ROOF_MOTOR_CLOSE_RELAY) || relay.isOn(ROOF_MOTOR_STOP_RELAY)) {
    lastError = "Error: Open already in motion";
    return false;
  }

  // Handle case of Garage door opener where we're not sure which way it'll move
  if (!safetyOverride && ROOF_SINGLE_OPEN_CLOSE_RELAY == ON && !sense.isOn(ROOF_LIMIT_OPENED_SENSE) && !sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    lastError = "Error: Motion direction unknown";
    return false;
  }
  
  // Figure out where the roof is right now best as we can tell...
  // Check for limit switch and reset times
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    nv.write(NV_ROOF_TIME_TO_OPEN, (long)timeAvg);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (long)0);
  }
  if (sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    nv.write(NV_ROOF_TIME_TO_OPEN, (long)0);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (long)timeAvg);
  }
  timeLeftToOpenAtStart = nv.readL(NV_ROOF_TIME_TO_OPEN);
  timeLeftToCloseAtStart = nv.readL(NV_ROOF_TIME_TO_CLOSE);

  // Check for validity of roof position timers before starting (they need to be within +/- 2 seconds)
  if (!safetyOverride && (abs((timeLeftToOpenAtStart+timeLeftToCloseAtStart) - timeAvg) > 2000)) {
    lastError = "Error: Open location unknown";
    return false;
  }

  // Check to see if the roof is already opened
  if (sense.isOn(ROOF_LIMIT_OPENED_SENSE) && !sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    lastError = "Warning: Already open";
    return false;
  }

  // Just one last sanity check before we start moving the roof
  if (sense.isOn(ROOF_LIMIT_OPENED_SENSE) && sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    lastError = "Error: Opened/closed limit sw on";
    return false;
  }

  #if ROOF_POWER_PWM_SOFTSTART == ON
    currentPower = 0;
  #else
    currentPower = ROOF_POWER_PWM_POWER;
  #endif

  // Flag status, no errors
  state = 'o';
  statusRegister = RSR_NO_ERROR;

  delay(ROOF_PRE_MOTION_TIME*1000);
  if (ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
    state = 'i';
    lastError = "Error: Open safety interlock";
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
  openStartTime = (long)millis();

  lastError = "";
  return true;
}

// Start closing the roof, returns true if successful or false otherwise (required)
bool Roof::close() {
  if (state != 'i' || relay.isOn(ROOF_MOTOR_OPEN_RELAY) || relay.isOn(ROOF_MOTOR_CLOSE_RELAY) || relay.isOn(ROOF_MOTOR_STOP_RELAY)) {
    lastError = "Error: Close already in motion";
    return false;
  }

  // Handle case of Garage door opener where we're not sure which way it'll move
  if (!safetyOverride && ROOF_SINGLE_OPEN_CLOSE_RELAY == ON && !sense.isOn(ROOF_LIMIT_OPENED_SENSE) && !sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    lastError = "Error: Motion direction unknown";
    return false;
  }

  // Figure out where the roof is right now best as we can tell...
  // Check for limit switch and reset times
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    nv.write(NV_ROOF_TIME_TO_OPEN, (long)timeAvg);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (long)0);
  }
  if (sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    nv.write(NV_ROOF_TIME_TO_OPEN, (long)0);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (long)timeAvg);
  }
  timeLeftToOpenAtStart = nv.readL(NV_ROOF_TIME_TO_OPEN);
  timeLeftToCloseAtStart = nv.readL(NV_ROOF_TIME_TO_CLOSE);

  // Check for validity of roof position timers before starting (they need to be within +/- 2 seconds)
  if (!safetyOverride && abs((timeLeftToOpenAtStart + timeLeftToCloseAtStart) - timeAvg) > 2000) {
    lastError = "Error: Close location unknown";
    return false;
  }

  // Check to see if the roof is already closed
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE) && !sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    lastError = "Warning: Already closed";
    return false;
  }

  // Just one last sanity check before we start moving the roof
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE) && sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    lastError = "Error: Closed/opened limit sw on";
    return false;
  }

  #if ROOF_POWER_PWM_SOFTSTART == ON
    currentPower = 0;
  #else
    currentPower = ROOF_POWER_PWM_POWER;
  #endif

  // Flag status, no errors
  state = 'c';
  statusRegister = RSR_NO_ERROR;

  delay(ROOF_PRE_MOTION_TIME*1000);
  if (ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
    state = 'i';
    lastError = "Error: Close safety interlock";
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

  lastError = "";
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
void Roof::clearStatus() {
  // Reset the status register
  statusRegister = RSR_NO_ERROR;
  lastError = "";
}

// returns an error description string if an error has occured, otherwise must return "Travel: n%" or "No Error" (required)
String Roof::getStatus() {
  String s = getLastError();
  if (s == "" && isMoving()) {
    s = "Travel: " + String(travel) + "%";
    return s;
  }
  if (s == "") s = "No Error";
  return s;
}

// returns an error description string if an error has occured, "" if no error (required)
String Roof::getLastError() {
  String s = "";
  if (statusRegister & RSR_OPEN_INTERLOCK)      s = "Error: Open safety interlock";
  if (statusRegister & RSR_CLOSE_INTERLOCK)     s = "Error: Close safety interlock";
  if (statusRegister & RSR_OPEN_UNKNOWN_ERROR)  s = "Error: Open unknown error"; else
  if (statusRegister & RSR_OPEN_LIMIT_SW_FAIL)  s = "Error: Open limit sw fail"; else
  if (statusRegister & RSR_OPEN_OVER_TIME)      s = "Error: Open over time"; else
  if (statusRegister & RSR_OPEN_UNDER_TIME)     s = "Error: Open under time"; else
  if (statusRegister & RSR_CLOSE_UNKNOWN_ERROR) s = "Error: Close unknown error"; else
  if (statusRegister & RSR_CLOSE_LIMIT_SW_FAIL) s = "Error: Close limit sw fail"; else
  if (statusRegister & RSR_CLOSE_OVER_TIME)     s = "Error: Close over time"; else
  if (statusRegister & RSR_CLOSE_UNDER_TIME)    s = "Error: Close under time";
  if (s == "") {
    if (state == 'i') {
      if (lastError == "") {
        // one final check for any wierd relay stuff going on
        if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE) && sense.isOn(ROOF_LIMIT_OPENED_SENSE)) s = "Error: Limit switch malfunction";
      } else s = lastError;
    }
  }
  return s;
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
  return ( state == 'o');
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
  // Open the roof, keeping track of time limit and sensor status
  if (isOpening()) continueOpening();

  // Close the roof, keeping track of time limit and sensor status
  if (isClosing()) continueClosing();
}

// called repeatedly to open the roof
void Roof::continueOpening() {
  cli();
  long msOfTravel = (long)millis() - openStartTime;
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
  long timeLeftToCloseNow=timeAvg - timeLeftToOpenNow;

  // keep track of where we are (to the nearest five seconds)
  long secondsOfTravel = round(msOfTravel/5000)*5000;
  if (lastSecondsOfTravel != secondsOfTravel) {
    lastSecondsOfTravel = secondsOfTravel;
    nv.write(NV_ROOF_TIME_TO_OPEN, (long)timeLeftToOpenNow);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (long)timeLeftToCloseNow);
  }

  // Or a stuck limit switch
  if (!safetyOverride && (timeAvg - timeLeftToOpenNow) > ROOF_TIME_LIMIT_SENSE_FAIL*1000 && sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    // Set the error in the status register, the user can resume the opening operation by checking for any malfunction then using the safety override if required
    statusRegister |= RSR_OPEN_LIMIT_SW_FAIL;
    // Go idle (assume the roof is still moving where we can't cut the power)
    if (!(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)) state = 'i';
  }

  // Or interlock was triggered
  if (ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
    // Set the error in the status register, the user can resume the opening operation by checking for any malfunction then using the safety override if required
    statusRegister |= RSR_OPEN_INTERLOCK;
    // Go idle (assume the roof is still moving where we can't cut the power)
    if (!(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)) state = 'i';
  }

  // Or the whole process taking too long
  if (!safetyOverride && (timeLeftToOpenAtStart - msOfTravel) < -timeErrorLimit) {
    // Set the error in the status register, the user can resume the opening operation by checking for any malfunction then using the safety override if required
    statusRegister |= RSR_OPEN_OVER_TIME;
    // Go idle (assume the roof has stopped where we can't cut the power)
    state = 'i';
  }

  // Calculate a percentage of roof travel
  travel = ((float)(timeAvg - (timeLeftToOpenAtStart - msOfTravel))/(float)timeAvg)*100;

  // Detect that the roof has finished opening
  if (sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    // wait for a bit before powering off the roof drive (for automatic opener that stops itself)
    if (ROOF_MOTOR_RELAY_MOMENTARY == ON) delay(ROOF_POST_MOTION_TIME*1000);
    // reset position timers
    nv.write(NV_ROOF_TIME_TO_OPEN, (long)0);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (long)timeAvg);
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
  long msOfTravel = (long)millis() - closeStartTime;
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
    nv.write(NV_ROOF_TIME_TO_OPEN, (long)timeLeftToOpenNow);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (long)timeLeftToCloseNow);
  }

  // On a stuck limit switch
  if (!safetyOverride && (timeAvg-timeLeftToCloseNow)>ROOF_TIME_LIMIT_SENSE_FAIL*1000 && sense.isOn(ROOF_LIMIT_OPENED_SENSE)) {
    // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
    statusRegister |= RSR_CLOSE_LIMIT_SW_FAIL;
    // Go idle (assume the roof is still moving where we can't cut the power)
    if (!(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)) state = 'i';
  }

  // Or interlock was triggered
  if (ROOF_INTERLOCK_SENSE != OFF && !sense.isOn(ROOF_INTERLOCK_SENSE)) {
    // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
    statusRegister |= RSR_CLOSE_INTERLOCK;
    // Go idle (assume the roof is still moving where we can't cut the power)
    if (!(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)) state = 'i';
  }

  // Or the whole process is taking too long
  if (!safetyOverride && (timeLeftToCloseAtStart-msOfTravel) < -timeErrorLimit) {
    // Set the error in the status register, the user can resume the closing operation by checking for any malfunction then using the safety override if required
    statusRegister |= RSR_CLOSE_OVER_TIME;
    // Go idle (assume the roof has stopped where we can't cut the power)
    state = 'i';
  }

  // Calculate a percentage of roof travel
  travel = ((float)(timeAvg - (timeLeftToCloseAtStart - msOfTravel))/(float)timeAvg)*100;

  // Detect that the roof has finished closing
  if (sense.isOn(ROOF_LIMIT_CLOSED_SENSE)) {
    // wait for a bit before powering off the roof drive (for automatic opener that stops itself)
    if (ROOF_MOTOR_RELAY_MOMENTARY == ON) delay(ROOF_POST_MOTION_TIME*1000);
    // reset position timers
    nv.write(NV_ROOF_TIME_TO_OPEN, (long)timeAvg);
    nv.write(NV_ROOF_TIME_TO_CLOSE, (long)0);
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
