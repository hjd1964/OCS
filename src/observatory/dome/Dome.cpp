// Dome control
#include "Dome.h"

#ifdef DOME_PRESENT

#include "../../lib/tasks/OnTask.h"
#include "../../lib/nv/Nv.h"

#include "../../observatory/Observatory.h"
#include "../roof/Roof.h"

void domeWrapper() { dome.monitor(); }

// initialize dome
void Dome::init() {
  // wait a moment for any background processing that may be needed
  delay(1000);

  // confirm the data structure size
  if (DomeSettingsSize < sizeof(DomeSettings)) { nv.initError = true; DL("ERR: Dome::init(); DomeSettingsSize error"); }

  // get settings stored in NV ready
  if (!nv.hasValidKey()) {
    VLF("MSG: Dome, writing defaults to NV");
  }

  nv.readBytes(NV_DOME_SETTINGS_BASE, &settings, sizeof(DomeSettings));

  if (settings.backlash.azimuth  < 0.0F)  { settings.backlash.azimuth = 0.0F; initError.value = true; DLF("ERR, Dome.init(): bad NV backlash.azimuth < 0 deg (set to 0)"); }
  if (settings.backlash.azimuth  > 10.0F) { settings.backlash.azimuth = 0.0F; initError.value = true; DLF("ERR, Dome.init(): bad NV backlash.azimuth > 10 deg (set to 0)"); }
  if (settings.backlash.altitude < 0.0F)  { settings.backlash.altitude = 0.0F; initError.value = true; DLF("ERR, Dome.init(): bad NV backlash.altitude < 0 deg (set to 0)"); }
  if (settings.backlash.altitude > 10.0F) { settings.backlash.altitude = 0.0F; initError.value = true; DLF("ERR, Dome.init(): bad NV backlash.altitude > 10 deg steps (set to 0)"); }
  if (settings.park.azimuth  < AXIS1_LIMIT_MIN) { settings.park.azimuth = 0.0F; initError.value = true; DLF("ERR, Dome.init(): bad NV park pos < AXIS1_LIMIT_MIN (set to 0.0)"); }
  if (settings.park.azimuth  > AXIS1_LIMIT_MAX) { settings.park.azimuth = 0.0F; initError.value = true; DLF("ERR, Dome.init(): bad NV park pos > AXIS1_LIMIT_MAX (set to 0.0)"); }
  if (settings.park.altitude < AXIS2_LIMIT_MIN) { settings.park.altitude = 0.0F; initError.value = true; DLF("ERR, Dome.init(): bad NV park pos < AXIS2_LIMIT_MIN (set to 0.0)"); }
  if (settings.park.altitude > AXIS2_LIMIT_MAX) { settings.park.altitude = 0.0F; initError.value = true; DLF("ERR, Dome.init(): bad NV park pos > AXIS2_LIMIT_MAX (set to 0.0)"); }

  VLF("MSG: Dome, init (Axis1)");
  if (!axis1.init(&motor1)) { DLF("ERR: Axis1, no motion controller exiting!"); return; }
  axis1.resetPositionSteps(round(AXIS1_HOME_DEFAULT*AXIS1_STEPS_PER_DEGREE));
  axis1.setBacklash(settings.backlash.azimuth);
  axis1.setFrequencyMax(AXIS1_SLEW_RATE_DESIRED);
  axis1.setFrequencyMin(0.01F);
  axis1.setFrequencySlew(AXIS1_SLEW_RATE_DESIRED);
  axis1.setSlewAccelerationTime(AXIS1_ACCELERATION_TIME);
  axis1.setSlewAccelerationTimeAbort(AXIS1_RAPID_STOP_TIME);
  if (AXIS1_POWER_DOWN == ON) axis1.setPowerDownTime(DEFAULT_POWER_DOWN_TIME);

  if (AXIS1_WRAP == ON) {
    axis1.coordinateWrap(360.0);
    axis1.settings.limits.min = -360.0;
    axis1.settings.limits.max = 360.0;
  }

  #if AXIS2_DRIVER_MODEL != OFF
    VLF("MSG: Dome, init (Axis2)");
    if (!axis2.init(&motor2)) { DLF("ERR: Axis2, no motion controller exiting!"); return; }
    axis2.resetPositionSteps(round(AXIS2_HOME_DEFAULT*AXIS2_STEPS_PER_DEGREE));
    axis2.setBacklash(settings.backlash.altitude);
    axis2.setFrequencyMax(AXIS2_SLEW_RATE_DESIRED);
    axis2.setFrequencyMin(0.01F);
    axis2.setFrequencySlew(AXIS2_SLEW_RATE_DESIRED);
    axis2.setSlewAccelerationTime(AXIS2_ACCELERATION_TIME);
    axis2.setSlewAccelerationTimeAbort(AXIS2_RAPID_STOP_TIME);
    if (AXIS2_POWER_DOWN == ON) axis2.setPowerDownTime(DEFAULT_POWER_DOWN_TIME);
  #endif

  // handle parked state
  if (settings.park.state == PS_PARKED) {
    axis1.setInstrumentCoordinate(settings.park.azimuth);
    #if AXIS2_DRIVER_MODEL != OFF
      axis2.setInstrumentCoordinate(settings.park.altitude);
    #endif
  }

  // start monitor task
  VF("MSG: Dome, start monitor task (rate 1s priority 6)... ");
  if (tasks.add(1000, 0, true, 6, domeWrapper, "DomeMon")) {
    VLF("success");
    ready = true;
  } else { VLF("FAILED!"); }
}

