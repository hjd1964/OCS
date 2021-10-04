// light ---------------------------------------------------------------------------------------------------------------------
#include "LightTile.h"

#if LIGHT == ON
  #include "htmlHeaders.h"
  #include "htmlScripts.h"
  #include "htmlTabs.h"

  #include "../lib/relay/Relay.h"
  #include "Pages.h"

  void lightTile() {
    char temp[100];
    
    strcpy_P(temp, htmlLight1);
    sendHtml(temp);

    lightContents();

    strcpy_P(temp,htmlLight3);
    sendHtml(temp);
  }

  void lightContents() {
    char temp[250];

    strcpy_P(temp, htmlLighting1);
    #if LIGHT_WRW_RELAY != OFF
      if (relay.isOn(LIGHT_WRW_RELAY)) check(temp, "%___WRW"); else erase(temp, "%___WRW");
    #endif
    #if LIGHT_WRR_RELAY != OFF
      if (relay.isOn(LIGHT_WRR_RELAY)) check(temp, "%___WRR"); else erase(temp, "%___WRR");
    #endif
    sendHtml(temp);

    strcpy_P(temp, htmlLighting2);
    #if LIGHT_ORW_RELAY != OFF
      if (relay.isOn(LIGHT_ORW_RELAY)) check(temp, "%___ORW"); else erase(temp, "%___ORW");
    #endif
    #if LIGHT_ORR_RELAY != OFF
      if (relay.isOn(LIGHT_ORR_RELAY)) check(temp, "%___ORR"); else erase(temp, "%___ORR");
    #endif
    sendHtml(temp);

    strcpy_P(temp, htmlLighting3);
    sendHtml(temp);
  }

#endif
