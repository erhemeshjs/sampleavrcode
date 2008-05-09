# Makefile Test
#
# Definition der Object-Files
OBJ = 05-pwm.o
HEX = 05-pwm.hex
#
# Welches Outputformat
FORMAT = ihex
#
# Definition des Programmers
SPEED=115200
PROG=avr910
SERIAL=/dev/ttyUSB0

MCU=atmega32
F_CPU=16000000
CC=avr-gcc
CFLAGS=-Os -g -mmcu=$(MCU) -DF_CPU=$(F_CPU)

%.o : %.c
	@echo
	@echo Compiling: $<
	$(CC) -c $(CFLAGS) $< -o $@

.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@echo
	@echo Linking: $@
	$(CC) $(CFLAGS)  -Wl,-Map,blinky.map $(OBJ) --output $@ $(LDFLAGS)

%.hex : %.elf
	@echo
	@echo Generate Hex: $@
	avr-objcopy -j .text -j .data -O $(FORMAT) $< $@ 

all:  $(HEX)

clean:
	rm -f *.o *.map *.out *.hex *.elf 

flash : $(HEX)
	#avrdude -p m32 -c avr910 -P /dev/ttyUSB0 -b 115200 -U flash:w:$(HEX)
	avrdude -c avrispv2 -P usb -p m32 -U flash:w:$(HEX)


