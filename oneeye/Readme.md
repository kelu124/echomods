# Module: oneeye

![](/oneeye/viewme.png)

## Name

[`MDL-oneeye_controlunit`]()

## Title

One-eye, the controler

## Description

* The controler heart of the echOmods
* version: V0.1
* date: 26/04/2016
* technology: Module-compatible
* language: Altium
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-S_3_3v`

### Outputs

* `ITF-G_gain_control`
* `ITF-I_pulse_on`
* `ITF-J_pulse_off`
* `ITF-N_cc_motor_pwm`

## Key Components

* `ArduinoTrinketPro`

## Information

### What is it supposed to do?

The module aims at making a microcontroler, for the moment the `ArduinoTrinketPro`, usable with the motherboard and the set of modules.

As the controler the module is at the heart of the control interfaces, and in the case of the echOmod set of modules, in the Pulser controls (signals I and J), as well as the Gain Control and the servo control (hence position).

### How does it work: block diagram

![Block schema](/oneeye/source/blocks.png)

* `ITF-B_5v`->`ArduinoTrinketPro`->`ITF-G_gain_control`
* `ArduinoTrinketPro`->`ITF-I_pulse_on`
* `ArduinoTrinketPro`->`ITF-J_pulse_off`
* `ArduinoTrinketPro`->`ITF-N_cc_motor_pwm`

## About the module

### Pros

* Based on a breadboard alim

### Cons

* Takes a lot of space 

## Constraint and limits

### Layout on the motherboard

![](images/oneeye-trinket.png)

## Discussions

### TODO

### DONE

* First test with Arduino Trinket

### People


## License


### echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [One-Eye](/oneye/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018


