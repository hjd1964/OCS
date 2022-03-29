// -----------------------------------------------------------------------------------
// Alpaca process calls
#pragma once

#include <Arduino.h>
#include "../Constants.h"
#include "../../Config.h"
#include "../../Extended.config.h"
#include "../lib/ethernet/webServer/WebServer.h"

extern WebServer apc;
extern uint32_t alpacaServerTransactionID;

// unique identifiers for this OCS
#define ALPACA_DRIVER_VERSION         "1.0"
#define ALPACA_INTERFACE_VERSION      1
#define ALPACA_PORT                   10000
#define ALPACA_DEVICE_NUMBER          "0"

// ASCOM exceptions
#define NoException                   0x000
#define InvalidOperationException     0x40B
#define InvalidValueException         0x401
#define NotConnectedException         0x400
#define NotImplementedException       0x400
#define ParkedException               0x408
#define SlavedException               0x409
#define ValueNotSetException          0x402

// setup
extern void alpacaSetup();
extern void alpacaSetupSafetyMonitor();

// management
extern void alpacaManagementApiVersions();
extern void alpacaManagementDescription();
extern void alpacaManagementConfiguredDevices();

// common
extern void alpacaJsonStart();
extern void alpacaJsonFinish(int errorNumber, String errorMessage);
extern void alpacaMethodNotImplemented();
extern void alpacaDescription();
extern void alpacaDriverInfo();
extern void alpacaDriverVersion();
extern void alpacaInterfaceVersion();
extern void alpacaName();

// common defaults
extern void alpacaDefaultAction();
extern void alpacaDefaultSupportedActions();

// error handling
extern void handleRequestFailed();
extern void alpacaServerError();

// ASCOM Safety Monitor methods
extern void alpacaSafetyMonitorConnected();
extern void alpacaNotFoundError();
extern void alpacaSafetyMonitorIsSafe();

// ASCOM Observing Conditions methods
extern void alpacaObservingConditionsConnected();
extern void alpacaObservingConditionsAveragePeriod();
extern void alpacaObservingConditionsCloudCover();
extern void alpacaObservingConditionsDewPoint();
extern void alpacaObservingConditionsHumidity();
extern void alpacaObservingConditionsPressure();
extern void alpacaObservingConditionsRainRate();
extern void alpacaObservingConditionsSkyBrightness();
extern void alpacaObservingConditionsSkyQuality();
extern void alpacaObservingConditionsSkyTemperature();
extern void alpacaObservingConditionsStarFwhm();
extern void alpacaObservingConditionsTemperature();
extern void alpacaObservingConditionsWindDirection();
extern void alpacaObservingConditionsWindGust();
extern void alpacaObservingConditionsWindSpeed();
extern void alpacaObservingConditionsRefresh();
extern void alpacaObservingConditionsSensorDescription();
extern void alpacaObservingConditionsTimeSinceLastUpdate();