// reset dome at the home position
void Dome::reset(bool useHomeSensorOffset) {
  VLF("MSG: Dome, reset at home");

  // after a homing run add in the residual between the recorded sensor trip point and the resting position
  long azmSteps = lround(AXIS1_HOME_DEFAULT*AXIS1_STEPS_PER_DEGREE);
  #if AXIS1_SENSE_HOME != OFF
    if (useHomeSensorOffset) azmSteps += axis1.getInstrumentCoordinateSteps() - axis1.getHomeFoundSteps();
  #endif
  axis1.resetPositionSteps(azmSteps);
  axis1.enable(false);
  #if AXIS2_DRIVER_MODEL != OFF
    long altSteps = lround(AXIS2_HOME_DEFAULT*AXIS2_STEPS_PER_DEGREE);
    #if AXIS2_SENSE_HOME != OFF
      if (useHomeSensorOffset) altSteps += axis2.getInstrumentCoordinateSteps() - axis2.getHomeFoundSteps();
    #endif
    axis2.resetPositionSteps(altSteps);
    axis2.enable(false);
  #endif
  UNUSED(useHomeSensorOffset);
  settings.park.state = PS_UNPARKED;
  nv.updateBytes(NV_DOME_SETTINGS_BASE, &settings, sizeof(DomeSettings));
}

// with DOME_SHUTTER_LOCK ON, dome motion is only allowed while the roof/shutter is fully open
// (this only checks the shutter, it never moves it)
bool Dome::shutterLocked() {
  #if defined(ROOF_PRESENT) && DOME_SHUTTER_LOCK == ON
    return !roof.isOpen();
  #else
    return false;
  #endif
}

// dome goto azimuth
CommandError Dome::gotoAzimuthTarget() {
  if (shutterLocked()) return CE_SLEW_ERR_IN_STANDBY;
  if (settings.park.state >= PS_PARKED) return CE_SLEW_ERR_IN_PARK;

  VF("MSG: Dome, goto azimuth target coordinate set ("); V(targetAzm); VL("°)");
  VLF("MSG: Dome, starting azimuth goto");

  if (!axis1.isEnabled()) axis1.enable(true);
  axis1.setTargetCoordinate(targetAzm);

  // isHoming() covers the settle gaps between homing moves, where the axis is idle but busy
  if (axis1.isSlewing() || axis1.isHoming()) return CE_NONE;

  CommandError e = axis1.autoGoto(AXIS1_SLEW_RATE_DESIRED);
  return e;
}

