#include "Arduino.h"
#include "Adxl345.h"

int main(void) {
    /* Initialization logic */
    init();

    Serial.begin(9600);

    Adxl345 accel;
    accel.begin();


    /* main loop */
    while(1) {
        Serial.write("Hello, world!\n");
        delay(500);
    }
}
