#pragma once

const char html_links1[] PROGMEM =
"<a href=\"/index.htm\" style=\"background-color: #222222;\">Overview</a>";

const char html_links1s[] PROGMEM =
"<a href=\"/index.htm\" style=\"background-color: #552222;\">Overview</a>";

#if WEATHER == ON && WEATHER_CHARTS == ON
  const char html_links2[] PROGMEM =
  "<a href=\"/weatherpage.htm\" style=\"background-color: #222222;\">Weather</a>";

  const char html_links2s[] PROGMEM =
  "<a href=\"/weatherpage.htm\" style=\"background-color: #552222;\">Weather</a>";

  #if WEATHER_SKY_QUAL == ON || WEATHER_CLOUD_CVR == ON
    const char html_links3[] PROGMEM =
    "<a href=\"/skypage.htm\" style=\"background-color: #222222;\">Sky Conditions</a>";
    const char html_links3s[] PROGMEM =
    "<a href=\"/skypage.htm\" style=\"background-color: #552222;\">Sky Conditions</a>";
  #endif
#endif
