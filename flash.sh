avrdude -p atmega328p -c arduino -P $1 -b 115200 -U flash:w:build/wearable-accelerometer.hex
