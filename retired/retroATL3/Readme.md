# Module: RetroATL3

![](/retroATL3/viewme.png)
![](/retired/retroATL3/viewme.png)

## Name

[`MDL-probe_retroATL3`]()

## Title

Retrohacking the ATL Access 3 probe

## Description

* Retroengineering of ATL Access 3
* version: V0.1
* date: 15/07/2016
* technology: Hacking the ATL Access 3
* language: n/a
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-F_12V`
* `ITF-N_cc_motor_pwm`
* `ITF-mET_Transducer`
* `Motor`
* `Tri-Piezo Head`

### Outputs

* `Motor`
* `ITF-mET_Transducer`
* `Tri-Piezo Head`

## Key Components

* `ATL3`

## Information

### What is it supposed to do?


The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former ATL3.


### How does it work: block diagram

![Block schema](source/blocks.png)

* `ITF-mET_Transducer`->`Tri-Piezo Head`->`ITF-mET_Transducer`
* `ITF-N_cc_motor_pwm`->`Motor`


## About the module

### Pros

* Simple to use

### Cons

* We have removed the position system : we don't have the encoding system
* Tough to find a old ATL Access 3  probe

### Constraint and limits

* Motor is a 12V... doesn't move below 10V ... using 300mA@10V -- we could use a [5V to 12V DC/DC boost similar to this one](https://www.pololu.com/product/2117/specs). Could feed onto the 5V entry and leave on the 12V output. Can be found on Gotronics and such. Or the 12V could be delivered to the board itself.
* How many pizeos??
* Oil to be found to replace lost one =) Feeback: linseed oil seems good !

* Tested with murgen : not really pratical to use, maybe to be replaced with a simple 3MHz probe. [Read the full test on murgen's repo](https://github.com/kelu124/murgen-dev-kit/blob/master/worklog/Session_9_ATL.md).

* __It seems that the noise previously seen with the bitscope was due to the computer! Not to the bitscope.__
* We have found an interesting doc: the ATL manual for the ultrasound machine - and specs for the whole set of transducers -- [found here](/include/ultramark/UltraMark_4-Manual.pdf)


## Discussions

### Tests 

An echo appears with [Murgen](https://github.com/kelu124/murgen-dev-kit), gain at 0.6V

![](images/TEK0005.JPG)

### TODO

* Finding the pins mapping
* Motor in action
* Get pictures

### DONE

* Refill Oil
* Test echoes
* Make Videos

### People

* ?

## License

### RetroATL3 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [RetroATL3](/RetroATL3/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018

