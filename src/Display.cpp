#include "Display.h"
#include "Adxl345.h"
#include "math_utils.h"


Display::Display() : display(0x20) {}

void Display::begin() {
    display.begin(16, 2);
    display.noCursor();
    display.clear();

    display.setCursor(0, 0);
    display.print("1.00G");
}

void Display::update_g(const AccelData& data) {
    if (prev_data.z == data.z) return;
    prev_data = data;

    int8_t whole = fixed_whole(data.z);
    int8_t frac = fixed_frac(data.z);

    display.setCursor(0, 0);
    display.print(whole);
    display.print(".");
    if (frac < 10) display.print("0");
    display.print(frac);
    display.print("G");
}
