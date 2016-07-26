# Module: Silent

![](/silent/viewme.png)

## Name

[`MDL-echomods_emulator`]()

## Title

This is the module which emulates the signal coming from the analog processing chain.

## Description

* Teensy for its DAC.
* version: V0.1
* date: 26/07/2016
* technology: Teensy 3.2
* language: C
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-S_3_3v`
* `ITF-I_pulse_on`
* `ITF-J_pulse_off`

### Outputs

* `ITF-E_signal_envelope`

## Key Components

* `Teensy 3.2`

## Information

### What is it supposed to do?


The aim of this echOmod is to simulate the enveloppe (or maybe soon the raw signal) that would come from the piezo and analog chain.

### How does it work: block diagram

![Block schema](/silent/source/blocks.png)

* `ITF-B_5v`->`Teensy 3.2`->`DAC`->`ITF-E_signal_envelope`
* `ITF-I_pulse_on`->`Teensy 3.2`

## About the module

### Pros

* TBD

### Cons

* TBD

### Constraint and limits

## Discussions


### TODO

* 

### DONE

* 

### People

* Kelu

## License

### Silent 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [silent](/silent/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018

