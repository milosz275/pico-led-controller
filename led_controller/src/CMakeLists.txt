cmake_minimum_required(VERSION 3.10)
project(led_controller VERSION 0)
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")

message("Running makefsdata python script")
execute_process(COMMAND
    py makefsdata.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_executable(led_controller)
        
file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)

pico_generate_pio_header(led_controller ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_sources(led_controller
        PRIVATE
        main.c)

target_link_libraries(led_controller
        PRIVATE
        pico_stdlib
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_http
        pico_multicore
        hardware_adc
        hardware_pio)

target_include_directories(led_controller PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../include)

pico_add_extra_outputs(led_controller)
example_auto_set_url(led_controller)
