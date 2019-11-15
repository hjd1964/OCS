// -----------------------------------------------------------------------------------------------------------------
// Weather functions
// ======= add your weather sensor support here =======

// this gets called once on startup to initialize any weather sensors
void weatherInit() {
  analogReference(DEFAULT);
}

// gets outside temperature in deg. C
// return (invalid) if not implemented or if there's an error
double weatherOutsideTemp() {
  return (invalid);
}

// gets sky IR temperature in deg. C
// return (invalid) if not implemented or if there's an error
double weatherSkyTemp() {
  return (invalid);
}

// gets windspeed in kph
// return (invalid) if not implemented or if there's an error
double weatherWindspeed() {
  return (invalid);
}

// gets absolute barometric pressure in mb (not sea-level adjusted)
// return (invalid) if not implemented or if there's an error
double weatherPressure() {
  return (invalid);
}

// gets barometric pressure in mb (sea-level adjusted)
// return (invalid) if not implemented or if there's an error
double weatherPressureSeaLevel() {
  return (invalid);
}

// gets relative humidity in %
// return (invalid) if not implemented or if there's an error
double weatherHumidity() {
  return (51);
}

// gets rain sensor info. 1 is Rain, 2 is Warn, and 3 is Dry
// return (invalid) if not implemented or if there's an error
int weatherRain() {
  return (invalid);
}

// gets sky brightness in mag/arc-sec^2
// return (invalid) if not implemented or if there's an error
double weatherSkyQuality() {
  return (invalid);
}

