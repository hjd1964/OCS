// -----------------------------------------------------------------------------------
// Observatory commands

#include "../Common.h"
#include "../tasks/OnTask.h"

#include "../lib/convert/Convert.h"
#include "../lib/sense/Sense.h"
#include "../lib/analog/Analog.h"

#include "Observatory.h"
#include "safety/Safety.h"
#include "power/Power.h"
#include "roof/Roof.h"
#include "thermostat/Thermostat.h"
#include "weather/Weather.h"

bool Observatory::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {

  if (power.command(reply, command, parameter, supressFrame, numericReply, commandError)) return true;

  #if ROOF == ON
    if (roof.command(reply, command, parameter, supressFrame, numericReply, commandError)) return true;
  #endif

  #if THERMOSTAT == ON
    if (thermostat.command(reply, command, parameter, supressFrame, numericReply, commandError)) return true;
  #endif

  #if WEATHER == ON
    if (weather.command(reply, command, parameter, supressFrame, numericReply, commandError)) return true;
  #endif

  if (command[0] == 'G') {
    //  :GAn#  Get Analog n state
    //         Example: :GA1#
    //         Returns: 124# (0 to 1023, 0 to 5V)
    if (command[1] == 'A' && parameter[1] == 0) {
      if ((parameter[0] >= '0' && parameter[0] <= '9') || (parameter[0] >= 'A' && parameter[0] <= 'F')) {
        int i = parameter[0] - '0';
        if (i > 9) i -= 7;
        *numericReply = false;
        sprintf(reply, "%d", (int)lroundf(analog.read(i)*1023.0));
      } else *commandError = CE_PARAM_RANGE;
    } else

    //  :GP#  Get power status
    //         Returns: OK#, OUT#, or N/A#
    //         
    if (command[1] == 'P' && parameter[0] == 0) {
      #if STAT_MAINS_SENSE != OFF
        if (sense.isOn(STAT_MAINS_SENSE)) strcpy(reply, "OK"); else strcpy(reply, "OUT"); 
      #else
        strcpy(reply, "N/A");
      #endif
      *numericReply = false;
    } else

    //  :GSn#  Get Digital Sense n state
    //         Example: :GS1#
    //         Returns: ON#, OFF#
    if (command[1] == 'S' && parameter[1] == 0) {
      if (parameter[0] >= '1' && parameter[0] <= '6') {
        int i = parameter[0] - '0';
        if (sense.isOn(i)) strcpy(reply, "ON"); else strcpy(reply, "OFF");
      *numericReply = false;
      } else *commandError = CE_PARAM_RANGE;
    } else

    //  :Gs#  Get safety status
    //         Example: :Gs#
    //         Returns: SAFE#, UNSAFE#
    if (command[1] == 's' && parameter[0] == 0) {
      if (safety.isSafe()) strcpy(reply,"SAFE"); else strcpy(reply,"UNSAFE");
      *numericReply = false;
    } else *commandError = CE_CMD_UNKNOWN;
  } else

  if (command[0] == 'I') {
    //  :IN#  get version Number
    //         Returns: s#
    if (command[1] == 'N' && parameter[0] == 0) {
      sprintf(reply, "%i.%i%s", (int)firmware.version.major, (int)firmware.version.minor, firmware.version.patch);
      *numericReply = false;
    } else

    //  :IP#  get Product (compatibility)
    //         Returns: s#
    if (command[1] == 'P' && parameter[0] == 0) {
      strcpy(reply, firmware.name);
      *numericReply = false;
    } else
      *commandError = CE_CMD_UNKNOWN;
  } else

  if (command[0] == 'S') {
    //  :SW#  Set the watchdog reset flag
    #if WATCHDOG != OFF
      if (command[1] == 'W' && parameter[0] == 0) {
        if (!roof.isMoving()) {
          strcpy(reply,"Rebooting in 8 seconds...");
          while (true) {};
        } else *commandError = CE_ROOF_IN_MOTION;
      } else
    #endif
      return false;
  } else return false;

  return true;
};
