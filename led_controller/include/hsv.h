#ifndef _HSV_H
#define _HSV_H

#include <stdint.h>

/**
 * Convert HSV to RGB.
 * 
 * @param h: hue
 * @param s: saturation
 * @param v: value
 * @return: RGB 32-bit color
 */
uint32_t hsv_to_rgb(uint16_t h, uint8_t s, uint8_t v);

#endif
