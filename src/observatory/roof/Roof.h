// -----------------------------------------------------------------------------------------------------------------
// Roof control functions
#pragma once

#include "../../Common.h"

#ifdef ROOF_PRESENT

typedef enum RoofError {
  RERR_NONE,
  RERR_OPEN_SAFETY_INTERLOCK,
  RERR_CLOSE_SAFETY_INTERLOCK,
  RERR_OPEN_UNKNOWN,
  RERR_OPEN_LIMIT_SW,
  RERR_OPEN_MAX_TIME,
  RERR_OPEN_MIN_TIME,
  RERR_CLOSE_UNKNOWN,
  RERR_CLOSE_LIMIT_SW,
  RERR_CLOSE_MAX_TIME,
  RERR_CLOSE_MIN_TIME,
  RERR_LIMIT_SW,
  RERR_CLOSE_EXCEPT_OPENED_LIMIT_SW_ON,
  RERR_CLOSE_EXCEPT_CLOSED,
  RERR_CLOSE_LOCATION_UNKNOWN,
  RERR_DIRECTION_UNKNOWN,
  RERR_CLOSE_EXCEPT_IN_MOTION,
  RERR_OPEN_EXCEPT_CLOSED_LIMIT_SW_ON,
  RERR_OPEN_EXCEPT_OPENED,
  RERR_OPEN_LOCATION_UNKNOWN,
  RERR_OPEN_EXCEPT_IN_MOTION,
  RERR_CLOSE_EXCEPT_MOUNT_NOT_PARKED
} RoofError;

#include "../../libApp/commands/ProcessCmds.h"

typedef struct RoofFault {
  uint16_t openUnknown: 1;
  uint16_t openInterlock: 1;
  uint16_t openLimitSW: 1;
  uint16_t openOverTime: 1;
  uint16_t openUnderTime: 1;
  uint16_t closeUnknown: 1;
  uint16_t closeInterlock: 1;
  uint16_t closeLimitSW: 1;
  uint16_t closeOverTime: 1;
  uint16_t closeUnderTime: 1;
  uint16_t closeNotParked: 1;
} RoofFault;

class Roof {
  public:
    // process commands associated with the ROOF
    bool command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError);

    // this gets called once on startup to initialize roof operation
    void init();

    // Start opening the roof, returns true if successful or false otherwise
    bool open();

    // Start closing the roof, returns true if successful or false otherwise
    bool close();

    // stop the roof, this must be ISR safe!
    void stop();

    // clear errors
    void clearStatus(bool last = true);

    // returns an error description string if an error has occured, otherwise must return "Travel: n%" or "No Error"
    const char * getStatus();

    // returns an error description string if an error has occured, "" if no error
    const char * getLastError();

    // true if the roof is closed
    bool isClosed();

    // true if the roof is opened
    bool isOpen();

    // true if the roof is moving
    bool isMoving();

    // true if the roof is moving (closing)
    bool isClosing();

    // true if the roof is moving (opening)
    bool isOpening();

    // safety override, ignores stuck limit switch and timeout
    void setSafetyOverride();

    // required
    bool setSafetyOverride(bool value);

    // forces pwm power to 100%
    void setMaxPower();

    // required
    bool isMaxPower();

    // for soft start etc, pwm power level
    int powerLevel();

    // called repeatedly to control roof movement
    void poll();

    // called repeatedly to check if the mount is parked to trigger roof close
    bool parkCheckPoll();

  private:
    // called repeatedly to open the roof
    void continueOpening();

    // called repeatedly to close the roof
    void continueClosing();

    // roof status and errors
    volatile char state = 'i';
    RoofFault fault = {false, false, false, false, false, false, false, false, false, false, false};
    RoofError lastError = RERR_NONE;
    
    // roof power and safety
    volatile bool safetyOverride = false;
    volatile bool maxPower = false;
    volatile int currentPower = 0;

    // roof timing and travel
    const long timeAvg = (long)(ROOF_TIME_AVG)*1000L;
    const long timeErrorLimit = (long)(ROOF_TIME_TOL)*1000L;
    long lastSecondsOfTravel, timeLeftToOpenAtStart, timeLeftToCloseAtStart;
    long travel = 0;
    unsigned long openStartTime, closeStartTime;
    int waitingForPark = 0;                  // counter for waiting period

    const char * ErrorMessage[22] = {
      "",                                    // 0
      "Error: Open safety interlock",        // 1
      "Error: Close safety interlock",       // 2
      "Error: Open unknown error",           // 3
      "Error: Open limit sw fail",           // 4
      "Error: Open over time",               // 5
      "Error: Open under time",              // 6
      "Error: Close unknown error",          // 7
      "Error: Close limit sw fail",          // 8
      "Error: Close over time",              // 9
      "Error: Close under time",             // 10
      "Error: Limit switch malfunction",     // 11
      "Error: Closed/opened limit sw on",    // 12
      "Warning: Already closed",             // 13
      "Error: Close location unknown",       // 14
      "Error: Motion direction unknown",     // 15
      "Error: Close already in motion",      // 16
      "Error: Opened/closed limit sw on",    // 17
      "Warning: Already open",               // 18
      "Error: Open location unknown",        // 19
      "Error: Open already in motion",       // 20
      "Error: Close mount not parked"        // 21
    };
};

extern Roof roof;

#endif
