#include "Display.h"
#include "Adxl345.h"
#include "math_utils.h"

#define RED 0x1
#define GREEN 0x2
#define WHITE 0x7


Display::Display() : display(0x20) {}

bool Display::begin() {
    if (!display.begin(16, 2)) return false;
    display.setBacklight(WHITE);
    display.noCursor();
    display.clear();

    display.setCursor(0, 0);
    display.print("1.00G");
    return true;
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

void Display::print_error(const char *msg) {
    display.setBacklight(RED);
    display.setCursor(0, 1);
    display.print("                ");
    display.setCursor(0, 1);
    display.print(msg);
}

void Display::init_complete() {
    display.setBacklight(GREEN);
    display.setCursor(0, 0);
    display.print("Startup Complete");
    delay(3000);
    display.clear();
    display.setBacklight(WHITE);
}
