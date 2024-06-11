cmake_minimum_required(VERSION 3.10)
project(led_controller)

add_executable(led_controller)

add_custom_command(
        TARGET led_controller PRE_BUILD
        COMMAND /usr/bin/env WIFI_SSID="$ENV{WIFI_SSID}" WIFI_PASSWORD="$ENV{WIFI_PASSWORD}" /bin/bash ${CMAKE_CURRENT_LIST_DIR}/pre_build_script.sh
        COMMENT "Running pre-build script with WIFI_SSID and WIFI_PASSWORD")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(led_controller ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_sources(led_controller
        PRIVATE
        led_controller.c)

target_link_libraries(led_controller
        PRIVATE
        pico_stdlib
        pico_cyw43_arch_none
        hardware_pio)

pico_add_extra_outputs(led_controller)

# add url via pico_set_program_url
example_auto_set_url(led_controller)

# Additionally generate python and hex pioasm outputs for inclusion in the RP2040 datasheet
add_custom_target(led_controller_datasheet DEPENDS ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py)

add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
        COMMAND Pioasm -o python ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
        VERBATIM)

add_dependencies(led_controller
        led_controller_datasheet)

add_custom_command(
        TARGET led_controller POST_BUILD
        COMMAND /bin/bash ${CMAKE_CURRENT_LIST_DIR}/post_build_script.sh
        COMMENT "Running post-build script")
