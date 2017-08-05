# Module: Elmo pHAT [](@description Main doc source for high speed Pi DAQ)

![](/elmo/viewme.png)

## Name

[`MDL-DAQ_AD9200`]()

## Title

Using a dual ADC raspberry extension for 20Msps+ DAQ

## Description

* High speed ADC pHAT
* version: V1.3
* date: 10/06/2017
* cost:45$
* sourcing:OSHPark, MacroFab
* technology: SMD, AD9200
* language: n/a
* author: Kelu124

## IOs

### Inputs

* `ITF-1_GND`
* `ITF-2_VDD_5V`
* `ITF-19_3.3V`
* `ITF-12_RPIn`

### Outputs

* `Signal Digitalized`

## Key Components

* `AD9200`

## Information

### What is it supposed to do?


The aim of this module is to achieve 10Msps, ideally 20Msps, at 9bits or more. Inspired from the [Bomanz]() project as well, which tried several high-speed ADCs setup for Raspberry Pi.


### How does it work: block diagram

![Block schema](/elmo/source/blocks.png)

* `Raw Signal`->`ITF-12_RPIn`->`ADC`->`Buffer`->`Pi`->`Signal Digitalized`
* `ITF-4_RawSig`->`ITF-12_RPIn`
* `ITF-11_OffSig`->`ITF-12_RPIn`
* `ITF-3_ENV`->`ITF-12_RPIn`

## About the module

### Pros

* High speed, 9 bit ADCs!

### Cons

* SMDs is tough to assemble?

## Constraint and limits


* Still being debugged




### Discussions

#### Let's start with the end: it works!

Testing the module with the [signal emulator module](/silent/), which yields a signal at 1.9MHz, it well seen at 1.9MHz, with a sampling speed equal to two times this freq, ie 24Msps ! See the details below:

![](/elmo/data/twoadcs.jpg)

#### Problem and solution

__Problem__ was that the Pi0 or PiW, with the current kernel module, can't run faster than around 10 to 12 Msps. Clock can be faster, but the _memcpy_ limits the transfer to memory. Soooo.. what can we do? As a reminder, I wanted at least a 10Msps 10bit ADC.

__Solution__ Why not interleaving two ADCs, with clocks in opposite phase? Hum that means 2 times 10 bits, and I had only 18 pins left once the Ultrasound SDK board connected. That means.. quite obviously, 2 times 9 bits.

So now I can run at twice the speed of the transfer, so a bit over 20Msps, over this time 9 bits. Or by oversampling, that could be 10Msps at 10 bits. __With more flexibility__ !

Win.

At least for the moment, now I need to order the PCBs and some components.

-> BOM is around 30$ components, 5$ OSHPark PCB.. that's quite neat.

#### Raw signal acquisition and enveloppe with this ADC pHAT

![](/elmo/data/arduino/LineImageEnveloppe.jpg)


![](/elmo/data/arduinoffset/LineImageEnveloppe.jpg)


#### First acquisitions:

See the [jupyter notebook](/elmo/data/20170609-NewADC-v3.ipynb):

![](/elmo/images/3rdAcq-low.png)

Issues: bugs in connected ADC pins + no offset really

#### What does it look like ?

__Top in 3D__

![](/elmo/top-3d.png)

__Bottom in 3D__

![](/elmo/bot-3d.png)


### TODO

* Lots
* Produce a batch of [rev2 elmo](/elmo/source/ADCpHat_r2.zip)

### DONE

* Getting a board an soldering some ADCs
* Understand GPIO [mem mapping](/elmo/data/20170609-NewADC.ipynb)
* Get raw data with [offset vref/2](/elmo/data/arduinoffset/20170612-ArduinoFFTed.ipynb)
* Tests with a single ADC at 11Msps

### People

* @ivan for his help on altium

## License

### RetroATL3 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [ADC pHAT](/elmo/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018





