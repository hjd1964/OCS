// -----------------------------------------------------------------------------------
// Alpaca management

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON

#include <ArduinoJson.h>
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

  JsonArray devices = alpacaJsonDoc.createNestedArray("Value");
  StaticJsonDocument<200> device;

  device.clear();
  device["DeviceName"] = "OCS Safety Monitor";
  device["DeviceType"] = "SafetyMonitor";
  device["DeviceNumber"] = 0;
  device["UniqueID"] = "4ba587e4-3530-45d6-b057-fb2e639b0be9";
  devices.add(device);

  device.clear();
  device["DeviceName"] = "OCS Observing Conditions";
  device["DeviceType"] = "ObservingConditions";
  device["DeviceNumber"] = 0;
  device["UniqueID"] = "42865d9a-8ea6-4fa7-b371-a90f44481998";
  devices.add(device);

  device.clear();
  device["DeviceName"] = "OCS Switch";
  device["DeviceType"] = "Switch";
  device["DeviceNumber"] = 0;
  device["UniqueID"] = "688e6fe6-b754-4791-a462-63c5ab3b747d";
  devices.add(device);

  #if defined(ROOF_PRESENT) || defined(DOME_PRESENT) 
    device.clear();
    device["DeviceName"] = "OCS Dome";
    device["DeviceType"] = "Dome";
    device["DeviceNumber"] = 0;
    device["UniqueID"] = "ddcf4d81-9095-4a9e-9e88-15e049473124";
    devices.add(device);
  #endif

  alpacaJsonFinish(NoException, "");
}

#endif
