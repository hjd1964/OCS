// -----------------------------------------------------------------------------------------------------------------
// Relay control
#include "Relay.h"
#include "../sense/Sense.h"

#include "../../observatory/roof/RollOff.h"

void Relay::init() {
  for (int r = 0; r < RELAYS_MAX; r++) {
    pinMode(settings[r].pin, OUTPUT);
    off(r);
  }
  /*
  // for dimming the led's etc, 1 millisecond period
  Timer1.initialize(1000);
  Timer1.attachInterrupt(RelayPwmISR);
  */
}

void Relay::on(int r, bool updateState) {
  if (r >= 0 && r < RELAYS_MAX) {
    if (updateState) settings[r].state = 1;
    digitalWrite(settings[r].pin, settings[r].onState);
  }
}

// delays up to 1 hour
void Relay::onDelayedOff(int r, float seconds) {
  if (r >= 0 && r < RELAYS_MAX && seconds >= 0.1 && seconds <= 3600.0) {
    settings[r].state = 19 + round(seconds*10.0);
    digitalWrite(settings[r].pin, settings[r].onState);
  }
}

void Relay::pwm(int r, int percentPower) {
  percentPower /= 10;
  if (r >= 0 && r < RELAYS_MAX && percentPower >= 1 && percentPower <= 9) {
    settings[r].state = 10 + percentPower;
  }
}

void Relay::off(int r, bool updateState) {
  if (r >= 0 && r < RELAYS_MAX) {
    if (updateState) settings[r].state = 0;
    uint8_t offState = LOW;
    if (settings[r].onState == LOW) offState = HIGH;
    digitalWrite(settings[r].pin, offState);
  }
}

bool Relay::isOn(int r) {
  if (r >= 0 && r < RELAYS_MAX) return !(settings[r].state == 0); else return false;
}

bool Relay::isOnDelayedOff(int r) {
  timedOff();
  if (r >= 0 && r < RELAYS_MAX) {
    return (settings[r].state > 19);
  } else return false;
}

// relayState: 0 = OFF, 1 = ON, 2..9 unused, 11..19 pwm 10% to 90%, 20..65535 timed off period in 1/10 seconds
// do timed relay off control
void Relay::timedOff() {
  // run at 1/10 second intervals
  static unsigned long last = 0;
  if ((long)(millis() - last) > 100) {
    last = millis();

    // Timed relay off
    for (int r = 0; r < RELAYS_MAX; r++) {
      if (settings[r].state >= 20) {
        settings[r].state -= 1;
        if (settings[r].state < 20) off(r);
      }
    }
  }
}

// do PWM on a solid state relay (ISR,) this runs at 1kHz
void Relay::poll() {
  fastPwmCycle++;
  if (fastPwmCycle > 9) fastPwmCycle = 0;
  for (int r = 0; r < RELAYS_MAX; r++) {
    if (settings[r].state >= 10) {
      if (fastPwmCycle == 0) {
        on(r, false);
      } else {
        if (settings[r].state/10 == fastPwmCycle) off(r, false);
      }
    }
  }

  #if ROR == ON
    #if ROR_POWER_PWM_FREQUENCY != OFF && ROR_POWER_PWM_POWER != OFF
      if (roof.isMoving()) {
        count++;
        if (count >= 1000/(ROR_POWER_PWM_FREQUENCY*10)) {
          count = 0;
          slowPwmCycle++;
          if (slowPwmCycle > 9) slowPwmCycle = 0;
          if (slowPwmCycle == 0) on(ROR_POWER_RELAY);
          if (!roof.isMaxPower() && (roof.powerLevel()/10 == slowPwmCycle)) off(ROR_POWER_RELAY);
        }
      } else {
        count = 0;
        slowPwmCycle = 0;
        if (isOn(ROR_POWER_RELAY)) off(ROR_POWER_RELAY);
      }
    #else
      if (roof.isMoving()) {
        on(ROR_POWER_RELAY);
      } else {
        if (isOn((ROR_POWER_RELAY)) off(ROR_POWER_RELAY);
      }
    #endif

    // ROR safety shutoff (via direction relays) here in an ISR where it can't be blocked by anything just incase the main-loop blocks
    if (ROR_MOTOR_RELAY_MOMENTARY == OFF) {
      if (isOn(ROR_MOTOR_OPEN_RELAY) && sense.isOn(ROR_LIMIT_OPENED_SENSE)) roof.stop();
      if (isOn(ROR_MOTOR_CLOSE_RELAY) && sense.isOn(ROR_LIMIT_CLOSED_SENSE)) roof.stop();
    }
  #endif
}

Relay relay;