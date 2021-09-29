// -----------------------------------------------------------------------------------------------------------------
// Relay control
#pragma once

#include "../../Common.h"

#define RELAYS_MAX 18

typedef struct RelaySettings {
  int16_t pin;
  int16_t onState;
  int16_t defaultState;
  int16_t state;
} RelaySettings;

class Relay {
  public:
    void init();

    void on(int r, bool updateState);

    inline void on(int r) { on(r, true); }

    void onDelayedOff(int r, float seconds);

    void pwm(int r, int percentPower);

    void off(int r, bool updateState);

    inline void off(int r) { off(r, true); }

    bool isOn(int r);

    inline bool isOn(const char *rs) { return isOn(atoi(rs)); }

    bool isOnDelayedOff(int r);

    void timedOff();

    // do PWM on a solid state relay (ISR,) this runs at 1kHz
    void poll();

  private:
    volatile uint8_t fastPwmCycle = 0;
    volatile uint8_t slowPwmCycle = 0;

    volatile int count = 0;

    volatile RelaySettings settings[RELAYS_MAX] {
      {RELAY1_PIN, RELAY1_ACTIVE_STATE, RELAY1_DEFAULT_STATE, OFF},
      {RELAY2_PIN, RELAY2_ACTIVE_STATE, RELAY2_DEFAULT_STATE, OFF},
      {RELAY3_PIN, RELAY3_ACTIVE_STATE, RELAY3_DEFAULT_STATE, OFF},
      {RELAY4_PIN, RELAY4_ACTIVE_STATE, RELAY4_DEFAULT_STATE, OFF},
      {RELAY5_PIN, RELAY5_ACTIVE_STATE, RELAY5_DEFAULT_STATE, OFF},
      {RELAY6_PIN, RELAY6_ACTIVE_STATE, RELAY6_DEFAULT_STATE, OFF},
      {RELAY7_PIN, RELAY7_ACTIVE_STATE, RELAY7_DEFAULT_STATE, OFF},
      {RELAY8_PIN, RELAY8_ACTIVE_STATE, RELAY8_DEFAULT_STATE, OFF},
      {RELAY9_PIN, RELAY9_ACTIVE_STATE, RELAY9_DEFAULT_STATE, OFF},
      {RELAY10_PIN, RELAY10_ACTIVE_STATE, RELAY10_DEFAULT_STATE, OFF},
      {RELAY11_PIN, RELAY11_ACTIVE_STATE, RELAY11_DEFAULT_STATE, OFF},
      {RELAY12_PIN, RELAY12_ACTIVE_STATE, RELAY12_DEFAULT_STATE, OFF},
      {RELAY13_PIN, RELAY13_ACTIVE_STATE, RELAY13_DEFAULT_STATE, OFF},
      {RELAY14_PIN, RELAY14_ACTIVE_STATE, RELAY14_DEFAULT_STATE, OFF},
      {RELAY15_PIN, RELAY15_ACTIVE_STATE, RELAY15_DEFAULT_STATE, OFF},
      {RELAY16_PIN, RELAY16_ACTIVE_STATE, RELAY16_DEFAULT_STATE, OFF},
      {RELAY17_PIN, RELAY17_ACTIVE_STATE, RELAY17_DEFAULT_STATE, OFF},
      {RELAY18_PIN, RELAY18_ACTIVE_STATE, RELAY18_DEFAULT_STATE, OFF}
    };
};

extern Relay relay;