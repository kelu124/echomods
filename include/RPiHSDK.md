# Building a Raspberry Pi based ultrasound imaging development platform

![](/elmo/data/arduinoffset/LineImageEnveloppe.jpg)

@kelu include(/include/AddUSSDK.md)

@kelu include(/include/sets/PiDAQ.cost.md)

## Experiments


### Benchmark of acquisition

The first acquisition, used as a reference, is through the ADCs of a STM32F205 (feather WICED) - reaching a whooping 1.7Msps (didn't master the interleaved mode..). Even at these speeds, one can see some features of an ultrasound image, on a wire-phantom. However, resolution isn't that great, let's see if that can be improved?

![](/croaker/data/20161217/20161217-222737-commented.png)

### Example of the experiment setup

It can be noted that the ADC used in the experiments below is running at half its acquisition speed, due to a blunder - soldering two pins of the second ADC together. However, the 9-bit, 11Msps ADC works relatively well.

![](/elmo/data/arduino/setup.png)

This is a picture from a [first test](/elmo/data/arduino/20170611-arduino.md) with all custom made modules, including raspberry ADC.

### Results / images

I'm getting similar images using the analog enveloppe detection, compared to the digital enveloppe detection, as described below, again on the wire phantom:

![](/elmo/data/arduinoffset/LineImageEnveloppe.jpg) 

And with the analog enveloppe detection:

![](/elmo/data/arduino/EnveloppeLineEnveloppe.jpg) 

### Next steps: plugging the Pi to an existing probe

A beaglebone black had been used with its high-speed DAQ to be connected to an existing mechanical probe. The next step will be to interface the Pi to this probe, to see if one can get the same quality of image, and produce a ultrasound loop.

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/20160814/sonde3V_1.gif) 

## What's next?

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


### Who's working on this?

A summary of the contributor is detailed below:

![](/include/community/map.jpg)
