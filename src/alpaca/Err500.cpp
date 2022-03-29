// -----------------------------------------------------------------------------------
// Alpaca server internal error 500

#include "../Common.h"
#include "Alpaca.h"

void alpacaServerError() {
  String message = "<big>OCS Alpaca Server, Error 500:</big>\r\n\r\nInternal error.\r\n";
  apc.send(500, "text/plain", message);
  VLF("MSG: OCS Alpaca Server, Error 500: Internal error.");
}
