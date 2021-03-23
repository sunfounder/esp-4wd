Setup Your Arduino
================================

Before you can start using the kit, you will need to complete the following steps.

Download the ESP-4WD Code
-------------------------------------

Click `here <https://github.com/sunfounder/esp-4wd>`_ to download the ESP-4WD code. After unzipping the zip file you have downloaded, you will see all the relevant files for the ESP-4WD.

.. image:: img/arduino_setup2.png
  :width: 400
  :align: center

Install Arduino IDE
--------------------

Go to `https://www.arduino.cc/en/software <https://www.arduino.cc/en/software>`_
, select the version to download.

.. image:: img/arduino_setup1.png
  :width: 400
  :align: center

Import Sunfounder Remote Control Supporter
-------------------------------------------

Open the arduino.

.. image:: img/arduino_setup3.png
  :width: 80
  :align: center

Click File -> Preferences.

.. image:: img/arduino_setup4.png
  :width: 300
  :align: center

In the Preferences interface, click the UPLOAD icon, and type in this URL, **https://dl.espressif.com/dl/package_esp32_index.json**, click OK.

.. image:: img/arduino_setup5.png
  :width: 400
  :align: center

Install ESP32 board
--------------------

Click Tools -> Board -> Boards Manager. Search esp32, click Install.

.. image:: img/arduino_setup6.png
  :width: 400
  :align: center

If you do not install the esp32 development board library, you will not be able to download the code to the ESP-4WD Car.

Include library
----------------

Include src
^^^^^^^^^^^^

Click Sketch -> Include Library -> Add .ZIP Library.

.. image:: img/arduino_setup7.png
  :width: 400
  :align: center

Choose esp-4wd -> Arduino -> src, you can call the functions in this library to write code to control ESP-4WD Car.

.. image:: img/arduino_setup8.png
  :width: 400
  :align: center

Include Adafruit NeoPixel
^^^^^^^^^^^^^^^^^^^^^^^^^^

Click Sketch -> Include Library -> Manage Libraries.

.. image:: img/arduino_setup9.png
  :width: 400
  :align: center

search Adafruit NeoPixel, find it in the drop-down options, click Install. When using
RGB lights, you need to call the functions in this library.

.. image:: img/arduino_setup10.png
  :width: 400
  :align: center

Include WebSockets
^^^^^^^^^^^^^^^^^^^

Continue to Search WebSockets, find it in the drop-down options, click Install. This library is used to open APP controlled services.

.. image:: img/arduino_setup11.png
  :width: 400
  :align: center

Include ArduinoJson
^^^^^^^^^^^^^^^^^^^^

Continue to search ArduinoJson, find it in the drop-down options, click Install. This library is used to communicate between APP and ESP-4WD Car.

.. image:: img/arduino_setup12.png
  :width: 400
  :align: center

Install driver
---------------

Connect ESP32 RDP to PC.

.. image:: img/arduino_setup13_.png
  :width: 400
  :align: center

Check your serial port information, right-click the "This PC" icon, Click Properties -> Device Manager -> Ports.

.. image:: img/arduino_setup14.png
  :width: 400
  :align: center

If the COM port information cannot be displayed, you need to install the CP210x driver.

.. image:: img/arduino_setup15.png
  :width: 250
  :align: center

Put the supporting CD into the computer CD drive, and then unzip the compressed package to a local folder.

.. image:: img/arduino_setup16.png
  :width: 200
  :align: center

After decompression, select the appropriate version to install.

.. image:: img/arduino_setup17.png
  :width: 250
  :align: center

Check the serial port information of the device manager again. If the COM port can be displayed, the installation is successful.

.. image:: img/arduino_setup18.png
  :width: 250
  :align: center


