#include "light.hpp"

void sensor_detected(t_info *info)
{
    const unsigned int five_min = 300000;
//    const unsigned int five_min = 10000;
    if (info->start_t == 0 || info->sensor_pin)
       info->start_t = millis(); 
    info->elapsed_t  = millis() - info->start_t;
                      
    if (info->elapsed_t >= five_min)
    {
        info->start_t = 0;
        info->elapsed_t = 0;
    }
}

