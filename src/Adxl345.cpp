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
    AccelData data;

    data.x = accel.getX() * G_SCALE / STEPS_PER_G;
    data.y = accel.getY() * G_SCALE / STEPS_PER_G;
    data.z = accel.getZ() * G_SCALE / STEPS_PER_G;

    return data;
}
