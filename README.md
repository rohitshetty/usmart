uSmart is a quasi smart watch running on Atmega16 and esp8266.
This project contains base firmware for pseudo-kernel and infrastructure to build your own apps on usmart!.
uSmart gives you an infrastructure where you can write your own apps on this hardware.
(like multimeter on watch, your own small game, a calculator etc, also has wireless capability)
uSmart contains a monochrome nokia 5110 screen, user interface consisting of small joystick and press buttons, RTC DS1307, LM35 and ESP8266 for wireless communication

The file is structured into
	|
	\_device_drivers
	\_peripheral_drivers
	\_utils
	\_apps
		\_apps.mains.c
		\_ user defined apps
	|-main.c
	|-main.h
	|-config.h


* device_drivers has all the device specific firmware like drivers for RTC, Screen, sensors, wifi communication etc.
* peripheral_drivers has all the device agnostic communication protocols/tasks drivers like spi, i2c, serial and pwm sources.
* utils has utility functions
* apps folder is where user adds their apps.
	Apps.mains.c contains basic code needed for app to run
	users can add more apps in this folder following hello world example (to be added)
* config.h contains all the configurations
* main.c is the entry boot point for the device (main ())
Architecture is as follows
```
				________________________________________
                |         |        |        |     |     |
				| APP1    | APP2   | APP2   | ... |APPN | Apps, only one runs at a time
				|_________|________|________|_____|_____|
                                           \
				____________________________|____________
				|                                       |
				|      	 Main HW entry point            | Main layer
				|_______________________________________|
				|        Device driver layer            |
				|(screen drivers,input drivers,rtc etc) | Device driver
				|_______________________________________|
				|         Device agnostic layer         |
				|         (SPI, I2C, Serial, PWM)       | peripheral_drivers
				|_______________________________________|
				|         Microcontroller               | Hardware baremetal
				|_______________________________________|
				|screen | RTC| input | esp8266|sensors  | Devices connected
				|_______|____|_______|________|_________|

```
