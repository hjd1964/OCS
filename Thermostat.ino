// -----------------------------------------------------------------------------------------------------------------
// Thermostat functions

#ifdef THERMOSTAT_ON
// ======= add your inside temperature sensor support here ========

// this gets called once on startup to initialize any weather sensors
void thermostatInit() {
  analogReference(DEFAULT);
}

// gets inside temperature in deg. C
// return (invalid) if not implemented or if there's an error
double thermostatInsideTemp() {
  // read lm335 temperature
  // 0..5 volts for 4096 count DA converter
  double t=25.0+(((analogRead(3)/1024.0)*5.0)-2.982)*100.0;
  if ((t<-60.0) || (t>60.0)) t=invalid;
  return t;
}

// gets inside RH in %
// return (invalid) if not implemented or if there's an error
double thermostatInsideHumidity() {
  return (invalid);
}
// =================================================================

double t1=-999;
double t2=-999;

// control temperature in observatory
void thermostat() {
  if ((long)(millis()-msFiveMinuteCounter)>=0) {
    msFiveMinuteCounter=millis()+300000UL;

    t2=t1; t1=thermostatInsideTemp(); if (t2==-999) { t2=t1; }
    insideTemperature=(t1+t2)/2.0; // average last two readings

    if (abs(insideTemperature-invalid)<0.1) {
#ifdef HEAT_RELAY
      setRelayOff(HEAT_RELAY);
#endif
#ifdef COOL_RELAY
      setRelayOff(COOL_RELAY);
#endif
      return;
    }

#ifdef HEAT_RELAY
    if (insideTemperature<getHeatSetpoint() && (getHeatSetpoint()!=0)) {
      setRelayOn(HEAT_RELAY);
    } else {
      setRelayOff(HEAT_RELAY);
    }
#endif
#ifdef COOL_RELAY
    if (insideTemperature>getCoolSetpoint() && (getCoolSetpoint()!=0)) {
      setRelayOn(COOL_RELAY);
    } else {
      setRelayOff(COOL_RELAY);
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

