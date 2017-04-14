// ----------------------------------------------------------------------------------------------------------------------------------
// Misc support functions

// gets cloud cover in %
double weatherCloudCover() {
  double s=getAvgSkyDiffTemp();
  if (s <= -200) return (invalid); else
  if (s <= WEATHER_CLER_THRESHOLD) return 10; else
  if (s <= WEATHER_HAZE_THRESHOLD) return 20; else
  if (s <= WEATHER_SAFE_THRESHOLD) return 30; else
  if (s <= (WEATHER_SAFE_THRESHOLD+WEATHER_OVRC_THRESHOLD)/2.0) return 40; else
  if (s <= WEATHER_OVRC_THRESHOLD) return 50; else
  if (s <= (WEATHER_OVRC_THRESHOLD+WEATHER_CLDY_THRESHOLD)/2.0) return 60; else
  if (s <= WEATHER_CLDY_THRESHOLD) return 70; else
  if (s <= (WEATHER_CLDY_THRESHOLD+WEATHER_VCLD_THRESHOLD)/2.0) return 80; else
  if (s <= WEATHER_VCLD_THRESHOLD) return 90; else
  if (s >  WEATHER_VCLD_THRESHOLD) return 100;
}

// gets cloud cover text
String weatherCloudCoverDescription() {
  double s=getAvgSkyDiffTemp();
  if (s <= -200) return "Invalid"; else
  if (s <= WEATHER_CLER_THRESHOLD) return "Clear"; else
  if (s <= WEATHER_HAZE_THRESHOLD) return "Mostly Clear"; else
  if (s <= WEATHER_SAFE_THRESHOLD) return "Slight Haze"; else
  if (s <= (WEATHER_SAFE_THRESHOLD+WEATHER_OVRC_THRESHOLD)/2.0) return "Overcast/Haze"; else
  if (s <= WEATHER_OVRC_THRESHOLD) return "Overcast"; else
  if (s <= (WEATHER_OVRC_THRESHOLD+WEATHER_CLDY_THRESHOLD)/2.0) return "Clouds/Overcast"; else
  if (s <= WEATHER_CLDY_THRESHOLD) return "Mostly Cloudy"; else
  if (s <= (WEATHER_CLDY_THRESHOLD+WEATHER_VCLD_THRESHOLD)/2.0) return "Cloudy"; else
  if (s <= WEATHER_VCLD_THRESHOLD) return "Very Cloudy"; else
  if (s >  WEATHER_VCLD_THRESHOLD) return "Very Cloudy";
}

// gets cloud cover text (short)
String weatherCloudCoverDescriptionShort() {
  double s=getAvgSkyDiffTemp();
  if (s <= -200) return "Invalid"; else
  if (s <= WEATHER_CLER_THRESHOLD) return "Clear"; else
  if (s <= WEATHER_HAZE_THRESHOLD) return "Mostly Clr"; else
  if (s <= WEATHER_SAFE_THRESHOLD) return "Slight Hze"; else
  if (s <= (WEATHER_SAFE_THRESHOLD+WEATHER_OVRC_THRESHOLD)/2.0) return "Ovrcst/Hze"; else
  if (s <= WEATHER_OVRC_THRESHOLD) return "Overcast"; else
  if (s <= (WEATHER_OVRC_THRESHOLD+WEATHER_CLDY_THRESHOLD)/2.0) return "Cld/Ovrcst"; else
  if (s <= WEATHER_CLDY_THRESHOLD) return "Mstly Cldy"; else
  if (s <= (WEATHER_CLDY_THRESHOLD+WEATHER_VCLD_THRESHOLD)/2.0) return "Cloudy"; else
  if (s <= WEATHER_VCLD_THRESHOLD) return "Very Cldy"; else
  if (s >  WEATHER_VCLD_THRESHOLD) return "Very Cldy";
}

