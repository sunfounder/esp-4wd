import esp32_rdp as car
import random
import time

def main():
    while True:
        color = [random.randint(0,255),random.randint(0,255),random.randint(0,255)]
        car.set_light_color(color)
        time.sleep(0.5)
        car.set_light_off()
        time.sleep(0.5)

if __name__ == "__main__":
    try:
        main()
    except:
        car.set_light_off()
