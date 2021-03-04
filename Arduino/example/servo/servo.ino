#include "ESP32_RDP.h"

Servo servo(27);
void setup() {
  // put your setup code here, to run once:
  servo.set_angle(-30);
  delay(1000);
  servo.set_angle(30);
  delay(1000);
  servo.set_angle(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  

}
