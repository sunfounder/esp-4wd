#include "ESP32_RDP.h"

Ultrasonic ult(13,12);
float dis;

void setup() {
  Serial.begin(115200);
}

void loop() {
  dis = ult.read_distance();
  Serial.printf("distance: %.2f \n",dis);
  delay(100);
}
