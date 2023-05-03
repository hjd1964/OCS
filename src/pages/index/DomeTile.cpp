// status --------------------------------------------------------------------------------------------------------------------
#include "DomeTile.h"

#if DOME == ON
  #include "../htmlHeaders.h"
  #include "../htmlScripts.h"

  #include "../../observatory/dome/Dome.h"

  void domeTile() {
    char temp[512] = "";

    strcpy_P(temp, htmlDomeBegin);
    www.sendContent(temp);

    domeContents();

    strcpy_P(temp, htmlDomeControlsBegin); www.sendContent(temp);

    sprintf_P(temp, htmlDomeAzimuth, (int)round(dome.getTargetAzimuth())); www.sendContent(temp);
    #if AXIS2_DRIVER_MODEL != OFF
      sprintf_P(temp, htmlDomeAltitude, (int)round(dome.getTargetAltitude())); www.sendContent(temp);
    #endif
    strcpy_P(temp, htmlDomeGoto); www.sendContent(temp);

    strcpy_P(temp, htmlDomeStop); www.sendContent(temp);

    strcpy_P(temp, htmlDomeHome); www.sendContent(temp);

    strcpy_P(temp, htmlDomePark1); www.sendContent(temp);
    strcpy_P(temp, htmlDomePark2); www.sendContent(temp);

    strcpy_P(temp, htmlDomeControlsEnd); www.sendContent(temp);

    strcpy_P(temp, htmlDomeEnd);
    www.sendContent(temp);
  }

  void domeContents() {
    char temp[512];
    if (dome.ready) {
      sprintf_P(temp, htmlDomeStatus, dome.statusMessage()); www.sendContent(temp);

      sprintf_P(temp, htmlDomePosition, "Azimuth", dome.getAzimuth()); www.sendContent(temp);
      #if AXIS2_DRIVER_MODEL != OFF
        sprintf_P(temp, htmlDomePosition, "Altitude", dome.getAltitude()); www.sendContent(temp);
      #endif

    } else {
      www.sendContent("&nbsp;&nbsp;Failed initialization!");
    }

  }
#endif
