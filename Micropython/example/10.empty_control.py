from ws import WS_Server
import json
import time
import esp32_rdp as car



ws = WS_Server(8765)
speed = car.Speed(26, 25)

def write():
    ws.write(json.dumps(ws.send_dict))
    return

def read():
    recv = ws.read()
    if recv == None:
        return
    tmp = json.loads(recv)
    return tmp




def main():
    ws.start()
    print("start")
    while True:
        result = read()
        if result != None:
            
            write()
        
        time.sleep_ms(15)

#main()

if __name__ == "__main__":
    try:
        main()
    except:
        ws.stop()