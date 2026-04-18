#pragma once

#include "Arduino.h"
#include "Adxl345.h"


inline int8_t fixed_whole(int16_t data) {
    return data / 256;
}

inline uint8_t fixed_frac(int16_t data) {
    uint16_t remainder = abs(data) % 256;
    return (uint8_t)((remainder * 100 + 128) >> 8);
}