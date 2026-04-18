#include "System.h"


int main(void) {
    /* Initialization logic */
    init(); // Arduino setup

    #if defined (DEBUG) || defined (SIM)
        Serial.begin(9600);
    #endif

    System system;
    system.begin("log.csv"); // peripheral initialization


    /* main loop */
    while(1) {
        system.update();
        delay(20);
    }
}
