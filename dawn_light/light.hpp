#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <Wire.h>
#include <RTClib.h>

extern const int mosfetPin;
extern const int rmosfetPin;
extern const int sensor_pin;

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



typedef struct s_info
{
   unsigned long  elapsed_t;
   unsigned long  start_t;
   int manual_mode;
   int brightness;
   int currentMinutes;

} t_info;

void manual_mode(int pin, t_info *info);






















#endif
