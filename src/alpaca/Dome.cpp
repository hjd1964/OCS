// -----------------------------------------------------------------------------------
// Alpaca Dome

#include <ArduinoJson.h>

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON

#if DOME == ON || ROOF == ON 

#include "Alpaca.h"
#include "../observatory/roof/Roof.h"
#include "../observatory/dome/Dome.h"

extern StaticJsonDocument<200> alpacaJsonDoc;
int32_t domeConnected = 0;

#define SHUTTER_STATUS_OPEN 0
#define SHUTTER_STATUS_CLOSED 1
#define SHUTTER_STATUS_OPENING 2
#define SHUTTER_STATUS_CLOSING 3
#define SHUTTER_STATUS_ERROR 4

void alpacaDomeConnected() {
  int exceptionCode = NoException;
  String exceptionValue = "";

  alpacaJsonStart();
  String connected = apc.argLowerCase("connected");
  if (!connected.equals(EmptyStr)) {
    if (connected.toLowerCase().equals("true")) domeConnected++; else
    if (connected.toLowerCase().equals("false")) domeConnected--; else {
      exceptionCode = InvalidValueException;
      exceptionValue = "Invalid value";
    }
    if (domeConnected < 0) domeConnected = 0;
  } else {
    alpacaJsonDoc["Value"] = domeConnected > 0;
  }
  alpacaJsonFinish(exceptionCode, exceptionValue);
}

void alpacaDomeAltitude() {
  alpacaJsonStart();
  #if DOME == ON && AXIS2_DRIVER_MODEL != OFF
    if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
    alpacaJsonDoc["Value"] = dome.getAltitude();
    alpacaJsonFinish(NoException, "");
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  #endif
}

void alpacaDomeAtHome() {
  alpacaJsonStart();
  #if DOME == ON
    if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
    alpacaJsonDoc["Value"] = (dome.getAzimuth() == 0.0F && dome.getAltitude() == 0.0F);
    alpacaJsonFinish(NoException, "");
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  #endif
}

void alpacaDomeAtPark() {
  alpacaJsonStart();
  #if DOME == ON
    if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
    alpacaJsonDoc["Value"] = dome.isParked();
    alpacaJsonFinish(NoException, "");
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  #endif
}

void alpacaDomeAzimuth() {
  alpacaJsonStart();
  #if DOME == ON
    if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
    alpacaJsonDoc["Value"] = dome.getAzimuth();
    alpacaJsonFinish(NoException, "");
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  #endif
}

void alpacaDomeCanFindHome() {
  alpacaJsonStart();
  #if DOME == ON
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanPark() {
  alpacaJsonStart();
  #if DOME == ON
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSetAltitude() {
  alpacaJsonStart();
  #if DOME == ON && AXIS2_DRIVER_MODEL != OFF
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSetAzimuth() {
  alpacaJsonStart();
  #if DOME == ON
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSetPark() {
  alpacaJsonStart();
  #if DOME == ON
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSetShutter() {
  alpacaJsonStart();
  #if ROOF == ON
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSlave() {
  alpacaJsonStart();
  #if ROOF == ON
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSyncAzimuth() {
  alpacaJsonStart();
  #if ROOF == ON
    alpacaJsonDoc["Value"] = true;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeShutterStatus() {
  alpacaJsonStart();
  #if ROOF == ON
    if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
    int status = SHUTTER_STATUS_ERROR;
    if (roof.isOpening()) status = SHUTTER_STATUS_OPENING; else
    if (roof.isClosing()) status = SHUTTER_STATUS_CLOSING; else
    if (roof.isOpen()) status = SHUTTER_STATUS_OPEN; else
    if (roof.isClosed()) status = SHUTTER_STATUS_CLOSED;
    alpacaJsonDoc["Value"] = status;
    alpacaJsonFinish(NoException, "");
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  #endif
}

void alpacaDomeSlaved() {
  alpacaJsonStart();
  String slaved = apc.argLowerCase("slaved");
  if (slaved.equals(EmptyStr)) {
    alpacaJsonDoc["Value"] = false;
    alpacaJsonFinish(NoException, "");
  } else {
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  }
}

void alpacaDomeSlewing() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
  bool domeSlewing = false;
  bool roofMoving = false;
  #if DOME == ON
    domeSlewing = dome.isSlewing();
  #endif
  #if ROOF == ON
    roofMoving = roof.isMoving();
  #endif
  alpacaJsonDoc["Value"] = domeSlewing || roofMoving;
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeAbortSlew() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
  #if DOME == ON
    dome.stop();
  #endif
  #if ROOF == ON
    roof.stop();
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCloseShutter() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
  #if ROOF == ON
    if (!roof.close()) {
      alpacaJsonFinish(InvalidOperationException, "Invalid Operation"); return;
    }
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeFindHome() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
  #if DOME == ON
    if (dome.findHome() != CE_NONE) {
      alpacaJsonFinish(InvalidOperationException, "Invalid Operation"); return;
    }
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeOpenShutter() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
  #if ROOF == ON
    if (!roof.open()) {
      alpacaJsonFinish(InvalidOperationException, "Invalid Operation"); return;
    }
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomePark() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
  #if DOME == ON
    if (dome.park() != CE_NONE) {
      alpacaJsonFinish(InvalidOperationException, "Invalid Operation"); return;
    }
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeSetPark() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, "Not connected"); return;  }
  #if DOME == ON
    if (dome.setpark() != CE_NONE) {
      alpacaJsonFinish(InvalidOperationException, "Invalid Operation"); return;
    }
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return; 
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeSlewToAltitude() {
  alpacaJsonStart();
  #if DOME == ON
    String v = apc.argLowerCase("altitude");
    if (!v.equals(EmptyStr)) {
      float altitude = atof(v.c_str());
      if (altitude < 0.0F || altitude > 90.0F) {
        alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; 
      }
      dome.setTargetAltitude(altitude);
      if (dome.gotoAltitudeTarget() != CE_NONE) {
        alpacaJsonFinish(InvalidOperationException, "Invalid Operation"); return;
      }
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; 
    }
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return;
  #endif
}

void alpacaDomeSlewToAzimuth() {
  alpacaJsonStart();
  #if DOME == ON
    String v = apc.argLowerCase("azimuth");
    if (!v.equals(EmptyStr)) {
      float azimuth = atof(v.c_str());
      if (azimuth < 0.0F || azimuth >= 360.0F) {
        alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; 
      }
      if (dome.isParked()) dome.unpark();
      dome.setTargetAzimuth(azimuth);
      if (dome.gotoAzimuthTarget() != CE_NONE) {
        alpacaJsonFinish(InvalidOperationException, "Invalid Operation"); return;
      }
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; 
    }
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return;
  #endif
}

void alpacaDomeSyncToAzimuth() {
  alpacaJsonStart();
  #if DOME == ON
    String v = apc.argLowerCase("azimuth");
    if (!v.equals(EmptyStr)) {
      float azimuth = atof(v.c_str());
      if (azimuth < 0.0F || azimuth >= 360.0F) {
        alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; 
      }
      if (dome.isParked()) dome.unpark();
      dome.setTargetAzimuth(azimuth);
      CommandError e = dome.syncAzimuthTarget();
      if (e != CE_NONE) {
        alpacaJsonFinish(InvalidOperationException, "Invalid Operation"); return;
      }
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(InvalidValueException, "Invalid Value"); return; 
    }
  #else
    alpacaJsonFinish(NotImplementedException, "Not implemented"); return;
  #endif
}

#endif

#endif
