cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_ASM_COMPILER avr-gcc)
set(CMAKE_SYSTEM_NAME Generic)

project(wearable-accelerometer CXX C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(MCU atmega328p)

set(CMAKE_C_FLAGS   "-mmcu=${MCU} -Os -Wall")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -Os -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

add_subdirectory(lib)

set(PROJECT_SRCS
    src/main.cpp
    src/Adxl345.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE
    src/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ArduinoCore
    Adafruit_BusIO
    Adafruit_Sensor
    Adafruit_ADXL345
    Adafruit_LiquidCrystal
    SD
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom
        $<TARGET_FILE:${PROJECT_NAME}>
        ${PROJECT_NAME}.hex
    COMMENT "Generating ${PROJECT_NAME}.hex"
)
