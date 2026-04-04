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
}

void System::update() {
    AccelData data = _sensor.read();
    _display.update_g(data);
    if (!_logger.log(data)) _handleError(SD_ERROR);
}

void System::_handleError(SystemError error) {
    const char* msg = errorToString(error);
    DEBUG_PRINT(msg);

    if (error != DISPLAY_ERROR) {
        // _display.show_error();
    }

    if (error != SD_ERROR) {
        _logger.log_error(msg);
    }
}
