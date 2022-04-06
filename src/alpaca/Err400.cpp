// -----------------------------------------------------------------------------------
// Alpaca could not interpret request 400

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON

#include "Alpaca.h"

void handleRequestFailed() {
  String message = "<big>OCS Alpaca Server, Error 400:</big>\r\n\r\nCould not interpret the request.\r\n";
  apc.send(400, "text/plain", message);
  VLF("MSG: OCS Alpaca Server, Error 400: Could not interpret the request.");
}

#endif
