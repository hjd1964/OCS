// -----------------------------------------------------------------------------------
// Alpaca Dome

#include <ArduinoJson.h>

#include "../Common.h"

#if ASCOM_ALPACA_SERVER == ON && (defined(ROOF_PRESENT) || defined(DOME_PRESENT))

#include "Alpaca.h"
#include "../observatory/roof/Roof.h"
#include "../observatory/dome/Dome.h"

extern StaticJsonDocument<1000> alpacaJsonDoc;
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
  String connected = alpacaArgLowerCase("connected");
  if (!connected.equals(EmptyStr)) {
    if (connected.equals("true")) domeConnected++; else
    if (connected.equals("false")) domeConnected--; else {
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
  #if defined(DOME_PRESENT) && AXIS2_DRIVER_MODEL != OFF
    if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
    alpacaJsonDoc["Value"] = dome.getAltitude();
    alpacaJsonFinish(NoException, "");
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  #endif
}

void alpacaDomeAtHome() {
  alpacaJsonStart();
  #ifdef DOME_PRESENT
    if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }

    #if AXIS2_DRIVER_MODEL != OFF
      alpacaJsonDoc["Value"] = (dome.getAzimuth() == 0.0F && dome.getAltitude() == 0.0F);
    #else
      alpacaJsonDoc["Value"] = (dome.getAzimuth() == 0.0F);
    #endif

    alpacaJsonFinish(NoException, "");
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  #endif
}

void alpacaDomeAtPark() {
  alpacaJsonStart();
  #ifdef DOME_PRESENT
    if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
    alpacaJsonDoc["Value"] = dome.isParked();
    alpacaJsonFinish(NoException, "");
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  #endif
}

void alpacaDomeAzimuth() {
  alpacaJsonStart();
  #ifdef DOME_PRESENT
    if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
    alpacaJsonDoc["Value"] = dome.getAzimuth();
    alpacaJsonFinish(NoException, "");
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  #endif
}

