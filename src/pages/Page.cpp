// OCS standard page
#include <Arduino.h>
#include "Page.h"

void pageHeader(int selected) {
  char temp[300];

  strcpy_P(temp, html_body_begin); www.sendContent(temp);

  strcpy_P(temp, html_page_header_begin); www.sendContent(temp);
  sprintf(temp, HOST_NAME " %s</b>", ocsVersion); www.sendContent(temp);
  strcpy_P(temp, html_page_header_links); www.sendContent(temp);

  strcpy_P(temp, html_links_index_begin); www.sendContent(temp);
  if (selected == PAGE_INDEX) { strcpy_P(temp, html_links_selected); www.sendContent(temp); }
  strcpy_P(temp, html_links_index_end); www.sendContent(temp);

  if (strlen(CAMERA_WEBPAGE) > 0) {
    strcpy_P(temp, html_links_cam_begin); www.sendContent(temp);
    if (selected == PAGE_CAMERA) { strcpy_P(temp, html_links_selected); www.sendContent(temp); }
    strcpy_P(temp, html_links_cam_end); www.sendContent(temp);
  }

  #if WEATHER == ON && WEATHER_CHARTS == ON
    strcpy_P(temp, html_links_weather_begin); www.sendContent(temp);
    if (selected == PAGE_WEATHER) { strcpy_P(temp, html_links_selected); www.sendContent(temp); }
    strcpy_P(temp, html_links_weather_end); www.sendContent(temp);

    #if WEATHER_SKY_QUAL == ON || WEATHER_CLOUD_CVR == ON 
      strcpy_P(temp, html_links_sky_begin); www.sendContent(temp);
      if (selected == PAGE_SKY_CONDITIONS) { strcpy_P(temp, html_links_selected); www.sendContent(temp); }
      strcpy_P(temp, html_links_sky_end); www.sendContent(temp);
    #endif
  #endif

  strcpy_P(temp, html_page_header_end); www.sendContent(temp);
}
