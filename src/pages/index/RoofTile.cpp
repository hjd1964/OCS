// roll-off roof -------------------------------------------------------------------------------------------------------------
#include "RoofTile.h"

#if ROOF == ON
  #include "../htmlHeaders.h"
  #include "../htmlScripts.h"

  #include "../../observatory/safety/Safety.h"
  #include "../../observatory/roof/Roof.h"
  #include "../CheckHelp.h"

  void roofTile() {
    {
      char temp[500] = "";
      strcpy_P(temp, htmlRoof1);
      www.sendContent(temp);
    }

    roofContents();

    {
      char temp[500] = "";
      strcpy_P(temp, htmlRoof2);
      www.sendContent(temp);

      strcpy_P(temp, htmlRoof3);
      #if ROOF_AUTOCLOSE_DAWN == ON
        if (safety.roofAutoClose) check(temp, "%___ACL"); else erase(temp, "%___ACL");
      #endif
      www.sendContent(temp);
    }
  }

  void roofGet() {
    www.setContentLength(CONTENT_LENGTH_UNKNOWN);
    www.sendHeader("Cache-Control", "no-cache");
    www.send(200, "text/plain", String());

    roofContents();

    www.sendContent("");
  }

  void roofContents() {
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
    if (strstr(statusStr, "No Error") || strstr(statusStr, "Travel: ") || strstr(statusStr, "Waiting for mount to park")) 
      strcpy(ws2, "#505090");
    else 
      strcpy(ws2, "red");
    sprintf_P(temp, htmlInnerRoofStat, ws1, ws2, statusStr);
    www.sendContent(temp);
  }

#endif
