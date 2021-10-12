// Dome control

#include "Dome.h"

#if DOME_DRIVER_MODEL != OFF

#ifdef DOME_SERVO
  const ServoDriverPins ServoPinsAxis3 = {DOME_SERVO_PH1_PIN, DOME_SERVO_PH1_STATE, DOME_SERVO_PH2_PIN, DOME_SERVO_PH2_STATE, DOME_ENABLE_PIN, DOME_ENABLE_STATE, DOME_FAULT_PIN};
  const ServoDriverSettings ServoSettingsAxis3 = {DOME_DRIVER_MODEL, DOME_SERVO_P, DOME_SERVO_I, DOME_SERVO_D, DOME_DRIVER_STATUS};
  ServoDriver servoDriver1(3, &ServoPinsAxis3, &ServoSettingsAxis3);

  ServoControl control3;
  #if DOME_SERVO_ENCODER == ENC_AB
    Encoder encAxis3(DOME_SERVO_ENC1_PIN, DOME_SERVO_ENC2_PIN);
  #else
    Encoder encAxis3(DOME_SERVO_ENC1_PIN, DOME_SERVO_ENC2_PIN, DOME_SERVO_ENCODER, DOME_SERVO_ENCODER_TRIGGER, &control1.directionHint);
  #endif
  PID pidAxis3(&control1.in, &control1.out, &control1.set, DOME_SERVO_P, DOME_SERVO_I, DOME_SERVO_D, DIRECT);

  ServoMotor motor3(3, &encAxis3, &pidAxis3, &servoDriver3, &control3);
  IRAM_ATTR void moveAxis3() { motor3.move(); }
#endif
#ifdef DOME_DRIVER_SD
  const DriverModePins DriverPinsAxis3 = {DOME_M0_PIN, DOME_M1_PIN, DOME_M2_PIN, DOME_M3_PIN, DOME_DECAY_PIN, DOME_FAULT_PIN};
  const DriverSettings DriverSettingsAxis3 = {DOME_DRIVER_MODEL, DOME_DRIVER_MICROSTEPS, DOME_DRIVER_MICROSTEPS_GOTO, OFF, OFF, OFF, DOME_DRIVER_DECAY, DOME_DRIVER_DECAY_GOTO, DOME_DRIVER_STATUS};
  StepDirDriver stepDirDriver3(3, &DriverPinsAxis3, &DriverSettingsAxis3);

  const StepDirPins StepDirPinsAxis3 = {DOME_STEP_PIN, DOME_STEP_STATE, DOME_DIR_PIN, DOME_ENABLE_PIN, DOME_ENABLE_STATE};
  StepDirMotor motor3(3, &StepDirPinsAxis3, &stepDirDriver3);
  IRAM_ATTR void moveAxis3() { motor3.move(DOME_STEP_PIN, DOME_DIR_PIN); }
#endif
const AxisPins PinsAxis3 = {DOME_SENSE_LIMIT_MIN_PIN, DOME_SENSE_HOME_PIN, DOME_SENSE_LIMIT_MAX_PIN, {DOME_SENSE_HOME, DOME_SENSE_HOME_INIT, DOME_SENSE_LIMIT_MIN, DOME_SENSE_LIMIT_MAX, DOME_SENSE_LIMIT_INIT}};
const AxisSettings SettingsAxis3 = {DOME_STEPS_PER_DEGREE, DOME_REVERSE, DOME_PARAMETER1, DOME_PARAMETER2, {DOME_LIMIT_MIN, DOME_LIMIT_MAX}, DOME_BACKLASH_RATE};
Axis axis3(3, &PinsAxis3, &SettingsAxis3);
void pollAxis3() { axis3.poll(); }

#endif
