// -----------------------------------------------------------------------------------
// Observatory
#include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

#include "Observatory.h"

#include "../lib/tasks/OnTask.h"
#include "../lib/watchdog/Watchdog.h"
#include "../lib/nv/Nv.h"
#include "../lib/sense/Sense.h"
#include "../lib/ethernet/webServer/WebServer.h"
#include "../lib/wifi/webServer/WebServer.h"

#include "../libApp/weatherSensor/WeatherSensor.h"
#include "../libApp/relay/Relay.h"

#include "power/Power.h"
#include "roof/Roof.h"
#include "safety/Safety.h"
#include "thermostat/Thermostat.h"
#include "weather/Weather.h"
#include "dome/Dome.h"

#include "../pages/Pages.h"
#include "../alpaca/Alpaca.h"

#if ASCOM_ALPACA_SERVER == ON
  WebServer apc;
#endif

int timeZone = TIME_ZONE;
time_t startupTime = 0;

#if CONNECT_CHECK_HOURS != OFF
  EthernetClient connectionCheckClient;
#endif

unsigned long msFiveMinuteCounter;
bool xBusy = false;
InitError initError = {false, false, false, false, false};
bool validKey = true;

void observatoryWrapper() { observatory.poll(); }

void Observatory::init(const char *fwName, int fwMajor, int fwMinor, const char *fwPatch, int fwConfig) {
  strcpy(firmware.name, fwName);
  firmware.version.major = fwMajor;
  firmware.version.minor = fwMinor;
  strcpy(firmware.version.patch, fwPatch);
  firmware.version.config = fwConfig;

  // get nv ready
  if (!nv.isKeyValid(INIT_NV_KEY)) {
    VF("MSG: NV, invalid key wipe "); V(nv.size); VLF(" bytes");
    if (nv.verify()) { VLF("MSG: NV, ready for reset to defaults"); }
  } else { VLF("MSG: NV, correct key found"); }

  // disable SPI devices at start up
  if (SDCARD_CS_PIN != OFF) {
    pinMode(SDCARD_CS_PIN, OUTPUT);
    digitalWrite(SDCARD_CS_PIN, HIGH);
  }

  if (ETHERNET_CS_PIN != OFF) {
    pinMode(ETHERNET_CS_PIN, OUTPUT);
    digitalWrite(ETHERNET_CS_PIN, HIGH);
  }

  if (AUX_CS_PIN != OFF) {
    pinMode(AUX_CS_PIN, OUTPUT);
    digitalWrite(AUX_CS_PIN, HIGH);
  }

  // init is done, write the NV key if necessary
  if (!nv.hasValidKey()) {
    nv.writeKey((uint32_t)INIT_NV_KEY);
    nv.wait();
    if (!nv.isKeyValid(INIT_NV_KEY)) { DLF("ERR: NV, failed to read back key!"); } else { VLF("MSG: NV, reset complete"); }
  }

  // senses are added in order and "forced" so all are present even if
  // the pin is OFF; this means the sense handle is the sense number
  if (SENSE1_PIN != OFF) sense.add(SENSE1_PIN, SENSE1_INIT, SENSE1_ON_STATE, true);
  if (SENSE2_PIN != OFF) sense.add(SENSE2_PIN, SENSE2_INIT, SENSE2_ON_STATE, true);
  if (SENSE3_PIN != OFF) sense.add(SENSE3_PIN, SENSE3_INIT, SENSE3_ON_STATE, true);
  if (SENSE4_PIN != OFF) sense.add(SENSE4_PIN, SENSE4_INIT, SENSE4_ON_STATE, true);
  if (SENSE5_PIN != OFF) sense.add(SENSE5_PIN, SENSE5_INIT, SENSE5_ON_STATE, true);
  if (SENSE6_PIN != OFF) sense.add(SENSE6_PIN, SENSE6_INIT, SENSE6_ON_STATE, true);
  if (SENSE7_PIN != OFF) sense.add(SENSE7_PIN, SENSE7_INIT, SENSE7_ON_STATE, true);
  if (SENSE8_PIN != OFF) sense.add(SENSE8_PIN, SENSE8_INIT, SENSE8_ON_STATE, true);

  relay.init();

  // Restore relay state
  #if POWER_DEVICE1_RELAY != OFF && POWER_DEVICE1_MEMORY != OFF
    if (nv.readC(NV_POWER_DEVICE1)) relay.on(POWER_DEVICE1_RELAY);
  #endif
  #if POWER_DEVICE2_RELAY != OFF && POWER_DEVICE2_MEMORY != OFF
    if (nv.readC(NV_POWER_DEVICE2)) relay.on(POWER_DEVICE2_RELAY);
  #endif
  #if POWER_DEVICE3_RELAY != OFF && POWER_DEVICE3_MEMORY != OFF
    if (nv.readC(NV_POWER_DEVICE3)) relay.on(POWER_DEVICE3_RELAY);
  #endif
  #if POWER_DEVICE4_RELAY != OFF && POWER_DEVICE4_MEMORY != OFF
    if (nv.readC(NV_POWER_DEVICE4)) relay.on(POWER_DEVICE4_RELAY);
  #endif
  #if POWER_DEVICE5_RELAY != OFF && POWER_DEVICE5_MEMORY != OFF
    if (nv.readC(NV_POWER_DEVICE5)) relay.on(POWER_DEVICE5_RELAY);
  #endif
  #if POWER_DEVICE6_RELAY != OFF && POWER_DEVICE6_MEMORY != OFF
    if (nv.readC(NV_POWER_DEVICE6)) relay.on(POWER_DEVICE6_RELAY);
  #endif

  #ifdef ROOF_PRESENT
    roof.init();
  #endif

  #ifdef WEATHER_PRESENT
    safety.init();
  #endif

  #ifdef THERMOSTAT_PRESENT
    thermostat.init();
  #endif

  #ifdef WEATHER_PRESENT
    weather.init();
  #endif

  #ifdef DOME_PRESENT
    dome.init();
  #endif

  watchdog.enable(8);

  // bring network servers up
  #if OPERATIONAL_MODE == WIFI
    wifiManager.init();
  #elif OPERATIONAL_MODE >= ETHERNET_FIRST && OPERATIONAL_MODE <= ETHERNET_LAST
    ethernetManager.init();
  #endif

  // ----------------------------------------------------------------------
  // initialize ethernet / wifi

  // Note: Ethernet webserver has the following defaults
  // WEB_HANDLER_COUNT_MAX  16 (changed to 200 for ASCOM Alpaca)
  // PARAMETER_COUNT_MAX    8

  #if WWW_SERVER == ON
    www.on("/index.htm", indexPage);
    www.on("/index-ajax-get.txt", indexAjaxGet);
    www.on("/index.txt", indexAjax);

    #if WEATHER == ON && WEATHER_CHARTS == ON
      www.on("/weatherpage.htm", weatherPage);
      #if WEATHER_SKY_QUAL == ON || WEATHER_CLOUD_CVR == ON
        www.on("/skypage.htm", skyPage);
      #endif
    #endif

    if (strlen(CAMERA_WEBPAGE) > 0) {
      www.on("/camerapage.htm", cameraPage);
    }

    www.on("/", indexPage);

    www.onNotFound(handleNotFound);
    www.begin();
  #endif

  #if ASCOM_ALPACA_SERVER == ON
    apc.on("/setup", alpacaSetup);
    #if defined(WEATHER_PRESENT)
      apc.on("/setup/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/setup", alpacaSetupSafetyMonitor);
      apc.on("/setup/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/setup", alpacaSetupObservingConditions);
    #endif
    #if defined(LIGHT_PRESENT) || defined(POWER_PRESENT)
      apc.on("/setup/v1/switch/" ALPACA_DEVICE_NUMBER "/setup", alpacaSetupSwitch);
    #endif
    #if defined(ROOF_PRESENT) || defined(DOME_PRESENT) 
      apc.on("/setup/v1/dome/" ALPACA_DEVICE_NUMBER "/setup", alpacaSetupDome);
    #endif

    apc.on("/management/apiversions", alpacaManagementApiVersions);
    apc.on("/management/v1/description", alpacaManagementDescription);
    apc.on("/management/v1/configureddevices", alpacaManagementConfiguredDevices);

    #if defined(WEATHER_PRESENT)
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/action", alpacaDefaultAction);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/commandblind", alpacaMethodNotImplemented);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/commandbool", alpacaMethodNotImplemented);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/commandstring", alpacaMethodNotImplemented);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/connected", alpacaSafetyMonitorConnected);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/description", alpacaDescription);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/driverinfo", alpacaDriverInfo);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/driverversion", alpacaDriverVersion);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/interfaceversion", alpacaInterfaceVersion);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/name", alpacaName);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/supportedactions", alpacaDefaultSupportedActions);
      apc.on("/api/v1/safetymonitor/" ALPACA_DEVICE_NUMBER "/issafe", alpacaSafetyMonitorIsSafe);

      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/action", alpacaDefaultAction);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/commandblind", alpacaMethodNotImplemented);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/commandbool", alpacaMethodNotImplemented);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/commandstring", alpacaMethodNotImplemented);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/connected", alpacaObservingConditionsConnected);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/description", alpacaDescription);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/driverinfo", alpacaDriverInfo);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/driverversion", alpacaDriverVersion);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/interfaceversion", alpacaInterfaceVersion);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/name", alpacaName);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/supportedactions", alpacaDefaultSupportedActions);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/averageperiod", alpacaObservingConditionsAveragePeriod);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/cloudcover", alpacaObservingConditionsCloudCover);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/dewpoint", alpacaObservingConditionsDewPoint);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/humidity", alpacaObservingConditionsHumidity);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/pressure", alpacaObservingConditionsPressure);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/rainrate", alpacaObservingConditionsRainRate);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/skybrightness", alpacaObservingConditionsSkyBrightness);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/skyquality", alpacaObservingConditionsSkyQuality);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/skytemperature", alpacaObservingConditionsSkyTemperature);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/starfwhm", alpacaObservingConditionsStarFwhm);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/temperature", alpacaObservingConditionsTemperature);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/winddirection", alpacaObservingConditionsWindDirection);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/windgust", alpacaObservingConditionsWindGust);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/windspeed", alpacaObservingConditionsWindSpeed);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/refresh", alpacaObservingConditionsRefresh);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/sensordescription", alpacaObservingConditionsSensorDescription);
      apc.on("/api/v1/observingconditions/" ALPACA_DEVICE_NUMBER "/timesincelastupdate", alpacaObservingConditionsTimeSinceLastUpdate);
    #endif

    #if defined(LIGHT_PRESENT) || defined(POWER_PRESENT)
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/action", alpacaDefaultAction);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/commandblind", alpacaMethodNotImplemented);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/commandbool", alpacaMethodNotImplemented);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/commandstring", alpacaMethodNotImplemented);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/connected", alpacaSwitchConnected);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/description", alpacaDescription);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/driverinfo", alpacaDriverInfo);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/driverversion", alpacaDriverVersion);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/interfaceversion", alpacaInterfaceVersion);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/name", alpacaName);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/supportedactions", alpacaDefaultSupportedActions);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/maxswitch", alpacaSwitchMaxSwitch);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/canwrite", alpacaSwitchCanWrite);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/getswitch", alpacaSwitchGetSwitch);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/getswitchdescription", alpacaSwitchGetSwitchDescription);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/getswitchname", alpacaSwitchGetSwitchName);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/getswitchvalue", alpacaSwitchGetSwitchValue);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/maxswitchvalue", alpacaSwitchMaxSwitchValue);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/minswitchvalue", alpacaSwitchMinSwitchValue);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/setswitch", alpacaSwitchSetSwitch);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/setswitchname", alpacaSwitchSetSwitchName);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/setswitchvalue", alpacaSwitchSetSwitchValue);
      apc.on("/api/v1/switch/" ALPACA_DEVICE_NUMBER "/switchstep", alpacaSwitchSwitchStep);
    #endif

    #if defined(ROOF_PRESENT) || defined(DOME_PRESENT) 
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/action", alpacaDefaultAction);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/commandblind", alpacaMethodNotImplemented);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/commandbool", alpacaMethodNotImplemented);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/commandstring", alpacaMethodNotImplemented);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/connected", alpacaDomeConnected);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/description", alpacaDescription);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/driverinfo", alpacaDriverInfo);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/driverversion", alpacaDriverVersion);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/interfaceversion", alpacaInterfaceVersion);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/name", alpacaName);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/supportedactions", alpacaDefaultSupportedActions);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/altitude", alpacaDomeAltitude);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/athome", alpacaDomeAtHome);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/atpark", alpacaDomeAtPark);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/azimuth", alpacaDomeAzimuth);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/canfindhome", alpacaDomeCanFindHome);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/canpark", alpacaDomeCanPark);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/cansetaltitude", alpacaDomeCanSetAltitude);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/cansetazimuth", alpacaDomeCanSetAzimuth);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/cansetpark", alpacaDomeCanSetPark);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/cansetshutter", alpacaDomeCanSetShutter);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/canslave", alpacaDomeCanSlave);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/cansyncazimuth", alpacaDomeCanSyncAzimuth);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/shutterstatus", alpacaDomeShutterStatus);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/slaved", alpacaDomeSlaved);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/slewing", alpacaDomeSlewing);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/abortslew", alpacaDomeAbortSlew);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/closeshutter", alpacaDomeCloseShutter);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/findhome", alpacaDomeFindHome);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/openshutter", alpacaDomeOpenShutter);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/park", alpacaDomePark);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/setpark", alpacaDomeSetPark);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/slewtoaltitude", alpacaDomeSlewToAltitude);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/slewtoazimuth", alpacaDomeSlewToAzimuth);
      apc.on("/api/v1/dome/" ALPACA_DEVICE_NUMBER "/synctoazimuth", alpacaDomeSyncToAzimuth);
    #endif

    apc.onNotFound(alpacaNotFoundError);
    apc.begin(ALPACA_PORT);
  #endif

  #if TIME_LOCATION_SOURCE != OFF
    // get time ready
    #if TIME_LOCATION_SOURCE == DS3231
      tls = new TlsDs3231;
    #elif TIME_LOCATION_SOURCE == DS3234
      tls = new TlsDs3234;
    #elif TIME_LOCATION_SOURCE == NTP
      tls = new TlsNTP;
    #elif TIME_LOCATION_SOURCE == SD3031
      tls = new TlsSd3031;
    #elif TIME_LOCATION_SOURCE == TEENSY
      tls = new TlsTeensy;
    #endif

    tls->init();
    #if TIME_LOCATION_SOURCE != NTP
      startupTime = now();
    #endif
  #endif

  // start observatory monitor task
  VF("MSG: Observatory, start monitor task (rate 200ms priority 4)... ");
  if (tasks.add(200, 0, true, 4, observatoryWrapper, "Obsrvty")) { VLF("success"); } else { VLF("FAILED!"); }
}

