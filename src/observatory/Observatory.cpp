// -----------------------------------------------------------------------------------
// Observatory
#include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

#include "../Common.h"
#include "../tasks/OnTask.h"

#include "../lib/ethernet/Ethernet.h"
#include "../lib/ethernet/webServer/WebServer.h"
#include "../lib/weatherSensor/WeatherSensor.h"
#include "../lib/relay/Relay.h"
#include "../lib/sense/Sense.h"

#include "power/Power.h"
#include "roof/Roof.h"
#include "safety/Safety.h"
#include "thermostat/Thermostat.h"
#include "weather/Weather.h"

#include "../pages/Pages.h"

#include "Observatory.h"

int timeZone = TIME_ZONE;
time_t startupTime = 0;

#if CONNECTION_CHECK_HOURS != OFF
  EthernetClient client;
#endif

unsigned long msFiveMinuteCounter;
bool validKey = true;

void observatoryWrapper() { observatory.poll(); }

void Observatory::init(const char *fwName, int fwMajor, int fwMinor, const char *fwPatch, int fwConfig) {
  strcpy(firmware.name, fwName);
  firmware.version.major = fwMajor;
  firmware.version.minor = fwMinor;
  strcpy(firmware.version.patch, fwPatch);
  firmware.version.config = fwConfig;
  strcpy(firmware.date, __DATE__);
  strcpy(firmware.time, __TIME__);

  if (nv.readUL(NV_KEY) != INIT_NV_KEY) {
    validKey = false;

    VF("MSG: Observatory Wipe NV "); V(nv.size); VLF(" Bytes");
    for (int i = 0; i < (int)nv.size; i++) nv.write(i, (char)0);
    VLF("MSG: Observatory, Wipe NV waiting for commit");
    while (!nv.committed()) { nv.poll(false); delay(10); }

    VLF("MSG: Observatory, NV reset to defaults");
  } else { VLF("MSG: Observatory, correct NV key found"); }

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

  if (!validKey) {
    while (!nv.committed()) nv.poll();
    nv.write(NV_KEY, (uint32_t)INIT_NV_KEY);
    while (!nv.committed()) { nv.poll(); delay(10); }
    nv.ignoreCache(true);
    uint32_t key = nv.readUL(NV_KEY);
    if (key != (uint32_t)INIT_NV_KEY) { DLF("ERR: Observatory, NV reset failed to read back key!"); } else { VLF("MSG: Observatory, NV reset complete"); }
    nv.ignoreCache(false);
  }

  relay.init();

  // senses are added in order and "forced" so all are present even if
  // the pin is OFF; this means the sense handle is the sense number
  if (SENSE1_PIN != OFF) sense.add(SENSE1_PIN, SENSE1_INIT_STATE, SENSE1_ON_STATE, true);
  if (SENSE2_PIN != OFF) sense.add(SENSE2_PIN, SENSE2_INIT_STATE, SENSE2_ON_STATE, true);
  if (SENSE3_PIN != OFF) sense.add(SENSE3_PIN, SENSE3_INIT_STATE, SENSE3_ON_STATE, true);
  if (SENSE4_PIN != OFF) sense.add(SENSE4_PIN, SENSE4_INIT_STATE, SENSE4_ON_STATE, true);
  if (SENSE5_PIN != OFF) sense.add(SENSE5_PIN, SENSE5_INIT_STATE, SENSE5_ON_STATE, true);
  if (SENSE6_PIN != OFF) sense.add(SENSE6_PIN, SENSE6_INIT_STATE, SENSE6_ON_STATE, true);
  if (SENSE7_PIN != OFF) sense.add(SENSE7_PIN, SENSE7_INIT_STATE, SENSE7_ON_STATE, true);
  if (SENSE8_PIN != OFF) sense.add(SENSE8_PIN, SENSE8_INIT_STATE, SENSE8_ON_STATE, true);

  #if ROOF == ON
    roof.init();
  #endif

  safety.init();

  #if THERMOSTAT == ON
    thermostat.init();
  #endif

  #if WEATHER == ON
    weather.init();
  #endif

  WDT_ENABLE;

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

  // ----------------------------------------------------------------------
  // initialize ethernet

  #if ETHERNET_RESET_PIN != OFF
    // hold ethernet shield in reset for 2 seconds
    pinMode(ETHERNET_RESET_PIN, OUTPUT);
    digitalWrite(ETHERNET_RESET_PIN, LOW);
    tasks.yeild(2000);
    digitalWrite(ETHERNET_RESET_PIN, HIGH);
  #endif

  www.init();
  www.setResponseHeader(http_defaultHeader);

  www.on("index.htm", index);
  #if FAV_ICON == ON
    www.on("favicon.ico");
  #endif
  #if WEATHER == ON && WEATHER_CHARTS == ON
    www.on("weatherpage.htm", weatherPage);
  #if WEATHER_SKY_QUAL == ON || WEATHER_CLOUD_CVR == ON
    www.on("skypage.htm", skyPage);
  #endif
  #endif
  www.on("setvar", indexAjax);
  www.on("relay", relaysAjax);
  www.on("miscstatus", statusContents);
  #if WEATHER == ON
    www.on("weather", weatherContents);
  #endif
  #if THERMOSTAT == ON
    www.on("thermostat", thermostatContents);
    #if THERMOSTAT_HUMIDITY == ON
      www.on("thermostath", thermostath);
    #endif
  #endif
  #if ROOF == ON
    www.on("roofstatus", roofContents);
  #endif
  #if WEATHER_CHARTS == ON
    www.on("Chart.js", NULL);
  #endif
  www.on("/", index);

  // start observatory monitor task
  VF("MSG: Setup, start observatory monitor task (rate 1ms priority 4)... ");
  if (tasks.add(1, 0, true, 4, observatoryWrapper, "ObsPoll")) { VL("success"); } else { VL("FAILED!"); }
}

