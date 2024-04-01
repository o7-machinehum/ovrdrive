# Generic AVR Makefile
# Fuse Programming Take from: http://www.engbedded.com/fusecalc/

MCU_TARGET     = attiny24

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

deploy: fuse flash

clean:
	@echo =====Cleaning=====
	rm $(TARGET).elf $(TARGET).hex

rebuild: clean build
all: build flash fuse
