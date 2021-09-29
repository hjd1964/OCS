// status --------------------------------------------------------------------------------------------------------------------
#include "StatusTile.h"

#include <TimeLib.h>  // from here: https://github.com/PaulStoffregen/Time

#include "htmlHeaders.h"
#include "htmlScripts.h"
#include "htmlTabs.h"

extern int timeZone;
extern time_t startupTime;

#if OPERATIONAL_MODE != WIFI
void statusTile(EthernetClient *client) {
#else
void statusTile() {
#endif
  char temp[128] = "";

  strcpy_P(temp, htmlStatus1);
  sendHtml(temp);

  statusContents(client);

  strcpy_P(temp, htmlStatus3);
  sendHtml(temp);
}

#if OPERATIONAL_MODE != WIFI
void statusContents(EthernetClient *client) {
#else
void statusContents() {
#endif
  char temp[128] = "";
  char temp1[128] = "";
  char ws1[20] = "";
  char ws2[4] = "Std";
  float f;

  strcpy_P(temp, htmlInnerStatus1);
  sendHtml(temp);

  time_t t = now();
  t -= timeZone*SECS_PER_HOUR;  // convert to UTC
  #if TIME_DISPLAY == UTC
    strcpy(ws2, "UTC");
  #elif TIME_DISPLAY == DST
    if (isDst(year(t),month(t),day(t),hour(t),TIME_ZONE)) {
      t = now() + SECS_PER_HOUR;  // +1 hour, Daylight Time
      strcpy(ws2,"Dst");
    } else t = now();
  #endif

  strcpy_P(temp1, htmlInnerStatus2);
  sprintf(ws1, "%02d/%02d/%04d", month(t), day(t), year(t));
  sprintf(temp, temp1, ws2, ws1);
  sendHtml(temp);

  strcpy_P(temp1, htmlInnerStatus3);
  sprintf(ws1, "%02d:%02d", hour(t), minute(t));
  sprintf(temp, temp1, ws2, ws1);
  sendHtml(temp);

  t = (now() - startupTime);
  strcpy_P(temp1, htmlInnerStatus4);
  sprintf(ws1, "%08lu", (unsigned long)(t/60UL));
  sprintf(temp, temp1, ws1);
  sendHtml(temp);

  #if STAT_MAINS_SENSE != OFF
    strcpy_P(temp1,htmlInnerStatusMains);
    if (senseIsOn(STAT_MAINS_SENSE)) strcpy(ws1,"GOOD"); else strcpy(ws1,"OUT");
    sprintf(temp,temp1,ws1);
    sendHtml(temp);
  #endif

  #if STAT_MAINS_CURRENT_ANALOG != OFF
    f = toAmps(analogRead(STAT_MAINS_CURRENT_ANALOG));
    strcpy_P(temp1, htmlInnerStatusMainsA);
    dtostrf(f, 6, 1, ws1);
    strcat(ws1,"A");
    if (f == invalid) strcpy(ws1,"Invalid");
    sprintf(temp, temp1, ws1);
    sendHtml(temp);
  #endif

  #if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
    f = toAmps(analogRead(STAT_MAINS_AUX_CURRENT_ANALOG));
    strcpy_P(temp1, htmlInnerStatusMainsAA);
    dtostrf(f, 6, 1, ws1);
    strcat(ws1, "A");
    if (f == invalid) strcpy(ws1, "Invalid");
    sprintf(temp, temp1, ws1);
    sendHtml(temp);
  #endif

  #if STAT_DC_VOLTAGE_ANALOG != OFF
    f = toDC(analogRead(STAT_DC_VOLTAGE_ANALOG));
    strcpy_P(temp1,htmlInnerStatusDC);
    dtostrf(f,6,1,ws1);
    strcat(ws1,"V");
    if (f == invalid) strcpy(ws1,"Invalid");
    sprintf(temp, temp1, ws1);
    sendHtml(temp);
  #endif

  #if STAT_DC_CURRENT_ANALOG != OFF
    f = toDCAmps(analogRead(STAT_DC_CURRENT_ANALOG));
    strcpy_P(temp1, htmlInnerStatusDCA);
    dtostrf(f, 6, 1, ws1);
    strcat(ws1, "A");
    if (f == invalid) strcpy(ws1,"Invalid");
    sprintf(temp, temp1, ws1);
    sendHtml(temp);
  #endif

  #if STAT_BATTERY_VOLTAGE_ANALOG != OFF
    f = toDC(analogRead(STAT_BATTERY_VOLTAGE_ANALOG));
    strcpy_P(temp1, htmlInnerStatusBat);
    dtostrf(f, 6, 1, ws1);
    strcat(ws1,"V");
    if (f == invalid) strcpy(ws1,"Invalid");
    sprintf(temp, temp1, ws1);
    sendHtml(temp);
  #endif

  #if STAT_BATTERY_CURRENT_ANALOG != OFF
    f = toDCAmps(analogRead(STAT_BATTERY_CURRENT_ANALOG));
    strcpy_P(temp1, htmlInnerStatusBatA);
    dtostrf(f, 6, 1, ws1);
    strcat(ws1, "A");
    if (f == invalid) strcpy(ws1, "Invalid");
    sprintf(temp, temp1, ws1);
    sendHtml(temp);
  #endif
}
