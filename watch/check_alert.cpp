#include "system.hpp"

void check_alert(t_sys *sys)
{
    unsigned long start_t;
    const unsigned long one_minute = 60000;
    Serial.printf("the time passed from alert stoped is%zu\n",millis() - sys->elapsed_t);
    if (sys->elapsed_t && millis() - sys->elapsed_t <= 60000)
        return;
    if ((sys->c_hour == sys->alert_time.hour) && (sys->c_min == sys->alert_time.minute))
    {
        begin_alert(sys);
    }

}
