add_executable(led_controller
        led_controller.cpp
        )

target_link_libraries(led_controller
        pico_stdlib
        pico_cyw43_arch_none
        PicoLed
        )

pico_add_extra_outputs(led_controller)
