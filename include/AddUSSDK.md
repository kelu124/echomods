# Ultrasound SDK

## Introduction

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







