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
        if (relayState[i]==1) { digitalWrite(relayPin[i],LOW); relayState[i]=0; }
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
        relayState[i]=1; digitalWrite(relayPin[i],HIGH);
      } else {
        if ((relayState[i]/10)==fastPwmCycle) { relayState[i]=0; digitalWrite(relayPin[i],LOW); }
      }
    }
  }

#if defined(ROR_PWM_SPEED_HZ) && defined(ROR_PWM_POWER_PERCENT)
  if (roofState!='i') {
    count++; if (count>=(1000/(ROR_PWM_SPEED_HZ*10))) {
      count=0;
      slowPwmCycle++; if (slowPwmCycle>9) { slowPwmCycle=0; }
      if (slowPwmCycle==0) {
        relayState[ROR_PWR_RELAY]=1; digitalWrite(relayPin[ROR_PWR_RELAY],HIGH);
      }
      if ((!roofMaxPower) && ((roofCurrentPower/10)==slowPwmCycle)) { relayState[ROR_PWR_RELAY]=0; digitalWrite(relayPin[ROR_PWR_RELAY],LOW); }
    }
  } else {
    if (relayState[ROR_PWR_RELAY]==1) { relayState[ROR_PWR_RELAY]=0; digitalWrite(relayPin[ROR_PWR_RELAY],LOW); }
  }
#endif

#ifdef ROR_ON
  // ROR safety shutoff (via direction relays) here in an ISR where it can't be blocked by anything just incase the main-loop blocks
  if ((relayState[ROR_DIR_RELAY_A]==1) && (digitalRead(sensePin[ROR_OPENED_LIMIT_SENSE]))) { digitalWrite(relayState[ROR_DIR_RELAY_A], LOW); relayState[ROR_DIR_RELAY_A]=0; }
  if ((relayState[ROR_DIR_RELAY_B]==1) && (digitalRead(sensePin[ROR_CLOSED_LIMIT_SENSE]))) { digitalWrite(relayState[ROR_DIR_RELAY_B], LOW); relayState[ROR_DIR_RELAY_B]=0; }
#endif

}

bool relayOn(char rs[]) {
  int i=atoi(rs);
  if ((i>=1) && (i<=14)) return !(relayState[i]==0); else return false;
}

