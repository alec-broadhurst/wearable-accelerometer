# lib/CMakeLists.txt

set(ARDUINO_CORE_DIR ArduinoCore-avr/cores/arduino)
set(ARDUINO_VARIANTS_DIR ArduinoCore-avr/variants/standard)
set(ARDUINO_LIB_DIR ArduinoCore-avr/libraries)
set(BUSIO_DIR Adafruit_BusIO)
set(ADXL345_DIR Adafruit_ADXL345)
set(SENSOR_DIR Adafruit_Sensor)

set(ARDUINO_CORE_SRCS
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

set(BUSIO_SRCS
    ${BUSIO_DIR}/Adafruit_I2CDevice.cpp
    ${BUSIO_DIR}/Adafruit_SPIDevice.cpp
)

set(ADXL345_SRCS
    ${ADXL345_DIR}/Adafruit_ADXL345_U.cpp
)

set(SENSOR_SRCS
    ${SENSOR_DIR}/Adafruit_Sensor.cpp
)

add_library(ArduinoCore STATIC ${ARDUINO_CORE_SRCS})
target_include_directories(ArduinoCore PUBLIC
    ${ARDUINO_CORE_DIR}
    ${ARDUINO_VARIANTS_DIR}
    ${ARDUINO_LIB_DIR}/Wire/src
    ${ARDUINO_LIB_DIR}/SPI/src
    ${ARDUINO_LIB_DIR}/Wire/src/utility/
)

target_compile_definitions(ArduinoCore PUBLIC
    F_CPU=16000000UL
    ARDUINO=10819
)

add_library(Adafruit_BusIO STATIC ${BUSIO_SRCS})
target_include_directories(Adafruit_BusIO PUBLIC ${BUSIO_DIR})
target_link_libraries(Adafruit_BusIO PUBLIC ArduinoCore)

add_library(Adafruit_Sensor STATIC ${SENSOR_SRCS})
target_include_directories(Adafruit_Sensor PUBLIC ${SENSOR_DIR})
target_link_libraries(Adafruit_Sensor PUBLIC ArduinoCore)

add_library(Adafruit_ADXL345 STATIC ${ADXL345_SRCS})
target_include_directories(Adafruit_ADXL345 PUBLIC ${ADXL345_DIR})
target_link_libraries(Adafruit_ADXL345 PUBLIC ArduinoCore Adafruit_BusIO Adafruit_Sensor)
