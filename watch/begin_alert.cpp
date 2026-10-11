#include "system.hpp"

static void    listenForButton(void *parm)
{
    t_sys *sys = (t_sys *)(parm);

    const unsigned long double_click_gaptime = 1000; // 1 seconds .....maybe too fast?  

    unsigned long last_pressed_t = 0;                                               
    unsigned long whole_elapsed_t;                                               
    sys->alert_stop = 0;
    while (1)
    {
        if (!digitalRead(STOP_AT))
        {
            sys->elapsed_t = millis();
            last_pressed_t = millis();
            sys->alert_stop = 1;
            delay(300);
            while (millis() - last_pressed_t <= double_click_gaptime)
            {
                if(!digitalRead(STOP_AT))
                {
                    Serial.printf("\nactivate Snooze!!\n");
                    snooze(sys);
                    break;
                }
                Serial.printf("\nNo double press detected!\n");
            }
            /*i also need to break the while loop in begin=_alert()*/
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelete(NULL);
}

void begin_alert(t_sys *sys)
{
    const unsigned long one_minute = 60000;
    unsigned long start_t;
    
    xTaskCreate(listenForButton,"Button_check",2048, sys, 1, NULL);
    start_t = millis();
    /* i want start a thread here to listen to button state*/
    while (millis() - start_t <=  one_minute)
    {
        sound_effect(104);
        if (sys->alert_stop == 1)
            break;
        Serial.printf("\nremaining time  : %zu \n",(one_minute - (millis() - start_t)));
    } 
}
