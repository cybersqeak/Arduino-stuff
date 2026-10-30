#include "light.hpp"

void print_status(t_info *info)
{
    Serial.println("\n========== DAWN LIGHT STATUS ==========");

    Serial.printf("Current time: %02d:%02d\n",
                  info->currentMinutes / 60,
                  info->currentMinutes % 60);

    Serial.printf("led_mode[0] (morning): %s\n",
                  info->led_mode[0] ? "ON" : "OFF");

    Serial.printf("led_mode[1] (bedtime): %s\n",
                  info->led_mode[1] ? "ON" : "OFF");

    Serial.printf("led_mode[2] (sensor): %s\n",
                  info->led_mode[2] ? "ON" : "OFF");

    Serial.printf("sensor_detected: %s\n",
                  info->sensor_detected ? "true" : "false");

//    Serial.printf("sensor_enable: %s\n",
 //                 info->sensor_enable ? "true" : "false");

    Serial.printf("Physical sensor pin: %d\n",
                  info->sensor_pin);

  //  Serial.printf("brightness: %d\n", info->brightness);
    Serial.printf("start_t: %lu ms\n", info->start_t);
    Serial.printf("elapsed_t: %lu ms\n", info->elapsed_t);
    Serial.printf("millis(): %lu ms\n", millis());

    Serial.println("=======================================");
}


