// -----------------------------------------------------------------------------------
// Alpaca Safety Monitor

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON && defined(WEATHER_PRESENT)

#include <ArduinoJson.h>
#include "Alpaca.h"
#include "../observatory/safety/Safety.h"

extern JsonDocument alpacaJsonDoc;
int32_t safetyMonitorConnected = 0;

void alpacaSafetyMonitorConnected() {
  int exceptionCode = NoException;
  String exceptionValue = "";

  alpacaJsonStart();
  String connected = alpacaArgLowerCase("connected");
  if (!connected.equals(EmptyStr)) {
    if (connected.equals("true")) safetyMonitorConnected++; else
    if (connected.equals("false")) safetyMonitorConnected--; else {
      exceptionCode = InvalidValueException;
      exceptionValue = "Invalid value";
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

#endif
