MCU = atmega16

OBJECTS = main.out peripheral_drivers/spi.out peripheral_drivers/pwm.out peripheral_drivers/i2c.out peripheral_drivers/serial.out device_drivers/screen.out  device_drivers/input.out device_drivers/rtc.out

all: upload.hex

upload.hex: upload.out
	avr-objcopy -j .text -j .data -O ihex upload.out upload.hex

%.out: %.c
	avr-gcc -mmcu=atmega16 -c -Os $< -o $@

upload.out: $(OBJECTS)
	avr-gcc -mmcu=atmega16 -Os -o upload.out $(OBJECTS)

flash: upload.hex
	sudo avrdude -c usbasp -p m16 -P USBasp -U flash:w:upload.hex

clean:
	rm -f *.out *.hex device_drivers/*.out peripheral_drivers/*.out
