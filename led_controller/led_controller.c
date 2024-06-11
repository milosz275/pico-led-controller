#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "generated/ws2812.pio.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pico/cyw43_arch.h"
#include "boards/pico_w.h"

#define WS2812_PIN 2
#define NUM_PIXELS 118
#define IS_RGBW false

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return
        ((uint32_t) (r) << 8) |
        ((uint32_t) (g) << 16) |
        (uint32_t) (b);
}

void onboard_led_blink(int on_time, int off_time)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(on_time);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(off_time);
}

bool init()
{
    stdio_init_all();
    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed");
        return false;
    }
    onboard_led_blink(250, 250);
    return true;
}

void set_all_leds(uint32_t color, uint len)
{
    for (uint i = 0; i < len; ++i)
    {
        put_pixel(color);
    }
}

void turn_off_all(uint len)
{
    uint32_t off = urgb_u32(0, 0, 0);
    set_all_leds(off, len);
}

void set_all_red(uint len, uint8_t brightness)
{
    uint32_t red = urgb_u32(brightness, 0, 0);
    set_all_leds(red, len);
}

void set_all_green(uint len, uint8_t brightness)
{
    uint32_t green = urgb_u32(0, brightness, 0);
    set_all_leds(green, len);
}

void set_all_blue(uint len, uint8_t brightness)
{
    uint32_t blue = urgb_u32(0, 0, brightness);
    set_all_leds(blue, len);
}

int main()
{
    if (!init())
    {
        return -1;
    }
    printf("WS2812 LED Control, using pin %d\n", WS2812_PIN);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    while (true)
    {
        onboard_led_blink(50, 0);

        puts("Turning on all LEDs white");
        set_all_leds(0xffffffff, NUM_PIXELS);
        sleep_ms(1000);

        puts("Turning on all LEDs red");
        set_all_red(NUM_PIXELS, 255);
        sleep_ms(1000);

        puts("Turning on all LEDs green");
        set_all_green(NUM_PIXELS, 255);
        sleep_ms(1000);

        puts("Turning on all LEDs blue");
        set_all_blue(NUM_PIXELS, 255);
        sleep_ms(1000);

        puts("Turning off all LEDs");
        turn_off_all(NUM_PIXELS);
        sleep_ms(1000);
    }
}