// -----------------------------------------------------------------------------------
// Alpaca generic functions

#include <ArduinoJson.h>

#include "../Common.h"
#include "Alpaca.h"

StaticJsonDocument<200> alpacaJsonDoc;
uint32_t alpacaServerTransactionID = 0;

// common

void alpacaFrame(int errorNumber, String errorMessage) {
  alpacaJsonDoc["ServerTransactionID"] = alpacaServerTransactionID++;
  String v = apc.argLowerCase("ClientTransactionID");
  if (!v.equals(EmptyStr)) { alpacaJsonDoc["ClientTransactionID"] = v.toInt(); }
  alpacaJsonDoc["ErrorNumber"] = errorNumber;
  alpacaJsonDoc["ErrorMessage"] = errorMessage;
}

void alpacaMethodNotImplemented() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());

  alpacaJsonDoc.clear();
  alpacaJsonDoc["Value"] = "";
  alpacaFrame(0, "");
  serializeJson(alpacaJsonDoc, apc.client);

  apc.sendContent("");
}

void alpacaDescription() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());

  alpacaJsonDoc.clear();
  alpacaJsonDoc["Value"] = "ONCUE OCS w/" PINMAP_STR;
  alpacaFrame(0, "");
  serializeJson(alpacaJsonDoc, apc.client);

  apc.sendContent("");
}

void alpacaDriverInfo() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());

  alpacaJsonDoc.clear();
  alpacaJsonDoc["Value"] = "OCS Alpaca Driver for Safety, Dome, Etc. version " ALPACA_DRIVER_VERSION;
  alpacaFrame(0, "");
  serializeJson(alpacaJsonDoc, apc.client);

  apc.sendContent("");
}

void alpacaDriverVersion() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());

  alpacaJsonDoc.clear();
  alpacaJsonDoc["Value"] = ALPACA_DRIVER_VERSION;
  alpacaFrame(0, "");
  serializeJson(alpacaJsonDoc, apc.client);

  apc.sendContent("");
}

void alpacaInterfaceVersion() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());

  alpacaJsonDoc.clear();
  alpacaJsonDoc["Value"] = ALPACA_INTERFACE_VERSION;
  alpacaFrame(0, "");
  serializeJson(alpacaJsonDoc, apc.client);

  apc.sendContent("");
}

void alpacaName() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());

  alpacaJsonDoc.clear();
  alpacaJsonDoc["Value"] = "OCS Alpaca Driver";
  alpacaFrame(0, "");
  serializeJson(alpacaJsonDoc, apc.client);

  apc.sendContent("");
}

// common defaults

void alpacaDefaultAction() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());

  alpacaJsonDoc.clear();
  alpacaJsonDoc["Value"] = "";
  alpacaFrame(ActionNotImplementedException, "Action Not Implemented");
  serializeJson(alpacaJsonDoc, apc.client);

  apc.sendContent("");
}

void alpacaDefaultSupportedActions() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());

  alpacaJsonDoc.clear();
  alpacaJsonDoc.createNestedArray("Value");
  alpacaFrame(0, "");
  serializeJson(alpacaJsonDoc, apc.client);

  apc.sendContent("");
}
