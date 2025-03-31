// -----------------------------------------------------------------------------------------------------------------
// Observatory power (relay) commands

#include "Power.h"

#include "../../libApp/relay/Relay.h"

bool Power::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {
  UNUSED(supressFrame);

  if (command[0] == 'G') {
    //  :GRn#  Get Relay n state
    //         Example: :GR1#
    //         Returns: ON#, OFF#, n# (pwm 0-9)
    if (command[1] == 'R' && (parameter[1] == 0 || parameter[2] == 0)) {
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
    //  :SRn,[state]#  Set Relay n [state] = ON, OFF, DELAY, n (pwm 0 to 10)
    //         Example: :SR1,ON#
    //         Returns: 1 on success
    if (command[1] == 'R' && (parameter[1] == ',' || parameter[2] == ',')) {
      int separator = 0;
      if (parameter[1] == ',') {separator = 2;}
      else if (parameter[2] == ',') {separator = 3;}
      int r = atoi(parameter);
      if (r >= 1 && r <= RELAYS_MAX) {
        String ws = String(parameter);
        ws = ws.substring(separator);
        if (ws.equals("DELAY")) relay.onDelayedOff(r, 30); else
        if (ws.equals("ON"))    relay.on(r); else
        if (ws.equals("OFF"))   relay.off(r); else
        if (ws.length() == 1 && ws[0] >= '0' && ws[0] <= '9') {
          int j = ws[0] - '0';
          relay.power(r, j*10);
        } else
        if (ws == "10") {
          relay.power(r, 100);
        } else
        *commandError = CE_PARAM_FORM;
      } else *commandError = CE_PARAM_RANGE;
    } else return false;
  } else

  #ifdef LIGHT_PRESENT
    //  :IL#  get Light relay #defines
    //         Returns: 8,9,10,-1,12#, LIGHT_WRW_RELAY,LIGHT_WRR_RELAY,LIGHT_ORW_RELAY,LIGHT_ORR_RELAY,
    //                                ,LIGHT_OUTSIDE_RELAY, -1 for undefined light
    if (command[0] == 'I' && command[1] == 'L' && parameter[0] == 0) {
      sprintf(reply, "%i,%i,%i,%i,%i", LIGHT_WRW_RELAY, LIGHT_WRR_RELAY,
                                        LIGHT_ORW_RELAY, LIGHT_ORR_RELAY, LIGHT_OUTSIDE_RELAY);
      *numericReply = false;
    } else
  #endif

  #ifdef POWER_PRESENT
    //  :Ip#  get Power relay #defines
    //        Returns: 1,2,3,-1,5,6#, POWER_DEVICE1_RELAY,POWER_DEVICE2_RELAY,POWER_DEVICE3_RELAY,
    //                                POWER_DEVICE4_RELAY,POWER_DEVICE5_RELAY,POWER_DEVICE6_RELAY
    //                                -1 for undefined power device
    if (command[0] == 'I' && command[1] == 'p' && parameter[0] == 0) {
      sprintf(reply, "%i,%i,%i,%i,%i,%i", POWER_DEVICE1_RELAY, POWER_DEVICE2_RELAY, POWER_DEVICE3_RELAY,
                                          POWER_DEVICE4_RELAY, POWER_DEVICE5_RELAY, POWER_DEVICE6_RELAY);
      *numericReply = false;
    } else

    //  :Ipn# get Power relay name #defines
    //        Example:  :Ip1#
    //        Returns:  s#
    if (command[0] == 'I' && command[1] == 'p' && parameter[1] == 0) {
      int r = atoi(parameter);
      if (r >= 1 && r <= RELAYS_MAX) {
        if (r == 1) {
          strcpy(reply, POWER_DEVICE1_NAME);
        } else if (r == 2) {
          strcpy(reply, POWER_DEVICE2_NAME);
        } else if (r == 3 ) {
          strcpy(reply, POWER_DEVICE3_NAME);
        } else if (r == 4) {
          strcpy(reply, POWER_DEVICE4_NAME);
        } else if (r == 5) {
          strcpy(reply, POWER_DEVICE5_NAME);
        } else if (r == 6) {
          strcpy(reply, POWER_DEVICE6_NAME);
        }
        *numericReply = false;
      } else *commandError = CE_PARAM_RANGE;
    } else
  #endif

  return false;
  
  return true;
}

Power power;
