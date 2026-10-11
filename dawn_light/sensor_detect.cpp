#include "light.hpp"

/* sensor is able during certain time zone. in my case I want to activate sensor 7:00 am ~ 18:00 pm */
/* i also want to choose which red to use depend on time */

int seven_am = 420; // this 7 am represented in minute passed from a day
int four_pm = 960;
int six_pm = 1080; // 18 pm
void turn_on(int pin, t_info *info);

void sensor_detected(int r_pin, int w_pin,t_info *info)
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

    if (seven_am < info->currentMinutes && info->currentMinutes < six_pm)
    {
        Serial.print("Red light system turned On!");
        analogWrite(255); // max strength is good here
    }

    if (info->elapsed_t >= five_min)
    {
        //turn_off(r_pin, w_pin);
        info->start_t = 0;
        info->elapsed_t = 0;
    }
}

