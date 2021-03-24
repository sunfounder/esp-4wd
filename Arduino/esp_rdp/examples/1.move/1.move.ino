#include "ESP32_RDP.h"

ESP32car car;

void setup() {
  car.move("forward", 30);
  delay(1000);
  car.move("backward", 30);
  delay(1000);
  car.move("left", 30);
  delay(1000);
  car.move("right", 30);
  delay(1000);
  car.move("stop");
}

void loop() {
}
