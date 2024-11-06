add_executable(${PROGRAM_NAME}
        ws2812b.c
        ntp.c
        ssi.c
        led_controller.c
        blink.c
        cgi.c
        hsv.c
        light_state.c
        main.c
)

message("Running makefsdata python script")
execute_process(COMMAND
        py makefsdata.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)
pico_generate_pio_header(${PROGRAM_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_link_libraries(${PROGRAM_NAME}
        pico_stdlib
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_http
        pico_multicore
        hardware_adc
        hardware_pio
)

target_include_directories(${PROGRAM_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../include
)

suppress_pico_sdk_warnings()
pico_enable_stdio_usb(${PROGRAM_NAME} 1)
pico_enable_stdio_uart(${PROGRAM_NAME} 0)
pico_add_extra_outputs(${PROGRAM_NAME})
