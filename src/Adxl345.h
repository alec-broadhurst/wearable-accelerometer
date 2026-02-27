#pragma once

#include "Arduino.h"
#include "Adafruit_ADXL345_U.h"

struct AccelData {
    int16_t x;
    int16_t y;
    int16_t z;
};

class Adxl345 {
    public:
        Adxl345();
        bool begin();
        AccelData read();

    private:
        Adafruit_ADXL345_Unified accel;
};
