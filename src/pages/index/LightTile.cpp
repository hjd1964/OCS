// light ----------------------------------------------------------------------
#include "LightTile.h"

#if LIGHT == ON
  #include "../htmlHeaders.h"
  #include "../htmlScripts.h"
  #include "../Pages.h"

  #include "../../libApp/relay/Relay.h"
  #include "../CheckHelp.h"

  void lightTile() {
    char temp[400];
    
    strcpy_P(temp, htmlLightingBeg);
    www.sendContent(temp);

    strcpy_P(temp, htmlLighting1);
    #if LIGHT_WRW_RELAY != OFF
      if (relay.isOn(LIGHT_WRW_RELAY)) check(temp, "%___WRW"); else erase(temp, "%___WRW");
    #endif
    #if LIGHT_WRR_RELAY != OFF
      if (relay.isOn(LIGHT_WRR_RELAY)) check(temp, "%___WRR"); else erase(temp, "%___WRR");
    #endif
    if (strlen(temp) > 0) www.sendContent(temp);

    strcpy_P(temp, htmlLighting2);
    #if LIGHT_ORW_RELAY != OFF
      if (relay.isOn(LIGHT_ORW_RELAY)) check(temp, "%___ORW"); else erase(temp, "%___ORW");
    #endif
    #if LIGHT_ORR_RELAY != OFF
      if (relay.isOn(LIGHT_ORR_RELAY)) check(temp, "%___ORR"); else erase(temp, "%___ORR");
    #endif
    if (strlen(temp) > 0) www.sendContent(temp);

    strcpy_P(temp, htmlLighting3);
    www.sendContent(temp);

    strcpy_P(temp,htmlLightingEnd);
    www.sendContent(temp);
  }

  void lightTileAjax() {
    #if LIGHT_WRW_RELAY != OFF
      www.sendContent("light_WRW|"); www.sendContent(relay.isOn(LIGHT_WRW_RELAY) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if LIGHT_WRR_RELAY != OFF
      www.sendContent("light_WRR|"); www.sendContent(relay.isOn(LIGHT_WRR_RELAY) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if LIGHT_ORW_RELAY != OFF
      www.sendContent("light_ORW|"); www.sendContent(relay.isOn(LIGHT_ORW_RELAY) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if LIGHT_ORR_RELAY != OFF
      www.sendContent("light_ORR|"); www.sendContent(relay.isOn(LIGHT_ORR_RELAY) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
  }

  void lightTileGet() {
    String s;
    UNUSED(s);

    #if LIGHT_WRR_RELAY != OFF
      s = www.arg("light_WRR");
      if (s.equals("true")) {
        relay.on(LIGHT_WRR_RELAY);
      } else
      if (s.equals("false")) {
        relay.off(LIGHT_WRR_RELAY);
      }
    #endif

    #if LIGHT_WRW_RELAY != OFF
      s = www.arg("light_WRW");
      if (s.equals("true")) {
        relay.on(LIGHT_WRW_RELAY);
      } else
      if (s.equals("false")) {
        relay.off(LIGHT_WRW_RELAY);
      }
    #endif

    #if LIGHT_ORW_RELAY != OFF
      s = www.arg("light_ORW");
      if (s.equals("true")) {
        relay.on(LIGHT_ORW_RELAY);
      } else
      if (s.equals("false")) {
        relay.off(LIGHT_ORW_RELAY);
      }
    #endif

    #if LIGHT_ORR_RELAY != OFF
      s = www.arg("light_ORR");
      if (s.equals("true")) {
        relay.on(LIGHT_ORR_RELAY);
      } else
      if (s.equals("false")) {
        relay.off(LIGHT_ORR_RELAY);
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
