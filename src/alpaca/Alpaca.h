// -----------------------------------------------------------------------------------
// Alpaca process calls
#pragma once

#include <Arduino.h>
#include "../Constants.h"
#include "../../Config.h"
#include "../../Extended.config.h"

#if ASCOM_ALPACA_SERVER == ON

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
extern void alpacaSetupObservingConditions();
extern void alpacaSetupSwitch();

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
extern void alpacaNotFoundError();

// ASCOM Safety Monitor methods
extern void alpacaSafetyMonitorConnected();
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

// ASCOM Switch methods
extern void alpacaSwitchConnected();
extern void alpacaSwitchMaxSwitch();
extern void alpacaSwitchCanWrite();
extern void alpacaSwitchGetSwitch();
extern void alpacaSwitchGetSwitchDescription();
extern void alpacaSwitchGetSwitchName();
extern void alpacaSwitchGetSwitchValue();
extern void alpacaSwitchMaxSwitchValue();
extern void alpacaSwitchMinSwitchValue();
extern void alpacaSwitchSetSwitch();
extern void alpacaSwitchSetSwitchName();
extern void alpacaSwitchSetSwitchValue();
extern void alpacaSwitchSwitchStep();

// ASCOM Dome methods
extern void alpacaDomeConnected();
extern void alpacaDomeAltitude();
extern void alpacaDomeAtHome();
extern void alpacaDomeAtPark();
extern void alpacaDomeAzimuth();
extern void alpacaDomeCanFindHome();
extern void alpacaDomeCanPark();
extern void alpacaDomeCanSetAltitude();
extern void alpacaDomeCanSetAzimuth();
extern void alpacaDomeCanSetPark();
extern void alpacaDomeCanSetShutter();
extern void alpacaDomeCanSlave();
extern void alpacaDomeCanSyncAzimuth();
extern void alpacaDomeShutterStatus();
extern void alpacaDomeSlaved();
extern void alpacaDomeSlewing();
extern void alpacaDomeAbortSlew();
extern void alpacaDomeCloseShutter();
extern void alpacaDomeFindHome();
extern void alpacaDomeOpenShutter();
extern void alpacaDomePark();
extern void alpacaDomeSetPark();
extern void alpacaDomeSlewToAltitude();
extern void alpacaDomeSlewToAzimuth();
extern void alpacaDomeSyncToAzimuth();

#endif
