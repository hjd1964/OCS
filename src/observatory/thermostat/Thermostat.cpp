// -----------------------------------------------------------------------------------------------------------------
// Observatory thermostat

#include "Thermostat.h"

#ifdef THERMOSTAT_PRESENT

#include "../../lib/tasks/OnTask.h"
#include "../../libApp/thermostatSensor/ThermostatSensor.h"
#include "../../libApp/relay/Relay.h"

void thermostatWrapper() { thermostat.poll(); }

// this gets called once on startup to initialize any thermostat sensors
void Thermostat::init() {
  thermostatSensor.init();

  // start polling task
  VF("MSG: Thermostat, start monitor task (rate 5 min priority 7)... ");
  if (tasks.add(5*60*1000UL, 0, true, 7, thermostatWrapper, "Thermst")) { VLF("success"); } else { VLF("FAILED!"); }
}

// control temperature in observatory, call once every 5 minutes
void Thermostat::poll() {
  t2 = t1;
  t1 = thermostatSensor.temperature();
  if (isnan(t2)) t2 = t1;
  averageTemperature = (t1 + t2)/2.0; // average last two readings

  #if HEAT_RELAY != OFF
    if (!isnan(averageTemperature) && averageTemperature < getHeatSetpoint() && getHeatSetpoint() != 0) {
      relay.on(HEAT_RELAY);
    } else {
      relay.off(HEAT_RELAY);
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
