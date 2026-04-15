# Wearable Accelerometer Data Logger

## Project Overview
This is an embedded wearable device designed to log high-frequency acceleration data to an SD card while providing real-time feedback via an I2C-enabled RGB Liquid Crystal Display (LCD). The system is built on the **Arduino Uno R3 (ATmega328P)** platform and is optimized for low-latency performance and data integrity.

This project serves as a Senior Project, demonstrating principles of embedded systems architecture, fixed-point mathematics, and hardware-software co-design.

---

## Hardware Architecture
The system utilizes a modular I2C/SPI bus architecture:
- **Processor:** Arduino Uno R3 (8-bit AVR @ 16MHz)
- **Sensor:** Adafruit ADXL345 (3-axis digital accelerometer)
- **Display:** 16x2 RGB LCD with I2C Backpack (MCP23017)
- **Storage:** Standard SD Data Logging Shield (SPI)

### Pin Mapping
| Component | Bus | Pin(s) | Notes |
| :--- | :--- | :--- | :--- |
| ADXL345 | I2C | A4 (SDA), A5 (SCL) | Default Address: `0x53` |
| LCD Backpack | I2C | A4 (SDA), A5 (SCL) | Configured Address: `0x20` |
| SD Card | SPI | 10 (CS), 11 (MOSI), 12 (MISO), 13 (SCK) | Default Hardware SS |

---

## Software Design
The firmware is written in C++ using a class-based approach to ensure modularity and ease of maintenance.

### Key Technical Decisions

1. **Fixed-Point Mathematics:**
   To maximize performance on the 8-bit ATmega328P (which lacks a Floating Point Unit), the system uses fixed-point math for G-force calculations.

2. **Loop Throttling (50 Hz):**
   The main loop is throttled to 50 Hz. This matches the sensor's internal data rate, preventing redundant SD card writes and extending battery life.

3. **Data Integrity:**
   The `Logger` class implements a structured CSV format (`G, Time`) and includes error logging to a separate `error.log` file on the SD card to assist in field-testing diagnostics.

4. **System Class Architecture:**
   A dedicated `System` class owns all peripherals and acts as the single coordination layer between them. Peripherals have no knowledge of each other — the `System` class is the only component with visibility across all hardware, making it the natural home for fault detection and error routing.

5. **Layered Error Indication:**
   Errors are reported through multiple channels simultaneously depending on which components are still functional. The LCD backlight turns red and displays the error message if the display is available. Errors are written to `error.log` if the SD card is available. Debug builds mirror all errors to Serial. This ensures no error is ever silently dropped regardless of which component failed.

---

## Code Structure
- `src/main.cpp` — Entry point. Handles hardware `init()` and the 50Hz throttled loop.
- `src/System.cpp` — High-level orchestrator that owns all peripherals, manages initialization order, and routes faults to available output channels.
- `src/Adxl345.cpp` — Wrapper for the Adafruit Unified Sensor library; configures the ±8g range and 50Hz data rate.
- `src/Logger.cpp` — Manages SD card initialization, CSV file writing, and error persistence to a separate `error.log`.
- `src/Display.cpp` — Handles real-time G-force output, RGB backlight state, and error messaging on the LCD.
- `src/math_utils.h` — Contains the fixed-point conversion logic.
- `src/debug.h` — Compile-time debug macro. `DEBUG_PRINT` expands to `Serial.println` in debug builds and nothing in release builds.

---

## Build Instructions
The project uses **CMake** with an AVR-specific toolchain to generate the production `.hex` file. A development container was made with all build dependencies pre-installed.

### Building
Inside the dev container:

Standard release build:
```bash
./build.sh
```

Debug build — enables Serial output at **9600 baud**:
```bash
./build.sh debug
```

This will generate `wearable-accelerometer.hex` in the `build/` directory, ready for flashing to the ATmega328P.

---

## Flashing

This script must run on your host machine, not within the dev container. You must have `avrdude` installed.

To flash:
```bash
./flash.sh <serial port>
```
where `<serial port>` is the USB serial port assigned to the board.

---

## Usage
1. **Startup:** Upon power-up, the system performs a self-test of the LCD, sensor, and SD card. If all components initialize successfully the LCD backlight turns green briefly before switching to white, signaling that the system is operational.
2. **Logging:** Once initialized, the system begins logging Z-axis G-force readings to `log.csv` at 50Hz.
3. **Debug Mode:** When compiled with `./build.sh debug`, initialization steps and errors are mirrored to the Serial Monitor at **9600 baud**.
4. **Error Handling:** If a fault occurs the LCD backlight turns red and the error is displayed on screen if the display is available, and written to `error.log` if the SD card is available.

---

## Failure Modes
| Component | Behavior | Continues? |
| :--- | :--- | :--- |
| SD Card | Logging disabled, error shown on LCD | Yes — live G-force still displayed |
| LCD | No display output, error written to `error.log` | Yes — logging continues |
| Accelerometer | Error displayed, system halts | No — no valid data source |
