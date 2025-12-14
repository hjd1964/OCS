// AutoClose plugin
#include "AutoClose.h"
#include <TimeLib.h>

void autoCloseWrapper() { autoClose.poll(); }

bool validTime() { return (now() < 315360000); }

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
    unsigned long interval = lastIsSafe ? 2000 : 500;
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
    if (overrideEnabled) return false; // block isSafe if override is on
    return safe;
}

void AutoClose::poll() {
    // Duplicate Safety::poll() logic for autoclose, but only if ROOF_AUTOCLOSE_SAFETY == OFF
    #if defined(ROOF_PRESENT) && (ROOF_AUTOCLOSE_SAFETY == OFF)
        if (roofAutoClose && validTime()) {
            if (hour() == 8 && !roofAutoCloseInitiated) {
                roofAutoCloseInitiated = true;
                roof.close();
            }
            if (hour() != 8) roofAutoCloseInitiated = false;
        }
    #endif
    updateWarningOutput();
}

bool AutoClose::command(char *reply, char *command, char *parameter, bool *supressFrame, bool *numericReply, CommandError *commandError) {
    // Accepts :SO0# or :SO1#
    if (command && strncmp(command, "SO", 2) == 0 && (command[2] == '0' || command[2] == '1') && command[3] == '#') {
        roofAutoClose = (command[2] == '1');
        snprintf(reply, 32, ":SO%d#", roofAutoClose ? 1 : 0);
        return true;
    }
        return true;
    }
    if (strcmp(command, ":GO#") == 0) {
        *supressFrame = false;
        *numericReply = false;
        strcpy(reply, overrideEnabled ? "Override=1" : "Override=0");
        return true;
    }
    UNUSED(*reply);
    UNUSED(*command);
    UNUSED(*parameter);
    UNUSED(*supressFrame);
    UNUSED(*numericReply);
    UNUSED(*commandError);
    return false;
}

AutoClose autoClose;
