// -----------------------------------------------------------------------------------
// Alpaca Setup

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON

#include <ArduinoJson.h>
#include "Alpaca.h"
#include "../observatory/safety/Safety.h"
#include "../pages/htmlHeaders.h"
#include "../libApp/weatherSensor/WeatherSensor.h"

void alpacaSetup() {
  char temp[256] = "";

  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "text/html", String());

  strcpy_P(temp, html_head_begin); apc.sendContent(temp);
  apc.sendContent(F("</head>\r\n<body>\r\n"));

  apc.sendContent(F("<big>Observatory Control System (OCS, Version "));
  apc.sendContent(ocsVersion);
  apc.sendContent(F(")<br/>ASCOM ALPACA Setup</big><br/><br/>\r\n"));

  apc.sendContent(F("Device:<br/>\r\n"));
  #if defined(WEATHER_PRESENT)
    apc.sendContent(F("&nbsp;&nbsp;<a href=\"/setup/v1/safetymonitor/0/setup\">SafetyMonitor</a>\r\n"));
    apc.sendContent(F("&nbsp;&nbsp;<a href=\"/setup/v1/observingconditions/0/setup\">Observing Conditions</a>\r\n"));
  #endif
  #if defined(LIGHT_PRESENT) || defined(POWER_PRESENT)
    apc.sendContent(F("&nbsp;&nbsp;<a href=\"/setup/v1/switch/0/setup\">Switch</a>\r\n"));
  #endif
  #if defined(ROOF_PRESENT) || defined(DOME_PRESENT) 
    apc.sendContent(F("&nbsp;&nbsp;<a href=\"/setup/v1/dome/0/setup\">Dome</a>\r\n"));
  #endif

  apc.sendContent(F("</body></html>\r\n"));
  apc.sendContent("");
}

#if defined(WEATHER_PRESENT)
  void alpacaSetupSafetyMonitor() {
    char temp[256] = "";

    apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
    apc.send(200, "text/html", String());

    strcpy_P(temp, html_head_begin); apc.sendContent(temp);
    apc.sendContent(F("</head>\r\n<body>\r\n"));

    apc.sendContent(F("<big>Observatory Control System (OCS, Version "));
    apc.sendContent(ocsVersion);
    apc.sendContent(F(")<br/>ASCOM ALPACA SafetyMonitor</big><br/><br/>\r\n"));

    apc.sendContent(F("Device:<br/>\r\n"));
    apc.sendContent(F("&nbsp;&nbsp;No setup supported.<br/>\r\n"));

    apc.sendContent(F("<br/><br/><a href=\"/setup\">OCS ASCOM ALPACA Setup</a>\r\n"));

    apc.sendContent(F("</body></html>\r\n"));
    apc.sendContent("");
  }

  void alpacaSetupObservingConditions() {
    char temp[256] = "";

    apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
    apc.send(200, "text/html", String());

    strcpy_P(temp, html_head_begin); apc.sendContent(temp);
    apc.sendContent(F("</head>\r\n<body>\r\n"));

    apc.sendContent(F("<big>Observatory Control System (OCS, Version "));
    apc.sendContent(ocsVersion);
    apc.sendContent(F(")<br/>ASCOM ALPACA ObservingConditions</big><br/><br/>\r\n"));

    apc.sendContent(F("Device:<br/>\r\n"));

    sprintf(temp, "&nbsp;&nbsp;Humidity: %s%s<br/>\r\n", weatherSensor.humidityName(), isnan(weatherSensor.humidity()) ? " (inactive)" : "");
    apc.sendContent(temp);
    sprintf(temp, "&nbsp;&nbsp;Pressure: %s%s<br/>\r\n", weatherSensor.pressureName(), isnan(weatherSensor.pressure()) ? " (inactive)" : "");
    apc.sendContent(temp);
    sprintf(temp, "&nbsp;&nbsp;Sky Quality: %s%s<br/>\r\n", weatherSensor.skyQualityName(), isnan(weatherSensor.skyQuality()) ? " (inactive)" : "");
    apc.sendContent(temp);
    sprintf(temp, "&nbsp;&nbsp;Sky Temperature: %s%s<br/>\r\n", weatherSensor.skyTemperatureName(), isnan(weatherSensor.skyTemperature()) ? " (inactive)" : "");
    apc.sendContent(temp);
    sprintf(temp, "&nbsp;&nbsp;Temperature: %s%s<br/>\r\n", weatherSensor.temperatureName(), isnan(weatherSensor.temperature()) ? " (inactive)" : "");
    apc.sendContent(temp);
    sprintf(temp, "&nbsp;&nbsp;Wind Speed: %s%s<br/>\r\n", weatherSensor.windspeedName(), isnan(weatherSensor.windspeed()) ? " (inactive)" : "");
    apc.sendContent(temp);

    apc.sendContent(F("<br/>&nbsp;&nbsp;No setup supported.<br/>\r\n"));

    apc.sendContent(F("<br/><br/><a href=\"/setup\">OCS ASCOM ALPACA Setup</a>\r\n"));

    apc.sendContent(F("</body></html>\r\n"));
    apc.sendContent("");
  }
#endif

