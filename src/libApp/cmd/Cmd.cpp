// -----------------------------------------------------------------------------------
// Help with commands, etc.

#include "Cmd.h"

#if defined(SERIAL_IP) || defined(SERIAL_UART)

void MountCmd::commandBlind(const char* cmd, long timeOutMs) {

  // clear the queues and send the command
  #ifdef SERIAL_IP
    if (!SERIAL_IP.isConnected()) return;
    SERIAL_IP.setTimeout(timeOutMs);
    SERIAL_IP.flush();
    while (SERIAL_IP.available() > 0) SERIAL_IP.read();
    SERIAL_IP.print(cmd);
  #endif
  #ifdef SERIAL_UART
    SERIAL_UART.setTimeout(timeOutMs);
    SERIAL_UART.flush();
    while (SERIAL_UART.available() > 0) SERIAL_UART.read();
    SERIAL_UART.print(cmd);
  #endif
}

int MountCmd::commandBool(const char* cmd, long timeOutMs) {
  char response[80] = "";

  // clear the queues and send the command
  #ifdef SERIAL_IP
    if (!SERIAL_IP.isConnected()) return false;
    SERIAL_IP.setTimeout(timeOutMs);
    SERIAL_IP.flush();
    while (SERIAL_IP.available() > 0) SERIAL_IP.read();
    SERIAL_IP.print(cmd);
  #endif
  #ifdef SERIAL_UART
    SERIAL_UART.setTimeout(timeOutMs);
    SERIAL_UART.flush();
    while (SERIAL_UART.available() > 0) SERIAL_UART.read();
    SERIAL_UART.print(cmd);
  #endif

  unsigned long timeout = millis() + (unsigned long)timeOutMs;
  while ((long)(timeout - millis()) > 0) {
    int available;

    #ifdef SERIAL_IP
      available = SERIAL_IP.available();
    #endif
    #ifdef SERIAL_UART
      available = SERIAL_UART.available();
    #endif

    if (available) {
      int length = 0;
      #ifdef SERIAL_IP
        length = SERIAL_IP.readBytes(response, 1);
      #endif
      #ifdef SERIAL_UART
        length = SERIAL_UART.readBytes(response, 1);
      #endif

      response[length] = 0;
      break;
    }
  }

  if ((long)(timeout - millis()) <= 0) { DF("WRN: cmd "); D(cmd); DLF(" timed out"); }

  return (response[0] != 0);
}

int MountCmd::commandString(const char* cmd, char* response, long timeOutMs) {
  strcpy(response, "");

  // clear the queues and send the command
  #ifdef SERIAL_IP
    if (!SERIAL_IP.isConnected()) return false;
    SERIAL_IP.setTimeout(timeOutMs);
    SERIAL_IP.flush();
    while (SERIAL_IP.available() > 0) SERIAL_IP.read();
    SERIAL_IP.print(cmd);
  #endif
  #ifdef SERIAL_UART
    SERIAL_UART.setTimeout(timeOutMs);
    SERIAL_UART.flush();
    while (SERIAL_UART.available() > 0) SERIAL_UART.read();
    SERIAL_UART.print(cmd);
  #endif

  unsigned long timeout = millis() + (unsigned long)timeOutMs;

  // get full response, '#' terminated
  int responsePos = 0;
  char b = 0;
  while ((long)(timeout - millis()) > 0 && b != '#') {
    int available = 0;

    #ifdef SERIAL_IP
      available = SERIAL_IP.available();
    #endif
    #ifdef SERIAL_UART
      available = SERIAL_UART.available();
    #endif

    if (available) {
      #ifdef SERIAL_IP
        b = SERIAL_IP.read();
      #endif
      #ifdef SERIAL_UART
        b = SERIAL_UART.read();
      #endif

      response[responsePos] = b;
      responsePos++;
      if (responsePos > 79) responsePos = 79;
      response[responsePos] = 0;
    }
  }
  if ((long)(timeout - millis()) <= 0) { DF("WRN: cmd \""); D(cmd); DLF("\" timed out"); }

  return response[strlen(response) - 1] == '#';
}

MountCmd mount;

#endif
