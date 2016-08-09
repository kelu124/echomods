# Module: Mogaba

![](/mogaba/viewme.png)

## Name

[`MDL-mogaba_small_powersupply`]()

## Title

Mogaba, the power supply

## Description

* The alimentation of the echOmods
* version: V0.1
* date: 
* technology:
* language: 
* author: Kelu124

## IOs

### Inputs

* `ITF-mEM_Alimentation`
* `ITF-F_12V`

### Outputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-F_12V`
* `ITF-S_3_3v`

## Key Components

* The voltage regulation `BreadBoardAlim` module

## Information

### What is it supposed to do?

The aim of this echOmod is to get 3.3V and 5V done.

### How does it work: block diagram

![Block schema](/mogaba/source/blocks.png)

* `ITF-mEM_Alimentation`->`BreadBoardAlim`->`ITF-B_5v`
* `BreadBoardAlim`->`ITF-B_3_3v`

## About the module

### Pros

* Based on a breadboard alim

### Cons

* Takes a lot of space 

## Constraint and limits

### Testing different alims

Quality of the power supply is key: it can introduce noise in the final 

#### 8V input, stabilized power supply

![](/include/images/2016-08-09/TEK0004.JPG)

#### 7.5V, "clean" power supply (Settable voltage)

![](/include/images/2016-08-09/TEK0005.JPG)

#### 12V, crappy power supply (amazon) 

![](/include/images/2016-08-09/TEK0006.JPG)


## Discussions

### TODO

* :thought_balloon: benchmark power supplies 

### DONE

* Manage to feed it 12V
* Bring power to it through the 12V `ITF-F_12V` track 
* Test if 12V OK
* Find supplier

### People


## License


### echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [Mogaba](/mogaba/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018
