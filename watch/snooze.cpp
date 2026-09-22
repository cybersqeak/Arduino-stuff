#include "system.h"

void snooze(t_sys *sys)
{
    sys->alert_time.minute += 10;
    sound_effect(105);
}


