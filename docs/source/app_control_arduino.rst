APP control
============

In this chapter,你将学习使用Sunfounder Controller这款遥控器软件，并在Sunfounder Controller上diy一个遥控器来
控制小车。

.. toctree::
  :maxdepth: 2

  Install Sunfounder Controller
  About Sunfounder Controller
  Establish communication
  APP操作
  DIY遥控器

  

Install Sunfounder Controller
-------------------------------

Open App Store (iOS/Mac OS X system) or Play Store (Android/Windows/Linux
system), then search and download Sunfounder Controller.

.. image:: img/arduino_app1.png
  :width: 500
  :align: center

About Sunfounder Controller
-----------------------------

Page Introduction
^^^^^^^^^^^^^^^^^^

Start the Sunfounder Controller.

.. image:: img/arduino_app2.png
  :width: 150
  :align: center

Click the middle button to add a new controller.

.. image:: img/arduino_app3.png
  :width: 450
  :align: center

Sunfounder Controller is a platform that can add custom remote control handles. It
reserves many control interfaces. There are a total of 17 areas from A to Q. Each area
has selectable widgets.

.. image:: img/arduino_app4.png
  :width: 450
  :align: center

The available widgets in the large square area include joystick and cross-shaped
steering wheel.

.. image:: img/arduino_app5.png
  :width: 400
  :align: center

The available widgets in the small square area include buttons, digital displays and
switches.

.. image:: img/arduino_app6.png
  :width: 360
  :align: center

The available widgets for the rectangular area include slider, dial, ultrasonic radar and
grayscale detection tool.

.. image:: img/arduino_app7.png
  :width: 510
  :align: center

Widget List
^^^^^^^^^^^^

For the convenience of writing code, this chapter will introduce the use of various
widgets on Sunfounder Controller, the parameter types and ranges of control widgets,
and the parameter types and ranges of display widgets.

The control widgets of Sunfounder Controller include buttons, switches, joystick,
cross-shaped steering wheel, and slider.

You can modify the widget name and the parameter range of some widgets by clicking 
the icon in the upper right corner of the widget.

.. image:: img/arduino_app8.png
  :width: 550
  :align: center

When we use these control widgets, ESP-4WD RDP will receive the control data.
Through these control data, we can write code to control the car.

.. image:: img/arduino_app9.png
  :width: 700
  :align: center

The display widget of Sunfounder Controller includes digital displays, dial, ultrasonic
radar, and grayscale detection tool.

When we send sensor data to these display widgets, we can display the data on the
corresponding widgets. At the same time, you can also modify the name, unit and
parameter range of the display widget by clicking the icon in the upper right
corner.

.. image:: img/arduino_app10.png
  :width: 700
  :align: center

Establish communication
------------------------

In addition to the Arduino control method, we also provide the APP control method.
You can open Sunfounder Controller on mobile phones, tablets and other devices,
and then make a controller to control ESP-4WD Car.

运行代码
^^^^^^^^^

Open the 8.app_control.ino file in the esp-4wd\example\Arduino\8.app_control path.

.. image:: img/arduino_app11.png
  :width: 180
  :align: center

AP mode
^^^^^^^^

There are two ways to establish communication between Sunfounder Controller
and ESP32 RDP: One is AP mode, the other is STA mode. We can switch the 
communication mode by modifying the code of app_control.ino.

If you want to use AP mode, you need to connect Sunfounder Contorller to the hotspot released by ESP32 RDP. 
Move the code to line 6, please set SSID and PSK here.（代码中的NAME既是SSID，同时也是小车的名字） If you have 
more than one EPS-4WD Cars, you need to set different NAMEs for them to avoid a wrong connection. 
In addition, you need to set a password of more than 8 digits.

.. code-block:: c
    #define NAME "ESP-4WD Car"
    #define AP_PASSWORD "123456789"

**Note: Click File -> Preferences, and then select the Display line numbers option to display the number of lines of arduino code.**

Then modify the content of line 10 and define the SWITCH_MODE variable as "ap".

.. code-block:: c
    #define SWITCH_MODE "ap"

After downloading the code, ESP32 RDP will send a hotspot signal, then take out your
electronic device, open the WLAN management interface and connect to the wifi
network.

.. image:: img/arduino_app12.png
  :width: 400
  :align: center

打开Sunfounder Controller，点击右上方的连接图标。

.. image:: img/arduino_app_new1.png
  :width: 300
  :align: center

连接成功会出现提示框。

.. image:: img/arduino_app_new2.png
  :width: 400
  :align: center

并且在sunfounder的界面上会显示小车的名字。

.. image:: img/arduino_app_new3.png
  :width: 300
  :align: center

