import esp32_rdp as car
import time

servo = car.Servo(27)

def main():
    servo.set_angle(-30)
    time.sleep(1)
    servo.set_angle(30)
    time.sleep(1)
    servo.set_angle(0)

main()