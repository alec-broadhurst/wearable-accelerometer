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

inline void print_g(Print& out, const AccelData& data) {
    int8_t whole = fixed_whole(data.z);
    uint8_t frac = fixed_frac(data.z);

    if (data.z < 0 && whole == 0) out.print("-");
    out.print(whole);
    out.print(".");
    if (frac < 10) out.print("0");
    out.print(frac);
}
