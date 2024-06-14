#ifndef _LIGHT_STATE_H
#define _LIGHT_STATE_H

#define NUM_PIXELS 120
#define NUM_LIGHTING_MODES 13

#include <stdint.h>

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

void set_lighting_mode(enum lighting_modes mode);
volatile static struct light_state_t
{
    bool state;
    uint8_t brightness;
    enum lighting_modes lighting_mode;
} light_state = {true, 255, MODE_RAINBOW_WHEEL};

void toggle_light_state()
{
    light_state.state = !light_state.state;
    if (!light_state.state || light_state.brightness == 0)
        turn_off_all(NUM_PIXELS);
    else
        set_lighting_mode(light_state.lighting_mode);
}

void set_lighting_mode(enum lighting_modes mode)
{
    light_state.lighting_mode = mode;
    switch (mode)
    {
    case MODE_RAINBOW_WHEEL:
        break;
    case MODE_RAINBOW_CYCLE:
        break;
    case MODE_RED:
        set_all_red(NUM_PIXELS, light_state.brightness);
        break;
    case MODE_GREEN:
        set_all_green(NUM_PIXELS, light_state.brightness);
        break;
    case MODE_BLUE:
        set_all_blue(NUM_PIXELS, light_state.brightness);
        break;
    case MODE_WHITE:
        set_all_white(NUM_PIXELS, light_state.brightness);
        break;
    case MODE_PURPLE:
        set_all_purple(NUM_PIXELS, light_state.brightness);
        break;
    case MODE_YELLOW:
        set_all_yellow(NUM_PIXELS, light_state.brightness);
        break;
    case MODE_CYAN:
        set_all_cyan(NUM_PIXELS, light_state.brightness);
        break;
    case MODE_ORANGE:
        set_all_orange(NUM_PIXELS, light_state.brightness);
        break;
    case MODE_PINK:
        set_all_pink(NUM_PIXELS, light_state.brightness);
        break;
    case MODE_TURQUOISE:
        set_all_turquoise(NUM_PIXELS, light_state.brightness);
        break;
    case MODE_MAGENTA:
        set_all_magenta(NUM_PIXELS, light_state.brightness);
        break;
    default:
        break;
    }
}

#endif
