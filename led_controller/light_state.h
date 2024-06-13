#ifndef _LIGHT_STATE_H
#define _LIGHT_STATE_H

#define NUM_PIXELS 118

#include <stdint.h>

volatile bool light_state = true;

void toggle_light_state()
{
    light_state = !light_state;
    if (!light_state)
        turn_off_all(NUM_PIXELS);
}

// extern struct light_state_t
// {
//     bool state;
//     uint8_t brightness;
//     uint8_t lighting_mode;
// } light_state;

#endif
