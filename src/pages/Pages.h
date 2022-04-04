// -----------------------------------------------------------------------------------
// Display and process data from webpages
#pragma once

#include <Arduino.h>
#include "../Constants.h"
#include "../../Config.h"
#include "../../Extended.config.h"

#include "htmlHeaders.h"

extern void check(char *ss, const char *rs);
extern void erase(char *ss, const char *rs);

extern void index();
extern void indexAjax();

extern void lightContents();
extern void powerContents();
extern void roofContents();
extern void domeContents();
extern void statusContents();
extern void thermostatTemperatureContents();
extern void thermostatHumidityContents();
extern void weatherContents();

extern void relaysAjax();

extern void weatherPage();
extern void skyPage();

extern void handleNotFound();