void Observatory::connectionCheck() {
  #if CONNECTION_CHECK_HOURS != OFF
    static int connectionCheckTry = 0;
    static unsigned long nextConnectionCheck = 1000UL*3600UL*(CONNECTION_CHECK_HOURS/CHECK_FAST);
    if ((long)(millis() - nextConnectionCheck) > 0) {
      connectionCheckTry++;
      int success=client.connect(connectCheck, 80);

      if (success) {
        VLF("MSG: Connection Check Success");
        client.stop();
        connectionCheckTry = 0;
        nextConnectionCheck = millis() + (1000UL*3600UL*(CONNECTION_CHECK_HOURS/CHECK_FAST));
      } else {
        VLF("MSG: Connection Check FAILED!");
        nextConnectionCheck = millis() + (1000UL*CONNECT_RECHECK_TIME);
      }

    #if WATCHDOG == ON_CC
      if (!success && !roofIsMoving() && connectionCheckTry >= CONNECT_REBOOT_TRIES) {
        VLF("MSG: Forcing Watchdog Reboot");
        while (true) {};
      }
    #endif

    #if ETHERNET_RESET_PIN != OFF
      if (!success && connectionCheckTry == CONNECT_RESET_TRIES) {
        VLF("MSG: Reset Ethernet shield");
        // reset ethernet shield
        digitalWrite(ETHERNET_RESET_PIN, LOW);
        tasks.yield(2000);
        digitalWrite(ETHERNET_RESET_PIN, HIGH);
        tasks.yield(2000);
        // restart servers
        Ethernet.begin(m, ip, myDns, gateway, subnet);
        Cmd.init(9999,500);
      #if TIME_LOCATION_SOURCE == NTP
        Udp.begin(localPort);
      #endif
      #if WATCHDOG != ON_CC
        connectionCheckTry = 0;
      #endif
      }
    #endif
    }
  #endif
}

void Observatory::poll() {
  connectionCheck();

  #if TIME_LOCATION_SOURCE == NTP
    // double check time if it looks like it's not set go back and ask for it again every 10 minutes
    if (now() < 365UL*24UL*60UL*60UL) {
      if (!fastNTPSync) { setSyncInterval(10L*60L); fastNTPSync = true; }
    } else {
      if (startupTime == 0) startupTime = now();
      if (fastNTPSync) { setSyncInterval(24L*60L*60L); fastNTPSync = false; }
    }
  #endif

  // ------------------------------------------------------------------------------------------
  // Handle comms

  // serve web-pages
  www.handleClient();

  // process commands
  //processCommands();

  // a wall switch can control lights
  #if LIGHT_SW_SENSE == ON && LIGHT_WRW_RELAY != OFF
    if (sense.changed(LIGHT_SW_SENSE)) {
      if (sense.isOn(LIGHT_SW_SENSE)) relay.on(LIGHT_WRW_RELAY); else relay.off(LIGHT_WRW_RELAY);
    }
  #endif

  // update relays
  relay.timedOff();

  #if THERMOSTAT == ON
    thermostat.poll();
  #endif

  #if ROOF == ON
    if (roof.isMoving()) roof.poll();
  #endif

  // Gather weather info. and log
  #if WEATHER == ON
    // except while the roof is moving
    #if ROOF == ON
      if (!roof.isMoving())
    #endif
    weather.poll();
  #endif
}

Observatory observatory;
