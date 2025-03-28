// -----------------------------------------------------------------------------------
// Command processing

#include "../../Common.h"

#include "../../lib/tasks/OnTask.h"
#include "../../lib/convert/Convert.h"

#include "../../observatory/Observatory.h"
#include "ProcessCmds.h"

#ifdef MOUNT_PRESENT
  #if ST4_INTERFACE == ON && ST4_HAND_CONTROL == ON
    #include "../serial/Serial_ST4_Master.h"
  #endif
  #include "../serial/Serial_Local.h"
#endif

#if DEBUG != OFF
  #define L_CE_NONE                    "no errors"
  #define L_CE_1                       "no error true"
  #define L_CE_0                       "no error false/fail"
  #define L_CE_CMD_UNKNOWN             "command unknown"
  #define L_CE_REPLY_UNKNOWN           "invalid reply"
  #define L_CE_PARAM_RANGE             "parameter out of range"
  #define L_CE_PARAM_FORM              "bad parameter format"
  #define L_CE_ALIGN_FAIL              "align failed"
  #define L_CE_ALIGN_NOT_ACTIVE        "align not active"
  #define L_CE_NOT_PARKED_OR_AT_HOME   "not parked or at home"
  #define L_CE_PARKED                  "already parked"
  #define L_CE_PARK_FAILED             "park failed"
  #define L_CE_NOT_PARKED              "not parked"
  #define L_CE_NO_PARK_POSITION_SET    "no park position set"
  #define L_CE_SLEW_FAIL               "goto failed"
  #define L_CE_LIBRARY_FULL            "library full"
  #define L_CE_SLEW_ERR_BELOW_HORIZON  "goto below horizon"
  #define L_CE_SLEW_ERR_ABOVE_OVERHEAD "goto above overhead"
  #define L_CE_SLEW_ERR_IN_STANDBY     "slew in standby"
  #define L_CE_SLEW_ERR_IN_PARK        "slew in park"
  #define L_CE_SLEW_ERR_SLEW           "already in goto"
  #define L_CE_SLEW_ERR_OUTSIDE_LIMITS "outside limits"
  #define L_CE_SLEW_ERR_HARDWARE_FAULT "hardware fault"
  #define L_CE_MOUNT_IN_MOTION         "mount in motion"
  #define L_CE_SLEW_ERR_UNSPECIFIED    "other"
  #define L_CE_UNK                     "unknown"

  static const char commandErrorStr[26][25] = {
  L_CE_NONE, L_CE_1, L_CE_0, L_CE_CMD_UNKNOWN, L_CE_REPLY_UNKNOWN, L_CE_PARAM_RANGE,
  L_CE_PARAM_FORM, L_CE_ALIGN_FAIL, L_CE_ALIGN_NOT_ACTIVE, L_CE_NOT_PARKED_OR_AT_HOME,
  L_CE_PARKED, L_CE_PARK_FAILED, L_CE_NOT_PARKED, L_CE_NO_PARK_POSITION_SET, L_CE_SLEW_FAIL,
  L_CE_LIBRARY_FULL, L_CE_SLEW_ERR_BELOW_HORIZON, L_CE_SLEW_ERR_ABOVE_OVERHEAD,
  L_CE_SLEW_ERR_IN_STANDBY, L_CE_SLEW_ERR_IN_PARK, L_CE_SLEW_ERR_SLEW, L_CE_SLEW_ERR_OUTSIDE_LIMITS,
  L_CE_SLEW_ERR_HARDWARE_FAULT, L_CE_MOUNT_IN_MOTION, L_CE_SLEW_ERR_UNSPECIFIED, L_CE_UNK
  };
#endif

// command processors
#ifdef SERIAL_A
  CommandProcessor processCommandsA(SERIAL_A_BAUD_DEFAULT,'A');
  void processCmdsA() { processCommandsA.poll(); }
#endif
#ifdef SERIAL_B
  CommandProcessor processCommandsB(SERIAL_B_BAUD_DEFAULT,'B');
  void processCmdsB() { processCommandsB.poll(); }
#endif
#ifdef SERIAL_C
  CommandProcessor processCommandsC(SERIAL_C_BAUD_DEFAULT,'C');
  void processCmdsC() { processCommandsC.poll(); }
