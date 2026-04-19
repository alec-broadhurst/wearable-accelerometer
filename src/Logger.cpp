#include "Logger.h"
#include "math_utils.h"


Logger::Logger() {}

bool Logger::begin(const char* filename) {
    if (!SD.begin()) return false;

    _file = SD.open(filename, FILE_WRITE);
    _error_file = SD.open("error.log", FILE_WRITE);
    if (!_file || !_error_file) return false;

    _file.println("G, Time");
    _file.flush();

    return true;
}

bool Logger::log(const AccelData& data) {
    if (!_file) return false;

    unsigned long time = millis();

    print_g(_file, data);
    _file.print(",");
    _file.println(time);
    _file.flush();

    return true;
}

bool Logger::log_error(const char* msg) {
    if (!_error_file) return false;

    unsigned long time = millis();
    _error_file.print("[ERROR] ");
    _error_file.print(time);
    _error_file.print(": ");
    _error_file.println(msg);
    _error_file.flush();

    return true;
}

LoggerSim::LoggerSim() {}

bool LoggerSim::begin(const char* filename) {
    return true;
}

bool LoggerSim::log(const AccelData& data) {
    unsigned long time = millis();

    Serial.print("[LOG] ");
    print_g(Serial, data);
    Serial.print(",");
    Serial.println(time);

    return true;
}

bool LoggerSim::log_error(const char* msg) {
    Serial.print("[ERROR] ");
    Serial.println(msg);

    return true;
}
