// -----------------------------------------------------------------------------------------------------------------
// Observatory thermostat
#pragma once

#include "../../Common.h"

#if THERMOSTAT == ON

#include "../../lib/commands/ProcessCmds.h"

class Thermostat {
  public:
    bool command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError);

    void init();
    void poll();

    void setHeatSetpoint(float value);
    float getHeatSetpoint();

    void setCoolSetpoint(float value);
    float getCoolSetpoint();

  private:
    float averageTemperature = NAN;
    float t1 = NAN;
    float t2 = NAN;
};

extern Thermostat thermostat;

#endif
