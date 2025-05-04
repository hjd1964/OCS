#pragma once

#include "../Common.h"
#include "../lib/ethernet/webServer/WebServer.h"
#include "../lib/wifi/webServer/WebServer.h"

#ifndef TILE_WIDTH_PIXELS
#define TILE_WIDTH_PIXELS "320"
#endif
#ifndef SWITCH_LINE_WIDTH_PIXELS
#define SWITCH_LINE_WIDTH_PIXELS "312"
#endif
#ifndef TILE_HEIGHT_PIXELS
#define TILE_HEIGHT_PIXELS "220"
#endif

#ifndef TILE_FONT_SIZE_PIXELS
#define TILE_FONT_SIZE_PIXELS "15"
#endif

#ifndef COLOR_BODY_BACKGROUND
#define COLOR_BODY_BACKGROUND "#26262A"
#endif

#ifndef COLOR_FOREGROUND
#define COLOR_FOREGROUND "#999999"
#endif
#ifndef COLOR_LIGHT_FOREGROUND
#define COLOR_LIGHT_FOREGROUND "#505090"
#endif
#ifndef COLOR_ALERT
#define COLOR_ALERT "#105010"
#endif
#ifndef COLOR_BACKGROUND
#define COLOR_BACKGROUND "#111111"
#endif
#ifndef COLOR_LIGHT_BACKGROUND
#define COLOR_LIGHT_BACKGROUND "#CCCCCC"
#endif
#ifndef COLOR_BORDER
#define COLOR_BORDER "#551111"
#endif

#ifndef COLOR_LINK
#define COLOR_LINK "#A07070"
#endif
#ifndef COLOR_LINK_BACKGROUND
#define COLOR_LINK_BACKGROUND "#332222"
#endif
#ifndef COLOR_LINK_SELECTED_BACKGROUND
#define COLOR_LINK_SELECTED_BACKGROUND "#552222"
#endif
#ifndef COLOR_LINK_BORDER
#define COLOR_LINK_BORDER "red"
#endif

#ifndef COLOR_CONTROL
#define COLOR_CONTROL "#aaa"
#endif
#ifndef COLOR_CONTROL_BACKGROUND
#define COLOR_CONTROL_BACKGROUND "#EEEEEE"
#endif
#ifndef COLOR_CONTROL_DISABLED
#define COLOR_CONTROL_DISABLED "#000"
#endif
#ifndef COLOR_CONTROL_SELECTED
#define COLOR_CONTROL_SELECTED "#ccc"
#endif
#ifndef COLOR_CONTROL_UNSELECTED
#define COLOR_CONTROL_UNSELECTED "#aaa"
#endif
#ifndef COLOR_CONTROL_DISABLED_BACKGROUND
#define COLOR_CONTROL_DISABLED_BACKGROUND "#888"
#endif
#ifndef COLOR_CONTROL_BORDER
#define COLOR_CONTROL_BORDER "red"
#endif
#ifndef COLOR_CRITICAL_CONTROL_BACKGROUND
#define COLOR_CRITICAL_CONTROL_BACKGROUND "#dcc"
#endif
#ifndef COLOR_IMPORTANT_CONTROL_BACKGROUND
#define COLOR_IMPORTANT_CONTROL_BACKGROUND "#eec"
#endif
#ifndef COLOR_CRITICAL_CONTROL_BORDER
#define COLOR_CRITICAL_CONTROL_BORDER "#f22"
#endif

#ifndef COLOR_CHART_BACKGROUND
#define COLOR_CHART_BACKGROUND "rgba(192,32,32,0.4)"
#endif

// common web site framework
const char html_head_begin[] PROGMEM =
"<!DOCTYPE HTML>\r\n"
"<html>\r\n<head>\r\n"
"<meta charset='utf-8'/>\r\n"
"<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\r\n";

const char html_head_refresh[] PROGMEM =
"<meta http-equiv=\"refresh\" content=\"5; URL=/index.htm\">\r\n";

