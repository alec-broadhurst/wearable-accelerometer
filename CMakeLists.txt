cmake_minimum_required(VERSION 3.21)

project(wearable-accelerometer LANGUAGES C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_subdirectory(lib)

add_library(avr_config INTERFACE)
target_compile_options(avr_config INTERFACE -mmcu=atmega328p -Os)
target_link_options(avr_config INTERFACE -mmcu=atmega328p)

add_executable(${PROJECT_NAME})

if(DEBUG_BUILD)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    src/Adxl345.cpp
    src/Logger.cpp
    src/Display.cpp
    src/System.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    avr_config
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
