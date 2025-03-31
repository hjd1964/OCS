// -----------------------------------------------------------------------------------------------------------------
// Observatory lighting commands

#include "Lighting.h"

#ifdef LIGHT_PRESENT

bool Lighting::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {
  UNUSED(supressFrame);

  #if LIGHT != OFF
    //  :GLW# Get warm room light mode 
    if (command[0] == 'G' && command[1] == 'L' && parameter[0] == 'W' && parameter[1] == 0) {
      if (get(LL_WARM_ROOM) == LM_OFF) strcpy(reply, "OFF"); else
      if (get(LL_WARM_ROOM) == LM_RED) strcpy(reply, "RED"); else
      if (get(LL_WARM_ROOM) == LM_WHITE) strcpy(reply, "WHITE");
      *numericReply = false;
    } else

    //  :GLO# Get observing room light mode
    if (command[0] == 'G' && command[1] == 'L' && parameter[0] == 'O' && parameter[1] == 0) {
      if (get(LL_OBSERVING_ROOM) == LM_OFF) strcpy(reply, "OFF"); else
      if (get(LL_OBSERVING_ROOM) == LM_RED) strcpy(reply, "RED"); else
      if (get(LL_OBSERVING_ROOM) == LM_WHITE) strcpy(reply, "WHITE");
      *numericReply = false;
    } else

    //  :SLW,[mode]# Set warm room light [mode] = OFF, RED, WHITE 
    //         Example: :SLW,OFF#
    //         Returns: 1 on success, 0 on failure
    if (command[0] == 'S' && command[1] == 'L' && parameter[0] == 'W' && parameter[1] == ',') {
      String ws = String(parameter);
      ws = ws.substring(2);
      if (ws.equals("OFF")) set(LL_WARM_ROOM, LM_OFF); else
      if (ws.equals("RED")) set(LL_WARM_ROOM, LM_RED); else
      if (ws.equals("WHITE")) set(LL_WARM_ROOM, LM_WHITE); else *commandError = CE_PARAM_FORM;
    } else

    //  :SLO,[mode]# Set observing room light [mode] = OFF, RED, WHITE 
    //         Example: :SLO,RED#
    //         Returns: 1 on success, 0 on failure
    if (command[0] == 'S' && command[1] == 'L' && parameter[0] == 'O' && parameter[1] == ',') {
      String ws = String(parameter);
      ws = ws.substring(2);
      if (ws.equals("OFF")) set(LL_OBSERVING_ROOM, LM_OFF); else
      if (ws.equals("RED")) set(LL_OBSERVING_ROOM, LM_RED); else
      if (ws.equals("WHITE")) set(LL_OBSERVING_ROOM, LM_WHITE); else *commandError = CE_PARAM_FORM;
    } else
  #endif

  return false;
  
  return true;
}

#endif
