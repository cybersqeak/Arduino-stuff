#include "watch.h"
// there has to be three modes such as time , humidity and temperature mode.

// if (set_mode_pin)
// set_mode(&current_mode); 

void  set_mode(int *current_mode)
{
    if (*current_mode == TIME)
        *current_mode = HUMIDITY;
    else if(*current_mode == HUMIDITY)
        *current_mode = TEMPERATURE;
    else if (*current_mode == TEMPERATURE)
        *current_mode = TIME;
}

