#include "light.hpp"

void    sensor_check(void *param)
{
    t_info *info =( t_info *)(param);
/*    if (info->sensor_enable == false)
        vTaskDelete(NULL);*/
    while (1)
    {
        if (!info->led_mode[2])
            continue;
        if (!digitalRead(sensor_pin))
        {
            info->sensor_detected = true;
            Serial.println("Motion detected\n");
        }
        else
            info->sensor_detected = false;

    /*    if (info->sensor_enable = false)
        {
            info->sensor_detected = false;
            vTaskDelete(NULL);
        }*/

        vTaskDelay(10);
    }
}
    
/* here program will choose what mode to select (depends on time*/

void    check_time(void *param)
{
    t_info *info = (t_info*)(param);

    while (1)
    {
        if (info->currentMinutes >= startMinutes &&
                info->currentMinutes <= wakeMinutes)
        {
            info->led_mode[0] = true;
            info->led_mode[1] = false;
            info->led_mode[2] = false;
        }
        else if (info->currentMinutes >= rstartMinutes &&
                info->currentMinutes <= bedMinutes)
        {
            info->led_mode[0] = false;
            info->led_mode[1] = true;
            info->led_mode[2] = false;
        }
        else
        {
            info->led_mode[0] = false;
            info->led_mode[1] = false;
            info->led_mode[2] = true;
        }
       vTaskDelay(10);
    }

}



