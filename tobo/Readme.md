# Module: Tobo

![](/tobo/viewme.png)

## Name

[`MDL-tobo_hvpulser`]()

## Title

Tobo: the HV-pulser

## Description

* The HV-Pulser of the echOmods
* version: V0.1
* date: 24/04/2016
* technology: Module-compatible, Homemade PCB, ICs based on `HV7360` and `R05-100B`
* language: Altium
* author: Kelu124


## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-I_pulse_on`
* `ITF-J_pulse_off`
* `ITF-S_3_3v`

### Outputs

* `ITF-R_reserved` : for the signal coming from the transducer
* `ITF-mET_SMA` : for the signal coming out to the signal processing (if through SMA)
* `ITF-mET_Transducer` : for the signal coming out of the pulser (if through SMA)

## Key Components

* `HV7360`
* `R05-100B`

## Information

### What is it supposed to do?

The aim of this echOmod is to get the HV Pulse done.

### How does it work: block diagram

![Block schema](source/blocks.png)

* `ITF-I_pulse_on`->`HV7360`
* `ITF-J_pulse_off`->`HV7360`
* `ITF-B_5v`->`R05-100B`->`HV7360`->`ITF-mET_Transducer`
* `ITF-mET_Transducer`->`ITF-mET_SMA`
* `ITF-mET_Transducer`->`ITF-R_reserved`

## About the module

### Pros

* Only needs 5V and 3.3V
* Energy use : TODO
* ADC V_REF is flexible: using PulseOn and PulseOff
* Can use the potentiometer to control the tension
* Modularity through jumpers and SMA

### Cons

* Takes a lot of space because of the modularity. SMA, jumpers and pots could be removed.
* Little flexibility from the use of ICs.

## Constraint and limits

## Discussions

### TODO

* Send microcircuits to Edgeflex
* Receive the module
* Test it with different transducers
* Publish the sources in KiCAD

### DONE

* Specs to write
* Agreeing on the strips 
* Defining the ICs to use
* Getting schematics

### People

* Sofian (for preparing the field with Murgen)

## License

### echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [Tobo](/tobo/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018







