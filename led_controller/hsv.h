#ifndef _HSV_H
#define _HSV_H

#include <stdint.h>
#include "urgb.h"

uint32_t hsv_to_rgb(uint16_t h, uint8_t s, uint8_t v)
{
    float hf = h / 60.0f;
    float sf = s / 255.0f;
    float vf = v / 255.0f;

    int i = (int)hf % 6;
    float f = hf - (int)hf;
    uint8_t p = (uint8_t)(vf * (1.0f - sf) * 255);
    uint8_t q = (uint8_t)(vf * (1.0f - sf * f) * 255);
    uint8_t t = (uint8_t)(vf * (1.0f - sf * (1.0f - f)) * 255);
    uint8_t vi = (uint8_t)(vf * 255);

    uint8_t r, g, b;
    switch (i) {
        case 0:
            r = vi;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = vi;
            b = p;
            break;
        case 2:
            r = p;
            g = vi;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = vi;
            break;
        case 4:
            r = t;
            g = p;
            b = vi;
            break;
        case 5:
            r = vi;
            g = p;
            b = q;
            break;
    }
    return urgb_u32(r, g, b);
}

#endif
