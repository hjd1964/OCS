// -----------------------------------------------------------------------------------
// Alpaca Observing Conditions

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON && defined(WEATHER_PRESENT)

#include <ArduinoJson.h>
#include "Alpaca.h"
#include "../observatory/weather/Weather.h"
#include "../libApp/weatherSensor/WeatherSensor.h"

extern JsonDocument alpacaJsonDoc;
int32_t observingConditionsConnected = 0;

void alpacaObservingConditionsConnected() {
  int exceptionCode = NoException;
  String exceptionValue = "";

  alpacaJsonStart();
  String connected = alpacaArgLowerCase("connected");
  if (!connected.equals(EmptyStr)) {
    if (connected.equals("true")) observingConditionsConnected++; else
    if (connected.equals("false")) observingConditionsConnected--; else {
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
  String v = alpacaArgLowerCase("averageperiod");
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
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  if (isnan(weather.cloudCover())) { alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; }
  alpacaJsonDoc["Value"] = weather.cloudCover();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsDewPoint() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  if (isnan(weatherSensor.temperature()) || isnan(weatherSensor.humidity())) { alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; }
  alpacaJsonDoc["Value"] = weatherSensor.temperature() - (100.0 - weatherSensor.humidity())/5.0;
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsHumidity() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  if (isnan(weatherSensor.humidity())) { alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; }
  alpacaJsonDoc["Value"] = weatherSensor.humidity();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsPressure() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  if (isnan(weatherSensor.pressure())) { alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; }
  alpacaJsonDoc["Value"] = weatherSensor.pressure();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsRainRate() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
}

void alpacaObservingConditionsSkyBrightness() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
}

void alpacaObservingConditionsSkyQuality() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  if (isnan(weatherSensor.skyQuality())) { alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; }
  alpacaJsonDoc["Value"] = weatherSensor.skyQuality();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsSkyTemperature() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  if (isnan(weatherSensor.skyTemperature())) { alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; }
  alpacaJsonDoc["Value"] = weatherSensor.skyTemperature();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsStarFwhm() {
  alpacaJsonStart();
  alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
}

void alpacaObservingConditionsTemperature() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  if (isnan(weatherSensor.temperature())) { alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; }
  alpacaJsonDoc["Value"] = weatherSensor.temperature();
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsWindDirection() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
}

void alpacaObservingConditionsWindGust() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
}

void alpacaObservingConditionsWindSpeed() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  if (isnan(weatherSensor.windspeed())) { alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; }
  alpacaJsonDoc["Value"] = weatherSensor.windspeed()/3.6;
  alpacaJsonFinish(NoException, "");
}

void alpacaObservingConditionsRefresh() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }
  alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
}

void alpacaObservingConditionsSensorDescription() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }

  String sensorName = alpacaArgLowerCase("sensorname");
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
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
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
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("humidity")) {
    if (!isnan(weatherSensor.humidity())) {
      alpacaJsonDoc["Value"] = weatherSensor.humidityName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("pressure")) {
    if (!isnan(weatherSensor.pressure())) {
      alpacaJsonDoc["Value"] = weatherSensor.pressureName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("rainrate")) {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
  } else

  if (sensorName.equals("skybrightness")) {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
  } else

  if (sensorName.equals("skyquality")) {
    if (!isnan(weatherSensor.skyQuality())) {
      alpacaJsonDoc["Value"] = weatherSensor.skyQualityName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("starfwhm")) {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
  } else

  if (sensorName.equals("skytemperature")) {
    if (!isnan(weatherSensor.skyTemperature())) {
      alpacaJsonDoc["Value"] = weatherSensor.skyTemperatureName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("temperature")) {
    if (!isnan(weatherSensor.temperature())) {
      alpacaJsonDoc["Value"] = weatherSensor.temperatureName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("winddirection")) {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
  } else

  if (sensorName.equals("windgust")) {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
  } else

  if (sensorName.equals("windspeed")) {
    if (!isnan(weatherSensor.windspeed())) {
      alpacaJsonDoc["Value"] = weatherSensor.windspeedName();
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonDoc["Value"] = "";
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else
  
  {
    alpacaJsonDoc["Value"] = "";
    alpacaJsonFinish(InvalidValueException, InvalidValueMessage);
  }
}

void alpacaObservingConditionsTimeSinceLastUpdate() {
  alpacaJsonStart();
  if (!observingConditionsConnected) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return; }

  String sensorName = alpacaArgLowerCase("sensorname");
  alpacaJsonDoc["Value"] = 0;

  if (sensorName.length() == 0) {
    alpacaJsonFinish(NoException, "");
  } else

  if (sensorName.equals("cloudcover")) {
    if (!isnan(weatherSensor.skyTemperature()) && !isnan(weatherSensor.temperature())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("dewpoint")) {
    if (!isnan(weatherSensor.temperature()) && !isnan(weatherSensor.humidity())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("humidity")) {
    if (!isnan(weatherSensor.humidity())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("pressure")) {
    if (!isnan(weatherSensor.pressure())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("rainrate")) {
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
  } else

  if (sensorName.equals("skybrightness")) {
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
  } else

  if (sensorName.equals("skyquality")) {
    if (!isnan(weatherSensor.skyQuality())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("starfwhm")) {
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
  } else

  if (sensorName.equals("skytemperature")) {
    if (!isnan(weatherSensor.skyTemperature())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("temperature")) {
    if (!isnan(weatherSensor.temperature())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else

  if (sensorName.equals("winddirection")) {
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
  } else

  if (sensorName.equals("windgust")) {
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
  } else

  if (sensorName.equals("windspeed")) {
    if (!isnan(weatherSensor.windspeed())) {
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(NotImplementedException, NotImplementedMessage);
    }
  } else
  
  {
    alpacaJsonFinish(InvalidValueException, "SensorName, Invalid value");
  }
}

#endif
