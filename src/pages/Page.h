// OCS standard page
#pragma once

#include "Pages.common.h"

#define PAGE_INDEX 0
#define PAGE_WEATHER 1
#define PAGE_SKY_CONDITIONS 2

void pageHeader(int selected);

const char html_body_begin[] PROGMEM = "<body bgcolor=\"#26262A\">\r\n";

const char html_page_header_begin[] PROGMEM =
"<div class=\"t\"><table width=\"100%\"><tr><td><b><font size=\"5\">Observatory Control System"
"</font></b></td><td align=\"right\"><b>";

const char html_page_header_links[] PROGMEM = "</td></tr></table>";

const char html_page_header_end[] PROGMEM = "<br /></div><div class=\"b\">\r\n";

const char html_links_index_begin[] PROGMEM = "<a href='/index.htm' ";
const char html_links_index_end[] PROGMEM = "'>" L_OVERVIEW "</a>";

const char html_links_weather_begin[] PROGMEM = "<a href='/weatherpage.htm' ";
const char html_links_weather_end[] PROGMEM = "'>" L_WEATHER "</a>";

const char html_links_sky_begin[] PROGMEM = "<a href='/skypage.htm' ";
const char html_links_sky_end[] PROGMEM = "'>" L_SKY_CONDITIONS "</a>";

const char html_links_selected[] PROGMEM =" style='background-color: #552222;";
