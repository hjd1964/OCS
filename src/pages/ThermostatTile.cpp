// thermostat ----------------------------------------------------------------------------------------------------------------
#include "ThermostatTile.h"

#if THERMOSTAT == ON
  #include "weather.h"
  #include "htmlHeaders.h"
  #include "htmlScripts.h"
  #include "htmlTabs.h"

  #include "../lib/thermostatSensor/ThermostatSensor.h"
  #include "../lib/relay/Relay.h"
  #include "../observatory/thermostat/Thermostat.h"

  #if OPERATIONAL_MODE != WIFI
  void thermostatTile(EthernetClient *client) {
  #else
  void thermostatTile() {
  #endif
    char temp[512] = "";
    char temp1[255] = "";
    char ws1[20] = "";
    char ws2[20] = "";

    float T = thermostatSensor.temperature();
    if (isnan(T)) {
      strcpy(ws2, "");
      strcpy(ws1, "Invalid");
    } else {
      char ws3[2] = "";
      #if HEAT_RELAY != OFF
        if (relay.isOn(HEAT_RELAY)) strcpy(ws3, "^"); else
      #endif
      #if COOL_RELAY != OFF
        if (relay.isOn(COOL_RELAY)) strcpy(ws3, "*"); else 
      #endif
      strcpy(ws3, "-");
      #if STAT_UNITS == IMPERIAL
        T = T*(9.0/5.0) + 32.0;
        strcpy(ws2, " &deg;F ");
      #else
        strcpy(ws2, " &deg;C ");
      #endif
      strcat(ws2, ws3);
      sprintF(ws1, "%6.1f", T);
    }
//    strcpy_P(temp1, htmlThermostat1);
//    sprintf(temp, temp1, ws1, ws2);
    sprintf_P(temp, htmlThermostat1, ws1, ws2);
    sendHtml(temp);

    #if THERMOSTAT_HUMIDITY == ON
      float h = thermostatInsideHumidity();
      if (isnan(h)) {
        strcpy(ws2, "");
        strcpy(ws1, "Invalid");
      } else {
        strcpy(ws2, " %");
        sprintF(ws1, "%5.1f", h);
      }
//      strcpy_P(temp1, htmlThermostatHumidity);
//      sprintf(temp, temp1, ws1, ws2);
      sprintf_P(temp, htmlThermostatHumidity, ws1, ws2);
      sendHtml(temp);
    #endif

    sendHtml("<br />");

    #if HEAT_RELAY != OFF
      strcpy_P(temp,htmlThermostatHeat1);
      sendHtml(temp);

      #if STAT_UNITS == IMPERIAL
        int h = round(getHeatSetpoint()*(9.0/5.0) + 32.0);
      if (getHeatSetpoint() == 0) h = 0;
      #else
        int h = round(thermostat.getHeatSetpoint());
      #endif

      if (h == 0) strcpy(ws1, "selected"); else strcpy(ws1, "");
      sprintf_P(temp, htmlThermostatOptionZero, ws1);
      sendHtml(temp);

      #if STAT_UNITS == IMPERIAL
        char unitHeat = 'F';
        int hs[11] = {40,50,60,65,67,68,69,70,71,72,73};
      #else
        char unitHeat = 'C';
        int hs[11] = {5,10,15,17,18,19,20,21,22,23,24};
      #endif

      for (int i = 0; i < 11; i++) {
        if (h == hs[i]) strcpy(ws1, "selected"); else strcpy(ws1, "");
        sprintf_P(temp, htmlThermostatOption, hs[i], ws1, hs[i], unitHeat);
        sendHtml(temp);
      }
      strcpy_P(temp,htmlThermostatHeat2);
      sendHtml(temp);
    #endif

    #if COOL_RELAY != OFF
      strcpy_P(temp, htmlThermostatCool1);
      sendHtml(temp);

      #if STAT_UNITS == IMPERIAL
        int c = round(getCoolSetpoint()*(9.0/5.0) + 32.0);
        if (getCoolSetpoint() == 0) c = 0;
      #else
        int c = round(thermostat.getCoolSetpoint());
      #endif

      if (c == 0) strcpy(ws1, "selected"); else strcpy(ws1, "");
      sprintf_P(temp, htmlThermostatOptionZero, ws1);
      sendHtml(temp);

      #if STAT_UNITS == IMPERIAL
        char unitCool = 'F';
        int cs[10] = {68,69,70,71,72,73,75,80,90,99};
      #else
        char unitCool = 'C';
        int cs[10] = {20,21,22,23,24,26,28,30,32,37};
      #endif

      for (int i = 0; i < 10; i++) {
        if (c == cs[i]) strcpy(ws1, "selected"); else strcpy(ws1, "");
        sprintf_P(temp, htmlThermostatOption, cs[i], ws1, cs[i]);
        sendHtml(temp);
      }
      strcpy_P(temp, htmlThermostatCool2);
      sendHtml(temp);
    #endif

    strcpy_P(temp, htmlThermostat2);
    sendHtml(temp);
  }

  #if OPERATIONAL_MODE != WIFI
  void thermostatContents(EthernetClient *client) {
  #else
  void thermostatContents() {
  #endif
    char temp[80] = "";
    char ws1[20] = "";
    char ws2[20] = "";
    
    float t = thermostatSensor.temperature();
    if (isnan(t)) {
      strcpy(ws2, "");
      strcpy(ws1, "Invalid");
    } else {
      char ws3[2] = "";

      #if HEAT_RELAY != OFF
        if (relay.isOn(HEAT_RELAY)) strcpy(ws3, "^"); else
      #endif
      #if COOL_RELAY != OFF
        if (relay.isOn(COOL_RELAY)) strcpy(ws3, "*"); else 
      #endif
        strcpy(ws3, "-");

      #if STAT_UNITS == IMPERIAL
        t = t*(9.0/5.0) + 32.0;
        strcpy(ws2," &deg;F ");
      #else
        strcpy(ws2," &deg;C ");
      #endif

      strcat(ws2, ws3);
      sprintF(ws1, "%6.1f", t);
    }

    sprintf(temp, "%s%s", ws1, ws2);
    sendHtml(temp);
  }

  #if THERMOSTAT_HUMIDITY == ON
    void thermostatHumidityContents(EthernetClient *client) {
      char temp[80] = "";
      char ws1[20] = "";
      char ws2[20] = "";
      
      float h = thermostatInsideHumidity();
      if (isnan(h)) {
        strcpy(ws2, "");
        strcpy(ws1, "Invalid");
      } else {
        strcpy(ws2, " %");
        dtostrf(h, 5, 1, ws1);
      }
      sprintf(temp, "%s%s", ws1, ws2);
      sendHtml(temp);
    }
  #endif

#endif
