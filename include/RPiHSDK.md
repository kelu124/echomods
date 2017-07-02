# Building a Raspberry Pi based ultrasound imaging development platform

![](/elmo/data/arduinoffset/LineImageEnveloppe.jpg)

@kelu include(/include/AddUSSDK.md)

@kelu include(/include/sets/PiDAQ.cost.md)

@kelu include(/include/AddPrinciples.md)

## Experiments


### Benchmark of acquisition

The first acquisition, used as a reference, is through the ADCs of a STM32F205 ([feather WICED](/croaker/)) - reaching a whooping 1.7Msps (didn't master the interleaved mode..). Even at these speeds, one can see some features of an ultrasound image, on a wire-phantom. However, resolution isn't that great, let's see if that can be improved?

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

### Lessons on the way

* __Start with common elements and modules__: I had been _quite_ presumptuous to try and create something from scratch. Do your homeworks, review
* __Modular design__ is the way to go. Discussing in various communities, there are only so many designs that didn't fail in the first time. Make modules out of your designs, so that if one part fails, you aren't left with nothing but a new invoice from the PCBA.
* __Share__: the world of open-source is awesome. There are plenty of good ideas around, and people don't have the time to implement them. There are other persons who like to implement stuff. Merge the two. Enjoy!
* __Do what you like__: don't do what you don't like. Find support - even if it's PCBA - for your designs. Sometimes, it's good to rely on pros to do your designs cleanly. Or maybe someone will be happy to review the designs. It does count.
* __Document__: an easy thing to say.. but it has to be repeated. Don't hesitate to use/make tools to support this quest, it makes your life soooo much easy. All of this gitbook is generated on the fly - my rule of thumb is: _Don't write anything twice_.

## What's next?

On a hardware side:

* The pulser-module design uses only two inputs and one high voltage source. However, the chip enables more complex uses as a pulser, which can be further explored.
* A multiplexer module can be used, to interface this single channel kit with an array probe. Doing this would permit to do synthetic aperture imaging, and to characterize as well each element in the array.
* A whole field left unexplored so far is that of the transducer. As the key sensor in the kit, it would be interesting to explore relevant technologies to develop an open and accessible transducer.
* Quite interestingly, it would be interesting to merge all modules once again on one RaspberryPi3-compatible hat

On a software side:

* The Raspberry Pi can be used a bit more. From a software point of view, the modules could be wirelessly controlled, leveraging the existing wireless communication channel, so that researchers can use a single unit for a laboratory, controlled from personal computers.
* The images will need to be stored in a DICOM-compatible format. 

On the OSH contribution part to the community:

* A campaign should start soon to make the ADC accessible. It seems there's a demand for high speed DAQ there. Just need to confirm the PCBA.


### Who's working on this?

A summary of the contributor is detailed below:

![](/include/community/map.jpg)

# And you?

Want to learn more? You can join the [slack channel](https://join.slack.com/usdevkit/shared_invite/MTkxODU5MjU0NjI1LTE0OTY1ODgxMDEtMmYyZTliZDBlZA) if you want to discuss, but there are plenty of other sources:

* Obviously, you can __read the [online manual/book](https://www.gitbook.com/book/kelu124/echomods/details)__ for a easily readable and searchable archive of the whole work;
* You can also __fork the [project repo](https://github.com/kelu124/echomods/)__, for the source files, raw data and raw experiment logs;
* or explore the [hackaday page](https://hackaday.io/project/9281-murgen-open-source-ultrasound-imaging), where I tried to blog day-to-day experiments in a casual format;
* __Want a scientific article?__ Have a look at the [article summarizing the experiment on the Journal of Open Hardware](http://openhardware.metajnl.com/articles/10.5334/joh.2/) - [DOI:10.5334/joh.2]( http://doi.org/10.5334/joh.2);
* __Want to buy the modules and make your own setup?__ Visit the Tindie store for the [analog processing unit](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/) and the [pulser](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/) or [the motherboard](https://www.tindie.com/products/kelu124/ultrasound-modules-motherboard/).
