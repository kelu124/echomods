# Module: un0rick [](@description ice40 all-in-one board readme)

![](/matty/viewme.png)

## Name

[`MDL-un0rick`]()

## Title

The motherboard of the echomods

## Description

* The motherboard for the modules
* Setup? Have a look at a [quick example](/matty/20180224b/Readme.md)
* Latest version: V1.0
* date: 25/02/2018
* technology: pcb
* language: upverter
* cost:250/350$
* sourcing:to come
* author: Kelu124

## IOs

### Inputs

* Power supply
* Probe

### Outputs

* Signal =)

## Key Components

* ice40 hx4k

## Information

### What is it supposed to do?

The aim is to summarize all modules in a all-inclusive board. Fast ADC, good load of memory, good SNR.. the not-so-DIY module, as it comes already assembled with nothing to do =)


### How does it work: block diagram

![Block schema](/matty/source/blocks.png)

* `ice40`->`SPI`->`Data Out`
* `ice40`->`PulserControl`->`Pulser`->`Transducer`
* `Transducer`->`Clipping`->`Time Gain Compensator`->`64Msps, 10-bit ADC`->`ice40`
* `ice40`->`Time Gain Compensator`
* `ice40`->`motor control`->`feedback`->`ice40`
* `Settings control`->`SPI`->`ice40`


## About the module

### Pros

* All inclusive!
* Cost effective 

### Cons

* v1.0 has still some issues

## Constraint and limits

### v1.0: Initial design

* Some issues are left, need to take care of as in [next steps](/matty/nextsteps.md)
* Interesting [first result](/matty/20180224b/Readme.md), summarized below:

#### Getting images from a [retroATL3](/retroATL3/) probe.

![](/matty/20180225a/probe.jpg)

![](/matty/20180225a/line70.jpg)

(see the [readme](/matty/20180225a/Readme.md) )

#### Setup

![](/matty/20180224b/images/IMG_20180224_195210.jpg)

* [Acquiring the signal](/matty/20180224b/20180221b-Server.ipynb)
* [On the computer / processing side](/matty/20180224b/20180221b-Client.ipynb)
* [The FPGA binary](/matty/20180224b/20180224b-binary.bin)

#### Results

![](/matty/20180224b/images/kk-1-VGA@0x11-spimode1-21msps.jpg)

#### Fooling around

##### Extracting spectrum analysis of this line

![](/matty/20180224b/images/fft.jpg)

##### Playing with the gain setting

![](/matty/20180224b/images/comparing_gain.jpg)

### Controling the pulser works!

* Checked [here](/matty/images/hv/PonPoff_test/Readme.md)

![](/matty/images/hv/PonPoff_test/75V_Piezo.png)

## Discussions

### TODO

* See the [next steps](/matty/nextsteps.md)
* Having it work with a [retroATL3](/retroATL3/)

### DONE

* Getting some signals!

### People

* Kelu124

## License

### Matty 

The [echOmods project](https://github.com/kelu124/echomods/) and its prototypes (amongst which we find the [matty-un0rick](/matty/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (kelu124@gmail.com) 2018

### Based on 

This board is based on a previous TAPR projects from the same author, [Murgen](https://github.com/kelu124/murgen-dev-kit) and [echOmods project](https://github.com/kelu124/echomods/)- and respects their  TAPR license.

Copyright Kelu124 (kelu124@gmail.com) 2018

