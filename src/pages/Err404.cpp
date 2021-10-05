// -----------------------------------------------------------------------------------
// Error not found, 404
#include "../Common.h"
#include "../lib/ethernet/webServer/WebServer.h"

#if OPERATIONAL_MODE == ETHERNET_W5100 || OPERATIONAL_MODE == ETHERNET_W5500
  void handleNotFound() {
    String message = "File Not Found\n\n";
    www.sendContent(message);
    VLF("File not found");
  }
#endif
