#include "ws2812b.h"

#include <stdlib.h>
#include <time.h>

#include "urgb.h"
#include "hsv.h"
#include "generated/ws2812.pio.h"

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
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
    uint32_t off = URGB(0, 0, 0);
    set_all_leds(off, len);
}


uint32_t get_red(uint8_t brightness)
{
    return URGB(brightness, 0, 0);
}

uint32_t get_green(uint8_t brightness)
{
    return URGB(0, brightness, 0);
}

uint32_t get_blue(uint8_t brightness)
{
    return URGB(0, 0, brightness);
}

uint32_t get_white(uint8_t brightness)
{
    return URGB(brightness, brightness, brightness);
}

uint32_t get_purple(uint8_t brightness)
{
    return URGB(brightness * 3 / 4, 0, brightness);
}

uint32_t get_yellow(uint8_t brightness)
{
    return URGB(brightness, brightness, 0);
}

uint32_t get_cyan(uint8_t brightness)
{
    return URGB(0, brightness, brightness);
}

uint32_t get_orange(uint8_t brightness)
{
    return URGB(brightness, brightness / 3, 0);
}

uint32_t get_pink(uint8_t brightness)
{
    return URGB(brightness, brightness / 3, brightness / 3);
}

uint32_t get_turquoise(uint8_t brightness)
{
    return URGB(brightness / 3, brightness * 2 / 3, brightness);
}

uint32_t get_magenta(uint8_t brightness)
{
    return URGB(brightness, 0, brightness);
}

void set_all_red(uint len, uint8_t brightness)
{
    uint32_t red = URGB(brightness, 0, 0);
    set_all_leds(red, len);
}

void set_all_green(uint len, uint8_t brightness)
{
    uint32_t green = URGB(0, brightness, 0);
    set_all_leds(green, len);
}

void set_all_blue(uint len, uint8_t brightness)
{
    uint32_t blue = URGB(0, 0, brightness);
    set_all_leds(blue, len);
}

void set_all_white(uint len, uint8_t brightness)
{
    uint32_t white = URGB(brightness, brightness, brightness);
    set_all_leds(white, len);
}

void set_all_purple(uint len, uint8_t brightness)
{
    uint32_t purple = URGB(brightness * 3 / 4, 0, brightness);
    set_all_leds(purple, len);
}

void set_all_yellow(uint len, uint8_t brightness)
{
    uint32_t yellow = URGB(brightness, brightness, 0);
    set_all_leds(yellow, len);
}

void set_all_cyan(uint len, uint8_t brightness)
{
    uint32_t cyan = URGB(0, brightness, brightness);
    set_all_leds(cyan, len);
}

void set_all_orange(uint len, uint8_t brightness)
{
    uint32_t orange = URGB(brightness, brightness / 3, 0);
    set_all_leds(orange, len);
}

void set_all_pink(uint len, uint8_t brightness)
{
    uint32_t pink = URGB(brightness, brightness / 3, brightness / 3);
    set_all_leds(pink, len);
}

void set_all_turquoise(uint len, uint8_t brightness)
{
    uint32_t turquoise = URGB(brightness / 3, brightness * 2 / 3, brightness);
    set_all_leds(turquoise, len);
}

void set_all_magenta(uint len, uint8_t brightness)
{
    uint32_t magenta = URGB(brightness, 0, brightness);
    set_all_leds(magenta, len);
}

void set_rainbow_spectrum(uint len)
{
    for (uint i = 0; i < len; ++i)
    {
        uint32_t color = hsv_to_rgb(i * 360 / len, 255, 255);
        put_pixel(color);
    }
}

void apply_rainbow_wheel_effect(uint len, uint16_t* base_hue, uint8_t* speed_factor, uint8_t* density_factor, volatile uint8_t* brightness)
{
    for (uint i = 0; i < len; ++i)
    {
        uint16_t hue = (*base_hue + i * 360 / len * *density_factor) % 360;
        uint32_t color = hsv_to_rgb(hue, 255, *brightness);
        put_pixel(color);
        hue++;
    }
    *speed_factor = rand() % 3 + 6; // 6, 7, 8
    *base_hue += *speed_factor;
    *base_hue %= 360;
}

void apply_rainbow_cycle_effect(uint len, uint16_t* hue, uint8_t* speed_factor, volatile uint8_t* brightness)
{
    for (uint i = 0; i < len; ++i)
    {
        uint32_t color = hsv_to_rgb(*hue, 255, *brightness);
        put_pixel(color);
    }
    *hue += *speed_factor;
}

void apply_breathing_effect(uint len, uint8_t* speed_factor, uint32_t* color, volatile uint8_t* base_brightness, uint8_t* brightness, bool* breathing_up)
{
    uint8_t min_brightness = 15;
    uint8_t max_brightness = *base_brightness;
    if (max_brightness < min_brightness)
        max_brightness = min_brightness;
    for (uint i = 0; i < len; ++i)
    {
        uint8_t r = URGB_R(*color);
        uint8_t g = URGB_G(*color);
        uint8_t b = URGB_B(*color);
        uint32_t color = URGB(r * *brightness / 255, g * *brightness / 255, b * *brightness / 255);
        put_pixel(color);
    }
    if (*brightness >= max_brightness)
    {
        *breathing_up = false;
        *brightness = max_brightness;
    }
    else if (*brightness <= min_brightness)
    {
        *breathing_up = true;
        *brightness = min_brightness;
    }
    if (*breathing_up)
        *brightness += *speed_factor;
    else
        *brightness -= *speed_factor;
}

void apply_flashing_effect(uint len, uint32_t* color)
{
    srand(time(NULL));
    int num_led_flash = 10;
    int *random_indices = (int *)malloc(num_led_flash * sizeof(int));
    for (int i = 0; i < num_led_flash; ++i)
        random_indices[i] = rand() % len;
    int leds_handled = 0;
    while (leds_handled < len)
    {
        int i = 0;
        if (random_indices[i] == leds_handled)
        {
            uint32_t new_color;
            if (!color)
                new_color = URGB(rand() % 256, rand() % 256, rand() % 256);
            else
            {
                uint8_t r = URGB_R(*color);
                uint8_t g = URGB_G(*color);
                uint8_t b = URGB_B(*color);
                new_color = URGB(r, g, b);
            }
            put_pixel(new_color);
            i++;
            if (i >= num_led_flash)
                break;
        }
        else
            put_pixel(0);
        leds_handled++;
    }
}
