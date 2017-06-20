# Raspberry Pi based ultrasound imaging


## Introduction

### Context 

This project was born at the end of 2015, when I built a ultrasound tool kit, and then wanted to split a bigger board into smaller modules. I went on exploring different options, combination of modules, hardware, probes, motors, and DAQ (from STM32s to Beaglebone PRUDAQ, passing through onboard smaller ADCs), which yielded lots of interesting results. I really enjoyed exploring all of this, and really learnt a lot. Who know I'd do this when 18 months ago I didn't know anything about electronics hardware (or at least had forgotten all from the golden age of my studies?).

Anyhow, the goal here is simple. I need a stand-alone "exploring tool" to explore ultrasound systems. I have built several versions with Murgen, and have made the proof that it's possible to have a small ultrasound machine in your garage. However, I found more pleasure in building the tools and in the process of digging into the different components.. and that's what I want to explore in this project.

Hardware is basically already built: previous lessons from the Murgen dev-kit have lead to the analog front end, what remains is to remove overkills on the circuits, and SIMPLIFY everything, making it more robust and more user friendly. The second step will be to have a good driver for the Raspberry Pi (which I believe is enough for my needs), to control the hardware, and develop a good enough server API.

### What is this?

This tool is based on the previous work done (like murgen, but was not simple enough), to get a ultrasound imaging dev kit. In short, this is a modularized version of Murgen, all equipped for imaging, based on two ad-hoc ultrasound boards, a Raspberry, a custom ADC, and a motherboard.

This HSDK has for objective to:

- consolidate existing hardware research;
- simplify and lower the cost of the kit;
- permits benchmarking of ultrasound systems;
- introduce a simple API to control hardware;
- have a server which provides both raw ultrasound and data standard DICOM files;
- have a kit that can be used for pedagogical and academic purposes - not to mention people who want to understand ultrasound!

This dev kit can be used in other projects such as dopplers, non-destructive testing, using piezos as sensors, ... 

## Architecture

Ultrasound imaging has evolved since the first ultrasound machine appeared. The first devices were using single-sensor (transducers) techniques, coupled with mechanical scanning. The architecture of such systems, as shown below, is well-known and formed the basis of ultrasound imaging.

![](http://openhardware.metajnl.com/articles/10.5334/joh.2/joh-1-2-g1.png/?action=download)

This kit consists of several modules mainly built from easily available components - after a short benchmark of [existing ICs](https://kelu124.gitbooks.io/echomods/content/Chapter6/bench.html). Two electronic modules were specifically designed to provide the basic development kit. 

* the Transducer Pulser Module (TPM): designed to provide a precise high-voltage pulse, necessary to excite the sensor, while remaining robust enough to be controlled by an Arduino;
* the Analog Processing Module (APM): designed to correctly process the raw ultrasound electric signal, while easily exposing all intermediary signals, and exposing a digital output to the user.

A modular approach was chosen to ensure that each key component inside the ultrasound image processing can easily be replaced and compared with another module. Each electronic module takes the place of a function in the signal processing chain or allows tapping into the different signals circulating between the blocks. 

### Approach

* Mono element, one channel, one ADC
* Approach: module
* 3 modules to be designed

* Costs

## Experiments

### Setup

![](Images)

## Different DAQs

STM32 - PRUDAQ - now myDAQ

![](Comparatif Bitscope / PRUDAQ / STM32 / ADC)

## Results / images


## So what?

### Big lessons

* Start with common elements
* Accept challenges
* Share

### Next steps

On a hardware side:

* The pulser-module design uses only two inputs and one high voltage source. However, the chip enables more complex uses as a pulser, which can be further explored.
* A multiplexer module can be used, to interface this single channel kit with an array probe. Doing this would permit to do synthetic aperture imaging, and to characterize as well each element in the array.
* A whole field left unexplored so far is that of the transducer. As the key sensor in the kit, it would be interesting to explore relevant technologies to develop an open and accessible transducer.
* Quite interestingly, it would be interesting to merge all modules once again on one RaspberryPi3-compatible hat

On a software side:

* The Raspberry Pi can be used a bit more. From a software point of view, the modules could be wirelessly controlled, leveraging the existing wireless communication channel, so that researchers can use a single unit for a laboratory, controlled from personal computers.
* The images will need to be stored in a DICOM-compatible format. 


### Articles refering to a Raspberry Pi challenge

* [ ] http://www.ndt.net/forum/thread.php?&rootID=56263
* [ ] https://www.raspberrypi.org/forums/viewtopic.php?f=37&t=96679
* [ ] https://www.reddit.com/r/raspberry_pi/comments/5mwgm9/anyone_use_a_raspberry_pi_to_make_a_diy_ultrasound/
* [ ] https://raspberrypi.stackexchange.com/questions/37013/using-pi-to-read-1-mhz-analog-ultrasound-signals

