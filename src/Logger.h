#pragma once

#include "SD.h"
#include "Adxl345.h"


class Logger {
    public:
        Logger();
        bool begin(const char* filename);
        bool log(const AccelData& data);
        bool log_error(const char* msg);

    private:
        File _file;
        File _error_file;
};
