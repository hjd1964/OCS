// ----------------------------------------------------------------------------------------------------------------------------------
// Misc support functions
// ======== add your adc voltage and current support here =========

// converts a raw analog reading into voltage for STAT_DC_PS_ANALOG and STAT_BATTERY_ANALOG
// return (invalid) if not implemented or if there's an error
double toDC(double d) {
  d=(d/1023.0);                // 0..1 for ADC range
  d=d*5.0;                     // 0..5 for Volts
  d=d/(220.0/(220.0+2200.0));  // a resistor divider 220 Ohm and 2.2K Ohm
  return d;
}

// converts a raw analog reading into current for STAT_MAINS_CURRENT_ANALOG and STAT_MAINS_AUX_CURRENT_ANALOG
// return (invalid) if not implemented or if there's an error
double toAmps(double d) {
  return (invalid);
}

// converts a raw analog reading into current for STAT_DC_CURRENT_ANALOG and STAT_BATTERY_CURRENT_ANALOG
// return (invalid) if not implemented or if there's an error
double toDCAmps(double d) {
  return (invalid);
}
// =================================================================

// gets cloud cover in %
double weatherCloudCover() {
#if defined(WEATHER_CLOUD_CVR_ON) && defined(WEATHER_ON)
  double s=getAvgSkyDiffTemp();
  if (s <= -200) return (invalid); else
  if (s <= WEATHER_VCLR_THRESHOLD) return 10; else
  if (s <= WEATHER_CLER_THRESHOLD) return 20; else
  if (s <= WEATHER_HAZE_THRESHOLD) return 30; else
  if (s <= (WEATHER_HAZE_THRESHOLD+WEATHER_OVRC_THRESHOLD)/2.0) return 40; else
  if (s <= WEATHER_OVRC_THRESHOLD) return 50; else
  if (s <= (WEATHER_OVRC_THRESHOLD+WEATHER_CLDY_THRESHOLD)/2.0) return 60; else
  if (s <= WEATHER_CLDY_THRESHOLD) return 70; else
  if (s <= (WEATHER_CLDY_THRESHOLD+WEATHER_VCLD_THRESHOLD)/2.0) return 80; else
  if (s <= WEATHER_VCLD_THRESHOLD) return 90; else
  if (s >  WEATHER_VCLD_THRESHOLD) return 100;
#else
  return 100;
#endif
}

// gets cloud cover text
String weatherCloudCoverDescription() {
#if defined(WEATHER_CLOUD_CVR_ON) && defined(WEATHER_ON)
  double s=getAvgSkyDiffTemp();
  if (s <= -200) return "Invalid"; else
  if (s <= WEATHER_VCLR_THRESHOLD) return "Clear"; else
  if (s <= WEATHER_CLER_THRESHOLD) return "Mostly Clear"; else
  if (s <= WEATHER_HAZE_THRESHOLD) return "Slight Haze"; else
  if (s <= (WEATHER_HAZE_THRESHOLD+WEATHER_OVRC_THRESHOLD)/2.0) return "Overcast/Haze"; else
  if (s <= WEATHER_OVRC_THRESHOLD) return "Overcast"; else
  if (s <= (WEATHER_OVRC_THRESHOLD+WEATHER_CLDY_THRESHOLD)/2.0) return "Clouds/Overcast"; else
  if (s <= WEATHER_CLDY_THRESHOLD) return "Mostly Cloudy"; else
  if (s <= (WEATHER_CLDY_THRESHOLD+WEATHER_VCLD_THRESHOLD)/2.0) return "Cloudy"; else
  if (s <= WEATHER_VCLD_THRESHOLD) return "Very Cloudy"; else
  if (s >  WEATHER_VCLD_THRESHOLD) return "Very Cloudy";
#else
  return "N/A";
#endif
}

// gets cloud cover text (short)
String weatherCloudCoverDescriptionShort() {
#if defined(WEATHER_CLOUD_CVR_ON) && defined(WEATHER_ON)
  double s=getAvgSkyDiffTemp();
  if (s <= -200) return "Invalid"; else
  if (s <= WEATHER_VCLR_THRESHOLD) return "Clear"; else
  if (s <= WEATHER_CLER_THRESHOLD) return "Mostly-Clr"; else
  if (s <= WEATHER_HAZE_THRESHOLD) return "Slight-Hze"; else
  if (s <= (WEATHER_HAZE_THRESHOLD+WEATHER_OVRC_THRESHOLD)/2.0) return "Ovrcst/Hze"; else
  if (s <= WEATHER_OVRC_THRESHOLD) return "Overcast"; else
  if (s <= (WEATHER_OVRC_THRESHOLD+WEATHER_CLDY_THRESHOLD)/2.0) return "Cld/Ovrcst"; else
  if (s <= WEATHER_CLDY_THRESHOLD) return "Mstly-Cldy"; else
  if (s <= (WEATHER_CLDY_THRESHOLD+WEATHER_VCLD_THRESHOLD)/2.0) return "Cloudy"; else
  if (s <= WEATHER_VCLD_THRESHOLD) return "Very-Cldy"; else
  if (s >  WEATHER_VCLD_THRESHOLD) return "Very-Cldy";
#else
  return "N/A";
#endif
}

