// -----------------------------------------------------------------------------------
// Error not found, 404
#include "../Common.h"
#include "../lib/ethernet/webServer/WebServer.h"

void handleNotFound() {
  String message = "<big>OCS Server, Error 404:</big>\r\n\r\nResource not found.\r\n";
  www.send(404, "text/plain", message);
  VLF("MSG: OCS Server, Error 404: Resource not found.");
}
