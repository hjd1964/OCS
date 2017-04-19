// -----------------------------------------------------------------------------------
// Web server, Index page

const char htmlStatus1[] PROGMEM =
"<div id=\"Status\" class=\"obsControl\">";
const char htmlStatus3[] PROGMEM =
"</div>\r\n";

const char htmlWeather1[] PROGMEM =
"<div id=\"Weather\" class=\"obsControl\" >";
const char htmlWeather3[] PROGMEM =
"</div>\r\n";

const char htmlPower1[] PROGMEM =
"<div id=\"Power\" class=\"obsControl\" >";
const char htmlPower3[] PROGMEM =
"</div>\r\n";

const char htmlThermostat1[] PROGMEM =
"<div class=\"obsControl\">"
"<b>Thermostat</b><br />"
"&nbsp;&nbsp;Temperature (Inside)<div id=\"Thermostat\" class=\"aStatus\">%s%s</div><br /><br />"
"<form name=\"thermostat\" >";
const char htmlThermostatHeat1[] PROGMEM =
"<div>"
"&nbsp;&nbsp;&nbsp;Heat <span id=\"HeatStatus\"></span>"
"<select style=\"float:right; margin-right:20px\" onchange='SetVar(\"thermostat_heat\",value)' >";
const char htmlThermostatHeat2[] PROGMEM =
"</select>"
"</div>"
"<br />";
const char htmlThermostatCool1[] PROGMEM =
"<div>"
"&nbsp;&nbsp;&nbsp;Cool/Venting"
"<select style=\"float:right; margin-right:20px\" onchange='SetVar(\"thermostat_cool\",value)' >";
const char htmlThermostatCool2[] PROGMEM =
"</select>&nbsp;&nbsp;&nbsp;&nbsp;"
"</div>";
const char htmlThermostat2[] PROGMEM =
"</form>"
"</div>\r\n";

const char htmlLight1[] PROGMEM =
"<div id=\"Light\" class=\"obsControl\" >";
const char htmlLight3[] PROGMEM =
"</div>\r\n";

const char htmlRoof1[] PROGMEM =
"<div id=\"Roof\" class=\"obsControl\">"
"<b>Roof or Shutter</b><br />"
"<div id=\"RoofStatus\" style=\"overflow:hidden;\">";
const char htmlRoof2[] PROGMEM =
"</div>"
"<div style=\"text-align: center\">"
"<br />"
"<input type=\"button\" onclick='SetVar(\"press\",\"roof_stop\")' value=\"Stop!\" />&nbsp;&nbsp;&nbsp;"
"<input type=\"button\" onclick='SetVar(\"press\",\"roof_override\")' value=\"Safety Override\" />"
"<br />"
"<input type=\"button\" onclick='SetVar(\"press\",\"roof_open\")' value=\"Open Roof\" />&nbsp;&nbsp;&nbsp;"
"<input type=\"button\" onclick='SetVar(\"press\",\"roof_close\")' value=\"Close Roof\" /><br />"
"<br />"
#ifdef ROR_AUTOCLOSE_DAWN_ON
"<input type=\"checkbox\"  onclick='SetVar(\"auto_close\",this.checked)' %___ACL />&nbsp;Automatically close at dawn<br />"
#endif
"</div>\r\n";

