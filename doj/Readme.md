# Module: Doj ![](@description Motherboard readme)

![](/doj/viewme.png)

## Name

[`MDL-echomods_motherboard`]()

## Title

The motherboard of the echomods

## Description

* A stripboard
* version: V2.0
* date: 04/06/2017
* technology: pcb
* language: kicad
* cost:5$
* sourcing:Anywhere for [stripboard](https://www.amazon.com/s/ref=nb_sb_noss_2?url=node%3D667846011&field-keywords=stripboard&rh=n%3A667846011%2Ck%3Astripboard). Or PCB from [OSHPark](https://oshpark.com/shared_projects/2taE6p4M) if you can order by 3. Or [straight from Tindie](https://www.tindie.com/products/kelu124/ultrasound-modules-motherboard/).
* author: Kelu124

## IOs

### Inputs

* Power supply

### Outputs

* Signal =)

## Key Components

* PCB

## Information

### What is it supposed to do?

Getting a motherboard: that's fitting all the modules in an easy way, with an easy access to all tracks. See [this](/doj/source/2.0-kicad) for the Kicad files.


### How does it work: block diagram

## About the module

### Pros

* Half of a A4 sheet .. that's the target!  

### Cons

* Maybe can introduce noise.

## Constraint and limits

### v1.0: Initial design

As in mind 

![](/doj/images/IMG_2607.JPG)

Now with the actual modules

![](/doj/images/doj-simple.png)

### v1.1: Adding new modules

#### Loaded

![](/doj/images/doj-loaded.jpg)

#### Unloaded

![](/doj/images/doj-unloaded.jpg)

### v1.2: PCB 

With the [OSHPark](https://oshpark.com/shared_projects/2taE6p4M) PCB, coming from the [brief](/doj/brief.md).

![](/doj/images/oshp.png)

### v2.0: A clean PCB for rasbperry

![](/doj/images/doj-v2.png)

![](/doj/images/doj_v2.jpg)



## Discussions


### TODO

* Change the viewme

### DONE

* [PCB on OSHPark](https://oshpark.com/shared_projects/2taE6p4M)
* Having the list of strips accessible
* Design
* Assemble it
* Test it
* Adapt power supply from v2 - smaller board footprint
* Add a level shifter been Pon 3.3 and 5 and Poff 3.3 and 5
* A bit more space around the Pi0/PiW headers
* Proper silkscreening around the Pi0 headers (they are reversed)
* Jumper for the ADC in.. and selector (enveloppe and amplified signal) (either to Feather or to ADC .. and dedicated pin on Rpi)
* SPI from RPi to Oled... or SPI to screen (to be checked in both case) .. or both kept, there are two SPI


### People

* Kelu124

## License

### Doj 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [doj](/doj/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018

