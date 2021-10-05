// -----------------------------------------------------------------------------------
// Common includes
#pragma once

#include <Arduino.h>
#include "Constants.h"
#include "Config.common.h"
#include "Validate.h"
#include "HAL/HAL.h"
#include "pinmaps/Models.h"
#include "debug/Debug.h"
#include "lib/nv/NV.h"
#include "lib/convert/Convert.h"

extern NVS nv;
extern char ocsVersion[10];
