// -----------------------------------------------------------------------------------
// Display and process data from webpages
#pragma once

#include <Arduino.h>
#include "../Constants.h"
#include "../../Config.h"
#include "../../Extended.config.h"

#include "htmlHeaders.h"
#include "../lib/ethernet/webServer/WebServer.h"

void check(char *ss, const char *rs);
void erase(char *ss, const char *rs);

#if OPERATIONAL_MODE == WIFI
  void index();
  void indexAjax();

  void lightContents();
  void powerContents();
  void roofContents();
  void statusContents();
  void thermostatContents();
  void thermostatHumidityContents();
  void weatherContents();

  void relaysAjax();

  void weatherPage();
  void skyPage();

  void handleNotFound();
#else
  void index(EthernetClient *client);
  void indexAjax(EthernetClient *client);

  void lightContents(EthernetClient *client);
  void powerContents(EthernetClient *client);
  void roofContents(EthernetClient *client);
  void statusContents(EthernetClient *client);
  void thermostatContents(EthernetClient *client);
  void thermostatHumidityContents(EthernetClient *client);
  void weatherContents(EthernetClient *client);

  void relaysAjax(EthernetClient *client);

  void weatherPage(EthernetClient *client);
  void skyPage(EthernetClient *client);

  void handleNotFound(EthernetClient *client);
#endif
