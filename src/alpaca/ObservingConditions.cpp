// -----------------------------------------------------------------------------------
// Alpaca Observing Conditions

#include <ArduinoJson.h>

#include "../Common.h"
#include "Alpaca.h"
#include "../observatory/weather/Weather.h"
#include "../libApp/weatherSensor/WeatherSensor.h"

extern StaticJsonDocument<200> alpacaJsonDoc;
int32_t observingConditionsConnected = 0;

void alpacaObservingConditionsConnected() {
  int exceptionCode = NoException;
  String exceptionValue = "";

  alpacaJsonStart();
  String connected = apc.argLowerCase("connected");
  if (!connected.equals(EmptyStr)) {
    if (connected.toLowerCase().equals("true")) observingConditionsConnected++; else
    if (connected.toLowerCase().equals("false")) observingConditionsConnected--; else {
      exceptionCode = InvalidValueException;
      exceptionValue = "Connected: Invalid value";
    }
    if (observingConditionsConnected < 0) observingConditionsConnected = 0;
  } else {
    alpacaJsonDoc["Value"] = observingConditionsConnected > 0;
  }
  alpacaJsonFinish(exceptionCode, exceptionValue);
}

void alpacaObservingConditionsAveragePeriod() {
  alpacaJsonStart();
  String v = apc.argLowerCase("averageperiod");
  if (!v.equals(EmptyStr)) {
    float averagePeriod = atof(v.c_str());
    if (abs(averagePeriod) > 0.0000001) { alpacaJsonFinish(InvalidValueException, "Invalid value, use 0.0 for instantaneous"); return; }
  } else {
    alpacaJsonDoc["Value"] = 0.0; // approximately 60 second averages, close enough to call instantaneous
  }
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsCloudCover() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  if (isnan(weather.cloudCover())) { alpacaJsonFinish(NotImplementedException, "Not implemented"); return; }
  alpacaJsonDoc["Value"] = weather.cloudCover();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsDewPoint() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  if (isnan(weatherSensor.temperature()) || isnan(weatherSensor.humidity())) { alpacaJsonFinish(NotImplementedException, "Not implemented"); return; }
  alpacaJsonDoc["Value"] = weatherSensor.temperature() - (100.0 - weatherSensor.humidity())/5.0;
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsHumidity() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  if (isnan(weatherSensor.humidity())) { alpacaJsonFinish(NotImplementedException, "Not implemented"); return; }
  alpacaJsonDoc["Value"] = weatherSensor.humidity();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsPressure() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  if (isnan(weatherSensor.pressure())) { alpacaJsonFinish(NotImplementedException, "Not implemented"); return; }
  alpacaJsonDoc["Value"] = weatherSensor.pressure();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsRainRate() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  alpacaJsonFinish(NotImplementedException, "Not implemented");
}

void alpacaObservingConditionsSkyBrightness() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  alpacaJsonFinish(NotImplementedException, "Not implemented");
}

void alpacaObservingConditionsSkyQuality() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  if (isnan(weatherSensor.skyQuality())) { alpacaJsonFinish(NotImplementedException, "Not implemented"); return; }
  alpacaJsonDoc["Value"] = weatherSensor.skyQuality();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsSkyTemperature() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  if (isnan(weatherSensor.skyTemperature())) { alpacaJsonFinish(NotImplementedException, "Not implemented"); return; }
  alpacaJsonDoc["Value"] = weatherSensor.skyTemperature();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsStarFwhm() {
  alpacaJsonStart();
  alpacaJsonFinish(NotImplementedException, "Not implemented");
}

void alpacaObservingConditionsTemperature() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  if (isnan(weatherSensor.temperature())) { alpacaJsonFinish(NotImplementedException, "Not implemented"); return; }
  alpacaJsonDoc["Value"] = weatherSensor.temperature();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsWindDirection() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  alpacaJsonFinish(NotImplementedException, "Not implemented");
}

void alpacaObservingConditionsWindGust() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  alpacaJsonFinish(NotImplementedException, "Not implemented");
}

void alpacaObservingConditionsWindSpeed() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  if (isnan(weatherSensor.windspeed())) { alpacaJsonFinish(NotImplementedException, "Not implemented"); return; }
  alpacaJsonDoc["Value"] = weatherSensor.windspeed()/3.6;
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsRefresh() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }
  alpacaJsonFinish(NotImplementedException, "Not implemented");
}

