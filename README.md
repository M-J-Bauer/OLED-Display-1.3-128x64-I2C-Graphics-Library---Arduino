# OLED-Display-1.3-128x64-I2C-Graphics-Library---Arduino
Efficient graphics function library for 1.3" OLED display module (monochrome, 128 x 64 pixels, I2C/TWI) using SH1106 controller.

Low-level SH1106 controller driver functions are included in this package. 
The drivers are customized to suit OLED modules with an IIC (I2C/TWI) connection to the microcontroller.
Be sure to include the Arduino "Wire" (I2C) library in your application sketch.

An actual "library" (object module) is not already built... This repo contains C source code from which an Arduino library may be built, if desired.
Alternatively, the source code files can be incorporated into your Arduino program, simply by copying them into an existing Arduino project folder.
When the project is re-opened, the display source files (.ino and .h) will appear under separate tabs in the IDE editor. However, all source files are 
treated by the IDE as being part of a single sketch. (Arduino IDE v1.5 does not support modular program development well.)

Note: This implementation uses 1024 bytes of RAM in the microcontroller for a screen buffer, so it may not be suitable for "low-end" microcontrollers
with small data RAM capacity, e.g. ATmega328P with 2kB of RAM, but it's not impossible, depending on how much RAM the application program needs.
The screen buffer allows display update functions to execute much faster than otherwise (i.e. using read-modify-write operations directly in the controller GDRAM).

See the header file "oled_display_lib.h" for a synopsis of functions provided.

More embedded resources at: www.mjbauer.biz/mjb_resources.htm
