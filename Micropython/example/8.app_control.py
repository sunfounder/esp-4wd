from ws import WS_Server
import json
import time
import esp32_rdp as car



ws = WS_Server(8765)
speed = car.Speed(26, 25)

def write():
    ws.write(json.dumps(ws.send_dict))
    #print(ws.send_dict)
    return

def read():
    recv = ws.read()
    if recv == None:
        return
    tmp = json.loads(recv)
    #print("tmp: %s"%tmp)
        
    return tmp




def main():
    ws.start()
    print("start")
    led_status = False
    while True:
        result = read()
        if result != None:
            car.move(result['K_region'], result['H_region'])
            if result['M_region']:
                if not led_status:
                    car.set_light_color([100, 100, 100])
                    led_status = True
            else:
                if led_status:
                    car.set_light_off()
                    led_status = False
            ws.send_dict['A_region'] = speed.get_speed()
            car.get_angle_distance()
            ws.send_dict['D_region'] = car.angle_distance
            ws.send_dict['L_region'] = car.get_grayscale_list()
            write()
        
        time.sleep_ms(15)

#main()

if __name__ == "__main__":
    try:
        main()
    except:
        ws.stop()