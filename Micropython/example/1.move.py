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

if __name__ == "__main__":
    try:
        main()
    except:
        car.move("stop")