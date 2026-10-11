#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <Wire.h>
#include <RTClib.h>
#include <Arduino.h>

extern const int mosfetPin;
extern const int rmosfetPin;
extern const int sensor_pin;
extern const int manual_mode_pin;
extern const int plus_pin;
extern const int minus_pin;


extern  const int startHour;
extern const int startMinute;

extern const int rstartHour;
extern const int rstartMinute;

extern const int wakeHour;
extern const int wakeMinute;

extern const int bedHour;
extern const int bedMinute;

extern  int startMinutes;
extern  int rstartMinutes;
extern  int bedMinutes;
extern  int wakeMinutes;



typedef struct s_info
{
   unsigned long  elapsed_t;
   unsigned long  start_t;
//   int manual_mode;
   bool sensor_detected;
   bool sensor_enable;
   bool led_mode[3];
   int brightness;
   int currentMinutes;

} t_info;

void manual_mode(int pin, t_info *info);
void check_time(void *param);
void sensor_check(void *param);






















#endif
