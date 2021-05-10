from esp32_rdp import servo_lib
import time

def main():
    servo_lib.set_angle(-30)
    time.sleep(1)
    servo_lib.set_angle(30)
    time.sleep(1)
    servo_lib.set_angle(0)

main()