#include "system.h"

void check_light(t_sys *sys)
{
    if (sys->c_hour >= 20 || (sys->c_hour < 5 && sys->c_min == 30))
        sys->dis.dis_light = 0; 
    else if (sys->c_hour >= 5)
        sys->dis.dis_light = 7;
}

        
