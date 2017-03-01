MCU = atmega16

SRC = $(wildcard device_drivers/*/*.c) \
	$(wildcard peripheral_drivers/*/*.c)\
	$(wildcard apps/*/*.c)\
	$(wildcard apps/*.c)\
	$(wildcard utils/*.c)\
	$(wildcard *.c)

OBJECTS = $(SRC:%.c=%.out)

all: upload.hex

printobj:
	@echo $(OBJECTS)

upload.hex: upload.out
	avr-objcopy -j .text -j .data -O ihex upload.out upload.hex

%.out: %.c
	avr-gcc -Wall -mmcu=atmega16 -c -Os $< -o $@

upload.out: $(OBJECTS)
	avr-gcc -Wall -mmcu=atmega16 -Os -o upload.out $(OBJECTS)
	@echo "\n\n\n"
	@avr-size -C --mcu=atmega16 upload.out

flash: upload.hex
	@sudo avrdude -c usbasp -p m16 -P USBasp -U flash:w:upload.hex

clean:
	@rm -f $(OBJECTS)
