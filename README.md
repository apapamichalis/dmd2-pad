# DMD2 pad for SEEED XIAO ESP32 C3
This is entirely based on the [RazorPad project](https://github.com/razorbac91/RazorPad), with the following changes:
1. Unneeded libraries have been removed
2. BleKeyboard library has been packed as a .zip file and included in the `libraries` directory
3. Code has been cleaned up
4. Bounce is now actually being used
5. A small delay has been added the loop to keep the device cool

## ESP32 C3
The device used in this project is [SEEED Xiao ESP32-C3](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/). Since this
project was done as an improvement over the original RazorPad, the same connection layout has been used. The main difference is that
the boards have different GPIO pins located at the same location on the board (relative to the location of the USB port). This means
that **e.g. what the schematic shows as GPIO 5 in Xiao ESP32-C3 is GPIO 2** (the D0 pin on the Xiao schematic). I am attaching the
original schematic here, which can only serve as an optical guide, since as mentioned above, **pin numbers are incorrect!**

![pad](https://github.com/user-attachments/assets/463b3c44-49c4-4bca-90d6-b63dc8f122e5)

## Libraries
### Bounce2
Accessing the digital input pins through [Bounce2](https://github.com/thomasfredericks/Bounce2) library instead of directly
reading values to take advantage of the libraries ability to filter out unwanted state changes to the input pins.
### BleKeyboard
Transform the esp32 device into a bluetooth "keyboard" device. The version used in this project comes from
[this repository](https://github.com/mushxoxo/ESP32-BLE-Keyboard/tree/master) which includes some bug fixes not included in the
[library's original repo](https://github.com/T-vK/ESP32-BLE-Keyboard).

## Getting started
1. Add https://raw.githubusercontent.com/espressif/arduino-esp32/ghpages/package_esp32_index.json to Arduino IDE (Preferences -> Additional boards manager URLs)
2. Add the Espressif ESP32 library to arduino IDE (through the left hand side nagivation menu).
3. Select the XIAO_ESP32C3 board (and associate it with the port to which the esp32 is connected).
4. Add the Bounce2 library by Thomas O Fredericks.
5. Add the included BleKeyboard zip library to the sketch.
6. Upload the code to the esp32.
