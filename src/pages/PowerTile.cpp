// power ---------------------------------------------------------------------------------------------
#include "PowerTile.h"

#if POWER == ON
  #include "htmlHeaders.h"
  #include "htmlScripts.h"
  #include "htmlTabs.h"
  #include "../lib/relay/Relay.h"

  #if OPERATIONAL_MODE != WIFI
  void powerTile(EthernetClient *client) {
  #else
  void powerTile() {
  #endif
    char temp[800];

    strcpy_P(temp, htmlPower1);
    sendHtml(temp);

    powerContents(client);

    strcpy_P(temp, htmlPower3);
    sendHtml(temp);
  }

  void check(char *ss, const char *rs) {
    char *w = strstr(ss,rs);
    if (w != NULL) { w[0]='c'; w[1]='h'; w[2]='e'; w[3]='c'; w[4]='k'; w[5]='e'; w[6]='d'; }
  }

  void erase(char *ss, const char *rs) {
    char *w = strstr(ss,rs);
    if (w != NULL) { w[0]=' '; w[1]=' '; w[2]=' '; w[3]=' '; w[4]=' '; w[5]=' '; w[6]=' '; }
  }

  #if OPERATIONAL_MODE != WIFI
  void powerContents(EthernetClient *client) {
  #else
  void powerContents() {
  #endif
    char temp[800];

    strcpy_P(temp, htmlPower);
    #if POWER_DEVICE1_RELAY != OFF
      if (relay.isOn(POWER_DEVICE1_RELAY)) check(temp, "%___PD1"); else erase(temp, "%___PD1");
    #endif
    #if POWER_DEVICE2_RELAY != OFF
      if (relay.isOn(POWER_DEVICE2_RELAY)) check(temp, "%___PD2"); else erase(temp, "%___PD2");
    #endif
    #if POWER_DEVICE3_RELAY != OFF
      if (relay.isOn(POWER_DEVICE3_RELAY)) check(temp, "%___PD3"); else erase(temp, "%___PD3");
    #endif
    #if POWER_DEVICE4_RELAY != OFF
      if (relay.isOn(POWER_DEVICE4_RELAY)) check(temp, "%___PD4"); else erase(temp, "%___PD4");
    #endif
    #if POWER_DEVICE5_RELAY != OFF
      if (relay.isOn(POWER_DEVICE5_RELAY)) check(temp, "%___PD5"); else erase(temp, "%___PD5");
    #endif
    #if POWER_DEVICE6_RELAY != OFF
      if (relay.isOn(POWER_DEVICE6_RELAY)) check(temp, "%___PD6"); else erase(temp, "%___PD6");
    #endif
    sendHtml(temp);
  }

#endif
