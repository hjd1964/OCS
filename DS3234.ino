// -----------------------------------------------------------------------------------------------------------------
// DS3234 time

#if defined(STAT_TIME_DS3234_ON) || defined(STAT_TIME_DS3234_INIT)

#include "TimeLib.h"

time_t getDs3234Time()
{
  #ifdef ROR_ON
  // no updates if the roof is moving
  if (roofIsMoving()) return 0;
  #endif

#ifdef DS3234_DEBUG_ON
  Serial.println("Starting connection to DS3234");
#endif
  rtc.begin(DS3234_CS_PIN);
#if defined(STAT_TIME_DS3234_INIT)
  rtc.autoTime();
#endif
  rtc.update();
  if ((rtc.year()>=0) && (rtc.month()<=99) && (rtc.month()>=1) && (rtc.month()<=12) && (rtc.date()>=1) && (rtc.date()<=31) &&
      (rtc.hour()>=0) && (rtc.hour()<=23) && (rtc.minute()>=0) && (rtc.minute()<=59) && (rtc.second()>=0) && (rtc.second()<=59)) {
    int y1=rtc.year(); if (y1>11) y1=y1+2000; else y1=y1+2100;
#ifdef DS3234_DEBUG_ON
    Serial.print("Year  ="); Serial.println(y1);
    Serial.print("Month ="); Serial.println(rtc.month());
    Serial.print("Day   ="); Serial.println(rtc.date());
    Serial.print("Hour  ="); Serial.println(rtc.hour());
    Serial.print("Minute="); Serial.println(rtc.minute());
    Serial.print("Second="); Serial.println(rtc.second());
#endif
    setTime(rtc.hour(),rtc.minute(),rtc.second(),rtc.date(),rtc.month(),y1);
    time_t t=now();
    return t;
  } else {
#ifdef DS3234_DEBUG_ON
  Serial.println("Failed to get valid date/time from DS3234.");
#endif
  }
  
  return 0; // return 0 if unable to get the time
}

#endif
