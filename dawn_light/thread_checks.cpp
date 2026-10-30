#include "light.hpp"

void    sensor_check(void *param)
{
    t_info *info =( t_info *)(param);
    vTaskDelay(7000);
    while(1)
    {
        info->sensor_pin = 0;
        while (info->led_mode[2])
        {
            info->sensor_pin = digitalRead(sensor_pin);
            vTaskDelay(100);
        }
        vTaskDelay(100);
    }
}
    
/* here program will choose what mode to select (depends on time*/

void    check_time(void *param)
{
    t_info *info = (t_info*)(param);

    vTaskDelay(7000);
    while (1)
    {
 //       Serial.println("checking time in check_time thread\n");

        if (info->currentMinutes >= startMinutes &&
                info->currentMinutes < wakeMinutes)
        {
  //          Serial.println("Wake up led mode enabled\n");
            info->led_mode[0] = true;
            info->led_mode[1] = false;
            info->led_mode[2] = false;
        }
        else if (info->currentMinutes >= rstartMinutes &&
                info->currentMinutes < bedMinutes)
        {
  //          Serial.println("bed mode enabled\n");
            info->led_mode[0] = false;
            info->led_mode[1] = true;
            info->led_mode[2] = false;
        }
        else if(wakeMinutes <= info->currentMinutes && info->currentMinutes < rstartMinutes)
        {
   //         Serial.println("Normal mode , sensor enabled\n");
            info->led_mode[0] = false;
            info->led_mode[1] = false;
            info->led_mode[2] = true;
        }
        else
        {
    //        Serial.println("Night mode enable goodnight\n");
            info->led_mode[0] = false;
            info->led_mode[1] = false;
            info->led_mode[2] = false;
        }
            
       vTaskDelay(100);
    }

}



