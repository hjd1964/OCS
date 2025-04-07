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
      www.sendContent("<div class='obsSwLine'>");
      www.sendContent(POWER_DEVICE1_NAME);
      www.sendContent("</div><div class='obsSwCtrl'>");
      sprintf_P(temp, html_powerControl, "1","on","left","1","on",L_ON);
      www.sendContent(temp);
      sprintf_P(temp, html_powerControl, "1","off","right","1","off",L_OFF);
      www.sendContent(temp);
      www.sendContent("</div><br/>");
    #endif
    #if POWER_DEVICE2_RELAY != OFF
      www.sendContent("<div class='obsSwLine'>");
      www.sendContent(POWER_DEVICE2_NAME);
      www.sendContent("</div><div class='obsSwCtrl'>");
      sprintf_P(temp, html_powerControl, "2","on","left","2","on",L_ON);
      www.sendContent(temp);
      sprintf_P(temp, html_powerControl, "2","off","right","2","off",L_OFF);
      www.sendContent(temp);
      www.sendContent("</div><br/>");
    #endif
    #if POWER_DEVICE3_RELAY != OFF
      www.sendContent("<div class='obsSwLine'>");
      www.sendContent(POWER_DEVICE3_NAME);
      www.sendContent("</div><div class='obsSwCtrl'>");
      sprintf_P(temp, html_powerControl, "3","on","left","3","on",L_ON);
      www.sendContent(temp);
      sprintf_P(temp, html_powerControl, "3","off","right","3","off",L_OFF);
      www.sendContent(temp);
      www.sendContent("</div><br/>");
    #endif
    #if POWER_DEVICE4_RELAY != OFF
      www.sendContent(POWER_DEVICE4_NAME);
      sprintf_P(temp, html_powerControl, "4","off","right","4","off",L_OFF);
      www.sendContent(temp);
      sprintf_P(temp, html_powerControl, "4","on","left","4","on",L_ON);
      strcat(temp, "<br/>\n");
      www.sendContent(temp);
    #endif
    #if POWER_DEVICE5_RELAY != OFF
      www.sendContent(POWER_DEVICE5_NAME);
      sprintf_P(temp, html_powerControl, "5","off","right","5","off",L_OFF);
      www.sendContent(temp);
      sprintf_P(temp, html_powerControl, "5","on","left","5","on",L_ON);
      strcat(temp, "<br/>\n");
      www.sendContent(temp);
    #endif
    #if POWER_DEVICE6_RELAY != OFF
      www.sendContent(POWER_DEVICE6_NAME);
      sprintf_P(temp, html_powerControl, "6","off","right","6","off",L_OFF);
      www.sendContent(temp);
      sprintf_P(temp, html_powerControl, "6","on","left","6","on",L_ON);
      strcat(temp, "<br/>\n");
      www.sendContent(temp);
    #endif

    strcpy_P(temp, htmlPowerEnd);
    www.sendContent(temp);
  }

  void powerTileAjax() {
    #if POWER_DEVICE1_RELAY != OFF
      if (relay.isOn(POWER_DEVICE1_RELAY)) www.sendContent("pwr1_on|selected\npwr1_off|unselected\n"); else www.sendContent("pwr1_on|unselected\npwr1_off|selected\n");
    #endif
    #if POWER_DEVICE2_RELAY != OFF
      if (relay.isOn(POWER_DEVICE2_RELAY)) www.sendContent("pwr2_on|selected\npwr2_off|unselected\n"); else www.sendContent("pwr2_on|unselected\npwr2_off|selected\n");
    #endif
    #if POWER_DEVICE3_RELAY != OFF
      if (relay.isOn(POWER_DEVICE3_RELAY)) www.sendContent("pwr3_on|selected\npwr3_off|unselected\n"); else www.sendContent("pwr3_on|unselected\npwr3_off|selected\n");
    #endif
    #if POWER_DEVICE4_RELAY != OFF
      if (relay.isOn(POWER_DEVICE4_RELAY)) www.sendContent("pwr4_on|selected\npwr4_off|unselected\n"); else www.sendContent("pwr4_on|unselected\npwr4_off|selected\n");
    #endif
    #if POWER_DEVICE5_RELAY != OFF
      if (relay.isOn(POWER_DEVICE5_RELAY)) www.sendContent("pwr5_on|selected\npwr5_off|unselected\n"); else www.sendContent("pwr5_on|unselected\npwr5_off|selected\n");
    #endif
    #if POWER_DEVICE6_RELAY != OFF
      if (relay.isOn(POWER_DEVICE6_RELAY)) www.sendContent("pwr6_on|selected\npwr6_off|unselected\n"); else www.sendContent("pwr6_on|unselected\npwr6_off|selected\n");
    #endif
  }

  void powerTileGet() {
    String s;
    UNUSED(s);

    #if POWER_DEVICE1_RELAY != OFF
      s = www.arg("pwr1");
      if (s.equals("on")) {
        relay.on(POWER_DEVICE1_RELAY);
        #if POWER_DEVICE1_MEMORY != OFF
          nv.write(NV_POWER_DEVICE1, (uint8_t)1);
        #endif
      } else
      if (s.equals("off")) {
        relay.off(POWER_DEVICE1_RELAY);
        #if POWER_DEVICE1_MEMORY != OFF
          nv.write(NV_POWER_DEVICE1, (uint8_t)0);
        #endif
      }
    #endif

    #if POWER_DEVICE2_RELAY != OFF
      s = www.arg("pwr2");
      if (s.equals("on")) {
        relay.on(POWER_DEVICE2_RELAY);
        #if POWER_DEVICE2_MEMORY != OFF
          nv.write(NV_POWER_DEVICE2, (uint8_t)1);
        #endif
      } else
      if (s.equals("off")) {
        relay.off(POWER_DEVICE2_RELAY);
        #if POWER_DEVICE2_MEMORY != OFF
          nv.write(NV_POWER_DEVICE2, (uint8_t)0);
        #endif
      }
    #endif

    #if POWER_DEVICE3_RELAY != OFF
      s = www.arg("pwr3");
      if (s.equals("on")) {
        relay.on(POWER_DEVICE3_RELAY);
        #if POWER_DEVICE3_MEMORY != OFF
          nv.write(NV_POWER_DEVICE3, (uint8_t)1);
        #endif
      } else
      if (s.equals("off")) {
        relay.off(POWER_DEVICE3_RELAY);
        #if POWER_DEVICE3_MEMORY != OFF
          nv.write(NV_POWER_DEVICE3, (uint8_t)0);
        #endif
      }
    #endif

    #if POWER_DEVICE4_RELAY != OFF
      s = www.arg("pwr4");
      if (s.equals("on")) {
        relay.on(POWER_DEVICE4_RELAY);
        #if POWER_DEVICE4_MEMORY != OFF
          nv.write(NV_POWER_DEVICE4, (uint8_t)1);
        #endif
      } else
      if (s.equals("off")) {
        relay.off(POWER_DEVICE4_RELAY);
        #if POWER_DEVICE4_MEMORY != OFF
          nv.write(NV_POWER_DEVICE4, (uint8_t)0);
        #endif
      }
    #endif

    #if POWER_DEVICE5_RELAY != OFF
      s = www.arg("pwr5");
      if (s.equals("on")) {
        relay.on(POWER_DEVICE5_RELAY);
        #if POWER_DEVICE5_MEMORY != OFF
          nv.write(NV_POWER_DEVICE5, (uint8_t)1);
        #endif
      } else
      if (s.equals("off")) {
        relay.off(POWER_DEVICE5_RELAY);
        #if POWER_DEVICE5_MEMORY != OFF
          nv.write(NV_POWER_DEVICE5, (uint8_t)0);
        #endif
      }
    #endif

    #if POWER_DEVICE6_RELAY != OFF
      s = www.arg("pwr6");
      if (s.equals("on")) {
        relay.on(POWER_DEVICE6_RELAY);
        #if POWER_DEVICE6_MEMORY != OFF
          nv.write(NV_POWER_DEVICE6, (uint8_t)1);
        #endif
      } else
      if (s.equals("off")) {
        relay.off(POWER_DEVICE6_RELAY);
        #if POWER_DEVICE6_MEMORY != OFF
          nv.write(NV_POWER_DEVICE6, (uint8_t)0);
        #endif
      }
    #endif
  }

#endif
