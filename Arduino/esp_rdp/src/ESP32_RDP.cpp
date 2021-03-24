#include "ESP32_RDP.h"

Ultrasonic::Ultrasonic(int triggerPin, int echoPin)
{
	this->triggerPin = triggerPin;
    this->echoPin    = echoPin;
	pinMode(triggerPin, OUTPUT);
    pinMode(echoPin,    INPUT);
}

float Ultrasonic::read_distance(void)
{
	digitalWrite(this->triggerPin, 0);
    delayMicroseconds(2);


    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(this->triggerPin, 1);
    delayMicroseconds(10);
    digitalWrite(this->triggerPin, 0); 

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(this->echoPin, 1);

    // Calculating the distance
    distance= duration*0.034/2;
    return distance;
}

Servo::Servo(int pin)
{
	// configure LED PWM functionalitites channel freq resolution
    ledcSetup(0, 50, 8);
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(pin, 0);
}

void Servo::set_angle(int angle)
{
	high_time = map(angle, -90, 90, 500, 2500);
    pwr = high_time / 20000.0;
    angle_value = int(pwr * 255.0);
	ledcWrite(0, angle_value);
}

Motor::Motor(int a_pin, int b_pin)
{
	this->pwm_channel_a = a_pin % 10;
	this->pwm_channel_b = b_pin % 10;
	ledcSetup(this->pwm_channel_a, 50, 8);
	ledcSetup(this->pwm_channel_b, 50, 8);
	ledcAttachPin(a_pin, this->pwm_channel_a);
	ledcAttachPin(b_pin, this->pwm_channel_b);
}

void Motor::set_power(int power)
{
	if(power > 0)
	{
		ledcWrite(this->pwm_channel_a, 0);
		power = map(power, 1, 100, 127, 255);
		ledcWrite(this->pwm_channel_b, power);
	}
	else if(power < 0)
	{
		power = map(abs(power), 1, 100, 127, 255);
		ledcWrite(this->pwm_channel_a, power);
		ledcWrite(this->pwm_channel_b, 0);
	}
	else
	{
		ledcWrite(this->pwm_channel_a, 0);
		ledcWrite(this->pwm_channel_b, 0);
	}
}

Ultrasonic us_web(13,12);
Servo servo_web(27); 
Motor left_front(23, 22);
Motor right_front(21, 19);
Motor left_rear(18, 17);
Motor right_rear(16, 4);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(24, 14, NEO_GRB + NEO_KHZ800);

ESP32car::ESP32car()
{
	this->us_status = true;
	pixels.begin();
}

int ESP32car::get_status_at(int ref)
{
  this->dis = us_web.read_distance();
  if(this->dis > ref) return 2;
  else if(this->dis > 10) return 1;
  else return 0;
  }
  
void ESP32car::scan_step(int ref)
{
  
   this->current_angle += this->us_step;
   if(this->current_angle >= 90)
   {
	   this->current_angle = 90;
	   this->us_step = -18;
   }
   else if(this->current_angle <= -90)
   {
	   this->current_angle = -90;
	   this->us_step = 18;
   }
   servo_web.set_angle(this->current_angle);
   delay(40);
   this->sta_temp = this->get_status_at(ref);
   this->index = this->current_angle / 18 + 5;
   this->scan_arr[this->index] = this->sta_temp;
 }
 
 
 void ESP32car::get_angle_distance(void)
 {
	this->current_angle += this->us_step;
    if(this->current_angle >= 90)
    {
	    this->current_angle = 90;
	    this->us_step = -18;
    }
    else if(this->current_angle <= -90)
    {
	    this->current_angle = -90;
	    this->us_step = 18;
    }
   servo_web.set_angle(this->current_angle);
   delay(40);
   this->angle_distance[0] = this->current_angle;
   this->angle_distance[1] = us_web.read_distance();
 }

