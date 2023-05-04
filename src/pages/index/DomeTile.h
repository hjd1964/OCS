// dome -----------------------------------------------------------------------
#pragma once

#include "../../Common.h"

#if DOME == ON
  void domeTile();
  void domeTileAjax();
  void domeTileGet();

  const char htmlDomeBegin[] PROGMEM = 
  "<div id='Dome' class='obsControl'>"
  "<b>Dome</b><br />"
  "<div id='DomeStatus' style='text-align: left; overflow:hidden;'>";

  const char htmlDomeEnd[] PROGMEM = "</div>\r\n";

  const char htmlDomeControlsBegin[] PROGMEM =
  "</div><div style='text-align: left; overflow:hidden;'>"
  "<div style='text-align: center'><br/>";

  const char htmlDomeControlsEnd[] PROGMEM = "</div>\r\n";

  const char htmlDomeStatus[] PROGMEM =
  "&nbsp;&nbsp;Status<div id='dome_sta' class='aStatus'>%s</div><br/>";

  const char htmlDomeAltitudeStatus[] PROGMEM =
  "&nbsp;&nbsp;Altitude<div id='dome_alt' class='aStatus'>%1.1f&nbsp;&deg;</div><br/>";

  const char htmlDomeAzimuthStatus[] PROGMEM =
  "&nbsp;&nbsp;Azimuth<div id='dome_azm' class='aStatus'>%1.1f&nbsp;&deg;</div><br/>";

  const char htmlDomeAzimuth[] PROGMEM =
  "<label for='azimuth'>Azm </label>"
  "<input size='4' type='number' id='azimuth' name='azimuth' min='0' max='360' "
  "onchange='s(\"dome_azm\",value)' value='%d'>&nbsp;&nbsp;";

  const char htmlDomeAltitude[] PROGMEM =
  "<label for='altitude'>Alt </label>"
  "<input size='3' type='number' id='altitude' name='altitude' min='0' max='90' "
  "onchange='s(\"dome_alt\",value)' value='%d'>&nbsp;&nbsp;";

  const char htmlDomeGoto[] PROGMEM =
  "<input type='button' onclick='s(\"dome\",\"goto\")' value='Goto'>&nbsp;&nbsp;"
  "<input type='button' onclick='s(\"dome\",\"sync\")' value='Sync'><br/>";

  const char htmlDomeStop[] PROGMEM =
  "<input type='button' class='stopBtn' onclick='s(\"dome\",\"stop\")' value='Stop!'><br/>";

  const char htmlDomeHome[] PROGMEM =
  "<input type='button' onclick='s(\"dome\",\"home\")' value='Find Home'>&nbsp;&nbsp;"
  "<input type='button' onclick='s(\"dome\",\"reset\")' value='Home (Reset)'><br/>";

  const char htmlDomePark1[] PROGMEM =
  "<input type='button' style='margin-top:5px;' onclick='s(\"dome\",\"park\")' value='Park'>"
  "<input type='button' onclick='s(\"dome\",\"unpark\")' value='Un-Park'>";
  const char htmlDomePark2[] PROGMEM =
  "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' onclick='s(\"dome\",\"setpark\")' value='Set-Park'><br/>";

#endif
