// -----------------------------------------------------------------------------------
// Handle webpage not found

#include "../Common.h"

#if WEB_SERVER == ON

#include "../lib/ethernet/webServer/WebServer.h"
#include "../lib/wifi/webServer/WebServer.h"
#include "../lib/tasks/OnTask.h"

void handleNotFound() {

  // open any sdcard file name that matches and serve that if possible
  #if SD_CARD == ON
    int statusCode = 0;
    char contentType[32] = "";

    if (www.uri().endsWith(".js")) {
      #ifndef ESP32
        if (www.modifiedSince()) statusCode = 304; else statusCode = 200;
      #else
        statusCode = 200;
      #endif
      strcpy(contentType, "application/javascript");
    } else
    if (www.uri().endsWith(".txt")) {
      statusCode = 200;
      strcpy(contentType, "text/plain");
    } else
    if (www.uri().endsWith(".htm") || www.uri().endsWith(".html")) {
      statusCode = 200;
      strcpy(contentType, "text/html");
    }

    if (statusCode) {
      File dataFile = FS.open(www.uri().c_str(), FILE_READ);
      if (dataFile) {
        char temp[260];
        long n;

        VF("MSG: OCS Server found file "); VL(www.uri());

        www.setContentLength(CONTENT_LENGTH_UNKNOWN);
        www.sendHeader("Etag", "3457807a63ac7bdabf8999b98245d0fe");
        www.sendHeader("Last-Modified", "Mon, 13 Apr 2015 15:35:56 GMT");
        www.sendHeader("Connection", "Close");
        www.send(statusCode, contentType, String());

        VF("MSG: OCS Server sending data... ");
        do {
          n = dataFile.available();
          if (n > 256) n = 256;
          if (n > 0) {
            dataFile.read((unsigned char*)temp, n);
            temp[n] = 0;
            www.sendContent(temp);
          }
          Y;
        } while (n > 0);
        dataFile.close();

        VL("done");
        www.sendContent("");

        return;
      }
    }
  #endif
  
  String message = "<body>";

  message.concat("<big>OCS Server, Error 404 File Not Found<br /><br />\n");
  message.concat("URI: " + www.uri() + "<br />\n");

  message.concat("Method: ");
  if (www.method() == HTTP_GET) message.concat("GET<br />\n"); else
  if (www.method() == HTTP_PUT) message.concat("PUT<br />\n"); else
  if (www.method() == HTTP_POST) message.concat("POST<br />\n"); else message.concat("Unknown<br />\n");

  message.concat("\nArguments: " + String(www.args()) + "<br />\n");
  for (uint8_t i = 0; i < www.args(); i++){
    message.concat(" " + www.argName(i) + ": " + www.arg(i) + "<br />\n");
  }

  message.concat("</body>");

  www.send(404, "text/html", message);
}

#endif