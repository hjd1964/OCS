// -----------------------------------------------------------------------------------
// Display and process data from webpages
#pragma once

#include <Arduino.h>
#include "../Constants.h"
#include "../../Config.h"
#include "../../Extended.config.h"

extern void indexPage();
extern void indexAjax();
extern void indexAjaxGet();

extern void lightContents();
extern void powerContents();
extern void roofAjax();
extern void domeAjax();
extern void statusAjax();
extern void thermostatTemperatureAjax();
extern void thermostatHumidityAjax();
extern void weatherAjax();

extern void relaysAjaxGet();

extern void weatherPage();
extern void skyPage();

extern void handleNotFound();
