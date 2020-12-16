import esp32_rdp as car

mode = 1

def main():
    while True:
        global mode
        if mode == 1:
            car.avoid(40,30)
        elif mode == 2:
            car.follow(40,30)
        elif mode == 3:
            car.is_on_edge(110)
        elif mode == 4:
            car.track_line(400,50)

if __name__ == "__main__":
    try:
        main()
    except:
        car.move("stop")