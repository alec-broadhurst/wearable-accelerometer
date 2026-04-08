#include "System.h"


int main(void) {
    /* Initialization logic */
    init(); // Arduino setup

    System system;
    system.begin("log.csv"); // peripheral initialization


    /* main loop */
    while(1) {
        system.update();
    }
}
