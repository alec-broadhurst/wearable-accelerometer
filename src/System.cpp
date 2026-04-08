#include "System.h"
#include "debug.h"


static const char* errorToString(SystemError error) {
    switch (error) {
        case DISPLAY_ERROR: return "Display error";
        case SENSOR_ERROR: return "Sensor error";
        case SD_ERROR: return "SD error";
        default: return "Unknown error";
    }
}

System::System() {}

void System::begin(const char* logFilename) {
    if (!_display.begin()) _handleError(DISPLAY_ERROR);
    if (!_sensor.begin()) _handleError(SENSOR_ERROR);
    if (!_logger.begin(logFilename)) _handleError(SD_ERROR);

    _display.init_complete();
}

void System::update() {
    _sensor.read(_sensorData);
    _display.update_g(_sensorData);
    if (!_logger.log(_sensorData)) _handleError(SD_ERROR);
}

void System::_handleError(SystemError error) {
    const char* msg = errorToString(error);
    DEBUG_PRINT(msg);

    if (error != DISPLAY_ERROR) {
        _display.print_error(msg);
    }

    if (error != SD_ERROR) {
        _logger.log_error(msg);
    }
}
