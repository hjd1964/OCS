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
  strcpy_P(temp, html_main_css1); www.sendContent(temp); 
  strcpy_P(temp, html_main_css2); www.sendContent(temp);
  strcpy_P(temp, html_main_css4); www.sendContent(temp);
  strcpy_P(temp, html_main_css6); www.sendContent(temp);
  strcpy_P(temp, html_main_css7); www.sendContent(temp);
  strcpy_P(temp, html_main_css8); www.sendContent(temp);
  strcpy_P(temp, html_main_css10); www.sendContent(temp);
  strcpy_P(temp, html_main_css11); www.sendContent(temp);
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
