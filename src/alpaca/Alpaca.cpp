// -----------------------------------------------------------------------------------
// Alpaca generic functions

#include <ArduinoJson.h>

#include "../Common.h"
#include "Alpaca.h"

StaticJsonDocument<200> alpacaJsonDoc;
uint32_t alpacaServerTransactionID = 0;

// common

// Start for html Json frame
void alpacaJsonStart() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());
  alpacaJsonDoc.clear();
}

// End of html Json frame
void alpacaJsonFinish(int errorNumber, String errorMessage) {
  alpacaJsonDoc["ServerTransactionID"] = alpacaServerTransactionID++;
  String v = apc.argLowerCase("ClientTransactionID");
  if (!v.equals(EmptyStr)) { alpacaJsonDoc["ClientTransactionID"] = v.toInt(); }
  alpacaJsonDoc["ErrorNumber"] = errorNumber;
  alpacaJsonDoc["ErrorMessage"] = errorMessage;
  serializeJson(alpacaJsonDoc, apc.client);
  apc.sendContent("");
}

void alpacaMethodNotImplemented() {
  alpacaJsonStart();
  alpacaJsonDoc["Value"] = "";
  alpacaJsonFinish(NoException, "");
}

void alpacaDescription() {
  alpacaJsonStart();
  alpacaJsonDoc["Value"] = "ONCUE OCS w/" PINMAP_STR;
  alpacaJsonFinish(NoException, "");
}

void alpacaDriverInfo() {
  alpacaJsonStart();
  alpacaJsonDoc["Value"] = "OCS Alpaca Driver for Safety, Dome, Etc. version " ALPACA_DRIVER_VERSION;
  alpacaJsonFinish(NoException, "");
}

void alpacaDriverVersion() {
  alpacaJsonStart();
  alpacaJsonDoc["Value"] = ALPACA_DRIVER_VERSION;
  alpacaJsonFinish(NoException, "");
}

void alpacaInterfaceVersion() {
  alpacaJsonStart();
  alpacaJsonDoc["Value"] = ALPACA_INTERFACE_VERSION;
  alpacaJsonFinish(NoException, "");
}

void alpacaName() {
  alpacaJsonStart();
  alpacaJsonDoc["Value"] = "OCS Alpaca Driver";
  alpacaJsonFinish(NoException, "");
}

// common defaults

void alpacaDefaultAction() {
  alpacaJsonStart();
  alpacaJsonDoc["Value"] = "";
  alpacaJsonFinish(ActionNotImplementedException, "Action Not Implemented");
}

void alpacaDefaultSupportedActions() {
  alpacaJsonStart();
  alpacaJsonDoc.createNestedArray("Value");
  alpacaJsonFinish(NoException, "");
}
