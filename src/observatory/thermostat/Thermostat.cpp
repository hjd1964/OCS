// -----------------------------------------------------------------------------------------------------------------
// Observatory thermostat

#include "Thermostat.h"

#if THERMOSTAT == ON

#include "../../lib/thermostatSensor/ThermostatSensor.h"

// this gets called once on startup to initialize any thermostat sensors
void Thermostat::init() {
  analogReference(DEFAULT);
  thermostatSensor.init();
}

// control temperature in observatory, call once every 5 minutes
void Thermostat::poll() {
  t2 = t1;
  t1 = thermostatSensor.temperature();
  if (isnan(t2)) t2 = t1;
  averageTemperature = (t1 + t2)/2.0; // average last two readings

  #if HEAT_RELAY != OFF
    if (!isnan(averageTemperature) && averageTemperature < getHeatSetpoint() && getHeatSetpoint() != 0) {
      setRelayOn(HEAT_RELAY);
    } else {
      setRelayOff(HEAT_RELAY);
    }

  #elif COOL_RELAY != OFF
    if (!isnan(averageTemperature) && averageTemperature > getCoolSetpoint() && getCoolSetpoint() != 0) {
      setRelayOn(COOL_RELAY);
    } else {
      setRelayOff(COOL_RELAY);
    }
  #endif
}

void Thermostat::setHeatSetpoint(float value) {
  nv.write(NV_HEAT_SETPOINT, (float)value);
}

float Thermostat::getHeatSetpoint() {
  return nv.readF(NV_HEAT_SETPOINT);
}

void Thermostat::setCoolSetpoint(float value) {
  nv.write(NV_COOL_SETPOINT, (float)value);
}

float Thermostat::getCoolSetpoint() {
  return nv.readF(NV_COOL_SETPOINT);
}

Thermostat thermostat;

#endif