// dome sync azimuth
CommandError Dome::syncAzimuthTarget() {
  if (shutterLocked()) return CE_SLEW_ERR_IN_STANDBY;
  if (settings.park.state >= PS_PARKED) return CE_SLEW_ERR_IN_PARK;

  VF("MSG: Dome, sync azimuth target coordinate set ("); V(targetAzm); VL("°)");
  reset();
  if (!axis1.isEnabled()) axis1.enable(true);
  axis1.setInstrumentCoordinate(targetAzm);

  return CE_NONE;
}

// dome goto altitude
CommandError Dome::gotoAltitudeTarget() {
  #if AXIS2_DRIVER_MODEL != OFF
    if (shutterLocked()) return CE_SLEW_ERR_IN_STANDBY;
    if (settings.park.state >= PS_PARKED) return CE_SLEW_ERR_IN_PARK;

    VF("MSG: Dome, goto altitude target coordinate set ("); V(targetAlt); VL("°)");
    VLF("MSG: Dome, starting altitude goto");

    if (!axis2.isEnabled()) axis2.enable(true);
    axis2.setTargetCoordinate(targetAlt);

    if (axis2.isSlewing() || axis2.isHoming()) return CE_NONE;

    CommandError e = axis2.autoGoto(AXIS2_SLEW_RATE_DESIRED);
    return e;
  #else
    return CE_GOTO_FAIL;
  #endif
}

// move to the home position
CommandError Dome::findHome() {
  if (shutterLocked()) return CE_SLEW_ERR_IN_STANDBY;
  if (settings.park.state >= PS_PARKED) return CE_PARKED;

  targetAzm = AXIS1_HOME_DEFAULT;
  targetAlt = AXIS2_HOME_DEFAULT;

  CommandError e = CE_NONE;

  // homing runs with backlash off as park()/unpark() already do, the approach always comes from the same side anyway
  #if AXIS1_SENSE_HOME != OFF
    axis1.setBacklash(0.0F);
    axis1.setFrequencySlew(AXIS1_SLEW_RATE_DESIRED);
    e = axis1.autoSlewHome();
    // set the restore flag only once the slew is actually running, since monitor() restores on !isSlewing()
    if (e == CE_NONE) { homing = true; backlashDisabled = true; }
  #else
    e = gotoAzimuthTarget();
  #endif

  #if AXIS2_DRIVER_MODEL != OFF
    if (e == CE_NONE) {
      #if AXIS2_SENSE_HOME != OFF
        axis2.setBacklash(0.0F);
        axis2.setFrequencySlew(AXIS2_SLEW_RATE_DESIRED);
        e = axis2.autoSlewHome();
        if (e == CE_NONE) {
          homing = true;
          backlashDisabled = true;
        } else {
          axis1.autoSlewAbort();
          homing = false;
        }
      #else
        e = gotoAltitudeTarget();
      #endif
    }
  #endif

  // nothing is slewing on a failed start, so monitor() will never restore backlash; do it here
  if (e != CE_NONE && !backlashDisabled) {
    axis1.setBacklash(settings.backlash.azimuth);
    #if AXIS2_DRIVER_MODEL != OFF
      axis2.setBacklash(settings.backlash.altitude);
    #endif
  }

  return e;
}

