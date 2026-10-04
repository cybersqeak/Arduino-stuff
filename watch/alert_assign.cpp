#include "system.hpp"

static void    dis_alert_time(t_sys *sys)
{
    int alert_t = sys->alert_time.hour * 100 + sys->alert_time.minute;
    display.showNumberDecEx(alert_t,0b01000000,true);
    display.setBrightness(sys->dis.dis_light,true);
} 
void    alert_assign(t_sys *sys)
{
    int  count = 1;
    const unsigned long double_pressed_gap = 300;   // widened from 150 — more reliable
    unsigned long last_pressed_t;
    int pressed = 0;
    int i = 1; // plus direction
    int j = 1;
    display.clear();
    delay(200);
    while (1)
    {
        dis_alert_time(sys);
        if (!digitalRead(DB_PIN))
        {
            last_pressed_t = millis();
            delay(150);   // debounce only, not a wait — shortened from 150
            while ((millis() - last_pressed_t <= double_pressed_gap)) 
            {
                if(!digitalRead(DB_PIN))
                {
                    if (i == 1)
                        i = 23;
                    else 
                        i = 1;
                    Serial.printf("hour direction mode changed %i",i);
                    break;
                }
            }
                sys->alert_time.hour = (sys->alert_time.hour + i) % 24;
                Serial.printf("hour : %d\n",sys->alert_time.hour);
        }
        if (!digitalRead(MODE_PIN))
        {
            last_pressed_t = millis();
            delay(150);   // debounce only, shortened from 150

            while(millis() - last_pressed_t <= double_pressed_gap)
            {
                if(!digitalRead(MODE_PIN))
                {
                    if (j == 1)
                       j  = 59;
                    else
                        j = 1;
                    Serial.printf("minute direction mode changed %i",j);
                    break;
                }
            }
                sys->alert_time.minute = (sys->alert_time.minute + i) % 60;
                Serial.printf("minute : %d\n",sys->alert_time.minute);
            }
    
        
        if (!digitalRead(ALERT_PIN))
        {
            sound_effect(105);
            break;
        }
        count++;
        delay(100);
    }
    display.clear();
}
