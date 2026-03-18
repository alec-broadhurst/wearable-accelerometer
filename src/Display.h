#pragma once

#include "Adxl345.h"
#include "Adafruit_LiquidCrystal.h"


class Display {
    public:
        Display();
        void begin();
        void update_g(const AccelData& data);

    private:
        Adafruit_LiquidCrystal display;
        AccelData prev_data;
};
