# OLED Display SH1106 I2C 128x64 Graphics Library for AVR Devices
Efficient graphics function library for OLED display modules (monochrome, 128 x 64 pixels, I2C/TWI) using SH1106 controller. Package customized to target 8-bit AVR MCU devices.

Low-level SH1106 controller driver functions are included in this package.  I2C/TWI driver functions for 8-bit AVR MCUs also included.

Pre-built library file "lib_OLED_display_avr8.a" works with Microchip/Atmel Studio (IDE) for AVR and SAM devices. Target any 8-bit AVR MCU (e.g. ATmega32U4).

An OLED display library for Arduino IDE may be built from the source code. The SH1106 driver source code can be modified to use the Arduino "Wire" (TWI) function library, if preferred, instead of the included I2C/TWI driver functions.

This implementation uses 1024 bytes of RAM in the microcontroller for a screen buffer, allowing display update functions to execute much faster than using read-modify-write operations directly on the controller GDRAM. Character font tables are located in MCU flash program memory to conserve remaining space in data RAM.

See the header file "OLED_display_avr8_lib.h" for a synopsis of functions provided.

More embedded resources at: www.mjbauer.biz/mjb_resources.htm
