# Module: Tom-Tom [](@description Analog processing module readme)

![](/tomtom/viewme.png)

## Name

[`MDL-rpiEchomods`]()

## Title

The Pi Heart of the echOmods

## Description

* A Pi W - wireless!
* version: V0.1
* date: 25/04/2016
* technology: RPiW
* language: python / kernel
* cost:10$
* sourcing: Get the Pi W from [plenty of sources](https://www.raspberrypi.org/products/pi-zero-w/)
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-E_signal_envelope`
* `ITF-I_pulse_on`

### Outputs

* `ITF-I_pulse_on` : on 3.3V
* `ITF-J_pulse_off`: on 3.3V
* `ITF-C_amplified_raw_signal`: Amplified Raw Signal, post TGC, before the enveloppe detection	
* `ITF-E_signal_envelope`: enveloppe of the signal, post TGC
* `ITF-N_cc_motor_pwm`

## Key Components

* `RPi` : see notes
* `Bomanz`: the ADC pHAT

## Information

### What is it supposed to do?

The aim of this echOmod is to digitalize the signal, and to control the pulser, servo, ...

### How does it work: block diagram

![Block schema](/tomtom/source/blocks.png)

* `ITF-C_amplified_raw_signal`->`Bomanz`
* `ITF-E_signal_envelope`->`Bomanz`->`RPi`
* `RPi`->`ITF-I_pulse_on`
* `RPi`->`ITF-J_pulse_off`
* `RPi`->`ITF-N_cc_motor_pwm`



## About the module

### Pros

* Building on an existing wireless device, the RPi 0 or RPi W

### Cons

* To be tested!

## Constraint and limits

* @todo

## Work

### Checking if it works with the [pulser](/tobo/)

It does! Pulses are :

![](/tobo/images/2017/TEK0008.JPG)

and the ouput of the pulser is:

![](/tobo/images/2017/TEK0009.JPG)



### Mapping the pins

@todo : mapping the pins shared between PWM, pHAT and tracks
* [Testing GPIOs](/tomtom/20170425-ExploringGPIOs.md)

## Discussions

### TODO

* Test the PWM
* Testing the limits of ADC acquisition (speed / bits)
* Save images as DICOMs
* Understand why some GPIOs do not have lower values at 0..

### DONE

* Developping a CA3306E version of [the 10Msps ADC pHAT](https://github.com/kelu124/bomanz/blob/master/CA3306E/20170422-FirstAcqs.ipynb) for testing.

### People

* Kelu124

## License

### TomTom 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [tomtom](/tomtom/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018

