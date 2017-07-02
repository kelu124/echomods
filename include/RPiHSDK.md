# Building a Raspberry Pi based ultrasound imaging development platform

![](/elmo/data/arduinoffset/LineImageEnveloppe.jpg)

@kelu include(/include/AddUSSDK.md)

@kelu include(/include/sets/PiDAQ.cost.md)

## Experiments


### Building the modules and choosing the DAQ

To save on costs and limit complexity, and to ensure the robustness of the designs, the two designed modules leverage existing ICs, based on a review of the [components used in the litterature](/include/AddBench.md):

* The Transducer Pulser Module (TPM) requires both a high-voltage source, and a pulser control. These functions used the Recom Power R05-100B DC/DC Regulated Converter with single-output, to generate a stable high-voltage, which level is determined by a potentiometer, and a Supertex HV7360, High Speed Two or Three Level Ultrasound Pulser, to precisely control the pulse level and duration.
* The mono-channel Analog Processing Module (APM) uses a single channel ultrasound Time Gain Compensation (TGC) integrated circuit, the Analog Devices AD8331, Ultralow Noise VGA with Preamplifier, which gain can be controlled by an external 0 to 1V track. The amplified signal is fed into a RF envelope detector, the Analog Devices ADL5511, RF envelope and TruPwr rms detector. The envelope is the unbiased with an Analog Devices AD8691 Series Precision Amplifier, and optimized for the last item, the Analog Devices AD7274, a 12-bit, 3 Msps Analog to Digital Converters.

Previous experiments have been done, to get images using different digital acquisition systems, such as a bitscope, a STM32, or a high-speed ADC for beaglebone. The Raspberry Pi was retained in the end for its ease of use, its price, and community working on it - increasing the potential reach of the project. 

### Example of the experiment setup

It can be noted that the ADC used in the experiments below is running at half its acquisition speed, due to a blunder - soldering two pins of the second ADC together. However, the 9-bit, 11Msps ADC works relatively well.

![](/elmo/data/arduino/setup.png)

This is a picture from a [first test](/elmo/data/arduino/20170611-arduino.md) with all custom made modules, including raspberry ADC.

## Results / images

I'm getting similar images using the analog enveloppe detection, compared to the digital enveloppe detection, as described below, again on the wire phantom:

![](/elmo/data/arduinoffset/LineImageEnveloppe.jpg) 

And with the analog enveloppe detection:

![](/elmo/data/arduino/EnveloppeLineEnveloppe.jpg) 

This is to be compared to the signal I got from the STM32 integrated ADC

![](/croaker/data/20161217/20161217-222737-commented.png)

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
