#include "system.hpp"

void snooze(t_sys *sys)
{
    sound_effect(105);
    sys->alert_time.minute += 10;
}


