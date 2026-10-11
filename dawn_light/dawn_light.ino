#include "light.hpp"
RTC_DS3231 rtc;

const int mosfetPin = 2;
const int rmosfetPin = 16;
const int sensor_pin = 4;
//const int manual_mode_pin = 13;

const int plus_pin = 14;
const int minus_pin = 27;
const int startHour = 5;
const int startMinute = 00;

const int rstartHour = 18;
const int rstartMinute = 0;

const int wakeHour = 7;
const int wakeMinute = 0;

const int bedHour = 21;
const int bedMinute = 15;


// Schedule times just a exampleee
int startMinutes;
int wakeMinutes;
int rstartMinutes;
int bedMinutes;


static t_info info;
void setup()
{
    Serial.begin(115200);

    /*transistor pins*/

    pinMode(mosfetPin, OUTPUT);
    pinMode(rmosfetPin, OUTPUT);
    /*sensor pin (two sensors but in single pin. cool right?*/
    pinMode(sensor_pin,INPUT);
    /* the button pins for manipulating the LED*/
    pinMode(manual_mode_pin,INPUT);
    pinMode(plus_pin,INPUT);
    pinMode(minus_pin,INPUT);
    analogWrite(mosfetPin, 0);
    analogWrite(rmosfetPin, 0);

    startMinutes = startHour * 60 + startMinute;
    wakeMinutes = wakeHour * 60 + wakeMinute;

    rstartMinutes = rstartHour * 60 + rstartMinute;
    bedMinutes = bedHour * 60 + bedMinute;

    rtc.begin();

    xTaskCreate(sensor_check, "check_sensor",2048,info,1,NULL);
    xTaskCreate(check_time, "check_time",2048,info,1,NULL);
    
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop()
{
    DateTime now = rtc.now();

    int info.currentMinutes = now.hour() * 60 + now.minute();

    Serial.printf("current time is %d\n",currentMinutes);

    // wake up with Fake sun_raise!! 
    if (info.led_mode[0])
    {
        Serial.print("sun raising\n");
        sun_raise(mosfetPin);
    }

    // EveningRED LED turn on
    else if (info.led_mode[1])
    {
        analogWrite(mosfetPin,0):
        Serial.print("night time!\n");
        sleepy_night(rmosfetPin);
        //analogWrite(rmosfetPin, 25);
    }

    else  if (info.sensor_detected = true || info.elapsed_t)
    {
        analogWrite(mosfetPin,0):
        Serial.print("the sensor detected  statement\n");
        sensor_detected(rmosfetPin,&info)
        Serial.printf("start_t is %d\n",info.start_t);
        Serial.printf("elapsed_t is %d\n",info.elapsed_t);
    }

    else 
    {
        Serial.print("the None statement\n");
        analogWrite(rmosfetPin,0);
        analogWrite(mosfetPin,0):
    }
}
