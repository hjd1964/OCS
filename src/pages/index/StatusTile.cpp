// status ---------------------------------------------------------------------
#include "StatusTile.h"

#if STAT == ON
  #include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

  #include "../htmlHeaders.h"
  #include "../htmlScripts.h"

  #include "../../lib/sense/Sense.h"
  #include "../../libApp/analog/Analog.h"
  #include "../../observatory/safety/Safety.h"

  extern int timeZone;
  extern time_t startupTime;

  uint16_t getFreeSram();

  void statusTile() {
    char temp[128];
    char temp1[20];
    char temp2[4];
    float f;
    UNUSED(f);

    strcpy_P(temp, htmlStatusBeg);
    www.sendContent(temp);

    strcpy_P(temp, htmlInnerStatusTitle);
    www.sendContent(temp);

    time_t t = now();
    t += timeZone*SECS_PER_HOUR;  // convert to UTC

    strcpy(temp2, "Std");
    #if TIME_DISPLAY == UT1
      strcpy(temp2, "UT1");
    #elif TIME_DISPLAY == DST
      if (isDst(year(t),month(t),day(t),hour(t),TIME_ZONE)) {
        t = now() + SECS_PER_HOUR;  // +1 hour, Daylight Time
        strcpy(temp2,"Dst");
      } else t = now();
    #endif

    sprintf(temp1, "%02d/%02d/%04d", month(t), day(t), year(t));
    sprintf_P(temp, htmlInnerStatusDate, temp2, temp1);
    www.sendContent(temp);

    sprintf(temp1, "%02d:%02d", hour(t), minute(t));
    sprintf_P(temp, htmlInnerStatusTime, temp2, temp1);
    www.sendContent(temp);

    t = (now() - startupTime);
    sprintf(temp1, "%08lu", (unsigned long)(t/60UL));
    sprintf_P(temp, htmlInnerStatusUpTime, temp1);
    www.sendContent(temp);

    #if STAT_MAINS_SENSE != OFF
      if (sense.isOn(STAT_MAINS_SENSE)) strcpy(temp1,"GOOD"); else strcpy(temp1,"OUT");
      sprintf_P(temp, htmlInnerStatusMains, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_MAINS_CURRENT_ANALOG != OFF
      f = STAT_MAINS_ANALOG_TO_CURRENT(analog.read(STAT_MAINS_CURRENT_ANALOG));
      if (isnan(f)) strcpy(temp1, "Invalid"); else sprintF(temp1, "%6.1fA", f);
      sprintf_P(temp, htmlInnerStatusMainsA, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
      f = STAT_MAINS_ANALOG_TO_CURRENT(analog.read(STAT_MAINS_AUX_CURRENT_ANALOG));
      if (isnan(f)) strcpy(temp1, "Invalid"); else sprintF(temp1, "%6.1fA", f);
      sprintf_P(temp, htmlInnerStatusAuxA, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_DC_VOLTAGE_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_VOLTAGE(analog.read(STAT_DC_VOLTAGE_ANALOG));
      if (isnan(f)) strcpy(temp1,"Invalid"); else sprintF(temp1, "%6.1fV", f);
      sprintf_P(temp, htmlInnerStatusDC, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_DC_CURRENT_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_CURRENT(analog.read(STAT_DC_CURRENT_ANALOG));
      if (isnan(f)) strcpy(temp1,"Invalid"); else sprintF(temp1, "%6.1fA", f);
      sprintf_P(temp, htmlInnerStatusDCA, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_BATTERY_VOLTAGE_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_VOLTAGE(analog.read(STAT_BATTERY_VOLTAGE_ANALOG));
      if (isnan(f)) strcpy(temp1,"Invalid"); else sprintF(temp1, "%6.1fV", f);
      sprintf_P(temp, htmlInnerStatusBat, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_BATTERY_CURRENT_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_CURRENT(analog.read(STAT_BATTERY_CURRENT_ANALOG));
      if (isnan(f)) strcpy(temp1, "Invalid"); else sprintF(temp1, "%6.1fA", f);
      sprintf_P(temp, htmlInnerStatusBatA, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_PROCESSOR_RAM != OFF
      long freeRam = getFreeSram();
      sprintf_P(temp, htmlInnerStatusMemory, freeRam);
      www.sendContent(temp);
    #endif

    #if WEATHER_RAIN != OFF || WEATHER_CLOUD_CVR != OFF || WEATHER_WIND_SPD != OFF || STAT_MAINS_SENSE != OFF
      if (safety.isSafe()) strcpy_P(temp, htmlInnerSafe); else strcpy_P(temp, htmlInnerUnSafe);
      www.sendContent(temp);
    #endif

    strcpy_P(temp, htmlStatusEnd);
    www.sendContent(temp);
  }

  void statusTileAjax() {
    char temp[64];
    float f;
    UNUSED(f);

    time_t t = now();
    t += timeZone*SECS_PER_HOUR;  // convert to UTC

    #if TIME_DISPLAY == DST
      if (isDst(year(t),month(t),day(t),hour(t),TIME_ZONE)) {
        t = now() + SECS_PER_HOUR;  // +1 hour, Daylight Time
      } else t = now();
    #endif

    sprintf(temp, "%02d/%02d/%04d", month(t), day(t), year(t));
    www.sendContent("stat_date|"); www.sendContent(temp); www.sendContent("\n");

    sprintf(temp, "%02d:%02d:%02d", hour(t), minute(t), second(t));
    www.sendContent("stat_time|"); www.sendContent(temp); www.sendContent("\n");

    t = (now() - startupTime);
    sprintf(temp, "%08lu", (unsigned long)(t/60UL));
    www.sendContent("stat_upTime|"); www.sendContent(temp); www.sendContent("\n");

    #if STAT_MAINS_SENSE != OFF
      if (sense.isOn(STAT_MAINS_SENSE)) strcpy(temp,"GOOD"); else strcpy(temp,"OUT");
      www.sendContent("stat_mains|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_MAINS_CURRENT_ANALOG != OFF
      f = STAT_MAINS_ANALOG_TO_CURRENT(analog.read(STAT_MAINS_CURRENT_ANALOG));
      if (isnan(f)) strcpy(temp, "Invalid"); else sprintF(temp, "%6.1fA", f);
      www.sendContent("stat_mains_A|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
      f = STAT_MAINS_ANALOG_TO_CURRENT(analog.read(STAT_MAINS_AUX_CURRENT_ANALOG));
      if (isnan(f)) strcpy(temp, "Invalid"); else sprintF(temp, "%6.1fA", f);
      www.sendContent("stat_aux_A|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_DC_VOLTAGE_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_VOLTAGE(analog.read(STAT_DC_VOLTAGE_ANALOG));
      if (isnan(f)) strcpy(temp, "Invalid"); else sprintF(temp, "%6.1fV", f);
      www.sendContent("stat_dc_V|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_DC_CURRENT_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_CURRENT(analog.read(STAT_DC_CURRENT_ANALOG));
      if (isnan(f)) strcpy(temp,"Invalid"); else sprintF(temp, "%6.1fA", f);
      www.sendContent("stat_dc_A|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_BATTERY_VOLTAGE_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_VOLTAGE(analog.read(STAT_BATTERY_VOLTAGE_ANALOG));
      if (isnan(f)) strcpy(temp,"Invalid"); else sprintF(temp, "%6.1fV", f);
      www.sendContent("stat_bat_V|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_BATTERY_CURRENT_ANALOG != OFF
      f = STAT_DC_ANALOG_TO_CURRENT(analog.read(STAT_BATTERY_CURRENT_ANALOG));
      if (isnan(f)) strcpy(temp, "Invalid"); else sprintF(temp, "%6.1fA", f);
      www.sendContent("stat_bat_A|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_PROCESSOR_RAM != OFF
      long freeRam = getFreeSram();
      sprintf(temp, "%ld", freeRam);
      www.sendContent("stat_mem|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if WEATHER_RAIN != OFF || WEATHER_CLOUD_CVR != OFF || WEATHER_WIND_SPD != OFF || STAT_MAINS_SENSE != OFF
      if (safety.isSafe()) strcpy(temp, "Safe"); else strcpy(temp, "<span style='color:#ff0000;'>UNSAFE</span>");
      www.sendContent("stat_mem|"); www.sendContent(temp); www.sendContent("\n");
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
