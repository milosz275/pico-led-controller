add_executable(rainbow
        rainbow.cpp
        )

target_link_libraries(rainbow
        pico_stdlib
        pico_cyw43_arch_none
        PicoLed
        )

pico_add_extra_outputs(rainbow)
