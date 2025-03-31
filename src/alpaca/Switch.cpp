// -----------------------------------------------------------------------------------
// Alpaca Switch

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON && (defined(LIGHT_PRESENT) || defined(POWER_PRESENT))

#include <ArduinoJson.h>
#include "Alpaca.h"
#include "../libApp/relay/Relay.h"
#include "../observatory/lighting/Lighting.h"

#define LightWRW -1
#define LightWRR -2
#define LightORW -3
#define LightORR -4

extern JsonDocument alpacaJsonDoc;
int32_t switchConnected = 0;
int32_t maxSwitch = 0;
int32_t switchIdentifier[10];
char switchDescription[10][40];
char switchName[10][40];

void findMaxSwitch() {
  maxSwitch = 0;
  #if POWER_DEVICE1_RELAY != OFF
    switchIdentifier[maxSwitch] = POWER_DEVICE1_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device1 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE1_NAME);
    maxSwitch++;
  #endif
  #if POWER_DEVICE2_RELAY != OFF
    switchIdentifier[maxSwitch] = POWER_DEVICE2_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device2 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE2_NAME);
    maxSwitch++;
  #endif
  #if POWER_DEVICE3_RELAY != OFF
    switchIdentifier[maxSwitch] = POWER_DEVICE3_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device3 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE3_NAME);
    maxSwitch++;
  #endif
  #if POWER_DEVICE4_RELAY != OFF
    switchIdentifier[maxSwitch] = POWER_DEVICE4_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device4 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE4_NAME);
    maxSwitch++;
  #endif
  #if POWER_DEVICE5_RELAY != OFF
    switchIdentifier[maxSwitch] = POWER_DEVICE5_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device5 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE5_NAME);
    maxSwitch++;
  #endif
  #if POWER_DEVICE6_RELAY != OFF
    switchIdentifier[maxSwitch] = POWER_DEVICE6_RELAY;
    strcpy(switchDescription[maxSwitch], "Power Device6 Relay");
    strcpy(switchName[maxSwitch], POWER_DEVICE6_NAME);
    maxSwitch++;
  #endif
  #if LIGHT_WRW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
    switchIdentifier[maxSwitch] = LightWRW;
    strcpy(switchDescription[maxSwitch], "Lights WRW");
    strcpy(switchName[maxSwitch], "Warm Room White Lights");
    maxSwitch++;
  #endif
  #if LIGHT_WRR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
    switchIdentifier[maxSwitch] = LightWRR;
    strcpy(switchDescription[maxSwitch], "Lights WRR");
    strcpy(switchName[maxSwitch], "Warm Room Red Lights");
    maxSwitch++;
  #endif
  #if LIGHT_ORW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
    switchIdentifier[maxSwitch] = LightORW;
    strcpy(switchDescription[maxSwitch], "Lights ORW");
    strcpy(switchName[maxSwitch], "Observing Room White Lights");
    maxSwitch++;
  #endif
  #if LIGHT_ORR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
    switchIdentifier[maxSwitch] = LightORR;
    strcpy(switchDescription[maxSwitch], "Lights ORR");
    strcpy(switchName[maxSwitch], "Observing Room Red Lights");
    maxSwitch++;
  #endif
}

