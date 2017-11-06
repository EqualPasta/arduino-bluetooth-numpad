# Bluetooth Arduino Numpad
Simple scanner for a custom numpad connected to a Adafruit Feather 32u4 BLE.
Can send HID keycodes over USB or Bluetooth.

#¤ Getting started
* Put Numpad library in Arduino IDE libraries folder (or use mklink to create a symbolic link). This folder is typically located at `Documents\Arduino\libraries`.
* Install Adafruit Board Manager. Stuff needed to support the Feather board. Tutorial found [here](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/setup)
* Install `HID-project` library. Include library -> Manage libraries... Find **HID-project** by **NicoHood**. Install that.
* Configure Boards and ports and run sketch.

## Structure
* **Numpad** - Custom numpad matrix scanner library.
* **Sketch_numpad_ble** - Main sketch. Scans numpad for pressed keys. Takes care of HID with computer both through USB and Bluetooth.
* **Sketch_numpad_read** - Shows how matrix scanner works.
