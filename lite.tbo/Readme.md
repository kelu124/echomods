---
module: lite.tbo
author: kelu124
---

# Module: lite.tbo

![](/lite.tbo/viewme.png)

## Name

[`MDL-lite.tbo_hvpulser`]()

## Title

lite.tbo: the bipolar HV-pulser

## Description

* The second iteration of the HV-Pulser of the echOmods
* Setup? Soon a quickstart?
* version: V0.1
* cost:120$
* sourcing:Tindie
* date: 15/04/2018
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

![Block schema](/lite.tbo/source/blocks.png)

* `Pulse-P`->`TC6320TG`
* `Pulse-N`->`TC6320TG`
* `Damper`->`TC6320TG`
* `NMT0572SC`->`HV-N`->`TC6320TG`
* `NMT0572SC`->`HV-P`->`TC6320TG`->`ITF-mET_Transducer`
* `ITF-mET_Transducer`->`ITF-mET_SMA`
* `ITF-mET_Transducer`->`ITF-18_Raw`

## About the module

### Pros

* Cheaper, more robust than [tobo](/retired/tobo/)
* Less issues with the MD0100

### Cons

* As of today (20180305), the damper still lacks

## Constraint and limits

### Testing

[First tests are here ](/include/20180415a/Readme.md)

### Brief

#### Specs

* Needed to get a couple of 10's of ns wide square pulses, both in the positive and negative.
* Control of pulses must be through 3.3 or 5V tolerant logic
* Pulses height must be selectable (say with a jumper?) for ~20V, 40V, 80V (for positive pulses).
* Only power supply available is 5V

#### Components

* See this [application note](http://ww1.microchip.com/downloads/en/AppNotes/AN-H53.pdf) - recommend MD1213 and TC6320 
* Possible (but not used in the end) high voltage source: https://datasheets.maximintegrated.com/en/ds/MAX5025-MAX5028.pdf (3 -> 30V) to be used with a [555 DC-DC convertor](http://www.eleccircuit.com/the-many-dc-to-dc-converters-using-ic-555/)
* Signal back from the diod is clipped by [MD0100](http://ww1.microchip.com/downloads/en/DeviceDoc/MD0100.pdf) + back to back diods.  

#### Build docs

* [Source files](/lite.tbo/source/)
  * [Schematics](/lite.tbo/schematics.PDF)
  * [BOM](/lite.tbo/build/BOM.xls)
  * [Gerbers](/lite.tbo/build/Gerbers_10_03_2018.zip)
  * [ODB](/lite.tbo/build/odb.zip)
  * [Pickplace](/lite.tbo/build/PickPlace_10_03_2018.zip)

#### Power use

* Needs only 5V

#### Components

* HV: NMT0572SC
* Pulser : MD1213 and TC6320 -> see [Fig.6 here, bipolar 3 level pulser](http://ww1.microchip.com/downloads/en/AppNotes/AN-H53.pdf).
  * [TC6320, undamped](http://ww1.microchip.com/downloads/en/DeviceDoc/tc6320.pdf), detailed here. 
  * TC6320 http://ww1.microchip.com/downloads/en/DeviceDoc/20005697A.pdf for the datasheet
* Protection: MD0100+diods -- should be enough, see [bottom of page 1, or Fig 9](http://ww1.microchip.com/downloads/en/DeviceDoc/MD0100.pdf)

## Discussions

### TODO

* Review a bipolar design (originally alt.tbo -- but double the components and hence the price)

### DONE

* Preliminary testing

### People

* Ivan for the TC6320TG

## License

### echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [lite.tbo](/lite.tbo/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (kelu124@gmail.com) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Kelu124 (kelu124@gmail.com) 2015-2018
---
module: lite.tbo
author: kelu124
---

# Module: lite.tbo

![](/lite.tbo/viewme.png)

## Name

[`MDL-lite.tbo_hvpulser`]()

## Title

lite.tbo: the bipolar HV-pulser

## Description

* The second iteration of the HV-Pulser of the echOmods
* Setup? Soon a quickstart?
* version: V0.1
* cost:120$
* sourcing:Tindie
* date: 15/04/2018
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

![Block schema](/lite.tbo/source/blocks.png)

* `Pulse-P`->`TC6320TG`
* `Pulse-N`->`TC6320TG`
* `Damper`->`TC6320TG`
* `NMT0572SC`->`HV-N`->`TC6320TG`
* `NMT0572SC`->`HV-P`->`TC6320TG`->`ITF-mET_Transducer`
* `ITF-mET_Transducer`->`ITF-mET_SMA`
* `ITF-mET_Transducer`->`ITF-18_Raw`

## About the module

### Pros

* Cheaper, more robust than [tobo](/retired/tobo/)
* Less issues with the MD0100

### Cons

* As of today (20180305), the damper still lacks

## Constraint and limits

### Testing

[First tests are here ](/include/20180415a/Readme.md)

### Brief

#### Specs

* Needed to get a couple of 10's of ns wide square pulses, both in the positive and negative.
* Control of pulses must be through 3.3 or 5V tolerant logic
* Pulses height must be selectable (say with a jumper?) for ~20V, 40V, 80V (for positive pulses).
* Only power supply available is 5V

#### Components

* See this [application note](http://ww1.microchip.com/downloads/en/AppNotes/AN-H53.pdf) - recommend MD1213 and TC6320 
* Possible (but not used in the end) high voltage source: https://datasheets.maximintegrated.com/en/ds/MAX5025-MAX5028.pdf (3 -> 30V) to be used with a [555 DC-DC convertor](http://www.eleccircuit.com/the-many-dc-to-dc-converters-using-ic-555/)
* Signal back from the diod is clipped by [MD0100](http://ww1.microchip.com/downloads/en/DeviceDoc/MD0100.pdf) + back to back diods.  

#### Build docs

* [Source files](/lite.tbo/source/)
  * [Schematics](/lite.tbo/schematics.PDF)
  * [BOM](/lite.tbo/build/BOM.xls)
  * [Gerbers](/lite.tbo/build/Gerbers_10_03_2018.zip)
  * [ODB](/lite.tbo/build/odb.zip)
  * [Pickplace](/lite.tbo/build/PickPlace_10_03_2018.zip)

#### Power use

* Needs only 5V

#### Components

* HV: NMT0572SC
* Pulser : MD1213 and TC6320 -> see [Fig.6 here, bipolar 3 level pulser](http://ww1.microchip.com/downloads/en/AppNotes/AN-H53.pdf).
  * [TC6320, undamped](http://ww1.microchip.com/downloads/en/DeviceDoc/tc6320.pdf), detailed here. 
  * TC6320 http://ww1.microchip.com/downloads/en/DeviceDoc/20005697A.pdf for the datasheet
* Protection: MD0100+diods -- should be enough, see [bottom of page 1, or Fig 9](http://ww1.microchip.com/downloads/en/DeviceDoc/MD0100.pdf)

## Discussions

### TODO

* Review a bipolar design (originally alt.tbo -- but double the components and hence the price)

### DONE

* Preliminary testing

### People

* Ivan for the TC6320TG

## License

### echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [lite.tbo](/lite.tbo/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (kelu124@gmail.com) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Kelu124 (kelu124@gmail.com) 2015-2018
