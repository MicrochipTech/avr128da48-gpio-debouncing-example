# AVR128DA48 GPIO Debouncing Example

This repository provides an Atmel Studio solution with a bare metal code example for a button debouncing. Using the event system, the button state change will trigger the timer configured in single shot mode. An interrupt on the timer is set to be activaed when the timer counter reaches the top value.

With this setup, when the button on the Curiosity Nano board is pressed, an interrupt will be triggered after ~32 milliseconds, when the button bouncing is over. In this example, the interrupt will turn on the LED0 when the button is pressed, and off when the button is released.

## Configurations

PC6 - LED0 led on Curiosity Nano board is configured as output pin

PC7 - SW0 button on Curiosity Nano board is configured as input pin with pull-up enable

EVSYS - Using Channel 3, PIN 7 of PORTC triggers the TCB0

TCB0 - Configured in Single Shot Mode

## Required Tools 

Software: ATMEL Studio and AVR-DA Device Packs

Hardware: AVR128DA48 Curiosity Nano

## Compatibility
The source code is compatible with the following devices: AVR128DA28, AVR128DA32, AVR128DA48, and AVR128DA64.
