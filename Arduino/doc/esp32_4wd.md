## Install the required libraries 
- Open Arduino IDE in File -> Preferences -> Additional Boards Manager URLs , add this URL: "https://dl.espressif.com/dl/package_esp32_index.json". Then in Tools -> Board -> Boards Manager ,  search "esp32" and install. When upload program choose board: "NodeMCU-32s".
- in Sketch -> include Library -> Library Manager:
 Seach "WebSockets" and install (by Markus Sattler). 
 Seach "Adafruit NeoPixel" and install.
 Seach "ArduinoJson" and install.
- in Sketch -> include Library  -> add .ZIP Library: add “ src ” folder. 

## Library API
ESP32_RDP.h
- class Ultrasonic
```
Ultrasonic(int triggerPin, int echoPin); // create ultrasonic object : Ultrasonic us(13,12);
float read_distance(void);  //read distance funtion
```
- class Servo
```
Servo(int pin);   // create servo object
void set_angle(int angle);  // set servo angle ,range is -90 to 90
```
- class Motor
```
Motor(int a_pin, int b_pin); // create motor object
void set_power(int power); 
```
- class Picar //Preset function library 
```
Picar();  //create car object: Picar car;
int wheel_reverse_value[4] = {-1, 1, -1, 1}; //The calibration value of wheel direction corresponds to left front, right front ,left rear ,right rear wheel
void move(string dir, int speed = 0);  //car move funtion, Optional argument dir include("forward","backward","left","right","stop"),speed range is 0-100
void avoid(int speed); //car avoid funtion
void get_angle_distance(void);  //Distance measurement by imitating radar with ultrasonic wave
int angle_distance[2];  //Return the corresponding angle data [angle, distance]
void track_line(int ref, int speed); //track line funtion
void is_on_edge(int ref); //Cliff inspection funtion
void follow(int ref, int speed); //Car simulation follow funtion
void set_light_color(int red, int green, int blue); //Turn on the light bar all lights funtion Parameter passes three bit RGB value
void set_num_light(int num, int red, int green, int blue);  //Turn on individual lights funtion.Parameter: num is position
void set_light_off(void); //Turn off light bar funtion
void get_grayscale(void);  // Get the value of the grayscale sensor
int adc_value[3]; //Return value of the grayscale sensor
```






