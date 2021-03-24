#include "ESP32_RDP.h"

ESP32car car;

int mode = 1;

void setup() {
}

void loop() {
  switch (mode)
  {
    case 1:
      car.avoid(40, 30);
      break;
    case 2:
      car.follow(40, 30);
      break;
    case 3:
      car.is_on_edge(110);
      break;
    case 4:
      car.track_line(400 , 50);
      break;
  }
}
