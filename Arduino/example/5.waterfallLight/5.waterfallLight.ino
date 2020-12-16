#include "ESP32_RDP.h"

ESP32car car;

void setup() {
}

void loop() {
  int red = random(255);
  int green = random(255);
  int blue = random(255);
  for (int i = 0; i < 24; i++)
  {
    car.set_num_light(i, red, green, blue);
    delay(20);
  }
  for (int i = 23; i > 11; i--)
  {
    int j = 23 - i;
    car.set_num_light(i, 0, 0, 0);
    car.set_num_light(j, 0, 0, 0);
    delay(40);
  }
  for (int i = 23; i >= 0; i--)
  {
    car.set_num_light(i, red, green, blue);
    delay(20);
  }
  for (int i = 23; i > 11; i--)
  {
    int j = 23 - i;
    car.set_num_light(i, 0, 0, 0);
    car.set_num_light(j, 0, 0, 0);
    delay(40);
  }
}
