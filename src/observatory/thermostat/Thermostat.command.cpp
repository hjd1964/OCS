// -----------------------------------------------------------------------------------------------------------------
// Observatory thermostat commands

#include "Thermostat.h"

#if THERMOSTAT == ON

#include "../../lib/weatherSensor/WeatherSensor.h"

bool Thermostat::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {

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
          setRelayOff(HEAT_RELAY);
        } else
        if (i >= 1 && i <= 40) {
          setHeatSetpoint(i);
          msFiveMinuteCounter = millis() + 5000UL;
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
          setRelayOff(COOL_RELAY);
        } else
        if (i >= 1 && i <= 40) {
          setCoolSetpoint(i);
          msFiveMinuteCounter = millis() + 5000UL;
        } else *commandError = CE_PARAM_RANGE;
      } else
    #endif
      return false;
  } else
    return false;

  return true;
}

#endif