// measure a full rotation, to calibrate AXIS1_STEPS_PER_DEGREE
CommandError Dome::calibrateRotation() {
  #if AXIS1_SENSE_HOME == OFF
    return CE_SLEW_ERR_UNSPECIFIED;
  #else
    #if defined(ROOF_PRESENT) && DOME_SHUTTER_LOCK == ON
      if (!roof.open()) return CE_SLEW_ERR_IN_STANDBY;
    #endif
    if (settings.park.state >= PS_PARKED) return CE_PARKED;
    if (isSlewing() || calibrating) return CE_SLEW_IN_SLEW;
    #if AXIS1_WRAP != ON
      // without wrap the software limits stop the axis before it can complete a revolution
      VLF("MSG: Dome, rotation calibration needs AXIS1_WRAP ON");
      return CE_SLEW_ERR_OUTSIDE_LIMITS;
    #endif

    VF("MSG: Dome, measuring rotation over "); V(DOME_CALIBRATE_REVOLUTIONS); VLF(" revolution(s)");

    axis1.enable(true);
    // no direction reversal happens during the run so lash can't affect the interval between passes, zero it anyway
    axis1.setBacklash(0.0F);
    axis1.setFrequencySlew(AXIS1_SLEW_RATE_DESIRED);

    // reject a trip closer than 10 degrees to the last, well past the switch width but far short of a revolution
    axis1.homeCaptureStart(lround(10.0*axis1.getStepsPerMeasure()));

    // rotate the way homing seeks, so calibration meets the switch on the same edge homing does
    CommandError e = axis1.autoSlew((HOME_SEEK_REVERSE) == ON ? DIR_REVERSE : DIR_FORWARD,
                                    AXIS1_SLEW_RATE_DESIRED);
    if (e != CE_NONE) {
      axis1.homeCaptureStop();
      axis1.setBacklash(settings.backlash.azimuth);
      VF("MSG: Dome, rotation calibration could not start, error "); VL(e);
      return e;
    }

    // allow three times the expected run time before giving up, so a switch that never trips ends the run
    calibrateTimeout = millis() +
      (unsigned long)((DOME_CALIBRATE_REVOLUTIONS + 1)*3.0*360.0/(AXIS1_SLEW_RATE_DESIRED)*1000.0);
    calibrating = true;
    backlashDisabled = true;
    return CE_NONE;
  #endif
}

#if AXIS1_SENSE_HOME != OFF
  // work out and report the result of a rotation measurement
  void Dome::calibrateReport() {
    uint8_t passes = axis1.getHomeCaptureCount();
    axis1.homeCaptureStop();
    calibrating = false;

    if (passes < 2) {
      DF("WRN: Dome, rotation calibration saw "); D(passes);
      DLF(" home switch pass(es), need at least 2 - nothing measured");
      return;
    }

    VLF("MSG: Dome, rotation calibration complete");
    long shortest = 0, longest = 0;
    for (uint8_t i = 1; i < passes; i++) {
      long interval = labs(axis1.getHomeCaptureSteps(i) - axis1.getHomeCaptureSteps(i - 1));
      if (i == 1 || interval < shortest) shortest = interval;
      if (i == 1 || interval > longest) longest = interval;
      VF("MSG: Dome,   pass "); V(i); VF(" -> "); V(i + 1); VF(": "); V(interval); VLF(" steps");
    }

    // average over the whole span, the intermediate passes cancel so only the first and last edges contribute error
    double mean = labs(axis1.getHomeCaptureSteps(passes - 1) - axis1.getHomeCaptureSteps(0))/
                  (double)(passes - 1);

    // V() prints a double to two decimals, not enough to carry a steps/degree figure
    char s[24];
    VF("MSG: Dome,   mean "); sprintF(s, "%0.1f", mean); V(s);
    VF(" steps/rev over "); V(passes - 1); VLF(" revolution(s)");
    VF("MSG: Dome,   spread "); V(longest - shortest); VF(" steps (");
    sprintF(s, "%0.3f", (longest - shortest)*100.0/mean); V(s); VLF("%)");
    VF("MSG: Dome,   set AXIS1_STEPS_PER_DEGREE "); sprintF(s, "%0.4f", mean/360.0); V(s);
    VF(" (currently "); sprintF(s, "%0.4f", axis1.getStepsPerMeasure()); V(s); VLF(")");
  }
#endif

