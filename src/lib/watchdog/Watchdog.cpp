#include "Watchdog.h"

#include "../../tasks/OnTask.h"

#if defined(TEENSYDUINO) && WATCHDOG != OFF

void watchdogWrapper() { watchdog.poll(); }

void Watchdog::init(int seconds) {
  if (this->seconds == -1) {
    this->seconds = seconds;

    // poll at 100ms
    VF("MSG: Watchdog, start monitor task (100ms rate priority 0)... ");
    uint8_t handle = tasks.add(100, 0, true, 0, watchdogWrapper, "wdog");
    if (handle) {
      VLF("success");
      if (tasks.requestHardwareTimer(handle, 2)) { VF(" (no hardware timer!)"); }
    } else { VLF("FAILED!"); }
  }
}

void Watchdog::poll() {
  if (!enabled) return;
  if (count++ > 10 * seconds) { HAL_RESET(); }
}

Watchdog watchdog;

#endif
