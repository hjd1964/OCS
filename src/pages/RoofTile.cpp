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
    char temp[200] = "";

    strcpy_P(temp, htmlRoof1);
    sendHtml(temp);

    roofContents(client);

    strcpy_P(temp, htmlRoof2);
    #if ROOF_AUTOCLOSE_DAWN == ON
      if (roofAutoClose) check(temp, "%___ACL"); else erase(temp, "%___ACL");
    #endif
    sendHtml(temp);
  }

  #if OPERATIONAL_MODE != WIFI
  void roofContents(EthernetClient *client) {
  #else
  void roofContents() {
  #endif
    char temp[200] = "";
    char temp1[200] = "";
    char ws1[20] = "";

    strcpy_P(temp1, htmlInnerRoofStat);

    if (!roof.isMoving()) {
      if (roof.isClosed()) strcpy(ws1, "Closed"); else
      if (roof.isOpen()) strcpy(ws1, "Open"); else strcpy(ws1, "Stopped");
    } else
    if (roof.isOpening()) strcpy(ws1, "Opening"); else
    if (roof.isClosing()) strcpy(ws1, "Closing");

    String s = roof.getStatus();
    if (s == "No Error" || s.indexOf("Travel: ") >= 0) {
      s = "<div style=\"color: #505090;\">" + s + "</div>";
    } else {
      s = "<div style=\"color: red;\">" + s + "</div>";
    }
    sprintf(temp, temp1, ws1, s.c_str());
    sendHtml(temp);
  }

#endif
