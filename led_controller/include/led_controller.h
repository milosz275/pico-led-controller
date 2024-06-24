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
#include <hardware/timer.h>

#include "blink_codes.h"
#include "ntp.h"

#define WS2812_PIN          2
#define LIGHT_TOGGLE_PIN    15
#define MODE_BUTTON_PIN     16
#define STOP_BUTTON_PIN     17
#define IS_RGBW             false
#define DEBOUNCE_TIME_US    250000 // 250ms

/**
 * Connect to WiFi. Function connects to WiFi using the SSID and password defined in the wifi_credentials.h file. 
 */
void connect_to_wifi();

/**
 * GPIO button interrupt handler. Function handles button interrupts setting proper flags.
 */
void gpio_button_irq_handler(uint gpio, uint32_t events);

/**
 * Init result enum. Enum for the initialization result.
 */
enum init_result_t
{
    INIT_SUCCESS,
    STDIO_INIT_FAILURE,
    WIFI_INIT_FAILURE
};

/**
 * Init. Function initializes the LED controller.
 * 
 * @return: initialization result
 */
enum init_result_t init();

/**
 * Shuffle modes. Function shuffles the LED modes.
 */
void shuffle_modes();

/**
 * Run loop. Function runs the main loop of the LED controller.
 */
void run_loop();

#endif
