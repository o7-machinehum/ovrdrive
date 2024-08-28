# Overdrive Firmware
The firmware is just one source file and a header `ovrdrive.c` and `ovrdrive.h`. The hardware is an ATmega25 programmed from a TC2030 programming pad (J3). I have tested that it's also possible to use a 1mm pitch, 2x3 header by just holding it down to the pads for a quick and dirty program.

## Software Requirements
```
make
avr-gcc
avrdude
```

## Building
```
make
```

## Flashing
To flash you need an AVR ISP programmer (or an Arduino in ISP mode). 
```
make fuse
make flash
```
In the `rel` folder you will find the `ovrdrive_r1.elf` which is the firmware that was shipped with the device. You can flash this with the `make deploy`
