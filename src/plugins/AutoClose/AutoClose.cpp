// AutoClose plugin
#include "AutoClose.h"
#include <TimeLib.h>

void autoCloseWrapper() { autoClose.poll(); }

bool isTimeValid() { return (now() < 315360000); }

void AutoClose::init() {
    VF("MSG: AutoClose, start monitor task (rate 1s priority 3)... ");
    pinMode(AUTOCLOSE_OUTPUT_PIN, OUTPUT);
    digitalWrite(AUTOCLOSE_OUTPUT_PIN, !AUTOCLOSE_OUTPUT_ON); // Ensure off
    if (tasks.add(100, 0, true, 3, autoCloseWrapper, "AutoClose")) { VLF("success"); } else { VLF("FAILED!"); }
}
void AutoClose::updateWarningOutput() {
    if (!overrideEnabled) {
        digitalWrite(AUTOCLOSE_OUTPUT_PIN, !AUTOCLOSE_OUTPUT_ON);
        outputState = false;
        return;
    }
    unsigned long now = millis();
    unsigned long interval = lastIsSafe ? 2000 : 250;
    if (now - lastToggle >= interval) {
        outputState = !outputState;
        digitalWrite(AUTOCLOSE_OUTPUT_PIN, outputState ? AUTOCLOSE_OUTPUT_ON : !AUTOCLOSE_OUTPUT_ON);
        lastToggle = now;
    }
}

bool AutoClose::isSafe() {
    bool safe = true;
    int safetyDeviceCount = 0;

    #if STAT_MAINS_SENSE != OFF
        if (sense.isOn(STAT_MAINS_SENSE)) {
            delayForMains = 0;
        } else {
            if (delayForMains < STAT_MAINS_SAFETY_DELAY) delayForMains++; else safe = false;
        }
        safetyDeviceCount++;
    #endif

    #ifdef WEATHER_PRESENT
        float f;
        UNUSED(f);

        #if WEATHER_RAIN == ON
            f = weatherSensor.rain();
            if (isnan(f) || f < 2.0F) safe = false;
            safetyDeviceCount++;
        #endif
        #if WEATHER_CLOUD_CVR == ON
            f = weather.getAvgSkyDiffTemp();
            if (isnan(f) || f < -200 || f > WEATHER_SAFE_THRESHOLD) safe = false;
            safetyDeviceCount++;
        #endif
        #if WEATHER_WIND_SPD == ON
            f = weatherSensor.windspeed();
            if (isnan(f) || f < 0 || f > WEATHER_WIND_SPD_THRESHOLD) safe = false;
            #if WEATHER_WIND_ACCUMULATE > 0
                if (!isnan(f) && f > WEATHER_WIND_SPD_THRESHOLD && wa < waMax) wa += (f * WEATHER_WIND_ACCUMULATE);
                if (wa > waMax) wa = waMax;
                if (!isnan(f) && f <= WEATHER_WIND_SPD_THRESHOLD && wa > 0) wa -= ((WEATHER_WIND_SPD_THRESHOLD - f) / WEATHER_WIND_ACCUMULATE);
                if (wa < 0) wa = 0;
                if (wa > 0) safe = false;
            #endif
            safetyDeviceCount++;
        #endif
    #endif
    if (safetyDeviceCount == 0) safe = false;
    lastIsSafe = safe;
    return safe;
}

void AutoClose::poll() {
    // Duplicate Safety::poll() logic for autoclose, but only if ROOF_AUTOCLOSE_SAFETY == OFF
    #if defined(ROOF_PRESENT) && (ROOF_AUTOCLOSE_SAFETY == OFF)
    if (!overrideEnabled) {    
      if (roofAutoClose && isTimeValid()) {
            if (hour() == 8 && !roofAutoCloseInitiated) {
                roofAutoCloseInitiated = true;
                roof.close();
            }
            if (hour() != 8) roofAutoCloseInitiated = false;
        }
      if (!isSafe()) {
        // if the roof isn't closed, and motion is idle, close it
        if (!roof.isClosed() && !roof.isMoving()) roof.close();
      }
    }
    #endif
    updateWarningOutput();
}

bool AutoClose::command(char *reply, char *command, char *parameter, bool *supressFrame, bool *numericReply, CommandError *commandError) {

    if (command[0] == 'S' && command[1] == 'O' && command[2] == 0) {
        // :SO0# or :SO1#
        if (parameter[0] == '0' && parameter[1] == 0) {
            overrideEnabled = false;
            strcpy(reply, "OFF");
            *supressFrame = false;
            *numericReply = false;
            return true;
        } else if (parameter[0] == '1' && parameter[1] == 0) {
            overrideEnabled = true;
            strcpy(reply, "ON");
            *supressFrame = false;
            *numericReply = false;
            return true;
        } else {
            *commandError = CE_PARAM_FORM;
            return false;
        }
    } else if (command[0] == 'G' && command[1] == 'O' && command[2] == 0) {
        // :GO#
        if (parameter[0] == 0) {
            strcpy(reply, overrideEnabled ? "ON" : "OFF");
            *supressFrame = false;
            *numericReply = false;
            return true;
        } else {
            *commandError = CE_PARAM_FORM;
            return false;
        }
    }
    // Not handled
    return false;
}

AutoClose autoClose;
