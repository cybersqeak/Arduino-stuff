#include "light.hpp"

void    sensor_check(void *param)
{
    t_info *info =( t_info *)(param);
    vTaskDelay(7000);
/*    if (info->sensor_enable == false)
        vTaskDelete(NULL);*/
    while (1)
    {
//        Serial.println("i ama here\n");
        if (!info->led_mode[2])
        {
            vTaskDelay(pdMS_TO_TICKS(100));
            info->sensor_pin = 0;
//            Serial.printf("skip\n");
            continue;
        }
        info->sensor_pin = digitalRead(sensor_pin);
        if (info->sensor_pin)
        {
            info->sensor_detected = true;
 //           Serial.println("Motion detected\n");
        }
        else
        {
  //          Serial.println("No motion detected\n");
        }

    /*    if (info->sensor_enable = false)
        {
            info->sensor_detected = false;
            vTaskDelete(NULL);
        }*/

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
                info->currentMinutes <= wakeMinutes)
        {
  //          Serial.println("Wake up led mode enabled\n");
            info->led_mode[0] = true;
            info->led_mode[1] = false;
            info->led_mode[2] = false;
        }
        else if (info->currentMinutes >= rstartMinutes &&
                info->currentMinutes <= bedMinutes)
        {
  //          Serial.println("bed mode enabled\n");
            info->led_mode[0] = false;
            info->led_mode[1] = true;
            info->led_mode[2] = false;
        }
        else if(wakeMinutes < info->currentMinutes && info->currentMinutes < rstartMinutes)
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