// Javascript for Ajax
const char html_ajax_active1[] PROGMEM = 
"<script>"
"var autoStatus=setInterval(Status,10000);"
"function Status() {"
" nocache='?nocache='+Math.random()*1000000;"
" var request = new XMLHttpRequest();"
" request.onreadystatechange = function() {"
" if ((this.readyState==4)&&(this.status==200)) {document.getElementById('Status').innerHTML=this.responseText;}};"
" request.open('GET','status'+nocache,true); request.send(null);}";
const char html_ajax_active2[] PROGMEM = 
#ifdef WEATHER_ON
"var autoWeather=setInterval(Weather,30000);"
"function Weather() {"
" nocache='?nocache='+Math.random()*1000000;"
" var request = new XMLHttpRequest();"
" request.onreadystatechange = function() {"
" if ((this.readyState==4)&&(this.status==200)) {document.getElementById('Weather').innerHTML=this.responseText;}};"
" request.open('GET','weather'+nocache,true); request.send(null);}";
#else
"";
#endif
const char html_ajax_active3[] PROGMEM = 
#ifdef THERMOSTAT_ON
"var autoTS=setInterval(InsideTemp,30000);"
"function InsideTemp() {"
" nocache='?nocache='+Math.random()*1000000;"
" var request = new XMLHttpRequest();"
" request.onreadystatechange = function() {"
" if ((this.readyState==4)&&(this.status==200)) {document.getElementById('Thermostat').innerHTML=this.responseText;}};"
" request.open('GET','thermostat'+nocache,true); request.send(null);}";
#else
"";
#endif
const char html_ajax_active4[] PROGMEM = 
#ifdef ROR_ON
"var autoRoofStat = setInterval(RoofStatus,2000);"
"function RoofStatus() {"
" nocache='?nocache='+Math.random()*1000000;"
" var request = new XMLHttpRequest();"
" request.onreadystatechange = function() {"
" if ((this.readyState==4)&&(this.status==200)) {document.getElementById('RoofStatus').innerHTML=this.responseText;}};"
" request.open('GET','roof_stat'+nocache,true); request.send(null);}"
"</script>\r\n";
#else
"</script>\r\n";
#endif
const char html_ajax_setRelay[] PROGMEM = 
"<script>function SetRelay(relay,value) {"
" nocache = '&nocache=' + Math.random() * 1000000;"
" var request = new XMLHttpRequest();"
" request.open('GET','relay?r'+relay+'='+value+nocache,true);"
" request.send(null);"
"}</script>";
const char html_ajax_setVar[] PROGMEM = 
"<script>function SetVar(name,value) {"
" nocache = '&nocache=' + Math.random() * 1000000;"
" var request = new XMLHttpRequest();"
" request.open('GET','setvar?'+name+'='+value+nocache,true);"
" request.send(null);"
"}</script>\r\n";

