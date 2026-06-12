#ifndef WATCH_H
#define WATCH_H

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
