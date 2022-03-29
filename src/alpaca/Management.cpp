// -----------------------------------------------------------------------------------
// Alpaca management

#include <ArduinoJson.h>

#include "../Common.h"
#include "Alpaca.h"
#include "../observatory/safety/Safety.h"

extern StaticJsonDocument<200> alpacaJsonDoc;

void alpacaManagementApiVersions() {
  alpacaJsonStart();
  JsonArray versions = alpacaJsonDoc.createNestedArray("Value");
  versions.add(1);
  alpacaJsonFinish(NoException, "");
}

void alpacaManagementDescription() {
  alpacaJsonStart();
  JsonObject values = alpacaJsonDoc.createNestedObject("Value");
  values["ServerName"] = "OCS Observatory Control System";
  values["Manufacturer"] = "OnCue";
  values["ManufacturerVersion"] = ocsVersion;
  values["Location"] = "Philadelphia PA, USA";
  alpacaJsonFinish(NoException, "");
}

void alpacaManagementConfiguredDevices() {
  alpacaJsonStart();
  JsonObject values = alpacaJsonDoc.createNestedObject("Value");
  values["DeviceName"] = "OCS Safety";
  values["DeviceType"] = "SafetyMonitor";
  values["DeviceNumber"] = 0;
  values["UniqueID"] = "4ba587e4-3530-45d6-b057-fb2e639b0be9";
  alpacaJsonFinish(NoException, "");
}
