// roof or shutter ------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if ROOF == ON
  #include "../../pages/Pages.h"

  void roofTile();
  void roofTileAjax();
  void roofTileGet();

  const char htmlRoofBeg[] PROGMEM =
  "<div id='Roof' class='obsControl'>"
  "<b>Roof or Shutter</b><br />"
  "<div id='RoofStatus' style='overflow:hidden;'>";

  const char htmlRoofEnd[] PROGMEM =
  "<input type='button' onclick='s(\"roof\",\"open\")' value='Open Roof' />&nbsp;&nbsp;&nbsp;"
  "<input type='button' onclick='s(\"roof\",\"close\")' value='Close Roof' /><br />"
  "<br />"
  #if ROOF_AUTOCLOSE_DAWN == ON
    "<input type='checkbox' onclick='s(\"roof_auto_close\",this.checked)' %___ACL />&nbsp;Automatically close at dawn<br />"
  #endif
  "</div>"
  "</div>\r\n";

  const char htmlRoofControl[] PROGMEM =
  "</div>"
  "<div style='text-align: center'>"
  #if !(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)
    #if ROOF_SINGLE_OPEN_CLOSE_STOP_RELAY == ON
      "<input type='button' class='stopBtn' onclick='s(\"roof\",\"stop\")' value='Press!' />&nbsp;&nbsp;&nbsp;"
    #else
      "<input type='button' class='stopBtn' onclick='s(\"roof\",\"stop\")' value='Stop!' />&nbsp;&nbsp;&nbsp;"
    #endif
  #endif
  #if ROOF_USER_SAFETY_OVERRIDE == ON
    "<input type='button' onclick='s(\"roof\",\"override\")' value='Safety Override' />"
  #endif
  "<br />";

  const char htmlInnerRoofStat[] PROGMEM =
  "&nbsp;&nbsp;Status <div id='roof_sta' class='aStatus'>%s</div><br />"
  "<div id='roof_err' style='text-align:center'>%s</div>";

  const char htmlRoofColorNormalStat[] PROGMEM =
  "<span style='color: #505090;'>%s</span>";

  const char htmlRoofColorRedStat[] PROGMEM =
  "<span style='color: red;'>%s</span>";

#endif
