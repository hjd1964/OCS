// power ---------------------------------------------------------------------------------------------
#include "PowerTile.h"

#if POWER == ON
  #include "htmlHeaders.h"
  #include "htmlScripts.h"
  #include "htmlTabs.h"
  #include "../lib/relay/Relay.h"
  #include "Pages.h"

  void powerTile() {
    char temp[50];
    strcpy_P(temp, htmlPowerBegin);
    sendHtml(temp);

    powerContents();

    strcpy_P(temp, htmlPowerEnd);
    sendHtml(temp);
  }

  void powerContents() {
    char temp[400];

    strcpy_P(temp, htmlPowerA);
    #if POWER_DEVICE1_RELAY != OFF
      if (relay.isOn(POWER_DEVICE1_RELAY)) check(temp, "%___PD1"); else erase(temp, "%___PD1");
    #endif
    #if POWER_DEVICE2_RELAY != OFF
      if (relay.isOn(POWER_DEVICE2_RELAY)) check(temp, "%___PD2"); else erase(temp, "%___PD2");
    #endif
    sendHtml(temp);

    strcpy_P(temp, htmlPowerB);
    #if POWER_DEVICE3_RELAY != OFF
      if (relay.isOn(POWER_DEVICE3_RELAY)) check(temp, "%___PD3"); else erase(temp, "%___PD3");
    #endif
    #if POWER_DEVICE4_RELAY != OFF
      if (relay.isOn(POWER_DEVICE4_RELAY)) check(temp, "%___PD4"); else erase(temp, "%___PD4");
    #endif
    sendHtml(temp);

    strcpy_P(temp, htmlPowerC);
    #if POWER_DEVICE5_RELAY != OFF
      if (relay.isOn(POWER_DEVICE5_RELAY)) check(temp, "%___PD5"); else erase(temp, "%___PD5");
    #endif
    #if POWER_DEVICE6_RELAY != OFF
      if (relay.isOn(POWER_DEVICE6_RELAY)) check(temp, "%___PD6"); else erase(temp, "%___PD6");
    #endif
    sendHtml(temp);
  }

#endif
