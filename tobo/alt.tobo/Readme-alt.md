## Alternative to Tobo

### Testing

* First experiment [jupyter notebook](/tobo/alt.tobo/test/20170930-AltPulser.ipynb) and first [datasets](/tobo/alt.tobo/test/)
* [Driver for raspberry pi](/tobo/alt.tobo/test/alt.bilevel.c)
* More tests with [fixed depth experiment](/tobo/alt.tobo/20171001a/20171001-new.ipynb) (for pulse quality tests).


### Images

#### Alone

![](/tobo/alt.tobo/test/images/20170930_175000.jpg)

#### Testing with a fixed depth of water

![](/tobo/alt.tobo/20171001a/20171001_135041.jpg)

#### Tests with 3 levels of HV (25, 50 and 75V) - unipolar
![](/tobo/alt.tobo/test/pulser.jpg)


#### Details of pulses at 50V

![](/tobo/alt.tobo/20171001a/Pulses_average_Tube.jpg)

### Brief

#### Specs

* Needed to get 200ns wide square pulses, both in the positive and negative.
* Control of pulses must be through 3.3 or 5V tolerant logic
* Pulses height must be selectable (say with a jumper?) for ~20V, 40V, 80V (for positive pulses) and -20, -40V, and -80V for negative.
* Only power supply available is 5V

#### Components

* See this [application note](http://ww1.microchip.com/downloads/en/AppNotes/AN-H53.pdf) - recommend MD1213 and TC6320 
* Possible (but not used in the end) high voltage source: https://datasheets.maximintegrated.com/en/ds/MAX5025-MAX5028.pdf (3 -> 30V) to be used with a [555 DC-DC convertor](http://www.eleccircuit.com/the-many-dc-to-dc-converters-using-ic-555/)
* Signal back from the diod is clipped by [MD0100](http://ww1.microchip.com/downloads/en/DeviceDoc/MD0100.pdf) + back to back diods.  

#### Power use

To be powered at 5V only.

#### Components

* HV: NMT0572SC
* Pulser : MD1213 and TC6320 -> see [Fig.6 here, bipolar 3 level pulser](http://ww1.microchip.com/downloads/en/AppNotes/AN-H53.pdf). [TC6320, undamped](http://ww1.microchip.com/downloads/en/DeviceDoc/tc6320.pdf), detailed here. 
* Protection: MD0100+diods -- should be enough, see [bottom of page 1, or Fig 9](http://ww1.microchip.com/downloads/en/DeviceDoc/MD0100.pdf)
