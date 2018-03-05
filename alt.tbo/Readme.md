---
module: alt.tbo
author: kelu124
---

# Module: alt.Tbo

![](/alt.tbo/viewme.png)

## Name

[`MDL-alt.tbo_hvpulser`]()

## Title

alt.tbo: the bipolar HV-pulser

## Description

* The second iteration of the HV-Pulser of the echOmods
* Setup? Soon a quickstart?
* version: V0.3
* cost:120$
* sourcing:Tindie
* date: 24/09/2017
* technology: Module-compatible, Homemade PCB, ICs based on `TC6320TG` and `NMT0572SC`
* language: Altium
* author: Kelu124


## IOs

### Inputs

* `ITF-1_GND`
* `ITF-2_VDD_5V`
* `ITF-9_Pon` 
* `ITF-10_Poff` 
* `ITF-19_3.3V`
* `ITF-mET_Transducer` : signal coming back	

### Outputs

* `ITF-18_Raw`  : for the signal coming from the transducer
* `ITF-mET_SMA` : for the signal coming out to the signal processing (if through SMA)
* `ITF-mET_Transducer` : for the signal coming out of the pulser (if through SMA)

## Key Components

* `TC6320TG`
* `NMT0572SC`

## Information

### What is it supposed to do?

The aim of this echOmod is to get the HV Pulse done.

### How does it work: block diagram

![Block schema](/alt.tbo/source/blocks.png)

* `Pulse-P`->`TC6320TG`
* `Pulse-N`->`TC6320TG`
* `Damper`->`TC6320TG`
* `NMT0572SC`->`HV-N`->`TC6320TG`
* `NMT0572SC`->`HV-P`->`TC6320TG`->`ITF-mET_Transducer`
* `ITF-mET_Transducer`->`ITF-mET_SMA`
* `ITF-mET_Transducer`->`ITF-18_Raw`

## About the module

### Pros

* Cheaper, more robust than [tobo](/tobo/)
* Less issues with the MD0100

### Cons

* As of today (20180305), the damper still lacks

## Constraint and limits

### Testing

* First experiment [jupyter notebook](/alt.tbo/test/20170930-AltPulser.ipynb) and first [datasets](/alt.tbo/test/)
* [Driver for raspberry pi](/alt.tbo/test/alt.bilevel.c)
* More tests with [fixed depth experiment](/alt.tbo/20171001a/20171001-new.ipynb) (for pulse quality tests).


### Images

#### Alone

![](/alt.tbo/test/images/20170930_175000.jpg)

#### Testing with a fixed depth of water

![](/alt.tbo/20171001a/20171001_135041.jpg)

#### Tests with 3 levels of HV (25, 50 and 75V) - unipolar
![](/alt.tbo/test/pulser.jpg)


#### Details of pulses at 50V

![](/alt.tbo/20171001a/Pulses_average_Tube.jpg)

### Brief

#### Specs

* Needed to get 200ns wide square pulses, both in the positive and negative.
* Control of pulses must be through 3.3 or 5V tolerant logic
* Pulses height must be selectable (say with a jumper?) for ~20V, 40V, 80V (for positive pulses) and -20, -40V, and -80V for negative.
* Only power supply available is 5V

#### Components

* See this [application note](http://ww1.microchip.com/downloads/en/AppNotes/AN-H53.pdf) - recommend MD1213 and TC6320 
* Possible (but not used in the end) high voltage source: https://datasheets.maximintegrated.com/en/ds/MAX5025-MAX5028.pdf (3 -> 30V) to be used with a [555 DC-DC convertor](http://www.eleccircuit.com/the-many-dc-to-dc-converters-using-ic-555/)
* Signal back from the diod is clipped by [MD0100](http://ww1.microchip.com/downloads/en/DeviceDoc/MD0100.pdf) + back to back diods.  

#### Power use

To be powered at 5V only.

#### Components

* HV: NMT0572SC
* Pulser : MD1213 and TC6320 -> see [Fig.6 here, bipolar 3 level pulser](http://ww1.microchip.com/downloads/en/AppNotes/AN-H53.pdf).
  * [TC6320, undamped](http://ww1.microchip.com/downloads/en/DeviceDoc/tc6320.pdf), detailed here. 
  * TC6320 http://ww1.microchip.com/downloads/en/DeviceDoc/20005697A.pdf for the datasheet
* Protection: MD0100+diods -- should be enough, see [bottom of page 1, or Fig 9](http://ww1.microchip.com/downloads/en/DeviceDoc/MD0100.pdf)

## Discussions

### TODO

* Check a design w/ [this idea](/alt.tbo/images/md1811_ref.jpg) which is similar to [this other idea](/alt.tbo/images/md1210_ref_2.jpg) or [this last idea](/alt.tbo/images/md1210_ref.jpg).

### DONE

* Preliminary tests

### People

* Sofian (for preparing the field with Murgen)
* Ivan for the TC6320TG

## License

### echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [alt.tbo](/alt.tbo/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (kelu124@gmail.com) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Kelu124 (kelu124@gmail.com) 2015-2018
