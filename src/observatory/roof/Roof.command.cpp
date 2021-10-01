// -----------------------------------------------------------------------------------------------------------------
// Observatory roof commands

#include "Roof.h"

#if ROOF == ON

bool Roof::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {

	if (command[0] == 'R') {
    //  :RC#  Roof Close
    //         Returns: nothing
    if (command[1] == 'C' && parameter[0] == 0) {
      roof.close();
      *numericReply = false;
    } else

    //  :RO#  Roof Open
    //         Returns: nothing
    if (command[1] == 'O' && parameter[0] == 0) {
      roof.open();
      *numericReply = false;
    } else

    //  :RH#  Roof Stop
    //         Returns: nothing
    if (command[1] == 'H' && parameter[0] == 0) {
      roof.stop();
      roof.clearStatus();
      *numericReply = false;
    } else

    //  :R!#  Roof Safety Override
    //         Returns: 1 on success
    if (command[1] == '!' && parameter[0] == 0) {
      roof.setSafetyOverride();
    } else

    //  :R+#  Roof High Power Mode
    //         Returns: 1 on success
    if (command[1] == '!' && parameter[0] == 0) {
      roof.setMaxPower();
    } else

    //  :RS#  Roof Status
    //         Returns: status string
    if (command[1] == 'S' && parameter[0] == 0) {
      char ws[128];
      if (roof.isClosed()) strcpy(ws, "CLOSED"); else
      if (roof.isOpen()) strcpy(ws, "OPEN"); else strcpy(ws, roof.getStatus());
      ws[47] = 0; // never longer than 47 chars
      if (roof.isClosing()) sprintf(reply, "c,%s", ws); else
      if (roof.isOpen()) sprintf(reply, "o,%s", ws); else sprintf(reply, "i,%s", ws);
      *numericReply = false;
    } else

    //  :RSL#  Roof Status Last Error
    //         Returns: status string
    if (command[1] == 'S' && parameter[0] == 'L' && parameter[1] == 0) {
      strcpy(reply, roof.getLastError());
      *numericReply = false;
    } else *commandError = CE_CMD_UNKNOWN;
	} else
  	return false;

  return true;
}

#endif
