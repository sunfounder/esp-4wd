Code Control
=============

In this chapter, we are provided with method of arduino control. Open ``esp-4wd\
Micropython\example`` , you can see a total of 7 code examples, you can use these 7
examples to quickly get started using the ESP-4WD Car.

.. image:: img/python_code1.png
  :width: 250
  :align: center


move
-----

Run the ``move.py`` file, the car will go forward 1s, go backward 1s, turn left 1s, turn right 1s at 30% speed, and finally stop.

.. code-block:: python

    import esp32_rdp as car
    import time

    def main():
        car.move("forward", 30)
        time.sleep(1)
        car.move("backward", 30)
        time.sleep(1)
        car.move("left", 30)
        time.sleep(1)
        car.move("right", 30)
        time.sleep(1)
        car.move("stop")

    try:
        main()
    finally:
        car.move("stop") 

ultrasonic
-----------

Run ``ultrasonic.py`` , the Shell window will always print the distance value read by the ultrasonic module.

.. code-block:: python

    import esp32_rdp as car
    import time

    ult = car.Ultrasonic(13,12)

    def main():
        while True:
            distance = ult.get_distance()
            print('distance:%0.2f' % distance)
            time.sleep(0.1)

    main()

grayValue
-----------

Run ``grayValue.py`` , the Shell window will always print the reading value of the grayscale sensor.

.. code-block:: python

    import esp32_rdp as car
    import time

    grayValue = []

    def main():
        while True:
            grayValue = car.get_grayscale_list()
            print('grayValue: %d %d %d' %(grayValue[0],grayValue[1],grayValue[2]))
            time.sleep(1)

    main()



flashingLight
---------------

Run ``flashingLight.py``, the RGB light under the car flashes every 0.5 seconds and
changes color every time it flashes.

.. code-block:: python

    import esp32_rdp as car
    import random
    import time

    def main():
        while True:
            color = [random.randint(0,255),random.randint(0,255),random.randint(0,255)]
            car.set_light_color(color)
            time.sleep(0.5)
            car.set_light_off()
            time.sleep(0.5)

    try:
        main()
    finally:
        car.set_light_off()

waterfallLight
----------------

Run ``waterfallLight.py``, the RGB lights under the car will gradually turn on from the 
first to the twenty-fourth, and then turn off from the end to the middle. After that, 
the RGB lights will turn on from the twenty-fourth to the first, and then turn off from 
the end to the middle.

.. code-block:: python

    import esp32_rdp as car
    import random
    import time

    def main():
        while True:
            color = [random.randint(0,255),random.randint(0,255),random.randint(0,255)]
            noColor = []
            for i in range(24):
                car.set_num_color(i,color)
                time.sleep_ms(20)
            for i in range(23,11,-1):
                j = 23-i
                car.set_num_color(i, noColor)
                car.set_num_color(j, noColor)
                time.sleep_ms(40)
            for i in range(23,0,-1):
                car.set_num_color(i,color)
                time.sleep_ms(20)
            for i in range(23,11,-1):
                j = 23-i
                car.set_num_color(i,noColor)
                car.set_num_color(j,noColor)
                time.sleep_ms(40)

    try:
        main()
    finally:
        car.set_light_off()

The sentence to light up the LED is ``car.set_num_color(i, red, green, blue)`` ; the first
parameter is the number of the light, and the last three parameters are the RGB value.
For example, ``car.set_num_color(4,255,0,0)`` means to make the No. 4 LED light up in
red.

.. image:: img/arduino_code1.png
  :width: 300
  :align: center

measureSpeed
--------------

Run ``measureSpeed.py`` ,  the car will move at a random speed, and the 2-ch Photo-
interrupter Module will detect the speed of the car.

The light emitted from the transmitting end of the 2-ch Photo-interrupter Module
to the receiving end will pass through the Encoding Disk (which has 20 holes). When
the receiving end does not receive the light, it will send a "0" to the microcontroller,
otherwise it will send a "1".

This means that when a total of 20 "1"s are detected, the small wheel has turned one
round (a distance of the wheel circumference has been traveled forward).

In the same way, we can detect the frequency of the "1" received by the
microcontroller and calculate the speed of the trolley in cm/s.

.. code-block:: python

    import esp32_rdp as car
    import random
    import time

    speed = car.Speed(26, 25)

    def main():
        while True:
            car.move("forward",random.randint(0,100))
            time.sleep(1)
            carSpeed = speed.get_speed()
            print('distance:%d' % carSpeed)

    try:
        main()
    finally:
        car.move("stop")

morePlay
---------

Run ``morePlay.py`` , this example provides 4 ways to use ESP-4WD Car. You can switch 
between different modes by modifying the value of the mode variable.

.. code-block:: python

    import esp32_rdp as car

    mode = 1

    def main():
        while True:
            global mode
            if mode == 1:
                car.avoid(40,30)
            elif mode == 2:
                car.follow(40,30)
            elif mode == 3:
                car.is_on_edge(110)
            elif mode == 4:
                car.track_line(400,50)

    try:
        main()
    finally:
        car.move("stop")

**avoid**

Modify the value of the mode variable to 1. ESP-4WD Car will advance at 30% speed
and turn right to avoid obstacles ahead。

**follow**

Modify the value of the mode variable to 2. ESP-4WD Car will move forward at 30%
speed and automatically follow objects within 40cm in front.

**cliff detection**

Modify the value of the mode variable to 3. When ESP-4WD Car detects a cliff (a place
where the grayscale sensor's detection value is below 110), it will retreat a certain
distance.

**track_line**

Modify the value of the mode variable to 4. The ESP-4WD Car moves along the black
line on the white ground (where the grayscale sensor detection value is below 400).

Startup at boot
--------------------

Here, we provide a method to let the python program start automatically. Click the new file icon in the upper left corner.

.. image:: img/python_code2.png
  :width: 300
  :align: center

Import the sample code file in the this file.

.. code-block:: python

    import move

Click the save button in the upper left corner, and select **MicroPython device** in the pop-up option box. 

.. image:: img/python_code3.png
  :width: 300
  :align: center

Name the file **main.py** .

.. image:: img/python_code4.png
  :width: 400
  :align: center

Unplug the data cable and re-power the main control board. **main.py** will run automatically.
If you want to run other effects, you can write the program directly on main.py, or you can import it in main.py after the other files have been programmed.

.. code-block:: python

    import waterfallLight

