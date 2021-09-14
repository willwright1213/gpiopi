# gpiopi
A playground for gpio related stuff with my Raspberry Pi

## About

This repository is basically my play ground for building stuff that makes use of the gpio interface on the raspberry pi.

## RGBLight test

This script makes use of 3 potentiometer to control the current flow (modulation) of an RGB light. In other words, the color can change. Here is a video to show how it works:

https://streamable.com/kvzzin

## LCD Display

In the BSC folder there is code that handles the Broadcom Serial Controller in the BCM2711. The controller does support 10-bits slave address, however only the 7-bits is supported for now. To test its functionality I made a code to operate an LCD screen. you can compile the code as such:

```
cd bsc
g++ main.c lcd.c bsc.c -o test
./test
```
This assume that the address for the lcd screen is 0x27. (you can change it in the main.c source file). Once running you will be able to type a word and it will print on the lcd screen.

The LCD screen is my current work in progress. Most of the work so far has been reading relevant documentation to learn how the BSC works and how the LCD screen work. My current project is to make it more useful (i.e: printing sentence rather than just words and allow messages to scroll).

For BCM2711 datasheet:

https://datasheets.raspberrypi.org/bcm2711/bcm2711-peripherals.pdf

For the LCD datasheet:

https://www.sparkfun.com/datasheets/LCD/HD44780.pdf



