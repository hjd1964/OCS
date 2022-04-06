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

  strcpy_P(temp, html_head1); apc.sendContent(temp);
  apc.sendContent("</head>\r\n<body>\r\n");

  apc.sendContent("<big>Observatory Control System (OCS, Version ");
  apc.sendContent(ocsVersion);
  apc.sendContent(")<br/>ASCOM ALPACA Setup</big><br/><br/>\r\n");

  apc.sendContent(F("Device:<br/>\r\n"));
  apc.sendContent(F("&nbsp;&nbsp;<a href=\"/setup/v1/safetymonitor/0/setup\">SafetyMonitor</a>\r\n"));
  apc.sendContent(F("&nbsp;&nbsp;<a href=\"/setup/v1/observingconditions/0/setup\">Observing Conditions</a>\r\n"));
  apc.sendContent(F("&nbsp;&nbsp;<a href=\"/setup/v1/switch/0/setup\">Switch</a>\r\n"));

  apc.sendContent(F("</body></html>\r\n"));
  apc.sendContent("");
}

void alpacaSetupSafetyMonitor() {
  char temp[256] = "";

  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "text/html", String());

  strcpy_P(temp, html_head1); apc.sendContent(temp);
  apc.sendContent("</head>\r\n<body>\r\n");

  apc.sendContent("<big>Observatory Control System (OCS, Version ");
  apc.sendContent(ocsVersion);
  apc.sendContent(")<br/>ASCOM ALPACA SafetyMonitor</big><br/><br/>\r\n");

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

  strcpy_P(temp, html_head1); apc.sendContent(temp);
  apc.sendContent("</head>\r\n<body>\r\n");

  apc.sendContent("<big>Observatory Control System (OCS, Version ");
  apc.sendContent(ocsVersion);
  apc.sendContent(")<br/>ASCOM ALPACA ObservingConditions</big><br/><br/>\r\n");

  apc.sendContent(F("Device:<br/>\r\n"));

  #if POWER_DEVICE1_RELAY != OFF
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
  #endif

  apc.sendContent(F("<br/>&nbsp;&nbsp;No setup supported.<br/>\r\n"));

  apc.sendContent(F("<br/><br/><a href=\"/setup\">OCS ASCOM ALPACA Setup</a>\r\n"));

  apc.sendContent(F("</body></html>\r\n"));
  apc.sendContent("");
}

void alpacaSetupSwitch() {
  char temp[256] = "";

  apc.setContentLength(CONTENT_LENGTH_UNKNOWN);
  apc.send(200, "text/html", String());

  strcpy_P(temp, html_head1); apc.sendContent(temp);
  apc.sendContent("</head>\r\n<body>\r\n");

  apc.sendContent("<big>Observatory Control System (OCS, Version ");
  apc.sendContent(ocsVersion);
  apc.sendContent(")<br/>ASCOM ALPACA Switch</big><br/><br/>\r\n");

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
  #if LIGHT_WRW_RELAY != OFF
    sprintf(temp, "&nbsp;&nbsp;Switch %d: Lights WRW Relay<br/>\r\n", maxSwitch);
    apc.sendContent(temp);
    maxSwitch++;
  #endif
  #if LIGHT_WRR_RELAY != OFF
    sprintf(temp, "&nbsp;&nbsp;Switch %d: Lights WRR Relay<br/>\r\n", maxSwitch);
    apc.sendContent(temp);
    maxSwitch++;
  #endif
  #if LIGHT_ORW_RELAY != OFF
    sprintf(temp, "&nbsp;&nbsp;Switch %d: Lights ORW Relay<br/>\r\n", maxSwitch);
    apc.sendContent(temp);
    maxSwitch++;
  #endif
  #if LIGHT_ORR_RELAY != OFF
    sprintf(temp, "&nbsp;&nbsp;Switch %d: Lights ORR Relay<br/>\r\n", maxSwitch);
    apc.sendContent(temp);
    maxSwitch++;
  #endif

  apc.sendContent(F("<br/>&nbsp;&nbsp;No setup supported.<br/>\r\n"));

  apc.sendContent(F("<br/><br/><a href=\"/setup\">OCS ASCOM ALPACA Setup</a>\r\n"));

  apc.sendContent(F("</body></html>\r\n"));
  apc.sendContent("");
}

#endif
