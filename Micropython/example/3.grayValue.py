import esp32_rdp as car
import time

grayValue = []

def main():
    while True:
        grayValue = car.get_grayscale_list()
        print('grayValue: %d %d %d' %(grayValue[0],grayValue[1],grayValue[2]))
        time.sleep(1)

if __name__ == "__main__":
    main()