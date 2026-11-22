// -----------------------------------------------------------------------------------------------------------------
// Observatory power (relays)
#pragma once

#include "../../Common.h"
#include "../../libApp/commands/ProcessCmds.h"

class Power {
  public:
    bool command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError);

    // save relay on/off state to NV for any power device using this relay that has memory enabled
    void rememberState(int relayNum, bool state);

  private:
};

extern Power power;
