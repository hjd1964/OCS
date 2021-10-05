// -----------------------------------------------------------------------------------
// Error not found, 404
#include "../Common.h"

#if OPERATIONAL_MODE == ETHERNET_W5100 || OPERATIONAL_MODE == ETHERNET_W5500
  void handleNotFound(EthernetClient *client) {
    String message = "File Not Found\n\n";
    www.sendContent(message);
    VLF("File not found");
  }
#endif
