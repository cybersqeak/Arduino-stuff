#include "system.h"

static void snooze(t_sys *sys)
{
    sys->alert_time.minute += 10;
    sound_effect(105);
}

static void begin_alert(t_sys *sys)
{ 
    static unsigned long elapsed;
    unsigned long current_t;
    Serial.printf("elapsed time :  %zu\n",elapsed);
    if (elapsed >= 60000)
        elapsed = 0;
    if (!(elapsed))
    {
        current_t = millis();
        while (1)
        {
            elapsed =  millis() -current_t;
            Serial.printf("\nelapse time is %zu",elapsed);
            sound_effect(107);
            if ((!digitalRead(STOP_AT))) /* each beeps takes about 0.2sec * 300 approx 1min.*/
            {
                Serial.print("stops");
                int i = 0;
                delay(300);
                while (i <= 5)// press stop_at within 4 src enables snoonz for +10min
                {
                    if(!digitalRead(STOP_AT))
                     {
                         Serial.print("\n10minutes snooze\n");
                         snooze(sys);
                         break;
                      }
                    else if ((!digitalRead(DB_PIN) || !digitalRead(MODE_PIN)))
                        break;
                      delay(800);
                      i++;
                }
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

