#pragma once

#ifdef DEBUG
    #include "Arduino.h"
    #define DEBUG_PRINT(msg) Serial.println(msg)
#else
    #define DEBUG_PRINT(msg)
#endif
