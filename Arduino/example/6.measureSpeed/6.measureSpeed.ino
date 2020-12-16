#include "ESP32_RDP.h"

ESP32car car;

#define SPEED_PIN_LEFT    26
#define SPEED_PIN_RIGHT    25

hw_timer_t * timer = NULL;
volatile uint8_t left_Counter = 0;
volatile uint8_t right_Counter = 0;
int counter = 0;
float carSpeed = 0;

void on_left_Pin() {
  left_Counter++;
}
void on_right_Pin() {
  right_Counter++;
}
void IRAM_ATTR onTimer() {
  counter = (left_Counter + right_Counter);
  left_Counter = 0;
  right_Counter = 0;
}

float get_speed() {
  float value = 0;
  value = float(counter) / 2.0 / 20.0 * 2.0 * 3.14 * 3.3;
  return value;
}

void setup() {
  Serial.begin(115200);
  pinMode(SPEED_PIN_LEFT, INPUT);
  attachInterrupt(SPEED_PIN_LEFT, on_left_Pin, RISING);
  pinMode(SPEED_PIN_RIGHT, INPUT);
  attachInterrupt(SPEED_PIN_RIGHT, on_right_Pin, RISING);
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
  // info).
  timer = timerBegin(2, 80, true);
  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer, true);
  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter)
  timerAlarmWrite(timer, 1000000, true);
  // Start an alarm
  timerAlarmEnable(timer);
}

void loop() {
  int speed = random(100);
  car.move("forward", speed);
  carSpeed = get_speed();
  Serial.println(carSpeed);
  delay(1000);
}
