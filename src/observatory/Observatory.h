
// -----------------------------------------------------------------------------------
// Observatory
#pragma once

#include "../Common.h"
#include "../libApp/commands/ProcessCmds.h"

typedef struct InitError {
  uint8_t nv:1;       // NV data size/structure error (disables writes to NV)
  uint8_t value:1;    // invalid value error
  uint8_t driver:1;   // the stepper driver wasn't detected properly (TMC SPI drivers only)
  uint8_t weather:1;  // the weather source (BME280, etc.) was not found
  uint8_t tls:1;      // the time location source (DS3231, GPS, etc.) was not found
} InitError;

extern InitError initError;

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
    inline static void lockup() { while (true) {};}

  private:
    Firmware firmware;
    bool fastNTPSync = false;
    IPAddress connectCheckIP = IPAddress CONNECT_IP_ADDR;
};

extern Observatory observatory;
