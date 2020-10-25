# Module: lit3rick [](@description up5k all-in-one board readme)

![](/lit3rick/viewme.png)

## Name

[`lit3rick`]()

## Title

A lightweight version of un0rick

## Description

* a up5k pHAT
* Setup? Just plug in
* Latest version: V2.0
* date: 25/09/2020
* technology: pcb
* language: upverter
* cost:350$
* sourcing:Tindie
* author: Kelu124

## IOs

### Inputs

* RPi IOs
* 5V
* HVp
* HVn
* GND

### Outputs

* RPi IOs
* Transmit SMA
* Receive SMA

## Key Components

* ice40 up5K

## Information

### What is it supposed to do?

The aim is to summarize all modules in a all-inclusive board. Fast ADC, good load of memory, good SNR.. the not-so-DIY module, as it comes already assembled with nothing to do. Based on up5k.


### How does it work: block diagram

![Block schema](/lit3rick/source/blocks.png)

* `up5k`->`SPI`->`Data Out`
* `up5k`->`PulserControl`->`Pulser`->`Transducer`
* `Transducer`->`Clipping`->`Time Gain Compensator`->`64Msps, 12-bit ADC`->`up5k`
* `up5k`->`DAC`->`Time Gain Compensator` 
* `Settings control`->`SPI`->`up5k`


## About the module

### Pros

* All inclusive!
* Cost effective 

### Cons

* No onboard HV
* Limited RAM

## Constraint and limits

* To be defined

## Discussions

### TODO

* Improve i2s transfers

### DONE

* Getting some signals proto!

### People

* Kelu124

## License

### lit3rick 

The [echOmods project](https://github.com/kelu124/echomods/) and its prototypes (amongst which we find the [lit3rick](/lit3rick/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (kelu124@gmail.com) 2018

### Based on 

This board is based on a previous TAPR projects from the same author, [Murgen](https://github.com/kelu124/murgen-dev-kit) and [echOmods project](https://github.com/kelu124/echomods/), or even [un0rick](https://github.com/kelu124/un0rick/)- and respects their  TAPR license.

Copyright Kelu124 (kelu124@gmail.com) 2020

