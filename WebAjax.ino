// -----------------------------------------------------------------------------------
// Web server, Ajax pages

void relays(EthernetClient *client) {
  for (int i=1; i<=14; i++) {
    String s="r"+String(i);
    String a=www.arg(s);
    uint8_t state=0;
    if (a!="") {
      if (a=="true") {
        setRelayOn(i); state=(uint8_t)true;
#if DEBUG_AJAX_RELAY == ON
        Serial.print(s); Serial.println("=on");  
#endif
      }
      if (a=="false") {
        setRelayOff(i); state=(uint8_t)false;
#if DEBUG_AJAX_RELAY == ON
        Serial.print(s); Serial.println("=off"); 
#endif
      }
      
      // if this relay is from the "Power Panel" store the setting if requested
      if (a == "true" || a == "false") {
        #if POWER_DEVICE1_RELAY != OFF && POWER_DEVICE1_MEMORY != OFF
          if (i == POWER_DEVICE1_RELAY) EEPROM.write(EE_powerDevice_1,state);
        #endif
        #if POWER_DEVICE2_RELAY != OFF && POWER_DEVICE2_MEMORY != OFF
          if (i == POWER_DEVICE2_RELAY) EEPROM.write(EE_powerDevice_2,state);
        #endif
        #if POWER_DEVICE3_RELAY != OFF && POWER_DEVICE3_MEMORY != OFF
          if (i == POWER_DEVICE3_RELAY) EEPROM.write(EE_powerDevice_3,state);
        #endif
        #if POWER_DEVICE4_RELAY != OFF && POWER_DEVICE4_MEMORY != OFF
          if (i == POWER_DEVICE4_RELAY) EEPROM.write(EE_powerDevice_4,state);
        #endif
        #if POWER_DEVICE5_RELAY != OFF && POWER_DEVICE5_MEMORY != OFF
          if (i == POWER_DEVICE5_RELAY) EEPROM.write(EE_powerDevice_5,state);
        #endif
        #if POWER_DEVICE6_RELAY != OFF && POWER_DEVICE6_MEMORY != OFF
          if (i == POWER_DEVICE6_RELAY) EEPROM.write(EE_powerDevice_6,state);
        #endif
      }
      if (a=="get") { s=String(relayState[i]); client->print(s); break; }
    }
  }
}

void setvar(EthernetClient *client) {
  String a=www.arg("press");
  
// lights
#if LIGHT == ON
#if LIGHT_OUTSIDE_RELAY != OFF
  if (a=="light_exit") { 
    setRelayOnDelayedOff(atoi(LIGHT_OUTSIDE_RELAY),236); // turn off after about 4 minutes
  }
#endif
#endif

// roll-off roof
#if ROR == ON
  if (a=="roof_open") { startRoofOpen(); }
  if (a=="roof_close") { startRoofClose(); }
  if (a=="roof_override") { setRoofSafetyOverride(); }
  if (a=="roof_stop") { stopRoof(); clearRoofStatus(); }
  a=www.arg("auto_close");
  if (a=="true") { roofAutoClose=true; }
  if (a=="false") { roofAutoClose=false; }
#endif

// thermostat
#if THERMOSTAT == ON
  #if HEAT_RELAY != OFF
    a=www.arg("thermostat_heat");
    if (a!="") {
  #if STAT_UNITS == IMPERIAL
      float f=0; if (atoi(a.c_str())!=0) f=(float(atoi(a.c_str()))-32.0)*(5.0/9.0);
  #else
      float f=atoi(a.c_str());
  #endif
    if (f >= 0.0 && f <= 37.0) setHeatSetpoint(f);
  }
#endif
  #if COOL_RELAY != OFF
    a=www.arg("thermostat_cool");
    if (a!="") {
    #if STAT_UNITS == IMPERIAL
        float f=0; if (atoi(a.c_str())!=0) f=(float(atoi(a.c_str()))-32.0)*(5.0/9.0);
    #else
        float f=atoi(a.c_str());
    #endif
      if (f >= 0.0 && f <= 37.0) setCoolSetpoint(f);
    }
  #endif
#endif
}

