#include "Adxl345.h"

Adxl345::Adxl345() : accel(117) {}

bool Adxl345::begin() {
    if (!accel.begin()) {
        return false;
    }

    accel.setRange(ADXL345_RANGE_8_G);
    accel.setDataRate(ADXL345_DATARATE_50_HZ);
    accel.writeRegister(ADXL345_REG_OFSZ, 8); // offset z-axis

    return true;
}

void Adxl345::read(AccelData& data) {
    data.x = accel.getX();
    data.y = accel.getY();
    data.z = accel.getZ();
}

Adxl345Sim::Adxl345Sim() {}

bool Adxl345Sim::begin() {
    return true;
}

void Adxl345Sim::read(AccelData& data) {
    static int16_t val = 256;
    static int8_t dir = 1;

    val += dir * 7;

    if (val > 600 || val < -300)
        dir *= -1;

    data.x = 0;
    data.y = 0;
    data.z = val;
}
