// light ---------------------------------------------------------------------------------------------------------------------
#include "LightTile.h"

#if LIGHT == ON
  #include "../htmlHeaders.h"
  #include "../htmlScripts.h"
  #include "../Pages.h"

  #include "../../libApp/relay/Relay.h"
  #include "../CheckHelp.h"

  void lightTile() {
    char temp[100];
    
    strcpy_P(temp, htmlLight1);
    www.sendContent(temp);

    lightContents();

    strcpy_P(temp,htmlLight3);
    www.sendContent(temp);
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
  }

#endif
