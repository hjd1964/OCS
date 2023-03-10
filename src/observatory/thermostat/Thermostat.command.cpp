// -----------------------------------------------------------------------------------------------------------------
// Observatory thermostat commands

#include "Thermostat.h"

#ifdef THERMOSTAT_PRESENT

#include "../../libApp/weatherSensor/WeatherSensor.h"
#include "../../libApp/relay/Relay.h"

bool Thermostat::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {
  UNUSED(*commandError);
  UNUSED(*numericReply);
  UNUSED(*supressFrame);
  UNUSED(*parameter);
  UNUSED(*command);
  UNUSED(*reply);

  if (command[0] == 'G') {
    #if HEAT_RELAY != OFF
      //  :GH#  Get Heat setpoint
      //         Example: :GH#
      //         Returns: 0# or 21#, 0 or temperature in C
      if (command[1] == 'H' && parameter[0] == 0) {
        int i = getHeatSetpoint();
        sprintf(reply, "%d", i);
        *numericReply = false;
      } else
    #endif
    #if COOL_RELAY != OFF
      //  :GV#  Get Cool/Vent setpoint
      //         Example: :GC#
      //         Returns: 0# or 30#, 0 or temperature in C
      if (command[1] == 'V' && parameter[0] == 0) {
        int i = getCoolSetpoint();
        sprintf(reply, "%d", i);
        *numericReply = false;
      } else
    #endif
    #if HUMIDITY_RELAY != OFF
      //  :GD#  Get Humidity setpoint
      //         Example: :GD#
      //         Returns: 0# or 55#, 0 or humidity in %
      if (command[1] == 'D' && parameter[0] == 0) {
        int i = getHumiditySetpoint();
        sprintf(reply, "%d", i);
        *numericReply = false;
      } else
    #endif
    //  :GT#  Get Thermostat status
    //         Example: :GT#
    //         Returns: 22.3,58.7, temperature in deg. C, humidity in %
    if (command[1] == 'T' && parameter[0] == 0) {
      float t = getTemperature();
      float h = getHumidity();
      sprintf(reply, "%.1f,%.1f", t, h);
      *numericReply = false;
    } else
      return false;
  } else

  if (command[0] == 'S') {
    #if HEAT_RELAY != OFF
      //  :SHnn#  Set heat nn = temperature in deg. C
      //         Example: :SH0# turns heat off
      //         Example: :SH21# heat setpoint 21 deg. C
      //         Returns: 1 on success
      if (command[1] == 'H') {
        String ws = String(parameter);
        int i = ws.toInt();
        if (i == 0) {
          setHeatSetpoint(0);
          relay.off(HEAT_RELAY);
        } else
        if (i >= 1 && i <= 40) {
          setHeatSetpoint(i);
        } else *commandError = CE_PARAM_RANGE;
      } else
    #endif
    #if COOL_RELAY != OFF
      //  :SCnnn#  Set cool nnn = temperature in deg. C
      //         Example: :SC0# turns cooling off
      //         Example: :SC30# cool setpoint 30 deg. C
      //         Returns: 1 on success
      if (command[1] == 'C') {
        String ws = String(parameter);
        int i = ws.toInt();
        if (i == 0) {
          setCoolSetpoint(0);
          relay.off(COOL_RELAY);
        } else
        if (i >= 1 && i <= 40) {
          setCoolSetpoint(i);
        } else *commandError = CE_PARAM_RANGE;
      } else
    #endif
    #if HUMIDITY_RELAY != OFF
      //  :SDnnn#  Set humidity nnn = humidity in %
      //         Example: :SD0# turns dehumidifying off
      //         Example: :SD55# dehumidifying setpoint 55%
      //         Returns: 1 on success
      if (command[1] == 'D') {
        String ws = String(parameter);
        int i = ws.toInt();
        if (i == 0) {
          setHumiditySetpoint(0);
          relay.off(HUMIDITY_RELAY);
        } else
        if (i >= 1 && i <= 40) {
          setHumiditySetpoint(i);
        } else *commandError = CE_PARAM_RANGE;
      } else
    #endif
      return false;
  } else
    return false;

  return true;
}

#endif
