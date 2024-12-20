// power ----------------------------------------------------------------------
#include "PowerTile.h"

#if POWER == ON
  #include "../../lib/nv/Nv.h"

  #include "../../libApp/relay/Relay.h"

  #include "../CheckHelp.h"

  void powerTile() {
    char temp[256];

    strcpy_P(temp, htmlPowerBegin);
    www.sendContent(temp);

    #if POWER_DEVICE1_RELAY != OFF
      strcpy_P(temp, htmlPower1);
      if (relay.isOn(POWER_DEVICE1_RELAY)) check(temp, "%___PD1"); else erase(temp, "%___PD1");
      www.sendContent(temp);
    #endif
    #if POWER_DEVICE2_RELAY != OFF
      strcpy_P(temp, htmlPower2);
      if (relay.isOn(POWER_DEVICE2_RELAY)) check(temp, "%___PD2"); else erase(temp, "%___PD2");
      www.sendContent(temp);
    #endif
    #if POWER_DEVICE3_RELAY != OFF
      strcpy_P(temp, htmlPower3);
      if (relay.isOn(POWER_DEVICE3_RELAY)) check(temp, "%___PD3"); else erase(temp, "%___PD3");
      www.sendContent(temp);
    #endif
    #if POWER_DEVICE4_RELAY != OFF
      strcpy_P(temp, htmlPower4);
      if (relay.isOn(POWER_DEVICE4_RELAY)) check(temp, "%___PD4"); else erase(temp, "%___PD4");
      www.sendContent(temp);
    #endif
    #if POWER_DEVICE5_RELAY != OFF
      strcpy_P(temp, htmlPower5);
      if (relay.isOn(POWER_DEVICE5_RELAY)) check(temp, "%___PD5"); else erase(temp, "%___PD5");
      www.sendContent(temp);
    #endif
    #if POWER_DEVICE6_RELAY != OFF
      strcpy_P(temp, htmlPower6);
      if (relay.isOn(POWER_DEVICE6_RELAY)) check(temp, "%___PD6"); else erase(temp, "%___PD6");
      www.sendContent(temp);
    #endif

    strcpy_P(temp, htmlPowerEnd);
    www.sendContent(temp);
  }

  void powerTileAjax() {
    #if POWER_DEVICE1_RELAY != OFF
      www.sendContent("power1|"); www.sendContent(relay.isOn(POWER_DEVICE1_RELAY) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if POWER_DEVICE2_RELAY != OFF
      www.sendContent("power2|"); www.sendContent(relay.isOn(POWER_DEVICE2_RELAY) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if POWER_DEVICE3_RELAY != OFF
      www.sendContent("power3|"); www.sendContent(relay.isOn(POWER_DEVICE3_RELAY) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if POWER_DEVICE4_RELAY != OFF
      www.sendContent("power4|"); www.sendContent(relay.isOn(POWER_DEVICE4_RELAY) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if POWER_DEVICE5_RELAY != OFF
      www.sendContent("power5|"); www.sendContent(relay.isOn(POWER_DEVICE5_RELAY) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
    #if POWER_DEVICE6_RELAY != OFF
      www.sendContent("power6|"); www.sendContent(relay.isOn(POWER_DEVICE6_RELAY) ? "checked" : "unchecked"); www.sendContent("\n");
    #endif
  }

  void powerTileGet() {
    String s;
    UNUSED(s);

    #if POWER_DEVICE1_RELAY != OFF
      s = www.arg("pwr1");
      if (s.equals("true")) {
        relay.on(POWER_DEVICE1_RELAY);
        #if POWER_DEVICE1_MEMORY != OFF
          nv.write(NV_POWER_DEVICE1, (uint8_t)1);
        #endif
      } else
      if (s.equals("false")) {
        relay.off(POWER_DEVICE1_RELAY);
        #if POWER_DEVICE1_MEMORY != OFF
          nv.write(NV_POWER_DEVICE1, (uint8_t)0);
        #endif
      }
    #endif

    #if POWER_DEVICE2_RELAY != OFF
      s = www.arg("pwr2");
      if (s.equals("true")) {
        relay.on(POWER_DEVICE2_RELAY);
        #if POWER_DEVICE2_MEMORY != OFF
          nv.write(NV_POWER_DEVICE2, (uint8_t)1);
        #endif
      } else
      if (s.equals("false")) {
        relay.off(POWER_DEVICE2_RELAY);
        #if POWER_DEVICE2_MEMORY != OFF
          nv.write(NV_POWER_DEVICE2, (uint8_t)0);
        #endif
      }
    #endif

    #if POWER_DEVICE3_RELAY != OFF
      s = www.arg("pwr3");
      if (s.equals("true")) {
        relay.on(POWER_DEVICE3_RELAY);
        #if POWER_DEVICE3_MEMORY != OFF
          nv.write(NV_POWER_DEVICE3, (uint8_t)1);
        #endif
      } else
      if (s.equals("false")) {
        relay.off(POWER_DEVICE3_RELAY);
        #if POWER_DEVICE3_MEMORY != OFF
          nv.write(NV_POWER_DEVICE3, (uint8_t)0);
        #endif
      }
    #endif

    #if POWER_DEVICE4_RELAY != OFF
      s = www.arg("pwr4");
      if (s.equals("true")) {
        relay.on(POWER_DEVICE4_RELAY);
        #if POWER_DEVICE4_MEMORY != OFF
          nv.write(NV_POWER_DEVICE4, (uint8_t)1);
        #endif
      } else
      if (s.equals("false")) {
        relay.off(POWER_DEVICE4_RELAY);
        #if POWER_DEVICE4_MEMORY != OFF
          nv.write(NV_POWER_DEVICE4, (uint8_t)0);
        #endif
      }
    #endif

    #if POWER_DEVICE5_RELAY != OFF
      s = www.arg("pwr5");
      if (s.equals("true")) {
        relay.on(POWER_DEVICE5_RELAY);
        #if POWER_DEVICE5_MEMORY != OFF
          nv.write(NV_POWER_DEVICE5, (uint8_t)1);
        #endif
      } else
      if (s.equals("false")) {
        relay.off(POWER_DEVICE5_RELAY);
        #if POWER_DEVICE5_MEMORY != OFF
          nv.write(NV_POWER_DEVICE5, (uint8_t)0);
        #endif
      }
    #endif

    #if POWER_DEVICE6_RELAY != OFF
      s = www.arg("pwr6");
      if (s.equals("true")) {
        relay.on(POWER_DEVICE6_RELAY);
        #if POWER_DEVICE6_MEMORY != OFF
          nv.write(NV_POWER_DEVICE6, (uint8_t)1);
        #endif
      } else
      if (s.equals("false")) {
        relay.off(POWER_DEVICE6_RELAY);
        #if POWER_DEVICE6_MEMORY != OFF
          nv.write(NV_POWER_DEVICE6, (uint8_t)0);
        #endif
      }
    #endif

  }

#endif
