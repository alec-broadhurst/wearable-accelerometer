#include "System.h"
#include "debug.h"

#define LOG_THRESHOLD 333 // 1.30 G


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
    uint8_t failures = 0;

    if (!_display.begin()) failures |= 1 << DISPLAY_ERROR;
    if (!_sensor.begin()) failures |= 1 << SENSOR_ERROR;
    if (!_logger.begin(logFilename)) failures |= 1 << SD_ERROR;

    if (failures & (1 << DISPLAY_ERROR)) _handleError(DISPLAY_ERROR);
    if (failures & (1 << SENSOR_ERROR)) _handleError(SENSOR_ERROR);
    if (failures & (1 << SD_ERROR)) _handleError(SD_ERROR);

    if (!failures) _display.init_complete();
}

void System::update() {
    _sensor.read(_sensorData);
    _display.update_g(_sensorData);

    if (abs(_sensorData.z) >= LOG_THRESHOLD) {
        if (!_logger.log(_sensorData)) _handleError(SD_ERROR);
    }
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

    if (error == SENSOR_ERROR) {
        while (1);
    }
}
