// -----------------------------------------------------------------------------------
// Alpaca Safety monitor

#include <ArduinoJson.h>

#include "../Common.h"
#include "Alpaca.h"
#include "../observatory/safety/Safety.h"

extern StaticJsonDocument<200> alpacaJsonDoc;
int32_t safetyMonitorConnected = 0;

void alpacaSafetyMonitorConnected() {
  int exceptionCode = NoException;
  String exceptionValue = "";
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());

  alpacaJsonDoc.clear();
  String connected = apc.argLowerCase("connected");
  if (!connected.equals(EmptyStr)) {
    if (connected.toLowerCase().equals("true")) safetyMonitorConnected++; else
    if (connected.toLowerCase().equals("false")) safetyMonitorConnected--; else {
      exceptionCode = InvalidValueException;
      exceptionValue = "Connected: Invalid value";
    }
    if (safetyMonitorConnected < 0) safetyMonitorConnected = 0;
  } else {
    alpacaJsonDoc["Value"] = safetyMonitorConnected > 0;
  }

  alpacaFrame(exceptionCode, exceptionValue);
  serializeJson(alpacaJsonDoc, apc.client);

  apc.sendContent("");
}

void alpacaSafetyMonitorIsSafe() {
  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "application/json", String());

  alpacaJsonDoc.clear();
  if (safetyMonitorConnected > 0) alpacaJsonDoc["Value"] = safety.isSafe(); else alpacaJsonDoc["Value"] = false;
  alpacaFrame(0, "");
  serializeJson(alpacaJsonDoc, apc.client);

  apc.sendContent("");
}
