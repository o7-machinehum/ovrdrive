# Ovrdrive
![](img/drive_built.png)

Ovrdrive is a purpose built security focused usb drive. If the user doesn't plug it in three times rapidly, the drive it will appear completely blank. It is entirely open source and all the tools used to build it are open source. 


## Getting this Code
I've added quite a bit of git lfs content, I will eventually remove all this, but for now you probably don't want to check this out. You can do so like this

    GIT_LFS_SKIP_SMUDGE=1 git clone git@github.com:o7-machinehum/ovrdrive.git

## Content
 - [Blog Post](https://interruptlabs.ca/2022/07/29/I-m-Building-a-Self-Destructing-USB-Drive/)
 - [YouTube Content](https://youtu.be/Wrcy6ySjSu8)


## Firmware
```
cd fw
make deploy
```
