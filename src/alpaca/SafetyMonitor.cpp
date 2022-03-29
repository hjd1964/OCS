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

  alpacaJsonStart();
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
  alpacaJsonFinish(exceptionCode, exceptionValue);
}

void alpacaSafetyMonitorIsSafe() {
  alpacaJsonStart();
  if (safetyMonitorConnected > 0) alpacaJsonDoc["Value"] = safety.isSafe(); else alpacaJsonDoc["Value"] = false;
  alpacaJsonFinish(NoException, "");
}