void index(EthernetClient *client) {
  char temp[800]="";
  
  // send a standard http response header with some css
  strcpy_P(temp,html_head1); client->print(temp);
  strcpy_P(temp,html_main_css1); client->print(temp); 
  strcpy_P(temp,html_main_css2); client->print(temp);
  strcpy_P(temp,html_main_css4); client->print(temp);
  strcpy_P(temp,html_main_css6); client->print(temp);
  strcpy_P(temp,html_main_css7); client->print(temp);
  strcpy_P(temp,html_main_css8); client->print(temp);
  strcpy_P(temp,html_main_css10); client->print(temp);

  strcpy_P(temp,html_head3); client->print(temp);

  strcpy_P(temp,html_pageHeader1); client->print(temp);
  strcpy_P(temp,html_pageHeader2); client->print(temp);
  strcpy_P(temp,html_links1s); client->print(temp);
#if defined(WEATHER_ON) && defined(SD_CARD_ON)
  strcpy_P(temp,html_links2); client->print(temp);
#if defined(WEATHER_SKY_QUAL_ON) || defined(WEATHER_CLOUD_CVR_ON)
  strcpy_P(temp,html_links3); client->print(temp);
#endif
#endif
  strcpy_P(temp,html_pageHeader3); client->print(temp);

  // Status
  strcpy_P(temp,htmlStatus1); client->print(temp);
  ocsstatus(client);
  strcpy_P(temp,htmlStatus3); client->print(temp);

#ifdef WEATHER_ON
  strcpy_P(temp,htmlWeather1); client->print(temp);
  weather(client);
  strcpy_P(temp,htmlWeather3); client->print(temp);
#endif

#ifdef POWER_ON
  strcpy_P(temp,htmlPower1); client->print(temp);
  power(client);
  strcpy_P(temp,htmlPower3); client->print(temp);
#endif

#ifdef THERMOSTAT_ON
  {
    char temp1[255]="";
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
    strcpy_P(temp1,htmlThermostat1); sprintf(temp,temp1,ws1,ws2); client->print(temp);
#ifdef HEAT_RELAY
    strcpy_P(temp,htmlThermostatHeat1); client->print(temp);
#ifdef IMPERIAL_UNITS_ON
    int h=round(getHeatSetpoint()*(9.0/5.0)+32.0);
    if (getHeatSetpoint()==0) h=0;
#else
    int h=round(getHeatSetpoint());
#endif
    strcpy(temp1,"<option value=\"0\" %s>OFF</option>");
    if (h==0) strcpy(ws1,"selected"); else strcpy(ws1,"");
    sprintf(temp,temp1,ws1); client->print(temp);
#ifdef IMPERIAL_UNITS_ON
    strcpy(temp1,"<option value=\"%d\" %s>%d&deg;F</option>");
    int hs[11]={40,50,60,65,67,68,69,70,71,72,73};
#else
    strcpy(temp1,"<option value=\"%d\" %s>%d&deg;C</option>");
    int hs[11]={5,10,15,17,18,19,20,21,22,23,24};
#endif
    for (int i=0; i<11; i++) {
      if (h==hs[i]) strcpy(ws1,"selected"); else strcpy(ws1,"");
      sprintf(temp,temp1,hs[i],ws1,hs[i]); client->print(temp);
    }
    strcpy_P(temp,htmlThermostatHeat2); client->print(temp);
#endif
#ifdef COOL_RELAY
    strcpy_P(temp,htmlThermostatCool1); client->print(temp);
#ifdef IMPERIAL_UNITS_ON
    int c=round(getCeatSetpoint()*(9.0/5.0)+32.0);
    if (getCoolSetpoint()==0) c=0;
#else
    int c=round(getCoolSetpoint());
#endif
    strcpy(temp1,"<option value=\"0\" %s>OFF</option>");
    if (c==0) strcpy(ws1,"selected"); else strcpy(ws1,"");
    sprintf(temp,temp1,ws1); client->print(temp);
#ifdef IMPERIAL_UNITS_ON
    strcpy(temp1,"<option value=\"%d\" %s>%d&deg;F</option>");
    int cs[10]={68,69,70,71,72,73,75,80,90,99};
#else
    strcpy(temp1,"<option value=\"%d\" %s>%d&deg;C</option>");
    int cs[10]={20,21,22,23,24,26,28,30,32,37};
#endif
    for (int i=0; i<10; i++) {
      if (c==cs[i]) strcpy(ws1,"selected"); else strcpy(ws1,"");
      sprintf(temp,temp1,cs[i],ws1,cs[i]); client->print(temp);
    }
    strcpy_P(temp,htmlThermostatCool2); client->print(temp);
#endif
    strcpy_P(temp,htmlThermostat2); client->print(temp);
  }
#endif

#ifdef LIGHT_ON
  strcpy_P(temp,htmlLight1); client->print(temp);
  light(client);
  strcpy_P(temp,htmlLight3); client->print(temp);
#endif

#ifdef ROR_ON
  strcpy_P(temp,htmlRoof1); client->print(temp);
  roof_stat(client);
  strcpy_P(temp,htmlRoof2);
#ifdef ROR_AUTOCLOSE_DAWN_ON
  if (roofAutoClose) check(temp,"%___ACL"); else erase(temp,"%___ACL");
#endif
  client->print(temp);
#endif

  client->print("</div>\r\n");
  
  // javascript for ajax relay control
  strcpy_P(temp,html_ajax_active1); client->print(temp);
  strcpy_P(temp,html_ajax_active2); client->print(temp);
  strcpy_P(temp,html_ajax_active3); client->print(temp);
  strcpy_P(temp,html_ajax_active4); client->print(temp);
  strcpy_P(temp,html_ajax_setRelay); client->print(temp);
  strcpy_P(temp,html_ajax_setVar); client->print(temp);

  client->print("</body></html>\r\n");
}

void check(char ss[], char rs[]) {
  char *w=strstr(ss,rs); if (w!=NULL) { w[0]='c'; w[1]='h'; w[2]='e'; w[3]='c'; w[4]='k'; w[5]='e'; w[6]='d'; }
}

void erase(char ss[], char rs[]) {
  char *w=strstr(ss,rs); if (w!=NULL) { w[0]=' '; w[1]=' '; w[2]=' '; w[3]=' '; w[4]=' '; w[5]=' '; w[6]=' '; }
}

