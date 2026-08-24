#ifndef SYSTEM_H
#define SYSTEM_H

#include <unistd.h>
#include <stdio.h>
#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <TM1637Display.h>
#include <DHT.h>

extern RTC_DS3231 rtc;
extern TM1637Display display;
extern DHT dht;

// custom symbols using segments already defined in system.h
#define SEG_DEGREE (SEG_A | SEG_B | SEG_F | SEG_G)          // small circle top-right
#define SEG_C      (SEG_A | SEG_D | SEG_E | SEG_F)          // letter C
#define SEG_H (SEG_B | SEG_C | SEG_E | SEG_F | SEG_G)
#define SEG_u (SEG_C | SEG_D | SEG_E)

#define ON 1
#define OFF 0

#define CLK 18
#define DIO 19

#define CLK 18
#define DIO 19

#define ALERT 2
#define DHTPIN 5

#define DB_PIN 4  // the button to select display state ON or OFF
#define MODE_PIN 13 // the button to select mode

#define DHTTYPE DHT11


/* struct about setting alert */
typedef struct s_alerm
{
    int hour;
    int minute;
}t_alerm;

/* modes to be selected*/
typedef enum    e_mode
{
    TIME, //0
    TEMP,// 1
    HUMID,//2
} t_mode;

/* struct about display setting */
typedef struct s_display
{
    int dis_light;
    t_mode mode;
} t_display;

/*structure that hold all system infomations*/
typedef struct s_sys
{
    t_alerm alert_time;
    t_display dis; 
    int switch_state;
}t_sys;


void run(t_sys *sys);
void check_mode(t_sys *sys);
void on_off(t_sys *sys);





#endif
