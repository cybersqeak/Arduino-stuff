#include "system.h"

void begin_alert(t_sys *sys)
{
   const unsigned long double_click_gaptime = 300; // 0.3 seconds .....maybe too fast?  
   const unsigned long one_minute = 60000;
   unsigned long last_pressed_t = 0;                                               
   unsigned long whole_elapsed_t;                                               

   whole_elapsed_t = millis();
   while (millis() - whole_elapsed_t > one_minute)
   {
       sound_effect(104);
       if (!digitalRead(STOP_AT))
       {
           delay(300);
           last_pressed_t = millis();
           while (1)
           {
                if(!digitalRead(STOP_AT) && (millis() - last_pressed_t <= double_click_gaptime))
                {
                    Serial.printf("\nactivate Snooze!!\n");
                    snooze(sys);
                    break;
                }
                else if (millis() - last_pressed_t > double_click_gaptime)
                {
                    Serial.printf("\nNo double press detected!\n");
                    break;
                }
           }
           break;
       }
       whole_elapsed_t = millis();
       Serial.printf("\nremaining time  : %zu \n",one_minute - whole_elapsed_t);
   } 
}
