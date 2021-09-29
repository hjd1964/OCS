// -----------------------------------------------------------------------------------------------------------------
// Observatory power (relays)
#pragma once

#include "../../Common.h"

#if POWER == ON

#include "../../commands/ProcessCmds.h"

class Power {
  public:
    bool command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError);

  private:
};

extern Power power;

#endif
