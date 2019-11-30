// -----------------------------------------------------------------------------------
// Web server

// misc.
#define WebSocketTimeOut 10000
typedef void (* webFunction) (EthernetClient *client);

class WebServer {
  public:
    void init();
    void handleClient();
    void setResponseHeader(const char *str);
    void on(String fn, webFunction handler);
#ifdef SD_CARD_ON
    void on(String fn);
#endif
    void onNotFound(webFunction handler);
    String arg(String id);

    bool SDfound=false;
  private:
#ifdef SD_CARD_ON
    void sdPage(String fn, EthernetClient *client);
#endif

    String inputBuffer;
    char responseHeader[200]="";
#ifdef SD_CARD_ON
    bool modifiedSinceFound=false;
#endif

    webFunction notFoundHandler=NULL;
    webFunction handlers[20];
    String handlers_fn[20];
    int handler_count;
    
    String parameters[20];
    String values[20];
    int parameter_count;
};

// pre-defined headers
const char http_defaultHeader[] PROGMEM = "HTTP/1.1 200 OK\r\n" "Content-Type: text/html\r\n" "Connection: close\r\n" "\r\n";
const char http_autoRefreshHeader[] PROGMEM = "HTTP/1.1 200 OK\r\n" "Content-Type: text/html\r\n" "Connection: close\r\n" "Refresh: 5\r\n" "\r\n";
const char http_js304Header[] PROGMEM = "HTTP/1.1 304 OK\r\n" "Content-Type: application/javascript\r\n" "Etag: \"3457807a63ac7bdabf8999b98245d0fe\"\r\n" "Last-Modified: Mon, 13 Apr 2015 15:35:56 GMT\r\n" "Connection: close\r\n" "\r\n";
const char http_jsHeader[] PROGMEM = "HTTP/1.1 200 OK\r\n" "Content-Type: application/javascript\r\n" "Etag: \"3457807a63ac7bdabf8999b98245d0fe\"\r\n" "Last-Modified: Mon, 13 Apr 2015 15:35:56 GMT\r\n" "Connection: close\r\n" "\r\n";

// common web site framework
const char html_head1[]      PROGMEM = "<!DOCTYPE HTML>\r\n<html>\r\n<head>\r\n<meta charset='utf-8'/>\r\n";
const char html_head_refresh[] PROGMEM = "<meta http-equiv=\"refresh\" content=\"5; URL=/index.htm\">\r\n";
const char html_main_css1[]  PROGMEM = "<STYLE>";
const char html_main_css2[]  PROGMEM = ".a { background-color: #111111; } .t { padding: 10px 10px 20px 10px; border: 5px solid #551111; margin: 25px 25px 0px 25px; color: #999999; background-color: #111111; }";
const char html_main_css3[]  PROGMEM = "input { width:4em; font-weight: bold; background-color: #A01010; padding: 2px 2px; }";
const char html_main_css4[]  PROGMEM = ".b { padding: 10px; border-left: 5px solid #551111; overflow:hidden; border-right: 5px solid #551111; border-bottom: 5px solid #551111; margin: 0px 25px 25px 25px; color: #999999; background-color: #111111; }";
const char html_main_css5[]  PROGMEM = "select { width:4em; font-weight: bold; background-color: #A01010; padding: 2px 2px; }";
const char html_main_css6[]  PROGMEM = "h1 { text-align: right; } .g { color: #105010; font-weight: bold; }";
const char html_main_css7[]  PROGMEM = "a:hover, a:active { background-color: red; } .c { color: #A01010; font-weight: bold; }";
const char html_main_css8[]  PROGMEM = "a:link, a:visited { background-color: #332222; color: #a07070; border:1px solid red; padding: 5px 10px; margin: 0px; text-align: center; text-decoration: none; display: inline-block; }";
const char html_main_css9[]  PROGMEM = "button { background-color: #A01010; font-weight: bold; border-radius: 5px; font-size: 12px; margin: 2px; padding: 4px 8px; }";
const char html_main_css10[] PROGMEM = ".obsControl { position: relative; font-size: 14px; width: 260px; height: 170px; float:left; padding: 10px; margin: 10px; background-color: #EEEEEE; border-style: solid; border-width: 3px; border-color: red; }"
                                       ".aStatus { color: #505090; width: 60px; height: 2px; float: right; padding: 0px; margin: 2px; background-color: #CCCCCC;} </STYLE>\r\n";

const char html_head3[]      PROGMEM = "</head>\r\n<body bgcolor=\"#26262A\">\r\n";

const char html_pageHeader1[] PROGMEM = "<div class=\"t\"><table width=\"100%\"><tr><td><b><font size=\"5\">Observatory Control System</font></b></td><td align=\"right\"><b>" FirmwareName " " FirmwareNumber "</b>";
const char html_pageHeader2[] PROGMEM = "</td></tr></table>";

const char html_links1[] PROGMEM = "<a href=\"/index.htm\" style=\"background-color: #222222;\">Overview</a>";
const char html_links1s[] PROGMEM = "<a href=\"/index.htm\" style=\"background-color: #552222;\">Overview</a>";
#if defined(WEATHER_ON) && defined(SD_CARD_ON)
const char html_links2[] PROGMEM = "<a href=\"/weatherpage.htm\" style=\"background-color: #222222;\">Weather</a>";
const char html_links2s[] PROGMEM = "<a href=\"/weatherpage.htm\" style=\"background-color: #552222;\">Weather</a>";
#if defined(WEATHER_SKY_QUAL_ON) || defined(WEATHER_CLOUD_CVR_ON)
const char html_links3[] PROGMEM = "<a href=\"/skypage.htm\" style=\"background-color: #222222;\">Sky Conditions</a>";
const char html_links3s[] PROGMEM = "<a href=\"/skypage.htm\" style=\"background-color: #552222;\">Sky Conditions</a>";
#endif
#endif

const char html_pageHeader3[] PROGMEM = "<br /></div><div class=\"b\">\r\n";
