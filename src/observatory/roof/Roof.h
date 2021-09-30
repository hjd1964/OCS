// -----------------------------------------------------------------------------------------------------------------
// Roof control functions
#pragma once

#include "../../Common.h"

#if ROOF == ON

#include "../../commands/ProcessCmds.h"

#define RSR_OPEN_INTERLOCK      512
#define RSR_CLOSE_INTERLOCK     256
#define RSR_OPEN_UNKNOWN_ERROR  128
#define RSR_OPEN_LIMIT_SW_FAIL  64
#define RSR_OPEN_OVER_TIME      32
#define RSR_OPEN_UNDER_TIME     16
#define RSR_CLOSE_UNKNOWN_ERROR 8
#define RSR_CLOSE_LIMIT_SW_FAIL 4
#define RSR_CLOSE_OVER_TIME     2
#define RSR_CLOSE_UNDER_TIME    1
#define RSR_NO_ERROR            0

class RollOffRoof {
  public:
    // process commands associated with the ROOF
    bool command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError);

    // this gets called once on startup to initialize roof operation (required)
    void init();

    // called repeatedly if roof is moving (required)
    void poll();

    // Start opening the roof, returns true if successful or false otherwise (required)
    bool open();

    // Start closing the roof, returns true if successful or false otherwise (required)
    bool close();

    // stop the roof, this must be ISR safe! (required)
    void stop();

    // clear errors (required)
    void clearStatus();

    // returns an error description string if an error has occured, otherwise must return "Travel: n%" or "No Error" (required)
    String getStatus();

    // returns an error description string if an error has occured, "" if no error (required)
    String getLastError();

    // true if the roof is closed (required)
    bool isClosed();

    // true if the roof is opened (required)
    bool isOpen();

    // true if the roof is moving (required)
    bool isMoving();

    // true if the roof is moving (closing, required)
    bool isClosing();

    // true if the roof is moving (opening, required)
    bool isOpening();

    // safety override, ignores stuck limit switch and timeout (required)
    void setSafetyOverride();

    // required
    bool setSafetyOverride(bool value);

    // forces pwm power to 100%
    void setMaxPower();

    // required
    bool isMaxPower();

    // for soft start etc, pwm power level (required)
    int powerLevel();

  private:
    // called repeatedly to open the roof
    void continueOpening();

    // called repeatedly to close the roof
    void continueClosing();

    bool autoClose = ROOF_AUTOCLOSE_DAWN_DEFAULT == ON;
    bool autoCloseInitiated = false;

    // roof status and errors
    volatile char state = 'i';
    uint16_t statusRegister = RSR_NO_ERROR;
    String lastError = "";

    // roof power and safety
    volatile bool safetyOverride = false;
    volatile bool maxPower = false;
    volatile int currentPower = 0;

    // roof timing and travel
    const long timeAvg = (long)(ROOF_TIME_AVG)*1000L;
    const long timeErrorLimit = (long)(ROOF_TIME_TOL)*1000L;
    long lastSecondsOfTravel, openStartTime, timeLeftToOpenAtStart, closeStartTime, timeLeftToCloseAtStart;
    long travel = 0;
};

extern Roof roof;

#endif
