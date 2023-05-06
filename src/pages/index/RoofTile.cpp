// roof or shutter ------------------------------------------------------------
#include "RoofTile.h"

#if ROOF == ON
  #include "../../observatory/safety/Safety.h"
  #include "../../observatory/roof/Roof.h"
  #include "../CheckHelp.h"

  void getRoofErrorStrColored(const char *errorStr, char *errorStrColored);

  void roofTile() {
    char temp[256];
    char temp1[64];

    strcpy_P(temp, htmlRoofBeg);
    www.sendContent(temp);

    getRoofErrorStrColored(roof.errorMessage(), temp1);
    sprintf_P(temp, htmlInnerRoofStat, roof.statusMessage(), temp1);
    www.sendContent(temp);

    #if !(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)
      strcpy_P(temp, htmlRoofControlStopPress);
      www.sendContent(temp);
    #endif

    strcpy_P(temp, htmlRoofControlSafetyOverride);
    www.sendContent(temp);

    strcpy_P(temp, htmlRoofControlOpenClose);
    www.sendContent(temp);

    strcpy_P(temp, htmlRoofEnd);

    #if ROOF_AUTOCLOSE_DAWN == ON
      if (safety.roofAutoClose) check(temp, "%___ACL"); else erase(temp, "%___ACL");
    #endif
    www.sendContent(temp);
  }

  void roofTileAjax() {
    char temp1[80];

    const char *statusStr = roof.statusMessage();
    www.sendContent("roof_sta|"); www.sendContent(statusStr); www.sendContent("\n");

    getRoofErrorStrColored(roof.errorMessage(), temp1);
    www.sendContent("roof_err|"); www.sendContent(temp1); www.sendContent("\n");
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

  void getRoofErrorStrColored(const char *errorStr, char *errorStrColored) {
    if (strstr(errorStr, L_NO_ERROR) || strstr(errorStr, L_TRAVEL) || strstr(errorStr, L_WAIT_FOR_PARK)) {
      sprintf_P(errorStrColored, htmlRoofColorNormalStat, errorStr);
    } else {
      sprintf_P(errorStrColored, htmlRoofColorRedStat, errorStr);
    }
  }

#endif
