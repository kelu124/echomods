---
module: tobo
author: kelu124
---

# Module: Tobo

![](/tobo/viewme.png)

## Name

[`MDL-tobo_hvpulser`]()

## Title

Tobo: the HV-pulser

## Description

* The HV-Pulser of the echOmods
* Setup? Have a look at the [quick start guide](/tobo/QuickStart.md)
* version: V0.2
* cost:120$
* sourcing:Custom made, get the [Gerbers](/tobo/source/), [buy it preassembled on tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/) or contact @kelu124
* date: 24/04/2016
* technology: Module-compatible, Homemade PCB, ICs based on `HV7360` and `R05-100B`
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

* `HV7360`
* `R05-100B`

## Information

### What is it supposed to do?

The aim of this echOmod is to get the HV Pulse done.

### How does it work: block diagram

![Block schema](/tobo/source/blocks.png)

* `ITF-9_Pon`->`HV7360`
* `ITF-10_Poff`->`HV7360`
* `ITF-2_VDD_5V`->`R05-100B`->`HV7360`->`ITF-mET_Transducer`
* `ITF-mET_Transducer`->`ITF-mET_SMA`
* `ITF-mET_Transducer`->`ITF-18_Raw`

## About the module

### Pros

* Only needs 5V and 3.3V
* Energy use : TODO
* Using any logic voltage for PulseOn and PulseOff is a pplus
* Can use the potentiometer to control the tension
* Modularity through jumpers and SMA

### Cons

* Takes a lot of space because of the modularity. SMA, jumpers and pots could be removed.

* Little flexibility from the use of ICs.
* There's no impedance matching for the pulser to the transducer, could be better.

## Constraint and limits

### The pulser-control

![](/tobo/images/2017/TEK0008.JPG)

### Output signal

![](/tobo/images/2017/TEK0009.JPG)

### With and without a pulser - no impedance adaptation

![](/tobo/images/TEK0008.JPG)

![](/tobo/images/TEK0007.JPG)

### Look of the schematics

![](/tobo/images/schema-tobo.png)

and [a link to it](/tobo/tobo_schematics.pdf) (plus some bonus with the [map](/tobo/tobo_map.PDF)). 

Source files include [Altium](/tobo/source/Tobo-Altium-II.zip) and [KiCad](/tobo/source/Tobo-Kicad.zip) - along with the [BOM](/tobo/source/tobo_bom.xls).


### Look of the actual board

![](/tobo/images/tobo-2.png)

### Availability of HV7360

* Some issues with the availability of the `HV7360`, living its end of life. The latest version of [Altium](/tobo/source/Altium/) and [Kicad](/tobo/source/Kicad/) source files should show the new [HV7360 CABGA](/tobo/datasheets/HV7360_CABGA.pdf).
* However, this latest should be available officially in Jan 2017.


### Setting up the module

Setup? Have a look at the [quick start guide](/tobo/QuickStart.md) on how to prepare the pulser.

### On the way towards a simpler board

![](/alt.tbo/alt.tbo/source/pulser-3d.png)

[The alt design](/alt.tbo/) (and the corresponding [the schematics](/alt.tbo/draft.alt.tobo.v0.01pdf)  + [BOM](/alt.tbo/source/v2/BOM.v2.macrofab.xlsx) ).



## Discussions


### TODO


### DONE

* Writing specs 
* HV7360 has been updated
* Sending microcircuits to Edgeflex
* Agreeing on the strips/tracks 
* Defining the ICs to use to pulse
* Getting schematics
* Publishing schematics
* Receive the module
* Test it with different transducers
* Publish the sources in KiCAD

### People

* Sofian (for preparing the field with Murgen)

## License

### echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [Tobo](/tobo/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (kelu124@gmail.com) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Kelu124 (kelu124@gmail.com) 2015-2018


