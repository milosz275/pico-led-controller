#ifndef _LED_CONTROLLER_H
#define _LED_CONTROLLER_H

#include <stdint.h>
#include <pico/stdlib.h>

#include <pico/cyw43_arch.h>
#include <pico/multicore.h>
#include <boards/pico_w.h>
#include <hardware/pio.h>
#include <hardware/gpio.h>
#include <hardware/clocks.h>

#include "blink_codes.h"

#define WS2812_PIN 2
#define LIGHT_TOGGLE_PIN 15
#define MODE_BUTTON_PIN 16
#define STOP_BUTTON_PIN 17
#define IS_RGBW false

void connect_to_wifi();
void gpio_button_irq_handler(uint gpio, uint32_t events);

enum init_result_t
{
    INIT_SUCCESS,
    STDIO_INIT_FAILURE,
    WIFI_INIT_FAILURE
};

enum init_result_t init();
void shuffle_modes();
void run_loop();

#endif
