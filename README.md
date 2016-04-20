# echomods

Creating modules out of the murgen board


# Modules foreseen 

## Basics 
### Alim 

Out of a stripboard at first

Made from the breadboard alims, since I only need 5 and 3.3

### HV+Pulser

Ongoing, PCB, 2 layers, RECOM-based. 

### TGC/VGA + enveloppe detection + 2Msps SPI ADC.

Classic from murgen, plus we'll need more learning with ADCs!

### Arduino Control 

Stripboard + Arduino Trinket Pro

## Further

Once this is done, two things are to be done, to discover STM32's, and transducer simulations !

### STM32's

Let's see and explore if a STM32 can handle acquisition, streaming of data, datalogging onto a SD card, and mapping data onto a small 1.8" TFT. That'd be interesting.

### A simulator
To benchmark the signal processing path, the HV+Pulser component can be replaced by a passive setup, which will provide a target.

### Adapted piezo mecanics

Indeed !

# License

## echOmods 

The echOmods project and its prototypes are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2016

## Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2016
