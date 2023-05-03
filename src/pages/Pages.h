// -----------------------------------------------------------------------------------
// Display and process data from webpages
#pragma once

#include <Arduino.h>
#include "../Constants.h"
#include "../../Config.h"
#include "../../Extended.config.h"

extern void indexPage();
extern void indexAjax();

extern void lightContents();
extern void powerContents();
extern void roofGet();
extern void domeGet();
extern void statusGet();
extern void thermostatTemperatureGet();
extern void thermostatHumidityGet();
extern void weatherGet();

extern void relaysAjax();

extern void weatherPage();
extern void skyPage();

extern void handleNotFound();
