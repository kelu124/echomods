# Module: pic0rick [](@description rp2040 all-in-one board readme)

![](/pic0rick/viewme.png)

## Name

[`pic0rick`]()

## Title

A lightweight version of un0rick

## Description

* a rp2040
* Setup? Just plug in
* Latest version: V1.0
* date: 13/04/2024
* technology: pcb
* language: kicad
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

* rp2040
## Information

### What is it supposed to do?

The aim is to summarize all modules in a all-inclusive board. 


### How does it work: block diagram

![Block schema](/pic0rick/source/blocks.png)

* `rp2040`->`SPI`->`Data Out`
* `rp2040`->`PulserControl`->`Pulser`->`Transducer`
* `Transducer`->`Clipping`->`Time Gain Compensator`->`64Msps, 12-bit ADC`->`rp2040`
* `rp2040`->`DAC`->`Time Gain Compensator` 
* `Settings control`->`SPI`->`rp2040`


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

### pic0rick 

The [echOmods project](https://github.com/kelu124/echomods/) and its prototypes (amongst which we find the [pic0rick](/pic0rick/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (kelu124@gmail.com) 2018
