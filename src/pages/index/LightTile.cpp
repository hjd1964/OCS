// light ----------------------------------------------------------------------
#include "LightTile.h"

#if LIGHT == ON
  #include "../../libApp/relay/Relay.h"
  #include "../../observatory/lighting/Lighting.h"
  #include "../CheckHelp.h"

  void lightTile() {
    char temp[288];

    strcpy_P(temp, htmlLightingBeg);
    www.sendContent(temp);

    strcpy_P(temp, htmlLighting1);
    #if LIGHT_WRW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      if (lighting.get(LL_WARM_ROOM) == LM_WHITE) check(temp, "%___WRW"); else erase(temp, "%___WRW");
    #endif
    #if LIGHT_WRR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      if (lighting.get(LL_WARM_ROOM) == LM_RED) check(temp, "%___WRR"); else erase(temp, "%___WRR");
    #endif    
    if (strlen(temp) > 0) www.sendContent(temp);

    strcpy_P(temp, htmlLighting2);
    #if LIGHT_ORW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      if (lighting.get(LL_OBSERVING_ROOM) == LM_WHITE) check(temp, "%___ORW"); else erase(temp, "%___ORW");
    #endif
    #if LIGHT_ORR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      if (lighting.get(LL_OBSERVING_ROOM) == LM_RED) check(temp, "%___ORR"); else erase(temp, "%___ORR");
    #endif
    if (strlen(temp) > 0) www.sendContent(temp);

    strcpy_P(temp, htmlLightingExit);
    www.sendContent(temp);

    strcpy_P(temp,htmlLightingEnd);
    www.sendContent(temp);
  }

  void lightTileAjax() {
    #if LIGHT_WRW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      www.sendContent("light_WRW|"); www.sendContent((lighting.get(LL_WARM_ROOM) == LM_WHITE) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if LIGHT_WRR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      www.sendContent("light_WRR|"); www.sendContent((lighting.get(LL_WARM_ROOM) == LM_RED)  ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if LIGHT_ORW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      www.sendContent("light_ORW|"); www.sendContent((lighting.get(LL_OBSERVING_ROOM) == LM_WHITE) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if LIGHT_ORR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      www.sendContent("light_ORR|"); www.sendContent((lighting.get(LL_OBSERVING_ROOM) == LM_RED) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
  }

  void lightTileGet() {
    String s;
    UNUSED(s);

    #if LIGHT_WRW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      s = www.arg("light_WRW");
      if (s.equals("true")) {
        lighting.set(LL_WARM_ROOM, LM_WHITE);
      } else
      if (s.equals("false")) {
        lighting.set(LL_WARM_ROOM, LM_OFF);
      }
    #endif

    #if LIGHT_WRR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      s = www.arg("light_WRR");
      if (s.equals("true")) {
        lighting.set(LL_WARM_ROOM, LM_RED);
      } else
      if (s.equals("false")) {
        lighting.set(LL_WARM_ROOM, LM_OFF);
      }
    #endif

    #if LIGHT_ORW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      s = www.arg("light_ORW");
      if (s.equals("true")) {
        lighting.set(LL_OBSERVING_ROOM, LM_WHITE);
      } else
      if (s.equals("false")) {
        lighting.set(LL_OBSERVING_ROOM, LM_OFF);
      }
    #endif

    #if LIGHT_ORR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      s = www.arg("light_ORR");
      if (s.equals("true")) {
        lighting.set(LL_OBSERVING_ROOM, LM_RED);
      } else
      if (s.equals("false")) {
        lighting.set(LL_OBSERVING_ROOM, LM_OFF);
      }
    #endif

    #if LIGHT_OUTSIDE_RELAY != OFF
      s = www.arg("light_EXIT");
      if (s.equals("true")) { 
        relay.onDelayedOff(LIGHT_OUTSIDE_RELAY, 4*60); // automatically turn off after about 4 minutes
      }
    #endif
  }

#endif