// stop slew
void Dome::stop() {
  if (isSlewing()) {
    if (settings.park.state == PS_PARKING) {
      settings.park.state = PS_UNPARKED;
      nv.updateBytes(NV_DOME_SETTINGS_BASE, &settings, sizeof(DomeSettings));
    }
    axis1.autoSlewAbort();
    #if AXIS2_DRIVER_MODEL != OFF
      axis2.autoSlewAbort();
    #endif
    homing = false;

    // a calibration stopped part way still yields a usable figure if it recorded two passes
    #if AXIS1_SENSE_HOME != OFF
      if (calibrating) { VLF("MSG: Dome, rotation calibration stopped early"); calibrateReport(); }
    #endif
  }
}

// dome park
CommandError Dome::park() {
  if (shutterLocked()) return CE_SLEW_ERR_IN_STANDBY;
  if (settings.park.state == PS_PARKED)      return CE_NONE;
  if (settings.park.state == PS_PARKING)     return CE_PARK_FAILED;
  if (settings.park.state == PS_UNPARKING)   return CE_PARK_FAILED;
  if (settings.park.state == PS_PARK_FAILED) return CE_PARK_FAILED;

  VLF("MSG: Dome, parking");
  axis1.setBacklash(0.0F);
  axis1.setTargetCoordinatePark(settings.park.azimuth);
  CommandError e = axis1.autoGoto(AXIS1_SLEW_RATE_DESIRED);

  #if AXIS2_DRIVER_MODEL != OFF
    if (e == CE_NONE) {
      axis2.setBacklash(0.0F);
      axis2.setTargetCoordinatePark(settings.park.altitude);
      e = axis2.autoGoto(AXIS2_SLEW_RATE_DESIRED);
    }
  #endif

  if (e == CE_NONE) {
    settings.park.state = PS_PARKING;
    nv.updateBytes(NV_DOME_SETTINGS_BASE, &settings, sizeof(DomeSettings));
  }

  return e;
}

// dome unpark
CommandError Dome::unpark() {
  if (shutterLocked()) return CE_SLEW_ERR_IN_STANDBY;
  if (settings.park.state == PS_PARKING)     return CE_PARK_FAILED;
  if (settings.park.state == PS_UNPARKING)   return CE_PARK_FAILED;
  if (settings.park.state == PS_PARK_FAILED) return CE_PARK_FAILED;

  VF("MSG: Dome, unpark position (Azm="); V(settings.park.azimuth); V("°, Alt="); V(settings.park.altitude); VL(")");

  axis1.enable(true);
  axis1.setBacklash(0.0F);
  axis1.setInstrumentCoordinatePark(settings.park.azimuth);
  axis1.setBacklash(settings.backlash.azimuth);
  axis1.setTargetCoordinate(settings.park.azimuth);
  CommandError e = axis1.autoGoto(AXIS1_SLEW_RATE_DESIRED);

  #if AXIS2_DRIVER_MODEL != OFF
    if (e == CE_NONE) {
      axis2.enable(true);
      axis2.setBacklash(0.0F);
      axis2.setInstrumentCoordinatePark(settings.park.altitude);
      axis2.setBacklash(settings.backlash.altitude);
      axis2.setTargetCoordinate(settings.park.altitude);
      e = axis2.autoGoto(AXIS2_SLEW_RATE_DESIRED);
    }
  #endif

  // wait for unpark to finish
  unsigned long timeout = millis() + 500;
  while (
    (axis1.isSlewing()
    #if AXIS2_DRIVER_MODEL != OFF
      || axis2.isSlewing()
    #endif
    ) && (long)(millis() - timeout) < 0
  ) { };

  if (e == CE_NONE) {
    settings.park.state = PS_UNPARKED;
    nv.updateBytes(NV_DOME_SETTINGS_BASE, &settings, sizeof(DomeSettings));
  }

  return e;
}

