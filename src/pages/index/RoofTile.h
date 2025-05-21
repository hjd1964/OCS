// roof or shutter ------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if ROOF == ON
  #include "../Pages.common.h"

  void roofTile();
  void roofTileAjax();
  void roofTileGet();

  const char htmlRoofBeg[] PROGMEM =
  "<div id='Roof' class='obsControl'>"
  "<b>" L_ROOF_SHUTTER "</b><br />"
  "<div id='RoofStatus' style='overflow:hidden;'>";

  const char htmlRoofEnd[] PROGMEM =
  "<br />"
  #if ROOF_AUTOCLOSE_DAWN == ON
    "<input type='checkbox' onclick='s(\"roof_auto_close\",this.checked)' %___ACL />&nbsp;" L_CLOSE_AT_DAWN "<br />"
  #endif
  "</div>"
  "</div>\r\n";

  const char htmlInnerRoofStat[] PROGMEM =
  "&nbsp;&nbsp;Status <div id='roof_sta' class='aStatus'>%s</div><br />"
  "<div id='roof_err' style='text-align:center'>%s</div></div>"
  "<div style='text-align: center'>";

  const char htmlRoofColorNormalStat[] PROGMEM =
  "<span style='color: #505090;'>%s</span>";

  const char htmlRoofColorRedStat[] PROGMEM =
  "<span style='color: red;'>%s</span>";

  #if !(ROOF_MOTOR_RELAY_MOMENTARY == ON && ROOF_MOTOR_STOP_RELAY == OFF && ROOF_POWER_RELAY == OFF)
    const char htmlRoofControlStopPress[] PROGMEM =
    #if ROOF_SINGLE_OPEN_CLOSE_STOP_RELAY == ON
      "<input type='button' class='btns_attn' onclick='s(\"roof\",\"stop\")' value='&nbsp;" L_PRESS "&nbsp;' />&nbsp;&nbsp;&nbsp;";
    #else
      "<input type='button' class='btns_attn' onclick='s(\"roof\",\"stop\")' value='&nbsp;" L_STOP "&nbsp;' />&nbsp;&nbsp;&nbsp;";
    #endif
  #endif

  const char htmlRoofControlSafetyOverride[] PROGMEM =
  #if ROOF_USER_SAFETY_OVERRIDE == ON
    "<input type='button' class='btns_attn' style='background-color: " COLOR_IMPORTANT_CONTROL_BACKGROUND "' onclick='if (confirm(\"" L_ARE_YOU_SURE_ROOF "?\")) s(\"roof\",\"override\")' value='&nbsp;" L_SAFETY_OVERRIDE "&nbsp;' />"
  #endif
  "<br />";

  const char htmlRoofControlOpenClose[] PROGMEM =
  "<button class='btns_right' onpointerdown=\"s('roof','open')\" type='button'>" L_OPEN_ROOF "</button>"
  "<button class='btns_left' onpointerdown=\"s('roof','close')\" type='button'>" L_CLOSE_ROOF "</button><br />";
//  "<input type='button' onclick='s(\"roof\",\"open\")' class='btns_left' value='" L_OPEN_ROOF "' />&nbsp;&nbsp;&nbsp;"
//  "<input type='button' onclick='s(\"roof\",\"close\")' class='btns_right' value='" L_CLOSE_ROOF "' /><br />";

#endif