void alpacaDomeCanFindHome() {
  alpacaJsonStart();
  #ifdef DOME_PRESENT
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanPark() {
  alpacaJsonStart();
  #ifdef DOME_PRESENT
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSetAltitude() {
  alpacaJsonStart();
  #if defined(DOME_PRESENT) && AXIS2_DRIVER_MODEL != OFF
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSetAzimuth() {
  alpacaJsonStart();
  #ifdef DOME_PRESENT
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSetPark() {
  alpacaJsonStart();
  #ifdef DOME_PRESENT
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSetShutter() {
  alpacaJsonStart();
  #ifdef ROOF_PRESENT
    alpacaJsonDoc["Value"] = true;
  #else
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSlave() {
  alpacaJsonStart();
  #ifdef ROOF_PRESENT
    alpacaJsonDoc["Value"] = false;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCanSyncAzimuth() {
  alpacaJsonStart();
  #ifdef ROOF_PRESENT
    alpacaJsonDoc["Value"] = true;
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeShutterStatus() {
  alpacaJsonStart();
  #ifdef ROOF_PRESENT
    if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
    int status = SHUTTER_STATUS_ERROR;
    if (roof.isOpening()) status = SHUTTER_STATUS_OPENING; else
    if (roof.isClosing()) status = SHUTTER_STATUS_CLOSING; else
    if (roof.isOpen()) status = SHUTTER_STATUS_OPEN; else
    if (roof.isClosed()) status = SHUTTER_STATUS_CLOSED;
    alpacaJsonDoc["Value"] = status;
    alpacaJsonFinish(NoException, "");
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  #endif
}

void alpacaDomeSlaved() {
  alpacaJsonStart();
  String slaved = alpacaArgLowerCase("slaved");
  if (slaved.equals(EmptyStr)) {
    alpacaJsonDoc["Value"] = false;
    alpacaJsonFinish(NoException, "");
  } else {
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  }
}

void alpacaDomeSlewing() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
  bool domeSlewing = false;
  bool roofMoving = false;
  #ifdef DOME_PRESENT
    domeSlewing = dome.isSlewing();
  #endif
  #ifdef ROOF_PRESENT
    roofMoving = roof.isMoving();
  #endif
  alpacaJsonDoc["Value"] = domeSlewing || roofMoving;
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeAbortSlew() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
  #ifdef DOME_PRESENT
    dome.stop();
  #endif
  #ifdef ROOF_PRESENT
    roof.stop();
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeCloseShutter() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
  #ifdef ROOF_PRESENT
    if (!roof.close()) {
      alpacaJsonFinish(InvalidOperationException, InvalidOperationMessage); return;
    }
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeFindHome() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
  #ifdef DOME_PRESENT
    if (dome.findHome() != CE_NONE) {
      alpacaJsonFinish(InvalidOperationException, InvalidOperationMessage); return;
    }
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeOpenShutter() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
  #ifdef ROOF_PRESENT
    if (!roof.open()) {
      alpacaJsonFinish(InvalidOperationException, InvalidOperationMessage); return;
    }
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomePark() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
  #ifdef DOME_PRESENT
    if (dome.park() != CE_NONE) {
      alpacaJsonFinish(InvalidOperationException, InvalidOperationMessage); return;
    }
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeSetPark() {
  alpacaJsonStart();
  if (domeConnected == 0) { alpacaJsonFinish(NotConnectedException, NotConnectedMessage); return;  }
  #ifdef DOME_PRESENT
    if (dome.setpark() != CE_NONE) {
      alpacaJsonFinish(InvalidOperationException, InvalidOperationMessage); return;
    }
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return; 
  #endif
  alpacaJsonFinish(NoException, "");
}

void alpacaDomeSlewToAltitude() {
  alpacaJsonStart();
  #if defined(DOME_PRESENT) && AXIS2_DRIVER_MODEL != OFF
    String v = alpacaArgLowerCase("altitude");
    if (!v.equals(EmptyStr)) {
      float altitude = atof(v.c_str());
      if (altitude < 0.0F || altitude > 90.0F) {
        alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; 
      }
      dome.setTargetAltitude(altitude);
      if (dome.gotoAltitudeTarget() != CE_NONE) {
        alpacaJsonFinish(InvalidOperationException, InvalidOperationMessage); return;
      }
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; 
    }
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return;
  #endif
}

void alpacaDomeSlewToAzimuth() {
  alpacaJsonStart();
  #ifdef DOME_PRESENT
    String v = alpacaArgLowerCase("azimuth");
    if (!v.equals(EmptyStr)) {
      float azimuth = atof(v.c_str());
      if (azimuth < 0.0F || azimuth >= 360.0F) {
        alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; 
      }
      if (dome.isParked()) dome.unpark();
      dome.setTargetAzimuth(azimuth);
      if (dome.gotoAzimuthTarget() != CE_NONE) {
        alpacaJsonFinish(InvalidOperationException, InvalidOperationMessage); return;
      }
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; 
    }
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return;
  #endif
}

void alpacaDomeSyncToAzimuth() {
  alpacaJsonStart();
  #ifdef DOME_PRESENT
    String v = alpacaArgLowerCase("azimuth");
    if (!v.equals(EmptyStr)) {
      float azimuth = atof(v.c_str());
      if (azimuth < 0.0F || azimuth >= 360.0F) {
        alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; 
      }
      if (dome.isParked()) dome.unpark();
      dome.setTargetAzimuth(azimuth);
      CommandError e = dome.syncAzimuthTarget();
      if (e != CE_NONE) {
        alpacaJsonFinish(InvalidOperationException, InvalidOperationMessage); return;
      }
      alpacaJsonFinish(NoException, "");
    } else {
      alpacaJsonFinish(InvalidValueException, InvalidValueMessage); return; 
    }
  #else
    alpacaJsonFinish(NotImplementedException, NotImplementedMessage); return;
  #endif
}

#endif
