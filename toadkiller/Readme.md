# Module: ToadKiller dog

![](/toadkiller/viewme.png)

## Name

[`MDL-echomods_prudaq`]()

## Title

This is the module to get high-speed (40Msps) signal acquisition.

## Description

* PRUDAQ
* version: V0.1
* date: 02/08/2016
* technology: PRUDAQ
* language: Who knows?
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-S_3_3v`
* `ITF-E_signal_envelope`

### Outputs

* `WiFi UDP Stream`
* `ITF-mED-TFT-Screen`
* `ITF-I_pulse_on`
* `ITF-J_pulse_off`
* `ITF-N_cc_motor_pwm`

## Key Components

* `BBB`
* `PRUDAQ`

## Information

### What is it supposed to do?


The aim of this echOmod is to simulate the enveloppe (or maybe soon the raw signal) that would come from the piezo and analog chain.

### How does it work: block diagram

![Block schema](/prudaq/source/blocks.png)

* `ITF-B_5v`->`BBB`->`PRUDAQ`->`BBB`->`File`
* `ITF-E_signal_envelope`->`PRUDAQ`
* `BBB`->`SPI`->`TFT Screen`

## About the module

### Pros


* Dual-channel simultaneously-sampled 10-bit ADC
* Up to 20MSPS per channel (40MSPS total) (but see below)
* 0-2V input voltage range (DC coupled)
* 4:1 analog switches in front of each channel provide a total of 8 single-ended analog inputs. (See here for differential input)
* SMA jacks for direct access to the 2 ADC channels
* Flexible clock options:
    * External input via SMA jack
    * Internal onboard 10MHz oscillator
    * Programmable clock from BeagleBone GPIO pins


### Cons

* Input signals outside the 0-2V range may damage the ADC
* Inputs are DC-coupled
* We provide a 1V reference for mid-scale, but it's unbuffered
* At 40MSPS the 1GHz ARMv7 only has 25 cycles per sample (and at least 25% of that is eaten by DMA overhead)
* Round-robin sampling across the 8 analog inputs is tricky
* As the previous section points out, you can buffer samples into the 512MB of main memory, but there's no way to get the samples into storage or off the board at the full 40MSPS data rate

### Constraint and limits

#### The 0-2V limit

The enveloppe signal (0-3.3V) coming from Goblin is clipped beforehands with 2 diodes, giving a 0-1.5V range with easy components.

#### Learn more

##### From BeagleLogic:

    grep -rnw '/path/to/somewhere/' -e "pattern"

* https://github.com/abhishek-kakkar/BeagleLogic/wiki/sysfs-attributes-Reference

* https://github.com/abhishek-kakkar/BeagleLogic/wiki

BeagleLogic can be used stand-alone for doing binary captures without any special client software.

     dd if=/dev/beaglelogic of=mydump bs=1M count=1

is sufficient to grab a binary dump, once sample rate has been configured via sysfs.


#### Install 

* Image pour PRUDAQ : https://docs.google.com/uc?id=0B72G9e_R3TcnNGFZSEF4bDNYU00&export=download

* https://raw.githubusercontent.com/RobertCNelson/boot-scripts/master/tools/eMMC/init-eMMC-flasher-v3.sh

* https://github.com/google/prudaq/wiki/QuickStart#option-1-use-the-beaglelogic-system-image

dd if=./beaglelogic-prudaq-system.img of=/dev/mmcblk0 bs=1M count=1

http://elinux.org/Beagleboard:Expanding_File_System_Partition_On_A_microSD


## Discussions

### TODO

* Do the quick check up

### DONE

* Nothing

### People

* PRUDAQ people !
* Kelu

## License

### Silent 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [toadkiller](/toadkiller/) module) are open hardware, and working with open-hardware components.

### Based on 

The following work is base on a previous Apache License project, [PRUDAQ](https://github.com/google/prudaq/).
