#ifndef _BLINK_H
#define _BLINK_H

#include <stdio.h>

#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>

#include "light_state.h"

void onboard_led_blink(int on_time, int off_time)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(on_time);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(off_time);
}

void led_blink(int on_time, int off_time)
{
    toggle_light_state();
    sleep_ms(on_time);
    toggle_light_state();
    sleep_ms(off_time);
}

#endif
