// -----------------------------------------------------------------------------------
// axis servo DC motor driver

#include "Dc.h"

#ifdef SERVO_DC_PRESENT

ServoDc::ServoDc(uint8_t axisNumber, const ServoDcPins *Pins, const ServoDcSettings *Settings) {
  this->axisNumber = axisNumber;

  this->Pins = Pins;
  enablePin = Pins->enable;
  enabledState = Pins->enabledState;
  faultPin = Pins->fault;

  this->Settings = Settings;
  model = Settings->model;
  statusMode = Settings->status;
  velocityMax = (Settings->velocityMax/100.0F)*ANALOG_WRITE_RANGE;
  acceleration = (Settings->acceleration/100.0F)*velocityMax;
  accelerationFs = acceleration/FRACTIONAL_SEC;
}

void ServoDc::init() {
  ServoDriver::init();

  // show velocity control settings
  VF("MSG: ServoDriver"); V(axisNumber);
  VF(", Vmax = "); V(Settings->velocityMax); VF("% power, Acceleration = "); V(Settings->acceleration); VLF("%/s/s");

  #if DEBUG == VERBOSE
    VF("MSG: ServoDriver"); V(axisNumber);
    if (model == SERVO_EE) {
      V(", pins pwm1="); if (Pins->in1 == OFF) V("OFF"); else V(Pins->in1);
      V(", pwm2="); if (Pins->in2 == OFF) VF("OFF"); else V(Pins->in2);
    } else
    if (model == SERVO_PE) {
      V(", pins dir="); if (Pins->in1 == OFF) V("OFF"); else V(Pins->in1);
      V(", pwm="); if (Pins->in2 == OFF) VF("OFF"); else V(Pins->in2);
    }
  #endif

  // init default driver control pins
  pinModeEx(Pins->in1, OUTPUT);
  digitalWriteF(Pins->in1, Pins->inState1); // either in1 or direction, state should default to inactive
  pinModeEx(Pins->in2, OUTPUT);
  digitalWriteF(Pins->in2, Pins->inState2); // either in2 or phase (PWM,) state should default to inactive

  // set fastest PWM speed for Teensy processors
  #ifdef ANALOG_WRITE_PWM_FREQUENCY
    VF("MSG: Servo"); V(axisNumber); VF(", setting control pins analog frequency "); VL(ANALOG_WRITE_PWM_FREQUENCY);
    analogWriteFrequency(Pins->in1, ANALOG_WRITE_PWM_FREQUENCY);
    analogWriteFrequency(Pins->in2, ANALOG_WRITE_PWM_FREQUENCY);
  #endif

  // set fault pin mode
  if (statusMode == ON) statusMode = LOW;
  if (statusMode == LOW) pinModeEx(faultPin, INPUT_PULLUP);
  #ifdef PULLDOWN
    if (statusMode == HIGH) pinModeEx(faultPin, INPUT_PULLDOWN);
  #else
    if (statusMode == HIGH) pinModeEx(faultPin, INPUT);
  #endif
}

// set motor velocity by adjusting power (0 to ANALOG_WRITE_RANGE for 0 to 100% power)
float ServoDc::setMotorVelocity(float velocity) {
  if (!enabled) velocity = 0.0F;
  if (velocity > velocityMax) velocity = velocityMax; else
  if (velocity < -velocityMax) velocity = -velocityMax;

  if (velocity > currentVelocity) {
    currentVelocity += accelerationFs;
    if (currentVelocity > velocity) currentVelocity = velocity;
  } else
  if (velocity < currentVelocity) {
    currentVelocity -= accelerationFs;
    if (currentVelocity < velocity) currentVelocity = velocity;
  }
  if (currentVelocity >= 0) motorDirection = DIR_FORWARD; else motorDirection = DIR_REVERSE;

  pwmUpdate(fabs(currentVelocity));
  return currentVelocity;
}

// motor control update
void ServoDc::pwmUpdate(float power) {
  if (model == SERVO_EE) {
    if (motorDirection == DIR_FORWARD) {
      if (Pins->inState1 == HIGH) analogWrite(Pins->in1, round(velocityMax)); else analogWrite(Pins->in1, 0);
      if (Pins->inState2 == HIGH) power = velocityMax - power;
      analogWrite(Pins->in2, round(power));
    } else
    if (motorDirection == DIR_REVERSE) {
      if (Pins->inState1 == HIGH) power = velocityMax - power;
      analogWrite(Pins->in1, round(power));
      if (Pins->inState2 == HIGH) analogWrite(Pins->in2, round(velocityMax)); else analogWrite(Pins->in2, 0);
    } else {
      if (Pins->inState1 == HIGH) analogWrite(Pins->in1, round(velocityMax)); else analogWrite(Pins->in1, 0);
      if (Pins->inState2 == HIGH) analogWrite(Pins->in2, round(velocityMax)); else analogWrite(Pins->in2, 0);
    }
  } else
  if (model == SERVO_PE) {
    if (motorDirection == DIR_FORWARD) {
      digitalWriteF(Pins->in1, Pins->inState1);
      if (Pins->inState2 == HIGH) power = velocityMax - power;
      analogWrite(Pins->in2, round(power));
    } else
    if (motorDirection == DIR_REVERSE) {
      digitalWriteF(Pins->in1, !Pins->inState1);
      if (Pins->inState2 == HIGH) power = velocityMax - power;
      analogWrite(Pins->in2, round(power));
    } else {
      digitalWriteF(Pins->in1, Pins->inState1);
      if (Pins->inState2 == HIGH) analogWrite(Pins->in2, round(velocityMax)); else analogWrite(Pins->in2, 0);
    }
  }
}

// update status info. for driver
void ServoDc::updateStatus() {
  if (statusMode == LOW || statusMode == HIGH) {
    status.fault = digitalReadEx(faultPin) == statusMode;
  }
  ServoDriver::updateStatus();
}

// empty calibrate function
void ServoDc::calibrate() {
  // do nothing
}

#endif