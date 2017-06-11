# Module: RetroATL3 [](@description Main doc source for hacking ATL probes)

![](/retroATL3/viewme.png)

## Name

[`MDL-probe_retroATL3`]()

## Title

Retrohacking the ATL Access 3 probe

## Description

* Retroengineering of ATL Access 3
* version: V0.1
* date: 15/07/2016
* cost:75$
* sourcing:Recycling a probe from [ebay](http://www.ebay.fr/sch/i.html?_odkw=%22atl+access%22+probe&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR0.TRC0.H0.X%22atl+access%22+.TRS0&_nkw=%22atl+access%22+&_sacat=0)
* technology: Hacking the ATL Access 3
* language: n/a
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-F_12V`
* `ITF-N_cc_motor_pwm`
* `ITF-mET_Transducer`
* `Motor`
* `Tri-Piezo Head`

### Outputs

* `Motor`
* `ITF-mET_Transducer`
* `Tri-Piezo Head`

## Key Components

* `ATL3`

## Information

### What is it supposed to do?


The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former ATL3.


### How does it work: block diagram

![Block schema](/retroATL3/source/blocks.png)

* `ITF-mET_Transducer`->`ATL3`->`Tri-Piezo Head`->`ITF-mET_Transducer`
* `ITF-N_cc_motor_pwm`->`ATL3`->`Motor`


## About the module

### Pros

* Simple to use
* 3 piezos, can be of different frequencies as for the ATL10PV

### Cons

* We have removed the position system : we don't have the encoding system
* Tough to find a old ATL Access 3  probe

## Constraint and limits


* For using the ATL Access 3, the 3.3V can be used directly from the [power supply](/mogaba/) -- see [this page](https://kelu124.gitbooks.io/echomods/content/Chapter2/basicdevkit.html).




### Discussions

#### Existing documentation

* We have found an interesting doc: the ATL manual for the ultrasound machine - and specs for the whole set of transducers -- [found here](/include/ultramark/UltraMark_4-Manual.pdf)

#### Details of the probe

![](/retroATL3/images/DSC_0723.JPG)

#### Replacing the oil


* Oil to be found to replace lost one =) Feeback: linseed oil seems good ! 

* Refilling? see below:

![](/retroATL3/images/DSC_0725.JPG)

#### Where to source?

Mostly ebay:
* 60$ for 1 probe - - http://www.ebay.com/itm/ATL-Access-C-3-0-MHZ-12-7mm-dia-Ultrasound-Transducer-P-N-101-25909-72-3862-/111898969844?hash=item1a0db2c6f4:m:mY5GvKHR7qPhPuufxAHnjyA
* 290$ for 2 probes - 2x ATL Access A  (3MHz) - http://www.ebay.com/itm/ATL-Access-A-Ultrasound-Probe-LOT-2-/131588905820?hash=item1ea34f5b5c:g:COUAAOSwyQtV3Xkg
* 5MHz @ http://www.ebay.com/itm/ATL-Access-A-5-0MHz-12-7mm-Dia-6cm-FP-Ultrasound-Probe-3359-/111904941527?hash=item1a0e0de5d7:m:m35HcHQafc7p8BdFvI01GZg (104$)

#### How to connect the motor?

I have not used any feedback action, just tried to provide a constant voltage.

![](/retroATL3/images/motor_pins.jpg)

Using 160mA@4V

#### Good images achieved! [RESOLVED]

[Please refer to this log to read more about how we got this image](/include/20160814/2016-08-14-HackingAUltrasoundProbe.md). Here's an example of the image we got:

![](/include/20160814/sonde3V_1-4.csv-SC.png)

### RealTime issues [RESOLVED]

The motor spins too fast... damned. As seen in "rotating probe image", we can't really say when the probe is rotating or not.  So we'll need a way to check the speed of the motor.

Having timestamped the bitscope acquisitions, there is a 20 +- 0.74 ms between each line.. a tad slow.

#### Real time achieved

Getting realtime information (with no stupid data transfer delays) gives continuous images.

![](/include/20160814/sonde3V_1.png)

#### Reconstructing one loop

With which one can reconstruct a movie:

![](/include/20160814/sonde3V_1.gif)





#### [ATL PV10](/retired/retro10PV/): a more difficult probe to test

* __BEWARE! Only for [ATL PV10](/retired/retro10PV/)__ Motor is a 12V... doesn't move below 10V ... using 300mA@10V -- we could use a [5V to 12V DC/DC boost similar to this one](https://www.pololu.com/product/2117/specs). Could feed onto the 5V entry and leave on the 12V output. Can be found on Gotronics and such. Or the 12V could be delivered to the board itself.


* Tested with murgen : not really pratical to use, maybe to be replaced with a simple 3MHz probe (which we have done with this [retro probe](/retroATL3/). [Read the full test on murgen's repo](https://github.com/kelu124/murgen-dev-kit/blob/master/worklog/Session_9_ATL.md).

* __It seems that the noise previously seen with the bitscope was due to the computer! Not to the bitscope.__


##### Getting an echo

An echo appears with [Murgen](https://github.com/kelu124/murgen-dev-kit), gain at 0.6V

![](/retroATL3/images/TEK0005.JPG)

##### Getting an image while the probe is rotating

![](/retroATL3/software/data/20160721-100523.png)

We don't really see much.. and it appears there is a slight delay 

_This data comes from the [Murgen project](http://github.com/kelu124/murgen-dev-kit/worklog/), Worklog 11_

##### Trying to sort out the details

We see that the image is there, but we don't know when/where the image was taken. See the [reference page for this old probe](/retired/retro10PV/).

![](/retroATL3/software/data/20160720-083810.png)

_This data comes from the [Murgen project](http://github.com/kelu124/murgen-dev-kit/worklog/), Worklog 10_

##### Tests  [RESOLVED]

Those were done with a bitscope at 5Msps.. with 'non-null' delays between each line.

### What ICs are inside the head?

And how are the signals prepared? See [this work](/retroATL3/2017-05-20_APeakInside.md) for pictures of the ICs inside, and for the type of signals inside the head of the probe. 

### Want to know more about electrical impedance?

Some resources:

* http://www.biosono.com/PrmtLgd/PrmtLgd.php?id=TrnsRlc
* http://alejandria.ccm.itesm.mx/biblioteca/digital/liele/pcmc.pdf

* Impedance matching? See https://www.ncbi.nlm.nih.gov/pubmed/23443705

### TODO

* Determine the impedance of the transducer seen by [tobo](/tobo/) (@ulb ?)
* Do a logic control of the probe
* Do some impedance matching (@ulb ? @will ?)
* Finding more precise pins mapping 

### DONE

* _BONUS!_ Get RealTime acquisition
* Finding the pins mapping
* Acquire and build ultrasound pictures =)
* Motor in action
* Refill Oil
* Test echoes
* [Make and insert a video: there](https://hackaday.io/project/9281-murgen-open-source-ultrasound-imaging/log/42113-testing-murgen-with-a-market-probe)

### People

* @eiffel for playing with hardware together 

## License

### RetroATL3 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (amongst which we find the [RetroATL3](/retroATL3/) module) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018

