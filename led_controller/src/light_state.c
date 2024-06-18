#include "light_state.h"

#include <stdint.h>

#include "urgb.h"
#include "ws2812b.h"

volatile struct light_state_t light_state = {true, 255, MODE_RAINBOW_WHEEL};

void toggle_light_state()
{
    light_state.state = !light_state.state;
    if (!light_state.state || light_state.brightness == 0)
        turn_off_all(NUM_PIXELS);
    else
        set_lighting_mode(light_state.lighting_mode);
}

void toggle_light_mode()
{
    light_state.lighting_mode = (light_state.lighting_mode + 1) % NUM_LIGHTING_MODES;
    set_lighting_mode(light_state.lighting_mode);
}

void set_lighting_mode(enum lighting_modes mode)
{
    light_state.lighting_mode = mode;
    if (!light_state.state || light_state.brightness == 0)
        return;
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
