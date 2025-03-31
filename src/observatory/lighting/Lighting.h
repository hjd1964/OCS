// -----------------------------------------------------------------------------------------------------------------
// Observatory lighting
#pragma once

#include "../../Common.h"
#include "../../libApp/commands/ProcessCmds.h"

#ifdef LIGHT_PRESENT

#if LIGHT_STRIP_DATA_PIN != OFF
  #include <FastLED.h>
#endif

enum LightLocation {LL_WARM_ROOM, LL_OBSERVING_ROOM};
enum LightMode {LM_OFF, LM_RED, LM_WHITE};

class Lighting {
  public:
    bool command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError);

    void init();

    void set(LightLocation location, LightMode color);
    LightMode get(LightLocation location);

  private:
    #if LIGHT_STRIP_DATA_PIN != OFF
      CRGB leds[LIGHT_STRIP_COUNT];
    #endif
    LightMode observingRoomLightMode = LM_OFF;
    LightMode warmRoomLightMode = LM_OFF;
};

extern Lighting lighting;

#endif
