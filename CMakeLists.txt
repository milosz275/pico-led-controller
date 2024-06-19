cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
include(pico_extras_import.cmake)

set(PICO_BOARD "pico_w")
set(ENV{'PICO_BOARD'} "pico_w")
set(ENV{'PICO_SDK_FETCH_FROM_GIT'} "ON")
set(ENV{'PICO_EXTRAS_FETCH_FROM_GIT'} "ON")
set(ENV{'PICO_SDK_FETCH_FROM_GIT_PATH'} "./pico-sdk")
set(ENV{'PICO_EXTRAS_FETCH_FROM_GIT_PATH'} "./pico-extras")

set(FAMILY rp2040)
set(BOARD pico_sdk)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(LedController C CXX ASM)
project(PRERELEASE VERSION 0.0.2)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

set(PICO_CXX_ENABLE_EXCEPTIONS 0)

set(PICO_CXX_ENABLE_RTTI 1)

pico_sdk_init()

add_executable(LedController
        led_controller/src/ws2812b.c
        led_controller/src/ntp.c
        led_controller/src/ssi.c
        led_controller/src/led_controller.c
        led_controller/src/blink.c
        led_controller/src/cgi.c
        led_controller/src/hsv.c
        led_controller/src/light_state.c
        led_controller/src/main.c)

pico_set_program_name(LedController "LedController")
pico_set_program_version(LedController "1.0")

pico_enable_stdio_uart(LedController 0)
pico_enable_stdio_usb(LedController 1)

target_link_libraries(LedController
        pico_stdlib
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_http
        pico_multicore
        hardware_adc
        hardware_pio)

target_include_directories(LedController PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/led_controller/src
        ${CMAKE_CURRENT_LIST_DIR}/led_controller/include
)

pico_add_extra_outputs(LedController)

add_compile_options(-O2 -g3 -march=armv6-m -mcpu=cortex-m0plus -mthumb
        -Wall
        -Wno-unused-result
        -Wno-format
        -Wno-unused-function
        -Wno-maybe-uninitialized
        -Werror)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

add_subdirectory(led_controller/src)
