# Module: Kina

![](/kina/viewme.png)

## Name

[`MDL-echomods_UDP-slow-streamer`]()

## Title

The module streaming ADC data to UDP.

## Description

* WiFi ADC!
* version: V0.1
* date: 26/07/2016
* technology: EMW3165
* language: n/a
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-S_3_3v`
* `ITF-E_signal_envelope`
* `ITF-I_pulse_on`

### Outputs

* `ITF-mEC-WiFi-UDP-Stream`
* `ITF-mED-TFT-Screen`
* `ITF-I_pulse_on`
* `ITF-J_pulse_off`
* `ITF-N_cc_motor_pwm`

## Key Components

* `EMW3165`

## Information

### What is it supposed to do?

The aim of this echOmod is to acquire the enveloppe of the signal and stream it. Designed for slow (~64 lines / s) acquisitions.


### How does it work: block diagram

![Block schema](/kina/source/blocks.png)

* `ITF-I_pulse_on`->`EMW3165`->`WiFi UDP Stream`
* `EMW3165`->`SPI`->`OLED 128x64 screen`
* `ITF-E_signal_envelope`->`EMW3165`

## About the module

### Pros

* TODO

### Cons

* TODO

### Constraint and limits

## Discussions


### TODO

* Get the code up and running
* Try to get the pulser there as well (timers)
* Get several samples per position to average then stream
* Output data to a 128x64 OLED screen

### DONE

* TODO

### People

* Kelu

## License

### Sleepy 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [Kina](/kina/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018

