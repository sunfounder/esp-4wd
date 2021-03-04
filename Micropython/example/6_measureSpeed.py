import esp32_rdp as car
import random
import time

speed = car.Speed(26, 25)

def main():
    while True:
        car.move("forward",random.randint(0,100))
        time.sleep(1)
        carSpeed = speed.get_speed()
        print('distance:%d' % carSpeed)

try:
    main()
finally:
    car.move("stop")