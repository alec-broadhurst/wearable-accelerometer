avrdude -p atmega328p -c arduino -P /dev/cu.usbmodem13201 -b 115200 -U flash:w:build/wearable-accelerometer.hex
