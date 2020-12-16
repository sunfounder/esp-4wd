# The Mircopython ESP32 Car

## Usage
### First deploying the firmware
The first thing you need to do is download the most recent MicroPython firmware .bin file to load onto your ESP32 device. You can download it from the MicroPython downloads page. From here, you have 3 main choices:
- Stable firmware builds
- Daily firmware builds
- Daily firmware builds with SPIRAM support
If you are just starting with MicroPython, the best bet is to go for the Stable firmware builds. If you are an advanced, experienced MicroPython ESP32 user who would like to follow development closely and help with testing new features, there are daily builds. If your board has SPIRAM support you can use either the standard firmware or the firmware with SPIRAM support, and in the latter case you will have access to more RAM for Python objects.
Once you have the MicroPython firmware you need to load it onto your ESP32 device.Currently we use esptool.py to copy across the firmware.
Open the terminal,install it using pip:
```
pip install esptool
```
For best results it is recommended to first erase the entire flash of your device before putting on new MicroPython firmware.Using esptool.py you can erase the flash with the command:
```
esptool.py --port COM5 erase_flash 
```
And then deploy the new firmware using():
```
esptool.py --chip esp32 --port COM5 write_flash -z 0x1000 esp32.bin
```
Notes:
- You might need to change the “port” setting to something else relevant for your PC
- The filename of the firmware should match the file that you have


### Second copy python file onto the board
Currently we use 'Thonny' to copy python files onto the ESP32 Board.
1. Download and install the 'Thonny' software.
2. Select Run ->  Select interperter -> device is "Mircopython(ESP32)" and port setting to something else relevant for your PC,Click OK.Click the "STOP" button to restart the process to connect to the development board.
3. Open the local folder where the python repository is located.When the ESP32 is connected, the files in the device are displayed above (empty if not).Right-click on the local file you want to upload and select Upload to Micropython device.
4. Open the file you need to run on the device,Click 'Run current script' to run.
5. If main.py is present in the device, the device bootloader will automatically run.（You can write your boot-up program to main.py）