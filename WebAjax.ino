// -----------------------------------------------------------------------------------
// Web server, Ajax Pages

void relay(EthernetClient *client) {
  for (int i=1; i<=14; i++) {
    String s="r"+String(i);
    String a=www.arg(s);
    byte state=0;
    if (a!="") {
      if (a=="true") {
        relayState[i]=1; digitalWrite(relayPin[i],HIGH); state=HIGH;
#ifdef AJAX_RELAY_DEBUG_ON
        Serial.print(s); Serial.println("=on");  
#endif
      }
      if (a=="false") {
        relayState[i]=0; digitalWrite(relayPin[i],LOW); state=LOW;
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
  
#ifdef LIGHT_ON
#ifdef LIGHT_OUTSIDE_RELAY
  if (a=="light_exit") { relayState[atoi(LIGHT_OUTSIDE_RELAY)]=5; digitalWrite(relayPin[atoi(LIGHT_OUTSIDE_RELAY)],HIGH); }
#endif
#endif


#ifdef ROR_ON
  if (a=="roof_open") { startRoofOpen(); }
  if (a=="roof_close") { startRoofClose(); }
  if (a=="roof_override") { roofSafetyOverride=true; }
  if (a=="roof_stop") { stopRoof(); }
  a=www.arg("auto_close");
  if (a=="true") { roofAutoClose=true; }
  if (a=="false") { roofAutoClose=false; }
#endif

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
"&nbsp;&nbsp;Date (Std Time)<div class=\"aStatus\">%s</div><br />";
const char htmlInnerStatus3[] PROGMEM =
"&nbsp;&nbsp;Time (Std Time)<div class=\"aStatus\">%s</div><br />";
const char htmlInnerStatus4[] PROGMEM =
"&nbsp;&nbsp;Up Time (Minutes)<div class=\"aStatus\">%s</div><br /><br />";
#ifdef STAT_MAINS_SENSE
const char htmlInnerStatus5[] PROGMEM =
"&nbsp;&nbsp;Mains Power<div class=\"aStatus\">%s</div><br />";
#endif
#ifdef STAT_12V_PS_ANALOG
const char htmlInnerStatus6[] PROGMEM =
"&nbsp;&nbsp;Low Voltage Power Supply<div class=\"aStatus\">%sV</div><br />";
#endif
#ifdef STAT_12V_BAT_ANALOG
const char htmlInnerStatus7[] PROGMEM =
"&nbsp;&nbsp;Roof Battery<div class=\"aStatus\">%sV</div><br />";
#endif

void ocsstatus(EthernetClient *client) {
  char temp[128]="";
  char temp1[128]="";
  char ws1[20]="";

  strcpy_P(temp,htmlInnerStatus1); client->print(temp);
  time_t t=now();
  strcpy_P(temp1,htmlInnerStatus2); sprintf(ws1,"%02d/%02d/%04d",month(t),day(t),year(t)); sprintf(temp,temp1,ws1); client->print(temp);
  strcpy_P(temp1,htmlInnerStatus3); sprintf(ws1,"%02d:%02d",hour(t),minute(t)); sprintf(temp,temp1,ws1); client->print(temp);
  t=(now()-startupTime);
  strcpy_P(temp1,htmlInnerStatus4); sprintf(ws1,"%08lu",(unsigned long)(t/60UL)); sprintf(temp,temp1,ws1); client->print(temp);
#ifdef STAT_MAINS_SENSE
  strcpy_P(temp1,htmlInnerStatus5); if (digitalRead(sensePin[STAT_MAINS_SENSE])==HIGH) strcpy(ws1,"GOOD"); else strcpy(ws1,"OUT"); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#ifdef STAT_12V_PS_ANALOG
  strcpy_P(temp1,htmlInnerStatus6); dtostrf(to12V(analogRead(STAT_12V_PS_ANALOG)),6,1,ws1); sprintf(temp,temp1,ws1); client->print(temp);
#endif
#ifdef STAT_12V_BAT_ANALOG
  strcpy_P(temp1,htmlInnerStatus7); dtostrf(to12V(analogRead(STAT_12V_BAT_ANALOG)),6,1,ws1); sprintf(temp,temp1,ws1); client->print(temp);
#endif
}

double to12V(double d) {
  d=(d/245.76)*12.0;  // For a voltage divider 12V/10: (1024*1.2)/5=245.76 
  return d;
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
  f=weatherPressure();
  strcpy(ws2," mb");
  if (f==invalid) { strcpy(ws1,"Invalid"); strcpy(ws2,""); } else dtostrf(f,6,0,ws1);
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
  f=f/0.621371; strcpy(ws2," mph");
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
  if (relayOn(POWER_DEVICE1_RELAY)) check(temp,"%___PD1"); else erase(temp,"%___PD1");
  #endif
  #ifdef POWER_DEVICE2_RELAY
  if (relayOn(POWER_DEVICE2_RELAY)) check(temp,"%___PD2"); else erase(temp,"%___PD2");
  #endif
  #ifdef POWER_DEVICE3_RELAY
  if (relayOn(POWER_DEVICE3_RELAY)) check(temp,"%___PD3"); else erase(temp,"%___PD3");
  #endif
  #ifdef POWER_DEVICE4_RELAY
  if (relayOn(POWER_DEVICE4_RELAY)) check(temp,"%___PD4"); else erase(temp,"%___PD4");
  #endif
  #ifdef POWER_DEVICE5_RELAY
  if (relayOn(POWER_DEVICE5_RELAY)) check(temp,"%___PD5"); else erase(temp,"%___PD5");
  #endif
  #ifdef POWER_DEVICE6_RELAY
  if (relayOn(POWER_DEVICE6_RELAY)) check(temp,"%___PD6"); else erase(temp,"%___PD6");
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
  if (relayOn(LIGHT_WRW_RELAY)) check(temp,"%___WRW"); else erase(temp,"%___WRW");
  #endif
  #ifdef LIGHT_WRR_RELAY
  if (relayOn(LIGHT_WRR_RELAY)) check(temp,"%___WRR"); else erase(temp,"%___WRR");
  #endif
  #ifdef LIGHT_ORW_RELAY
  if (relayOn(LIGHT_ORW_RELAY)) check(temp,"%___ORW"); else erase(temp,"%___ORW");
  #endif
  #ifdef LIGHT_ORR_RELAY
  if (relayOn(LIGHT_ORR_RELAY)) check(temp,"%___ORR"); else erase(temp,"%___ORR");
  #endif
  client->print(temp);
}
#endif

// roll-off roof -------------------------------------------------------------------------------------------------------------
#ifdef ROR_ON
const char htmlInnerRoofStat[] PROGMEM =
"&nbsp;&nbsp;Status <div class=\"aStatus\">%s</div><br />"
"<div style=\"text-align:center\">%s</div>";

void roof_stat(EthernetClient *client) {
  char temp[200]="";
  char temp1[200]="";
  char ws1[20]="";

  strcpy_P(temp1,htmlInnerRoofStat);
  if (roofState=='i') {
    if ((digitalRead(sensePin[ROR_CLOSED_LIMIT_SENSE])==HIGH) && (digitalRead(sensePin[ROR_OPENED_LIMIT_SENSE])==LOW)) strcpy(ws1,"Closed"); else
    if ((digitalRead(sensePin[ROR_OPENED_LIMIT_SENSE])==HIGH) && (digitalRead(sensePin[ROR_CLOSED_LIMIT_SENSE])==LOW)) strcpy(ws1,"Open"); else strcpy(ws1,"Stopped");
  }
  if (roofState=='o') strcpy(ws1,"Opening");
  if (roofState=='c') strcpy(ws1,"Closing");

  String s=getRoofStatus();
  if ((s=="No Error") || (s.indexOf("Travel: ")>=0))  s="<div style=\"color: #505090;\">"+s+"</div>"; else s="<div style=\"color: red;\">"+s+"</div>";
  sprintf(temp,temp1,ws1,s.c_str()); client->print(temp);
}
#endif

