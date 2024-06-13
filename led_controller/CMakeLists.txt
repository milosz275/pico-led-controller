cmake_minimum_required(VERSION 3.10)
project(led_controller VERSION 0)
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")

add_executable(led_controller)
        
file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(led_controller ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_sources(led_controller
        PRIVATE
        led_controller.c)

target_link_libraries(led_controller
        PRIVATE
        pico_stdlib
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_http
        hardware_adc
        hardware_pio)

target_include_directories(led_controller PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts
)

pico_add_extra_outputs(led_controller)

# add url via pico_set_program_url
example_auto_set_url(led_controller)
