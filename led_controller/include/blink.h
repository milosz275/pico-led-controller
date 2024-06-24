#ifndef _BLINK_H
#define _BLINK_H

#include <stdint.h>
#include "light_state.h"

/**
 * Blink the onboard LED. Function blinks the onboard LED with the given on and off times blocking current thread with sleep.
 * 
 * @param on_time: time in milliseconds the LED is on
 * @param off_time: time in milliseconds the LED is off
 */
void onboard_led_blink(uint32_t on_time, uint32_t off_time);

/**
 * Blink the LED strip. Function blinks the LED strip with the given on and off times blocking current thread with sleep.
 * 
 * @param on_time: time in milliseconds the LED is on
 * @param off_time: time in milliseconds the LED is off
 */
void led_blink(uint32_t on_time, uint32_t off_time);

#endif
