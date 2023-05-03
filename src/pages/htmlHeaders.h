#pragma once

#include "../Common.h"
#include "../lib/ethernet/webServer/WebServer.h"
#include "../lib/wifi/webServer/WebServer.h"

// common web site framework
const char html_head1[] PROGMEM =
"<!DOCTYPE HTML>\r\n"
"<html>\r\n<head>\r\n"
"<meta charset='utf-8'/>\r\n"
"<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\r\n";

const char html_head_refresh[] PROGMEM =
"<meta http-equiv=\"refresh\" content=\"5; URL=/index.htm\">\r\n";

const char html_main_css1[]  PROGMEM = "<STYLE>";
const char html_main_css2[]  PROGMEM = 
".a { background-color: #111111; } .t { padding: 10px 10px 20px 10px; border: 5px solid #551111; "
"margin: 25px 25px 0px 25px; color: #999999; background-color: #111111; }";
const char html_main_css3[] PROGMEM =
"input { width:4em; font-weight: bold; background-color: #A01010; padding: 2px 2px; }";
const char html_main_css4[] PROGMEM =
".b { padding: 10px; border-left: 5px solid #551111; overflow:hidden; border-right: 5px solid #551111; "
"border-bottom: 5px solid #551111; margin: 0px 25px 25px 25px; color: #999999; background-color: #111111; }";
const char html_main_css5[] PROGMEM =
"select { width:4em; font-weight: bold; background-color: #A01010; padding: 2px 2px; }";
const char html_main_css6[] PROGMEM =
".stopBtn {width:6em;height:2.5em;border-radius:5px;border-color:#f22;background-color:#dcc;margin-bottom:5px;margin-top:5px;}"
"h1 { text-align: right; } .g { color: #105010; font-weight: bold; }";
const char html_main_css7[] PROGMEM =
"a:hover, a:active { background-color: red; } .c { color: #A01010; font-weight: bold; }";
const char html_main_css8[] PROGMEM =
"a:link, a:visited { background-color: #332222; color: #a07070; border:1px solid red; "
"padding: 5px 10px; margin: 0px; text-align: center; text-decoration: none; display: inline-block; }";
const char html_main_css9[] PROGMEM =
"button { background-color: #A01010; font-weight: bold; border-radius: 5px; font-size: 12px; margin: 2px; padding: 4px 8px; }";
const char html_main_css10[] PROGMEM =
".obsControl { position: relative; font-size: 14px; width: 260px; height: 198px; float:left; padding: 10px; margin: 10px; "
"background-color: #EEEEEE; border-style: solid; border-width: 3px; border-color: red; }";
const char html_main_css11[] PROGMEM =
".aStatus { color: #505090; width: 80px; height: 2px; float: right; padding: 0px; margin: 2px; background-color: #CCCCCC;}"
"</STYLE>\r\n";

const char html_head3[] PROGMEM =
"</head>\r\n<body bgcolor=\"#26262A\">\r\n";

const char html_pageHeader1[] PROGMEM =
"<div class=\"t\"><table width=\"100%\"><tr><td><b><font size=\"5\">Observatory Control System"
"</font></b></td><td align=\"right\"><b>";

const char html_pageHeader2[] PROGMEM =
"</td></tr></table>";

const char html_pageHeader3[] PROGMEM =
"<br /></div><div class=\"b\">\r\n";
