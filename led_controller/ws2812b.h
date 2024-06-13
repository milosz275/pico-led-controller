#include <stdint.h>
#include "urgb.h"
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
