#include "light.hpp"


// Gradually raise the morning light!!!

void sun_raise(int pin, t_info *info)
{
    // no manual_mode needed here 
    // i want to make a mathematical model that represent(not perfect) gradiation of light intensity like a sun in morning 
    /* sun raises 15 degree per one hour thus every minute sun raises about 0.25 degree per minute   
     * I(t) = I_max * sin(0.25 * t) where t is minute and info->currentMinutes - startMinute correspond to it
     * but I i mean brightness has to be an integer to use for analogwrite mm. what should i do..
     * i should check if there is a other function simmilar to it but more flexible one 
     * I found a function called  ledWrite() for esp32 core 3.x~ i need check my version
     * oh yes i can use it lets try!!*/
    
    info->brightness = (info->currentMinutes - startMinute)*2 + 1;

    if (info->brightness>= 255)
        info->brightness = 255;
    analogWrite(pin, info->brightness);
}

