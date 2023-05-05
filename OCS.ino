/*
 * Title       Observatory-Control-System
 * by          Howard Dutton
 *
 * Copyright (C) 2012 to 2023 Howard Dutton
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 
 *
 * Revision History, see GitHub
 *
 *
 * Author: Howard Dutton
 * http://www.stellarjourney.com
 * hjd1964@gmail.com
 *
 * Description
 *
 * General Purpose Observatory Control
 * with LX200 derived command set.
 *
 */

// Use tabs "Config..." to configure the OCS to your requirements

// Firmware version ----------------------------------------------------------------------------------------------------------------
#define FirmwareName                "OCS"
#define FirmwareVersionMajor        3
#define FirmwareVersionMinor        05     // minor version 00 to 99
#define FirmwareVersionPatch        "d"    // for example major.minor patch: 10.03c
#define FirmwareVersionConfig       2      // internal, for tracking configuration file changes

#include "src/Common.h"
NVS nv;
#include "src/Validate.h"
#include "src/lib/sense/Sense.h"
#include "src/lib/tasks/OnTask.h"

#include "src/observatory/Observatory.h"

char ocsVersion[10];

#if DEBUG == PROFILER
  extern void profiler();
#endif

void systemServices() {
  nv.poll();
}

void sensesPoll() {
  sense.poll();
}

bool hasFileSystem = false;

void setup() {
  sprintf(ocsVersion, "%d.%02d%s", FirmwareVersionMajor, FirmwareVersionMinor, FirmwareVersionPatch);
  
  #if DEBUG != OFF
    SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUD);
    delay(2000);
  #endif

  VF("MSG: OCS "); VL(ocsVersion);
  VF("MSG: MCU = "); VLF(MCU_STR);

  // start low level hardware
  VLF("MSG: Setup, HAL initalize");
  HAL_INIT();
  HAL_NV_INIT();
  delay(2000);

  // start any file system
  #ifdef BUILTIN_SDCARD
    #if defined(SDCARD_CS_PIN) && SDCARD_CS_PIN == OFF
      #undef SDCARD_CS_PIN
    #endif
    #define SDCARD_CS_PIN BUILTIN_SDCARD
  #endif

  VF("MSG: Setup, start filesystem ");
  #if WEATHER_CHARTS == ON
    #ifdef ESP32
      hasFileSystem = FS.begin();
    #else
      #if defined(SDCARD_CS_PIN) && SDCARD_CS_PIN != OFF
        #if SD_CARD == ON
          hasFileSystem = FS.begin(SDCARD_CS_PIN);
        #else
          pinMode(SDCARD_CS_PIN, OUTPUT);
          digitalWrite(SDCARD_CS_PIN, HIGH);
        #endif
      #endif
    #endif
  #endif
  if (hasFileSystem) { VLF("success"); } else { VLF("FAILED!"); }

  // start system service task
  VF("MSG: Setup, start system service task (rate 10ms priority 7)... ");
  // add task for system services, runs at 10ms intervals so commiting 1KB of NV takes about 10 seconds
  // the cache is scanned (for writing) at 2000 bytes/second but can be slower while reading data into the cache at startup
  if (tasks.add(10, 0, true, 7, systemServices, "SysSvcs")) { VLF("success"); } else { VLF("FAILED!"); }

  // start input sense monitor task
  VF("MSG: Setup, start input sense monitor task (rate 1ms priority 7)... ");
  if (tasks.add(10, 0, true, 7, sensesPoll, "Sensors")) { VLF("success"); } else { VLF("FAILED!"); }

  // start observatory instance
  observatory.init(FirmwareName, FirmwareVersionMajor, FirmwareVersionMinor, FirmwareVersionPatch, FirmwareVersionConfig);

  // start the IP command channels
  #if OPERATIONAL_MODE != OFF
    #if SERIAL_SERVER == STANDARD || SERIAL_SERVER == BOTH
      SERIAL_SIP.begin(9999, 2L*1000L);
    #endif
    #if SERIAL_SERVER == PERSISTANT || SERIAL_SERVER == BOTH
      SERIAL_PIP1.begin(9998, 120L*1000L, true);
    #endif
  #endif

  // start command channel tasks
  commandChannelInit();

  tasks.yield(2000);

  // start task manager debug events
  #if DEBUG == PROFILER
    tasks.add(142, 0, true, 7, profiler, "Profilr");
  #endif
}

void loop() {
  tasks.yield();
  WDT_RESET;
}
