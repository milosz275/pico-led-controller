#include "ws2812b.h"

#include <stdlib.h>

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

void set_all_white(uint len, uint8_t brightness)
{
    uint32_t white = urgb_u32(brightness, brightness, brightness);
    set_all_leds(white, len);
}

void set_rainbow_spectrum(uint len)
{
    for (uint i = 0; i < len; ++i)
    {
        uint32_t color = hsv_to_rgb(i * 360 / len, 255, 255);
        put_pixel(color);
    }
}

void set_all_purple(uint len, uint8_t brightness)
{
    uint32_t purple = urgb_u32(brightness * 3 / 4, 0, brightness);
    set_all_leds(purple, len);
}

void set_all_yellow(uint len, uint8_t brightness)
{
    uint32_t yellow = urgb_u32(brightness, brightness, 0);
    set_all_leds(yellow, len);
}

void set_all_cyan(uint len, uint8_t brightness)
{
    uint32_t cyan = urgb_u32(0, brightness, brightness);
    set_all_leds(cyan, len);
}

void set_all_orange(uint len, uint8_t brightness)
{
    uint32_t orange = urgb_u32(brightness, brightness / 3, 0);
    set_all_leds(orange, len);
}

void set_all_pink(uint len, uint8_t brightness)
{
    uint32_t pink = urgb_u32(brightness, brightness / 3, brightness / 3);
    set_all_leds(pink, len);
}

void set_all_turquoise(uint len, uint8_t brightness)
{
    uint32_t turquoise = urgb_u32(brightness / 3, brightness * 2 / 3, brightness);
    set_all_leds(turquoise, len);
}

void set_all_magenta(uint len, uint8_t brightness)
{
    uint32_t magenta = urgb_u32(brightness, 0, brightness);
    set_all_leds(magenta, len);
}

void apply_rainbow_wheel_effect(uint len, uint16_t* base_hue, uint8_t* speed_factor, uint8_t* density_factor)
{
    for (uint i = 0; i < len; ++i)
    {
        uint16_t hue = (*base_hue + i * 360 / len * *density_factor) % 360;
        uint32_t color = hsv_to_rgb(hue, 255, 255);
        put_pixel(color);
        hue++;
    }
    *speed_factor = rand() % 3 + 6; // 6, 7, 8
    *base_hue += *speed_factor;
    *base_hue %= 360;
}

void apply_rainbow_cycle_effect(uint len, uint16_t* hue, uint8_t* speed_factor)
{
    for (uint i = 0; i < len; ++i)
    {
        uint32_t color = hsv_to_rgb(*hue, 255, 255);
        put_pixel(color);
    }
    *hue += *speed_factor;
}
