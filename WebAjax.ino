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
#ifdef AJAX_RELAY_DEBUG_ON
        Serial.print(s); Serial.println("=on");  
#endif
      }
      if (a=="false") {
        setRelayOff(i); state=(uint8_t)false;
#ifdef AJAX_RELAY_DEBUG_ON
        Serial.print(s); Serial.println("=off"); 
#endif
      }
      
      // if this relay is from the "Power Panel" store the setting if requested
      if ((a=="true") || (a=="false")) {
        #if defined(POWER_DEVICE1_RELAY) && defined(POWER_DEVICE1_MEMORY_ON)
        if (i==atoi(POWER_DEVICE1_RELAY)) EEPROM.write(EE_powerDevice_1,state);
        #endif
        #if defined(POWER_DEVICE2_RELAY) && defined(POWER_DEVICE2_MEMORY_ON)
        if (i==atoi(POWER_DEVICE2_RELAY)) EEPROM.write(EE_powerDevice_2,state);
        #endif
        #if defined(POWER_DEVICE3_RELAY) && defined(POWER_DEVICE3_MEMORY_ON)
        if (i==atoi(POWER_DEVICE3_RELAY)) EEPROM.write(EE_powerDevice_3,state);
        #endif
        #if defined(POWER_DEVICE4_RELAY) && defined(POWER_DEVICE4_MEMORY_ON)
        if (i==atoi(POWER_DEVICE4_RELAY)) EEPROM.write(EE_powerDevice_4,state);
        #endif
        #if defined(POWER_DEVICE5_RELAY) && defined(POWER_DEVICE5_MEMORY_ON)
        if (i==atoi(POWER_DEVICE5_RELAY)) EEPROM.write(EE_powerDevice_5,state);
        #endif
        #if defined(POWER_DEVICE6_RELAY) && defined(POWER_DEVICE6_MEMORY_ON)
        if (i==atoi(POWER_DEVICE6_RELAY)) EEPROM.write(EE_powerDevice_6,state);
        #endif
      }
      if (a=="get") { s=String(relayState[i]); client->print(s); break; }
    }
  }
}

