// light ---------------------------------------------------------------------------------------------------------------------
#include "LightTile.h"

#if LIGHT == ON
  #include "htmlHeaders.h"
  #include "htmlScripts.h"
  #include "htmlTabs.h"
  #include "../lib/relay/Relay.h"
  #include "Pages.h"

  #if OPERATIONAL_MODE != WIFI
  void lightTile(EthernetClient *client) {
  #else
  void lightTile() {
  #endif
    char temp[100];
    
    strcpy_P(temp, htmlLight1);
    sendHtml(temp);

    lightContents(client);

    strcpy_P(temp,htmlLight3);
    sendHtml(temp);
  }

  #if OPERATIONAL_MODE != WIFI
  void lightContents(EthernetClient *client) {
  #else
  void lightContents() {
  #endif
    char temp[600];
    
    strcpy_P(temp, htmlLighting);
    #if LIGHT_WRW_RELAY != OFF
      if (relay.isOn(LIGHT_WRW_RELAY)) check(temp, "%___WRW"); else erase(temp, "%___WRW");
    #endif
    #if LIGHT_WRR_RELAY != OFF
      if (relay.isOn(LIGHT_WRR_RELAY)) check(temp, "%___WRR"); else erase(temp, "%___WRR");
    #endif
    #if LIGHT_ORW_RELAY != OFF
      if (relay.isOn(LIGHT_ORW_RELAY)) check(temp, "%___ORW"); else erase(temp, "%___ORW");
    #endif
    #if LIGHT_ORR_RELAY != OFF
      if (relay.isOn(LIGHT_ORR_RELAY)) check(temp, "%___ORR"); else erase(temp, "%___ORR");
    #endif
    sendHtml(temp);
  }

#endif
