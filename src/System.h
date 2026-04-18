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
        #ifdef DEBUG
        Adxl345Sim _sensor;
        DisplaySim _display;
        LoggerSim _logger;
        #else
        Adxl345 _sensor;
        Display _display;
        Logger _logger;
        #endif

        AccelData _sensorData;
        void _handleError(SystemError error);
};
