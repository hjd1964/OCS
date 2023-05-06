// thermostat -----------------------------------------------------------------
#include "ThermostatTile.h"

#if THERMOSTAT == ON
  #include "../../libApp/thermostatSensor/ThermostatSensor.h"
  #include "../../libApp/relay/Relay.h"
  #include "../../observatory/thermostat/Thermostat.h"

  void getThermostatTemperatureStr(char *temp);
  #if THERMOSTAT_HUMIDITY == ON
    void getThermostatHumidityStr(char *temp);
  #endif

  void thermostatTile() {
    char temp[256];
    char temp1[32];
    UNUSED(temp1);

    strcpy_P(temp, htmlThermostatBegin);
    www.sendContent(temp);

    strcpy_P(temp, htmlThermostatTemperatureBeg);
    www.sendContent(temp);

    getThermostatTemperatureStr(temp);
    www.sendContent(temp);

    strcpy_P(temp, htmlThermostatTemperatureEnd);
    www.sendContent(temp);

    #if THERMOSTAT_HUMIDITY == ON
      strcpy_P(temp, htmlThermostatHumidityBeg);
      www.sendContent(temp);

      getThermostatHumidityStr(temp);
      www.sendContent(temp);

      strcpy_P(temp, htmlThermostatHumidityEnd);
      www.sendContent(temp);
    #endif

    www.sendContent(F("<br />"));

    #if HEAT_RELAY != OFF
    {
      strcpy_P(temp, htmlThermostatHeatBeg);
      www.sendContent(temp);

      #if DISPLAY_UNITS == IMPERIAL
        int h = round(thermostat.getHeatSetpoint()*(9.0/5.0) + 32.0);
      if (thermostat.getHeatSetpoint() == 0) h = 0;
      #else
        int h = round(thermostat.getHeatSetpoint());
      #endif

      if (h == 0) strcpy(temp1, "selected"); else strcpy(temp1, "");
      sprintf_P(temp, htmlThermostatOptionZero, temp1);
      www.sendContent(temp);

      #if DISPLAY_UNITS == IMPERIAL
        char unitHeat = 'F';
        int hs[11] = {40,50,60,65,67,68,69,70,71,72,73};
      #else
        char unitHeat = 'C';
        int hs[11] = {5,10,15,17,18,19,20,21,22,23,24};
      #endif

      for (int i = 0; i < 11; i++) {
        if (h == hs[i]) strcpy(temp1, "selected"); else strcpy(temp1, "");
        sprintf_P(temp, htmlThermostatOption, hs[i], temp1, hs[i], unitHeat);
        www.sendContent(temp);
      }
      strcpy_P(temp,htmlThermostatHeatEnd);
      www.sendContent(temp);
    }
    #endif

    #if COOL_RELAY != OFF
    {
      strcpy_P(temp, htmlThermostatCoolBeg);
      www.sendContent(temp);

      #if DISPLAY_UNITS == IMPERIAL
        int c = round(thermostat.getCoolSetpoint()*(9.0/5.0) + 32.0);
        if (thermostat.getCoolSetpoint() == 0) c = 0;
      #else
        int c = round(thermostat.getCoolSetpoint());
      #endif

      if (c == 0) strcpy(temp1, "selected"); else strcpy(temp1, "");
      sprintf_P(temp, htmlThermostatOptionZero, temp1);
      www.sendContent(temp);

      #if DISPLAY_UNITS == IMPERIAL
        char unitCool = 'F';
        int cs[10] = {68,69,70,71,72,73,75,80,90,99};
      #else
        char unitCool = 'C';
        int cs[10] = {20,21,22,23,24,26,28,30,32,37};
      #endif

      for (int i = 0; i < 10; i++) {
        if (c == cs[i]) strcpy(temp1, "selected"); else strcpy(temp1, "");
        sprintf_P(temp, htmlThermostatOption, cs[i], temp1, cs[i], unitCool);
        www.sendContent(temp);
      }
      strcpy_P(temp, htmlThermostatCoolEnd);
      www.sendContent(temp);
    }
    #endif

    #if HUMIDITY_RELAY != OFF
    {
      strcpy_P(temp, htmlThermostatHumidityControlBeg);
      www.sendContent(temp);
      int c = round(thermostat.getHumiditySetpoint());
      if (c == 0) strcpy(temp1, "selected"); else strcpy(temp1, "");
      sprintf_P(temp, htmlThermostatOptionZero, temp1);
      www.sendContent(temp);
      char unitHumidity = '%';
      int cs[11] = {30,35,40,45,50,55,60,65,70,75,80};

      for (int i = 0; i < 10; i++) {
        if (c == cs[i]) strcpy(temp1, "selected"); else strcpy(temp1, "");
        sprintf_P(temp, htmlThermostatHumidityOption, cs[i], temp1, cs[i], unitHumidity);
        www.sendContent(temp);
      }
      strcpy_P(temp, htmlThermostatHumidityControlEnd);
      www.sendContent(temp);
    }
    #endif

    strcpy_P(temp, htmlThermostatEnd);
    www.sendContent(temp);
  }

  void thermostatTileAjax() {
    char temp[80];
    getThermostatTemperatureStr(temp);
    www.sendContent("tstat_T|"); www.sendContent(temp); www.sendContent("\n");

    #if THERMOSTAT_HUMIDITY == ON
      getThermostatHumidityStr(temp);
      www.sendContent("tstat_H|"); www.sendContent(temp); www.sendContent("\n");
    #endif
  }

  void thermostatTileGet() {
    #if HEAT_RELAY != OFF
      String heat = www.arg("tstat_heat");
      if (!heat.equals(EmptyStr)) {
        #if DISPLAY_UNITS == IMPERIAL
          float f = 0;
          if (heat.toInt() != 0) f = (heat.toInt() - 32.0)*(5.0/9.0);
        #else
          float f = heat.toFloat();
        #endif
      if (f >= 0.0 && f <= 37.0) thermostat.setHeatSetpoint(f);
    }
    #endif

    #if COOL_RELAY != OFF
      String cool = www.arg("tstat_cool");
      if (!cool.equals(EmptyStr)) {
        #if DISPLAY_UNITS == IMPERIAL
          float f = 0;
          if (cool.toInt() != 0) f = (cool.toInt() - 32.0)*(5.0/9.0);
        #else
          float f = atoi(cool.c_str());
        #endif
        if (f >= 0.0 && f <= 37.0) thermostat.setCoolSetpoint(f);
      }
    #endif

    #if HUMIDITY_RELAY != OFF
      String humidity = www.arg("tstat_humidity");
      if (!humidity.equals(EmptyStr)) {
        float f = atoi(humidity.c_str());
        if (f >= 0.0 && f <= 75.0) thermostat.setHumiditySetpoint(f);
      }
    #endif
  }

  void getThermostatTemperatureStr(char *temp) {
    float t = thermostatSensor.temperature();
    if (isnan(t)) {
      strcpy_P(temp, htmlStringInvalid);
    } else {
      #if DISPLAY_UNITS == IMPERIAL
        t = t*(9.0/5.0) + 32.0;
        sprintF(temp, "%6.1f &deg;F ", t);
      #else
        sprintF(temp, "%6.1f &deg;C ", t);
      #endif

      #if HEAT_RELAY != OFF
        if (relay.isOn(HEAT_RELAY)) strcat(temp, "^"); else
      #endif
      #if COOL_RELAY != OFF
        if (relay.isOn(COOL_RELAY)) strcat(temp, "*"); else 
      #endif
      strcat(temp, "-");
    }
  }

  #if THERMOSTAT_HUMIDITY == ON
    void getThermostatHumidityStr(char *temp) {
      float h = thermostatSensor.humidity();
      if (isnan(h)) {
        strcpy_P(temp, htmlStringInvalid);
      } else {
        sprintF(temp, "%5.1f % ", h);
      }
      #if HUMIDITY_RELAY != OFF
        if (relay.isOn(HUMIDITY_RELAY)) strcat(temp, "ˇ"); else strcat(temp, "-");
      #endif
    }
  #endif

#endif
