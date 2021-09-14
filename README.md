# gpiopi
A playground for gpio related stuff with my Raspberry Pi

## About

This repository is basically my play ground for building stuff that makes use of the gpio interface on the raspberry pi.

## RGBLight test

This script makes use of 3 potentiometer to control the current flow (modulation) of an RGB light. In other words, the color can change. Here is a a schematic provided by https://freenove.com in their tutorial book on how to use the raspberry pi:

![schematc](https://github.com/willwright1213/gpiopi/blob/main/schema.png)

## LCD Display

In the BSC folder there is code that handles the Broadcom Serial Controller in the BCM2711. The controller does support 10-bits slave address, however only the 7-bits is supported for now. To test its functionality I made a code to operate an LCD screen. you can compile the code as such:

```
cd bsc
g++ main.c lcd.c bsc.c -o test
sudo ./test
```
This assumes the following:

1. you connected the LCD screen to SDA1/SCL1 (this can be changed in bsc.c)
2. the address to the peripheral is 0x27 (this can be changed in main.c)

When you execute test you can input non-spaced words, and it will output to the lcd screen. Typing another word will clear what's on the screen before sending the commands.

The LCD screen is my current work in progress. Most of the work so far has been reading relevant documentation to learn how the BSC works and how the LCD screen work. My current project is to make it more useful (i.e: printing sentence rather than just words and allow messages to scroll).


=== Source ===

For BCM2711 datasheet:

https://datasheets.raspberrypi.org/bcm2711/bcm2711-peripherals.pdf

For the LCD datasheet:

https://www.sparkfun.com/datasheets/LCD/HD44780.pdf



