
#include "system.h"

// e.g. put this in alert_assign.cpp or a new sound.cpp
#include "system.h"

void beep(int freq, int duration_ms)
{
    ledcWriteTone(ALERT, freq);
    delay(duration_ms);
    ledcWriteTone(ALERT, 0);
}
// rising sweep — good for "wake up" alarm
static void alert_rising_sweep()
{
    for (int freq = 500; freq <= 2200; freq += 60)
    {
        ledcWriteTone(ALERT, freq);
        delay(12);
    }
    ledcWriteTone(ALERT, 0);
}

// classic two-tone siren
static void alert_siren()
{
    for (int i = 0; i < 4; i++)
    {
        beep(1000, 150);
        beep(1500, 150);
    }
}

// playful R2D2-style chirps — good for button/mode change
static void chirp_fun()
{
    int freqs[] = {800, 1200, 1000, 1600, 1400};
    for (int i = 0; i < 5; i++)
    {
        beep(freqs[i], 60);
        delay(30);
    }
}

// clean triple beep — good for confirmations
static void triple_beep()
{
    for (int i = 0; i < 3; i++)
    {
        beep(2000, 120);
        delay(80);
    }
}

// short single click — good for button press feedback
static void click()
{
    beep(1800, 40);
}

// descending "power down" style tone
static void power_down()
{
    for (int freq = 2000; freq >= 400; freq -= 80)
    {
        ledcWriteTone(ALERT, freq);
        delay(10);
    }
    ledcWriteTone(ALERT, 0);
}

// little 3-note chime melody — good for alarm going off
static void chime_melody()
{
    beep(1046, 150); // C6
    beep(1318, 150); // E6
    beep(1568, 250); // G6
    delay(80);
    beep(1568, 250);
}

void sound_effect(int type)
{
    switch (type)
    {
        case 101: alert_rising_sweep(); break;  // alarm trigger
        case 102: alert_siren();        break;  // alternate alarm style
        case 103: chirp_fun();          break;  // mode change
        case 104: triple_beep();        break;  // confirm action
        case 105: click();              break;  // button press
        case 106: power_down();         break;  // switch off
        case 107: chime_melody();       break;  // alarm melody
    }
}
