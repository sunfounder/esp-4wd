import esp32_rdp as car
import time

def main():
    car.move("forward", 30)
    time.sleep(1)
    car.move("backward", 30)
    time.sleep(1)
    car.move("left", 30)
    time.sleep(1)
    car.move("right", 30)
    time.sleep(1)
    car.move("stop")

try:
    main()
finally:
    car.move("stop")