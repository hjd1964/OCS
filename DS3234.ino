// -----------------------------------------------------------------------------------------------------------------
// DS3234 time

#if STAT_TIME_SOURCE == DS3234 || STAT_TIME_SOURCE == DS3234INIT

#include "TimeLib.h"

time_t getDs3234Time()
{
#if ROR == ON
  // no updates if the roof is moving
  if (roofIsMoving()) return 0;
#endif

#if DEBUG_DS3234 == ON
  Serial.println("Starting connection to DS3234");
#endif
  rtc.begin(DS3234_CS_PIN);
#if STAT_TIME_SOURCE == DS3234INIT
  rtc.autoTime();
#endif
  rtc.update();
  if ((rtc.year()>=0) && (rtc.month()<=99) && (rtc.month()>=1) && (rtc.month()<=12) && (rtc.date()>=1) && (rtc.date()<=31) &&
      (rtc.hour()>=0) && (rtc.hour()<=23) && (rtc.minute()>=0) && (rtc.minute()<=59) && (rtc.second()>=0) && (rtc.second()<=59)) {
    int y1=rtc.year(); if (y1>11) y1=y1+2000; else y1=y1+2100;
#if DEBUG_DS3234 == ON
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
#if DEBUG_DS3234 == ON
  Serial.println("Failed to get valid date/time from DS3234.");
#endif
  }
  
  return 0; // return 0 if unable to get the time
}

#endif
