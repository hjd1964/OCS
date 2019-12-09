// -----------------------------------------------------------------------------------
// Web server, Weather charts

#if defined(WEATHER_ON) && defined(SD_CARD_ON)
#define WEATHER_NOMINAL_PRESSURE_SEA_LEVEL 1013.25  // in mb

const char ChartJs1[] PROGMEM =
"ctx%s=document.getElementById(\"%s\");"
"var scatterChart = new Chart(ctx%s, {"
"type: 'line',"
  "data: {"
    "datasets: [{"
      "label: '";
const char ChartJs3[] PROGMEM = "',"
      "backgroundColor: \"rgba(192,32,32,0.4)\","
      "data: [";
const char ChartJs4[] PROGMEM = 
      "]"
    "}]"
  "},"
  "options: {"
    "scales: {"
      "xAxes: [{"
        "type: 'linear',"
        "position: 'bottom'"
      "}],"
      "yAxes: [{"
        "ticks: {"
          "max: %d,"
          "min: %d,"
          "stepSize: %d"
        "}"
      "}]"
    "}"
  "}"
"});\n";

const char ChartOptions1a[] PROGMEM = 
"<form method=\"get\" action=\"/weatherpage.htm\">";
const char ChartOptions1b[] PROGMEM = 
"<form method=\"get\" action=\"/skypage.htm\">";
const char ChartOptions2[] PROGMEM = 
"<button name=\"chart\" value=\"recent\" type=\"submit\">Recent</button>"
"<button name=\"chart\" value=\"last24\" type=\"submit\">Last 24 Hours</button>"
"<button name=\"chart\" value=\"last48\" type=\"submit\">Last 48 Hours</button>"
"</form>";

void weatherPage(EthernetClient *client) {
  char temp[512]="";
  String a=www.arg("chart");
  
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
  strcpy_P(temp,html_links1);  client->print(temp);
  strcpy_P(temp,html_links2s); client->print(temp);
#if defined(WEATHER_SKY_QUAL_ON) || defined(WEATHER_CLOUD_CVR_ON)
  strcpy_P(temp,html_links3);  client->print(temp);
#endif
  strcpy_P(temp,html_pageHeader3); client->print(temp);

  int period=1;
  String periodStr="";
  if ((a=="recent") || (a=="")) { period=1; periodStr="60 minutes"; }
  if (a=="last24") { period=24; periodStr="24 hours"; }
  if (a=="last48") { period=48; periodStr="48 hours"; }
  
  client->print(F("<script type=\"text/javascript\" src=\"Chart.js\"></script>\r\n"));
  client->print(F("<script>\r\n"));
  client->print(F("window.onload = function(){\r\n"));
#ifdef WEATHER_OUT_TEMP_ON
  #ifdef  IMPERIAL_UNITS_ON
    // a negative column# means this is a temperature and needs conversion to degrees F
    makeChartJs(client,"ambientT","Outside Temperature F (last "+periodStr+")",-8,5,-40,120,20,period);
  #else
    makeChartJs(client,"ambientT","Outside Temperature C (last "+periodStr+")",8,5,-40,50,10,period);
  #endif
#endif
#ifdef WEATHER_WIND_SPD_ON
  #ifdef  IMPERIAL_UNITS_ON
    makeChartJs(client,"WS","Wind Speed mph (last "+periodStr+")",-39,5,0,50,10,period);
  #else
    makeChartJs(client,"WS","Wind Speed kph (last "+periodStr+")",39,5,0,80,10,period);
  #endif
#endif
#ifdef WEATHER_PRESSURE_ON
  #ifdef IMPERIAL_UNITS_ON
    makeChartJs(client,"BP","Barometric Pressure in inches (last "+periodStr+")",-26,6,floor((WEATHER_NOMINAL_PRESSURE_SEA_LEVEL-50)*0.02953),ceil((WEATHER_NOMINAL_PRESSURE_SEA_LEVEL+40)*0.02953),1,period);
  #else
    makeChartJs(client,"BP","Barometric Pressure in mb (last "+periodStr+")",26,6,WEATHER_NOMINAL_PRESSURE_SEA_LEVEL-50,WEATHER_NOMINAL_PRESSURE_SEA_LEVEL+40,10,period);
  #endif
#endif
#ifdef WEATHER_HUMIDITY_ON
  makeChartJs(client,"RH","Relative Humidity % (last "+periodStr+")",33,5,0,100,10,period);
#endif
  client->print(F("}\r\n"));
  client->print(F("</script>\r\n"));

  strcpy_P(temp,ChartOptions1a); client->print(temp);
  strcpy_P(temp,ChartOptions2); client->print(temp);
  
#ifdef WEATHER_OUT_TEMP_ON
  makeChartCanvas(client,"ambientT");
#endif
#ifdef WEATHER_WIND_SPD_ON
  makeChartCanvas(client,"WS");
#endif
#ifdef WEATHER_PRESSURE_ON
  makeChartCanvas(client,"BP");
#endif
#ifdef WEATHER_HUMIDITY_ON
  makeChartCanvas(client,"RH");
#endif

  client->print("</div></body></html>\r\n");
}

