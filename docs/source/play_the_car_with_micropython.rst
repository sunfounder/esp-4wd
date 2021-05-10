Play the Car with MicroPython
=====================================

There are two ways to play for Micropython users to learn and use ESP-4WD car: Code Control and APP Control.
You can directly use Micropython code to control the car, or DIY a remote control.

It should be noted that before using APP Control, you need to understand Code Control first.

.. note::
  In the last two chapters, we stored a main.py file() for the ESP32 RDP, 
  which allows the servo to automatically rotate to 0 degrees when powered up. 
  Now that the ESP-4WD car is assembled, you can now delete main.py or replace the import name with other example's name.

.. toctree::
  :maxdepth: 2

  code_control_micropython
  app_control_micropython