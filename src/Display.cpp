#include "Display.h"
#include "Adxl345.h"


Display::Display() : display(0x20) {}

void Display::begin() {}

void Display::update_g(const AccelData& data) {}
