
[](@description Using a Raspberry Pi to image)

## Introduction


### Context 

This project was born at the end of 2015, when I built a ultrasound tool kit, and then wanted to split a bigger board into smaller modules. I went on exploring different options, combination of modules, hardware, probes, motors, and DAQ (from STM32s to Beaglebone PRUDAQ, passing through onboard smaller ADCs), which yielded lots of interesting results. I really enjoyed exploring all of this, and really learnt a lot. Who know I'd do this when 18 months ago I didn't know anything about electronics hardware (or at least had forgotten all from the golden age of my studies?).

Anyhow, the goal here is simple. I need a stand-alone "exploring tool" to explore ultrasound systems. I have built several versions with Murgen, and have made the proof that it's possible to have a small ultrasound machine in your garage. However, I found more pleasure in building the tools and in the process of digging into the different components.. and that's what I want to explore in this project.

Hardware is basically already built: previous lessons from the Murgen dev-kit have lead to the analog front end, what remains is to remove overkills on the circuits, and SIMPLIFY everything, making it more robust and more user friendly. The second step will be to have a good driver for the Raspberry Pi (which I believe is enough for my needs), to control the hardware, and develop a good enough server API.


### Objective

Based on the previous work done with different solutions, to get a ultrasound imaging dev kit, I want to:

- consolidate existing hardware research;
- simplify and lower the cost of the kit;
- permits benchmarking of ultrasound systems;
- introduce a simple API to control hardware;
- have a server which provides raw ultrasound data, and for ultrasound imaging, can deliver standard DICOM files;
- have a kit that can be used for pedagogical and academic purposes - not to mention people who want to understand ultrasound!

Murgen has prooved the feasibility of the hardware, but was not simple enough. Let's keep the momentum, and apply this dev kit to other projects as well - such as dopplers, non-destructive testing, using piezos as sensors,

Cost of materials should be around 200-250$.

More info on the basis of this work: http://openhardware.metajnl.com/articles/10.5334/joh.2/

### Way of work

Anyhow, the goal here is simple. I need a "exploring tool" to explore ultrasound systems. I have built several versions with Murgen, and have made the proof that it's possible to have a small ultrasound machine in your garage. However, I found more pleasure in building the tools and in the process of digging into the different components.. and that's what I want to explore in this project.

Hardware is basically already built: previous lessons from [Murgen](https://hackaday.io/project/9281-murgen) bring the analog front end, a hack I have can be used to emulate a probe: what remains is to remove overkills on the circuits, and SIMPLIFY everything, making it more robust and more user friendly.

The second step will be to have a good driver for the Raspberry Pi (which I believe is enough for my needs), to control the hardware, and develop a good enough server API.

Once this is done, I'll be happy to test it with probes like the ATL probes I've been debugging, with [doppler probes](https://hackaday.io/project/19685-early-and-low-cost-detection-of-heart-failure) projects here and also to explore [this chinese probe of mine](https://hackaday.io/project/20533-improving-a-chinese-wireless-ultrasound-probe).

So, on with this project, and see if cross-pollination works =) 

## Architecture

Ultrasound imaging has evolved since the first ultrasound machine appeared. The first devices were using single-sensor (transducers) techniques, coupled with mechanical scanning. The architecture of such systems, as shown below, is well-known and formed the basis of ultrasound imaging.

![](http://openhardware.metajnl.com/articles/10.5334/joh.2/joh-1-2-g1.png/?action=download)

This kit consists of several modules mainly built from easily available components - after a short benchmark of [existing ICs](https://kelu124.gitbooks.io/echomods/content/Chapter6/bench.html). Two electronic modules were specifically designed to provide the basic development kit. 

* the Transducer Pulser Module (TPM): designed to provide a precise high-voltage pulse, necessary to excite the sensor, while remaining robust enough to be controlled by an Arduino;
* the Analog Processing Module (APM): designed to correctly process the raw ultrasound electric signal, while easily exposing all intermediary signals, and exposing a digital output to the user.

A modular approach was chosen to ensure that each key component inside the ultrasound image processing can easily be replaced and compared with another module. Each electronic module takes the place of a function in the signal processing chain or allows tapping into the different signals circulating between the blocks. 

## Assembly guide 

### Required materials

* A [pulser board](/tobo/)
* An [analog front end](/goblin/)
* the [motherboard, v2](/doj/)
* an [ADC cape](https://github.com/kelu124/bomanz/)
* and some extras such as headers, jumpers, and a smallish OLED screen

For the transducer, one can use either a [ATL mechanical probe](/retroATL3/) for example, or a [piezo + servo setup](/cletus). 

## Example of a setup with a servo

![](/elmo/data/arduino/setup.png)

This is a picture from a [first test](/elmo/data/arduino/20170611-arduino.md) with all custom made modules, including raspberry ADC.







