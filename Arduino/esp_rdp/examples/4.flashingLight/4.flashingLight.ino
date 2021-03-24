#include "ESP32_RDP.h"

ESP32car car;

void setup() {
}

void loop() {
  car.set_light_color(random(255), random(255), random(255));
  delay(500);
  car.set_light_off();
  delay(500);
}