#if defined(LIGHT_PRESENT) || defined(POWER_PRESENT)
  void alpacaSetupSwitch() {
    char temp[256] = "";

    apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
    apc.send(200, "text/html", String());

    strcpy_P(temp, html_head_begin); apc.sendContent(temp);
    apc.sendContent(F("</head>\r\n<body>\r\n"));

    apc.sendContent(F("<big>Observatory Control System (OCS, Version "));
    apc.sendContent(ocsVersion);
    apc.sendContent(F(")<br/>ASCOM ALPACA Switch</big><br/><br/>\r\n"));

    apc.sendContent(F("Device:<br/>\r\n"));

    int maxSwitch = 0;
    #if POWER_DEVICE1_RELAY != OFF
      sprintf(temp, "&nbsp;&nbsp;Switch %d: Power Device%d Relay<br/>\r\n", maxSwitch, 1);
      apc.sendContent(temp);
      maxSwitch++;
    #endif
    #if POWER_DEVICE2_RELAY != OFF
      sprintf(temp, "&nbsp;&nbsp;Switch %d: Power Device%d Relay<br/>\r\n", maxSwitch, 2);
      apc.sendContent(temp);
      maxSwitch++;
    #endif
    #if POWER_DEVICE3_RELAY != OFF
      sprintf(temp, "&nbsp;&nbsp;Switch %d: Power Device%d Relay<br/>\r\n", maxSwitch, 3);
      apc.sendContent(temp);
      maxSwitch++;
    #endif
    #if POWER_DEVICE4_RELAY != OFF
      sprintf(temp, "&nbsp;&nbsp;Switch %d: Power Device%d Relay<br/>\r\n", maxSwitch, 4);
      apc.sendContent(temp);
      maxSwitch++;
    #endif
    #if POWER_DEVICE5_RELAY != OFF
      sprintf(temp, "&nbsp;&nbsp;Switch %d: Power Device%d Relay<br/>\r\n", maxSwitch, 5);
      apc.sendContent(temp);
      maxSwitch++;
    #endif
    #if POWER_DEVICE6_RELAY != OFF
      sprintf(temp, "&nbsp;&nbsp;Switch %d: Power Device%d Relay<br/>\r\n", maxSwitch, 6);
      apc.sendContent(temp);
      maxSwitch++;
    #endif
    #if LIGHT_WRW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      sprintf(temp, "&nbsp;&nbsp;Switch %d: Lights WRW<br/>\r\n", maxSwitch);
      apc.sendContent(temp);
      maxSwitch++;
    #endif
    #if LIGHT_WRR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      sprintf(temp, "&nbsp;&nbsp;Switch %d: Lights WRR<br/>\r\n", maxSwitch);
      apc.sendContent(temp);
      maxSwitch++;
    #endif
    #if LIGHT_ORW_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      sprintf(temp, "&nbsp;&nbsp;Switch %d: Lights ORW<br/>\r\n", maxSwitch);
      apc.sendContent(temp);
      maxSwitch++;
    #endif
    #if LIGHT_ORR_RELAY != OFF || LIGHT_STRIP_DATA_PIN != OFF
      sprintf(temp, "&nbsp;&nbsp;Switch %d: Lights ORR<br/>\r\n", maxSwitch);
      apc.sendContent(temp);
      maxSwitch++;
    #endif

    apc.sendContent(F("<br/>&nbsp;&nbsp;No setup supported.<br/>\r\n"));

    apc.sendContent(F("<br/><br/><a href=\"/setup\">OCS ASCOM ALPACA Setup</a>\r\n"));

    apc.sendContent(F("</body></html>\r\n"));
    apc.sendContent("");
  }
#endif

#if defined(ROOF_PRESENT) || defined(DOME_PRESENT) 
  void alpacaSetupDome() {
    char temp[256] = "";

    apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
    apc.send(200, "text/html", String());

    strcpy_P(temp, html_head_begin); apc.sendContent(temp);
    apc.sendContent(F("</head>\r\n<body>\r\n"));

    apc.sendContent(F("<big>Observatory Control System (OCS, Version "));
    apc.sendContent(ocsVersion);
    apc.sendContent(F(")<br/>ASCOM ALPACA Dome</big><br/><br/>\r\n"));

    apc.sendContent(F("Device:<br/>\r\n"));

    #if POWER_DEVICE1_RELAY != OFF
      #ifdef ROOF_PRESENT
        apc.sendContent(F("&nbsp;&nbsp;Roof/Dome Shutter: Present<br/>\r\n"));
      #else
        apc.sendContent(F("&nbsp;&nbsp;Roof/Dome Shutter: Not Present<br/>\r\n"));
      #endif
      #ifdef DOME_PRESENT
        #if AXIS2_DRIVER_MODEL != OFF
          apc.sendContent(F("&nbsp;&nbsp;Dome Azimuth and Altitude control: Present<br/>\r\n"));
        #else
          apc.sendContent(F("&nbsp;&nbsp;Dome Azimuth control: Present<br/>\r\n"));
        #endif
      #else
        apc.sendContent(F("&nbsp;&nbsp;Dome: Not Present<br/>\r\n"));
      #endif
    #endif

    apc.sendContent(F("<br/>&nbsp;&nbsp;No setup supported.<br/>\r\n"));

    apc.sendContent(F("<br/><br/><a href=\"/setup\">OCS ASCOM ALPACA Setup</a>\r\n"));

    apc.sendContent(F("</body></html>\r\n"));
    apc.sendContent("");
  }
#endif

#endif
