# Module: oneeye  [](@description Standalone pulser control unit - readme)

![](/retired/oneeye/viewme.png)

## Name

[`MDL-oneeye_controlunit`]()

## Title

One-eye, the controler

## Description

* The controler heart of the echOmods
* version: V0.1
* cost:10$
* sourcing:from [Adafruit](https://www.adafruit.com/product/2000)
* date: 26/04/2016
* technology: Module-compatible
* language: Altium
* author: Kelu124

## IOs

### Inputs

* `ITF-3_ENV`
* `ITF-1_GND`
* `ITF-2_VDD_5V`


### Outputs

* `ITF-7_GAIN` 
* `ITF-9_Pon` 
* `ITF-10_Poff` 
* `ITF-14_PWM` 


## Key Components

* `ArduinoTrinketPro`

## Information

### What is it supposed to do?

The module aims at making a microcontroler, for the moment the `ArduinoTrinketPro`, usable with the motherboard and the set of modules.

As the controler the module is at the heart of the control interfaces, and in the case of the echOmod set of modules, in the Pulser controls (signals I and J), as well as the Gain Control and the servo control (hence position).

A simple arduino code is [presented here](/retired/oneeye/oneye_pulser.ino).

### How does it work: block diagram

![Block schema](/retired/oneeye/source/blocks.png)

* `ITF-2_VDD_5V`->`ArduinoTrinketPro`->`ITF-7_GAIN` 
* `ArduinoTrinketPro`->`ITF-9_Pon` 
* `ArduinoTrinketPro`->`ITF-10_Poff` 
* `ArduinoTrinketPro`->`ITF-14_PWM` 

## About the module

### Pros

* Based on a breadboard alim

### Cons

* Takes a lot of space 

## Constraint and limits

### Layout on the motherboard

![](/retired/oneeye/images/oneeye-trinket.png)

## Discussions

### TODO

* Find the code back

### DONE

* First test with Arduino Trinket

### People


## License


### echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [One-Eye](/retired/oneeye/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018