#endif
#ifdef SERIAL_D
  CommandProcessor processCommandsD(SERIAL_D_BAUD_DEFAULT,'D');
  void processCmdsD() { processCommandsD.poll(); }
#endif
#ifdef SERIAL_ST4
  CommandProcessor processCommandsST4(9600,'S');
  void processCmdsST4() { processCommandsST4.poll(); }
#endif
#if SERIAL_BT_MODE == SLAVE
  CommandProcessor processCommandsBT(9600,'T');
  void processCmdsBT() { processCommandsBT.poll(); }
#endif
#ifdef SERIAL_SIP
  CommandProcessor processCommandsSIP(9600,'I');
  void processCmdsSIP() { ::yield(); processCommandsSIP.poll(); }
#endif
#ifdef SERIAL_PIP1
  CommandProcessor processCommandsPIP1(9600,'1');
  void processCmdsPIP1() { ::yield(); processCommandsPIP1.poll(); }
#endif
#ifdef SERIAL_LOCAL
  CommandProcessor processCommandsLocal(9600,'L');
  void processCmdsLocal() { processCommandsLocal.poll(); }
#endif

CommandProcessor::CommandProcessor(long baud, char channel) {
  this->channel = channel;
  serialBaud = baud;
}

CommandProcessor::~CommandProcessor() {
  SerialPort.end();
}

void CommandProcessor::poll() {
  if (!serialReady) { delay(200); SerialPort.begin(serialBaud); serialReady = true; }
  if (SerialPort.available()) buffer.add(SerialPort.read()); else return;

  if (buffer.ready()) {
    char reply[50] = "";
    bool numericReply = true;
    bool supressFrame = false;

    commandError = command(reply, buffer.getCmd(), buffer.getParameter(), &supressFrame, &numericReply);

    if (numericReply) {
      if (commandError != CE_NONE && commandError != CE_1) strcpy(reply,"0"); else strcpy(reply,"1");
      supressFrame = true;
    }
    if (strlen(reply) > 0 || buffer.checksum) {
      if (buffer.checksum) {
        appendChecksum(reply);
        strcat(reply, buffer.getSeq());
        supressFrame = false;
      }
      if (!supressFrame) strcat(reply,"#");
      SerialPort.write(reply);
    }

    // debug, log errors and/or commands
    #if DEBUG_ECHO_COMMANDS == ON
      DF("MSG: cmd"); D(channel); D(" = "); D(buffer.getCmd()); D(buffer.getParameter()); DF(", reply = "); D(reply);
    #endif
    if (commandError != CE_NULL) {
      lastCommandError = commandError;
      #if DEBUG_ECHO_COMMANDS == ON
        if (commandError > CE_0) { DF(", Error "); D(commandErrorStr[commandError]); }
      #endif
    }
    #if DEBUG_ECHO_COMMANDS == ON
      DL("");
    #endif

    buffer.flush();
  }
}

CommandError CommandProcessor::command(char *reply, char *command, char *parameter, bool *supressFrame, bool *numericReply) {
  commandError = CE_NONE;

  // handle telescope commands
  if (observatory.command(reply, command, parameter, supressFrame, numericReply, &commandError)) return commandError;

  // silent bool "errors" allow processing commands more than once
  if (commandError == CE_0 || commandError == CE_1) return commandError;

  // :SB[n]#    Set Baud Rate where n is an ASCII digit (1..9) with the following interpertation
  //            0=115.2K, 1=56.7K, 2=38.4K, 3=28.8K, 4=19.2K, 5=14.4K, 6=9600, 7=4800, 8=2400, 9=1200
  //            Returns: 1 (at the current baud rate and then changes to the new rate for further communication)
  if (command[0] == 'S' && command[1] == 'B') {
    int rate = parameter[0] - '0';
    if (rate >= 0 && rate <= 9) {
      const static long baud[10] = {115200, 56700, 38400, 28800, 19200, 14400, 9600, 4800, 2400, 1200};
      SerialPort.print("1");
      tasks.yield(50);
      SerialPort.begin(baud[rate]);
      *numericReply = false;
    } else commandError = CE_PARAM_RANGE;
    return commandError;
  } else

  // :GX9F#     Get internal MCU temperature in deg. C
  //            Returns: +/-n.n
  if (command[0] == 'G' && command[1] == 'X' && parameter[0] == '9' && parameter[1] == 'F' && parameter[2] == 0) {
    float t = HAL_TEMP();
    if (!isnan(t)) { sprintF(reply, "%1.0f", t); *numericReply = false; } else { *numericReply = true; commandError = CE_0; }
    return commandError;
  } else

  return CE_CMD_UNKNOWN;
}

