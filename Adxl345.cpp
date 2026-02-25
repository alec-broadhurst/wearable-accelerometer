#include "Adxl345.h"

Adxl345::Adxl345() : accel(117) {}

bool Adxl345::begin() {
    if (!accel.begin()) {
        return false;
    }

    accel.setRange(ADXL345_RANGE_8_G);             
    accel.setDataRate(ADXL345_DATARATE_50_HZ);     

    return true;
}

AccelData Adxl345::read() {
    return { accel.getX(), accel.getY(), accel.getZ() };
}
