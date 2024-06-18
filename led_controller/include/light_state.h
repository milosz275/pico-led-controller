#ifndef _LIGHT_STATE_H
#define _LIGHT_STATE_H

#define NUM_PIXELS 120
#define NUM_LIGHTING_MODES 13

#include <stdio.h>
#include <pico/stdlib.h>

#include "urgb.h"
#include "ws2812b.h"

enum lighting_modes
{
    MODE_RAINBOW_WHEEL,
    MODE_RAINBOW_CYCLE,
    MODE_RED,
    MODE_GREEN,
    MODE_BLUE,
    MODE_CYAN,
    MODE_YELLOW,
    MODE_MAGENTA,
    MODE_PURPLE,
    MODE_ORANGE,
    MODE_TURQUOISE,
    MODE_PINK,
    MODE_WHITE,
};

struct light_state_t
{
    bool state;
    uint8_t brightness;
    enum lighting_modes lighting_mode;
};

extern volatile struct light_state_t light_state;

void toggle_light_state();
void toggle_light_mode();
void set_lighting_mode(enum lighting_modes mode);

#endif
