#ifndef _WS2812B_H
#define _WS2812B_H

#include <stdio.h>

/**
 * Put pixel to the LED strip.
 * 
 * @param pixel_grb: pixel color in GRB format
 */
static inline void put_pixel(uint32_t pixel_grb);

/**
 * Set all leds to the same color.
 * 
 * @param color: color in RGB format
 * @param len: number of leds
 */
void set_all_leds(uint32_t color, uint len);

/**
 * Turn off all leds.
 * 
 * @param len: number of leds
 */
void turn_off_all(uint len);

/**
 * Set all leds to red.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_red(uint len, uint8_t brightness);

/**
 * Set all leds to green.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_green(uint len, uint8_t brightness);

/**
 * Set all leds to blue.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_blue(uint len, uint8_t brightness);

/**
 * Set all leds to white.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_white(uint len, uint8_t brightness);

/**
 * Set all leds to rainbow spectrum.
 * 
 * @param len: number of leds
 */
void set_rainbow_spectrum(uint len);

/**
 * Set all leds purple.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_purple(uint len, uint8_t brightness);

/**
 * Set all leds yellow.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_yellow(uint len, uint8_t brightness);

/**
 * Set all leds cyan.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_cyan(uint len, uint8_t brightness);

/**
 * Set all leds orange.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_orange(uint len, uint8_t brightness);

/**
 * Set all leds pink.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_pink(uint len, uint8_t brightness);

/**
 * Set all leds turquoise.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_turquoise(uint len, uint8_t brightness);

/**
 * Set all leds magenta.
 * 
 * @param len: number of leds
 * @param brightness: brightness
 */
void set_all_magenta(uint len, uint8_t brightness);

/**
 * Apply rainbow wheel effect.
 * 
 * @param len: number of leds
 * @param base_hue: base hue
 * @param speed_factor: speed factor
 * @param density_factor: density factor
 */
void apply_rainbow_wheel_effect(uint len, uint16_t* base_hue, uint8_t* speed_factor, uint8_t* density_factor);

/**
 * Apply rainbow cycle effect.
 * 
 * @param len: number of leds
 * @param hue: hue
 * @param speed_factor: speed factor
 */
void apply_rainbow_cycle_effect(uint len, uint16_t* hue, uint8_t* speed_factor);

#endif
