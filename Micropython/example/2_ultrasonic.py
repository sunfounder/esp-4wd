import esp32_rdp as car
import time

ult = car.Ultrasonic(13,12)

def main():
    while True:
        distance = ult.get_distance()
        print('distance:%0.2f' % distance)
        time.sleep(0.1)

main()