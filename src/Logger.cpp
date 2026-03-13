#include "Logger.h"


Logger::Logger(const char* filename) {
    SD.begin();
    file = SD.open(filename, FILE_WRITE);
    file.println("G, Time");
}

void Logger::log(const AccelData& data) {
    unsigned long time = millis();

    file.print(data.z / G_SCALE);
    file.print(".");
    file.print(data.z % G_SCALE);
    file.print(",");
    file.println(time);
}
