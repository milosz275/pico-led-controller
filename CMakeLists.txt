cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "/home/mlsh/projects/pico/pico-sdk")

include(pico_sdk_import.cmake)

include(pico_extras_import_optional.cmake)

project(LedController C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

set(PICO_CXX_ENABLE_RTTI 1)

pico_sdk_init()

add_executable(LedController led_controller/led_controller.cpp)

pico_set_program_name(LedController "LedController")
pico_set_program_version(LedController "0.1")

pico_enable_stdio_uart(LedController 1)
pico_enable_stdio_usb(LedController 1)

# Add the standard library to the build
target_link_libraries(LedController pico_stdlib pico_cyw43_arch_none PicoLed)

pico_add_extra_outputs(LedController)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

# Hardware-specific examples in subdirectories:
add_subdirectory(led_controller)
