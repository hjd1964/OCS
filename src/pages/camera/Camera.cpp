// -----------------------------------------------------------------------------------
// Observatory camera
#include "Camera.h"

void cameraPage() {
  char temp[256] = "";

  // send the header
  www.setContentLength(CONTENT_LENGTH_UNKNOWN);
  www.sendHeader("Cache-Control", "no-cache");
  www.send(200, "text/html", String());

  // send a standard http response header with some css
  strcpy_P(temp, html_head_begin); www.sendContent(temp);
  strcpy_P(temp, html_main_css_begin); www.sendContent(temp); 
  strcpy_P(temp, html_main_css_a); www.sendContent(temp);
  strcpy_P(temp, html_main_css_a1); www.sendContent(temp);
  strcpy_P(temp, html_main_css_a2); www.sendContent(temp);
  strcpy_P(temp, html_main_css_b); www.sendContent(temp);
  strcpy_P(temp, html_main_css_misc); www.sendContent(temp);
  strcpy_P(temp, html_main_css_end); www.sendContent(temp);
  strcpy_P(temp, html_head_end); www.sendContent(temp);

  pageHeader(PAGE_CAMERA);

  www.sendContent(F("<iframe id='obsImg' width='720px' height='480px' src='"));
  www.sendContent(CAMERA_WEBPAGE);
  www.sendContent(F("' title='Observatory Camera'>"));
  www.sendContent(F("</iframe>"));

  www.sendContent(F("<script>\n"));
  www.sendContent(F("window.setInterval(function() { reloadIFrame(); }, 3000);\n"));
  www.sendContent(F("function reloadIFrame() { document.getElementById('obsImg').src += ''; }\n"));
  www.sendContent(F("</script>\n"));

  www.sendContent(F("</div></body></html>\r\n"));
  www.sendContent("");
}
