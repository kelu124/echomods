# Module: Cletus

![](/cletus/viewme.png)

## Name

[`MDL-echomods_servopiezo`]()

## Title

The object containing the different modules.

## Description

* The servo/transducer part of the echOmods
* version: V0.1
* date: 29/04/2016
* technology:  
* language:  
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-N_cc_motor_pwm`
* `ITF-S_3_3v`
* `ITF-mET_Transducer` : for the signal coming out of the pulser (if through SMA)
* `ITF-mET_Piezo` : connection to the piezo

### Outputs

* `ITF-mET_Piezo` : connection to the piezo
* `ITF-mET_Transducer` : for the signal coming out of the pulser (if through SMA)

## Key Components

* Servo
* Piezo

## Information

### What is it supposed to do?

The aim of this module is to interface the transducer and the servo, aka the physical parts, to the analog part of the modules chain.


### How does it work: block diagram

![Block schema](/cletus/source/blocks.png)

## About the module

### Pros

* Simple to use

### Cons

* Slow sweeping

### Constraint and limits

## Discussions


### TODO

* Choose the design once the modules are done
* Get to work with Arthur

### DONE

* Checking Arthur availability

### People

* ?

## License

## Cletus 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (so Cletus) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

## Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018


