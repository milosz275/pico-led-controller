cmake_minimum_required(VERSION 3.12)

# Define the project
project(LedController C CXX ASM)

# Define the target board
set(PICO_BOARD "pico_w")
set(PICO_SDK_PATH "pico-sdk")
set(PICO_EXTRAS_PATH "pico-extras")

# Include the Pico SDK initialization
include(pico-sdk/pico_sdk_init.cmake)

# Initialize the SDK
pico_sdk_init()

# Add your executable
add_executable(LedController
        led_controller/src/ws2812b.c
        led_controller/src/ssi.c
        led_controller/src/led_controller.c
        led_controller/src/blink.c
        led_controller/src/cgi.c
        led_controller/src/hsv.c
        led_controller/src/light_state.c
        led_controller/src/main.c
)

# Link libraries
target_link_libraries(LedController
        pico_stdlib
        pico_time
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_arch
        pico_multicore
        hardware_adc
        hardware_pio
)

# Set include directories
target_include_directories(LedController PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/led_controller/src
        ${CMAKE_CURRENT_LIST_DIR}/led_controller/include
)

# Additional configuration
pico_add_extra_outputs(LedController)
