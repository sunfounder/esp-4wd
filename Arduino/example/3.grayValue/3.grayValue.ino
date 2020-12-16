#include "ESP32_RDP.h"

ESP32car car;

int grayValue[3] = {0};

void setup() {
  Serial.begin(115200);
}

void loop() {
  car.get_grayscale();
  for (int i = 0; i < 3; i++) {
    grayValue[i] = car.adc_value[i];
  }
  Serial.printf("grayValue:");
  Serial.printf(" %d", grayValue[0]);
  Serial.printf("  %d", grayValue[1]);
  Serial.printf("  %d\n", grayValue[2]);
  delay(100);
}
