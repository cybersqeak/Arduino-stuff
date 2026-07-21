#ifndef WATCH_H
#define WATCH_H

#define TIME 1
#define HUMIDITY 2
#define TEMPERATURE 3

#define SEG_A   0b00000001
#define SEG_B   0b00000010
#define SEG_C   0b00000100
#define SEG_D   0b00001000
#define SEG_E   0b00010000
#define SEG_F   0b00100000
#define SEG_G   0b01000000
#define SEG_DP  0b10000000


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




void set_mode(int *current_mode);

int alert_sound(int pin);

int check_alert(int h, int m);




#endif
