from machine import Timer, Pin, PWM, ADC, time_pulse_us
import time
import neopixel

PERIOD = 20
pin_list = [
    #[obj, pw, status]
]

_counter = False
_tick_count = 0
_tim = Timer(2)

pin = None
_pulse_width = 0

def tick(ch):
    global  _counter, _tick_count, pin_list, pin
    for i in range(len(pin_list)):
        if _tick_count == pin_list[i][1]:
            if pin_list[i][2]:
                pin_list[i][0].off()
                pin_list[i][2] = False
                # print("on counter %d off pin %d", _tick_count, i)
        elif _tick_count == 0:
            if pin_list[i][1] > 0:
                pin_list[i][0].on()
                pin_list[i][2] = True
                # print("on counter %d on pin %d", _tick_count, i)
        
    _tick_count += 1
    if _tick_count > 20:
       _tick_count = 0

_tim.init(period=1, mode=Timer.PERIODIC, callback=tick)
        

class SoftPWM(object):
    def __init__(self, pin):
        global pin_list
        pin_list.append([Pin(pin, Pin.OUT), 0, False])
        self.ch = len(pin_list) - 1
        
    def duty(self, value):
        global pin_list, PERIOD
        pw = int(value / 100 * PERIOD)
        pin_list[self.ch][1] = pw

class Speed():
    def __init__(self, pin1, pin2):
        self.left_counter = 0
        self.right_counter = 0
        self.counter = 0
        left_pin = Pin(pin1, Pin.IN)
        right_pin = Pin(pin2, Pin.IN)
        self.tim = Timer(0)
        left_pin.irq(trigger=Pin.IRQ_RISING, handler=self.on_left)
        right_pin.irq(trigger=Pin.IRQ_RISING, handler=self.on_right)
        self.tim.init(period=1000, mode=Timer.PERIODIC, callback=self.on_timer)
        
        
        
    def on_left(self, ch):
        self.left_counter += 1
        
    
    def on_right(self, ch):
        self.right_counter += 1
        
    def on_timer(self, ch):
        self.counter = self.left_counter + self.right_counter
        self.left_counter = 0
        self.right_counter = 0
        
    def get_speed(self):
        value = self.counter / 2.0 / 20.0 * 2.0 * 3.14 * 3.3
        return value
    
    
    
