#ifndef _URGB_H
#define _URGB_H

#include <stdio.h>

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return
        ((uint32_t) (r) << 8) |
        ((uint32_t) (g) << 16) |
        (uint32_t) (b);
}

#endif
