// -----------------------------------------------------------------------------------------------------------------
// Observatory power (relay) commands

#include "Power.h"

#if POWER == ON

#include "../../lib/relay/Relay.h"

bool Power::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {

  if (command[0] == 'G') {
    //  :GRn#  Get Relay n state
    //         Example: :GR1#
    //         Returns: ON#, OFF#, n# (pwm 0-9)
    if (command[1] == 'R' && parameter[1] == 0) {
      if ((parameter[0] >= '1' && parameter[0] <= '9') || (parameter[0] >= 'A' && parameter[0] <= 'E')) {
        int r = parameter[0] - '0';
        if (r > 9) r -= 7;
        if (!relay.isOn(r)) strcpy(reply, "OFF"); else
        if (relay.isOn(r)) strcpy(reply, "ON"); else
        if (relay.isOnDelayedOff(r)) strcpy(reply, "DELAY"); else strcpy(reply, "?");
        *numericReply = false;
      } else *commandError = CE_PARAM_RANGE;
    } else return false;
  } else

  if (command[0] == 'S') {
    //  :SRn,[state]#  Set Relay n [state] = ON, OFF, DELAY, n (pwm 1-9)
    //         Example: :SR1,ON#
    //         Returns: 1 on success
    if (command[1] == 'R' && parameter[1] == ',') {
      if ((parameter[0] >= '1' && parameter[0] <= '9') || (parameter[0] >= 'A' && parameter[0] <= 'E')) {
        int r = parameter[0] - '0';
        if (r > 9) r -= 7;
        String ws = String(parameter);
        ws = ws.substring(2);
        if (ws == "DELAY") relay.onDelayedOff(r, 30); else
        if (ws == "ON")    relay.on(r); else
        if (ws == "OFF")   relay.off(r); else
        if (ws.length() == 1) {
          int j = ws[0] - '0';
          relay.pwm(r, j*10);
        } else *commandError = CE_PARAM_FORM;
      } else *commandError = CE_PARAM_RANGE;
    } else return false;
  } else return false;

  return true;
}

Power power;

#endif