STA mode
^^^^^^^^^

If you want to use STA mode, you need to connect Sunfounder Controller and ESP32 RDP to the same LAN.
Turn the code to line 8, there are two macros that define the wifi information. ESP32
RDP will search for and connect to this wifi, and at the same time your electronic
device should connect to this wifi.

.. code-block:: c
    #define STA_NAME "MakerStarsHall"
    #define STA_PASSWORD "sunfounder"

Then modify the content of line 10 and define the SWITCH_MODE variable as "sta".

.. code-block:: c
    #define SWITCH_MODE "sta"

After downloading the code, ESP32 RDP will automatically connect to the wifi network
, and at the same time take out your electronic device, open the WLAN management interface 
and connect to this wifi network.

.. image:: img/arduino_app13.png
  :width: 400
  :align: center

打开Sunfounder Controller，点击右上方的连接图标。

.. image:: img/arduino_app_new1.png
  :width: 300
  :align: center

在弹出的确认框中找到小车名字，点击它。

.. image:: img/arduino_app_new4.png
  :width: 450
  :align: center

连接成功后，在sunfounder的界面上会显示小车的名字。

.. image:: img/arduino_app_new3.png
  :width: 300
  :align: center

APP操作
--------

Download this code, and then using any of the above methods to establish
communication.

添加按键
^^^^^^^^^

Open Sunfounder Controller, and then 创建 an empty controller.

.. image:: img/arduino_app3.png
  :width: 450
  :align: center

As shown in the figure, select the corresponding widget for the controller. After
adding, click the icon in the upper right corner to save the configuration.

.. image:: img/arduino_app14.png
  :width: 450
  :align: center

Click the start button in the upper right corner, and then try to use this controller to
control ESP-4WD Car.

Widget A is used to display the driving speed of the car.

Widget D is used to simulate radar scanning.

Widget H is used to control the driving speed of the car.

Widget K is used to control the driving direction of the car.

Widget L is used to display the detection result of the grayscale sensor.

Widget M is used to control the on and off of the RGB board.

.. image:: img/arduino_app15.png
  :width: 450
  :align: center

DIY遥控器
----------

如果你想要DIY一个新的遥控器，你需要了解ESP32 RDP和Sunfounder Controller之间的通信过程。Open the 
9.test_control.ino file in the esp-4wd\Arduino\example\9.test_control. 你将通过这个代码来了解它们之间的通信。

Program framework
^^^^^^^^^^^^^^^^^^^

First, let us understand the general operating framework of the program.

Turn the code to line 103. In setup(), the temp_data variable defines the device
information and proofreading information of ESP-4WD Car, and sends it to
Sunfounder Controller through the deserializeJson() function.