void setvar(EthernetClient *client) {
  String a=www.arg("press");
  
// lights
#ifdef LIGHT_ON
#ifdef LIGHT_OUTSIDE_RELAY
  if (a=="light_exit") { 
    setRelayOnDelayedOff(atoi(LIGHT_OUTSIDE_RELAY),236); // turn off after about 4 minutes
  }
#endif
#endif

// roll-off roof
#ifdef ROR_ON
  if (a=="roof_open") { startRoofOpen(); }
  if (a=="roof_close") { startRoofClose(); }
  if (a=="roof_override") { setRoofSafetyOverride(); }
  if (a=="roof_stop") { stopRoof(); clearRoofStatus(); }
  a=www.arg("auto_close");
  if (a=="true") { roofAutoClose=true; }
  if (a=="false") { roofAutoClose=false; }
#endif

// thermostat
#ifdef THERMOSTAT_ON
#ifdef HEAT_RELAY
  a=www.arg("thermostat_heat");
  if (a!="") {
#ifdef IMPERIAL_UNITS_ON
    float f=0; if (atoi(a.c_str())!=0) f=(float(atoi(a.c_str()))-32.0)*(5.0/9.0);
#else
    float f=atoi(a.c_str());
#endif
    if ((f>=0.0) && (f<=37.0)) setHeatSetpoint(f);
  }
#endif
#ifdef COOL_RELAY
  a=www.arg("thermostat_cool");
  if (a!="") {
#ifdef IMPERIAL_UNITS_ON
    float f=0; if (atoi(a.c_str())!=0) f=(float(atoi(a.c_str()))-32.0)*(5.0/9.0);
#else
    float f=atoi(a.c_str());
#endif
    if ((f>=0.0) && (f<=37.0)) setCoolSetpoint(f);
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
#ifdef STAT_MAINS_SENSE
const char htmlInnerStatusMains[] PROGMEM =
"&nbsp;&nbsp;Mains Power<div class=\"aStatus\">%s</div><br />";
#endif
#ifdef STAT_MAINS_CURRENT_ANALOG
const char htmlInnerStatusMainsA[] PROGMEM =
"&nbsp;&nbsp;Mains Current<div class=\"aStatus\">%s</div><br />";
#endif
#ifdef STAT_MAINS_AUX_CURRENT_ANALOG
const char htmlInnerStatusMainsAA[] PROGMEM =
"&nbsp;&nbsp;Mains Aux Current<div class=\"aStatus\">%s</div><br />";
#endif
#ifdef STAT_DC_PS_ANALOG
const char htmlInnerStatusDC[] PROGMEM =
"&nbsp;&nbsp;DC Power Supply<div class=\"aStatus\">%s</div><br />";
#endif
#ifdef STAT_DC_CURRENT_ANALOG
const char htmlInnerStatusDCA[] PROGMEM =
"&nbsp;&nbsp;DC Current<div class=\"aStatus\">%s</div><br />";
#endif
#ifdef STAT_BATTERY_ANALOG
const char htmlInnerStatusBat[] PROGMEM =
"&nbsp;&nbsp;Battery<div class=\"aStatus\">%s</div><br />";
#endif
#ifdef STAT_BATTERY_CURRENT_ANALOG
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
#ifdef UTC_ON
  t-=timeZone*SECS_PER_HOUR; // UTC
  strcpy(ws2,"UTC");
#elif defined(DST_ON)
  t-=timeZone*SECS_PER_HOUR; // UTC
  if (isDst(year(t),month(t),day(t),hour(t),TimeZone)) {
    t=now()+SECS_PER_HOUR;   // +1 hour, Daylight Time
    strcpy(ws2,"Dst");
  } else t=now();
#endif

  strcpy_P(temp1,htmlInnerStatus2); sprintf(ws1,"%02d/%02d/%04d",month(t),day(t),year(t)); sprintf(temp,temp1,ws2,ws1); client->print(temp);
  strcpy_P(temp1,htmlInnerStatus3); sprintf(ws1,"%02d:%02d",hour(t),minute(t)); sprintf(temp,temp1,ws2,ws1); client->print(temp);
  t=(now()-startupTime);
  strcpy_P(temp1,htmlInnerStatus4); sprintf(ws1,"%08lu",(unsigned long)(t/60UL)); sprintf(temp,temp1,ws1); client->print(temp);
#ifdef STAT_MAINS_SENSE
  strcpy_P(temp1,htmlInnerStatusMains);  if (senseIsOn(STAT_MAINS_SENSE)) strcpy(ws1,"GOOD"); else strcpy(ws1,"OUT"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#ifdef STAT_MAINS_CURRENT_ANALOG
  f=toAmps(analogRead(STAT_MAINS_CURRENT_ANALOG));
  strcpy_P(temp1,htmlInnerStatusMainsA);  dtostrf(f,6,1,ws1); strcat(ws1,"A"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#ifdef STAT_MAINS_AUX_CURRENT_ANALOG
  f=toAmps(analogRead(STAT_MAINS_AUX_CURRENT_ANALOG));
  strcpy_P(temp1,htmlInnerStatusMainsAA); dtostrf(f,6,1,ws1); strcat(ws1,"A"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#ifdef STAT_DC_PS_ANALOG
  f=toDC(analogRead(STAT_DC_PS_ANALOG));
  strcpy_P(temp1,htmlInnerStatusDC);      dtostrf(f,6,1,ws1); strcat(ws1,"V"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#ifdef STAT_DC_CURRENT_ANALOG
  f=toDCAmps(analogRead(STAT_DC_CURRENT_ANALOG));
  strcpy_P(temp1,htmlInnerStatusDCA);     dtostrf(f,6,1,ws1); strcat(ws1,"A"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#ifdef STAT_BATTERY_ANALOG
  f=toDC(analogRead(STAT_BATTERY_ANALOG));
  strcpy_P(temp1,htmlInnerStatusBat);     dtostrf(f,6,1,ws1); strcat(ws1,"V"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#ifdef STAT_BATTERY_CURRENT_ANALOG
  f=toDCAmps(analogRead(STAT_BATTERY_CURRENT_ANALOG));
  strcpy_P(temp1,htmlInnerStatusBatA);    dtostrf(f,6,1,ws1); strcat(ws1,"A"); if (f==invalid) strcpy(ws1,"Invalid"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
}

// weather -------------------------------------------------------------------------------------------------------------------
#ifdef WEATHER_ON
const char htmlInnerWeather1[] PROGMEM =
"<b>Weather</b><br />";
#ifdef WEATHER_OUT_TEMP_ON
const char htmlInnerWeatherTemp[] PROGMEM =
"&nbsp;&nbsp;Temperature (Outside)<div class=\"aStatus\">%s%s</div><br />";
#endif
#ifdef WEATHER_PRESSURE_ON
const char htmlInnerWeatherPres[] PROGMEM =
"&nbsp;&nbsp;Barometric Pressure<div class=\"aStatus\">%s%s</div><br />";
#endif
#ifdef WEATHER_HUMIDITY_ON
const char htmlInnerWeatherHumd[] PROGMEM =
"&nbsp;&nbsp;Relative Humidity<div class=\"aStatus\">%s%s</div><br />";
#endif
#ifdef WEATHER_WIND_SPD_ON
const char htmlInnerWeatherWind[] PROGMEM =
"&nbsp;&nbsp;Wind Speed<div class=\"aStatus\">%s%s</div><br />";
#endif
#ifdef WEATHER_RAIN_ON
const char htmlInnerWeatherRain[] PROGMEM =
"&nbsp;&nbsp;Rain sensor<div class=\"aStatus\">%s</div><br />";
#endif
#ifdef WEATHER_SKY_QUAL_ON
const char htmlInnerWeatherSq[] PROGMEM =
"&nbsp;&nbsp;Sky Quality<div class=\"aStatus\">%s%s</div><br />";
#endif
#ifdef WEATHER_CLOUD_CVR_ON
const char htmlInnerWeatherCloud[] PROGMEM =
"&nbsp;&nbsp;Sky Conditions<div class=\"aStatus\">%s</div><br />";
#endif
#if defined(WEATHER_RAIN_ON) || defined(WEATHER_CLOUD_CVR_ON) || defined(WEATHER_WIND_SPD_ON) || defined(STAT_MAINS_SENSE)
const char htmlInnerWeatherSafe[] PROGMEM =
"<div style=\"position: absolute; bottom: 5px; left: 120px; text-align:center\";><div style=\"display:inline-block; ";
const char htmlInnerWeatherSafe1[] PROGMEM =
"background-color: #bcccbc; color: green; border:1px solid green; padding: 4px 4px;\">SAFE</div></div><br />";
#endif
#if defined(WEATHER_RAIN_ON) || defined(WEATHER_CLOUD_CVR_ON) || defined(WEATHER_WIND_SPD_ON) || defined(STAT_MAINS_SENSE)
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
#ifdef WEATHER_OUT_TEMP_ON
  f=weatherOutsideTemp(); strcpy(ws2," &deg;C");
#ifdef IMPERIAL_UNITS_ON
  f=f*(9.0/5.0)+32.0; strcpy(ws2," &deg;F");
#endif
  if (f<-200) { strcpy(ws1,"Invalid"); strcpy(ws2,""); } else dtostrf(f,5,1,ws1);
  strcpy_P(temp1,htmlInnerWeatherTemp); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#endif
#ifdef WEATHER_PRESSURE_ON
#ifdef IMPERIAL_UNITS_ON
  f=weatherPressureSeaLevel()*0.02953; strcpy(ws2," in");
  if (f==invalid) { strcpy(ws1,"Invalid"); strcpy(ws2,""); } else dtostrf(f,6,2,ws1);
#else
  f=weatherPressureSeaLevel(); strcpy(ws2," mb");
  if (f==invalid) { strcpy(ws1,"Invalid"); strcpy(ws2,""); } else dtostrf(f,6,0,ws1);
#endif
  strcpy_P(temp1,htmlInnerWeatherPres); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#endif
#ifdef WEATHER_HUMIDITY_ON
  f=weatherHumidity();
  strcpy(ws2," %");
  if (f==invalid) { strcpy(ws1,"Invalid"); strcpy(ws2,""); } else dtostrf(f,6,1,ws1); 
  strcpy_P(temp1,htmlInnerWeatherHumd); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#endif
#ifdef WEATHER_WIND_SPD_ON
  f=weatherWindspeed(); strcpy(ws2," kph");
#ifdef IMPERIAL_UNITS_ON
  f=f*0.621371; strcpy(ws2," mph");
#endif
  if (f<0) { strcpy(ws2,""); strcpy(ws1,"Invalid"); } else dtostrf(f,6,0,ws1);
  strcpy_P(temp1,htmlInnerWeatherWind); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#endif
#ifdef WEATHER_RAIN_ON
  char rainSensorStr[4][8] = {"Invalid","Rain","Warn","Dry"};
  int i=weatherRain(); if ((i>3) || (i<0)) i=0;
  strcpy_P(temp1,htmlInnerWeatherRain);  sprintf(temp,temp1,rainSensorStr[i]); client->print(temp);
#endif
#ifdef WEATHER_SKY_QUAL_ON
  f=weatherSkyQuality();
  if (f==invalid) {
    strcpy(ws1,"Invalid"); strcpy(ws2,"");
  } else {
    dtostrf(weatherSkyQuality(),5,2,ws1); strcpy(ws2," m\"^2"); 
  }
  strcpy_P(temp1,htmlInnerWeatherSq); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#endif
#ifdef WEATHER_CLOUD_CVR_ON
  strcpy_P(temp1,htmlInnerWeatherCloud); strcpy(ws1,weatherCloudCoverDescriptionShort().c_str()); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#if defined(WEATHER_RAIN_ON) || defined(WEATHER_CLOUD_CVR_ON)
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
#ifdef THERMOSTAT_ON
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
#ifdef IMPERIAL_UNITS_ON
    T=T*(9.0/5.0)+32.0;
    strcpy(ws2," &deg;F");
#endif
    dtostrf(T,6,1,ws1);
  }

#ifdef HEAT_RELAY
  if (relayIsOn(HEAT_RELAY)) 
  {
    sprintf(temp,"%s%s ^",ws1,ws2); client->print(temp);
  } else
#endif
#ifdef COOL_RELAY
  if (relayIsOn(COOL_RELAY)) 
  {
    sprintf(temp,"%s%s *",ws1,ws2); client->print(temp);
  } else 
#endif
  {
    sprintf(temp,"%s%s -",ws1,ws2); client->print(temp);
  }
}

#ifdef THERMOSTAT_HUMIDITY_ON
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
#ifdef POWER_ON
const char htmlPower[] PROGMEM =
"<b>Power</b><br />"
"<form><div>"
#ifdef POWER_DEVICE1_RELAY
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" POWER_DEVICE1_RELAY "\",this.checked)' %___PD1 />&nbsp;&nbsp;" POWER_DEVICE1_NAME "<br />"
#endif
#ifdef POWER_DEVICE2_RELAY
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" POWER_DEVICE2_RELAY "\",this.checked)' %___PD2 />&nbsp;&nbsp;" POWER_DEVICE2_NAME "<br />"
#endif
#ifdef POWER_DEVICE3_RELAY
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" POWER_DEVICE3_RELAY "\",this.checked)' %___PD3 />&nbsp;&nbsp;" POWER_DEVICE3_NAME "<br />"
#endif
#ifdef POWER_DEVICE4_RELAY
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" POWER_DEVICE4_RELAY "\",this.checked)' %___PD4 />&nbsp;&nbsp;" POWER_DEVICE4_NAME "<br />"
#endif
#ifdef POWER_DEVICE5_RELAY
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" POWER_DEVICE5_RELAY "\",this.checked)' %___PD5 />&nbsp;&nbsp;" POWER_DEVICE5_NAME "<br />"
#endif
#ifdef POWER_DEVICE6_RELAY
"&nbsp;&nbsp;<input type=\"checkbox\" onclick='SetRelay(\"" POWER_DEVICE6_RELAY "\",this.checked)' %___PD6 />&nbsp;&nbsp;" POWER_DEVICE6_NAME "<br />"
#endif
"<br />"
"</div></form>";

void power(EthernetClient *client) {
  char temp[800];

  strcpy_P(temp,htmlPower);
  #ifdef POWER_DEVICE1_RELAY
  if (relayIsOn(POWER_DEVICE1_RELAY)) check(temp,"%___PD1"); else erase(temp,"%___PD1");
  #endif
  #ifdef POWER_DEVICE2_RELAY
  if (relayIsOn(POWER_DEVICE2_RELAY)) check(temp,"%___PD2"); else erase(temp,"%___PD2");
  #endif
  #ifdef POWER_DEVICE3_RELAY
  if (relayIsOn(POWER_DEVICE3_RELAY)) check(temp,"%___PD3"); else erase(temp,"%___PD3");
  #endif
  #ifdef POWER_DEVICE4_RELAY
  if (relayIsOn(POWER_DEVICE4_RELAY)) check(temp,"%___PD4"); else erase(temp,"%___PD4");
  #endif
  #ifdef POWER_DEVICE5_RELAY
  if (relayIsOn(POWER_DEVICE5_RELAY)) check(temp,"%___PD5"); else erase(temp,"%___PD5");
  #endif
  #ifdef POWER_DEVICE6_RELAY
  if (relayIsOn(POWER_DEVICE6_RELAY)) check(temp,"%___PD6"); else erase(temp,"%___PD6");
  #endif
  client->print(temp);
}
#endif

// light ---------------------------------------------------------------------------------------------------------------------
#ifdef LIGHT_ON
const char htmlLighting[] PROGMEM =
"<b>Lighting</b><br />"
"<form><div>"
"&nbsp;&nbsp;"
#ifdef LIGHT_WRR_RELAY
"<input type=\"checkbox\" onclick='SetRelay(\"" LIGHT_WRR_RELAY "\",this.checked)' %___WRR />&nbsp;Red"
#endif
#ifdef LIGHT_WRW_RELAY
" <input type=\"checkbox\" onclick='SetRelay(\"" LIGHT_WRW_RELAY "\",this.checked)' %___WRW />&nbsp;White"
#endif
" Warm Rm Lights<br />&nbsp;&nbsp;"
#ifdef LIGHT_ORR_RELAY
"<input type=\"checkbox\" onclick='SetRelay(\"" LIGHT_ORR_RELAY "\",this.checked)' %___ORR />&nbsp;Red"
#endif
#ifdef LIGHT_ORW_RELAY
" <input type=\"checkbox\" onclick='SetRelay(\"" LIGHT_ORW_RELAY "\",this.checked)' %___ORW />&nbsp;White"
#endif
" Obs Rm Lights<br />&nbsp;&nbsp;"
"<br /><br />"
"&nbsp;&nbsp;<input type=\"button\" onclick='SetVar(\"press\",\"light_exit\")' value=\"Exit\" />&nbsp;&nbsp;Outside Light Timer<br />"
"</div></form>";

void light(EthernetClient *client) {
  char temp[800];
  
  strcpy_P(temp,htmlLighting);
  #ifdef LIGHT_WRW_RELAY
  if (relayIsOn(LIGHT_WRW_RELAY)) check(temp,"%___WRW"); else erase(temp,"%___WRW");
  #endif
  #ifdef LIGHT_WRR_RELAY
  if (relayIsOn(LIGHT_WRR_RELAY)) check(temp,"%___WRR"); else erase(temp,"%___WRR");
  #endif
  #ifdef LIGHT_ORW_RELAY
  if (relayIsOn(LIGHT_ORW_RELAY)) check(temp,"%___ORW"); else erase(temp,"%___ORW");
  #endif
  #ifdef LIGHT_ORR_RELAY
  if (relayIsOn(LIGHT_ORR_RELAY)) check(temp,"%___ORR"); else erase(temp,"%___ORR");
  #endif
  client->print(temp);
}
#endif

// roll-off roof -------------------------------------------------------------------------------------------------------------
#ifdef ROR_ON
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
