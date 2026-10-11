#include "system.hpp"

void snooze(t_sys *sys)
{
    sound_effect(105);
    if (sys->alert_time.minute >= 50)
        sys->alert_time.hour += 1;
    sys->alert_time.minute += 10;
}


