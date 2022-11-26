# Generic AVR Makefile
# Fuse Programming Take from: http://www.engbedded.com/fusecalc/

# MCU_TARGET     = at90s2313
# MCU_TARGET     = at90s2333
# MCU_TARGET     = at90s4414
# MCU_TARGET     = at90s4433
# MCU_TARGET     = at90s4434
# MCU_TARGET     = at90s8515
# MCU_TARGET     = at90s8535
# MCU_TARGET     = atmega128
# MCU_TARGET     = atmega1280
# MCU_TARGET     = atmega1281
# MCU_TARGET     = atmega1284p
# MCU_TARGET     = atmega16
# MCU_TARGET     = atmega163
# MCU_TARGET     = atmega164p
# MCU_TARGET     = atmega165
# MCU_TARGET     = atmega165p
# MCU_TARGET     = atmega168
# MCU_TARGET     = atmega169
# MCU_TARGET     = atmega169p
# MCU_TARGET     = atmega2560
# MCU_TARGET     = atmega2561
# MCU_TARGET     = atmega32
# MCU_TARGET     = atmega324p
# MCU_TARGET     = atmega325
# MCU_TARGET     = atmega3250
# MCU_TARGET     = atmega329
# MCU_TARGET     = atmega3290
# MCU_TARGET     = atmega32u4
# MCU_TARGET     = atmega48
# MCU_TARGET     = atmega64
# MCU_TARGET     = atmega640
# MCU_TARGET     = atmega644
# MCU_TARGET     = atmega644p
# MCU_TARGET     = atmega645
# MCU_TARGET     = atmega6450
# MCU_TARGET     = atmega649
# MCU_TARGET     = atmega6490
# MCU_TARGET     = atmega8
# MCU_TARGET     = atmega8515
# MCU_TARGET     = atmega8535
# MCU_TARGET     = atmega88
# MCU_TARGET     = attiny2313
MCU_TARGET     = attiny24
# MCU_TARGET     = attiny25
# MCU_TARGET     = attiny26
# MCU_TARGET     = attiny261
# MCU_TARGET     = attiny44
# MCU_TARGET     = attiny45
# MCU_TARGET     = attiny461
# MCU_TARGET     = attiny84
# MCU_TARGET     = attiny85
# MCU_TARGET     = attiny861

# Target file name
TARGET = ovrdrive

# List of C source files and object files
SRC =	$(TARGET).c

# Executable names
COMPILER = avr-gcc
COPY = avr-objcopy
DFU = avrisp2

# Generated user string
USER = $(shell whoami)

# Misc arguments
FRQ = 8000000
DEFS = -Wp,-DF_CPU=$(FRQ)UL
LIBS = -lm
OPT = s #s = size, 0 = none, 3 = maximum
STD = gnu99

build: version
	@echo =====Compiling=====
	$(COMPILER) -mmcu=$(MCU_TARGET) $(DEFS) -O$(OPT) $(LIBS) -std=$(STD) $(SRC) -o $(TARGET).elf
	@echo =====Making .hex File=====
	$(COPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature $(TARGET).elf $(TARGET).hex
	@echo =====Build Done=====

version:
	@echo =====Version=====
	@$(COMPILER) --version
	@echo =================

flash: build
	@echo =====Programming Board=====
	avrdude -p $(MCU_TARGET) -c $(DFU) -e -U flash:w:$(TARGET).elf
	@echo =====Programming Done=====

fuse:
	# -avrdude -p $(MCU_TARGET) -c $(DFU) -U lfuse:w:0xa4:m -U hfuse:w:0xd8:m
	-avrdude -p $(MCU_TARGET) -c $(DFU) -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

clean:
	@echo =====Cleaning=====
	rm $(TARGET).elf $(TARGET).hex

rebuild: clean build
all: build flash fuse
