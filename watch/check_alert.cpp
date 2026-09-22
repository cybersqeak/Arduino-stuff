#include "system.h"

void check_alert(t_sys *sys)
{
    static unsigned long Alert_stop_elapsed_t;   
    static unsigned long start_t;
    const unsigned long one_minute = 60000;

    Serial.printf("\nhello  %zu\n", Alert_stop_elapsed_t);
    if (millis() - start_t > one_minute)
        Alert_stop_elapsed_t = 0;

    if ((sys->c_hour == sys->alert_time.hour) && (sys->c_min == sys->alert_time.minute))
    {
        Serial.printf("\nin here %zu\n", Alert_stop_elapsed_t);
        if (Alert_stop_elapsed_t)
            return; 
        else
        { 
            begin_alert(sys);
            Alert_stop_elapsed_t = millis() - start_t;;
        }
    }
}
