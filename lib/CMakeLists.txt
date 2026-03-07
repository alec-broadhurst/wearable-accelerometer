# directory variables
set(ARDUINO_CORE_DIR ArduinoCore-avr/cores/arduino)
set(ARDUINO_VARIANT_DIR ArduinoCore-avr/variants/standard)
set(ARDUINO_LIB_DIR ArduinoCore-avr/libraries)

set(BUSIO_DIR Adafruit_BusIO)
set(ADXL345_DIR Adafruit_ADXL345)
set(SENSOR_DIR Adafruit_Sensor)
set(DISPLAY_DIR Adafruit_LiquidCrystal)
set(MCP_DIR Adafruit-MCP23017/src)
set(SD_DIR SD/src)


# Arduino config
add_library(arduino_config INTERFACE)

target_compile_definitions(arduino_config INTERFACE
    F_CPU=16000000UL
    ARDUINO=10819
)


# Arduino core
add_library(ArduinoCore STATIC)

target_sources(ArduinoCore PRIVATE
    ${ARDUINO_CORE_DIR}/wiring.c
    ${ARDUINO_CORE_DIR}/wiring_digital.c
    ${ARDUINO_CORE_DIR}/wiring_analog.c
    ${ARDUINO_CORE_DIR}/hooks.c
    ${ARDUINO_CORE_DIR}/HardwareSerial.cpp
    ${ARDUINO_CORE_DIR}/HardwareSerial0.cpp
    ${ARDUINO_CORE_DIR}/Print.cpp
    ${ARDUINO_CORE_DIR}/Stream.cpp
    ${ARDUINO_CORE_DIR}/abi.cpp
    ${ARDUINO_CORE_DIR}/new.cpp
    ${ARDUINO_LIB_DIR}/Wire/src/Wire.cpp
    ${ARDUINO_LIB_DIR}/Wire/src/utility/twi.c
    ${ARDUINO_LIB_DIR}/SPI/src/SPI.cpp
)

target_include_directories(ArduinoCore PUBLIC
    ${ARDUINO_CORE_DIR}
    ${ARDUINO_VARIANT_DIR}
    ${ARDUINO_LIB_DIR}/Wire/src
    ${ARDUINO_LIB_DIR}/Wire/src/utility
    ${ARDUINO_LIB_DIR}/SPI/src
)

target_link_libraries(ArduinoCore PUBLIC arduino_config)


# BusIO
add_library(Adafruit_BusIO STATIC)

target_sources(Adafruit_BusIO PRIVATE
    ${BUSIO_DIR}/Adafruit_I2CDevice.cpp
    ${BUSIO_DIR}/Adafruit_SPIDevice.cpp
)

target_include_directories(Adafruit_BusIO PUBLIC ${BUSIO_DIR})

target_link_libraries(Adafruit_BusIO PUBLIC ArduinoCore)


# Unified Sensor
add_library(Adafruit_Sensor STATIC)

target_sources(Adafruit_Sensor PRIVATE
    ${SENSOR_DIR}/Adafruit_Sensor.cpp
)

target_include_directories(Adafruit_Sensor PUBLIC ${SENSOR_DIR})

target_link_libraries(Adafruit_Sensor PUBLIC ArduinoCore)


# Accelerometer
add_library(Adafruit_ADXL345 STATIC)

target_sources(Adafruit_ADXL345 PRIVATE
    ${ADXL345_DIR}/Adafruit_ADXL345_U.cpp
)

target_include_directories(Adafruit_ADXL345 PUBLIC ${ADXL345_DIR})

target_link_libraries(Adafruit_ADXL345 PUBLIC
    ArduinoCore
    Adafruit_BusIO
    Adafruit_Sensor
)


# MCP23017
add_library(MCP23017 STATIC)

target_sources(MCP23017 PRIVATE
    ${MCP_DIR}/Adafruit_MCP23X08.cpp
    ${MCP_DIR}/Adafruit_MCP23X17.cpp
    ${MCP_DIR}/Adafruit_MCP23XXX.cpp
)

target_include_directories(MCP23017 PUBLIC ${MCP_DIR})

target_link_libraries(MCP23017 PUBLIC
    ArduinoCore
    Adafruit_BusIO
)


# Display
add_library(Adafruit_LiquidCrystal STATIC)

target_sources(Adafruit_LiquidCrystal PRIVATE
    ${DISPLAY_DIR}/Adafruit_LiquidCrystal.cpp
)

target_include_directories(Adafruit_LiquidCrystal PUBLIC ${DISPLAY_DIR})

target_link_libraries(Adafruit_LiquidCrystal PUBLIC
    ArduinoCore
    MCP23017
)


# SD card
add_library(SD STATIC)

target_sources(SD PRIVATE
    ${SD_DIR}/SD.cpp
    ${SD_DIR}/File.cpp
    ${SD_DIR}/utility/SdFile.cpp
    ${SD_DIR}/utility/Sd2Card.cpp
    ${SD_DIR}/utility/SdVolume.cpp
)

target_include_directories(SD PUBLIC
    ${SD_DIR}
    ${SD_DIR}/utility
    ${ARDUINO_CORE_DIR}
    ${ARDUINO_VARIANT_DIR}
    ${ARDUINO_LIB_DIR}/SPI/src
)

target_link_libraries(SD PUBLIC ArduinoCore)
