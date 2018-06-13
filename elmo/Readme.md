# Module: Elmo pHAT [](@description Main doc source for high speed Pi DAQ)

![](/elmo/viewme.png)

## Name

[`MDL-DAQ_elmo`]()

## Title

Using a dual ADC raspberry pHAT for 20Msps+ acquisition

## Description

* High speed ADC pHAT
* version: V2.0
* date: 05/03/2018
* cost:75$
* sourcing:OSHPark, MacroFab, Tindie
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


The aim of this module is to achieve 20Msps, at 9bits or more. 

### How does it work: block diagram

![Block schema](/elmo/source/blocks.png)

* `Raw Signal`->`ITF-12_RPIn`->`Selector`->`ADC`->`Buffer`->`Pi`->`Signal Digitalized`
* `Raw Signal`->`Onboard header`->`Selector`
* `+Vref/2 jumper`->`ADC`
* `GND`->`Selector`
* `External`->`Selector`
* `ITF-4_RawSig`->`Doj Jumper`->`ITF-12_RPIn`
* `ITF-11_OffSig`->`Doj Jumper`
* `ITF-3_ENV`->`Doj Jumper`

## About the module

### Pros

* High speed, 9 bit ADCs!
* Full [Altium source](/elmo/source/v2/elmov2_altium.zip), [Gerbers](/elmo/source/v2/elmov2_gerber.zip), [BOM](/elmo/source/v2/BOM.xls), [schematics](/elmo/source/v2/ADC_pHAT.pdf).
* [Driver](/elmo/software/driver.c) for the board.

### Cons

* SMDs is tough to assemble
* Linux is not real time: there will be inaccuracies in the measurements!
* Need a custom kernel module

## Constraint and limits

* See above ;)

### Discussions

#### Where can I get elements to play with ?

You can refer to the [20180415r](/include/20180415r/) experiment. It is made of a unipolar pulser, double ADC board, and analog processing board. The experiment documentations is based on :

* [Raspberry Pi drivers](/include/20180415r/driver.c) which create the /dev/ device on the raspberry pi from which a `cat /dev/hsdk/ > Datafile.DAT` extracts signals. The driver includes control for the pulser.
* An example of [Raw data](/include/20180415r/lit-tbo.DAT) that is created out of the driver
* [the Jupyter notebook](/include/20180415r/20180415r-lit.tbo.ipynb) which processes capture files from the ADC into signals
* the resulting [Processed data](/include/20180415r/lit-tbo.npz)

Even without the board, you can use an example of such a file to play with.

#### Let's start with the end: it works!

Testing the module with the [signal emulator module](/silent/), which yields a signal at 1.9MHz, it well seen at 1.9MHz, with a sampling speed equal to two times this freq, ie 24Msps ! See the details below:

![](/elmo/data/twoadcs.jpg)

#### Problem and solution

__Problem__ was that the Pi0 or PiW, with the current kernel module, can't run faster than around 10 to 12 Msps. Clock can be faster, but the _memcpy_ limits the transfer to memory. Soooo.. what can we do? As a reminder, I wanted at least a 10Msps 10bit ADC.

__Solution__ Why not interleaving two ADCs, with clocks in opposite phase? Hum that means 2 times 10 bits, and I had only 18 pins left once the Ultrasound SDK board connected. That means.. quite obviously, 2 times 9 bits.

So now I can run at twice the speed of the transfer, so a bit over 20Msps, over this time 9 bits. Or by oversampling, that could be 10Msps at 10 bits. __With more flexibility__ !

Win.

At least for the moment, now I need to order the PCBs and some components.

-> [BOM](/elmo/source/v2/BOM.xls) is around 30$ components, 5$ OSHPark PCB.. that's quite neat.

#### Raw signal acquisition and enveloppe with this ADC pHAT

With the enveloppe

![](/elmo/data/arduino/EnveloppeLineEnveloppe.jpg)

With the raw signal

![](/elmo/data/arduinoffset/LineImageEnveloppe.jpg)


#### First acquisitions:

See the [jupyter notebook](/elmo/data/20170609-NewADC-v3.ipynb):

![](/elmo/images/3rdAcq-low.png)

Issues: bugs in connected ADC pins + no offset really

#### What does v2 look like ?

![](/elmo/source/v2/3d.jpg)

and the corresponding [schematics (PDF)](/elmo/source/v2/ADC_pHAT.pdf).

#### What does it look like ?

##### Without headers

![](/elmo/images/20180414_224236.jpg)

##### On the motherboard

__Beware__ the motherboard is designed to have the phat assembled as shown below

![](/elmo/images/20170717_210209.jpg)

or as below:

![](/include/20180415r/20180415_121351.jpg)

### TODO

* Lots

### DONE

* Write the [Quickstart](/elmo/QuickStart.md)
* Getting a board an soldering some ADCs
* Understand GPIO [mem mapping](/elmo/data/20170609-NewADC.ipynb)
* Get raw data with [offset vref/2](/elmo/data/arduinoffset/20170612-ArduinoFFTed.ipynb)
* Tests with a single ADC at 11Msps
* Produce a batch of [rev2 elmo](/elmo/source/v2/elmov2_altium.zip)

### People

* @ivan for his help on altium

## License

### RetroATL3 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [ADC pHAT](/elmo/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (kelu124@gmail.com) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Kelu124 (kelu124@gmail.com) 2015-2018

