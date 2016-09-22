# Module: Croaker

![](/croaker/viewme.png)

## Name

[`MDL-probe_echomods_controler_croaker`]()

## Title

The acquisition heart of the echOmods

## Description

* A STM32...
* version: V0.2
* date: 22/09/2016
* technology: STM32F205
* language: n/a
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-E_signal_envelope`
* `ITF-I_pulse_on`
* `ITF-J_pulse_off`

### Outputs

* `ITF-mED-TFT-Screen`
* `ITF-mED-OLED-Screen`
* `ITF-mEC-WiFi-UDP-Stream`


## Key Components

* `Feather WICED` : see notes


## Information

### What is it supposed to do?


The aim of this echOmod is to receive the signal and process it.


### How does it work: block diagram

![Block schema](source/blocks.png)

* `ITF-E_signal_envelope`->`Feather WICED`->`WiFi`
* `Feather WICED`->`ITF-mED-TFT-Screen`
* `Feather WICED`->`ITF-mEC-WiFi-UDP-Stream`

## About the module

### Pros

* Building on an existing STM32, compatible with the Arduino IDE

### Cons

* ADC is tough to master

## Constraint and limits

* A series of work has been done on ![EMW3165](notes_EMW3165.md),  ![ESP8266](notes_ESP8266.md), ![Raspberry Pi Zero](notes_RPi0.md), ![feather WICED](notes_feather_WICED.md). The EMW3165 gave birth to __[Kina](/kina/)__ for slow speed wireless UDP streaming.
* A recap of microcontrolers has been added [here](notes_uC.md)

## As of 22/09/2016

### Getting to work with two onboard ADCs. Getting a relatively nice signal.

In a nutshell: getting roughly 12bits, 2Msps+ ADC acquisition and Wifi-streaming, on a powerbank. [Read more here](/croaker/feather_tests/2016-09-10-Feather_ADC.md) for the details on the STM32 work.

### In images

#### Following unprocessed signal, 

![](/silent/Images/SilentOutput.JPG)

#### After enveloppe detection

![](/silent/Images/SilentEnveloppeFinal.JPG)


#### Out of the Croaker module

![](/croaker/feather_tests/SilentAcqDualADC.png)


## Discussions


### TODO


* Replace the work done by [OneEye](/oneeye/) by [Croaker](/croaker/).

### DONE

* Choose the platform (BBB, RPi0, STM32, ... ?) : that'll be a `Feather WICED`
* Getting some images
* Getting images onto a screen

### People

* ??

## License

### Croaker 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [croaker](/croaker/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018

