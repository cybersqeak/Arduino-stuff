#include "system.h"

void    on_off(t_sys *sys)
{
    if (sys->switch_state == 0)
        sys->switch_state = 1;
    else if (sys->switch_state == 1)
        sys->switch_state = 0;
}