void Observatory::connectionCheck() {
  #if CONNECT_CHECK_HOURS != OFF
    static int connectionCheckTry = 0;
    static unsigned long nextConnectionCheck = 1000UL*3600UL*(CONNECT_CHECK_HOURS/CHECK_FAST);
    if ((long)(millis() - nextConnectionCheck) > 0) {
      connectionCheckTry++;

      int success = connectionCheckClient.connect(connectCheckIP, 80);

      if (success) {
        VLF("MSG: Observatory, connection check success");
        connectionCheckClient.stop();
        connectionCheckTry = 0;
        nextConnectionCheck = millis() + (1000UL*3600UL*(CONNECT_CHECK_HOURS/CHECK_FAST));
      } else {
        DLF("MSG: Observatory, connection check FAILED!");
        nextConnectionCheck = millis() + (1000UL*CONNECT_RECHECK_TIME);
      }

    #if WATCHDOG == ON && CONNECT_FAIL_WATCHDOG == ON
      if (!success &&
        #ifdef ROOF_PRESENT
          !roof.isMoving() &&
        #endif
        #ifdef DOME_PRESENT
          !dome.isSlewing() &&
        #endif
        connectionCheckTry >= CONNECT_REBOOT_TRIES) {
        DLF("MSG: Observatory, forcing watchdog reboot!");
        while (true) {};
      }
    #endif

    #if ETHERNET_RESET_PIN != OFF
      if (!success && connectionCheckTry == CONNECT_RESET_TRIES) {

        ethernetManager.restart();

        #if STANDARD_COMMAND_CHANNEL == ON
          ipSerial.restart();
        #endif

        #if PERSISTENT_COMMAND_CHANNEL == ON
          pipSerial.restart();
        #endif

        #if TIME_LOCATION_SOURCE == NTP
          tls->restart();
        #endif

        #if CONNECT_FAIL_WATCHDOG == OFF
          connectionCheckTry = 0;
        #endif
      }
    #endif
    }
  #endif
}

