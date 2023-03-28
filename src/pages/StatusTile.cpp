// status --------------------------------------------------------------------------------------------------------------------
#include "StatusTile.h"

#if STAT == ON
  #include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

  #include "htmlHeaders.h"
  #include "htmlScripts.h"
  #include "htmlTabs.h"

  #include "../lib/sense/Sense.h"
  #include "../libApp/analog/Analog.h"

  extern int timeZone;
  extern time_t startupTime;

  void statusTile() {
    char temp[100] = "";

    strcpy_P(temp, htmlStatus1);
    www.sendContent(temp);

    statusContents();

    strcpy_P(temp, htmlStatus3);
    www.sendContent(temp);
  }

  uint16_t getFreeSram();

  void statusContents() {
    char temp[128];
    char ws1[20];
    char ws2[4];
    float f;
    UNUSED(f);

    strcpy_P(temp, htmlInnerStatus1);
    www.sendContent(temp);

    time_t t = now();
    t += timeZone*SECS_PER_HOUR;  // convert to UTC

    strcpy(ws2, "Std");
    #if TIME_DISPLAY == UT1
      strcpy(ws2, "UT1");
    #elif TIME_DISPLAY == DST
      if (isDst(year(t),month(t),day(t),hour(t),TIME_ZONE)) {
        t = now() + SECS_PER_HOUR;  // +1 hour, Daylight Time
        strcpy(ws2,"Dst");
      } else t = now();
    #endif

    sprintf(ws1, "%02d/%02d/%04d", month(t), day(t), year(t));
    sprintf_P(temp, htmlInnerStatus2, ws2, ws1);
    www.sendContent(temp);

    sprintf(ws1, "%02d:%02d", hour(t), minute(t));
    sprintf_P(temp, htmlInnerStatus3, ws2, ws1);
    www.sendContent(temp);

    t = (now() - startupTime);
    sprintf(ws1, "%08lu", (unsigned long)(t/60UL));
    sprintf_P(temp, htmlInnerStatus4, ws1);
    www.sendContent(temp);

    #if STAT_MAINS_SENSE != OFF
      if (sense.isOn(STAT_MAINS_SENSE)) strcpy(ws1,"GOOD"); else strcpy(ws1,"OUT");
      sprintf_P(temp, htmlInnerStatusMains, ws1);
      www.sendContent(temp);
    #endif

    #if STAT_MAINS_CURRENT_ANALOG != OFF
      f = STAT_MAINS_ANALOG_TO_CURRENT(analog.read(STAT_MAINS_CURRENT_ANALOG));
      if (isnan(f)) strcpy(ws1, "Invalid"); else sprintF(ws1, "%6.1fA", f);
      sprintf_P(temp, htmlInnerStatusMainsA, ws1);
      www.sendContent(temp);
    #endif

    #if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
      f = STAT_MAINS_ANALOG_TO_CURRENT(analog.read(STAT_MAINS_AUX_CURRENT_ANALOG));
      if (isnan(f)) strcpy(ws1, "Invalid"); else sprintF(ws1, "%6.1fA", f);
      sprintf_P(temp, htmlInnerStatusMainsAA, ws1);
      www.sendContent(temp);
    #endif

    #if STAT_DC_VOLTAGE_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_VOLTAGE(analog.read(STAT_DC_VOLTAGE_ANALOG));
      if (isnan(f)) strcpy(ws1,"Invalid"); else sprintF(ws1, "%6.1fV", f);
      sprintf_P(temp, htmlInnerStatusDC, ws1);
      www.sendContent(temp);
    #endif

    #if STAT_DC_CURRENT_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_CURRENT(analog.read(STAT_DC_CURRENT_ANALOG));
      if (isnan(f)) strcpy(ws1,"Invalid"); else sprintF(ws1, "%6.1fA", f);
      sprintf_P(temp, htmlInnerStatusDCA, ws1);
      www.sendContent(temp);
    #endif

    #if STAT_BATTERY_VOLTAGE_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_VOLTAGE(analog.read(STAT_BATTERY_VOLTAGE_ANALOG));
      if (isnan(f)) strcpy(ws1,"Invalid"); else sprintF(ws1, "%6.1fV", f);
      sprintf_P(temp, htmlInnerStatusBat, ws1);
      www.sendContent(temp);
    #endif

    #if STAT_BATTERY_CURRENT_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_CURRENT(analog.read(STAT_BATTERY_CURRENT_ANALOG));
      if (isnan(f)) strcpy(ws1, "Invalid"); else sprintF(ws1, "%6.1fA", f);
      sprintf_P(temp, htmlInnerStatusBatA, ws1);
      www.sendContent(temp);
    #endif

    #if STAT_PROCESSOR_RAM != OFF
      long freeRam = getFreeSram();
      sprintf_P(temp, htmlInnerStatusMemory, freeRam);
      www.sendContent(temp);
    #endif
  }

  #if STAT_PROCESSOR_RAM != OFF
    extern unsigned int __bss_end;
    extern unsigned int __heap_start;
    extern void *__brkval;

    uint16_t getFreeSram() {
      uint8_t newVariable;
      // heap is empty, use bss as start memory address
      if ((uint16_t)__brkval == 0)
        return (((uint16_t)&newVariable) - ((uint16_t)&__bss_end));
      // use heap end as the start of the memory address
      else
        return (((uint16_t)&newVariable) - ((uint16_t)__brkval));
    };
  #endif
#endif
