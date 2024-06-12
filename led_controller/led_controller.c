#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "boards/pico_w.h"
#include "generated/ws2812.pio.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#define WS2812_PIN 2
#define NUM_PIXELS 118
#define IS_RGBW false

const char* WIFI_SSID = "wifi_ssid";
const char* WIFI_PASSWORD = "wifi_password";

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

    cyw43_arch_enable_sta_mode();
    cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK);
    onboard_led_blink(250, 50);
    onboard_led_blink(250, 0);
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

uint32_t hsv_to_rgb(uint16_t h, uint8_t s, uint8_t v)
{
    float hf = h / 60.0f;
    float sf = s / 255.0f;
    float vf = v / 255.0f;

    int i = (int)hf % 6;
    float f = hf - (int)hf;
    uint8_t p = (uint8_t)(vf * (1.0f - sf) * 255);
    uint8_t q = (uint8_t)(vf * (1.0f - sf * f) * 255);
    uint8_t t = (uint8_t)(vf * (1.0f - sf * (1.0f - f)) * 255);
    uint8_t vi = (uint8_t)(vf * 255);

    uint8_t r, g, b;
    switch (i) {
        case 0:
            r = vi;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = vi;
            b = p;
            break;
        case 2:
            r = p;
            g = vi;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = vi;
            break;
        case 4:
            r = t;
            g = p;
            b = vi;
            break;
        case 5:
            r = vi;
            g = p;
            b = q;
            break;
    }
    return ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
}

void apply_rainbow_effect(int *base_hue, int *speed_factor, int *density_factor, int *brightness)
{
    for (int i = 0; i < NUM_PIXELS; ++i)
        {
            int hue = (*base_hue + i * 360 / NUM_PIXELS * *density_factor) % 360;
            uint32_t color = hsv_to_rgb(hue * *brightness / 100, 255 * *brightness / 100, 255* *brightness / 100);
            put_pixel(color);
            hue++;
        }
        *speed_factor = rand() % 3 + 5;
        *base_hue += *speed_factor;
        *base_hue %= 360;
}

int main()
{
    if (!init())
        return -1;
    printf("WS2812 LED Control, using pin %d\n", WS2812_PIN);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    puts("Beginning main loop");
    int base_hue = 0;
    int speed_factor = 5;
    int density_factor = 2;
    int brightness = 100;
    while (true)
    {
        onboard_led_blink(50, 0);
        apply_rainbow_effect(&base_hue, &speed_factor, &density_factor, &brightness);
    }
}
