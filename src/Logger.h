#pragma once

#include "SD.h"
#include "Adxl345.h"


class Logger {
    public:
        Logger(const char* filename);
        void log(AccelData data);

    private:
        File file;
};
