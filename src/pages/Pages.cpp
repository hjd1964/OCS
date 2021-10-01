// -----------------------------------------------------------------------------------
// Display and process data from webpages
#include "Pages.h"

void check(char *ss, const char *rs) {
  char *w = strstr(ss,rs);
  if (w != NULL) { w[0]='c'; w[1]='h'; w[2]='e'; w[3]='c'; w[4]='k'; w[5]='e'; w[6]='d'; }
}

void erase(char *ss, const char *rs) {
  char *w = strstr(ss,rs);
  if (w != NULL) { w[0]=' '; w[1]=' '; w[2]=' '; w[3]=' '; w[4]=' '; w[5]=' '; w[6]=' '; }
}
