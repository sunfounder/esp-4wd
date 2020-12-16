# esp32_rdp - basic driver

## Class SoftPWM

Usage:
```python
from esp32_rdp import SoftPWM

pwm1 = SoftPWM(23)  # Creating PWM Objects,Parameter is Pin
pwm1.duty(50)  # Set Duty Cycle

```
### Methods
<!--input:value is duty cycle,range is 0-100   -->
- duty - set duty cycle
```python
SoftPWM.duty(value)
```

## Class Speed
Usage:
```python
from esp32_rdp import Speed
speed = Speed(26, 25)  # Creating Velocimetry Objects,Parameter is Pin
value = speed.get_speed() # Get the current measured speed
```
### Methods
<!--output: current measured speed,The unit is Cm/s  -->
- get_speed - Get the current measured speed
```python
Speed.get_speed()
```

## Class Servo
Usage:
```python
from esp32_rdp import Servo 
servo = Servo(27) # Creating Velocimetry Objects,Parameter is Pin
servo.set_angle(20) # set angle
```
### Methods
<!--input:angle is Servo rotation angle,range is -90 - 90   -->
- set_angle
```python
Servo.set_angle(angle)
```

## Class Ultrasonic
Usage:
```python
from esp32_rdp import Ultrasonic
us = Ultrasonic(13, 12) # Creating Ultrasonic Objects,Parameter is trig_Pin and echo_Pin
us.get_distance() # Get the current measured distance
```
### Methods
<!--output: the current measured distance,The unit is Cm -->
- get_distance
```python
Ultrasonic.get_distance()
```

## Class Motor
Usage:
```python
from esp32_rdp import Motor
motor = Motor(23, 22)# Creating Motor Objects,Parameter is two pins
motor.set_power # set current power
```
### Methods
<!--input:power is motor speed,range is -100 - 100,
Negative values are motor reversal   -->
- set_power
```python
Motor.set_power(power)
```

## The functions
Usage:
```python
import esp32_rdp as car
car.set_light_color([100, 100, 100]) #Turn on all lights in the light bar,Parameter is RGB color
car.get_grayscale_list() # get the data of grayscale
```

### Methods
<!--input:color is RGB value,list[R, G, B],RGB is 0 - 255 -->
- set_light_color - Turn on all lights in the light bar
```python
car.set_light_color(color)
```
<!--input:“num” is which light want to turn on, color is RGB value,list[R, G, B],RGB is 0 - 255 -->
- set_num_color
```python
car.set_num_color(num, color)
```
- set_light_off - turn off  all lights
```python
car.set_light_off()
```
- get_grayscale_list - get the data of grayscale
```python
adc_list = []
adc_list = car.get_grayscale_list()
```
<!--input:ref is Overhead Detection Calibration value, gs_list is the data of grayscale-->
- is_on_edge - Overhead Detection 
```python
status = car.is_on_edge(ref, gs_list)
```
<!--input:ref is back line Detection Calibration value, gs_list is the data of grayscale-->
- get_line_status(ref,fl_list) - get the line status.
```python
status = car.get_line_status(ref,fl_list) 
```
<!--input: angle is radar Current Angle-->
- get_distance_at(angle) - get the angle and distance.
```python
ad_list = []
ad_list = get_distance_at(angle) 
```
<!--input: angle is radar Current Angle-->
- get_status_at(angle, ref1=35, ref2=10) - get the status of distance.
```python
status = get_status_at(angle) 
```
<!--input: ref is distance calibration
 output: status list-->
- scan_step(ref) - scan a range of angle.
```python
scan_step() 
```
<!--input: dir is Movement Direction("forward","backward","left", "right"), speed range is 0-100-->
- move - car move
```python
car.move(dir, speed=0)
```
<!--input:ref is back line Detection Calibration value, speed range is 0-100-->
- track_line - car track line
```python
car.track_line(ref, speed)
```
<!--input:speed range is 0-100-->
- avoid - car Obstacle Avoidance
```python
car.avoid(speed)
```
<!--input:ref is distance calibration value,speed range is 0-100-->
- follow - car follow by Ultrasonic
```python
car.follow(ref, speed))
