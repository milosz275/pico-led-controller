#ifndef _LIGHT_STATE_H
#define _LIGHT_STATE_H

#define NUM_PIXELS 120
#define NUM_LIGHT_MODES 8
#define NUM_LIGHT_COLORS 11

#include <stdio.h>
#include <pico/stdlib.h>

#include "urgb.h"
#include "ws2812b.h"

/**
 * Light modes enum. Enum for the light modes.
 */
enum light_modes
{
    MODE_RAINBOW_WHEEL,
    MODE_RAINBOW_CYCLE,
    MODE_STATIC,
    MODE_BREATHING,
    MODE_FLASHING,
    MODE_LOADING,
    MODE_WAVE,
    MODE_FADE
};

/**
 * Light colors enum. Enum for the light colors.
 */
enum light_colors
{
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_CYAN,
    COLOR_YELLOW,
    COLOR_MAGENTA,
    COLOR_PURPLE,
    COLOR_ORANGE,
    COLOR_TURQUOISE,
    COLOR_PINK,
    COLOR_WHITE
};

/**
 * Light state struct. Struct for the light state.
 * 
 * @param state: state
 * @param brightness: brightness
 * @param previous_brightness: last set brightness
 * @param light_mode: light mode
 * @param color: color
 */
struct light_state_t
{
    bool state;
    uint8_t brightness;
    uint8_t previous_brightness;
    enum light_modes light_mode;
    enum light_colors color;
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
 * Toggle light mode. Function toggles the light mode iterating through the light modes.
 */
void toggle_light_mode();

/**
 * Toggle light color. Function toggles the light color iterating through the light colors.
 */
void toggle_light_color();

/**
 * Set light mode. Function sets the light mode to the specified mode.
 * 
 * @param mode: mode
 */
void set_light_mode(enum light_modes mode);

/**
 * Set light color. Function sets the light mode to the specified color.
 * 
 * @param color: color
 */
void set_light_color(enum light_colors color);

/**
 * Get current color. Function gets the current color.
 * 
 * @return current color in RGB format
 */
uint32_t get_current_color();

#endif
