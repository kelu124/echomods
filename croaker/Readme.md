# Module: Croaker [](@description Analog processing module readme)

![](/croaker/viewme.png)

## Name

[`MDL-probe_echomods_controler_croaker`]()

## Title

The acquisition heart of the echOmods

## Description

* A STM32...
* version: V0.3
* date: 15/11/2016
* technology: STM32F205
* language: n/a
* cost:35$
* sourcing:Get Feather from [Amz](http://amzn.to/2eGzlbG ) or [Adafruit](https://www.adafruit.com/products/3056). [OLED at Amz](http://amzn.to/2gi0vHl)
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

![Block schema](/croaker/source/blocks.png)

* `ITF-E_signal_envelope`->`Feather WICED`->`WiFi`
* `Feather WICED`->`ITF-mED-TFT-Screen`
* `Feather WICED`->`WiFi`->`ITF-mEC-WiFi-UDP-Stream`



## About the module

### Pros

* Building on an existing STM32, compatible with the Arduino IDE

### Cons

* ADC is tough to master

## Constraint and limits

* A series of work has been done on ![EMW3165](/croaker/notes_EMW3165.md),  ![ESP8266](/croaker/notes_ESP8266.md), ![Raspberry Pi Zero](/croaker/notes_RPi0.md), ![feather WICED](/croaker/notes_feather_WICED.md). The EMW3165 gave birth to __[Kina](/retired/kina/)__ for slow speed wireless UDP streaming.
* A recap of microcontrolers has been added [here](/croaker/notes_uC.md)



## Some images

They can be [found here](/croaker/data/examples/). 

They have been acquired with `nc -lu 5005` to listen to data coming from UDP port 5005, then translated in images using the [CreateCSV.py](/croaker/data/examples/CreateCSV.py) script, which creates the raw data files, ready to be processed, respecting the format, and scan converted using the [CreateSC.py](/croaker/data/examples/CreateSC.py) script for a nearest neighbour scan conversion.

## Boosting the ADC work

### Getting to work with two onboard ADCs. Getting a relatively nice signal.

#### September:

In a nutshell: getting roughly 12bits, 2Msps+ ADC acquisition and Wifi-streaming, on a powerbank. [Read more here](/croaker/feather_tests/2016-09-10-Feather_ADC.md) for the details on the STM32 work. [Arduino code here, with details for setup](/croaker/feather_tests/2ADC2UDP.ino).

Video is [here](https://www.youtube.com/watch?v=iyfDMsgAquI).

#### December:

Later on, in december, I got it work with a [breadboard phantom](/croaker/data/20161217/20161217-TestingArduinoAndPhantom.md)

### In images

#### In vs Out : in a nutshell


#### Out of the Croaker module

![](/croaker/feather_tests/SilentAcqDualADC.png)

#### Following unprocessed signal, 

![](/silent/images/SilentOutput.JPG)

#### After enveloppe detection

![](/silent/images/SilentEnveloppeFinal.JPG)

## Discussions

### TODO

* Replace the work done by [OneEye](/oneeye/) by [Croaker](/croaker/).
* Get better total ADC speed with an iterleaved move

### DONE

* Choose the platform (BBB, RPi0, STM32, ... ?) : that'll be a `Feather WICED`
* Getting some images
* Getting images onto a screen

### People

* Kelu124

## License

### Croaker 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [croaker](/croaker/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018

