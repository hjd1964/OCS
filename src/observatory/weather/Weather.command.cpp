// -----------------------------------------------------------------------------------
// Weather/Safety monitor commands

#include "Weather.h"

#ifdef WEATHER_PRESENT

#include "../../libApp/weatherSensor/WeatherSensor.h"

bool Weather::command(char reply[], char command[], char parameter[], bool *supressFrame, bool *numericReply, CommandError *commandError) {
  UNUSED(*commandError);
  UNUSED(*numericReply);
  UNUSED(*supressFrame);
  UNUSED(*parameter);
  UNUSED(*command);
  UNUSED(*reply);

  if (command[0] == 'G') {
    //  :G1#  Get outside temperature
    //         Returns: nnn.n#
    if (command[1] == '1' && parameter[0] == 0) {
      sprintF(reply, "%3.1f", weatherSensor.temperature());
      *numericReply = false;
    } else

    //  :G1N#  Get outside temperaturer Sensor name
    //         Returns: s#
    if (command[1] == '1' && parameter[0] == 'N' && parameter[1] == 0) {
      sprintf(reply, "%s", weatherSensor.temperatureName());
      *numericReply = false;
    } else

    //  :G2#  Get sky IR temperature
    //         Returns: nnn.n#
    if (command[1] == '2' && parameter[0] == 0) {
      sprintF(reply, "%3.1f", weatherSensor.skyTemperature());
      *numericReply = false;
    } else

    //  :G2N#  Get sky IR temperature Sensor Name
    //         Returns: s#
    if (command[1] == '2' && parameter[0] == 'N' && parameter[1] == 0) {
      sprintf(reply, "%s", weatherSensor.skyTemperatureName());
      *numericReply = false;
    } else

    //  :G3#  Get differential sky temperature
    //         Returns: nnn.n#
    //         where <= 21 is cloudy
    if (command[1] == '3' && parameter[0] == 0) {
      sprintF(reply, "%3.1f", weather.getAvgSkyDiffTemp());
      *numericReply = false;
    } else
  
    //  :Gb#  Get absolute barometric pressure as Float
    //         Returns: n.nnn#
    //         where n ranges from about 980.0 to 1050.0 (mbar, sea-level compensated)
    if (command[1] == 'b' && parameter[0] == 0) {
      sprintF(reply, "%1.1f", weatherSensor.pressure());
      *numericReply = false;
    } else

    //  :GbN#  Get absolute barometric pressure Sersor name
    //         Returns: s#
    if (command[1] == 'b' && parameter[0] == 'N' && parameter[1] == 0) {
      sprintf(reply, "%s", weatherSensor.pressureName());
      *numericReply = false;
    } else
  
    //  :GC#  Get cloud description
    //         Example: :GC#
    //         Returns: sssss...#
    if (command[1] == 'C' && parameter[0] == 0) {
      strcpy(reply, weather.cloudCoverDescription());
      *numericReply = false;
    } else
  
    //  :Gh#  Get relative humidity reading as Float
    //         Returns: n.n#
    //         where n ranges from 0.0 to 100.0
    if (command[1] == 'h' && parameter[0] == 0) {
      sprintF(reply, "%1.1f", weatherSensor.humidity());
      *numericReply = false;
    } else

    //  :GhN#  Get relative humidity Sersor name
    //         Returns: s#
    if (command[1] == 'h' && parameter[0] == 'N' && parameter[1] == 0) {
      sprintf(reply, "%s", weatherSensor.humidityName());
      *numericReply = false;
    } else
  
    //  :GQ#  Get sky quality in mag/arc-sec^2
    //         Returns: nnn.n#
    if ((command[1] == 'Q') && (parameter[0] == 0)) {
      sprintF(reply, "%3.1f", weatherSensor.skyQuality());
      *numericReply = false;
    } else
  
    //  :GQN#  Get sky quality Sersor name
    //         Returns: s#
    if (command[1] == 'Q' && parameter[0] == 'N' && parameter[1] == 0) {
      sprintf(reply, "%s", weatherSensor.skyQualityName());
      *numericReply = false;
    } else
  
    //  :GR#  Get rain sensor status
    //         Returns: n#
    //         1# is Rain, 2# is Warn, and 3# is Dry
    if (command[1] == 'R' && parameter[0] == 0) {
      sprintF(reply,"%1.0f", weatherSensor.rain());
      *numericReply = false;
    } else
  
    //  :GRN#  Get rain Sersor name
    //         Returns: s#
    if (command[1] == 'R' && parameter[0] == 'N' && parameter[1] == 0) {
      sprintf(reply, "%s", weatherSensor.rainSenseName());
      *numericReply = false;
    } else
  
    //  :GS#  Get averaged sky differential temperature
    //         Returns: nnn.n#
    //         where <=21 is cloudy
    if ((command[1] == 'S') && (parameter[0] == 0)) {
      sprintF(reply, "%3.1f", weather.getAvgSkyDiffTemp());
      *numericReply = false;
    } else
  
    //  :GW#  Get wind status
    //         Returns: OK#, HIGH#
    if (command[1] == 'W' && parameter[0] == 0) {
      if (isnan(weatherSensor.windspeed())) strcpy(reply, "NAN"); else
      if (weatherSensor.windspeed() > WEATHER_WIND_SPD_THRESHOLD) strcpy(reply, "HIGH"); else strcpy(reply, "OK");
      *numericReply = false;
    } else

    //  :Gw#  Get wind speed
    //         Returns: n# kph, Invalid# or N/A#
    //
    if (command[1] == 'w' && parameter[0] == 0) {
      sprintF(reply, "%1.0f", weatherSensor.windspeed());
      *numericReply = false;
    } else

    //  :GwN#  Get wind Sersor name
    //         Returns: s#
    if (command[1] == 'w' && parameter[0] == 'N' && parameter[1] == 0) {
      sprintf(reply, "%s", weatherSensor.windspeedName());
      *numericReply = false;
    } else return false;
  
  } else

  if (command[0] == 'I') {
    //  :IW#  get Weather threshold #defines
    //         Returns: 20,-14#, WEATHER_WIND_SPD_THRESHOLD,WEATHER_SAFE_THRESHOLD, N/A if sensor == OFF
    if (command[1] == 'W' && parameter[0] == 0) {
      char ws[20];
      if (WEATHER_WIND_SPD != OFF) { sprintf(ws, "%d", WEATHER_WIND_SPD_THRESHOLD); } else { sprintf(ws, "%s", "N/A"); }
      char wt[20];
      if (WEATHER_CLOUD_CVR != OFF) { sprintf(wt, "%d", WEATHER_SAFE_THRESHOLD); } else { sprintf(wt, "%s", "N/A"); }
      sprintf(reply, "%s,%s", ws, wt);
      *numericReply = false;
    } else return false;
  }

  return false;
}

#endif
