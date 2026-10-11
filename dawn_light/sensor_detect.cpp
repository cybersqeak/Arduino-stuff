#include "light.hpp"

void sensor_detected(int pin, t_info *info)
{
    const unsigned int five_min = 300000;
    if (info->start_t == 0)
       info->start_t = millis(); 
    info->elapsed_t  = millis() - info->start_t;
    /*if (seven_am < info->currentMinutes && info->currentMinutes < four_pm)
    {
        Serial.print("white light would be good at this time!\n");
       turn_on(w_pin,info);
    }
    */
    /*else if  (four_pm <= info->currentMinutes && info->currentMinutes < six_pm)
    {
        Serial.print("red light would be good at this time!\n");
        turn_on(r_pin,info);
    }*/
    analogWrite(pin,255); // max strength is good here
    Serial.println("RED LED ON!\n");
                      
    if (info->elapsed_t >= five_min)
    {
        info->start_t = 0;
        info->elapsed_t = 0;
    }
}

