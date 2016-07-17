# Module: Retro10PV

![](/elmo/viewme.png)
![](/retired/elmo/viewme.png)

## Name

[`MDL-echomods-FeatherWICED`]()

## Title

Microcontroler and WiFi

## Description

* Playing with FeatherWICED
* version: V0.1
* date: 18/07/2016
* technology: FeatherWICED
* language: n/a
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-E_signal_envelope`

### Outputs

* `WiFi`
* `Screen`
* `ITF-G_gain_control`
* `ITF-I_pulse_on`
* `ITF-J_pulse_off`
* `ITF-N_cc_motor_pwm`

## Key Components

* `FeatherWICED`

## Information

### What is it supposed to do?


The aim of this echOmod is to get be the microcontroller heart


### How does it work: block diagram

![Block schema](source/blocks.png)

* `ITF-E_signal_envelope`->`WiFi`
* `ITF-E_signal_envelope`->`Screen`

## About the module

### Pros

* Simple to use

### Cons

* FeatherWICED IDE is difficult to manage

### Constraint and limits

* Readmore with [adafruit FWICED_Introduction](doc/FWICED_Introduction.pdf)
* STM32 - [datasheet](doc/FWICED_STM32.pdf)


## Discussions

### TODO

* Integrate more controls
* `sudo usermod -aG dialout <myuser>`

### DONE

* Basic code

### People

* Igor

## License

### Elmo 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [Elmo](/elmo/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018

