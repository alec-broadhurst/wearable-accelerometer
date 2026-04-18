#include "Logger.h"
#include "math_utils.h"


Logger::Logger() {}

bool Logger::begin(const char* filename) {
    if (!SD.begin()) return false;

    _file = SD.open(filename, FILE_WRITE);
    _error_file = SD.open("error.log", FILE_WRITE);
    if (!_file || !_error_file) return false;

    _file.println("G, Time");

    return true;
}

bool Logger::log(const AccelData& data) {
    if (!_file) return false;

    unsigned long time = millis();

    int8_t whole = fixed_whole(data.z);
    int8_t frac = fixed_frac(data.z);

    if (data.z < 0 && whole == 0) _file.print("-");
    _file.print(whole);
    _file.print(".");
    if (frac < 10) _file.print("0");
    _file.print(frac);
    _file.print(",");
    _file.println(time);

    return true;
}

bool Logger::log_error(const char* msg) {
    if (!_error_file) return false;

    unsigned long time = millis();
    _error_file.print("[ERROR] ");
    _error_file.print(time);
    _error_file.print(": ");
    _error_file.println(msg);

    return true;
}