// status --------------------------------------------------------------------------------------------------------------------
const char htmlInnerStatus1[] PROGMEM =
"<b>Status</b><br />";
const char htmlInnerStatus2[] PROGMEM =
"&nbsp;&nbsp;Date (%s Time)<div class=\"aStatus\">%s</div><br />";
const char htmlInnerStatus3[] PROGMEM =
"&nbsp;&nbsp;Time (%s Time)<div class=\"aStatus\">%s</div><br />";
const char htmlInnerStatus4[] PROGMEM =
"&nbsp;&nbsp;Up Time (Minutes)<div class=\"aStatus\">%s</div><br /><br />";
#if STAT_MAINS_SENSE != OFF
const char htmlInnerStatusMains[] PROGMEM =
"&nbsp;&nbsp;Mains Power<div class=\"aStatus\">%s</div><br />";
#endif
#if STAT_MAINS_CURRENT_ANALOG != OFF
const char htmlInnerStatusMainsA[] PROGMEM =
"&nbsp;&nbsp;Mains Current<div class=\"aStatus\">%s</div><br />";
#endif
#if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
const char htmlInnerStatusMainsAA[] PROGMEM =
"&nbsp;&nbsp;Mains Aux Current<div class=\"aStatus\">%s</div><br />";
#endif
#if STAT_DC_VOLTAGE_ANALOG != OFF
const char htmlInnerStatusDC[] PROGMEM =
"&nbsp;&nbsp;DC Power Supply<div class=\"aStatus\">%s</div><br />";
#endif
#if STAT_DC_CURRENT_ANALOG != OFF
const char htmlInnerStatusDCA[] PROGMEM =
"&nbsp;&nbsp;DC Current<div class=\"aStatus\">%s</div><br />";
#endif
#if STAT_BATTERY_VOLTAGE_ANALOG != OFF
const char htmlInnerStatusBat[] PROGMEM =
"&nbsp;&nbsp;Battery<div class=\"aStatus\">%s</div><br />";
#endif
#if STAT_BATTERY_CURRENT_ANALOG != OFF
const char htmlInnerStatusBatA[] PROGMEM =
"&nbsp;&nbsp;Battery Current<div class=\"aStatus\">%s</div><br />";
#endif

