// -----------------------------------------------------------------------------------
// Alpaca generic functions

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON

#include <ArduinoJson.h>
#include "Alpaca.h"

StaticJsonDocument<1000> alpacaJsonDoc;
uint32_t alpacaServerTransactionID = 0;

// common

// looks up lower case get argument from webserver and returns lower case value string 
String alpacaArgLowerCase(String id) {
  int j = apc.args();
  for (int i = 0; i < j; i++) {
    String name = apc.argName(i);
    name.toLowerCase();
    if (id == name) {
      String value = apc.arg(i);
      value.toLowerCase();
      return value;
    }
  }
  return EmptyStr;
}

// Start for html Json frame
void alpacaJsonStart() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());
  alpacaJsonDoc.clear();
}

// End of html Json frame
void alpacaJsonFinish(int errorNumber, String errorMessage) {
  alpacaJsonDoc["ServerTransactionID"] = alpacaServerTransactionID++;
  String v = alpacaArgLowerCase("ClientTransactionID");
  if (!v.equals(EmptyStr)) { alpacaJsonDoc["ClientTransactionID"] = v.toInt(); }
  alpacaJsonDoc["ErrorNumber"] = errorNumber;
  alpacaJsonDoc["ErrorMessage"] = errorMessage;
  String result;
  serializeJson(alpacaJsonDoc, result);
  apc.sendContent(result);
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
  alpacaJsonDoc["Value"] = "OCS Alpaca Driver for Dome, Observing Conditions, Safety, and Switch version " ALPACA_DRIVER_VERSION;
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
  alpacaJsonFinish(NotImplementedException, "Action Not Implemented");
}

void alpacaDefaultSupportedActions() {
  alpacaJsonStart();
  alpacaJsonDoc.createNestedArray("Value");
  alpacaJsonFinish(NoException, "");
}

#endif
