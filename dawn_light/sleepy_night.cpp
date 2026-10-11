#include "light.hpp"

void manual_mode(int pin, t_info *info)
{
    analogWrite(pin, info->brightness);
}

void sleepy_night(int pin, t_info *info)
{
    if (info->manual_mode)
    {
        manual_mode(pin, info);
        return;
    }

    int bright = 50 -  (info->currentMinutes - rstartMinutes);

  if (bright <= 10)
     bright = 10; 
   analogWrite(pin, bright);
}

