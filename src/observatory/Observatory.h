
// -----------------------------------------------------------------------------------
// Observatory
#pragma once

#include "../Common.h"

#include "../commands/ProcessCmds.h"

#include "../lib/serial/Serial_IP_Ethernet.h"

typedef struct Version {
  uint8_t major;
  uint8_t minor;
  char patch[2];
  uint8_t config;
} Version;

typedef struct Firmware {
  char name[4];
  Version version;
} Firmware;

class Observatory {
  public:
    void init(const char *fwName, int fwMajor, int fwMinor, const char *fwPatch, int fwConfig);
    bool command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError);

    void connectionCheck();
    void poll();

  private:
    Firmware firmware;
    bool fastNTPSync = false;
    IPAddress connectCheckIP = IPAddress CHECK_IP_ADDR;
};

extern Observatory observatory;
