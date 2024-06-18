#ifndef _BLINK_H
#define _BLINK_H

#include <stdint.h>
#include "light_state.h"

void onboard_led_blink(uint32_t on_time, uint32_t off_time);
void led_blink(uint32_t on_time, uint32_t off_time);

#endif
