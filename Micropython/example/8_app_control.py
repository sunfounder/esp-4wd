from ws import WS_Server
import json
import time
import esp32_rdp as car



ws = WS_Server(8765) # init websocket 
speed = car.Speed(26, 25) # init speed measurement 

# websocket send data
def write():
    ws.write(json.dumps(ws.send_dict))
    #print(ws.send_dict)
    return

#  websocket recevice data
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
            
            #Move
            car.move(result['K_region'], result['H_region'])
            
            # RGB LED
            if result['M_region']:
                if not led_status:
                    car.set_light_color([100, 100, 100])
                    led_status = True
            else:
                if led_status:
                    car.set_light_off()
                    led_status = False
                    
            # speed measurement
            ws.send_dict['A_region'] = speed.get_speed()
            
            # radar
            car.get_angle_distance()
            ws.send_dict['D_region'] = car.angle_distance
            
            # greyscale
            ws.send_dict['L_region'] = car.get_grayscale_list()
            
            write()
        
        time.sleep_ms(15)


try:
    main()
finally:
    ws.stop()