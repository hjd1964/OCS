// -----------------------------------------------------------------------------------------------------------------
// Basic relay functions

// do timed relay off control
void RelayTimedOff() {
  // run once/thirty seconds
  if ((long)(tst-millis())<0) {
    tst=millis()+30000UL;
  
    // Timed relay off
    for (int i=1; i<=14; i++) {
      if ((relayState[i]>1) && (relayState[i]<10)) {
        relayState[i]-=1;
        if (relayState[i]==1) { setRelayOff(i); }
      }
    }
  }
}

// do PWM on a solid state relay (ISR,) this runs at 1kHz
volatile byte fastPwmCycle = 0;
volatile byte slowPwmCycle = 0;
volatile int count = 0;
void RelayPwmISR() {
  fastPwmCycle++; if (fastPwmCycle>9) { fastPwmCycle=0; }
  for (int i=7; i<=14; i++) {
    if (relayState[i]>=10) {
      if (fastPwmCycle==0) {
        setRelayOn(i,false);
      } else {
        if ((relayState[i]/10)==fastPwmCycle) { setRelayOff(i,false); }
      }
    }
  }

#ifdef ROR_ON
#if defined(ROR_PWM_SPEED_HZ) && defined(ROR_PWM_POWER_PERCENT)
  if (roofIsMoving()) {
    count++; if (count>=(1000/(ROR_PWM_SPEED_HZ*10))) {
      count=0;
      slowPwmCycle++; if (slowPwmCycle>9) slowPwmCycle=0;
      if (slowPwmCycle==0) setRelayOn(ROR_PWR_RELAY);
      if ((!roofMaxPowerOn()) && ((roofPowerLevel()/10)==slowPwmCycle)) setRelayOff(ROR_PWR_RELAY);
    }
  } else {
    count=0; slowPwmCycle=0;
    if (relayIsOn(ROR_PWR_RELAY)) setRelayOff(ROR_PWR_RELAY);
  }
#endif

  // ROR safety shutoff (via direction relays) here in an ISR where it can't be blocked by anything just incase the main-loop blocks
  if (relayIsOn(ROR_DIR_RELAY_A) && senseIsOn(ROR_OPENED_LIMIT_SENSE)) stopRoof();
  if (relayIsOn(ROR_DIR_RELAY_B) && senseIsOn(ROR_CLOSED_LIMIT_SENSE)) stopRoof();
#endif
}

void setRelayOn(int r) { setRelayOn(r,true); }

void setRelayOn(int r, bool updateState) {
  if ((r>=1) && (r<=14)) {
    if (updateState) relayState[r]=1;
    digitalWrite(relay[r].pin,relay[r].onState);
  }
}

void setRelayPwm(int r, int percentPower) {
  percentPower/=10;
  if ((r>=7) && (r<=14) && ((percentPower>=1) && (percentPower<=9))) {
    relayState[r]=10+percentPower;
  }
}

void setRelayOnDelayedOff(int r, int minutes) {
  if (((r>=1) && (r<=14)) && ((minutes>=2) && (minutes<=9))) {
    relayState[r]=round(minutes/2);
    digitalWrite(relay[r].pin,relay[r].onState);
  }
}

void setRelayOff(int r) { setRelayOff(r,true); }

void setRelayOff(int r, bool updateState) {
  if ((r>=1) && (r<=14)) {
    if (updateState) relayState[r]=0;
    uint8_t offState=LOW;
    if (relay[r].onState==LOW) offState=HIGH;
    digitalWrite(relay[r].pin,offState);
  }
}

bool relayIsOn(char rs[]) { return relayIsOn(atoi(rs)); }

bool relayIsOn(int r) {
  if ((r>=1) && (r<=14)) return !(relayState[r]==0); else return false;
}

bool senseChanged(int s) {
  if ((s>=1) && (s<=6)) {
    bool currentState=false;
    if (digitalRead(sense[s].pin)==sense[s].onState) currentState=true;
    return currentState!=senseState[s];
  } else return false;
}

bool senseIsOn(int s) {
  if ((s>=1) && (s<=6)) {
    bool currentState=false;
    if (digitalRead(sense[s].pin)==sense[s].onState) currentState=true;
    senseState[s]=currentState;
    return currentState;
  } else return false;
}

