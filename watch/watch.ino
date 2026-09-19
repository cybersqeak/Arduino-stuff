#include "system.h"


t_sys sys{0}; /* set alert time by default at 5:30 */

DHT dht(DHTPIN, DHTTYPE);  
RTC_DS3231 rtc;
TM1637Display display(CLK, DIO);  
void setup() {
 Serial.begin(115200);
  Wire.begin(21, 22);
  rtc.begin();
  dht.begin();
  sys.alert_time.hour = 5;
  sys.alert_time.minute= 30;
  pinMode(ALERT,OUTPUT);
  
  pinMode(DB_PIN,INPUT_PULLUP); 
  pinMode(MODE_PIN,INPUT_PULLUP);
  pinMode(ALERT_PIN,INPUT_PULLUP);
  pinMode(STOP_AT,INPUT_PULLUP);
  analogWrite(ALERT,0);

  display.clear();   
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  delay(2000);
 }



void loop() 
{
    DateTime now = rtc.now();
    sys.c_hour = now.hour();
    sys.c_min = now.minute();
    sys.c_time = sys.c_hour * 100 + sys.c_min;

    if (!digitalRead(DB_PIN))
        on_off(&sys), delay(300);
    if (!digitalRead(MODE_PIN))
        check_mode(&sys), delay(300);
    if (!digitalRead(ALERT_PIN))
        alert_assign(&sys),delay(300);

    check_alert(&sys); 
    check_light(&sys);
    check_stop_alert(&sys);

    Serial.print("\nThe switch_state ");
    Serial.printf("%d\n", sys.switch_state);

    Serial.print("\ndis.mode ");
    Serial.print(sys.dis.mode);   // t_mode is an enum, prints as its underlying int

    Serial.print("\nthe alert time is set to ");
    Serial.print(sys.alert_time.hour);
    Serial.print(": hour and");
    Serial.print(sys.alert_time.minute);
    Serial.print(" minute\n");


    if (sys.switch_state == 0)
    {
        Serial.print("haha turn off\n");
        display.clear();   // <-- actually pushes the off-state to the chip
    }

    if (sys.switch_state == 1)
    {
        Serial.print("haha  turned on\n");
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
