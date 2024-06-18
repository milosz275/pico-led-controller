cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "${PICO_SDK_PATH}")

include(pico_sdk_import.cmake)

include(pico_extras_import_optional.cmake)

project(LedController C CXX ASM)
project(PRERELEASE VERSION 0.0.2)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

set(PICO_CXX_ENABLE_EXCEPTIONS 0)

set(PICO_CXX_ENABLE_RTTI 1)

pico_sdk_init()

add_executable(LedController
        # led_controller/src/led_controller.c
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

add_compile_options(-Wall
        -Wno-format
        -Wno-unused-function)
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()
include(example_auto_set_url.cmake)
add_subdirectory(led_controller/src)
