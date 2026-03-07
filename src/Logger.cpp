#include "Adxl345.h"
#include "Logger.h"

#define LOG_BUF_SIZE 16


Logger::Logger(const char* filename) {
    SD.begin();
    file = SD.open(filename, FILE_WRITE);
    file.println("G, Time");
}

void Logger::log(AccelData data) {
    unsigned long time = millis();
    char entry[LOG_BUF_SIZE];

    strcat(entry, itoa(data.z / G_SCALE, entry, 10));
    strcat(entry, ".");
    strcat(entry, itoa(data.z % G_SCALE, entry, 10));
    strcat(entry, ",");
    strcat(entry, ultoa(time, entry, 10));
    strcat(entry, ",");

    file.println(entry);
}
