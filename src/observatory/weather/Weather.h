// -----------------------------------------------------------------------------------
// Weather/Safety monitor and logging
#pragma once

#include "../../Common.h"

#if WEATHER == ON

#include "../../commands/ProcessCmds.h"

#define SecondsBetweenLogEntries 30

// this is the response time required to cover approximately 2/3 of a change in cloud temperature
// adjust higher for less sensitivity to passing clouds/changing conditions, lower for more sensitivity
#define AvgTimeSeconds 600.0

class Weather {
  public:
    bool command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError);

    void init();

    float getSkyDiffTemp();

    float getAvgSkyDiffTemp();

    bool isSafe();

    void poll();

  private:
    void dtostrf2(float d, int i, int i1, float l, float h, char result[]);

    long TimeSeconds = 0;
    unsigned long last = 10000;

    float skyDiffTemp = NAN;
    float avgSkyDiffTemp = NAN;
    float sa = NAN;
    float ss = NAN;
    float sad = NAN;
    float lad = NAN;
    float wa = NAN;
};

extern Weather weather;

#endif
