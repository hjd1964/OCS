// AutoClose plugin

/* This plugin replaces the existing roof auto-close functionality with a version
*  that allows the user to disable auto-closing of the roof by sending a command.
*  The intended use is for when the observatory is manned and being dubugged where
*  the user does not want the roof to close automatically on bad weather conditions,
*  but still wants to monitor the weather conditions and have the ability to enable
*  auto-closing when desired.
*  A definable output pin is also provided to allow for a warning light that the auto
*  close is disabled and current safety status.
*/


#pragma once

#include "../../lib/commands/CommandErrors.h"
#include "../../Common.h"
#include "../../lib/tasks/OnTask.h"
#include "../../lib/sense/Sense.h"
#include "../../libApp/weatherSensor/WeatherSensor.h"
#include "../../observatory/weather/Weather.h"
#include "../../observatory/roof/Roof.h"

// User configuration for warning output
#define AUTOCLOSE_OUTPUT_PIN    OFF // Set to pin number or OFF to disable
#define AUTOCLOSE_OUTPUT_ON    HIGH // Set to HIGH or LOW for ON state

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
