#include "light.hpp"
RTC_DS3231 rtc;

const int mosfetPin = 2;
const int rmosfetPin = 16;
const int sensor_pin = 4

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


void setup()
{
    Serial.begin(115200);
    pinMode(mosfetPin, OUTPUT);
    pinMode(rmosfetPin, OUTPUT);
    pinMode(sensor_pin,INPUT);

    analogWrite(mosfetPin, 0);
    analogWrite(rmosfetPin, 0);

    startMinutes = startHour * 60 + startMinute;
    wakeMinutes = wakeHour * 60 + wakeMinute;

    rstartMinutes = rstartHour * 60 + rstartMinute;
    bedMinutes = bedHour * 60 + bedMinute;

    rtc.begin();

    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}


void loop()
{
    DateTime now = rtc.now();
    static t_info info;

    int info.currentMinutes = now.hour() * 60 + now.minute();
    Serial.printf("current time is %d\n",currentMinutes);


    // wake up with Fake sun_raise!! 
    if (info.currentMinutes >= startMinutes && info.currentMinutes <= wakeMinutes)
    {
        Serial.print("sun raising\n");
        sun_raise(mosfetPin);
    }


    // EveningRED LED turn on
    else if (info.currentMinutes >= rstartMinutes && info.currentMinutes <= bedMinutes && info.manual_switch = 1;)
    {
        Serial.print("RED LED time!\n");
        sleepy_night(rmosfetPin);
        //analogWrite(rmosfetPin, 25);
    }

    else  if (sensor_pin == HIGH || info.elapsed_t)
    {
        Serial.print("the sensor detected  statement\n");
        //Serial.printf("elapsed_t is %d\n",info.elapsed_t);
        sensor_detected(rmosfetPin,mosfetPin,&info)
        Serial.printf("start_t is %d\n",info.start_t);
        Serial.printf("elapsed_t is %d\n",info.elapsed_t);
    }

    else 
    {
        Serial.print("the None  statement\n");
        analogWrite(rmosfetPin,0);
        analogWrite(mosfetPin,0):
    }
}
