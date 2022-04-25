// -----------------------------------------------------------------------------------------------------------------
// Relay control
#pragma once

#include "../../Common.h"

#define RELAYS_MAX 18

typedef struct RelaySettings {
  int8_t pin;
  uint8_t onState;
  int8_t defaultState;
  uint16_t state;
} RelaySettings;

class Relay {
  public:
    void init();

    void on(int r, bool updateState);

    inline void on(int r) { on(r, true); }

    void onDelayedOff(int r, float seconds);

    void power(int r, int percentPower);

    void off(int r, bool updateState);

    inline void off(int r) { off(r, true); }

    bool isOn(int r);

    inline bool isOn(const char *rs) { return isOn(atoi(rs)); }

    bool isOnDelayedOff(int r);

    void poll();

    void pwm();

  private:
    volatile uint8_t fastPwmCycle = 0;
    volatile uint8_t slowPwmCycle = 0;

    volatile int count = 0;

    volatile RelaySettings settings[RELAYS_MAX] {
      {RELAY1_PIN, RELAY1_ON_STATE, RELAY1_DEFAULT_STATE, 0},
      {RELAY2_PIN, RELAY2_ON_STATE, RELAY2_DEFAULT_STATE, 0},
      {RELAY3_PIN, RELAY3_ON_STATE, RELAY3_DEFAULT_STATE, 0},
      {RELAY4_PIN, RELAY4_ON_STATE, RELAY4_DEFAULT_STATE, 0},
      {RELAY5_PIN, RELAY5_ON_STATE, RELAY5_DEFAULT_STATE, 0},
      {RELAY6_PIN, RELAY6_ON_STATE, RELAY6_DEFAULT_STATE, 0},
      {RELAY7_PIN, RELAY7_ON_STATE, RELAY7_DEFAULT_STATE, 0},
      {RELAY8_PIN, RELAY8_ON_STATE, RELAY8_DEFAULT_STATE, 0},
      {RELAY9_PIN, RELAY9_ON_STATE, RELAY9_DEFAULT_STATE, 0},
      {RELAY10_PIN, RELAY10_ON_STATE, RELAY10_DEFAULT_STATE, 0},
      {RELAY11_PIN, RELAY11_ON_STATE, RELAY11_DEFAULT_STATE, 0},
      {RELAY12_PIN, RELAY12_ON_STATE, RELAY12_DEFAULT_STATE, 0},
      {RELAY13_PIN, RELAY13_ON_STATE, RELAY13_DEFAULT_STATE, 0},
      {RELAY14_PIN, RELAY14_ON_STATE, RELAY14_DEFAULT_STATE, 0},
      {RELAY15_PIN, RELAY15_ON_STATE, RELAY15_DEFAULT_STATE, 0},
      {RELAY16_PIN, RELAY16_ON_STATE, RELAY16_DEFAULT_STATE, 0},
      {RELAY17_PIN, RELAY17_ON_STATE, RELAY17_DEFAULT_STATE, 0},
      {RELAY18_PIN, RELAY18_ON_STATE, RELAY18_DEFAULT_STATE, 0}
    };
};

extern Relay relay;
