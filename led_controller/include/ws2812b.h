#ifndef _WS2812B_H
#define _WS2812B_H

#include <stdio.h>

static inline void put_pixel(uint32_t pixel_grb);

void set_all_leds(uint32_t color, uint len);

void turn_off_all(uint len);

void set_all_red(uint len, uint8_t brightness);

void set_all_green(uint len, uint8_t brightness);

void set_all_blue(uint len, uint8_t brightness);

void set_all_white(uint len, uint8_t brightness);

void set_rainbow_spectrum(uint len);

void set_all_purple(uint len, uint8_t brightness);

void set_all_yellow(uint len, uint8_t brightness);

void set_all_cyan(uint len, uint8_t brightness);

void set_all_orange(uint len, uint8_t brightness);

void set_all_pink(uint len, uint8_t brightness);

void set_all_turquoise(uint len, uint8_t brightness);

void set_all_magenta(uint len, uint8_t brightness);

void apply_rainbow_wheel_effect(uint len, uint16_t* base_hue, uint8_t* speed_factor, uint8_t* density_factor);

void apply_rainbow_cycle_effect(uint len, uint16_t* hue, uint8_t* speed_factor);

#endif