void alpacaObservingConditionsSensorDescription() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }

  String sensorName = apc.argLowerCase("sensorname").toLowerCase();

  if (sensorName.equals("cloudcover")) {
    if (!isnan(weatherSensor.skyTemperature()) && !isnan(weatherSensor.temperature())) {
      char temp[128] = "";
      strcpy(temp, weatherSensor.skyTemperatureName());
      strcat(temp, " & ");
      strcat(temp, weatherSensor.temperatureName());
      alpacaJsonDoc["Value"] = temp;
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("dewpoint")) {
    if (!isnan(weatherSensor.temperature()) && !isnan(weatherSensor.humidity())) {
      char temp[128] = "";
      strcpy(temp, weatherSensor.temperatureName());
      strcat(temp, " & ");
      strcat(temp, weatherSensor.humidityName());
      alpacaJsonDoc["Value"] = temp;
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("humidity")) {
    if (!isnan(weatherSensor.humidity())) {
      alpacaJsonDoc["Value"] = weatherSensor.humidityName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("pressure")) {
    if (!isnan(weatherSensor.pressure())) {
      alpacaJsonDoc["Value"] = weatherSensor.pressureName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("rainrate")) {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(NotImplementedException, "Not implemented");
  } else

  if (sensorName.equals("skybrightness")) {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(NotImplementedException, "Not implemented");
  } else

  if (sensorName.equals("skyquality")) {
    if (!isnan(weatherSensor.skyQuality())) {
      alpacaJsonDoc["Value"] = weatherSensor.skyQualityName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("starfwhm")) {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(NotImplementedException, "Not implemented");
  } else

  if (sensorName.equals("skytemperature")) {
    if (!isnan(weatherSensor.skyTemperature())) {
      alpacaJsonDoc["Value"] = weatherSensor.skyTemperatureName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("temperature")) {
    if (!isnan(weatherSensor.temperature())) {
      alpacaJsonDoc["Value"] = weatherSensor.temperatureName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("winddirection")) {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(NotImplementedException, "Not implemented");
  } else

  if (sensorName.equals("windgust")) {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(NotImplementedException, "Not implemented");
  } else

  if (sensorName.equals("windspeed")) {
    if (!isnan(weatherSensor.windspeed())) {
      alpacaJsonDoc["Value"] = weatherSensor.windspeedName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else
  
  {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(InvalidValueException, "SensorName, Invalid value");
  }
}

void alpacaObservingConditionsTimeSinceLastUpdate() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, "Not connected"); return; }

  String sensorName = apc.argLowerCase("sensorname").toLowerCase();

  alpacaJsonDoc["Value"] = 0;

  if (sensorName.length() == 0) {
    alpacaJsonFinish(NoException, "");
  } else

  if (sensorName.equals("cloudcover")) {
    if (!isnan(weatherSensor.skyTemperature()) && !isnan(weatherSensor.temperature())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("dewpoint")) {
    if (!isnan(weatherSensor.temperature()) && !isnan(weatherSensor.humidity())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("humidity")) {
    if (!isnan(weatherSensor.humidity())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("pressure")) {
    if (!isnan(weatherSensor.pressure())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("rainrate")) {
    alpacaJsonFinish(NotImplementedException, "Not implemented");
  } else

  if (sensorName.equals("skybrightness")) {
    alpacaJsonFinish(NotImplementedException, "Not implemented");
  } else

  if (sensorName.equals("skyquality")) {
    if (!isnan(weatherSensor.skyQuality())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("starfwhm")) {
    alpacaJsonFinish(NotImplementedException, "Not implemented");
  } else

  if (sensorName.equals("skytemperature")) {
    if (!isnan(weatherSensor.skyTemperature())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("temperature")) {
    if (!isnan(weatherSensor.temperature())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else

  if (sensorName.equals("winddirection")) {
    alpacaJsonFinish(NotImplementedException, "Not implemented");
  } else

  if (sensorName.equals("windgust")) {
    alpacaJsonFinish(NotImplementedException, "Not implemented");
  } else

  if (sensorName.equals("windspeed")) {
    if (!isnan(weatherSensor.windspeed())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, "Not implemented");
    }
  } else
  
  {
    alpacaJsonFinish(InvalidValueException, "SensorName, Invalid value");
  }
}