.. code-block:: c
    void setup() {
        String stringone = "{\'Name\':\"";
        String stringtwo = "\", \'Type\':\"ESP-4WD Car\", \'Check\':\"SunFounder Controller\"}";
        temp_data = stringone + String(AP_NAME) + stringtwo;
        deserializeJson(doc_send, temp_data);

This if statement is used to determine the communication mode between ESP32 RDP
and Sunfounder Controller. You can change the communication mode by modifying
SWITCH_MODE.

.. code-block:: c

    if(SWITCH_MODE == "ap")
    {
        WiFi.softAP(AP_NAME, AP_PASSWORD);
        ...  
    }
    else if(SWITCH_MODE == "sta")
    {
        WiFi.begin(STA_NAME, STA_PASSWORD);
        ...
    }

These two lines of statements indicate that the APP service starts running and enters
the event processing process.

.. code-block:: c

    webSocket.begin(); 
    webSocket.onEvent(onWebSocketEvent);

Then, we turn the code to line 26, onWebSocketEvent() is the event handling function,
which uses the switch statement to determine the event type. The event types that
the current program can trigger are WStype_DISCONNECTED, WStype_CONNECTED,
and WStype_TEXT.

WStype_DISCONNECTED is a disconnected event. The processing method is to print
the disconnected information.

WStype_CONNECTED is a connected event. The processing method is to print
the connection information, and then send the device information to Sunfounder
Controller.

WStype_TEXT is a sending and receiving event, and we will process the received and
sent string information in this event.

.. code-block:: c

    void onWebSocketEvent(uint8_t client_num,
                        WStype_t type,
                        uint8_t * payload,
                        size_t length) {
    char output[300];
    // Figure out the type of WebSocket event
    switch(type) {

        // Client has disconnected
        case WStype_DISCONNECTED:
        Serial.printf("[%u] Disconnected!\n", client_num);
        break;

        // New client has connected
        case WStype_CONNECTED:
        {
            IPAddress ip = webSocket.remoteIP(client_num);
            Serial.printf("[%u] Connection from ", client_num);
            Serial.println(ip.toString());
            webSocket.sendTXT(client_num, temp_data);
        }
        break;

        case WStype_TEXT:
            ...

By modifying the content of the WStype_TEXT event, we
can understand the data receiving and sending process between ESP-4WD Car and
Sunfounder Controller.

接收过程
^^^^^^^^^

在ESP32 RDP会与Sunfounder Controller的通信过程会产生数据交互，ESP32 RDP既会接收来自Sunfounder Controller的数据，
也会将自身的传感器数据发送给Sunfounder Controller。所以我们先来了解一下ESP32 RDP从Sunfounder Controller接收了
哪些数据。

**Step 1:创建遥控器**

Download this code, re-establish communication, and then open Sunfounder Controller to create 
a new controller. We add a slider in the H area and a cross-shaped steering wheel in the K area. After
adding, click the icon in the upper right corner to save.

.. image:: img/arduino_app16.png
  :width: 450
  :align: center

**Step 2:小车接收控件的值**

Turn the code to line 53, in this if statement, we print out the string data (payload
variable) received from Sunfounder Controller.

.. code-block:: c

    if(strcmp((char * )payload, temp_recv) != 0) 
    {
        memset(temp_recv, 0, 300);
        Serial.printf(" Received text: %s\n", payload);
        memcpy(temp_recv, (char *)payload, strlen((char *)payload));
    }

Click the start icon in the upper right corner to run the controller.

.. image:: img/arduino_app17.png
  :width: 250
  :align: center

Open the serial debugging assistant of arduino, we can find that the initial data of K
control is the string "stop", and the initial data of H widget is the int value 50.

.. image:: img/arduino_app18.png
  :width: 450
  :align: center

按住K区域的cross-shaped steering wheel的不同方向键，并且滑动H区域的slider。

.. image:: img/arduino_app19.png
  :width: 450
  :align: center

You can see that the cross-shaped steering
wheel widget sends a string of data ("forward", "backward", "left", "right") to the ESP-
4WD RDP. The slider widget will send an int data (range: 0-100) to the ESP-4WD RDP.

.. image:: img/arduino_app20.png
  :width: 450
  :align: center

**Step 3:小车响应**

当ESP-4WD Car接收到来自Sunfounder Controller不同控件的数据时，它需要做出相应的响应。
Let’s write a piece of code that uses the widgets on the Sunfounder Controller 
to control the movement of the car. The K widget(cross-shaped steering wheel) controls
the direction of the car, and the H widget(slider) controls the speed of the car.

By modifying the content of the WStype_TEXT event, 我们可以实现用Sunfounder Controller的控件来控制小车的移动。
Turn the code to line 62，我们将以下代码添加在这一行里。

.. code-block:: c

    car.move(doc_recv["K_region"], doc_recv["H_region"]);

添加完成后，我们来解释一下content of the WStype_TEXT event。（有部分被注释的内容未展示，请不要将它们删除。）

.. code-block:: c
    :emphasize-lines:8,9

    case WStype_TEXT:
        if(strcmp((char * )payload, temp_recv) != 0) 
        {
        memset(temp_recv, 0, 300);
        Serial.printf(" Received text: %s\n", payload);
        memcpy(temp_recv, (char *)payload, strlen((char *)payload));
        }
        deserializeJson(doc_recv, payload);
        car.move(doc_recv["K_region"], doc_recv["H_region"]);
        serializeJson(doc_send, output);
        if(strcmp(output, temp_send) != 0) 
        {
        memset(temp_send, 0, 300);
        Serial.printf(" Send text: %s\n", output);
        memcpy(temp_send, output, strlen(output));
        }
        webSocket.sendTXT(client_num, output);     
        break;

解释content of the WStype_TEXT event之前，turn the code to line 19, where a global variable doc_recv that 
can store json objects(similar to the structure of C language) is defined, which is used to receive string 
data from Sunfounder Controller.

.. code-block:: c

    DynamicJsonDocument doc_recv(1024);

回到WStype_TEXT event, Through the function deserializeJson( ), the payload variable (the string data
received from the Sunfounder Controller) is converted into an operable doc_recv variable.

.. code-block:: c

    deserializeJson(doc_recv, payload);

The value of doc_recv["K_region"] is the string data ("forward", "backward","left",
"right") sent by the K widget (cross-shaped steering wheel), the same as the value of
doc_recv["H_region"] is the int data sent by H widget (slide) (range: 0-100).

Pass doc_recv["K_region"] as the first parameter to the car.move() function to control
the direction of the ESP-4WD Car. Pass doc_recv["H_region"] as the second parameter
to the car.move() function to control the speed of ESP-4WD Car.

.. code-block:: c

    car.move(doc_recv["K_region"], doc_recv["H_region"]);

After downloading the modified code and re-establishing communication, open the
controller and click the start icon in the upper right corner to run the controller.
The cross-shaped steering wheel in the K area can control the direction of the ESP-
4WD Car, and the slider in the H area can control the speed of the ESP-4WD Car.

.. image:: img/arduino_app17.png
  :width: 250
  :align: center

发送过程
^^^^^^^^^

我们再来了解一下ESP32 RDP是如何将自身的传感器数据发送给Sunfounder Controller。

**Step 1:创建遥控器**

回到WStype_TEXT event, delete the comment symbol in lines 67-71，让这段代码重新启用。

.. code-block:: c

    car.get_grayscale();
    for(int i = 0; i < 3; i++)
    {
    doc_send["L_region"][i] = car.adc_value[i];
    }

Download this code, re-establish communication, and then open Sunfounder Controller to create 
a new controller. We add a grayscale detection tool in the L area. After adding, 
click the icon in the upper right corner to save.

.. image:: img/arduino_app21.png
  :width: 450
  :align: center

**Step 2:小车接收控件的值**

Turn the code to line 77. In this if statement, we print the output variable (the string
information that stores the sensor data).

.. code-block:: c

    if(strcmp(output, temp_send) != 0) 
    {
        memset(temp_send, 0, 300);
        Serial.printf(" Send text: %s\n", output);
        memcpy(temp_send, output, strlen(output));
    }

Click the start icon in the upper right corner to run the controller.

.. image:: img/arduino_app17.png
  :width: 250
  :align: center

Open the serial debugging assistant of arduino, you will see that the ESP-4WD RDP has been sending
device information, calibration information and the value of the grayscale sensor to
the Sunfounder Controller.

.. image:: img/arduino_app22.png
  :width: 450
  :align: center

**Step 3:小车响应**

Let's write a piece of code that display the sensor data of ESP-4WD RDP on the
widget of Sunfounder Controller.Widget D (grayscale detection tool)将会根据检测到的灰度值显示地面情况。

让我们来重新解释一下content of the WStype_TEXT event。（有部分被注释的内容未展示，请不要将它们删除。）

.. code-block:: c
    :emphasize-lines:11,12,13,14,15,16,17,18,19,20,21,22,23

    case WStype_TEXT:
        if(strcmp((char * )payload, temp_recv) != 0) 
        {
        memset(temp_recv, 0, 300);
        Serial.printf(" Received text: %s\n", payload);
        memcpy(temp_recv, (char *)payload, strlen((char *)payload));
        }
        deserializeJson(doc_recv, payload);
        car.move(doc_recv["K_region"], doc_recv["H_region"]);
        car.get_grayscale();
        for(int i = 0; i < 3; i++)
        {
            doc_send["L_region"][i] = car.adc_value[i];
        }
        serializeJson(doc_send, output);
        if(strcmp(output, temp_send) != 0) 
        {
        memset(temp_send, 0, 300);
        Serial.printf(" Send text: %s\n", output);
        memcpy(temp_send, output, strlen(output));
        }
        webSocket.sendTXT(client_num, output);     
        break;

解释content of the WStype_TEXT event之前，turn the code to line 18, where the global variable doc_send 
that can store the json object (similar to the structure of the c language) is defined, 
which is used to send the sensor data of the Sunfounder Controller.

.. code-block:: c

    DynamicJsonDocument doc_send(1024);

通过car.get_grayscale()函数，我们可以获取灰度传感器检测到的左边值(car.adc_value[0])，
中间值(car.adc_value[1])和右边值(car.adc_value[2])，并将它们依次储存在doc_send["L_region"]里。

.. code-block:: c

    car.get_grayscale();
    for(int i = 0; i < 3; i++)
    {
        doc_send["L_region"][i] = car.adc_value[i];
    }

Use the function serializeJson() to convert the doc_send variable (stored sensor
data) into an output variable (a string type that can be recognized by Sunfounder
Controller).

.. code-block:: c

    serializeJson(doc_send, output);

Send the client_num variable (storing the device information and proofreading
information of the ESP-4WD RDP) and output variable to Sunfounder Controller.

.. code-block:: c

    webSocket.sendTXT(client_num, output); 

回到遥控器界面，Widget D (grayscale detection tool)正在显示当前地面情况，如果想要知道更多关于控件的信息，请回到
Widget List查看。

.. image:: img/arduino_app23.png
  :width: 250
  :align: center




