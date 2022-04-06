// ----------------------------------------------------------------------------------
// Alpaca resource not found 404

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON

#include "Alpaca.h"

void alpacaNotFoundError() {
  String message = "<big>OCS Alpaca Server, Error 404:</big>\r\n\r\nResource not found.\r\n";
  apc.send(404, "text/plain", message);
  VLF("MSG: OCS Alpaca Server, Error 404: Resource not found.");
}

#endif
