// dome -----------------------------------------------------------------------
#include "DomeTile.h"

#if DOME == ON
  #include "../htmlHeaders.h"
  #include "../htmlScripts.h"

  #include "../../observatory/dome/Dome.h"

  void domeTile() {
    char temp[400];

    strcpy_P(temp, htmlDomeBegin);
    www.sendContent(temp);

    if (dome.ready) {
      sprintf_P(temp, htmlDomeStatus, dome.statusMessage()); www.sendContent(temp);

      #if AXIS2_DRIVER_MODEL != OFF
        sprintf_P(temp, htmlDomeAltitudeStatus, dome.getAltitude()); www.sendContent(temp);
      #endif

      sprintf_P(temp, htmlDomeAzimuthStatus, dome.getAzimuth()); www.sendContent(temp);
    } else {
      www.sendContent("&nbsp;&nbsp;Failed initialization!");
    }

    strcpy_P(temp, htmlDomeControlsBegin); www.sendContent(temp);

    #if AXIS2_DRIVER_MODEL != OFF
      sprintf_P(temp, htmlDomeAltitude, (int)round(dome.getTargetAltitude())); www.sendContent(temp);
    #endif
    sprintf_P(temp, htmlDomeAzimuth, (int)round(dome.getTargetAzimuth())); www.sendContent(temp);

    strcpy_P(temp, htmlDomeGoto); www.sendContent(temp);

    strcpy_P(temp, htmlDomeStop); www.sendContent(temp);

    strcpy_P(temp, htmlDomeHome); www.sendContent(temp);

    strcpy_P(temp, htmlDomePark1); www.sendContent(temp);
    strcpy_P(temp, htmlDomePark2); www.sendContent(temp);

    strcpy_P(temp, htmlDomeControlsEnd); www.sendContent(temp);

    strcpy_P(temp, htmlDomeEnd);
    www.sendContent(temp);
  }

  void domeTileAjax() {
    char temp[40];

    www.sendContent("dome_sta|"); www.sendContent(dome.statusMessage()); www.sendContent("\n");

    sprintf(temp, "%1.1f&nbsp;&deg;", dome.getAltitude());
    www.sendContent("dome_alt|"); www.sendContent(temp); www.sendContent("\n");

    sprintf(temp, "%1.1f&nbsp;&deg;", dome.getAzimuth());
    www.sendContent("dome_azm|"); www.sendContent(temp); www.sendContent("\n");
  }

  void domeTileGet() {
    String azm = www.arg("dome_azm");
    if (!azm.equals(EmptyStr)) {
      int z = azm.toInt();
      if (z >= 0 && z <= 360) dome.setTargetAzimuth(z);
    }

    #if AXIS2_DRIVER_MODEL != OFF
      String alt = www.arg("dome_alt");
      if (!alt.equals(EmptyStr)) {
        int a = alt.toInt();
        if (a >= 0 && a <= 90) dome.setTargetAltitude(a);
      }
    #endif

    String s = www.arg("dome");
    if (!s.equals(EmptyStr)) {
      if (s.equals("goto")) {
        dome.gotoAzimuthTarget();
        #if AXIS2_DRIVER_MODEL != OFF
          dome.gotoAltitudeTarget();
        #endif
      }
      if (s.equals("sync")) dome.syncAzimuthTarget();
      if (s.equals("stop")) dome.stop();
      if (s.equals("home")) dome.findHome();
      if (s.equals("reset")) dome.reset();
      if (s.equals("park")) dome.park();
      if (s.equals("unpark")) dome.unpark();
      if (s.equals("setpark")) dome.setpark();
    }
  }

#endif