const char html_main_css_begin[]  PROGMEM = "<STYLE>";
const char html_main_css_a[]  PROGMEM = 
".a { background-color: " COLOR_BACKGROUND "; } .t { padding: 10px 10px 20px 10px; border: 5px solid " COLOR_BORDER "; "
"margin: 25px 25px 0px 25px; color:" COLOR_FOREGROUND "; background-color:" COLOR_BACKGROUND "; }";
const char html_main_css_a1[] PROGMEM =
"a:hover, a:active { background-color:" COLOR_LINK_BORDER "; } .c { color:" COLOR_CONTROL "; font-weight: bold; }";
const char html_main_css_a2[] PROGMEM =
"a:link, a:visited { background-color:" COLOR_LINK_BACKGROUND "; color:" COLOR_LINK "; border:1px solid " COLOR_LINK_BORDER "; "
"padding: 5px 10px; margin: 0px; text-align: center; text-decoration: none; display: inline-block; }";
const char html_main_css_b[] PROGMEM =
".b { padding: 10px; border-left: 5px solid " COLOR_BORDER "; overflow:hidden; border-right: 5px solid " COLOR_BORDER "; "
"border-bottom: 5px solid " COLOR_BORDER "; margin: 0px 25px 25px 25px; color:" COLOR_FOREGROUND "; background-color:" COLOR_BACKGROUND "; }";
const char html_main_css_misc[] PROGMEM =
"h1 { text-align: right; } .g { color: " COLOR_ALERT "; font-weight: bold; }";
const char html_main_css_obsSwLine[] PROGMEM =
".obsSwLine { height: 2em; width: " SWITCH_LINE_WIDTH_PIXELS "px; line-height: 2em; float: left; padding: 0px; margin: 0px; }";
const char html_main_css_obsSwCtrl[] PROGMEM =
".obsSwCtrl { height: 2em; width: 86px; vertical-align: middle; float: right; padding: 0px; margin: 0px; }";
const char html_main_css_obsWideSwCtrl[] PROGMEM =
".obsWideSwCtrl { height: 2em; width: 174px; vertical-align: middle; float: right; padding: 0px; margin: 0px; }";
const char html_main_css_obsControl[] PROGMEM =
".obsControl { position: relative; font-size: " TILE_FONT_SIZE_PIXELS "px; width: " TILE_WIDTH_PIXELS "px; height: " TILE_HEIGHT_PIXELS "px; float:left; padding: 10px; margin: 10px; "
"background-color:" COLOR_CONTROL_BACKGROUND "; border-style: solid; border-width: 3px; border-color: " COLOR_CONTROL_BORDER "; }";
const char html_main_css_buttons[] PROGMEM = 
"button:disabled { background-color: " COLOR_CONTROL_DISABLED_BACKGROUND "; color: " COLOR_CONTROL_DISABLED "; } button { background-color: " COLOR_CONTROL ";  border-radius:6px; margin:2px; padding: 4px 8px; }";
const char html_main_css_buttons_left[] PROGMEM = 
".btns_left { margin-left: -1px; border-top-left-radius: 0px; border-bottom-left-radius: 0px; }";
const char html_main_css_buttons_mid[] PROGMEM = 
".btns_mid { margin-left: -1px; margin-right: -1px; border-top-left-radius: 0px; border-bottom-left-radius: 0px; border-top-right-radius: 0px; border-bottom-right-radius: 0px; }";
const char html_main_css_buttons_right[] PROGMEM = 
".btns_right { margin-right: -1px; border-top-right-radius: 0px; border-bottom-right-radius: 0px; }";
const char html_main_css_buttons_attn[] PROGMEM =
".btns_attn { height:3em; border-radius:5px; border-color:" COLOR_CRITICAL_CONTROL_BORDER "; background-color:" COLOR_CRITICAL_CONTROL_BACKGROUND "; margin-bottom:5px; margin-top:5px; }";
const char html_main_css_end[] PROGMEM =
".aStatus { background-color:" COLOR_LIGHT_BACKGROUND "; color:" COLOR_LIGHT_FOREGROUND "; width: 80px; height: 2px; float: right; padding: 0px; margin: 2px;}"
"</STYLE>\r\n";

const char html_head_end[] PROGMEM =
"</head>\r\n";

const char htmlStringInvalid[] PROGMEM = "Invalid";