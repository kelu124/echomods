# Mogaba 

## In a nutshell

Getting a module, based on the echomods methodology, which simulates the behavior of the transducer + pulser component.

It could ideally  work alone with the microcontroler (+ ADC + ... ? modules).

## Specs

* This module, given a logic pulse (~100-300ns), answers with a signal that is basically linearly decreasing 
* from 2V at t = 0, to 0V at t = 200us, 
* which is a 3.5MHz sine signal, whose enveloppe follows a 1MHz sine. 

So basically f(t) = 2V*(sin(2pi 3.5MHz t )*sin (2 pi 1MHz))*(200us-t)

The module has access to 5V and 3.3V alim


### Questions

* What is the acceptable sine waves' distortion level? 
* What is the output power?


# License

## echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [Mogaba](/mogaba/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

## Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018
