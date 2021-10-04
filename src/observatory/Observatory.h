
// -----------------------------------------------------------------------------------
// Observatory
#pragma once

#include "../commands/ProcessCmds.h"

#ifdef ESP8266
  #ifndef ETHERNET_W5500
    #error "The ESP8266 Ethernet option supports the W5500 only"
  #endif
  #include <Ethernet2.h>  // https://github.com/adafruit/Ethernet2
#else
  #include <Ethernet.h>
#endif

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
