#include "light.hpp"


// Gradually raise the morning light!!!

void sun_raise(int pin, t_info *info)
{
    // no manual_mode needed here 
    int bright = (info->currentMinutes - startMinute)*2 + 2; // 2, 4, 6, 8,10...255 
    if (bright >= 255)
        bright = 255;
    analogWrite(pin, bright);
}

