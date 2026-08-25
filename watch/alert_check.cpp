#include "system.h"

void    dis_alert_time(t_sys *sys)
{
   int alert_t = sys->alert_time.hour * 100 + sys->alert_time.minute;
  display.showNumberDecEx(alert_t,0b01000000,true);
 display.setBrightness(7,true);
} 

void    alert_check(t_sys *sys)
{
    while (1)
    {
        dis_alert_time(sys);
        if (!digitalRead(DB_PIN))
        {
            sys->alert_time.hour++;
            Serial.print("hour++: %d\n",sys->alert_time.hour);
            deley(300);
        }
        if (!digitalRead(MODE_PIN))
        {
            sys->alert_time.minute++;
            Serial.print("minute++: %d\n",sys->alert_time.minute);
            deley(300);
        }
        if (
        delay(100);
    }

