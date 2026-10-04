#include "system.hpp"

void begin_alert(t_sys *sys)
{
   const unsigned long double_click_gaptime = 1000; // 1 seconds .....maybe too fast?  
   const unsigned long one_minute = 60000;

   unsigned long last_pressed_t = 0;                                               
   unsigned long whole_elapsed_t;                                               
   unsigned long start_t;

   start_t = millis();
   while (millis() - start_t <=  one_minute)
   {
       sound_effect(104);
       if (!digitalRead(STOP_AT))
       {
           sys->elapsed_t = millis();
           last_pressed_t = millis();
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
           break;
       }
       whole_elapsed_t = millis();
       Serial.printf("\nremaining time  : %zu \n",(one_minute - (millis() - start_t)));
   } 
}
