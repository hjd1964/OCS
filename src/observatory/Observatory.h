
// -----------------------------------------------------------------------------------
// Observatory
#pragma once

#include "../commands/ProcessCmds.h"

typedef struct Version {
  uint8_t major;
  uint8_t minor;
  char patch[2];
  uint8_t config;
} Version;

typedef struct Firmware {
  char name[8];
  Version version;
  char date[20];
  char time[20];
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
};

extern Observatory observatory;
