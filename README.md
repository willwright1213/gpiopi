# gpiopi
A playground for gpio related stuff with my Raspberry Pi

## About

This repository is basically my play ground for building stuff that makes use of the gpio interface on the raspberry pi.

## RGBLight test

This script makes use of 3 potentiometer to control the current flow (modulation) of an RGB light. In other words, the color can change. Here is a video to show how it works:

https://streamable.com/kvzzin

## LCD Display

This is my current work in progress. The LCD display I'm using is soldered with an I2C interface which means it only needs 4 connections rather than 16. To make use of i2c with
Pi we need to use the Broadcom Serial Control which is specified in the Datasheet(https://datasheets.raspberrypi.org/bcm2711/bcm2711-peripherals.pdf). I am currently figuring out how to send commands properly to the BSC so that the LCD receives the proper instructions. The model of the LCD is LCD1602b and uses 4-bit operations.

