// -----------------------------------------------------------------------------------------------------------------
// Observatory dome commands

#include "Dome.h"

#ifdef DOME_PRESENT

bool Dome::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {

	if (command[0] == 'D') {
    // :DC#  Dome Return Home
    //         Returns: nothing
    if (command[1] == 'C' && parameter[0] == 0) {
      dome.findHome();
      *numericReply = false;
    } else

    // :DF#  Dome Reset Home
    //         Returns: nothing
    if (command[1] == 'F' && parameter[0] == 0) {
      dome.reset();
      *numericReply = false;
    } else

    // :DH#  Dome Halt motion
    //         Returns: nothing
    if (command[1] == 'H' && parameter[0] == 0) {
      dome.stop();
      *numericReply = false;
    } else

    // :DP#  Dome goto park position
    //            Return: 0 on failure
    //                    1 on success
    if (command[1] == 'P' && parameter[0] == 0) {
      CommandError e = dome.park();
      if (e == CE_NONE) *commandError = CE_1; else { VF("MSG: Dome, park error "); VL(e); *commandError = e; }
    } else

    // :DQ#  Dome set park position
    //            Return: 0 on failure
    //                    1 on success
    if (command[1] == 'Q' && parameter[0] == 0) {
      CommandError e = dome.setpark();
      if (e == CE_NONE) *commandError = CE_1; else { VF("MSG: Dome, set park error "); VL(e); *commandError = e; }
    } else

    // :DR#  Dome restore park position
    //            Return: 0 on failure
    //                    1 on success
    if (command[1] == 'R' && parameter[0] == 0) {
      CommandError e = dome.unpark();
      if (e == CE_NONE) *commandError = CE_1; else { VF("MSG: Dome, unpark error "); VL(e); *commandError = e; }
    } else

    // :DZ#  Dome Get Azimuth (0 to 360 degrees)
    //         Returns: D.D
    if (command[1] == 'Z' && parameter[0] == 0) {
      sprintF(reply, "%0.3f", dome.getAzimuth());
      *numericReply = false;
    } else

    // :Dz[D.D]#  Dome Set Azimuth target (0 to 360 degrees)
    //         Returns: nothing
    if (command[1] == 'z') {
      float azimuth = atof(parameter);
      dome.setTargetAzimuth(azimuth);
      *numericReply = false;
    } else

    #if AXIS2_DRIVER_MODEL != OFF
      // :DA#  Dome Get Altitude (0 to 90 degrees)
      //         Returns: D.D
      if (command[1] == 'A' && parameter[0] == 0) {
        sprintF(reply, "%0.3f", dome.getAltitude());
        *numericReply = false;
      } else

      // :Da[D.D]#  Dome Set Altitude target (0 to 90 degrees)
      //         Returns: nothing
      if (command[1] == 'a') {
        float altitude = atof(parameter);
        dome.setTargetAltitude(altitude);
        *numericReply = false;
      } else
    #endif

    // :DN#       Dome Sync Target (Azimuth only)
    //            Returns:
    //              See :DS# command
    if (command[1] == 'N' && parameter[0] == 0) {
      CommandError e = dome.syncAzimuthTarget();
      strcpy(reply,"0");
      if (e >= CE_SLEW_ERR_BELOW_HORIZON && e <= CE_SLEW_ERR_UNSPECIFIED) reply[0] = (char)(e - CE_SLEW_ERR_BELOW_HORIZON) + '1';
      if (e == CE_NONE) reply[0] = '0';
      *numericReply = false;
      *supressFrame = true;
      *commandError = e;
    } else

    // :DS#       Dome Goto Target
    //            Returns:
    //              0=Goto is possible
    //              1=below the horizon limit
    //              2=above overhead limit
    //              3=controller in standby
    //              4=dome is parked
    //              5=Goto in progress
    //              6=outside limits (AXIS2_LIMIT_MAX, AXIS2_LIMIT_MIN, AXIS1_LIMIT_MIN/MAX, MERIDIAN_E/W)
    //              7=hardware fault
    //              8=already in motion
    //              9=unspecified error
    if (command[1] == 'S' && parameter[0] == 0) {
      D("Dome Goto =");
      CommandError e = dome.gotoAzimuthTarget();
      DL(e);
      #if AXIS2_DRIVER_MODEL != OFF
        if (e == CE_NONE) e = dome.gotoAltitudeTarget();
      #endif
      strcpy(reply,"0");
      if (e >= CE_SLEW_ERR_BELOW_HORIZON && e <= CE_SLEW_ERR_UNSPECIFIED) reply[0] = (char)(e - CE_SLEW_ERR_BELOW_HORIZON) + '1';
      if (e == CE_NONE) reply[0] = '0';
      *numericReply = false;
      *supressFrame = true;
      *commandError = e;
    } else

    //  :DU#  Get Dome Status
    //         Returns: 'P' if parked, 'K' if parking, 'S' if slewing, 'H' if at Home, 'I' if idle
    if (command[1] == 'U' && parameter[0] == 0) {
      if (dome.isParked()) reply[0] = 'P'; else
      if (settings.park.state == PS_PARKING) reply[0] = 'K'; else
      if (dome.isSlewing()) reply[0] = 'S'; else
      #if AXIS2_DRIVER_MODEL != OFF
        if (dome.getAzimuth() == 0.0F && dome.getAltitude() == 0.0F) reply[0] = 'H'; else
      #else
        if (dome.getAzimuth() == 0.0F) reply[0] = 'H'; else
      #endif
      reply[0] = 'I';
      reply[1] = 0;
      *numericReply = false;
    } else *commandError = CE_CMD_UNKNOWN;
	} else
  	return false;

  return true;
}

#endif