void ESP32car::move(string dir, int speed)
{
  if(dir == "forward")
    {
      left_front.set_power(this->wheel_reverse_value[0] * speed);
      right_front.set_power(this->wheel_reverse_value[1] * speed);
      left_rear.set_power(this->wheel_reverse_value[2] * speed);
      right_rear.set_power(this->wheel_reverse_value[3] * speed);
    }
	else if(dir == "backward")
	{  
	left_front.set_power(- this->wheel_reverse_value[0] * speed);
	right_front.set_power(- this->wheel_reverse_value[1] * speed);
	left_rear.set_power(- this->wheel_reverse_value[2] * speed);
	right_rear.set_power(- this->wheel_reverse_value[3] * speed);
	}
	else if(dir == "left")
	{
	left_front.set_power(- this->wheel_reverse_value[0] * speed);
	right_front.set_power(this->wheel_reverse_value[1] * speed);
	left_rear.set_power(- this->wheel_reverse_value[2] * speed);
	right_rear.set_power(this->wheel_reverse_value[3] * speed);
	} 
	else if(dir == "right")
	{
	left_front.set_power(this->wheel_reverse_value[0] * speed);
	right_front.set_power(- this->wheel_reverse_value[1] * speed);
	left_rear.set_power(this->wheel_reverse_value[2] * speed);
	right_rear.set_power(- this->wheel_reverse_value[3] * speed);
	}
	else 
	{
	left_front.set_power(0);
	right_front.set_power(0);
	left_rear.set_power(0);
	right_rear.set_power(0);  
	}

}



void ESP32car::avoid(int ref, int speed)
{
	this->scan_step(ref);
	if((this->scan_arr[4] == 2) && (this->scan_arr[5] == 2) && (this->scan_arr[6] == 2))
	{
		this->move("forward", speed);
	}
	else this->move("right", speed);
	
}

void ESP32car::follow(int ref, int speed)
{
	this->scan_step(ref);
	int max_length = 0;
	int count = 0;
	// int list_len = 0;
	float pos = 0;
	int temp = 0;
	for(int i = 0; i < 11; i++)
	{
		if (this->scan_arr[i] == 0 || this->scan_arr[i] == 1) {
			temp ++;
			
		}if ((this->scan_arr[i] == 2)  || (i == 10)) {
			if (max_length < temp) {
				max_length = temp;
				pos = temp / 2 + i - temp;
			}
			
			temp = 0;
			count ++;
		}
	}
	if(max_length == 0) this->move("stop", 0);
	else
	{
		if(pos < (11.0 / 3.0)) this->move("right", speed);
		else if(pos > (11.0 / 3.0 * 2.0)) this->move("left", speed);
		else if(this->scan_arr[5] == 0) this->move("backward", 100);
		else this->move("forward", speed);
	}
}

void ESP32car::get_grayscale(void)
 {
  this->adc_value[0] = analogRead(this->adc_pin1);
  this->adc_value[1] = analogRead(this->adc_pin2);
  this->adc_value[2] = analogRead(this->adc_pin3);
  
 }
 
void ESP32car::is_on_edge(int ref)
{
	this->get_grayscale();
	if((this->adc_value[0] <= ref) or (this->adc_value[1] <= ref) or (this->adc_value[2] <= ref))
	{
		this->move("backward", 20);
		delay(500);
		this->move("stop", 0);
	}
} 
 
int ESP32car::get_line_status(int ref)
{
  if(this->adc_value[1] <= ref)
  {
    return 0;
    }
   else if(this->adc_value[0] <= ref)
   {
    return -1;
    }
   else if(this->adc_value[2] <= ref)
   {
    return 1;
    }
   else return 2;
}

void ESP32car::track_line(int ref, int speed)
{
	this->get_grayscale();
	dir_status = this->get_line_status(ref);
	if(dir_status == 0)
	{
		this->move("forward", speed);
	}
	else if(dir_status == -1)
	{
		this->move("left", speed);
	}
	else if(dir_status == 1)
	{ 
		this->move("right", speed);
	}
}

void ESP32car::set_light_color(int red, int green, int blue)
{
	for(int n = 0; n < 24; n++)
	{
		pixels.setPixelColor(n, pixels.Color(red, green, blue)); // Moderately bright green color.
		pixels.show(); // This sends the updated pixel color to the hardware.
		delay(2); // Delay for a period of time (in milliseconds).
	}
	
}

void ESP32car::set_num_light(int num, int red, int green, int blue)
{
	pixels.setPixelColor(num, pixels.Color(red, green, blue)); // Moderately bright green color.
	pixels.show(); // This sends the updated pixel color to the hardware.
	delay(5); // Delay for a period of time (in milliseconds).
}

void ESP32car::set_light_off(void)
{
	// pixels.clear();
	pixels.clear();
	this-> set_light_color(0, 0, 0);
}