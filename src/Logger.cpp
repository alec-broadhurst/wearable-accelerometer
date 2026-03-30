#include "Logger.h"
#include "math_utils.h"


Logger::Logger() {}

bool Logger::begin(const char* filename) {
    if (!SD.begin()) return false;

    _file = SD.open(filename, FILE_WRITE);
    _file.println("G, Time");

    return true;
}

void Logger::log(const AccelData& data) {
    unsigned long time = millis();

    int8_t whole = fixed_whole(data.z);
    int8_t frac = fixed_frac(data.z);

    _file.print(whole);
    _file.print(".");
    if (frac < 10) _file.print("0");
    _file.print(frac);
    _file.print(",");
    _file.println(time);
}
