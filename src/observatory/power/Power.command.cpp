// -----------------------------------------------------------------------------------------------------------------
// Observatory power (relay) commands

#include "Power.h"

#include "../../lib/relay/Relay.h"

bool Power::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {

  if (command[0] == 'G') {
    //  :GRn#  Get Relay n state
    //         Example: :GR1#
    //         Returns: ON#, OFF#, n# (pwm 0-9)
    if (command[1] == 'R' && parameter[1] == 0) {
      int r = atoi(parameter);
      if (r >= 1 && r <= RELAYS_MAX) {
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
      int r = atoi(parameter);
      if (r >= 1 && r <= RELAYS_MAX) {
        String ws = String(parameter);
        ws = ws.substring(2);
        if (ws.equals("DELAY")) relay.onDelayedOff(r, 30); else
        if (ws.equals("ON"))    relay.on(r); else
        if (ws.equals("OFF"))   relay.off(r); else
        if (ws.length() == 1) {
          int j = ws[0] - '0';
          relay.power(r, j*10);
        } else *commandError = CE_PARAM_FORM;
      } else *commandError = CE_PARAM_RANGE;
    } else return false;
  } else return false;

  return true;
}

Power power;
