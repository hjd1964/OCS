// AutoClose plugin
#pragma once

#include "../../lib/commands/CommandErrors.h"
#include "../../Common.h"
#include "../../lib/tasks/OnTask.h"
#include "../../lib/sense/Sense.h"
#include "../../libApp/weatherSensor/WeatherSensor.h"
#include "../../observatory/weather/Weather.h"
#include "../../observatory/roof/Roof.h"

// User configuration for warning output
#ifndef AUTOCLOSE_OUTPUT_PIN
#define AUTOCLOSE_OUTPUT_PIN RELAY16_PIN // Set to desired output pin
#endif
#ifndef AUTOCLOSE_OUTPUT_ON
#define AUTOCLOSE_OUTPUT_ON HIGH // Set to HIGH or LOW for ON state
#endif

// Enable this plugin by defining AUTOCLOSE_PLUGIN in Config.h or build flags
#ifdef AUTOCLOSE_PLUGIN

class AutoClose {
public:
    void init();
    void loop();
    bool isSafe();
    float gustCount() { return wa; }
    void poll();
    bool roofAutoClose = false;
    // Command interface
    bool command(char *reply, char *command, char *parameter, bool *supressFrame, bool *numericReply, CommandError *commandError);
private:
    bool roofAutoCloseInitiated = false;
    int delayForMains = 0;
    float wa = 0;
    float waMax = 600;
    // Blocker logic
    bool overrideEnabled = false;
    bool lastIsSafe = true;
    // Output warning logic
    unsigned long lastToggle = 0;
    bool outputState = false;
    void updateWarningOutput();
};

extern AutoClose autoClose;

#endif
