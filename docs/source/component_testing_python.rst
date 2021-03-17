Component Testing by Python
=======================================

Before assembling the ESP-4WD Car, you need to test each device to make sure they are working properly, if there is any problem with the device, please contact us.

Power to ESP32 RDP
---------------------------

Connect ESP32 RDP to PC.

.. image:: img/arduino_setup13.png
  :width: 400
  :align: center

Powering ESP32 RDP with batteries.

.. image:: img/arduino_test1.jpg
  :width: 400
  :align: center

Test the Motor
-----------------

Finishing the wire up according to the diagram.

.. image:: img/arduino_test2.png
  :width: 500
  :align: center

Double-click the ``move.py`` file in the MicroPython device window.
Click the green icon at the top left to run the current script, and then 
click the red icon next to it to stop the current script.

.. image:: img/python_setup16.png
  :width: 450
  :align: center

After running the code, you will see the four motors turning and changing the direction of rotation back and forth, and finally stopping.

Test the Ultrasonic Module
---------------------------

Finishing the wire up according to the diagram.

.. image:: img/arduino_test3.png
  :width: 400
  :align: center

There is a Shell window under Thonny, where you can view running information, error
information and print information.

.. image:: img/python_setup17.png
  :width: 450
  :align: center

Run ``ultrasonic.py``, the Shell window under Thonny will always print the distance value read
by the ultrasonic module.

Test the Grayscale Sensor Module
---------------------------------

Finishing the wire up according to the diagram.

.. image:: img/arduino_test4.png
  :width: 400
  :align: center

Run ``grayValue.py``, the Shell window under Thonny will always print the reading value of the
grayscale sensor.

When using the grayscale sensor module, the probe should be about 5 mm from the ground.

Normally, it will detect a value above 1100 on white ground. 
On black ground, it will detect values below 900. 
On a cliff, it will detect a value below 110. (If the reading is 0, it means that the probe does not detect the ground.)

If the grayscale sensor module does not detect normal values, you will need to calibrate it.

Hover it over a white ground and twist the potentiometer clockwise so that the reading is greater than 1100 (usually around 1200). Then suspend it on a dark ground and twist the potentiometer counterclockwise so that it is less than 900 (usually between 300 and 600). Repeat this several times to get it to the maximum difference in both cases.


.. image:: img/arduino_test4-1.png
  :width: 400
  :align: center

Test the RGB Board
--------------------

Finishing the wire up according to the diagram.

.. image:: img/arduino_test5.jpg
  :width: 400
  :align: center

.. image:: img/arduino_test6.png
  :width: 400
  :align: center

Run ``flashingLight.py``, the RGB light under the car flashes every 0.5 seconds and
changes color every time it flashes.

Test the Servo
---------------

Finishing the wire up according to the diagram.

.. image:: img/arduino_test7.png
  :width: 400
  :align: center

Run ``servo.py``. The servo will first turn 30 degrees left, then 30 degrees right, and finally return to 0 degrees.