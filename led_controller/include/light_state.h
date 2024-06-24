#ifndef _LIGHT_STATE_H
#define _LIGHT_STATE_H

#define NUM_PIXELS 120
#define NUM_LIGHTING_MODES 13

#include <stdio.h>
#include <pico/stdlib.h>

#include "urgb.h"
#include "ws2812b.h"

/**
 * Lighting modes enum. Enum for the lighting modes.
 */
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

/**
 * Light state struct. Struct for the light state.
 */
struct light_state_t
{
    bool state;
    uint8_t brightness;
    enum lighting_modes lighting_mode;
};

/**
 * Light state. External, not optimized variable for the light state.
 */
extern volatile struct light_state_t light_state;

/**
 * Toggle light state. Function toggles on/off the light state.
 */
void toggle_light_state();

/**
 * Toggle light mode. Function toggles the light mode iterating through the lighting modes.
 */
void toggle_light_mode();

/**
 * Set light mode. Function sets the light mode to the specified mode.
 * 
 * @param mode: mode
 */
void set_lighting_mode(enum lighting_modes mode);

#endif
