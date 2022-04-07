// -----------------------------------------------------------------------------------
// Alpaca Switch

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON && (defined(LIGHT_PRESENT) || defined(POWER_PRESENT))

#include <ArduinoJson.h>
#include "Alpaca.h"
#include "../libApp/relay/Relay.h"

extern StaticJsonDocument<200> alpacaJsonDoc;
int32_t switchConnected = 0;
int32_t maxSwitch = 0;
int32_t switchRelay[10];
char switchDescription[10][40];
char switchName[10][40];

void findMaxSwitch() {
  maxSwitch = 0;
  #if POWER_DEVICE1_RELAY != OFF
    switchRelay[maxSwitch] = POWER_DEVICE1_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device1 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE1_NAME);
    maxSwitch++;
  #endif
  #if POWER_DEVICE2_RELAY != OFF
    switchRelay[maxSwitch] = POWER_DEVICE2_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device2 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE2_NAME);
    maxSwitch++;
  #endif
  #if POWER_DEVICE3_RELAY != OFF
    switchRelay[maxSwitch] = POWER_DEVICE3_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device3 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE3_NAME);
    maxSwitch++;
  #endif
  #if POWER_DEVICE4_RELAY != OFF
    switchRelay[maxSwitch] = POWER_DEVICE4_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device4 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE4_NAME);
    maxSwitch++;
  #endif
  #if POWER_DEVICE5_RELAY != OFF
    switchRelay[maxSwitch] = POWER_DEVICE5_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device5 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE5_NAME);
    maxSwitch++;
  #endif
  #if POWER_DEVICE6_RELAY != OFF
    switchRelay[maxSwitch] = POWER_DEVICE6_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device6 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE6_NAME);
    maxSwitch++;
  #endif
  #if LIGHT_WRW_RELAY != OFF
    switchRelay[maxSwitch] = LIGHT_WRW_RELAY;
    strcpy(switchDescription[maxSwitch], "Lights WRW Relay");
    strcpy(switchName[maxSwitch], "Warm Room White Lights");
    maxSwitch++;
  #endif
  #if LIGHT_WRR_RELAY != OFF
    switchRelay[maxSwitch] = LIGHT_WRR_RELAY;
    strcpy(switchDescription[maxSwitch], "Lights WRR Relay");
    strcpy(switchName[maxSwitch], "Warm Room Red Lights");
    maxSwitch++;
  #endif
  #if LIGHT_ORW_RELAY != OFF
    switchRelay[maxSwitch] = LIGHT_ORW_RELAY;
    strcpy(switchDescription[maxSwitch], "Lights ORW Relay");
    strcpy(switchName[maxSwitch], "Observing Room White Lights");
    maxSwitch++;
  #endif
  #if LIGHT_ORR_RELAY != OFF
    switchRelay[maxSwitch] = LIGHT_ORR_RELAY;
    strcpy(switchDescription[maxSwitch], "Lights ORR Relay");
    strcpy(switchName[maxSwitch], "Observing Room Red Lights");
    maxSwitch++;
  #endif
}

void alpacaSwitchConnected() {
  int exceptionCode = NoException;
  String exceptionValue = "";
  findMaxSwitch();

  alpacaJsonStart();
  String connected = apc.argLowerCase("connected");
  if (!connected.equals(EmptyStr)) {
    if (connected.toLowerCase().equals("true")) switchConnected++; else
    if (connected.toLowerCase().equals("false")) switchConnected--; else {
      exceptionCode = InvalidValueException;
      exceptionValue = "Invalid value";
    }
    if (switchConnected < 0) switchConnected = 0;
  } else {
    alpacaJsonDoc["Value"] = switchConnected > 0;
  }
  alpacaJsonFinish(exceptionCode, exceptionValue);
}

void alpacaSwitchMaxSwitch() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  alpacaJsonDoc["Value"] = maxSwitch;
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchCanWrite() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  int id = apc.argLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  alpacaJsonDoc["Value"] = "true";
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchGetSwitch() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  int id = apc.argLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  alpacaJsonDoc["Value"] = relay.isOn(switchRelay[id]) ? "true" : "false";
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchGetSwitchDescription() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  int id = apc.argLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  alpacaJsonDoc["Value"] = switchDescription[id];
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchGetSwitchName() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  int id = apc.argLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  alpacaJsonDoc["Value"] = switchName[id];
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchGetSwitchValue() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  int id = apc.argLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  alpacaJsonDoc["Value"] = relay.isOn(switchRelay[id]) ? 1.0 : 0.0;
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchMaxSwitchValue() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  int id = apc.argLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  alpacaJsonDoc["Value"] = 1.0;
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchMinSwitchValue() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  int id = apc.argLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  alpacaJsonDoc["Value"] = 0.0;
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchSetSwitch() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  int id = apc.argLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  String state = apc.argLowerCase("state").toLowerCase();
  if (state.equals("true")) relay.on(switchRelay[id]); else
    if (state.equals("false")) relay.off(switchRelay[id]); else
      { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchSetSwitchName() {
  alpacaJsonStart();
  alpacaJsonFinish(NotImplementedException, "Not implemented");
}

void alpacaSwitchSetSwitchValue() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  int id = apc.argLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  int32_t value = round(atof(apc.argLowerCase("value").c_str()));
  if (value == 1) relay.on(switchRelay[id]); else
    if (value == 0) relay.off(switchRelay[id]); else
      { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchSwitchStep() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  int id = apc.argLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; }
  alpacaJsonDoc["Value"] = 1.0;
  alpacaJsonFinish(NoException, "");
}

#endif