def mapping(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

class Servo():
    MAX_PW = 2500
    MIN_PW = 500
    PERIOD = 1024
    
    def __init__(self, pin):
        self.servo = PWM(Pin(pin, Pin.OUT), freq=50)
        
    def set_angle(self, angle):
        try:
            angle = int(angle)
        except:
            raise ValueError("Angle value should be int value, not %s"%angle)
        if angle < -90:
            angle = -90
        if angle > 90:
            angle = 90
        High_level_time = mapping(angle, -90, 90, self.MIN_PW, self.MAX_PW)
        pwr =  High_level_time / 20000
        value = int(pwr*self.PERIOD)
        self.servo.duty(value)


class Ultrasonic():
    def __init__(self, trig_Pin, echo_Pin):
        """Initialize Input(echo) and Output(trig) Pins."""
        self._trig = Pin(trig_Pin, Pin.OUT)
        self._echo = Pin(echo_Pin, Pin.IN)
        self._sound_speed = 340.0  # m/s

    def _pulse(self):
        """Trigger ultrasonic module with 10us pulse."""
        self._trig.on()
        time.sleep_us(10)
        self._trig.off()

    def get_distance(self):
        """Measure pulse length and return calculated distance [cm]."""
        self._pulse()
        pulse_width_s = time_pulse_us(self._echo, Pin.on) / 10000
        #print(pulse_width_s)
        dis = (pulse_width_s / 2.0) * self._sound_speed
        return dis


class Motor():
    def __init__(self, pin_a, pin_b):
        self.pin_1 = SoftPWM(pin_a)
        self.pin_2 = SoftPWM(pin_b)
        

    def set_power(self, power):
        if power > 0:
            self.pin_1.duty(0)
            self.pin_2.duty(power)
        elif power < 0:
            self.pin_1.duty(abs(power))
            self.pin_2.duty(0)
        else:
            self.pin_1.duty(0)
            self.pin_2.duty(0)



np =  neopixel.NeoPixel(Pin(14, Pin.OUT), 24)
        

def set_light_color(color):
    for i in range(24):
        np[i] = [color[0], color[1], color[2]]
    np.write()
    
def set_num_color(num, color):
    np[num] = [color[0], color[1], color[2]]
    np.write()
    
def set_light_off():
    for i in range(24):
        np[i] = [0, 0, 0]
    np.write()


gs0 = ADC(Pin(35))
gs1 = ADC(Pin(34))
gs2 = ADC(Pin(36)) 
servo_lib = Servo(27)
us_lib = Ultrasonic(13, 12)


# Grayscale 
def get_grayscale_list():
    adc_value_list = []
    adc_value_list.append(gs0.read())
    adc_value_list.append(gs1.read())
    adc_value_list.append(gs2.read())
    return adc_value_list

def is_on_edge(ref):
    ref = int(ref)
    gs_list = get_grayscale_list()
    if gs_list[2] <= ref or gs_list[1] <= ref or gs_list[0] <= ref:  
        move("backward", 40)
        time.sleep(0.5)
        move("stop")
    

def get_line_status(ref,fl_list):#170<x<300
    ref = int(ref)
    if fl_list[1] <= ref:
        return 0
    
    elif fl_list[0] <= ref:
        return -1

    elif fl_list[2] <= ref:
        return 1     
    
# Ultrasonic
ANGLE_RANGE = 180
STEP = 18
us_step = STEP
angle_distance = [0,0]
current_angle = 0
max_angle = ANGLE_RANGE/2
min_angle = -ANGLE_RANGE/2
scan_list = [] 

def get_distance_at(angle):
    global angle_distance
    servo_lib.set_angle(angle)
    time.sleep(0.04)
    distance = us_lib.get_distance()
    angle_distance = [angle, distance]
    return distance

def get_status_at(angle, ref1=35, ref2=7):
    dist = get_distance_at(angle)
    if dist > ref1 or dist == -2:
        return 2
    elif dist > ref2:
        return 1
    else:
        return 0

def get_angle_distance():
    global scan_list, current_angle, us_step
    current_angle += us_step
    if current_angle >= max_angle:
        current_angle = max_angle
        us_step = -STEP
    elif current_angle <= min_angle:  
        current_angle = min_angle
        us_step = STEP
    get_distance_at(current_angle)

def scan_step(ref):
    global scan_list, current_angle, us_step
    current_angle += us_step
    if current_angle >= max_angle:
        current_angle = max_angle
        us_step = -STEP
    elif current_angle <= min_angle:  
        current_angle = min_angle
        us_step = STEP
    status = get_status_at(current_angle, ref1=ref)#ref1

    scan_list.append(status)
    if current_angle == min_angle or current_angle == max_angle:
        if us_step < 0:
            # print("reverse")
            scan_list.reverse()
        # print(scan_list)
        tmp = scan_list.copy()
        scan_list = []
        return tmp
    else:
        return False
    
left_front = Motor(23, 22) # motor 1
right_front = Motor(21, 19) # motor 2
left_rear = Motor(18, 17) # motor 3
right_rear = Motor(16, 4) # motor 4
cali_dir_value = [-1, 1, -1, 1]

def motor_direction_calibration(motor, value):
    # 0: positive direction
    # 1:negative direction
    global cali_dir_value
    motor -= 1
    if value == 1:
        cali_dir_value[motor] = -1*cali_dir_value[motor]


def move(dir, speed=0):
    if dir == "forward":
        left_front.set_power(cali_dir_value[0] * speed)
        right_front.set_power(cali_dir_value[1] * speed)
        left_rear.set_power(cali_dir_value[2] * speed)
        right_rear.set_power(cali_dir_value[3] * speed)
    elif dir == "backward":
        left_front.set_power(- cali_dir_value[0] * speed)
        right_front.set_power(- cali_dir_value[1] * speed)
        left_rear.set_power(- cali_dir_value[2] * speed)
        right_rear.set_power(- cali_dir_value[3] * speed)
    elif dir == "left":
        left_front.set_power(- cali_dir_value[0] * speed)
        right_front.set_power(cali_dir_value[1] * speed)
        left_rear.set_power(- cali_dir_value[2] * speed)
        right_rear.set_power(cali_dir_value[3] * speed)
    elif dir == "right":
        left_front.set_power(cali_dir_value[0] * speed)
        right_front.set_power(- cali_dir_value[1] * speed)
        left_rear.set_power(cali_dir_value[2] * speed)
        right_rear.set_power(- cali_dir_value[3] * speed)
    else:
        left_front.set_power(0)
        right_front.set_power(0)
        left_rear.set_power(0)
        right_rear.set_power(0)
        
def track_line(ref, speed):
    gs_list = get_grayscale_list()
    if get_line_status(ref,gs_list) == 0:
        move("forward", speed)      
    elif get_line_status(ref,gs_list) == -1:
        move("left", speed)
    elif get_line_status(ref,gs_list) == 1:
        move("right", speed)   
        
def avoid(ref, speed):
    scan_list = scan_step(ref)
    if scan_list:
        tmp = scan_list[3:7]
        if tmp != [2,2,2,2]:
            move("right", speed)
        else:
            move("forward", speed)

def follow(ref, speed):
    scan_list = scan_step(ref)
    if scan_list != False:
        scan_list = [str(i) for i in scan_list]
        scan_list = "".join(scan_list)
        paths = scan_list.split("2")
        length_list = []
        for path in paths:
            length_list.append(len(path))
        if max(length_list) == 0:
            move("stop") 
        else:
            i = length_list.index(max(length_list))
            pos = scan_list.index(paths[i])
            pos += (len(paths[i]) - 1) / 2
            delta = len(scan_list) / 3
            if pos < delta:
                move("left", speed)
            elif pos > 2 * delta:
                move("right", speed)
            else:
                if scan_list[int(len(scan_list)/2-1)] == "0":
                    move("backward", 100)
                else:
                    move("forward", speed)

def test():
    # servo1 = Servo(14)
    #speed = Speed(26, 25)
    while True:
    #     for i in range(-90, 90, 5):
    #         servo1.set_angle(i)
    #         time.sleep(0.1)
    #     for i in range(90, -90, -5):
    #         servo1.set_angle(i)
    #         time.sleep(0.1)
    # motor = Motor(23, 22)
    # motor.set_power(100)
    # time.sleep(3)
    # motor.set_power(-100)
    # time.sleep(3)
    # motor.set_power(0)
    # time.sleep(1)
    # print("red")
    # set_light_color([50, 0, 0])
    # time.sleep(2)
    # set_light_off()
    # print("demo")
    # demo()
    # print("forward")
    # move("forward", 100)
    # time.sleep(5)
    # print("stop")
    # move("stop")
        dis = us_lib.get_distance()
        print("dis%d"%dis)
        time.sleep(1)
            
#test()