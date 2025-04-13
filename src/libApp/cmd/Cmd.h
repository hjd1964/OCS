// -----------------------------------------------------------------------------------
// Help with commands, etc.
#pragma once

#include "../../Common.h"

#if defined(SERIAL_IP) || defined(SERIAL_UART)

class MountCmd {
  public:
    void commandBlind(const char* cmd, long timeOutMs = 1000);
    int commandBool(const char* cmd, long timeOutMs = 1000);
    int commandString(const char* cmd, char* response, long timeOutMs = 1000);

  private:
};

extern MountCmd mount;

#endif
