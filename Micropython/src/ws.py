# This module should be imported from REPL, not run from command line.
import socket
import uos
import network
import uwebsocket
import websocket_helper
import time
import json

NAME = 'esp32_4wd_micropython'
PASSWARD = "123456789"

# NAME = 'MakerStarsHall'
# PASSWARD = "sunfounder"




class WS_Server():
    
    # read -- <function>
    # readinto -- <function>
    # readline -- <function>
    # write -- <function>
    # ioctl -- <function>
    # close -- <function>
    send_dict = {
        'Name':NAME,
        'Type':'ESP-4WD Car',
        'Check':'SunFounder Controller',
        }

    def __init__(self, port):
        self.port = port
        self.listen_s = None
        self.client_s = None
        self.ws = None
        self.wlan = None
    
    def setup_conn(self, accept_handler):
        self.listen_s = socket.socket()
        self.listen_s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        ai = socket.getaddrinfo("0.0.0.0", self.port)
        addr = ai[0][4]

        self.listen_s.bind(addr)
        self.listen_s.listen(5)
        if accept_handler:
            self.listen_s.setsockopt(socket.SOL_SOCKET, 20, accept_handler)
        for i in (network.AP_IF, network.STA_IF):
            iface = network.WLAN(i)
            if iface.active():
                print("WebServer started on ws://%s:%d" % (iface.ifconfig()[0], self.port))
        return self.listen_s

    def accept_conn(self, listen_sock):
        cl, remote_addr = listen_sock.accept()
        print("\nWebSocket connection from:", remote_addr)
        self.client_s = cl
        websocket_helper.server_handshake(cl)
        self.ws = uwebsocket.websocket(cl, True)
        self.ws.write(json.dumps(self.send_dict))
        print("have sended!")
        cl.setblocking(False)

    def read(self):
        if self.ws == None:
            return None
        recv = self.ws.read()
        if recv != None and recv != b"":
            recv = recv.decode()
            # print("accept_conn: %s" % recv)
            return recv
        else:
            return None

    def write(self, value):
        value = value.encode()
        self.ws.write(value)

    def stop(self):
        if self.client_s:
            self.client_s.close()
        if self.listen_s:
            self.listen_s.close()
        self.wlan.active(False)

    def start(self):
        # self.stop()
        self.wlan = network.WLAN(network.AP_IF)
        self.wlan.config(essid=NAME, authmode=4, password=PASSWARD)
        self.wlan.active(True)  # turning on the hotspot
        # self.wlan = network.WLAN(network.STA_IF)
        # self.wlan.active(True)
        # self.wlan.connect(NAME, PASSWARD)
        # for _ in range(5):
        #     if self.wlan.isconnected():
        #         print('network config:', self.wlan.ifconfig())
        #         break
        #     time.sleep(1)
        # if not self.wlan.isconnected():
        #     print("wifi connected fail ")
        self.setup_conn(self.accept_conn)

    def start_foreground(self):
        self.stop()
        s = self.setup_conn(None)
        self.accept_conn(s)

