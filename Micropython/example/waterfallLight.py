import esp32_rdp as car
import random
import time

def main():
    while True:
        color = [random.randint(0,255),random.randint(0,255),random.randint(0,255)]
        noColor = []
        for i in range(24):
            car.set_num_color(i,color)
            time.sleep_ms(20)
        for i in range(23,11,-1):
            j = 23-i
            car.set_num_color(i, noColor)
            car.set_num_color(j, noColor)
            time.sleep_ms(40)
        for i in range(23,0,-1):
            car.set_num_color(i,color)
            time.sleep_ms(20)
        for i in range(23,11,-1):
            j = 23-i
            car.set_num_color(i,noColor)
            car.set_num_color(j,noColor)
            time.sleep_ms(40)

try:
    main()
finally:
    car.set_light_off()