void CommandProcessor::appendChecksum(char *s) {
  char HEXS[3] = "";
  uint8_t cks = 0; for (unsigned int cksCount0 = 0; cksCount0 < strlen(s); cksCount0++) { cks += s[cksCount0]; }
  sprintf(HEXS, "%02X", cks);
  strcat(s, HEXS);
}

void commandChannelInit() {
  // Command processing
  // add tasks to process commands
  // period ms (0=idle), duration ms (0=forever), repeat, priority (highest 0..7 lowest), task_handle
  uint8_t handle;
  #ifdef HAL_SLOW_PROCESSOR
    long comPollRate = 2000;
  #else
    long comPollRate = 500;
  #endif
  #ifdef SERIAL_A
    VF("MSG: Setup, start command channel A task (priority 5)... ");
    handle = tasks.add(0, 0, true, 5, processCmdsA, "CmdA");
    if (handle) { VLF("success"); } else { VLF("FAILED!"); }
    tasks.setPeriodMicros(handle, comPollRate);
  #endif
  #ifdef SERIAL_B
    VF("MSG: Setup, start command channel B task (priority 5)... ");
    handle = tasks.add(0, 0, true, 5, processCmdsB, "CmdB");
    if (handle) { VLF("success"); } else { VLF("FAILED!"); }
    tasks.setPeriodMicros(handle, comPollRate);
  #endif
  #ifdef SERIAL_C
    VF("MSG: Setup, start command channel C task (priority 5)... ");
    handle = tasks.add(0, 0, true, 5, processCmdsC, "CmdC");
    if (handle) { VLF("success"); } else { VLF("FAILED!"); }
    tasks.setPeriodMicros(handle, comPollRate);
  #endif
  #ifdef SERIAL_D
    VF("MSG: Setup, start command channel D task (priority 5)... ");
    handle = tasks.add(0, 0, true, 5, processCmdsD, "CmdD")) { VLF("success"); } else { VLF("FAILED!"); }
    if (handle) { VLF("success"); } else { VLF("FAILED!"); }
    tasks.setPeriodMicros(handle, comPollRate);
  #endif
  #ifdef SERIAL_ST4
    VF("MSG: Setup, start command channel ST4 task (priority 5)... ");
    handle = tasks.add(0, 0, true, 5, processCmdsST4, "CmdS");
    if (handle) { VLF("success"); } else { VLF("FAILED!"); }
    tasks.setPeriodMicros(handle, comPollRate*4);
  #endif
  #if SERIAL_BT_MODE == SLAVE
    VF("MSG: Setup, start command channel BT task (priority 5)... ");
    handle = tasks.add(0, 0, true, 5, processCmdsBT, "CmdT");
    if (handle) { VLF("success"); } else { VLF("FAILED!"); }
    tasks.setPeriodMicros(handle, comPollRate);
  #endif
  #ifdef SERIAL_SIP
    VF("MSG: Setup, start command channel SIP task (priority 5)... ");
    handle = tasks.add(0, 0, true, 5, processCmdsSIP, "CmdI");
    if (handle) { VLF("success"); } else { VLF("FAILED!"); }
    tasks.setPeriodMicros(handle, comPollRate);
  #endif
  #ifdef SERIAL_PIP1
    VF("MSG: Setup, start command channel PIP1 task (priority 5)... ");
    handle = tasks.add(0, 0, true, 5, processCmdsPIP1, "Cmd1");
    if (handle) { VLF("success"); } else { VLF("FAILED!"); }
    tasks.setPeriodMicros(handle, comPollRate);
  #endif
  #ifdef SERIAL_LOCAL
    VF("MSG: Setup, start command channel Local task (priority 5)... ");
    if (tasks.add(3, 0, true, 5, processCmdsLocal, "PrcCmdL")) { VLF("success"); } else { VLF("FAILED!"); }
  #endif
}
