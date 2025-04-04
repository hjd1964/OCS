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

    #if LIGHT_WRW_RELAY != OFF || LIGHT_WRR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      www.sendContent("<div class='obsSwLine'>");
      www.sendContent(L_WARM_ROOM_LIGHTS);
      www.sendContent("</div><div class='obsWideSwCtrl'>");
      sprintf_P(temp, htmlLightControl, "wr","off","right","wr","off",L_OFF);
      www.sendContent(temp);
      #if LIGHT_WRR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
        sprintf_P(temp, htmlLightControl, "wr","dr","mid","wr","dr",L_DARK);
        www.sendContent(temp);
        sprintf_P(temp, htmlLightControl, "wr","r",(LIGHT_WRW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF) ? "mid" : "left","wr","r",L_RED);
        www.sendContent(temp);
      #endif
      #if LIGHT_WRW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
        sprintf_P(temp, htmlLightControl, "wr","w","left","wr","w",L_ON);
        www.sendContent(temp);
      #endif
      www.sendContent("</div><br />\n");
    #endif

    #if LIGHT_ORW_RELAY != OFF || LIGHT_ORR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      www.sendContent("<div class='obsSwLine'>");
      www.sendContent(L_OBSERVING_ROOM_LIGHTS);
      www.sendContent("</div><div class='obsWideSwCtrl'>");
      sprintf_P(temp, htmlLightControl, "or","off","right","or","off",L_OFF);
      www.sendContent(temp);
      #if LIGHT_ORR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
        sprintf_P(temp, htmlLightControl, "or","dr","mid","or","dr",L_DARK);
        www.sendContent(temp);
        sprintf_P(temp, htmlLightControl, "or","r",(LIGHT_ORW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF) ? "mid" : "left","or","r",L_RED);
        www.sendContent(temp);
      #endif
      #if LIGHT_ORW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
        sprintf_P(temp, htmlLightControl, "or","w","left","or","w",L_ON);
        www.sendContent(temp);
      #endif
      www.sendContent("</div><br />\n");
    #endif

    strcpy_P(temp, htmlLightingExit);
    www.sendContent(temp);

    strcpy_P(temp,htmlLightingEnd);
    www.sendContent(temp);
  }
  void lightTileAjax() {
    LightMode lightMode;
    UNUSED(lightMode);

    #if LIGHT_WRR_RELAY != OFF || LIGHT_WRW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      lightMode = lighting.get(LL_WARM_ROOM);
      if (lightMode == LM_OFF) www.sendContent("light_wr_off|selected\n"); else www.sendContent("light_wr_off|unselected\n");
      #if LIGHT_WRR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
        if (lightMode == LM_DIM_RED) www.sendContent("light_wr_dr|selected\n"); else www.sendContent("light_wr_dr|unselected\n");
        if (lightMode == LM_RED) www.sendContent("light_wr_r|selected\n"); else www.sendContent("light_wr_r|unselected\n");
      #endif
      #if LIGHT_WRR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
        if (lightMode == LM_WHITE) www.sendContent("light_wr_w|selected\n"); else www.sendContent("light_wr_w|unselected\n");
      #endif
    #endif

    #if LIGHT_ORR_RELAY != OFF || LIGHT_ORW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      lightMode = lighting.get(LL_OBSERVING_ROOM);
      if (lightMode == LM_OFF) www.sendContent("light_or_off|selected\n"); else www.sendContent("light_or_off|unselected\n");
      #if LIGHT_ORR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
        if (lightMode == LM_DIM_RED) www.sendContent("light_or_dr|selected\n"); else www.sendContent("light_or_dr|unselected\n");
        if (lightMode == LM_RED) www.sendContent("light_or_r|selected\n"); else www.sendContent("light_or_r|unselected\n");
      #endif
      #if LIGHT_ORR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
        if (lightMode == LM_WHITE) www.sendContent("light_or_w|selected\n"); else www.sendContent("light_or_w|unselected\n");
      #endif
    #endif
  }

  void lightTileGet() {
    String s;
    UNUSED(s);

    #if LIGHT_WRR_RELAY != OFF || LIGHT_WRW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      s = www.arg("light_wr");
      if (s.equals("off")) {
        lighting.set(LL_WARM_ROOM, LM_OFF);
      } else
      if (s.equals("dr")) {
        lighting.set(LL_WARM_ROOM, LM_DIM_RED);
      } else
      if (s.equals("r")) {
        lighting.set(LL_WARM_ROOM, LM_RED);
      } else
      if (s.equals("w")) {
        lighting.set(LL_WARM_ROOM, LM_WHITE);
      }
    #endif

    #if LIGHT_ORR_RELAY != OFF || LIGHT_ORW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      s = www.arg("light_or");
      if (s.equals("off")) {
        lighting.set(LL_OBSERVING_ROOM, LM_OFF);
      } else
      if (s.equals("dr")) {
        lighting.set(LL_OBSERVING_ROOM, LM_DIM_RED);
      } else
      if (s.equals("r")) {
        lighting.set(LL_OBSERVING_ROOM, LM_RED);
      } else
      if (s.equals("w")) {
        lighting.set(LL_OBSERVING_ROOM, LM_WHITE);
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
