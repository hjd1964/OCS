// -----------------------------------------------------------------------------------
// Web server

// SD CARD support, simply enable and provide a webserver.on("filename.htm") to serve each file
#if WEATHER_CHARTS == ON
  #include <SD.h>
#endif

EthernetServer _server(80);

void WebServer::init() {
  // start the Ethernet connection and the server:
  setResponseHeader(http_defaultHeader);

  _server.begin();
#if DEBUG_WEBSERVER == ON
  Serial.print("www server is at ");
  Serial.println(Ethernet.localIP());
#endif

#if WEATHER_CHARTS == ON
  SDfound=SD.begin(4);
#endif

  handler_count=0;
}

void WebServer::handleClient() {
  // listen for incoming clients
  EthernetClient _client;
  _client = _server.available();
  if (_client) {
#if DEBUG_WEBSERVER == ON
    Serial.println("new client");
#endif
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    unsigned long to=millis()+WebSocketTimeOut;
    while ((_client.connected()) && ((long)(millis()-to) < 0)) {
      WDT_RESET;
      if (_client.available()) {
        char c = _client.read();
#if DEBUG_WEBSERVER == ON
        Serial.write(c);
#endif
        if (inputBuffer.length()<128) inputBuffer+=c;

        // if you've gotten to the end of the line (received a newline character) and the line is blank, the http request has ended, send a reply
        if (c == '\n' && currentLineIsBlank) {
          // grab the URL
          int url_start=inputBuffer.indexOf("GET ")+4;
          int url_end=inputBuffer.indexOf("HTTP/")-1;
          int url_pageEnd=inputBuffer.indexOf("?"); if (url_pageEnd<0) url_pageEnd=url_end;
          if ((url_start!=-1) && (url_end!=-1)) {
            String command=inputBuffer.substring(url_start,url_end);
            String page=inputBuffer.substring(url_start,url_pageEnd);

#if WEATHER_CHARTS == ON
            // watch for cache requests
            if ((!modifiedSinceFound) && (command.indexOf("If-Modified-Since:")>=0)) modifiedSinceFound=true;
#endif

            // pass to handlers
            bool handlerFound=false;
            for (int i=0; i<handler_count; i++) {
              String fn=handlers_fn[i];
              if (!fn.startsWith("/")) fn="/"+fn;
              if (page==fn) {
                // but first, isolate any get parameters and their values
                command=command.substring(command.indexOf(handlers_fn[i])+handlers_fn[i].length()); 
                while (command[0]==' ') command=command.substring(1);
                while (command[command.length()-1]==' ') command=command.substring(0,command.length()-1);

                if (handlers[i]!=NULL) {
                  // check to see if there's a ?a=1& or &a=1
                  parameter_count=0;
                  while ((command[0]=='?') || (command[0]=='&')) {
                    command=command.substring(1);
                    int j =command.indexOf('='); if (j==-1) j=command.length(); if (j==-1) break; // invalid formatting
                    int j1=command.indexOf('&'); if (j1==-1) j1=command.length()+1;
                    String thisArg=command.substring(0,j);
                    String thisVal=command.substring(j+1,j1);
                    if (thisArg!="") {
                      parameter_count++;
                      parameters[parameter_count-1]=thisArg;
                      values[parameter_count-1]=thisVal;
                    }
                    command=command.substring(j1);
  #if DEBUG_WEBSERVER == ON
                    Serial.print(thisArg); Serial.print("="); Serial.println(thisVal);
  #endif
                  }
                  _client.print(responseHeader);
                  (*handlers[i])(&_client); // send page content
                  handlerFound=true;
                  break;
                } else {
#if WEATHER_CHARTS == ON
                  // send a 304 header
                  if ((modifiedSinceFound) && true ) {
                    char temp[255]; strcpy_P(temp,http_js304Header); _client.print(temp);
                    handlerFound=true;
                    break;
                  } else {
                    if (handlers_fn[i].indexOf(".js")>0) {
                      char temp[255]; strcpy_P(temp,http_jsHeader); _client.print(temp); 
                    } else _client.print(responseHeader);
                    sdPage(handlers_fn[i],&_client);
                    handlerFound=true;
                    break;
                  }
#endif
                }
              }
            }
            // handle not found
            if (!handlerFound && (notFoundHandler!=NULL)) (*notFoundHandler)(&_client);
          } else {
#if DEBUG_WEBSERVER == ON
            Serial.println("Invalid response");
#endif
          }
          inputBuffer="";
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(5);
#if DEBUG_WEBSERVER == ON
    Serial.println("client closing connection");
#endif
    // close the connection:
    _client.stop();
    // clear the input buffer
    inputBuffer="";
#if WEATHER_CHARTS == ON
    modifiedSinceFound=false;
#endif
#if DEBUG_WEBSERVER == ON
    Serial.println("client disconnected");
#endif
  }
}

void WebServer::setResponseHeader(const char *str) {
  if(!str) return;
  strcpy_P(responseHeader,str);
}

void WebServer::on(String fn, webFunction handler) {
  handler_count++; if (handler_count>20) { handler_count=20; return; }
  handlers[handler_count-1]=handler;
  handlers_fn[handler_count-1]=fn;
}

void WebServer::onNotFound(webFunction handler) {
  notFoundHandler=handler;
}

String WebServer::arg(String id) {
  for (int i=0; i<parameter_count; i++) {
    if (id==parameters[i]) return values[i];
  }
  return "";
}

#if WEATHER_CHARTS == ON
void WebServer::on(String fn) {
  handler_count++; if (handler_count>20) { handler_count=20; return; }
  handlers[handler_count-1]=NULL;
  handlers_fn[handler_count-1]=fn;
}

void WebServer::sdPage(String fn, EthernetClient *client) {
  char temp[256] = "";
  int n;

  // open the sdcard file
  if (SDfound) {
    if (WATCHDOG_DURING_SD == OFF) WDT_DISABLE;
    File dataFile=SD.open(fn, FILE_READ);
    if (dataFile) {
      do {
        n=dataFile.available(); if (n>256) n=256;
        if (n>0) { dataFile.read(temp,n); client->write(temp,n); }
      } while (n>0);
      dataFile.close();
    }
    if (WATCHDOG_DURING_SD == OFF) WDT_ENABLE;
  }
}
#endif
