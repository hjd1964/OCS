// roll-off roof -------------------------------------------------------------------------------------------------------------
#include "RoofTile.h"

#if ROOF == ON
  #include "htmlHeaders.h"
  #include "htmlScripts.h"
  #include "htmlTabs.h"

  #include "../observatory/roof/Roof.h"

  #if OPERATIONAL_MODE != WIFI
  void roofTile(EthernetClient *client) {
  #else
  void roofTile() {
  #endif
    {
      char temp[250] = "";
      strcpy_P(temp, htmlRoof1);
      sendHtml(temp);
    }

    roofContents(client);

    {
      char temp[250] = "";
      strcpy_P(temp, htmlRoof2);
      sendHtml(temp);

      strcpy_P(temp, htmlRoof3);
      #if ROOF_AUTOCLOSE_DAWN == ON
        if (roofAutoClose) check(temp, "%___ACL"); else erase(temp, "%___ACL");
      #endif
      sendHtml(temp);
    }
  }

  #if OPERATIONAL_MODE != WIFI
  void roofContents(EthernetClient *client) {
  #else
  void roofContents() {
  #endif
    char temp[250];
    char ws1[10] = "";
    char ws2[10] = "";

    if (!roof.isMoving()) {
      if (roof.isClosed()) strcpy(ws1, "Closed"); else
      if (roof.isOpen()) strcpy(ws1, "Open"); else strcpy(ws1, "Stopped");
    } else
    if (roof.isOpening()) strcpy(ws1, "Opening"); else
    if (roof.isClosing()) strcpy(ws1, "Closing");

    const char *statusStr = roof.getStatus();
    if (strstr(statusStr, "No Error") || strstr(statusStr, "Travel: ") >= 0) 
      strcpy(ws2, "#505090");
    else 
      strcpy(ws2, "red");
    sprintf_P(temp, htmlInnerRoofStat, ws1, ws2, statusStr);
    sendHtml(temp);
  }

#endif
