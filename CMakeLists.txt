cmake_minimum_required(VERSION 3.25)
set(PROGRAM_NAME LedController)

set(PICO_BOARD "pico_w")
include(cmake/utils.cmake)

include(lib/pico-sdk/pico_sdk_init.cmake)
include(lib/pico-extras/pico_sdk_import.cmake)

project(${PROGRAM_NAME} C CXX ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(
        -Wall
        -Werror
        -Wno-unused-function
)

pico_sdk_init()

add_subdirectory(led_controller/src)