#if defined(WEATHER_SKY_QUAL_ON) || defined(WEATHER_CLOUD_CVR_ON)
void skyPage(EthernetClient *client) {
  char temp[512]="";
  String a=www.arg("chart");
  
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
  strcpy_P(temp,html_links1);  client->print(temp);
  strcpy_P(temp,html_links2);  client->print(temp);
  strcpy_P(temp,html_links3s); client->print(temp);
  strcpy_P(temp,html_pageHeader3); client->print(temp);

  int period=1;
  String periodStr="";
  if ((a=="recent") || (a=="")) { period=1; periodStr="60 minutes"; }
  if (a=="last24") { period=24; periodStr="24 hours"; }
  if (a=="last48") { period=48; periodStr="48 hours"; }
  
  client->print(F("<script type=\"text/javascript\" src=\"Chart.js\"></script>\r\n"));
  client->print(F("<script>\r\n"));
  client->print(F("window.onload = function(){\r\n"));
#ifdef WEATHER_SKY_QUAL_ON
  makeChartJs(client,"SQ","Sky Quality mag/sq arc-sec (last "+periodStr+")",45,5,-30,5,5,period);
#endif
#ifdef WEATHER_CLOUD_CVR_ON
  makeChartJs(client,"skyT","Sky IR Temperature C (last "+periodStr+")",14,5,-40,5,5,period);
#endif
  client->print(F("}\r\n"));
  client->print(F("</script>\r\n"));

  strcpy_P(temp,ChartOptions1b); client->print(temp);
  strcpy_P(temp,ChartOptions2); client->print(temp);
  
#ifdef WEATHER_SKY_QUAL_ON
  makeChartCanvas(client,"SQ");
#endif
#ifdef WEATHER_CLOUD_CVR_ON
  makeChartCanvas(client,"skyT");
#endif

  client->print("</div></body></html>\r\n");
}
#endif

void makeChartJs(EthernetClient *client, const char chartId[], String chartName, int logColumn, int colWidth, int rangeMin, int rangeMax, int rangeStep, long hours) {
  char temp[256]="";
  char temp1[256]="";
  char ws1[90]="";
  char ws2[90]="";
  long rec=0;
  long k=0;

  strcpy_P(temp1,ChartJs1); sprintf(temp,temp1,chartId,chartId,chartId); client->print(temp);
  client->print(chartName);
  strcpy_P(temp,ChartJs3); client->print(temp);

  time_t t = now();
  rec=logRecordLocation(t)-120L*hours;
  while (rec<0) { rec+=2880; t-=24L*60L*60L; }
  int y=year(t); y-=2000; sprintf(temp,"%02d%02d%02d",y,month(t),day(t)); String fn="L"+String(temp)+".TXT";
  //Serial.print("Primary log="); Serial.println(fn);
  //Serial.print("Reading "); Serial.print(120); Serial.print(" records from rec#"); Serial.println(rec);

  File dataFile=SD.open(fn, FILE_READ);
  if (dataFile) {
    for (long i=0; i<120; i++) {
      if (((rec+i*hours)-k)>=2880L) {
        dataFile.close();
        k=rec+i*hours;
        t+=24L*60L*60L; y=year(t); y-=2000; sprintf(temp,"%02d%02d%02d",y,month(t),day(t)); fn="L"+String(temp)+".TXT";
        dataFile=SD.open(fn, FILE_READ);
        if (!dataFile) break;
        //Serial.print("Secondary log="); Serial.println(fn);
        //Serial.print("Reading "); Serial.print(120-i); Serial.print(" records from rec#"); Serial.println(0);
      }
      dataFile.seek(((rec+i*hours)-k)*80L);
      //if (chartId[0]=='B') Serial.println(((rec+i*step)-k));
      dataFile.read(ws1,80); ws1[abs(logColumn)+colWidth]=0;
      int j=abs(logColumn); while ((ws1[j]==' ') && (ws1[j]!=0)) j++;
      strcpy(ws2,(char*)&(ws1[j]));
      if (ws2[0]!=0) {
        double f=atof(ws2);
        if (logColumn==-8) f=f*(9.0/5.0)+32.0; // temperature C to F
        if (logColumn==-39) f=f*0.621371;      // wind kph to mph
        if (logColumn==-26) f=f*0.02953;       // pressure in inches
        if (logColumn==-26) dtostrf(f,1,3,ws2); else dtostrf(f,1,1,ws2);
        if (hours==1) dtostrf((120-i)/2.0,1,1,ws1);
        if (hours==24) dtostrf((120-i)/5.0,1,1,ws1);
        if (hours==48) dtostrf((120-i)/2.5,1,1,ws1);
        sprintf(temp,"{x:%s,y:%s},",ws1,ws2);
        client->print(temp);
      }
    }
    dataFile.close();
  }

  strcpy_P(temp1,ChartJs4); sprintf(temp,temp1,rangeMax,rangeMin,rangeStep); client->print(temp);
}

void makeChartCanvas(EthernetClient *client, const char chartId[]) {
  client->print(F("<div style=\"font-size: 14px;  float:left; padding: 10px; margin: 10px; background-color: #EEEEEE; border-style: solid; border-width: 3px; border-color: red;\">\r\n"));
  client->print(F("<canvas id=\"")); client->print(chartId); client->print(F("\" width=\"600\" height=\"200\"></canvas>\r\n"));
  client->print(F("</div>\r\n"));
}
#endif
