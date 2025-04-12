// -----------------------------------------------------------------------------------
// I2C PCF8575 GPIO support

#include "Pcf8574.h"

#if defined(GPIO_DEVICE) && GPIO_DEVICE == X8574

#ifndef GPIO_PCF8574_I2C_BASE_ADDRESS
  #define GPIO_PCF8574_I2C_BASE_ADDRESS 0x39
#endif
#ifndef GPIO_PCF8574_I2C_NUM_DEVICES
  #define GPIO_PCF8574_I2C_NUM_DEVICES 1
#endif

PCF8574 pcf0(GPIO_PCF8574_I2C_BASE_ADDRESS);
#if GPIO_PCF8574_I2C_NUM_DEVICES > 1
  PCF8574 pcf1(GPIO_PCF8574_I2C_BASE_ADDRESS + 1);
  #if GPIO_PCF8574_I2C_NUM_DEVICES > 2
    PCF8574 pcf2(GPIO_PCF8574_I2C_BASE_ADDRESS + 2);
    #if GPIO_PCF8574_I2C_NUM_DEVICES > 3
      PCF8574 pcf3(GPIO_PCF8574_I2C_BASE_ADDRESS + 3);
    #endif
  #endif
#endif

// check for up to four PCF8574 devices on the I2C bus
bool GpioPcf8574::init() {
  static bool initialized = false;
  if (initialized) return found;

  for (int i = 0; i < 4; i++) { pcf[i] = NULL; }
  pcf[0] = &pcf0;
  #if GPIO_PCF8574_I2C_NUM_DEVICES > 1
    pcf[1] = &pcf1;
    #if GPIO_PCF8574_I2C_NUM_DEVICES > 2
      pcf[2] = &pcf2;
      #if GPIO_PCF8574_I2C_NUM_DEVICES > 3
        pcf[3] = &pcf3;
      #endif
    #endif
  #endif

  for (int i = 0; i < 4; i++) {
    if (pcf[i] != NULL) {
      if (pcf[i]->begin()) {
        found = true;
      } else {
        found = false;
        DF("WRN: Gpio.init(), PCF8574 (I2C 0x");
        if (DEBUG != OFF) {
          switch (i) {
            case 0: SERIAL_DEBUG.print(GPIO_PCF8574_I2C_BASE_ADDRESS, HEX); break;
            #if GPIO_PCF8574_I2C_NUM_DEVICES > 1
            case 1: SERIAL_DEBUG.print(GPIO_PCF8574_I2C_BASE_ADDRESS + 1, HEX); break;
            #endif
            #if GPIO_PCF8574_I2C_NUM_DEVICES > 2
            case 2: SERIAL_DEBUG.print(GPIO_PCF8574_I2C_BASE_ADDRESS + 2, HEX); break;
            #endif
            #if GPIO_PCF8574_I2C_NUM_DEVICES > 3
            case 3: SERIAL_DEBUG.print(GPIO_PCF8574_I2C_BASE_ADDRESS + 3, HEX); break;
            #endif
          }
        }
        DLF(") not found");
      }
    }
  }

  #ifdef HAL_WIRE_CLOCK
    HAL_WIRE.setClock(HAL_WIRE_CLOCK);
  #endif

  for (int i = 0; i < 32; i++) { mode[i] = INPUT; state[i] = false; };

  return found;
}

// set GPIO pin (0 to 31) mode for INPUT or OUTPUT
void GpioPcf8574::pinMode(int pin, int mode) {
  if (found && pin >= 0 && pin <= 31) {
    #ifdef INPUT_PULLDOWN
      if (mode == INPUT_PULLDOWN) mode = INPUT;
    #endif
    if (mode == INPUT_PULLUP) mode = INPUT;
    pcf[pin >> 3]->pinMode(pin & 0b111, mode);
    this->mode[pin] = mode;
  }
}

// get GPIO pin (0 to 31) state
int GpioPcf8574::digitalRead(int pin) {
  if (found && pin >= 0 && pin <= 31) {
    if (mode[pin] == INPUT) {
      return pcf[pin >> 3]->digitalRead(pin & 0b111);
    } else return state[pin];
  } else return 0;
}

// set GPIO pin (0 to 31) state
void GpioPcf8574::digitalWrite(int pin, int value) {
  if (found && pin >= 0 && pin <= 31) {
    state[pin] = value;
    if (mode[pin] == OUTPUT) {
      pcf[pin >> 3]->digitalWrite(pin & 0b111, value);
    }
  } else return;
}

GpioPcf8574 gpio;

#endif
