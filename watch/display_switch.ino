#include "watch.h"
#include <TM1637Display.h>

#define ON 1
#define OFF 0

#define CLK 18
#define DIO 19


TM1637Display display(CLK, DIO);

void Turn_switch(int *current_state)
{
    if (*current_state == ON)
        display.setBrightness(7,true);
    else
       display.setBrightness(0,false);
} 

void Display_switch(int *current_state)
{
    if (*current_state == OFF)
        *current_state = ON;
    else 
        *current_state = OFF;
}
