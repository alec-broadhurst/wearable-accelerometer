#include "Display.h"
#include "HardwareSerial.h"
#include "Wire.h"
#include "math_utils.h"

#define RED 0x1
#define GREEN 0x2
#define WHITE 0x7


Display::Display() : _prev_data() {}

bool Display::begin() {
    _display.begin(16, 2);
    _display.setBacklight(WHITE);
    _display.noCursor();
    _display.clear();

    _display.setCursor(0, 0);
    _display.print("1.00G");
    return true;
}

void Display::update_g(const AccelData& data) {
    if (abs(_prev_data.z - data.z) < 5) return;
    _prev_data = data;

    _display.setCursor(0, 0);
    print_g(_display, data);
    _display.print(" G ");
}

void Display::print_error(const char *msg) {
    _display.setBacklight(RED);
    _display.setCursor(0, 1);
    _display.print("                ");
    _display.setCursor(0, 1);
    _display.print(msg);
}

void Display::init_complete() {
    _display.setBacklight(GREEN);
    _display.setCursor(0, 0);
    _display.print("Startup Complete");
    delay(3000);
    _display.clear();
    _display.setBacklight(WHITE);
}

DisplaySim::DisplaySim() {}

bool DisplaySim::begin() {
    return true;
}

void DisplaySim::update_g(const AccelData& data) {
    Serial.print("[DISPLAY] ");
    print_g(Serial, data);
    Serial.println(" G");
}

void DisplaySim::print_error(const char *msg) {
    Serial.print("[ERROR] ");
    Serial.println(msg);
}

void DisplaySim::init_complete() {
}
