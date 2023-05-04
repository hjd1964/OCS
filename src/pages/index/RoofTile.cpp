// roof or shutter ------------------------------------------------------------
#include "RoofTile.h"

#if ROOF == ON
  #include "../htmlHeaders.h"
  #include "../htmlScripts.h"

  #include "../../observatory/safety/Safety.h"
  #include "../../observatory/roof/Roof.h"
  #include "../CheckHelp.h"

  void roofTile() {
    char temp[400] = "";

    strcpy_P(temp, htmlRoofBeg);
    www.sendContent(temp);

    const char *statusStr = roof.statusMessage();
    const char *errorStr = roof.errorMessage();
    char errorStrColored[80];
    if (strstr(errorStr, "No Error") || strstr(errorStr, "Travel: ") || strstr(errorStr, "Waiting for mount to park")) {
      sprintf_P(errorStrColored, htmlRoofColorNormalStat, errorStr);
    } else {
      sprintf_P(errorStrColored, htmlRoofColorRedStat, errorStr);
    }
    sprintf_P(temp, htmlInnerRoofStat, statusStr, errorStrColored);
    www.sendContent(temp);

    strcpy_P(temp, htmlRoofControl);
    www.sendContent(temp);

    strcpy_P(temp, htmlRoofEnd);
    #if ROOF_AUTOCLOSE_DAWN == ON
      if (safety.roofAutoClose) check(temp, "%___ACL"); else erase(temp, "%___ACL");
    #endif
    www.sendContent(temp);
  }

  void roofTileAjax() {
    const char *statusStr = roof.statusMessage();
    const char *errorStr = roof.errorMessage();
    char errorStrColored[80];
    if (strstr(errorStr, "No Error") || strstr(errorStr, "Travel: ") || strstr(errorStr, "Waiting for mount to park")) {
      sprintf_P(errorStrColored, htmlRoofColorNormalStat, errorStr);
    } else {
      sprintf_P(errorStrColored, htmlRoofColorRedStat, errorStr);
    }
    www.sendContent("roof_sta|"); www.sendContent(statusStr); www.sendContent("\n");
    www.sendContent("roof_err|"); www.sendContent(errorStrColored); www.sendContent("\n");
  }

  void roofTileGet() {
    String s;

    s = www.arg("roof");
    if (!s.equals(EmptyStr)) {
      if (s.equals("open")) roof.open();
      if (s.equals("close")) roof.close();
      if (s.equals("override")) roof.setSafetyOverride(true);
      if (s.equals("stop")) { roof.stop(); roof.clearStatus(); }
    }

    s = www.arg("roof_auto_close");
    if (!s.equals(EmptyStr)) {
      if (s.equals("true")) safety.roofAutoClose = true;
      if (s.equals("false")) safety.roofAutoClose = false;
    }
  }

#endif
