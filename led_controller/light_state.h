#ifndef _LIGHT_STATE_H
#define _LIGHT_STATE_H

bool light_state = true;

void toggle_light_state()
{
    light_state = !light_state;
}

#endif
