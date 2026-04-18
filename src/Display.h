#pragma once

#include "Adxl345.h"
#include "Adafruit_LiquidCrystal.h"


class Display {
    public:
        Display();
        bool begin();
        void update_g(const AccelData& data);
        void print_error(const char* msg);
        void init_complete();

    private:
        Adafruit_LiquidCrystal display;
        AccelData prev_data;
};

class DisplaySim {
    public:
        DisplaySim();
        bool begin();
        void update_g(const AccelData& data);
        void print_error(const char* msg);
        void init_complete();
};
