# Raspberry Pi based ultrasound imaging

@kelu include(/include/AddUSSDK.md)

@kelu include(/include/sets/PiDAQ.cost.md)


## Experiments

### Example of a setup with a servo

![](/elmo/data/arduino/setup.png)

This is a picture from a [first test](/elmo/data/arduino/20170611-arduino.md) with all custom made modules, including raspberry ADC.

### Setup

![](Images)

## Different DAQs

STM32 - PRUDAQ - now myDAQ

![](Comparatif Bitscope / PRUDAQ / STM32 / ADC)

## Results / images

I'm getting similar images using the analog enveloppe detection, compared to the digital enveloppe detection, as described below, again on the wire phantom:

![](/elmo/data/arduinoffset/LineImageEnveloppe.jpg) 


![](/elmo/data/arduino/EnveloppeLineEnveloppe.jpg) 

This is to be compared to the signal I got from the STM32 integrated ADC

![](/croaker/data/20161217/20161217-222737-commented.png)

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
* [ ] https://www.raspberrypi.org/forums/viewtopic.php?f=41&t=50230
* [ ] https://www.raspberrypi.org/forums/viewtopic.php?f=31&t=39475
* [ ] https://raspberrypi.stackexchange.com/questions/4129/is-pi-powerful-enough-for-an-oscilloscope-project


* [ ] https://raspberrypi.stackexchange.com/questions/53139/parallel-data-adc-with-gpio
* [ ] https://www.raspberrypi.org/forums/viewtopic.php?f=37&t=96679
* [ ] http://projects-raspberry.com/projects/medical-health-based-projects/
* [ ] http://innovations.bmj.com/content/early/2016/03/14/bmjinnov-2015-000080

* https://circuitdigest.com/microcontroller-projects/raspberry-pi-adc-tutorial
