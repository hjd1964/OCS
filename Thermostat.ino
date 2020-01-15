// -----------------------------------------------------------------------------------------------------------------
// Thermostat functions

#if THERMOSTAT == ON

// =================================================================================================================
// ============================== add your inside temperature sensor support here ==================================

// this gets called once on startup to initialize any weather sensors
void thermostatInit() {
  analogReference(DEFAULT);
}

// gets inside temperature in deg. C
// return (invalid) if not implemented or if there's an error
double thermostatInsideTemp() {
  return invalid;
/*  
  // read lm335 temperature
  // 0..5 volts for 4096 count DA converter
  double t=25.0+(((analogRead(7)/1024.0)*5.0)-2.982)*100.0;
  if ((t<-60.0) || (t>60.0)) t=invalid;
  return t;
*/
}

// gets inside RH in %
// return (invalid) if not implemented or if there's an error
double thermostatInsideHumidity() {
  return (invalid);
}

// ============================== no user changes are required beyond this point ===================================
// =================================================================================================================

double t1=-999;
double t2=-999;

// control temperature in observatory
void thermostat() {
  if ((long)(millis()-msFiveMinuteCounter)>=0) {
    msFiveMinuteCounter=millis()+300000UL;

    t2=t1; t1=thermostatInsideTemp(); if (t2==-999) { t2=t1; }
    insideTemperature=(t1+t2)/2.0; // average last two readings

    if (abs(insideTemperature-invalid)<0.1) {
#if HEAT_RELAY != OFF
      setRelayOff(HEAT_RELAY);
#endif
#if COOL_RELAY != OFF
      setRelayOff(COOL_RELAY);
#endif
      return;
    }

#if HEAT_RELAY != OFF
    if (insideTemperature<getHeatSetpoint() && (getHeatSetpoint()!=0)) {
      setRelayOn(HEAT_RELAY);
    } else {
      setRelayOff(HEAT_RELAY);
    }
#endif
#if COOL_RELAY != OFF
    if (insideTemperature>getCoolSetpoint() && (getCoolSetpoint()!=0)) {
      setRelayOn(COOL_RELAY);
    } else {
      setRelayOff(COOL_RELAY);
    }
#endif
  }
}

#if HEAT_RELAY != OFF
void setHeatSetpoint(float f) {
  EEPROM_writeFloat(EE_heatSetpoint,f);
}
float getHeatSetpoint() {
  return EEPROM_readFloat(EE_heatSetpoint);
}
#endif
#if COOL_RELAY != OFF
void setCoolSetpoint(float f) {
  EEPROM_writeFloat(EE_coolSetpoint,f);
}
float getCoolSetpoint() {
  return EEPROM_readFloat(EE_coolSetpoint);
}
#endif
#endif
