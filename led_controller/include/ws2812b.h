#ifndef _WS2812B_H
#define _WS2812B_H

#include <stdio.h>
#include <stdbool.h>

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
 * Get red color.
 * 
 * @param brightness: brightness
 * @return red color in RGB format
 */
uint32_t get_red(uint8_t brightness);

/**
 * Get green color.
 * 
 * @param brightness: brightness
 * @return green color in RGB format
 */
uint32_t get_green(uint8_t brightness);

/**
 * Get blue color.
 * 
 * @param brightness: brightness
 * @return blue color in RGB format
 */
uint32_t get_blue(uint8_t brightness);

/**
 * Get white color.
 * 
 * @param brightness: brightness
 * @return white color in RGB format
 */
uint32_t get_white(uint8_t brightness);

/**
 * Get purple color.
 * 
 * @param brightness: brightness
 * @return purple color in RGB format
 */
uint32_t get_purple(uint8_t brightness);

/**
 * Get yellow color.
 * 
 * @param brightness: brightness
 * @return yellow color in RGB format
 */
uint32_t get_yellow(uint8_t brightness);

/**
 * Get cyan color.
 * 
 * @param brightness: brightness
 * @return cyan color in RGB format
 */
uint32_t get_cyan(uint8_t brightness);

/**
 * Get orange color.
 * 
 * @param brightness: brightness
 * @return orange color in RGB format
 */
uint32_t get_orange(uint8_t brightness);

/**
 * Get pink color.
 * 
 * @param brightness: brightness
 * @return pink color in RGB format
 */
uint32_t get_pink(uint8_t brightness);

/**
 * Get turquoise color.
 * 
 * @param brightness: brightness
 * @return turquoise color in RGB format
 */
uint32_t get_turquoise(uint8_t brightness);

/**
 * Get magenta color.
 * 
 * @param brightness: brightness
 * @return magenta color in RGB format
 */
uint32_t get_magenta(uint8_t brightness);

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
 * @param brightness: brightness
 */
void apply_rainbow_wheel_effect(uint len, uint16_t* base_hue, uint8_t* speed_factor, uint8_t* density_factor, volatile uint8_t* brightness);

/**
 * Apply rainbow cycle effect.
 * 
 * @param len: number of leds
 * @param hue: hue
 * @param speed_factor: speed factor
 * @param brightness: brightness
 */
void apply_rainbow_cycle_effect(uint len, uint16_t* hue, uint8_t* speed_factor, volatile uint8_t* brightness);

/**
 * Apply breathing effect.
 * 
 * @param len: number of leds
 * @param speed_factor: speed factor
 * @param color: color
 * @param base_brightness: base brightness
 * @param brightness: brightness
 * @param breathing_up: breathing up
 */
void apply_breathing_effect(uint len, uint8_t* speed_factor, uint32_t* color, volatile uint8_t* base_brightness, uint8_t* brightness, bool* breathing_up);

/**
 * Apply flashing effect.
 * 
 * @param len: number of leds
 * @param led_values: led values
 * @param color: color
 */
void apply_flashing_effect(uint len, uint32_t* color);

#endif
