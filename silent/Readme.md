# Module: Silent

![](/silent/viewme.png)

## Name

[`MDL-echomods_emulator`]()

## Title

This is the module which emulates the signal coming from the analog processing chain.

## Description

* Teensy for its DAC.
* version: V0.1
* date: 26/07/2016
* cost:35$
* sourcing:Get from [Adafruit](https://www.adafruit.com/products/3056)
* technology: Adafruit Feather
* language: C
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-J_pulse_off`

### Outputs

* `ITF-R_reserved` which is a raw signal

## Key Components

* `Feather WICED`

## Information

### What is it supposed to do?

The aim of this echOmod is to simulate a raw signal that would come from the piezo and analog chain.

### How does it work: block diagram

![Block schema](/silent/source/blocks.png)

* `ITF-B_5v`->`Feather WICED`->`DAC`->`Biais removal`->`ITF-R_reserved`
* `ITF-J_pulse_off`->`5V to 3.3V`->`B5`->`Feather WICED`

## About the module

### Pros

* TBD

### Cons

* TBD

## Constraint and limits

#### Getting a signal 

With a simple code on feather WICED, managed to get a 1.8 - 2Mhz signal ( [code is here](/silent/software/featherWICED/SimpleSignalGenerator.ino) ).

![](/silent/software/featherWICED/SimpleSignalGenerator.png)

#### Look of the module

The pins needed to be rerouted, so an intermediary board was made ouf of stripboard

![](/silent/images/silent.png)

The interrupt was brought done to 3.3V instead of the 5V coming from the trinket pro, routed to pin B5.

#### Result with Goblin, the analog processing

##### Signal out of DAC

![](/silent/images/SilentOutput.JPG)

##### Signal out of Goblin

![](/silent/images/SilentEnveloppeFinal.JPG)

#### Why not a Feather WICED ?

* [Fading](https://github.com/adafruit/Adafruit_WICED_Arduino/blob/master/examples/Hardware/PWM/Fading/Fading.ino) as well 
* IT has two DACs : see [here](https://cdn-learn.adafruit.com/assets/assets/000/031/391/medium800/adafruit_products_WICEDPinout.jpg?1458753854) 

##### Interrupts:

If similar to the Feather M0Proto

* `#0 / RX - GPIO #0`, also receive (input) pin for Serial1 and Interrupt 2
* `#1 / TX - GPIO #1`, also transmit (output) pin for Serial1 and Interrupt 3
* `#2 / SDA - GPIO #2`, also the I2C (Wire) data pin. There's no pull up on this pin by default so when using with I2C, you may need a 2.2K-10K pullup. Also Interrupt #1
* `#3 / SCL - GPIO #3`, also the I2C (Wire) clock pin. There's no pull up on this pin by default so when using with I2C, you may need a 2.2K-10K pullup. Can also do PWM output and act as Interrupt 0.

### Why not a Teensy ?

Simplement (TEENSY) pour émuler un signal. A "high" speed DAC is required. Since the acquisition period is 200us, we should have say 2 periods over this, hence a period of 100us, that's a 10kHz signal we should see. At 20 pts per period, we should have roughly a 200kHz DAC.
* https://www.pjrc.com/teensy/td_timing_elaspedMillis.html
* https://forum.pjrc.com/attachment.php?attachmentid=2790&d=1413271011
* Pin Change teensy: https://www.pjrc.com/teensy/interrupts.html


## Discussions

### TODO

### DONE

* Feather: [work with an interrupt](/silent/software/featherWICED/SignalGenerator/SignalGenerator.ino)
* Write code for feather WICED
* Publish this code
* Remove Signal Bias
* Validated with a Feather WICED ([code](/silent/software/featherWICED/SimpleSignalGenerator.ino)).
* Feather: remove the average value before inputing in Goblin
* [Check output with Goblin](/silent/2016-08-09-SilentPlusTobo.md)

### People

* Kelu

## License

### Silent 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [silent](/silent/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018

