#ifndef _URGB_H
#define _URGB_H

#include <stdio.h>

#define URGB(r, g, b) ((uint32_t) (r) << 8) | ((uint32_t) (g) << 16) | (uint32_t) (b)

#endif
