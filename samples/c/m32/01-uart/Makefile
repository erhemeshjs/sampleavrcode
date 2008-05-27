# Makefile Test
#
include ../Makefile.rules
#
# Definition der Object-Files
OBJ = 01-uart.o
HEX = 01-uart.hex
#

CFLAGS=-Os -g -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I .

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

program : $(HEX)
	avrdude -c $(PROG) -P $(SERIAL) -p $(MCU) -U flash:w:$(HEX)

