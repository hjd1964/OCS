// status ---------------------------------------------------------------------
#include "StatusTile.h"

#if STAT == ON
  #include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

  #include "../../lib/sense/Sense.h"
  #include "../../libApp/analog/Analog.h"
  #include "../../observatory/safety/Safety.h"

  extern int timeZone;
  extern time_t startupTime;

  #if STAT_PROCESSOR_RAM != OFF
    uint16_t getFreeSram();
  #endif
  time_t getStatusDateTimeAndUnitStr(char *temp);
  void getStatusVoltsStr(float f, char *temp);
  void getStatusAmpsStr(float f, char *temp);

  void statusTile() {
    char temp[256];
    char temp1[32];
    char temp2[32];

    strcpy_P(temp, htmlStatusBeg);
    www.sendContent(temp);

    strcpy_P(temp, htmlInnerStatusTitle);
    www.sendContent(temp);

    time_t t = getStatusDateTimeAndUnitStr(temp2);

    sprintf(temp1, "%02d/%02d/%04d", month(t), day(t), year(t));
    sprintf_P(temp, htmlInnerStatusDate, temp2, temp1);
    www.sendContent(temp);

    sprintf(temp1, "%02d:%02d:%02d", hour(t), minute(t), second(t));
    sprintf_P(temp, htmlInnerStatusTime, temp2, temp1);
    www.sendContent(temp);

    sprintf(temp1, "%08lu", (unsigned long)((now() - startupTime)/60));
    sprintf_P(temp, htmlInnerStatusUpTime, temp1);
    www.sendContent(temp);

    #if STAT_MAINS_SENSE != OFF
      if (sense.isOn(STAT_MAINS_SENSE)) strcpy(temp1, "GOOD"); else strcpy(temp1, "OUT"); 
      sprintf_P(temp, htmlInnerStatusMains, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_MAINS_CURRENT_ANALOG != OFF
      getStatusAmpsStr(STAT_MAINS_ANALOG_TO_CURRENT(analog.read(STAT_MAINS_CURRENT_ANALOG)), temp1);
      sprintf_P(temp, htmlInnerStatusMainsA, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
      getStatusAmpsStr(STAT_MAINS_ANALOG_TO_CURRENT(analog.read(STAT_MAINS_AUX_CURRENT_ANALOG)), temp1);
      sprintf_P(temp, htmlInnerStatusAuxA, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_DC_VOLTAGE_ANALOG != OFF
      getStatusVoltsStr(STAT_DC_ANALOG_TO_VOLTAGE(analog.read(STAT_DC_VOLTAGE_ANALOG)), temp1);
      sprintf_P(temp, htmlInnerStatusDC, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_DC_CURRENT_ANALOG != OFF
      getStatusAmpsStr(STAT_DC_ANALOG_TO_CURRENT(analog.read(STAT_DC_CURRENT_ANALOG)), temp1);
      sprintf_P(temp, htmlInnerStatusDCA, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_BATTERY_VOLTAGE_ANALOG != OFF
      getStatusVoltsStr(STAT_DC_ANALOG_TO_VOLTAGE(analog.read(STAT_BATTERY_VOLTAGE_ANALOG)), temp1);
      sprintf_P(temp, htmlInnerStatusBat, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_BATTERY_CURRENT_ANALOG != OFF
      getStatusAmpsStr(STAT_DC_ANALOG_TO_CURRENT(analog.read(STAT_BATTERY_CURRENT_ANALOG)), temp1);
      sprintf_P(temp, htmlInnerStatusBatA, temp1);
      www.sendContent(temp);
    #endif

    #if STAT_PROCESSOR_RAM != OFF
      sprintf_P(temp, htmlInnerStatusMemory, (long)getFreeSram());
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
    char temp[48];

    time_t t = getStatusDateTimeAndUnitStr(temp);

    sprintf(temp, "%02d/%02d/%04d", month(t), day(t), year(t));
    www.sendContent("stat_date|"); www.sendContent(temp); www.sendContent("\n");

    sprintf(temp, "%02d:%02d:%02d", hour(t), minute(t), second(t));
    www.sendContent("stat_time|"); www.sendContent(temp); www.sendContent("\n");

    sprintf(temp, "%08lu", (unsigned long)((now() - startupTime)/60));
    www.sendContent("stat_upTime|"); www.sendContent(temp); www.sendContent("\n");

    #if STAT_MAINS_SENSE != OFF
      if (sense.isOn(STAT_MAINS_SENSE)) strcpy(temp,"GOOD"); else strcpy(temp,"OUT");
      www.sendContent("stat_mains|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_MAINS_CURRENT_ANALOG != OFF
      getStatusAmpsStr(STAT_MAINS_ANALOG_TO_CURRENT(analog.read(STAT_MAINS_CURRENT_ANALOG)), temp);
      www.sendContent("stat_mains_A|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
      getStatusAmpsStr(STAT_MAINS_ANALOG_TO_CURRENT(analog.read(STAT_MAINS_AUX_CURRENT_ANALOG)), temp);
      www.sendContent("stat_aux_A|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_DC_VOLTAGE_ANALOG != OFF
      getStatusVoltsStr(STAT_DC_ANALOG_TO_VOLTAGE(analog.read(STAT_DC_VOLTAGE_ANALOG)), temp);
      www.sendContent("stat_dc_V|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_DC_CURRENT_ANALOG != OFF
      getStatusAmpsStr(STAT_DC_ANALOG_TO_CURRENT(analog.read(STAT_DC_CURRENT_ANALOG)), temp);
      www.sendContent("stat_dc_A|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_BATTERY_VOLTAGE_ANALOG != OFF
      getStatusVoltsStr(STAT_DC_ANALOG_TO_VOLTAGE(analog.read(STAT_BATTERY_VOLTAGE_ANALOG)), temp);
      www.sendContent("stat_bat_V|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_BATTERY_CURRENT_ANALOG != OFF
      getStatusAmpsStr(STAT_DC_ANALOG_TO_CURRENT(analog.read(STAT_BATTERY_CURRENT_ANALOG)), temp1)
      www.sendContent("stat_bat_A|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if STAT_PROCESSOR_RAM != OFF
      sprintf(temp, "%ld", (long)getFreeSram());
      www.sendContent("stat_mem|"); www.sendContent(temp); www.sendContent("\n");
    #endif

    #if WEATHER_RAIN != OFF || WEATHER_CLOUD_CVR != OFF || WEATHER_WIND_SPD != OFF || STAT_MAINS_SENSE != OFF
      if (safety.isSafe()) strcpy(temp, L_SAFE); else strcpy_P(temp, htmlStringUnSafe);
      www.sendContent("stat_safe|"); www.sendContent(temp); www.sendContent("\n");
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

  time_t getStatusDateTimeAndUnitStr(char *temp) {
    time_t t = now();
    t += timeZone*SECS_PER_HOUR;  // convert to UTC

    strcpy(temp, L_STD_TIME);
    #if TIME_DISPLAY == UT1
      strcpy(temp, L_UT1_TIME);
    #elif TIME_DISPLAY == DST
      if (isDst(year(t),month(t),day(t),hour(t),TIME_ZONE)) {
        t = now() + SECS_PER_HOUR;  // +1 hour, Daylight Time
        strcpy(temp,L_DST_TIME);
      } else t = now();
    #endif
    return t;
  }

  void getStatusVoltsStr(float f, char *temp) {
    if (isnan(f)) strcpy_P(temp, htmlStringInvalid); else sprintF(temp, "%6.1fV", f);
  }

  void getStatusAmpsStr(float f, char *temp) {
    if (isnan(f)) strcpy_P(temp, htmlStringInvalid); else sprintF(temp, "%6.1fA", f);
  }

#endif
