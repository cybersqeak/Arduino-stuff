#include "system.h"

void    check_stop_alert(t_sys *sys)
{
    if (sys->alert_time.stoped_alert) 
        sys->alert_time.stoped_alert = 0;
}
