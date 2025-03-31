// -----------------------------------------------------------------------------------
// Observatory commands

#include "../Common.h"
#include "../lib/tasks/OnTask.h"

#include "../lib/convert/Convert.h"
#include "../lib/sense/Sense.h"
#include "../lib/tls/Tls.h"

#include "../libApp/analog/Analog.h"

#include "Observatory.h"
#include "safety/Safety.h"
#include "power/Power.h"
#include "lighting/Lighting.h"
#include "thermostat/Thermostat.h"
#include "weather/Weather.h"
#include "roof/Roof.h"
#include "dome/Dome.h"

bool Observatory::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {

  if (power.command(reply, command, parameter, supressFrame, numericReply, commandError)) return true;

  #ifdef LIGHT_PRESENT
    if (lighting.command(reply, command, parameter, supressFrame, numericReply, commandError)) return true;
  #endif

  #ifdef THERMOSTAT_PRESENT
    if (thermostat.command(reply, command, parameter, supressFrame, numericReply, commandError)) return true;
  #endif

  #ifdef WEATHER_PRESENT
    if (weather.command(reply, command, parameter, supressFrame, numericReply, commandError)) return true;
  #endif

  #ifdef ROOF_PRESENT
    if (roof.command(reply, command, parameter, supressFrame, numericReply, commandError)) return true;
  #endif

  #ifdef DOME_PRESENT
    if (dome.command(reply, command, parameter, supressFrame, numericReply, commandError)) return true;
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
    } else return false;
  } else

  if (command[0] == 'I') {
    //  :IN#  get version Number
    //         Returns: s#
    if (command[1] == 'N' && parameter[0] == 0) {
      sprintf(reply, "%d.%02d%s", (int)firmware.version.major, (int)firmware.version.minor, firmware.version.patch);
      *numericReply = false;
    } else

    //  :IP#  get Product (compatibility)
    //         Returns: s#
    if (command[1] == 'P' && parameter[0] == 0) {
      strcpy(reply, firmware.name);
      *numericReply = false;
    } else

    //  :IT#  get Timeout #defines
    //         Returns: 1.5,2.0#, ROOF_INTERLOCK_PRE_MOVE_TIME,ROOF_INTERLOCK_POST_MOVE_TIME
    if (command[1] == 'T' && parameter[0] == 0) {
      sprintf(reply, "%.1f,%.1f", ROOF_INTERLOCK_PRE_MOVE_TIME, ROOF_INTERLOCK_POST_MOVE_TIME);
      *numericReply = false;
    } else return false;
  } else

  if (command[0] == 'S') {
    //  :SU[MM/DD/YYYY,HH:MM:SS]#
    //            Set the UTC Date and Time
    //            Return: 0 failure, 1 success
    if (command[1] == 'U') {
      if (strlen(parameter) == 19 && parameter[2] == '/' && parameter[5] == '/' && parameter[10] == ',' && parameter[13] == ':' && parameter[16] == ':') {
        int m = atoi(&parameter[0]);
        int d = atoi(&parameter[3]);
        int y = atoi(&parameter[6]);
        int h = atoi(&parameter[11]);
        int n = atoi(&parameter[14]);
        int s = atoi(&parameter[17]);
        if (m >= 1 && m <= 12 && d >= 1 && d <= 31 && y >= 2022 && y <= 3000 && h >= 0 && h <= 23 && n >= 0 && n <= 59 && s >= 0 && s <= 59) {
          tls->set(y, m, d, h, n, s);
        } else *commandError = CE_PARAM_RANGE;
      } else *commandError = CE_PARAM_FORM;
    } else

    //  :SW#  Set the watchdog reset flag
    #if WATCHDOG != OFF
      if (command[1] == 'W' && parameter[0] == 0) {
        #ifdef ROOF_PRESENT
          if (roof.isMoving()) { *commandError = CE_SLEW_IN_MOTION; return true; }
        #endif
        #ifdef DOME_PRESENT
          if (dome.isSlewing()) { *commandError = CE_SLEW_IN_MOTION; return true; }
        #endif
        strcpy(reply, "Rebooting in a few seconds...");
        *numericReply = false;
        tasks.add(1000, 0, false, 7, lockup, "lockup");
      } else
    #endif
      return false;
  } else return false;

  return true;
};