void alpacaSwitchConnected() {
  int exceptionCode = NoException;
  String exceptionValue = "";
  findMaxSwitch();

  alpacaJsonStart();
  String connected = alpacaArgLowerCase("connected");
  if (!connected.equals(EmptyStr)) {
    if (connected.equals("true")) switchConnected++; else
    if (connected.equals("false")) switchConnected--; else {
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
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  alpacaJsonDoc["Value"] = maxSwitch;
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchCanWrite() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  int id = alpacaArgLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; }
  alpacaJsonDoc["Value"] = true;
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchGetSwitch() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  int id = alpacaArgLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; }
  #ifdef LIGHT_PRESENT
    if (switchIdentifier[id] == LightWRW) alpacaJsonDoc["Value"] = (lighting.get(LL_WARM_ROOM) == LM_WHITE) ? true : false; else
    if (switchIdentifier[id] == LightWRR) alpacaJsonDoc["Value"] = (lighting.get(LL_WARM_ROOM) == LM_RED) ? true : false; else
    if (switchIdentifier[id] == LightORW) alpacaJsonDoc["Value"] = (lighting.get(LL_OBSERVING_ROOM) == LM_WHITE) ? true : false; else
    if (switchIdentifier[id] == LightORR) alpacaJsonDoc["Value"] = (lighting.get(LL_OBSERVING_ROOM) == LM_RED) ? true : false; else
  #endif
  alpacaJsonDoc["Value"] = relay.isOn(switchIdentifier[id]) ? true : false;
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchGetSwitchDescription() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  int id = alpacaArgLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; }
  alpacaJsonDoc["Value"] = switchDescription[id];
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchGetSwitchName() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  int id = alpacaArgLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; }
  alpacaJsonDoc["Value"] = switchName[id];
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchGetSwitchValue() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  int id = alpacaArgLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; }
  #ifdef LIGHT_PRESENT
    if (switchIdentifier[id] == LightWRW) alpacaJsonDoc["Value"] = lighting.get(LL_WARM_ROOM) == LM_WHITE ? 1.0 : 0.0; else
    if (switchIdentifier[id] == LightWRR) alpacaJsonDoc["Value"] = lighting.get(LL_WARM_ROOM) == LM_RED ? 1.0 : 0.0; else
    if (switchIdentifier[id] == LightORW) alpacaJsonDoc["Value"] = lighting.get(LL_OBSERVING_ROOM) == LM_WHITE ? 1.0 : 0.0; else
    if (switchIdentifier[id] == LightORR) alpacaJsonDoc["Value"] = lighting.get(LL_OBSERVING_ROOM) == LM_RED ? 1.0 : 0.0; else
  #endif
  alpacaJsonDoc["Value"] = relay.isOn(switchIdentifier[id]) ? 1.0 : 0.0;
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchMaxSwitchValue() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  int id = alpacaArgLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; }
  alpacaJsonDoc["Value"] = 1.0;
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchMinSwitchValue() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  int id = alpacaArgLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; }
  alpacaJsonDoc["Value"] = 0.0;
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchSetSwitch() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  int id = alpacaArgLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; }
  String state = alpacaArgLowerCase("state");
  if (state.equals("true")) {
    #ifdef LIGHT_PRESENT
      if (switchIdentifier[id] == LightWRW) lighting.set(LL_WARM_ROOM, LM_WHITE); else
      if (switchIdentifier[id] == LightWRR) lighting.set(LL_WARM_ROOM, LM_RED); else
      if (switchIdentifier[id] == LightORW) lighting.set(LL_OBSERVING_ROOM, LM_WHITE); else
      if (switchIdentifier[id] == LightORR) lighting.set(LL_OBSERVING_ROOM, LM_RED); else
    #endif
    relay.on(switchIdentifier[id]);
  } else
  if (state.equals("false")) {
    #ifdef LIGHT_PRESENT
      if (switchIdentifier[id] == LightWRW || switchIdentifier[id] == LightWRR) lighting.set(LL_WARM_ROOM, LM_OFF); else
      if (switchIdentifier[id] == LightORW || switchIdentifier[id] == LightORR) lighting.set(LL_OBSERVING_ROOM, LM_OFF); else
    #endif
    relay.off(switchIdentifier[id]);
  } else {
    alpacaJsonFinish(InvalidValueException, InvalidValueMessage);
    return;
  }
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchSetSwitchName() {
  alpacaJsonStart();
  alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
}

void alpacaSwitchSetSwitchValue() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  int id = alpacaArgLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; }
  int32_t value = round(atof(alpacaArgLowerCase("value").c_str()));
  if (value == 1) {
    #ifdef LIGHT_PRESENT
      if (switchIdentifier[id] == LightWRW) lighting.set(LL_WARM_ROOM, LM_WHITE); else
      if (switchIdentifier[id] == LightWRR) lighting.set(LL_WARM_ROOM, LM_RED); else
      if (switchIdentifier[id] == LightORW) lighting.set(LL_OBSERVING_ROOM, LM_WHITE); else
      if (switchIdentifier[id] == LightORR) lighting.set(LL_OBSERVING_ROOM, LM_RED); else
    #endif
    relay.on(switchIdentifier[id]);
  } else
  if (value == 0) {
    #ifdef LIGHT_PRESENT
      if (switchIdentifier[id] == LightWRW || switchIdentifier[id] == LightWRR) lighting.set(LL_WARM_ROOM, LM_OFF); else
      if (switchIdentifier[id] == LightORW || switchIdentifier[id] == LightORR) lighting.set(LL_OBSERVING_ROOM, LM_OFF); else
    #endif
    relay.off(switchIdentifier[id]);
  } else {
    alpacaJsonFinish(InvalidValueException, InvalidValueMessage);
    return;
  }
  alpacaJsonFinish(NoException, "");
}

void alpacaSwitchSwitchStep() {
  alpacaJsonStart();
  if (!switchConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  int id = alpacaArgLowerCase("id").toInt();
  if (id < 0 || id >= maxSwitch) { alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; }
  alpacaJsonDoc["Value"] = 1.0;
  alpacaJsonFinish(NoException, "");
}

#endif
