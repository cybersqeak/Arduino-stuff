#include "system.h"

static void    dis_alert_time(t_sys *sys)
{
    int alert_t = sys->alert_time.hour * 100 + sys->alert_time.minute;
    display.showNumberDecEx(alert_t,0b01000000,true);
    display.setBrightness(sys->dis.dis_light,true);
} 

void    alert_assign(t_sys *sys)
{
    int  count = 1;
    display.clear();
    delay(200);
    while (1)
    {

        if ((count % 10) == 0) 
        {
            Serial.printf("count is %i\n",count);
            count = count % 10; //reset prevent overflow risks
            display.clear(); 
            delay(500);
        }
        dis_alert_time(sys);
        if (!digitalRead(DB_PIN))
        {
            sys->alert_time.hour = (sys->alert_time.hour + 1) % 24;
            Serial.printf("hour++: %d\n",sys->alert_time.hour);
            delay(300);
        }
        if (!digitalRead(MODE_PIN))
        {
            sys->alert_time.minute = (sys->alert_time.minute + 1) % 60;
            Serial.printf("minute++: %d\n",sys->alert_time.minute);
            delay(300);
        }
        if (!digitalRead(ALERT_PIN))
        {
            sound_effect(105);
           /* i want to add some visiual effect when you choose time  saved_dis();*/
            break;
        }
        count++;
        delay(100);
    }
        display.clear();
}
