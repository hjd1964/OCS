// -----------------------------------------------------------------------------------------------------------------
// Thermostat functions

#ifdef THERMOSTAT_ON

// gets inside temperature in deg. C
// I'm using an LM335
// ======= add your inside temperature sensor support here ========
double thermostatInsideTemp() {
  // read lm335 temperature
  // 0..5 volts for 4096 count DA converter
  double t=25.0+(((analogRead(3)/1024.0)*5.0)-2.982)*100.0;
  if ((t<-60.0) || (t>60.0)) t=invalid;
  return t;
}

double t1=-999;
double t2=-999;

// control temperature in observatory
void thermostat() {
  if ((long)(millis()-msFiveMinuteCounter)>=0) {
    msFiveMinuteCounter=millis()+300000UL;

    t2=t1; t1=thermostatInsideTemp(); if (t2==-999) { t2=t1; }
    insideTemperature=(t1+t2)/2.0; // average last two readings

    if (insideTemperature==invalid) {
#ifdef HEAT_RELAY
      relayState[HEAT_RELAY]=0; digitalWrite(relayPin[HEAT_RELAY],LOW);
#endif
#ifdef COOL_RELAY
      relayState[COOL_RELAY]=0; digitalWrite(relayPin[COOL_RELAY], LOW);
#endif
      return;
    }

#ifdef HEAT_RELAY
    if (insideTemperature<getHeatSetpoint() && (getHeatSetpoint()!=0)) {
      relayState[HEAT_RELAY]=1; digitalWrite(relayPin[HEAT_RELAY],HIGH);
    } else {
      relayState[HEAT_RELAY]=0; digitalWrite(relayPin[HEAT_RELAY],LOW);
    }
#endif

#ifdef COOL_RELAY
    if (insideTemperature>getCoolSetpoint() && (getCoolSetpoint()!=0)) {
      relayState[COOL_RELAY]=1; digitalWrite(relayPin[COOL_RELAY], HIGH);
    } else {
      relayState[COOL_RELAY]=0; digitalWrite(relayPin[COOL_RELAY], LOW);
    }
#endif
  }
}

#ifdef HEAT_RELAY
void setHeatSetpoint(float f) {
  EEPROM_writeFloat(EE_heatSetpoint,f);
}
float getHeatSetpoint() {
  return EEPROM_readFloat(EE_heatSetpoint);
}
#endif
#ifdef COOL_RELAY
void setCoolSetpoint(float f) {
  EEPROM_writeFloat(EE_coolSetpoint,f);
}
float getCoolSetpoint() {
  return EEPROM_readFloat(EE_coolSetpoint);
}
#endif
#endif

