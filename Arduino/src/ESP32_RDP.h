#ifndef __ESP32_RDP_H__
#define __ESP32_RDP_H__

#include <Wire.h>
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

using namespace std;

class Ultrasonic
{
	public:
        Ultrasonic(int triggerPin, int echoPin);
		float read_distance(void);

	private:
		int triggerPin;
        int echoPin;
		long duration;
		float distance;
};

class Servo
{
	public:
		Servo(int pin);
		void set_angle(int angle);
	private:
		int high_time;
		float pwr;
		int angle_value;
}; 

class Motor
{
	public:
		Motor(int a_pin, int b_pin);
		void set_power(int power);
		//void move(string dir, int speed);
	private:
		int pwm_channel_a;
		int pwm_channel_b;
};

class ESP32car
{
	public:
		ESP32car();
		int wheel_reverse_value[4] = {-1, 1, -1, 1};
		int adc_value[3];
		int angle_distance[2];
		void move(string dir, int speed = 0);
		void avoid(int ref, int speed);
		void get_angle_distance(void);
		void track_line(int ref, int speed);
		void is_on_edge(int ref);
		void follow(int ref, int speed);
		void set_light_color(int red, int green, int blue);
		void set_num_light(int num, int red, int green, int blue);
		void set_light_off(void);
		void get_grayscale(void);
	private:
		int dis = 0;
		int sta_temp = 0;
		int index = 0;
		int current_angle = 0;
		int us_step = 18;
		int adc_pin1 = 35;
		int adc_pin2 = 34;
		int adc_pin3 = 36;
		int dir_status;
		int left_counter = 0;
		int right_counter = 0;
		int forward_counter = 0;
		bool us_status;
		int get_status_at(int ref);
		void scan_step(int ref);
		int scan_arr[11] = {0};
		int get_line_status(int ref);
};

#endif