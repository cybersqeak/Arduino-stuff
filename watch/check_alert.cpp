#include "system.h"
static void beep(void)
{
    int count = 0;
    while (count <= 3)
    {
        analogWrite(ALERT,10);
        delay(100);
        analogWrite(ALERT,0);
        delay(100);
        count++;
    }
}    


static void begin_alert(void)
{
    while (1)
    {
        beep();
        if (!digitalRead(ALERT_PIN))
            break;
    }
}
            
void check_alert(t_sys *sys)
{
    if ((sys->c_hour == sys->alert_time.hour) && (sys->c_min == sys->alert_time.minute))
    {
        begin_alert();
        /* here i want to make something displays cool stuff like good morning in display.*/ 
    }
}

