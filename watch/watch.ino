#include <unistd.h>
#include <Wire.h>
#include "RTClib.h"
#include <TM1637Display.h>
#include <stdio.h>
#include <DHT11.h>
RTC_DS3231 rtc;

#define CLK 18
#define DIO 19
#define ALERT 2
#define DB_PIN 4 
#define DHT11PIN 5

TM1637Display display(CLK, DIO);
DHT11 dht11(DHT11PIN);  

void checkdht(int humidity, int temperature)
{
    if (humidity == DHT11::ERROR_CHECKSUM ||
        humidity == DHT11::ERROR_TIMEOUT ||
        temperature == DHT11::ERROR_CHECKSUM ||
        temperature == DHT11::ERROR_TIMEOUT)
    {
        Serial.println("DHT read failed");
        return;
    }

    Serial.print("humidity: ");
    Serial.println(humidity);

    Serial.print("temperature: ");
    Serial.println(temperature);
}
/*
void    checkdht(int humidity, int temperature)
{
    if (isnan(humidity) || isnan(temperature))
  {
      Serial.println("Failed to read from  dht sensor");
      return ;
  }
  Serial.println("humidity: ");
  Serial.println(humidity);
  Serial.println(" %");
  Serial.println("temperature: ");
  Serial.println(temperature);
  Serial.println(" *C");
}
  
*/
int check_button_state(int button_pin, int flag)
{
    if (button_pin == 0 && flag == 1) 
      {
          display.setBrightness(0,false); 
          flag= 0;
          printf("the display  is now off  %d\n",flag);
          delay(500);
      }
      else if (button_pin == 0 && flag == 0)
      {
          display.setBrightness(7,true);
          flag = 1;
          printf("the display is now on %d\n", flag);
          delay(500);
      }
      else if (button_pin == 1 && flag == 1)
          display.setBrightness(7,true);
      return (flag);
}

int check_alert(int h, int m)
{
    if (h == 6 && (0 <= m && m < 1))
            return (1);
    return (0);
}

int alert_sound(int pin)
{
    int count = 0;
    while (count <= 3)
    {
        analogWrite(pin,10);
        delay(100);
        analogWrite(pin,0);
        delay(100);
        count++;
    }
    return (0); // turn on the display
}    

int db_state;
int laststate = 1;
void setup() {
  Wire.begin(21, 22);
  rtc.begin();
//  dht.begin();
  Serial.begin(115200);
  pinMode(ALERT,OUTPUT);
  pinMode(DB_PIN,INPUT_PULLUP);
  analogWrite(ALERT,0);
  delay(2000);
}
void loop() {
  DateTime now = rtc.now();
  int h = now.hour();
  int m = now.minute();
 int hum = dht11.readHumidity();
  int  temp = dht11.readTemperature();
  checkdht(hum,temp);
  db_state = digitalRead(DB_PIN);

  // HHMM dis // 
  int value = h * 100 + m;
  display.showNumberDecEx(value, 0b01000000, true);

  laststate = check_button_state(db_state,laststate);
  if (check_alert(h,m))
      {
          laststate = check_button_state(0,0);
          alert_sound(ALERT);
      }

      // i want to 
//  display.showNumberDecEx(temp, 0b01000000, true);
//  printf("the current time is :%d\n",value);
//    printf("the db_state and laststate is  %d : %d\n",db_state, laststate);
  delay(1000);
}



/*
TM1637（4桁表示）
VCC → 3.3V or 5V
GND → GND
CLK → GPIO18
DIO → GPIO19
DS3231（時間）
SDA → GPIO21
SCL → GPIO22
VCC → 3.3V
GND → GND
*/
