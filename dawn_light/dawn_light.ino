#include "light.hpp"
RTC_DS3231 rtc;

const int mosfetPin = 2;
const int rmosfetPin = 16;
const int sensor_pin = 4;
//const int manual_mode_pin = 13;

//const int plus_pin = 14;
//const int minus_pin = 27;
const int startHour = 5;
const int startMinute = 30;

const int rstartHour = 20;
const int rstartMinute = 0;

const int wakeHour = 7;
const int wakeMinute = 0;

const int bedHour = 21;
const int bedMinute = 30;


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
    pinMode(sensor_pin,INPUT_PULLDOWN);
    /* the button pins for manipulating the LED*/
    //pinMode(manual_mode_pin,INPUT);
//    pinMode(plus_pin,INPUT);
 //   pinMode(minus_pin,INPUT);
    analogWrite(mosfetPin, 0);
    analogWrite(rmosfetPin, 0);

    startMinutes = startHour * 60 + startMinute;
    wakeMinutes = wakeHour * 60 + wakeMinute;

    rstartMinutes = rstartHour * 60 + rstartMinute;
    bedMinutes = bedHour * 60 + bedMinute;

    rtc.begin();

    xTaskCreate(sensor_check, "check_sensor",2048,&info,1,NULL);
    xTaskCreate(check_time, "check_time",2048,&info,1,NULL);
    
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    delay(5000);
}
   
void loop()
{
    DateTime now = rtc.now();
    info.currentMinutes = now.hour() * 60 + now.minute();

    // Print the complete state every second.
    print_status(&info);

    if (info.led_mode[0])
    {
        sun_raise(mosfetPin, &info);
    }
    else if (info.led_mode[1])
    {
        info.elapsed_t = 0;
        analogWrite(mosfetPin, 0);
        sleepy_night(rmosfetPin, &info);
    }
    else if (info.sensor_pin || info.elapsed_t)
    {
        analogWrite(mosfetPin, 0);
        analogWrite(rmosfetPin,255); // max strength is good here
        sensor_detected(&info);
    }
    else
    {
        Serial.println("am here\n");
        analogWrite(rmosfetPin, 0);
        analogWrite(mosfetPin, 0);
    }

    delay(100);
}
 
