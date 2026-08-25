#include "system.h"


t_sys sys{0};

DHT dht(DHTPIN, DHTTYPE);  
RTC_DS3231 rtc;
TM1637Display display(CLK, DIO);  
void setup() {
 Serial.begin(115200);
  Wire.begin(21, 22);
  rtc.begin();
  dht.begin();

  pinMode(ALERT,OUTPUT);
  pinMode(DB_PIN,INPUT_PULLUP); pinMode(MODE_PIN,INPUT_PULLUP);
  analogWrite(ALERT,0);

  display.clear();   // <-- actually pushes the off-state to the chip
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  delay(2000);
 }



void loop() 
{
    if (!digitalRead(DB_PIN))
        {
            on_off(&sys);
            delay(300);
        }

    if (!digitalRead(MODE_PIN))
        {
            check_mode(&sys);
            delay(300);
        }
    alert_check(&info);
   
    Serial.print("\nThe switch_state ");
    Serial.printf("%d\n", sys.switch_state);

    Serial.print("\ndis.mode ");
    Serial.print(sys.dis.mode);   // t_mode is an enum, prints as its underlying int

    if (sys.switch_state == 0)
    {
        Serial.print("haha turn off");
        display.clear();   // <-- actually pushes the off-state to the chip
    }

    if (sys.switch_state == 1)
    {
        Serial.print("i am here");
        run(&sys);
    }
    delay(100);
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
