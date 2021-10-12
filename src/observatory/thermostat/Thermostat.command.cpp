// -----------------------------------------------------------------------------------------------------------------
// Observatory thermostat commands

#include "Thermostat.h"

#if THERMOSTAT == ON

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
      return false;
  } else
    return false;

  return true;
}

#endif
