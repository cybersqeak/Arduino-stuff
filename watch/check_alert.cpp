#include "system.h"

static void snooze(t_sys *sys)
{
    sys->alert_time.minute += 10;
}

static void begin_alert(t_sys *sys)
{ 
    unsigned long elapsed = 0;
    
    if (!(sys->alert_time.stoped_alert))
    {
        elapsed = millis();
        while (1)
        {
            Serial.printf("\nelapse time is %zu",elapsed);
            sound_effect(103);
            if ((!digitalRead(STOP_AT) || elapsed >= 60000)) /* each beeps takes about 0.2sec * 300 approx 1min.*/
            {
                
                Serial.print("stops");
                int i = 0;
                while (i <= 5)// press stop_at within 4 src enables snoonz for +10min
                {
                    if(!digitalRead(STOP_AT))
                     {
                         Serial.print("snooze");
                         snooze(sys);
                         sound_effect(102);
                         break;
                      }
                      delay(800);
                      i++;
                }
                sys->alert_time.stoped_alert = millis(); // tell system you already notice alert and beg to stop!  
                break;
            }
        }
    }
}        

void check_alert(t_sys *sys)
{
    if ((sys->c_hour == sys->alert_time.hour) && (sys->c_min == sys->alert_time.minute))
    {
        
        begin_alert(sys);
        /* here i want to make something displays cool stuff like good morning in display.*/ 
    }
}

