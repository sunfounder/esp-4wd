## Sunfounder Controller Description
### APP_Seting
- Enter the app, you can add your own custom remote control handle. Enter the edit interface, the controls are corresponding to A-Q 17 areas, each area can select the desired control.Controls available for the rectangular area are sliders, dials, ultrasonic radar-like scanning and grayscale detection.Controls available in the small square area are digital displays, switches and buttons, with the two large areas K and Q available as a cross-shaped steering wheel and joystick.
- Each control can be named by clicking on the settings in the top right corner, where the dial can set the maximum value, minimum value and units, and the slider can set the maximum value, minimum value and initial value.The grayscale detection control can set cliff detection thresholds and car track line thresholds.

### Arduino app_control
- After customizing the app remote control, you need to program the corresponding websocket server in the Arduino IDE to receive the data sent by the app and process it and execute the corresponding car functions.The app sends control values corresponding to all regions each time, each with a corresponding subscript and value (dict format in python, struct format in C), sending object strings like this:
```C
{"A_region":0,"B_region":null,"C_region":null,"D_region":null,"E_region":null,"F_region":false,"G_region":null,"H_region":50,"I_region":null,"J_region":null,"K_region":"stop","L_region":[110,400],"N_region":null,"O_region":null,"P_region":null,"Q_region":[0,0],"M_region":false}
```
- Enter the value sent by the control：The values of the corresponding areas of the dial, numeric display and radar scan controls are not required.The value of the area corresponding to the grayscale sensor is a two-digit shaped array with the first digit of the array used for the cart cliff detection calibration value and the second digit used for the cart track line calibration value.
- Output the value sent by the control：The slider control sends the current value of the int type. Switches and buttons send the current state value as a bool,send true when open and send false when close.The data sent from the cross-shaped steering wheel in the K-area and Q-area is a string, and the string sent from each direction is "forward" in the up, "left" in the left, "backword" in the down, and "right" in the right.The joystick control sends a two-digit shaped array of values [0, 0], the first of which is the value in the horizontal direction, corresponding to 0-100 when moving to the right and 0 to -100 when moving to the left.The second value of the array is the value in the vertical direction, from 0 to 100 for upward values and from 0 to -100 for downward values.
- null is sent with the subscript string if the control is not set in the region.
- In the app_control arduino program, define the global variables cart WiFi name, password, temporary string for sending data, create cart function class object, create websockets object and open up a space for storing json objects for sending and receiving data.In the setup function, write the WiFi name into the initial string, then ESP32 selects AP mode (access point mode) to turn on the hotspot, start the websocket service and specify the callback function.The code is as follows：
```C
#define NAME "PiCar-4WD"
// Constants
const char *ssid = NAME;
const char *password =  "123456789";
ESP32car car;
WebSocketsServer webSocket = WebSocketsServer(8765);
DynamicJsonDocument doc_send(1024);
DynamicJsonDocument doc_recv(1024);
String temp_send;

void setup() {
    String stringone = "{\'Name\':\"";
    String stringtwo = "\", \'Type\':\"PiCar-4WD\", \'Check\':\"SunFounder Controller\"}";
    temp_send = stringone + String(NAME) + stringtwo;
    Serial.begin(115200);
     // Start access point
    WiFi.softAP(ssid, password);
    // Print our IP address 
    Serial.println();
    Serial.println("AP running");
    Serial.print("My IP address: ");
    Serial.println(WiFi.softAPIP());
    //   Start WebSocket server and assign callback
    webSocket.begin(); 
    webSocket.onEvent(onWebSocketEvent);
}

```

- The carts can also be connected to the router WiFi by selecting STA mode (client mode) and then the remote control device connects to the same WiFi.Replacing the code corresponding to turning on the hotspot and the print message code in the  setup function.Replace the code as follows:
```C
// Connect to access point
  Serial.println("Connecting");
  WiFi.begin("MakerStarsHall", "sunfounder");  // Parameter: (ssid,password)
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }

  // Print our IP address
  Serial.println("Connected!");
  Serial.print("My IP address: ");
  Serial.println(WiFi.localIP());
  ```
- handles various event types in the callback function (onWebSocketEvent), and the function executes "case WStype_CONNECTED" event when the app connects.Here will send the initialized WiFi name and check value string in setup to APP for verification, APP will disconnect if the check fails, this can also print out the serial port information to see if there is a client connection.The code is as follows：
```C
case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_num);
        Serial.printf("[%u] Connection from ", client_num);
        Serial.println(ip.toString());
        webSocket.sendTXT(client_num, temp_send);
      }

```
- Execute "case WStype_TEXT" event if data is received in the callback function .The data is first parsed into a json object, similar to a structured object that gets its corresponding value from the subscript element.If we define the K area as the cross-shaped steering wheel control and the H area as the slider bar in the app remote control, we can use the subscripts of these two areas to get values to process the corresponding functions.For example, if we want the K region to control the car to move, and the H region to control the car's power, we call the car function move to execute.(What APIs are available in the cart library are described in the cart documentation.) The code is as follows：

```C
case WStype_TEXT:
    deserializeJson(doc_recv, payload);
    car.move(doc_recv["K_region"], doc_recv["H_region"]);
```
- Another example is to set a switch in the M area to control the bottom light state of the car, we can call the "set_light_color" library function to turn on all lights.The code is as follows：
```C
if(doc_recv["M_region"]) 
      {
        if(! led_status)  //Adding flags to prevent function duplication
        {
          car.set_light_color(50,100,10);
          led_status = true;
        }
      }
      else 
      {
        if(led_status)
        {
          car.set_light_off();
          led_status = false;
        }
      }
```
- To send data to the app client, we also send in the "case WStype_TEXT" event in the callback function, thus acting as a responsive communication.First, convert the initial temp_send string into a json object to facilitate the direct assignment of the subscript string to the corresponding region.After all the assignments are done, the json object is converted back to a string at the end because webscoket's send function can only send character variables.For example, to send the value measured by the car speed module to area A.（Car speedometer uses interrupts to get in the web control example）To send the angle and ultrasonic distance required by the radar scan control to region D, call the get function from the library and assign the values from the class to the corresponding region subscript.The code is as follows：
```C
deserializeJson(doc_send, temp_send);  
doc_send["A_region"] = get_speed();  
car.get_angle_distance();
doc_send["D_region"][0] = car.angle_distance[0]; 
doc_send["D_region"][1] = car.angle_distance[1]; 
serializeJson(doc_send, output);
webSocket.sendTXT(client_num, output); 
```

### Sunfounder control connect to car
- Upload the written websocket server code, then  the device to connect the car's WiFi, open the app click the auto connect button in the top right corner to connect the websocket。Go to the customizable remote control page and click the start button in the top right corner to remote control the cart.

