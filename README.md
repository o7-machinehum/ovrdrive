# Ovrdrive
![](img/drive_built.png)

Ovrdrive is a purpose built security focused usb drive. If the user doesn't lick their fingers while inserting the drive it will appear completely blank. It is entirely open source and all the tools used to build it are open source. There is a blog series listed below with more information for the curious.

## Content
 - [First Blog Post](https://interruptlabs.ca/2022/07/29/I-m-Building-a-Self-Destructing-USB-Drive/)
 - [Second Blog Post](https://interruptlabs.ca/2022/08/31/I-m-Building-a-Self-Destructing-USB-Drive-Part-2/)
 - [YouTube Content](https://youtu.be/Wrcy6ySjSu8)

## Parts
  - ATTINY24A-CCUR  - BGA version
  - ATTINY24-20PU   - DIP version
  - K9gag08u0e-Scb0 - NAND Flash
  - SM3255AA        - What dmesg thinks the chip is
  - SM3257EN        - Part number on the chip
  - SM3257ENAA      - Reported by SMI Mass Production Tool
  - 838-22-004-10-001101

## Notes
```
[machinehum@whitebox Star_SM3257ENAA_N0726]$ find . -iname "SM3257ENAA*.FFW"
./UFD_ALL_ForceFW/SM3257ENAA.FFW
```
This is the "ISP" or firmware, source: https://www.usbdev.ru/articles/a_smi/ispcantbefound/

## SMI Mass QC tool
Settings Password: 320
Debug Password: 1111

## Links and Notes
  - [Russian Site 1](https://www.usbdev.ru/articles/testmod/)
  - [Russian Site 2](https://www.usbdev.ru/files/smi/)
  - [SMI MP Tool](https://www.usbdev.ru/files/smi/smimptool/)
  - [Notes on Flash](https://www.elinfor.com/knowledge/practical-guide-for-flash-memory-p-10889)
  - [SMI MP Tool 2](https://flashboot.ru/files/file/243/)
  - [ST's Part](https://www.st.com/en/microcontrollers-microprocessors/st72681.html)
