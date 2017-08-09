# Module: Loftus  [](@description Piezo+Servo module)

![](/loftus/viewme.png)

## Name

[`MDL-echomods_integratedhead`]()

## Title

Recycling an existing head

## Description

* The scanning part
* version: V0.1
* date: 04/08/2017
* technology: Chinese
* cost:200$
* sourcing:Recycling a transducer and motor from China
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

* `Motor`
* `Piezo`

## Information

### What is it supposed to do?

The aim of this module is to recycle a previous head


### How does it work: block diagram

![Block schema](/loftus/source/blocks.png)

* `ITF-mET_Piezo`->`Piezo`->`ITF-mET_Piezo`
* `ITF-N_cc_motor_pwm`->`Servo`
* `ITF-B_5v`->`Servo`

## About the module

### Discussion

#### Suppliers ?

Ask me =)

### Pros

* Simple to use

### Cons

* To be determined ;)

## Constraint and limits

* TBD

## Discussions

### TODO

* TBD

### DONE

* Identifying a supplier

### People

* Thanks Anna ;)

## License

### Cletus 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (so Loftus) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (kelu124@gmail.com) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Kelu124 (kelu124@gmail.com) 2015-2018