// dome set park
CommandError Dome::setpark() {
  if (shutterLocked()) return CE_SLEW_ERR_IN_STANDBY;
  if (settings.park.state == PS_PARKED)      return CE_NONE;
  if (settings.park.state == PS_PARKING)     return CE_PARK_FAILED;
  if (settings.park.state == PS_UNPARKING)   return CE_PARK_FAILED;
  if (settings.park.state == PS_PARK_FAILED) return CE_PARK_FAILED;

  VLF("MSG: Dome, setting park position");
  settings.park.azimuth = axis1.getInstrumentCoordinate();
  #if AXIS2_DRIVER_MODEL != OFF
    settings.park.altitude = axis2.getInstrumentCoordinate();
  #else
    settings.park.altitude = NAN;
  #endif

  nv.updateBytes(NV_DOME_SETTINGS_BASE, &settings, sizeof(DomeSettings));
  return CE_NONE;
}

// check if dome is slewing
bool Dome::isSlewing() {
  // isHoming() covers the pauses between homing moves, where the axis is idle but still busy
  return
    (axis1.isSlewing() || axis1.isHoming()
    #if AXIS2_DRIVER_MODEL != OFF
      || axis2.isSlewing() || axis2.isHoming()
    #endif
    );
}

// check if dome is parked
bool Dome::isParked() {
  return settings.park.state == PS_PARKED;
}

// return dome status message
const char* Dome::statusMessage() {
  if (settings.park.state == PS_PARKED) strcpy(statusMsg, L_PARKED); else
  if (settings.park.state == PS_PARKING) strcpy(statusMsg, L_PARKING); else
  if (isSlewing()) strcpy(statusMsg, L_SLEWING); else strcpy(statusMsg, L_STOPPED);
  return statusMsg;
}

// poll dome to monitor motion
void Dome::monitor() {
  #if AXIS1_SENSE_HOME != OFF
    // a calibration run just rotates until enough passes are recorded, the passes themselves are captured in Axis::poll()
    if (calibrating) {
      if (axis1.getHomeCaptureCount() > DOME_CALIBRATE_REVOLUTIONS) {
        axis1.autoSlewStop();
        calibrateReport();
      } else
      if ((long)(millis() - calibrateTimeout) > 0) {
        DLF("WRN: Dome, rotation calibration timed out");
        axis1.autoSlewStop();
        calibrateReport();
      } else
      if (!axis1.isSlewing()) {
        DLF("WRN: Dome, rotation calibration ended early, the axis stopped");
        calibrateReport();
      }
      return;
    }
  #endif

  // isSlewing() also covers a homing run that is between moves, so nothing below fires early
  if (!isSlewing()) {
      // restore backlash after a homing run, keyed off its own flag so it fires on every way out of homing
      if (backlashDisabled) {
        backlashDisabled = false;
        axis1.setBacklash(settings.backlash.azimuth);
        #if AXIS2_DRIVER_MODEL != OFF
          axis2.setBacklash(settings.backlash.altitude);
        #endif
      }

      if (settings.park.state == PS_PARKING) {
        settings.park.state = PS_PARKED;
        nv.updateBytes(NV_DOME_SETTINGS_BASE, &settings, sizeof(DomeSettings));
        axis1.enable(false);
        #if AXIS2_DRIVER_MODEL != OFF
          axis2.enable(false);
        #endif
      } else

      if (settings.park.state == PS_UNPARKED) {
        if (homing) {
          homing = false;

          // a timeout, motion error, or the motor disabling itself also end the slew, so check home was actually found
          bool found = true;
          #if AXIS1_SENSE_HOME != OFF
            found = found && axis1.isHomeFound();
          #endif
          #if AXIS2_DRIVER_MODEL != OFF && AXIS2_SENSE_HOME != OFF
            found = found && axis2.isHomeFound();
          #endif

          if (found) reset(true); else {
            DLF("WRN: Dome, homing stopped without reaching the home sensor, position NOT set");
          }
        }
      }
  }
}

Dome dome;

#endif
