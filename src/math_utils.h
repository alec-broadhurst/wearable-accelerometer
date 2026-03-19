#pragma once

#include "Arduino.h"
#include "Adxl345.h"


inline int8_t fixed_whole(int16_t data) {
    return data >> 8;
}

inline uint8_t fixed_frac(int16_t data) {
    return ((abs(data) & 0xFF) * 100 >> 8) - (fixed_whole(data) * 100);
}
