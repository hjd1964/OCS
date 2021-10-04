// -----------------------------------------------------------------------------------
// Wifi Web and Cmd servers
#pragma once

#include "../../Common.h"

#if OPERATIONAL_MODE == WIFI
  #if defined(ESP32)
    #include <WiFi.h>
    #include <WiFiClient.h>
    #include <WiFiAP.h>
    #include <WebServer.h>
    extern WebServer www;
  #elif defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <WiFiClient.h>
    #include <ESP8266WiFiAP.h>
    #include <ESP8266WebServer.h>
    extern ESP8266WebServer www;
  #else
    #error "Configuration (Config.h): No Wifi support is present for this device"
  #endif

  void wifiInit(void);
  void wifiStart(void);

  // macros to help with sending webpage data, chunked
  #define sendHtmlStart() www.setContentLength(CONTENT_LENGTH_UNKNOWN); www.sendHeader("Cache-Control","no-cache"); www.send(200, "text/html", String());
  #define sendHtml(x) www.sendContent(x);
  #define sendHtmlDone(x) www.sendContent("");

#endif
