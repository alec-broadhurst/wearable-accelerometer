#pragma once

#include "Adxl345.h"
#include "Display.h"
#include "Logger.h"


enum SystemError {
    SD_ERROR,
    SENSOR_ERROR,
    DISPLAY_ERROR,
};

class System {
    public:
        System();
        void begin(const char* logFilename);
        void update();

    private:
        Adxl345 _sensor;
        Display _display;
        Logger _logger;

        void _handleError(SystemError error);
};