void miscstatus(EthernetClient *client) {
  char temp[128]="";
  char temp1[128]="";
  char ws1[20]="";
  char ws2[4]="Std";
  double f;

  strcpy_P(temp,htmlInnerStatus1); client->print(temp);

  time_t t=now();
#if TIME_DISPLAY == UTC
  t-=timeZone*SECS_PER_HOUR; // convert to UTC
  strcpy(ws2,"UTC");
#elif TIME_DISPLAY == DST
  t-=timeZone*SECS_PER_HOUR; // convert to UTC
  if (isDst(year(t),month(t),day(t),hour(t),TIME_ZONE)) {
    t=now()+SECS_PER_HOUR;   // +1 hour, Daylight Time
    strcpy(ws2,"Dst");
  } else t=now();
#endif

  strcpy_P(temp1,htmlInnerStatus2); sprintf(ws1,"%02d/%02d/%04d",month(t),day(t),year(t)); sprintf(temp,temp1,ws2,ws1); client->print(temp);
  strcpy_P(temp1,htmlInnerStatus3); sprintf(ws1,"%02d:%02d",hour(t),minute(t)); sprintf(temp,temp1,ws2,ws1); client->print(temp);
  t=(now()-startupTime);
  strcpy_P(temp1,htmlInnerStatus4); sprintf(ws1,"%08lu",(unsigned long)(t/60UL)); sprintf(temp,temp1,ws1); client->print(temp);
#if STAT_MAINS_SENSE != OFF
  strcpy_P(temp1,htmlInnerStatusMains);  if (senseIsOn(STAT_MAINS_SENSE)) strcpy(ws1,"GOOD"); else strcpy(ws1,"OUT"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#if STAT_MAINS_CURRENT_ANALOG != OFF
  f=toAmps(analogRead(STAT_MAINS_CURRENT_ANALOG));
  strcpy_P(temp1,htmlInnerStatusMainsA);  dtostrf(f,6,1,ws1); strcat(ws1,"A"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#if STAT_MAINS_AUX_CURRENT_ANALOG != OFF
  f=toAmps(analogRead(STAT_MAINS_AUX_CURRENT_ANALOG));
  strcpy_P(temp1,htmlInnerStatusMainsAA); dtostrf(f,6,1,ws1); strcat(ws1,"A"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#if STAT_DC_VOLTAGE_ANALOG != OFF
  f=toDC(analogRead(STAT_DC_VOLTAGE_ANALOG));
  strcpy_P(temp1,htmlInnerStatusDC);      dtostrf(f,6,1,ws1); strcat(ws1,"V"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#if STAT_DC_CURRENT_ANALOG != OFF
  f=toDCAmps(analogRead(STAT_DC_CURRENT_ANALOG));
  strcpy_P(temp1,htmlInnerStatusDCA);     dtostrf(f,6,1,ws1); strcat(ws1,"A"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#if STAT_BATTERY_VOLTAGE_ANALOG != OFF
  f=toDC(analogRead(STAT_BATTERY_VOLTAGE_ANALOG));
  strcpy_P(temp1,htmlInnerStatusBat);     dtostrf(f,6,1,ws1); strcat(ws1,"V"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#if STAT_BATTERY_CURRENT_ANALOG != OFF
  f=toDCAmps(analogRead(STAT_BATTERY_CURRENT_ANALOG));
  strcpy_P(temp1,htmlInnerStatusBatA);    dtostrf(f,6,1,ws1); strcat(ws1,"A"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
}

// weather -------------------------------------------------------------------------------------------------------------------
#if WEATHER == ON
const char htmlInnerWeather1[] PROGMEM =
"<b>Weather</b><br />";
#if WEATHER_TEMPERATURE == ON
  const char htmlInnerWeatherTemp[] PROGMEM =
  "&nbsp;&nbsp;Temperature<div class=\"aStatus\">%s%s</div><br />";
#endif
#if WEATHER_PRESSURE == ON
const char htmlInnerWeatherPres[] PROGMEM =
"&nbsp;&nbsp;Barometric Pressure<div class=\"aStatus\">%s%s</div><br />";
#endif
#if WEATHER_HUMIDITY == ON
const char htmlInnerWeatherHumd[] PROGMEM =
"&nbsp;&nbsp;Relative Humidity<div class=\"aStatus\">%s%s</div><br />";
#endif
#if WEATHER_WIND_SPD == ON
const char htmlInnerWeatherWind[] PROGMEM =
"&nbsp;&nbsp;Wind Speed<div class=\"aStatus\">%s%s</div><br />";
#endif
#if WEATHER_RAIN == ON
const char htmlInnerWeatherRain[] PROGMEM =
"&nbsp;&nbsp;Rain sensor<div class=\"aStatus\">%s</div><br />";
#endif
#if WEATHER_SKY_QUAL == ON
const char htmlInnerWeatherSq[] PROGMEM =
"&nbsp;&nbsp;Sky Quality<div class=\"aStatus\">%s%s</div><br />";
#endif
#if WEATHER_CLOUD_CVR == ON
const char htmlInnerWeatherCloud[] PROGMEM =
"&nbsp;&nbsp;Sky Conditions<div class=\"aStatus\">%s</div><br />";
#endif
#if WEATHER_RAIN == ON || WEATHER_CLOUD_CVR == ON || WEATHER_WIND_SPD == ON || STAT_MAINS_SENSE != OFF
const char htmlInnerWeatherSafe[] PROGMEM =
"<div style=\"position: absolute; bottom: 5px; left: 120px; text-align:center\";><div style=\"display:inline-block; ";
const char htmlInnerWeatherSafe1[] PROGMEM =
"background-color: #bcccbc; color: green; border:1px solid green; padding: 4px 4px;\">SAFE</div></div><br />";
#endif
#if WEATHER_RAIN == ON || WEATHER_CLOUD_CVR == ON || WEATHER_WIND_SPD == ON || STAT_MAINS_SENSE != OFF
const char htmlInnerWeatherUnSafe[] PROGMEM =
"<div style=\"position: absolute; bottom: 5px; left: 110px; text-align:center\";><div style=\"display:inline-block; ";
const char htmlInnerWeatherUnSafe1[] PROGMEM =
"background-color: #ccbcbc; color: red; border:1px solid red; padding: 4px 4px;\">UNSAFE</div></div><br />";
#endif

void weather(EthernetClient *client) {
  char temp[128]="";
  char temp1[128]="";
  char ws1[30]="";
  char ws2[30]="";
  float f;

  strcpy_P(temp,htmlInnerWeather1); client->print(temp);
#if WEATHER_TEMPERATURE == ON
  f=weatherOutsideTemp(); strcpy(ws2," &deg;C");
  #if STAT_UNITS == IMPERIAL
    f=f*(9.0/5.0)+32.0; strcpy(ws2," &deg;F");
  #endif
  if (f<-200) { strcpy(ws1,"Invalid"); strcpy(ws2,""); } else dtostrf(f,5,1,ws1);
  strcpy_P(temp1,htmlInnerWeatherTemp); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#endif
#if WEATHER_PRESSURE == ON
  #if STAT_UNITS == IMPERIAL
    f=weatherPressureSeaLevel()*0.02953; strcpy(ws2," in");
    if (f==invalid) { strcpy(ws1,"Invalid"); strcpy(ws2,""); } else dtostrf(f,6,2,ws1);
  #else
    f=weatherPressureSeaLevel(); strcpy(ws2," mb");
    if (f==invalid) { strcpy(ws1,"Invalid"); strcpy(ws2,""); } else dtostrf(f,6,0,ws1);
  #endif
  strcpy_P(temp1,htmlInnerWeatherPres); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#endif
#if WEATHER_HUMIDITY == ON
  f=weatherHumidity();
  strcpy(ws2," %");
  if (f==invalid) { strcpy(ws1,"Invalid"); strcpy(ws2,""); } else dtostrf(f,6,1,ws1); 
  strcpy_P(temp1,htmlInnerWeatherHumd); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#endif
#if WEATHER_WIND_SPD == ON
  f=weatherWindspeed(); strcpy(ws2," kph");
  #if STAT_UNITS == IMPERIAL
    f=f*0.621371; strcpy(ws2," mph");
  #endif
  if (f<0) { strcpy(ws2,""); strcpy(ws1,"Invalid"); } else dtostrf(f,6,0,ws1);
  strcpy_P(temp1,htmlInnerWeatherWind); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#endif
#if WEATHER_RAIN == ON
  char rainSensorStr[4][8] = {"Invalid","Rain","Warn","Dry"};
  int i=weatherRain(); if ((i>3) || (i<0)) i=0;
  strcpy_P(temp1,htmlInnerWeatherRain);  sprintf(temp,temp1,rainSensorStr[i]); client->print(temp);
#endif
#if WEATHER_SKY_QUAL == ON
#if WATCHDOG == ON
  if (!blockReset) wdt_reset();
#endif
  f=weatherSkyQuality();
  if (f==invalid) {
    strcpy(ws1,"Invalid"); strcpy(ws2,"");
  } else {
    dtostrf(f,4,1,ws1); strcpy(ws2,"mpsas"); 
  }
  strcpy_P(temp1,htmlInnerWeatherSq); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#endif
#if WEATHER_CLOUD_CVR == ON
  strcpy_P(temp1,htmlInnerWeatherCloud); strcpy(ws1,weatherCloudCoverDescriptionShort().c_str()); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#if WEATHER_RAIN == ON || WEATHER_CLOUD_CVR == ON
  if (isSafe()) {
    strcpy_P(temp,htmlInnerWeatherSafe);  client->print(temp);
    strcpy_P(temp,htmlInnerWeatherSafe1); client->print(temp);
  } else {
    strcpy_P(temp,htmlInnerWeatherUnSafe);  client->print(temp);
    strcpy_P(temp,htmlInnerWeatherUnSafe1); client->print(temp);
  }
#endif
}
#endif

// thermostat ----------------------------------------------------------------------------------------------------------------
#if THERMOSTAT == ON
void thermostat(EthernetClient *client) {
  char temp[80]="";
  char ws1[20]="";
  char ws2[20]="";
  
  double T=thermostatInsideTemp();
  if (T==invalid) {
    strcpy(ws2,"");
    strcpy(ws1,"Invalid");
  } else {
    strcpy(ws2," &deg;C");
#if STAT_UNITS == IMPERIAL
    T=T*(9.0/5.0)+32.0;
    strcpy(ws2," &deg;F");
#endif
    dtostrf(T,6,1,ws1);
  }

#if HEAT_RELAY != OFF
  if (relayIsOn(HEAT_RELAY)) 
  {
    sprintf(temp,"%s%s ^",ws1,ws2); client->print(temp);
  } else
#endif
#if COOL_RELAY != OFF
  if (relayIsOn(COOL_RELAY)) 
  {
    sprintf(temp,"%s%s *",ws1,ws2); client->print(temp);
  } else 
#endif
  {
    sprintf(temp,"%s%s -",ws1,ws2); client->print(temp);
  }
}

#if THERMOSTAT_HUMIDITY == ON
void thermostath(EthernetClient *client) {
  char temp[80]="";
  char ws1[20]="";
  char ws2[20]="";
  
  double H=thermostatInsideHumidity();
  if (H==invalid) {
    strcpy(ws2,"");
    strcpy(ws1,"Invalid");
  } else {
    strcpy(ws2," %");
    dtostrf(H,5,1,ws1);
  }
  sprintf(temp,"%s%s",ws1,ws2); client->print(temp);
}
#endif
#endif

// power ---------------------------------------------------------------------------------------------------------------------
#if POWER == ON
const char htmlPower[] PROGMEM =
"<b>Power</b><br />"
"<form><div>"
#if POWER_DEVICE1_RELAY != OFF
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE1_RELAY) "\",this.checked)' %___PD1 />&nbsp;&nbsp;" POWER_DEVICE1_NAME "<br />"
#endif
#if POWER_DEVICE2_RELAY != OFF
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE2_RELAY) "\",this.checked)' %___PD2 />&nbsp;&nbsp;" POWER_DEVICE2_NAME "<br />"
#endif
#if POWER_DEVICE3_RELAY != OFF
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE3_RELAY) "\",this.checked)' %___PD3 />&nbsp;&nbsp;" POWER_DEVICE3_NAME "<br />"
#endif
#if POWER_DEVICE4_RELAY != OFF
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE4_RELAY) "\",this.checked)' %___PD4 />&nbsp;&nbsp;" POWER_DEVICE4_NAME "<br />"
#endif
#if POWER_DEVICE5_RELAY != OFF
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE5_RELAY) "\",this.checked)' %___PD5 />&nbsp;&nbsp;" POWER_DEVICE5_NAME "<br />"
#endif
#if POWER_DEVICE6_RELAY != OFF
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" STR(POWER_DEVICE6_RELAY) "\",this.checked)' %___PD6 />&nbsp;&nbsp;" POWER_DEVICE6_NAME "<br />"
#endif
"<br />"
"</div></form>";

void power(EthernetClient *client) {
  char temp[800];

  strcpy_P(temp,htmlPower);
  #if POWER_DEVICE1_RELAY != OFF
    if (relayIsOn(POWER_DEVICE1_RELAY)) check(temp,"%___PD1"); else erase(temp,"%___PD1");
  #endif
  #if POWER_DEVICE2_RELAY != OFF
    if (relayIsOn(POWER_DEVICE2_RELAY)) check(temp,"%___PD2"); else erase(temp,"%___PD2");
  #endif
  #if POWER_DEVICE3_RELAY != OFF
    if (relayIsOn(POWER_DEVICE3_RELAY)) check(temp,"%___PD3"); else erase(temp,"%___PD3");
  #endif
  #if POWER_DEVICE4_RELAY != OFF
    if (relayIsOn(POWER_DEVICE4_RELAY)) check(temp,"%___PD4"); else erase(temp,"%___PD4");
  #endif
  #if POWER_DEVICE5_RELAY != OFF
    if (relayIsOn(POWER_DEVICE5_RELAY)) check(temp,"%___PD5"); else erase(temp,"%___PD5");
  #endif
  #if POWER_DEVICE6_RELAY != OFF
    if (relayIsOn(POWER_DEVICE6_RELAY)) check(temp,"%___PD6"); else erase(temp,"%___PD6");
  #endif
  client->print(temp);
}
#endif

// light ---------------------------------------------------------------------------------------------------------------------
#if LIGHT == ON
const char htmlLighting[] PROGMEM =
"<b>Lighting</b><br />"
"<form><div>"
"&nbsp;&nbsp;"
#if LIGHT_WRR_RELAY != OFF
"<input type=\"checkbox\" onclick='SetRelay(\"" STR(LIGHT_WRR_RELAY) "\",this.checked)' %___WRR />&nbsp;Red "
#endif
#if LIGHT_WRW_RELAY != OFF
"<input type=\"checkbox\" onclick='SetRelay(\"" STR(LIGHT_WRW_RELAY) "\",this.checked)' %___WRW />&nbsp;White"
#endif
#if LIGHT_WRR_RELAY != OFF || LIGHT_WRW_RELAY != OFF
" Warm Rm Lights<br />&nbsp;&nbsp;"
#endif
#if LIGHT_ORR_RELAY != OFF
"<input type=\"checkbox\" onclick='SetRelay(\"" STR(LIGHT_ORR_RELAY) "\",this.checked)' %___ORR />&nbsp;Red "
#endif
#if LIGHT_ORW_RELAY != OFF
"<input type=\"checkbox\" onclick='SetRelay(\"" STR(LIGHT_ORW_RELAY) "\",this.checked)' %___ORW />&nbsp;White"
#endif
#if LIGHT_ORR_RELAY != OFF || LIGHT_ORW_RELAY != OFF
" Obs Rm Lights<br />&nbsp;&nbsp;"
#endif
"<br />"
#if LIGHT_OUTSIDE_RELAY != OFF
"<br />"
"&nbsp;&nbsp;<input type=\"button\" onclick='SetVar(\"press\",\"light_exit\")' value=\"Exit\" />&nbsp;&nbsp;Outside Light Timer<br />"
#endif
"</div></form>";

void light(EthernetClient *client) {
  char temp[800];
  
  strcpy_P(temp,htmlLighting);
  #if LIGHT_WRW_RELAY != OFF
    if (relayIsOn(LIGHT_WRW_RELAY)) check(temp,"%___WRW"); else erase(temp,"%___WRW");
  #endif
  #if LIGHT_WRR_RELAY != OFF
    if (relayIsOn(LIGHT_WRR_RELAY)) check(temp,"%___WRR"); else erase(temp,"%___WRR");
  #endif
  #if LIGHT_ORW_RELAY != OFF
    if (relayIsOn(LIGHT_ORW_RELAY)) check(temp,"%___ORW"); else erase(temp,"%___ORW");
  #endif
  #if LIGHT_ORR_RELAY != OFF
    if (relayIsOn(LIGHT_ORR_RELAY)) check(temp,"%___ORR"); else erase(temp,"%___ORR");
  #endif
  client->print(temp);
}
#endif

// roll-off roof -------------------------------------------------------------------------------------------------------------
#if ROR == ON
const char htmlInnerRoofStat[] PROGMEM =
"&nbsp;&nbsp;Status <div class=\"aStatus\">%s</div><br />"
"<div style=\"text-align:center\">%s</div>";

void roofstatus(EthernetClient *client) {
  char temp[200]="";
  char temp1[200]="";
  char ws1[20]="";

  strcpy_P(temp1,htmlInnerRoofStat);
  if (!roofIsMoving()) {
    if (roofIsClosed()) strcpy(ws1,"Closed"); else
    if (roofIsOpened()) strcpy(ws1,"Open"); else strcpy(ws1,"Stopped");
  } else
  if (roofIsOpening()) strcpy(ws1,"Opening"); else
  if (roofIsClosing()) strcpy(ws1,"Closing");

  String s=getRoofStatus();
  if ((s=="No Error") || (s.indexOf("Travel: ")>=0))  s="<div style=\"color: #505090;\">"+s+"</div>"; else s="<div style=\"color: red;\">"+s+"</div>";
  sprintf(temp,temp1,ws1,s.c_str()); client->print(temp);
}
#endif
