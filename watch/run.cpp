#include "system.h"

static void display_temp(void)
{
    int temp = dht.readTemperature();
    uint8_t seg_data[4];

    seg_data[0] = display.encodeDigit(temp / 10);   // tens digit
    seg_data[1] = display.encodeDigit(temp % 10);   // ones digit
    seg_data[2] = SEG_DEGREE;                        // °
    seg_data[3] = SEG_C;                              // C

    display.setSegments(seg_data);
    display.setBrightness(7, true);
}

static void display_humid(void)
{
    int hum = dht.readHumidity();
    uint8_t seg_data[4];
    seg_data[0] = 0;                                  // blank
    seg_data[1] = display.encodeDigit(hum / 10);
    seg_data[2] = display.encodeDigit(hum % 10);
    seg_data[3] = 118;                               // H for humidity (no real % glyph exists)
    display.setSegments(seg_data);
    display.setBrightness(7, true);
    
}
static void dis(void)
{
    DateTime now = rtc.now();
    int time_value = now.hour() * 100 + now.minute();
    display.showNumberDecEx(time_value, 0b01000000,true);
    display.setBrightness(7,true);
}

void   run(t_sys *sys)
{
    if (sys->dis.mode == TIME)
        dis();
    else if (sys->dis.mode == HUMID)
        display_humid();
    else 
        display_temp();
}

