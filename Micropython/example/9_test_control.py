from ws import WS_Server
import json
import time
import esp32_rdp as car



ws = WS_Server(8765) # init websocket 
temp = None
temp_send = None


#  websocket recevice data
def read():
    global temp
    recv = ws.read()
    if recv == None:
        return
    recv_data = json.loads(recv)
    if temp != recv_data:
        print("recv_data: %s\n"%recv_data)
        temp = recv_data        
    return recv_data

# websocket send data
def write():
    global temp_send
    ws.write(json.dumps(ws.send_dict))
    if temp_send != ws.send_dict:
        print("send_data:%s\n"%ws.send_dict)
        temp_send = ws.send_dict.copy
    return

def main():
    ws.start()
    print("start")
    while True:
        result = read()
        if result != None:
            # coding the control function here.
            
            # coding the sensor function here.
            
            # ws.send_dict['L_region'] = car.get_grayscale_list() # example for test sensor date sending.
            write()
        time.sleep_ms(15)


try:
    main()
finally:
    ws.stop()