void Observatory::poll() {

  connectionCheck();

  #if OPERATIONAL_MODE != OFF && TIME_LOCATION_SOURCE == NTP
    // double check time if it looks like it's not set go back and ask for it again every 10 minutes
    if (now() < 365L*24L*60L*60L) {
      if (!fastNTPSync) { setSyncInterval(10L*60L); fastNTPSync = true; }
    } else {
      if (startupTime == 0) startupTime = now();
      if (fastNTPSync) { setSyncInterval(24L*60L*60L); fastNTPSync = false; }
    }
  #endif

  // handle WiFi/Ethernet servers
  #if WWW_SERVER == ON
    www.handleClient();
  #endif

  #if ASCOM_ALPACA_SERVER == ON
    apc.handleClient();
  #endif

  // a wall switch can control lights
  #if LIGHT_SW_SENSE != OFF && LIGHT_WRW_RELAY != OFF
    if (sense.changed(LIGHT_SW_SENSE)) {
      if (sense.isOn(LIGHT_SW_SENSE)) relay.on(LIGHT_WRW_RELAY); else relay.off(LIGHT_WRW_RELAY);
    }
  #endif

  // keep DHCP alive if used
  #if OPERATIONAL_MODE >= ETHERNET_FIRST && OPERATIONAL_MODE <= ETHERNET_LAST
    if (ethernetManager.settings.dhcpEnabled) Ethernet.maintain();
  #endif
}

Observatory observatory;
