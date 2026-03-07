set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_ASM_COMPILER avr-gcc)

set(CMAKE_OBJCOPY avr-objcopy)
set(CMAKE_OBJDUMP avr-objdump)
set(CMAKE_SIZE avr-size)

set(CMAKE_CXX_STANDARD 17)

set(AVR_MCU atmega328p)
set(CMAKE_C_FLAGS "-mmcu=${AVR_MCU} -Os")
set(CMAKE_CXX_FLAGS "-mmcu=${AVR_MCU} -Os")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${AVR_MCU}")
