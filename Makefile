MCU = atmega16
OBJECTS =main.out screen.out spi.out pwm.out input.out i2c.out rtc.out serial.out
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
	rm -f *.out *.hex
