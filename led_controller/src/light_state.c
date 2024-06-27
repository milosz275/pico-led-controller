#include "light_state.h"

#include <stdint.h>

#include "urgb.h"
#include "ws2812b.h"

volatile struct light_state_t light_state = {true, 128, MODE_RAINBOW_WHEEL, COLOR_BLUE};

void toggle_light_state()
{
    light_state.state = !light_state.state;
    if (!light_state.state || light_state.brightness == 0)
        turn_off_all(NUM_PIXELS);
    else
        set_light_mode(light_state.light_mode);
}

void toggle_light_mode()
{
    light_state.light_mode = (light_state.light_mode + 1) % NUM_LIGHT_MODES;
    set_light_mode(light_state.light_mode);
}

void toggle_light_color()
{
    light_state.color = (light_state.color + 1) % NUM_LIGHT_COLORS;
    set_light_color(light_state.color);
}

void set_light_mode(enum light_modes mode)
{
    light_state.light_mode = mode;
    if (!light_state.state || light_state.brightness == 0)
        return;
    switch (mode)
    {
    case MODE_RAINBOW_WHEEL:
        printf("Setting rainbow wheel mode\n");
        break;
    case MODE_RAINBOW_CYCLE:
        printf("Setting rainbow cycle mode\n");
        break;
    case MODE_STATIC:
        printf("Setting static mode\n");
        set_light_color(light_state.color);
        break;
    case MODE_BREATHING:
        printf("Setting breathing mode\n");
        break;
    case MODE_FLASHING:
        printf("Setting flashing mode\n");
        break;
    case MODE_LOADING:
        printf("Setting loading mode\n");
        break;
    case MODE_WAVE:
        printf("Setting wave mode\n");
        break;
    case MODE_FADE:
        printf("Setting fade mode\n");
        break;
    default:
        break;
    }
}

void set_light_color(enum light_colors color)
{
    light_state.color = color;
    if (!light_state.state || light_state.brightness == 0)
        return;
    if (light_state.light_mode == MODE_STATIC)
    {
        switch (color)
        {
        case COLOR_RED:
            set_all_red(NUM_PIXELS, light_state.brightness);
            break;
        case COLOR_GREEN:
            set_all_green(NUM_PIXELS, light_state.brightness);
            break;
        case COLOR_BLUE:
            set_all_blue(NUM_PIXELS, light_state.brightness);
            break;
        case COLOR_WHITE:
            set_all_white(NUM_PIXELS, light_state.brightness);
            break;
        case COLOR_PURPLE:
            set_all_purple(NUM_PIXELS, light_state.brightness);
            break;
        case COLOR_YELLOW:
            set_all_yellow(NUM_PIXELS, light_state.brightness);
            break;
        case COLOR_CYAN:
            set_all_cyan(NUM_PIXELS, light_state.brightness);
            break;
        case COLOR_ORANGE:
            set_all_orange(NUM_PIXELS, light_state.brightness);
            break;
        case COLOR_PINK:
            set_all_pink(NUM_PIXELS, light_state.brightness);
            break;
        case COLOR_TURQUOISE:
            set_all_turquoise(NUM_PIXELS, light_state.brightness);
            break;
        case COLOR_MAGENTA:
            set_all_magenta(NUM_PIXELS, light_state.brightness);
            break;
        default:
            break;
        }
    }
}

uint32_t get_current_color()
{
    switch (light_state.color)
    {
    case COLOR_RED:
        return get_red(light_state.brightness);
    case COLOR_GREEN:
        return get_green(light_state.brightness);
    case COLOR_BLUE:
        return get_blue(light_state.brightness);
    case COLOR_WHITE:
        return get_white(light_state.brightness);
    case COLOR_PURPLE:
        return get_purple(light_state.brightness);
    case COLOR_YELLOW:
        return get_yellow(light_state.brightness);
    case COLOR_CYAN:
        return get_cyan(light_state.brightness);
    case COLOR_ORANGE:
        return get_orange(light_state.brightness);
    case COLOR_PINK:
        return get_pink(light_state.brightness);
    case COLOR_TURQUOISE:
        return get_turquoise(light_state.brightness);
    case COLOR_MAGENTA:
        return get_magenta(light_state.brightness);
    default:
        return 0;
    }
}
