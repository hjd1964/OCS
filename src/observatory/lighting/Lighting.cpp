// -----------------------------------------------------------------------------------------------------------------
// Observatory lighting
#include "Lighting.h"

#ifdef LIGHT_PRESENT

#include "../../libApp/relay/Relay.h"

void Lighting::init() {
  #if LIGHT_STRIP_DATA_PIN != OFF
    FastLED.addLeds LIGHT_STRIP_INIT (leds, LIGHT_STRIP_COUNT);
  #endif
}

void Lighting::set(LightLocation location, LightMode mode) {

  #if LIGHT_STRIP_DATA_PIN != OFF
    const int ObservingRoom[2] = LIGHT_STRIP_OR_RANGE;
    const int WarmRoom[2] = LIGHT_STRIP_WR_RANGE;
    CRGB rgb;
    switch (mode) {
      case LM_OFF: rgb = 0x000000; break;
      case LM_RED: rgb = LIGHT_STRIP_RED; break;
      case LM_WHITE: rgb = LIGHT_STRIP_WHITE; break;
    }
  #endif

  switch (location) {
    case LL_OBSERVING_ROOM:
      #if LIGHT_STRIP_DATA_PIN != OFF
        for (int index = ObservingRoom[0]; index <= ObservingRoom[1]; index++) leds[index] = rgb;
        FastLED.show();
      #endif
      #if LIGHT_ORW_RELAY != OFF
        if (mode == LM_WHITE) relay.on(LIGHT_ORW_RELAY); else relay.off(LIGHT_ORW_RELAY);
      #endif
      #if LIGHT_ORR_RELAY != OFF
        if (mode == LM_RED) relay.on(LIGHT_ORR_RELAY); else relay.off(LIGHT_ORR_RELAY);
      #endif
      observingRoomLightMode = mode;
    break;
    case LL_WARM_ROOM:
      #if LIGHT_STRIP_DATA_PIN != OFF
        for (int index = WarmRoom[0]; index <= WarmRoom[1]; index++) leds[index] = rgb;
        FastLED.show();
      #endif
      #if LIGHT_WRW_RELAY != OFF
        if (mode == LM_WHITE) relay.on(LIGHT_WRW_RELAY); else relay.off(LIGHT_WRW_RELAY);
      #endif
      #if LIGHT_WRR_RELAY != OFF
        if (mode == LM_RED) relay.on(LIGHT_WRR_RELAY); else relay.off(LIGHT_WRR_RELAY);
      #endif
      warmRoomLightMode = mode;
    break;
  }
}

LightMode Lighting::get(LightLocation location) {
  switch (location) {
    case LL_OBSERVING_ROOM:
      if (relay.isOn(LIGHT_ORW_RELAY)) return LM_WHITE; else
      if (relay.isOn(LIGHT_ORR_RELAY)) return LM_RED; else
      return observingRoomLightMode;
    break;
    case LL_WARM_ROOM:
      if (relay.isOn(LIGHT_WRW_RELAY)) return LM_WHITE; else
      if (relay.isOn(LIGHT_WRR_RELAY)) return LM_RED; else
      return warmRoomLightMode;
    break;
    default:
      return LM_OFF;
    break;
  }
}

Lighting lighting;

#endif
