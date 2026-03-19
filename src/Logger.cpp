#include "Logger.h"
#include "math_utils.h"


Logger::Logger(const char* filename) {
    SD.begin();
    file = SD.open(filename, FILE_WRITE);
    file.println("G, Time");
}

void Logger::log(const AccelData& data) {
    unsigned long time = millis();

    int8_t whole = fixed_whole(data.z);
    int8_t frac = fixed_frac(data.z);

    file.print(whole);
    file.print(".");
    if (frac < 10) file.print("0");
    file.print(frac);
    file.print(",");
    file.println(time);
}
