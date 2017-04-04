# ATmega-BLE
A simple demo for Arduino UNO R3 (ATmega328p) + BLE communication.

## Features:
- BLE debug app on mobile phone send a character to Arduino, and the Arduino return it back;
- if BLE send a character 'A' --> turn on the on board LED;
- if BLE send a character 'B' --> turn off the on board LED.

## Usage:
- using "avr-gcc + avrdude" toolchain (ref4);
- use `make flash` to compile and upload codes to MCU;
- Please disconnect Rx pin on Arduino when uploading code, since Arduino's USART port is shared with usb.

## Hardware connections:
- ATmega pins <--->   BLE module pins
- Rx (PD0)    <--->   Tx
- Tx (PD1)    <--->   Rx
- VCC         <--->   VCC
- GND         <--->   GND


## BLE module:
- “LinkSprite”, BLE4.0 Shield based on TICC2541 (ref3)


## BLE app on mobile phone:
- “LightBlue” on App store


## References:
1. Williams E. AVR Programming: Learning to Write Software for Hardware[M]. Maker Media, Inc., 2014.
2. ATmega328p datasheet
3. http://learn.linksprite.com/arduino/shields/how-to-use-ble4-0-shield/ (BLE module)
4. http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/ (avr-gcc + avrdude toolchain)
