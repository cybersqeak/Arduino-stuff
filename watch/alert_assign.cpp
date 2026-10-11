#include "system.hpp"

static void    dis_alert_time(t_sys *sys)
{
    int alert_t = sys->alert_time.hour * 100 + sys->alert_time.minute;
    display.showNumberDecEx(alert_t,0b01000000,true);
    display.setBrightness(sys->dis.dis_light,true);
} 




static void    minute_button(void *param)
{
   t_sys *sys = (t_sys *)(param);
    const unsigned long double_pressed_gap = 300;   // widened from 150 — more reliable
    unsigned long last_pressed_t;
    int i;

   while (1)
   {
       i = 1;
       if (!digitalRead(MODE_PIN))
       {
           last_pressed_t = millis();
           delay(150);   // debounce only, shortened from 150

           while(millis() - last_pressed_t <= double_pressed_gap)
           {
               if(!digitalRead(MODE_PIN))
               {
                   i  = 59;
                   delay(150);
                   break;
               }
           }
           sys->alert_time.minute = (sys->alert_time.minute + i) % 60;
       }
       if (sys->scheduled[1] == 1)
       {
               sys->scheduled[1] = 0;
               vTaskDelete(NULL);
       }
       vTaskDelay(10);
   }
}




static void    hour_button(void *param)
{
   t_sys *sys = (t_sys *)(param);
    const unsigned long double_pressed_gap = 300;   // widened from 150 — more reliable
    unsigned long last_pressed_t;
    int i;

   while (1)
   {
       i = 1;
       if (!digitalRead(DB_PIN))
       {
           last_pressed_t = millis();
           delay(150);   // debounce only, not a wait — shortened from 150
           while ((millis() - last_pressed_t <= double_pressed_gap)) 
           {
               if(!digitalRead(DB_PIN))
               {
                   /*if (i == 1)
                       i = 23;
                   else 
                       i = 1;
                   Serial.printf("hour direction mode changed %i",i);
                   */
                   i = 23;
                   delay(150);
                   break;
               }
           }
           sys->alert_time.hour = (sys->alert_time.hour + i) % 24;
       }
       if (sys->scheduled[0] == 1)
       {
           sys->scheduled[0] = 0;
           vTaskDelete(NULL);
       } 
       vTaskDelay(10);

   }
}

 
static void    selected_button(void *param)
{
   t_sys *sys = (t_sys *)(param);
   delay(300);
   while (1)
   {
       if (!digitalRead(ALERT_PIN))
       {
           sound_effect(105);
           sys->scheduled[0] = 1;
           sys->scheduled[1] = 1;
           sys->scheduled[2] = 1;
           break;
       }
       vTaskDelay(10);
   }
   vTaskDelete(NULL);
}

      
/*static void fade_display(void *param)
{
    while(1)
    {
        display.close();
        if
        delay(3000);
        
*/

void    alert_assign(t_sys *sys)
{
    xTaskCreate(hour_button,"hourbuttoncheck",2048,sys,1,NULL);
    xTaskCreate(minute_button,"minutebuttoncheck",2048,sys,1,NULL);
    xTaskCreate(selected_button,"selected_check",2048,sys,1,NULL);
 //   XTaskCreate(fade_display, "fadedisplay", 2048, sys,1, NULL);
    while (1)
    {
        dis_alert_time(sys);
        if(sys->scheduled[2] == 1)
        {
            sys->scheduled[2] = 0;
            return;
        }
        Serial.printf("seleted time %d:%d\n",sys->alert_time.hour, sys->alert_time.minute);
    }
}
