// ----------------------------------------------------------------------------------------------------------------------------------
// Misc support functions
// ======== add your adc voltage and current support here =========

// converts a raw analog reading into voltage for STAT_DC_VOLTAGE_ANALOG and STAT_BATTERY_VOLTAGE_ANALOG
// return (invalid) if not implemented or if there's an error
float toDC(float d) {
  d=(d/1023.0);                // 0..1 for ADC range
  d=d*5.0;                     // 0..5 for Volts
  d=d/(220.0/(220.0+2200.0));  // a resistor divider 220 Ohm and 2.2K Ohm
  return d;
}

// converts a raw analog reading into current for STAT_MAINS_CURRENT_ANALOG and STAT_MAINS_AUX_CURRENT_ANALOG
// return (invalid) if not implemented or if there's an error
float toAmps(float d) {
  return (invalid);
}

// converts a raw analog reading into current for STAT_DC_CURRENT_ANALOG and STAT_BATTERY_CURRENT_ANALOG
// return (invalid) if not implemented or if there's an error
float toDCAmps(float d) {
  return (invalid);
}
