## Sunfounder Controller Description
### APP_Seting
- Enter the app, you can add your own custom remote control handle. Enter the edit interface, the controls are corresponding to A-Q 17 areas, each area can select the desired control.Controls available for the rectangular area are sliders, dials, ultrasonic radar-like scanning and grayscale detection.Controls available in the small square area are digital displays, switches and buttons, with the two large areas K and Q available as a cross-shaped steering wheel and joystick.
- Each control can be named by clicking on the settings in the top right corner, where the dial can set the maximum value, minimum value and units, and the slider can set the maximum value, minimum value and initial value.The grayscale detection control can set cliff detection thresholds and car track line thresholds.

### Micropython app_control
- After customizing the app remote control, you need to program the corresponding websocket server to receive the data sent by the app and process it and execute the corresponding car functions.The app sends control values corresponding to all regions each time, each with a corresponding subscript and value, sending dict like this:
```python
{"A_region":0,"B_region":null,"C_region":null,"D_region":null,"E_region":null,"F_region":false,"G_region":null,"H_region":50,"I_region":null,"J_region":null,"K_region":"stop","L_region":[110,400],"N_region":null,"O_region":null,"P_region":null,"Q_region":[0,0],"M_region":false}
```
- Enter the value sent by the control：The values of the corresponding areas of the dial, numeric display and radar scan controls are not required.The value of the area corresponding to the grayscale sensor is a two-digit shaped array with the first digit of the array used for the cart cliff detection calibration value and the second digit used for car black line detection calibration value.
- Output the value sent by the control：The slider control sends the current value of the int type. Switches and buttons send the current state value as a bool,send true when open and send false when close.The data sent from the cross-shaped steering wheel in the K-area and Q-area is a string, and the string sent from each direction is "forward" in the up, "left" in the left, "backword" in the down, and "right" in the right.The joystick control sends a two-digit shaped array of values [0, 0], the first of which is the value in the horizontal direction, corresponding to 0-100 when moving to the right and 0 to -100 when moving to the left.The second value of the array is the value in the vertical direction, from 0 to 100 for upward values and from 0 to -100 for downward values.
- null is sent with the subscript string if the control is not set in the region.
- In the app_control example,'ws' is the websockets library from which we can call the read and write functions.In the main function, we continuously process the received data to execute the corresponding functionand, and we can customize the corresponding remote control app here.
For example, if we want the K region to control the car to move, and the H region to control the car's power, we call the car function move to execute.To send the angle and ultrasonic distance required by the radar scan control to region D, call the get function from the library and assign the values from the library to the corresponding region subscript.(What APIs are available in the cart library are described in the 'esp32_rdp.md')Finally, the send data function is called. The code is as follows：
```python
def main():
    ws.start()
    print("start")
    led_status = False
    while True:
        result = read()
        if result != None:
            car.move(result['K_region'], result['H_region'])
            car.get_angle_distance()
            ws.send_dict['D_region'] = car.angle_distance
            write()
        
        time.sleep_ms(15)
```

- The carts can also be connected to the router WiFi by selecting STA mode (client mode) and then the remote control device connects to the same WiFi.Replacing the code corresponding to turning on the hotspot in the  'ws.py' start function, then modify the variables NAME and PASSWARD to your WIFI ssid and passward.Replace the code as follows:
```python
self.wlan = network.WLAN(network.STA_IF)
self.wlan.active(True)
self.wlan.connect(NAME, PASSWARD)
for _ in range(5):
    if self.wlan.isconnected():
        print('network config:', self.wlan.ifconfig())
        break
    time.sleep(1)
if not self.wlan.isconnected():
    print("wifi connected fail ")
self.setup_conn(self.accept_conn)
```


### Sunfounder control connect to car
- Upload the written websocket server code, then  the device to connect the car's WiFi, open the app click the auto connect button in the top right corner to connect the websocket。Go to the customizable remote control page and click the start button in the top right corner to remote control the cart.

