// -----------------------------------------------------------------------------------
// Alpaca Setup

#include <ArduinoJson.h>

#include "../Common.h"
#include "Alpaca.h"
#include "../observatory/safety/Safety.h"
#include "../pages/htmlHeaders.h"

void alpacaSetup() {
  char temp[250] = "";

  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "text/html", String());

  strcpy_P(temp, html_head1); apc.sendContent(temp);
  apc.sendContent("</head>\r\n<body>\r\n");

  apc.sendContent("<big>Observatory Control System (OCS, Version ");
  apc.sendContent(ocsVersion);
  apc.sendContent(")<br/>ASCOM ALPACA Setup</big><br/><br/>\r\n");

  apc.sendContent(F("Device:<br/>\r\n"));
  apc.sendContent(F("&nbsp;&nbsp;<a href=\"/setup/v1/safetymonitor/0/setup\">SafetyMonitor</a>\r\n"));

  apc.sendContent(F("</body></html>\r\n"));
  apc.sendContent("");
}

void alpacaSetupSafetyMonitor() {
  char temp[250] = "";

  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "text/html", String());

  strcpy_P(temp, html_head1); apc.sendContent(temp);
  apc.sendContent("</head>\r\n<body>\r\n");

  apc.sendContent("<big>Observatory Control System (OCS, Version ");
  apc.sendContent(ocsVersion);
  apc.sendContent(")<br/>ASCOM ALPACA SafetyMonitor</big><br/><br/>\r\n");

  apc.sendContent(F("Device:<br/>\r\n"));
  apc.sendContent(F("&nbsp;&nbsp;No setup supported.<br/>\r\n"));

  apc.sendContent(F("<br/><br/><a href=\"/setup\">OCS ASCOM ALPACA Setup</a>\r\n"));

  apc.sendContent(F("</body></html>\r\n"));
  apc.sendContent("");
}
