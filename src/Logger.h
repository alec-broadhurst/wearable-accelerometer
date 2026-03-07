#pragma once

#include "SD.h"
#include "Adxl345.h"

struct Timestamp {
    char hours[2];
    char minutes[2];
    char seconds[2];
    char milliseconds[3];
};

class Logger {
    public:
        Logger(const char* filename);
        void log(AccelData data);

    private:
        File file;
};
