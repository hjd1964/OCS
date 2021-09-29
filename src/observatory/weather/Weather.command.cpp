// -----------------------------------------------------------------------------------
// Weather/Safety monitor commands

#include "Weather.h"

#if WEATHER == ON

#include "../../lib/weatherSensor/WeatherSensor.h"

bool Weather::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {

  #if WEATHER_TEMPERATURE == ON
  //  :G1#  Get outside temperature
  //         Returns: nnn.n#
  if (command[1] == '1' && parameter[0] == 0) {
    sprintF(reply, "%3.1f", weatherSensor.temperature());
    *numericReply = false;
  } else
  #endif
 
  #if WEATHER_CLOUD_CVR == ON
  //  :G2#  Get sky IR temperature
  //         Returns: nnn.n#
  if (command[1] == '2' && parameter[0] == 0) {
    dtostrf(weatherSkyTemp(),3,1,reply);
    *numericReply = false;
  } else
  //  :G3#  Get differential sky temperature
  //         Returns: nnn.n#
  //         where <= 21 is cloudy
  if (command[1] == '3' && parameter[0] == 0) {
    dtostrf(getSkyDiffTemp(), 3, 1, reply);
    *numericReply = false;
  } else
  #endif
 
  #if WEATHER_PRESSURE == ON
  //  :Gb#  Get absolute barometric pressure as Float
  //         Returns: n.nnn#
  //         where n ranges from about 980.0 to 1050.0 (mbar, sea-level compensated)
  if (command[1] == 'b' && parameter[0] == 0) {
    sprintF(reply, "%1.1f", weatherSensor.pressure());
    *numericReply = false;
  } else
  #endif
 
  //  :GC#  Get cloud description
  //         Example: :GC#
  //         Returns: sssss...#
  if (command[1] == 'C' && parameter[0] == 0) {
    #if WEATHER_CLOUD_CVR == ON
      strcpy(reply,weatherCloudCoverDescription().c_str());
    #else
      strcpy(reply,"N/A");
    #endif
    *numericReply = false;
  } else
 
  #if WEATHER_HUMIDITY == ON
  //  :Gh#  Get relative humidity reading as Float
  //         Returns: n.n#
  //         where n ranges from 0.0 to 100.0
  if (command[1] == 'h' && parameter[0] == 0) {
    sprintF(reply, "%1.1f", weatherSensor.humidity());
    *numericReply = false;
  } else
  #endif
 
  #if WEATHER_SKY_QUAL == ON
  //  :GQ#  Get sky quality in mag/arc-sec^2
  //         Returns: nnn.n#
  if ((command[1] == 'Q') && (parameter[0] == 0)) {
    sprintF(reply, "%3.1f", weatherSensor.skyQuality());
    *numericReply = false;
  } else
  #endif
 
  //  :GR#  Get rain sensor status
  //         Returns: n#
  //         -1000# is invalid, 0# is N/A, 1# is Rain, 2# is Warn, and 3# is Dry
  if (command[1] == 'R' && parameter[0] == 0) {
    #if WEATHER_RAIN == ON
      sprintf(reply,"%d", (int)lroundf(weatherSensor.rain()));
    #else
      strcpy(reply,"0");
    #endif
    *numericReply = false;
  } else
 
  #if WEATHER_CLOUD_CVR == ON
  //  :GS#  Get averaged sky differential temperature
  //         Returns: nnn.n#
  //         where <=21 is cloudy
  if ((command[1] == 'S') && (parameter[0] == 0)) {
    dtostrf(getAvgSkyDiffTemp(),3,1,reply);
    *numericReply = true;
  } else
  #endif
 
  //  :GW#  Get wind status
  //         Returns: OK#, HIGH#, or N/A#
  //         
  if (command[1] == 'W' && parameter[0] == 0) {
    #if WEATHER_WIND_SPD == ON && WEATHER == ON
      if (weatherSensor.windspeed() > WEATHER_WIND_SPD_THRESHOLD) strcpy(reply, "HIGH"); else 
      if (isnan(weatherSensor.windspeed())) strcpy(reply, "Invalid"); else strcpy(reply, "OK");
    #else
      strcpy(reply,"N/A");
    #endif
    *numericReply = false;
  } else return false;

  return true;
}

#endif
