# Module: Tom-Tom [](@description Analog processing module readme)

![](/tomtom/viewme.png)

## Name

[`MDL-rpiEchomods`]()

## Title

The Pi Heart of the echOmods

## Description

* A Pi W - wireless!
* version: V0.1
* date: 25/04/2017
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
* `ITF-E_signal_envelope`->`Jumper`->`Bomanz`->`RPi`
* `RPi`->`ITF-I_pulse_on`
* `RPi`->`ITF-J_pulse_off`
* `RPi`->`ITF-N_cc_motor_pwm`
* `RPi`->`/dev/charnode`->`Wifi`


## About the module

### Pros

* Building on an existing wireless device, the RPi 0 or RPi W
* Wireless server and documentation server

### Cons

* To be tested!

## Constraint and limits

* @todo

## Work

### Installation

* The image of the SD card for a PiW, along with the kernel module, scripts and all, is [available here](). Login 'pi' and password 'root'. Bad, I know. Change your wifi details in the `/etc/wpa_supplicant/wpa_supplicant.conf`. Once the pi has booted, you can _ssh pi@raspberrypi.local_ to connect to it. This [procedure rocks](https://raspberrypi.stackexchange.com/questions/1686/how-do-i-set-up-ssh-keys-to-log-into-my-rpi) to get your ssh keys on the device and not be bothered anymore.

* The image was created with 

```
 sudo dd if=/dev/sdc of=./rpi_kernel_module.img bs=1M
 gzip rpi_kernel_module.img
```

to flash it, (replacing the rdisk1 by the appropriate disk)

```
 gzip -dc rpi_kernel_module.img.gz | sudo dd of=/dev/rdisk1 bs=1m
```

The module is already compiled. It must be inserted by 

```
 ./run.sh
```

The module on the image creates the two pulses and listens to the ADC (if plugged in). It can be used as a standalone tool to test the pulser module, provided both jumpers on Doj v2 J2 jumpers connect Pon to Pon3 and Poff to Poff3.

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


* Testing the limits of ADC acquisition (speed / bits)
* Save images as DICOMs
* Understand why some GPIOs do not have lower values at 0..
* MixedGadget => [Storage + ethernet](http://isticktoit.net/?p=1383) or [this](https://gist.github.com/gbaman/50b6cca61dd1c3f88f41) or [that](https://learn.adafruit.com/turning-your-raspberry-pi-zero-into-a-usb-gadget/overview).
* Set pins to down [on boot](https://raspberrypi.stackexchange.com/questions/4664/setting-gpio-value-on-boot)

### DONE

* Developping a CA3306E version of [the 10Msps ADC pHAT](https://github.com/kelu124/bomanz/blob/master/CA3306E/20170422-FirstAcqs.ipynb) for testing.
* Dev a version of the [ADC08200](https://github.com/kelu124/bomanz/blob/master/ADC08200/)
* Create a kernel module
* Test the [PWM](http://www.toptechboy.com/raspberry-pi/raspberry-pi-lesson-28-controlling-a-servo-on-raspberry-pi-with-python/)

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

