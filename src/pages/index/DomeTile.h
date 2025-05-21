// dome -----------------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if DOME == ON
  #include "../Pages.common.h"
  
  void domeTile();
  void domeTileAjax();
  void domeTileGet();

  const char htmlDomeBegin[] PROGMEM = 
  "<div id='Dome' class='obsControl'>"
  "<b>" L_DOME "</b><br />"
  "<div id='DomeStatus' style='text-align: left; overflow:hidden;'>";

  const char htmlDomeEnd[] PROGMEM = "</div>\r\n";

  const char htmlDomeControlsBegin[] PROGMEM =
  "</div><div style='text-align: left; overflow:hidden;'>"
  "<div style='text-align: center; margin-top:5px;'>";

  const char htmlDomeControlsEnd[] PROGMEM = "</div>\r\n";

  const char htmlDomeStatus[] PROGMEM =
  "&nbsp;&nbsp;" L_STATUS "<div id='dome_sta' class='aStatus'>%s</div><br/>";

  const char htmlDomeAltitudeStatus[] PROGMEM =
  "&nbsp;&nbsp;" L_ALTITUDE "<div id='dome_alt' class='aStatus'>%1.1f&nbsp;&deg;</div><br/>";

  const char htmlDomeAzimuthStatus[] PROGMEM =
  "&nbsp;&nbsp;" L_AZIMUTH "<div id='dome_azm' class='aStatus'>%1.1f&nbsp;&deg;</div><br/>";

  const char htmlDomeAltitude[] PROGMEM =
  "<label for='altitude'>" L_ALT " </label>"
  "<input size='3' type='number' id='altitude' name='altitude' min='0' max='90' "
  "onchange='s(\"dome_alt\",value)' value='%d'>&nbsp;&nbsp;";

  const char htmlDomeAzimuth[] PROGMEM =
  "<label for='azimuth'>" L_AZM " </label>"
  "<input size='4' type='number' id='azimuth' name='azimuth' min='0' max='360' "
  "onchange='s(\"dome_azm\",value)' value='%d'>&nbsp;&nbsp;";

  const char htmlDomeGoto[] PROGMEM =
  "<button onclick='s(\"dome\",\"goto\")' type='button'>" L_GOTO "</button>&nbsp;"
  "<button onclick='s(\"dome\",\"sync\")'  type='button'>" L_SYNC "</button><br/>";
  "<button onclick='if (confirm(\"" L_ARE_YOU_SURE_ORIENTATION "?\")) s(\"dome\",\"sync\")'  type='button'>" L_SYNC "</button><br/>";

  const char htmlDomeStop[] PROGMEM =
  "<button class='btns_attn' onclick='s(\"dome\",\"stop\")' type='button'>&nbsp;" L_STOP "&nbsp;</button><br/>";

  const char htmlDomeHome[] PROGMEM =
  "<button onclick='s(\"dome\",\"home\")' type='button'>" L_FIND_HOME "</button>&nbsp;&nbsp;"
  "<button onclick='s(\"dome\",\"reset\")' type='button'>" L_RESET_HOME "</button><br/>";
  "<button onclick='if (confirm(\"" L_ARE_YOU_SURE_ORIENTATION "?\")) s(\"dome\",\"reset\")' type='button'>" L_RESET_HOME "</button><br/>";

  const char htmlDomePark1[] PROGMEM =
  "<button onclick='s(\"dome\",\"unpark\")' type='button'>" L_UNPARK "</button>"
  "<button onclick='if (confirm(\"" L_ARE_YOU_SURE_ORIENTATION "?\")) s(\"dome\",\"unpark\")' type='button'>" L_UNPARK "</button>"
  "<button onclick='s(\"dome\",\"park\")' type='button'>" L_PARK "</button>";
  const char htmlDomePark2[] PROGMEM =
  "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
  "<button onclick='s(\"dome\",\"setpark\")' type='button'>" L_SET_PARK "</button><br/>";

#endif
