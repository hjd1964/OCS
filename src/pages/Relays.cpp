// relays -------------------------------------------------------------------------------------------
#include "Relays.h"

#include "../lib/ethernet/webServer/WebServer.h"
#include "../libApp/relay/Relay.h"
#include "../lib/nv/NV.h"

void relaysAjax() {
  for (int i = 1; i <= 18; i++) {
    String s = "r" + String(i);
    String a = www.arg(s);

    uint8_t state = 0;
    if (!a.equals(EmptyStr)) {
      if (a.equals("true")) {
        relay.on(i);
        state = (uint8_t)true;
      }
      if (a.equals("false")) {
        relay.off(i);
        state = (uint8_t)false;
      }
      state = state;
      
      // if this relay is from the "Power Panel" store the setting if requested
      if (a.equals("true") || a.equals("false")) {
        #if POWER_DEVICE1_RELAY != OFF && POWER_DEVICE1_MEMORY != OFF
          if (i == POWER_DEVICE1_RELAY) nv.write(NV_POWER_DEVICE1, state);
        #endif
        #if POWER_DEVICE2_RELAY != OFF && POWER_DEVICE2_MEMORY != OFF
          if (i == POWER_DEVICE2_RELAY) nv.write(NV_POWER_DEVICE2, state);
        #endif
        #if POWER_DEVICE3_RELAY != OFF && POWER_DEVICE3_MEMORY != OFF
          if (i == POWER_DEVICE3_RELAY) nv.write(NV_POWER_DEVICE3, state);
        #endif
        #if POWER_DEVICE4_RELAY != OFF && POWER_DEVICE4_MEMORY != OFF
          if (i == POWER_DEVICE4_RELAY) nv.write(NV_POWER_DEVICE4, state);
        #endif
        #if POWER_DEVICE5_RELAY != OFF && POWER_DEVICE5_MEMORY != OFF
          if (i == POWER_DEVICE5_RELAY) nv.write(NV_POWER_DEVICE5, state);
        #endif
        #if POWER_DEVICE6_RELAY != OFF && POWER_DEVICE6_MEMORY != OFF
          if (i == POWER_DEVICE6_RELAY) nv.write(NV_POWER_DEVICE6, state);
        #endif
      }

      // get relay state
      if (a.equals("get")) {
        s = String(relay.isOn(i));
        www.sendContent(s);
        break;
      }
    }
  }
}
