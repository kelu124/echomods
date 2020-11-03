[![ko-fi](https://www.ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/G2G81MT0G)

# What is this project? [](@description Pitch/Intro of the project)

This project has a specific target of providing a __low-cost, open source technological kit to allow scientists, academics, hackers, makers or OSHW fans to hack their way to ultrasound imaging__ - below 500$ - at home, with no specific equipment required. For complementary sources of information, you can visit:

* the [github repo](https://github.com/kelu124/echomods/), for the source files, raw data and raw experiment logs;
* the [online manual/book](https://www.gitbook.com/book/kelu124/echomods/details) for a easily readable and searchable archive of the whole work;
  * with [list of probes](/include/probes/)
  * and [list of experiments](/include/experiments/)
* the [hackaday page](https://hackaday.io/project/9281-murgen-open-source-ultrasound-imaging), where I tried to blog day-to-day experiments in a casual format;
* an [article summarizing the experiment on the Journal of Open Hardware](http://openhardware.metajnl.com/articles/10.5334/joh.2/) - [DOI:10.5334/joh.2]( http://doi.org/10.5334/joh.2);
* the [slack channel if you want to discuss](https://join.slack.com/t/usdevkit/shared_invite/zt-2g501obl-z53YHyGOOMZjeCXuXzjZow);
* the Tindie store for the [analog processing unit](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/) and the [unipolar pulser](https://www.tindie.com/products/kelu124/ultrasound-unipolar-high-voltage-pulser/) or [the motherboard](https://www.tindie.com/products/kelu124/ultrasound-modules-motherboard/).
* And of course, the [ice40 research board](https://www.tindie.com/products/kelu124/un0rick-open-ice40-ultrasound-imaging-dev-board/), on [un0rick.cc](http://un0rick.cc) and its [doc](http://doc.un0rick.cc) or even [its github](https://github.com/kelu124/un0rick). _It's a bit cheaper, and has better specs_. 

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.377054.svg)](https://doi.org/10.5281/zenodo.377054)

* __Disclaimer #0__: __This is not a medical ultrasound scanner__! It's a development kit that can be used for pedagogical and academic purposes - possible immediate use as a non-destructive testing (NDT) tool, for example in metallurgical crack analysis. As in all electronics, be [careful](/WordOfCaution.md).
* __Disclaimer #1__: though an engineer, this project is the first of its sort, I never did something related. It's all but a finalized product.
* __Disclaimer #2__: Ultrasound raises questions. In case you build a scanner, use caution and good sense!
* __Disclaimer #3__: This project is not part of echopen.


# Principles of ultrasound imaging

## General principles of ultrasound imaging

### Using echoes to map interfaces

Medical ultrasound is based on the use of high frequency sound to aid in the diagnosis and treatment of patients. Ultrasound frequencies range from 2 MHz to approximately 15 MHz, although even higher frequencies may be used in some situations.

The ultrasound beam originates from mechanical oscillations of numerous crystals in a transducer, which are excited by electrical pulses (piezoelectric effect). The transducer converts one type of energy into another (electrical <--> mechanical/sound). 

![](/include/20161016/concept1.PNG)

The ultrasound waves (pulses of sound) are sent from the transducer, propagate through different tissues, and then return to the transducer as reflected echoes when crossing an interface. The returned echoes are converted back into electrical impulses by the transducer crystals and are further processed - _mostly to extract the enveloppe of the signal, a process that transforms the electrical signal in an image_ -  in order to form the ultrasound image presented on the screen.

Ultrasound waves are reflected at the surfaces between the tissues of different density, the reflection being proportional to the difference in impedance. If the difference in density is increased, the proportion of reflected sound is increased and the proportion of transmitted sound is proportionately decreased.

If the difference in tissue density is very different, then sound is completely reflected, resulting in total acoustic shadowing. Acoustic shadowing is present behind bones, calculi (stones in kidneys, gallbladder, etc.) and air (intestinal gas). Echoes are not produced on the other hand if there is no difference in a tissue or between tissues. Homogenous fluids like blood, bile, urine, contents of simple cysts, ascites and pleural effusion are seen as echo-free structures.

### Creating a 2D image

If the process is repeated with the probe sweeping the area to image, one can build a 2D image. In practice, in the setups we'll be discussing, this sweep is done with a transducer coupled to a servo, or using a probe that has an built-in motor to create the sweep.

![](/include/20161016/concept2.PNG)







# Necessary architecture

### Transducer

A critical component of this system is the ultrasound transducer. A typical ultrasound imaging system uses a wide variety of transducers optimized for specific diagnostic applications, but in our case, we'll limit the costs.
 
### High-Voltage Transmitters ([see the module](/retired/tobo/))

A digital transmit beamformer typically generates the necessary digital transmit signals with the proper timing and phase to produce a focused transmit signal. High-voltage pulsers quickly switch the transducer element to the appropriate programmable high-voltage supplies to generate the transmit waveform. To generate a simple bipolar transmit waveform, a transmit pulser alternately connects the element to a positive and negative transmit supply voltage controlled by the digital beamformer. More complex realizations allow connections to multiple supplies and ground in order to generate more complex multilevel waveforms with better characteristics.


### TGC + LNA = Variable-Gain Amplifier (VGA) ([see the module](/goblin/))

The LNA in the receiver must have excellent noise performance and sufficient gain. In a properly designed receiver the LNA will generally determine the noise performance of the full receiver. 

The VGA, sometimes called a time gain control (TGC) amplifier, provides the receiver with sufficient dynamic range over the full receive cycle. Ultrasound signals propagate in the body at approximately 1540 meters per second and attenuate at a rate of about 1.4dB/cm-MHz roundtrip. Immediately after an acoustic transmit pulse, the received "echo" signal at the LNA's input can be as large as 0.5VP-P. This signal quickly decays to the thermal noise floor of the transducer element. The dynamic range required to receive this signal is approximately 100dB to 110dB, and is well beyond the range of a realistic ADC. As a result, a VGA is used to map this signal into the ADC. A VGA with approximately 30dB to 40dB of gain is necessary to map the received signal into a typical 12-bit ADC used in this application. The gain is ramped as a function of time (i.e., "time gain control") to accomplish this dynamic range mapping.


### Anti-Alias Filter (AAF) and ADC ([see the module](/retired/toadkiller/))

The AAF in the receive chain keeps high-frequency noise and extraneous signals that are beyond the normal maximum imaging frequencies from being aliased back to baseband by the ADC. Many times an adjustable AAF is provided in the design. To avoid aliasing and to preserve the time-domain response of the signal, the filter itself needs to attenuate signals beyond the first Nyquist zone. For this reason Butterworth or higher-order Bessel filters are used.

The ADC used in this application is typically a 12-bit device running from 40Msps to 60Msps. This converter provides the necessary instantaneous dynamic range at acceptable cost and power levels. In a properly designed receiver, this ADC should limit the instantaneous SNR of the receiver. As previously mentioned, however, limitations in the poor-performing VGAs many times limit receiver SNR performance






## Ultrasound hardware structure

[](@description Short description of the organization of modules)

To produce an image, the modules have to create a [high voltage pulse](/retired/tobo/), which excites a [transducer](/retroATL3/). Echoes coming from the body are amplified using a [TGC + LNA](/goblin/), which cleans the analog signal, which itself [gets digitalized](/retired/toadkiller/). 

The diagram is represented below:

![](/include/images/blockdiagram.gif)




# Un0rick, the ice40 board

![](https://raw.githubusercontent.com/kelu124/un0rick/master/images/un0desc.png)

## Why a FPGA board ?


Non destructive testing and imaging ultrasound modalities have been around since the '50s in . More and more ultrasound-based initiative are emerging, mostly focusing on image processing - while hardware has been left behind. Several teams have produced succesful designs for the different possible uses, mostly efforts from research laboratories. Most have been used on commercial US scanners, traditionaly used as experiment platforms, but they are not cheap, and yield very little in terms of data access and control. Others have been developped in labs, but, sadly, very few have been open-sourced. Let's tackle this!

It has also been shown that simple (be it low-power, low-cost and small) can be achieved - and this, even for relatively complex systems, based on 16 to 64  parallel   channels   front-end  processing and software back-end processing (embedded PC or DSP). This makes it a bit more complex for the layman, hobbyist, or non-specialist researcher to use, not to mention the very little information that is accessible.

## Hardware specifications and features


1. __FPGA__: Lattice iCE40HX4K - TQFP 144 Package
2. __Memory__:
  * 8 Mbit SRAM, 10ns, 512 k x 16, equivalent:
      * 65 full lines of 120us at 64Msps
      * 840 lines of 120us at 10Msps, 8 bits
  * 8 Mb SPI Flash for FPGA configuration 
3. __Ultrasound processing__:
  * __VGA__: AD8331 controled by DAC
  * __Pulser__: MD1210 + TC6320
  * __ADC__: 65Msps ADC10065
    * 10 bits of data / sample
    * 2 bits of line counters
    * 4 bits of IOs (counters, ...) 
4. __Parameters__: Settings programable via USB or Raspberry Pi 
  * Type of acquisition (one line / set of lines)
  * Number of lines
  * Length of lines acquisitions
  * Delay between acquisitions
  * Pulse width 
  * Delay between pulse and beginning of acquisitions
  * 200us time-gain-compensation programmable (8 bits, from 0 to Max), every 5us
5. __Extensibility__:
  * 2 x Pmod connectors
  * SMA plug for transducers
  * RPi GPIO
6. __User Interfaces__:
  * 2 x PMOD for IOs
  * 3 x push button (with software noise debouncing)
  * Jumpers for high voltage selection
7. __Input Voltage__: 
  * 5 V from RPi or USB
  * Uses 350mA-450mA at 5V
8. __Fully Open Source__:
  * Hardware: _github repository_
  * Software: _github repository_
  * Toolchain: _Project IceStorm_
  * Documentation: _gitbook_
9. __Operating Voltage__: 
  * FPGA and logics at at 3.3 V
  * High voltage at 25V, 50V, 75V
10. __Dimensions__: @todo!
11. __Weight__: @todo! 

## Comparative

| Tool           	| Murgen 	| echOmods        	| unoric               	|
|----------------	|--------	|-----------------	|----------------------	|
| Open Source    	| Yes    	| Yes             	| Yes                  	|
| ADC            	| 20Msps 	| 1Msps to 24Msps 	| 65Msps up to 100Msps 	|
| Onboard memory 	| 300 Mb 	| 10 Mb           	| 20Mb                 	|
| Price of a set	| 400$		| 450$			| 400$			|
| Modular		| Np		| Yes			| No			| 


# Modules

## What are the arduino-like ultrasound module ?

__Creating modules to facilitate ultrasound hacking__ : the principles of the echOmods is to enable a full chain of ultrasound image processing and hardware control.

We have chosen to use a module approach to make sure that each key component inside ultrasound image processing can easily be replaced and compared with another module, while providing logical _logic blocks_ and corresponding interfaces for these modules to communicate. There's a module for [high-voltage pulsing](/retired/tobo/), one for the [transducer](/retroATL3/), one for the [analog processing](/goblin/), one for [data acquisiton](/retired/toadkiller/), ... and many more!

## What images does it give ?

![](/elmo/data/arduinoffset/LineImageEnveloppe.jpg)

## What does it look like?

The modules sit on a breadboard, and communicate through the tracks laying below. The configuration represented below show the Basic dev kit.

![](/doj/images/doj_v2_notes.jpg)

and used in a wider context:

![](/elmo/data/arduino/setup.png)


# A recap of the modules 


| ThumbnailImage | Name | In | Out |
|------|-------|----|------|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retroATL3/viewme.png' align='center' width='150'>|**[retroATL3](/retroATL3/Readme.md)**: The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former ATL3.|<ul><li>ITF-A_gnd</li><li>ITF-F_12V</li><li>ITF-N_cc_motor_pwm</li><li>ITF-mET_Transducer</li><li>Motor</li><li>Tri-Piezo Head</li></ul>|<ul><li>Motor</li><li>ITF-mET_Transducer</li><li>Tri-Piezo Head</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/elmo/viewme.png' align='center' width='150'>|**[elmo](/elmo/Readme.md)**: The aim of this module is to achieve 20Msps, at 9bits or more. |<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-19_3.3V</li><li>ITF-12_RPIn</li></ul>|<ul><li>Signal Digitalized</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/goblin/viewme.png' align='center' width='150'>|**[goblin](/goblin/Readme.md)**: The aim of this echOmod is to get the signal coming back from a transducer, and to deliver the signal, analogically processed, with all steps accessible to hackers. |<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-7_GAIN</li><li>ITF-4_RawSig</li><li>ITF-3_ENV</li><li>ITF-18_Raw</li><li>ITF-mET_SMA</li></ul>|<ul><li>ITF-4_RawSig</li><li>ITF-3_ENV_signal_envelope</li><li>ITF-mEG_SPI</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/lite.tbo/viewme.png' align='center' width='150'>|**[lite.tbo](/lite.tbo/Readme.md)**: The aim of this echOmod is to get the HV Pulse done.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-9_Pon</li><li>ITF-10_Poff</li><li>ITF-19_3.3V</li><li>ITF-mET_Transducer</li></ul>|<ul><li>ITF-18_Raw</li><li>ITF-mET_SMA</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/lit3rick/viewme.png' align='center' width='150'>|**[lit3rick](/lit3rick/Readme.md)**: The aim is to summarize all modules in a all-inclusive board. Fast ADC, good load of memory, good SNR.. the not-so-DIY module, as it comes already assembled with nothing to do. Based on up5k.|||
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/matty/viewme.png' align='center' width='150'>|**[matty](/matty/Readme.md)**: The aim is to summarize all modules in a all-inclusive board. Fast ADC, good load of memory, good SNR.. the not-so-DIY module, as it comes already assembled with nothing to do =)|||
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/doj/viewme.png' align='center' width='150'>|**[doj](/doj/Readme.md)**: Getting a motherboard: that's fitting all the modules in an easy way, with an easy access to all tracks. See this for the Kicad files.|||
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/wirephantom/viewme.png' align='center' width='150'>|**[wirephantom](/wirephantom/Readme.md)**: Just a phantom for calibrated signals|<ul><li>na</li></ul>|<ul><li>na</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/silent/viewme.png' align='center' width='150'>|**[silent](/silent/Readme.md)**: The aim of this echOmod is to simulate a raw signal that would come from the piezo and analog chain.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-17_POff3</li></ul>|<ul><li>ITF-18_Raw</li></ul>|







# List of experiments

# Experiments

 * [20201103a](/include/experiments/auto/20201103a.md)
 * [20201031a](/include/experiments/auto/20201031a.md)
 * [20201028a](/include/experiments/auto/20201028a.md)
 * [20201026a](/include/experiments/auto/20201026a.md)
 * 2020-10-24: [i2s issue](/include/experiments/auto/20201024a.md): Exploring the i2s offsets _(20201024a)_
 * 2020-10-23: [Canada](/include/experiments/auto/20201023a.md): Silvio first lit3rick tests _(20201023a)_
 * 2020-10-22: [Spain](/include/experiments/auto/20201022a.md): Jorge tests on lit3rick _(20201022a)_
 * 2020-10-08: [benchmark lit3 and un0](/include/experiments/auto/20201008a.md): Running acquisitions on the same rig. _(20201008a)_
 * 2020-08-09: [bard vna](/include/experiments/auto/20200809r.md): bard vna tests _(20200809r)_
 * 2020-08-08: [all probes vna](/include/experiments/auto/20200808r.md): getting impedance params of all probes _(20200808r)_
 * 2020-06-08: [brd35 test](/include/experiments/auto/20200608a.md): testing an electromagnetic movement probe _(20200608a)_
 * 2020-05-08: [testing bard probe](/include/experiments/auto/20200508a.md): Nothing much really _(20200508a)_
 * 2020-04-21: [a-law](/include/experiments/auto/20200421b.md): testing a-law compressions compared to log and sqrt _(20200421b)_
 * 2020-04-21: [comparing boards](/include/experiments/auto/20200421a.md): preliminary check between lit3rick and un0rick _(20200421a)_
 * 2020-04-18: [echo-tomo](/include/experiments/auto/20200418a.md): Trying to get a tomo echo image _(20200418a)_
 * 2020-04-16: [testing new piezos](/include/experiments/auto/20200416a.md): and calibrating new piezos against bubbles _(20200416a)_
 * 2020-03-25: [NDT pulse widths](/include/experiments/auto/20200325a.md): Trying and getting different pulse on a steel block. _(20200325a)_
 * 2020-03-21: [pulse widths](/include/experiments/auto/20200321a.md): Trying and getting different pulse on the test bench. _(20200321a)_
 * 2019-10-27: [lit3rick De.bin](/include/experiments/auto/20191027b.md): New success with lit3rick, with dynamic DAC _(20191027b)_
 * 2019-10-27: [meh - noisy](/include/experiments/auto/20191027a.md): still some tests, Dd.bin for lit3rick _(20191027a)_
 * 2019-10-26: [meh C2w](/include/experiments/auto/20191026a.md): testing new bins for lit3rick _(20191026a)_
 * 2019-10-24: [getting better at dyn dac](/include/experiments/auto/20191024a.md): tests _(20191024a)_
 * 2019-10-23: [lit3 success](/include/experiments/auto/20191023a.md): Some better acquisitions - it works ! _(20191023a)_
 * 2019-10-22: [lit3 weird](/include/experiments/auto/20191022b.md): Strange signals ahead _(20191022b)_
 * 2019-10-22: [weird acqs again](/include/experiments/auto/20191022a.md): investigating _(20191022a)_
 * 2019-10-18: [first un0 acqs from Tri](/include/experiments/auto/20191018a.md): his [setup seems to work](https _(20191018a)_
 * 2019-10-16: [weird acqs](/include/experiments/auto/20191016a.md): what is wrong with me ? _(20191016a)_
 * 2019-10-06: [lit3 questions](/include/experiments/auto/20191006a.md): what is happening ? _(20191006a)_
 * 2019-08-04: [tuto video for Un0rick](/include/experiments/auto/20190804a.md): [more here on youtube](https _(20190804a)_
 * 2019-07-13: [new un0 batch](/include/experiments/auto/20190713b.md): quality tests _(20190713b)_
 * 2019-07-13: [RPI3](/include/experiments/auto/20190713a.md): yes, I had to test _(20190713a)_
 * 2019-04-15: [NDT tests](/include/experiments/auto/20190415a.md): testing what the NDT probes does _(20190415a)_
 * 2019-04-04: [NDT tests double peak](/include/experiments/auto/20190404a.md): why are there two frequencies ? _(20190404a)_
 * 2019-03-29: [NDT dual transducer](/include/experiments/auto/20190329a.md): understanding the transducer _(20190329a)_
 * 2019-03-24: [lit3rick](/include/experiments/auto/20190324a.md): testing at first the pulser _(20190324a)_
 * 2019-02-26: [flashing UP5K sran](/include/experiments/auto/20190226a.md): using a m5stack to flash the sram of the up5K, temporarily, through a web interface _(20190226a)_
 * 2019-02-23: [Testing pHATrick flash](/include/experiments/auto/20190223a.md): Testing pHATrick flash _(20190223a)_
 * 2019-01-13: [m5stack bis](/include/experiments/auto/20190113a.md): retesting with details the m5stack experiment _(20190113a)_
 * 2019-01-11: [faster checks](/include/experiments/auto/20190111a.md): multi, single, process commands for the lib _(20190111a)_
 * 2019-01-04: [lib improvements part II](/include/experiments/auto/20190104a.md): streamlining processing images _(20190104a)_
 * 2019-01-03: [lib improvements](/include/experiments/auto/20190103a.md): streamlining processing images _(20190103a)_
 * 2018-11-26: [HV tests part II](/include/experiments/auto/20181126b.md): checking what's the fact with HV parts _(20181126b)_
 * 2018-11-26: [HV tests](/include/experiments/auto/20181126a.md): checking what's the fact with HV parts _(20181126a)_
 * 2018-11-04: [matty and 724A](/include/experiments/auto/20181104c.md): testing a new probe with matty v1.01 _(20181104c)_
 * 2018-11-04: [matty and Apogee10 recabled](/include/experiments/auto/20181104b.md): testing a new probe with matty v1.01 _(20181104b)_
 * 2018-11-04: [matty and hp2121](/include/experiments/auto/20181104a.md): playing with hp2121 and matty _(20181104a)_
 * 2018-10-13: [opening an hp2121](/include/experiments/auto/20181013a.md): try and open an hp2121, while waiting for a new matty _(20181013a)_
 * 2018-09-01: [wirephantom and kretzaw145ba](/include/experiments/auto/20180901a.md): wirephantom and kretzaw145ba _(20180901a)_
 * 2018-08-31: [wirephantom and retroATL3](/include/experiments/auto/20180831c.md): wirephantom and retroATL3 _(20180831c)_
 * 2018-08-26: [16bits n-cycles](/include/experiments/auto/20180826a.md): Testing if the 16bits n cycles works _(20180826a)_
 * 2018-08-25: [2D images building](/include/experiments/auto/20180825a.md): Testing new functions to unpack images (with N lines) _(20180825a)_
 * 2018-08-14: [Reaching 128msps](/include/experiments/auto/20180814a.md): Trying to experiment getting 128Msps _(20180814a)_
 * 2018-08-13: [pyUn0 lib glitches](/include/experiments/auto/20180813a.md): Experiment to capture glitches. Now captured (bugs with timing), pending is increasing NCycles above a 8 bit count. _(20180813a)_
 * 2018-08-12: [KretzImage](/include/experiments/auto/20180812a.md): Getting an image with a kretz AW14/5B/A ultrasound probe _(20180812a)_
 * 2018-08-09: [Ausonics 7.5MHz probe](/include/experiments/auto/20180809b.md): Getting in a Ausonics 7.5MHz probe _(20180809b)_
 * 2018-08-07: [InterspecApogee](/include/experiments/auto/20180807b.md): Opening an InterspecApogee probe _(20180807b)_
 * 2018-08-07: [ADR Ultrasound probe](/include/experiments/auto/20180807a.md): Photo reportage of opening an ADR Ultrasound probe. _(20180807a)_
 * 2018-07-21: [pyUn0 python lib and TGC](/include/experiments/auto/20180721a.md): Testing class-approach for acquisition and processing. Also tested Gain setup. _(20180721a)_
 * 2018-06-20: [Uwe setup](/include/experiments/auto/20180620a.md): Testing ADC with Uwe setup with elmo and a 250khz source _(20180620a)_
 * 2018-05-16: [Matty file format](/include/experiments/auto/20180516a.md): Testing to format the data for experiments to be easily reproduced _(20180516a)_
 * 2018-05-11: [Enveloppe detection](/include/experiments/auto/20180511a.md): Checking different ways to rebuild enveloppe _(20180511a)_
 * 2018-05-06: [SPI timing on Raspberry](/include/experiments/auto/20180506a.md): Checking SPI bottlenecks on Matty _(20180506a)_
 * 2018-04-30: [JSON and Servo](/include/experiments/auto/20180430a.md): Better file management and servo control using Matty. _(20180430a)_
 * 2018-04-17: [echomods vs MATTY](/include/experiments/auto/20180417a.md): Comparing the performances of the modules vs the FPGA board Matty _(20180417a)_
 * 2018-04-15: [Test of new batch 2/2](/include/experiments/auto/20180415r.md): Testing the lite.tbo, goblin and elmo boards done at the fab - on a doj v2 motherboard. _(20180415r)_
 * 2018-04-15: [Test of new batch 1/2](/include/experiments/auto/20180415a.md): Testing the goblin board with silent, then test of the new lite.tbo pulser with a piezo. _(20180415a)_
 * 2018-04-03: [Tomas first acq](/include/experiments/auto/20180403t.md): Tomas, a user, is getting a first image from a NDT setup with a block of steel. _(20180403t)_
 * 2018-04-03: [Matty TGC test](/include/experiments/auto/20180403b.md): Testing matty 's TGC, including playing with the gain DAC and pulse control. _(20180403b)_
 * 2018-04-03: [Voltage checks](/include/experiments/auto/20180403a.md): Testing matty at different voltages. _(20180403a)_
 * 2018-03-10: [Matty DAQ](/include/experiments/auto/20180310a.md): testing the programmation of matty DAC control for the TGC. _(20180310a)_
 * 2018-02-25: [Matty and RetroATL3](/include/experiments/auto/20180225a.md): Acquisition of a probe image with matty. _(20180225a)_
 * 2018-02-24: [Matty Gain](/include/experiments/auto/20180224b.md): Testing matty's fixed gain settings. _(20180224b)_
 * 2018-02-24: [Matty speed tests](/include/experiments/auto/20180224a.md): Testing matty s acquisition at different speed, 12Msps to 24Msps. _(20180224a)_
 * 2018-02-17: [Alt.tbo and Elmo](/include/experiments/auto/20180217a.md): Testing alt.tbo and elmo new boards for pulser issues (there is not positive and negative pulse, only goes in direction). _(20180217a)_
 * 2018-02-16: [Alt.tbo and Elmo](/include/experiments/auto/20180216a.md): Testing alt.tbo and elmo new boards. _(20180216a)_
 * 2018-01-15: [Matty](/include/experiments/auto/20180115a.md): Receiving the first matty. _(20180115a)_
 * 2018-01-03: [Felix experiment](/include/experiments/auto/20180103a.md): Testing Felix setup with previous Bomanz module. _(20180103a)_
 * 2017-11-24: [Impedance matching](/include/experiments/auto/20171124a.md): Doing some tests for impedance matching. _(20171124a)_
 * 2017-11-12: [Probe](/include/experiments/auto/20171112a.md): Testing new probe with new pulser _(20171112a)_
 * 2017-11-11: [Alt.tbo](/include/experiments/auto/20171111a.md): Testing new pulser again 4/4 _(20171111a)_
 * 2017-10-01: [Alt.tbo](/include/experiments/auto/20171001b.md): Testing new pulser again 3/4 _(20171001b)_
 * 2017-10-01: [Alt.tbo](/include/experiments/auto/20171001a.md): Testing new pulser again 2/4 _(20171001a)_
 * 2017-09-30: [Alt.tbo](/include/experiments/auto/20170930a.md): Testing new pulser again 1/4 _(20170930a)_
 * 2017-07-15: [RetroATL3 acquisition](/include/experiments/auto/20170715a.md): Getting an image from the retroATL3 probe. _(20170715a)_
 * 2017-07-13: [Elmo](/include/experiments/auto/20170713a.md): Testing the new DAQ with two ADCs. _(20170713a)_
 * 2017-06-11: [Croaker](/include/experiments/auto/20170611a.md): Testing the acquisition with the croaker module. _(20170611a)_
 * 2016-12-17: [Croaker](/include/experiments/auto/20161217a.md): Testing the acquisition with the croaker module. _(20161217a)_
 * 2016-08-22: [BBB+Probe](/include/experiments/auto/20160822a.md): Images acquired from a BeagleBone black with a probe _(20160822a)_
 * 2016-08-14: [RPi](/include/experiments/auto/20160814a.md): Testing the acquisition with the BeagleBone DAQ. _(20160814a)_
 * 2016-08-09: [Goblin tests](/include/experiments/auto/20160809a.md): Testing the goblin board with the silent emulator. _(20160809a)_




# List of probes

That's the list of probes been playing with:

* [724A](/include/probes/auto/724A.md)
* [BiViPiezo](/include/probes/auto/BiViPiezo.md)
* [NDTPiezo](/include/probes/auto/NDTPiezo.md)
* [adrus](/include/probes/auto/adrus.md)
* [apogee](/include/probes/auto/apogee.md)
* [apogee10MHz](/include/probes/auto/apogee10MHz.md)
* [apogee5MHz](/include/probes/auto/apogee5MHz.md)
* [atlannular](/include/probes/auto/atlannular.md)
* [atlidrict](/include/probes/auto/atlidrict.md)
* [ausonics75](/include/probes/auto/ausonics75.md)
* [bard](/include/probes/auto/bard.md)
* [brd35](/include/probes/auto/brd35.md)
* [brd75](/include/probes/auto/brd75.md)
* [brd90](/include/probes/auto/brd90.md)
* [diasonics_50](/include/probes/auto/diasonics_50.md)
* [diasonics_75](/include/probes/auto/diasonics_75.md)
* [diasonics_gpm_plus_35](/include/probes/auto/diasonics_gpm_plus_35.md)
* [diasonics_tr](/include/probes/auto/diasonics_tr.md)
* [duc2m](/include/probes/auto/duc2m.md)
* [hp2121](/include/probes/auto/hp2121.md)
* [kretzaw145ba](/include/probes/auto/kretzaw145ba.md)
* [linscan](/include/probes/auto/linscan.md)
* [myapo](/include/probes/auto/myapo.md)
* [retro10PV](/include/probes/auto/retro10PV.md)
* [retro10apogee](/include/probes/auto/retro10apogee.md)
* [retroATL3](/include/probes/auto/retroATL3.md)
* [s3](/include/probes/auto/s3.md)
* [shzmch](/include/probes/auto/shzmch.md)
* [sw45b](/include/probes/auto/sw45b.md)
* [uprobe1](/include/probes/auto/uProbe1.md)




# Todos

## Shopping list

Here's a couple of things we're working on, for which you could help as well.

* Boosting the [6Msps croaker](/retired/croaker/) acquisition (see Wayne?) to the full 6Msps 

#### Un0rick

* Get one V1.0 board
* Get one V1.1 board (with winbond :p)
* Test new HDL code
* Test david 1.1 code
* Buy headers for VGA (??)
* Do logo
* Do sticker
* Do mini matty
* Do QR code to doc
* PayMeACoffee button
* other readme buttons
* improve readme (and delete home page?)

#### Rest

### Todos from Modules
* Test Goblin v2 (in [goblin](/goblin/))
* Review a bipolar design (originally alt.tbo -- but double the components and hence the price) (in [lite.tbo](/lite.tbo/))
* Improve i2s transfers (in [lit3rick](/lit3rick/))
* See the <a href="/matty/nextsteps.md">next steps</a> (in [matty](/matty/))
* Having it work with a <a href="/retroATL3/">retroATL3</a> (in [matty](/matty/))
* None (in [wirephantom](/wirephantom/))


### Todos from worklog
* PMODs US:
* Documentation - update for lit3 once it is ready, with http://2012.oshwa.org/files/2012/07/Wozniak-OHS2012-Final.pdf, http://2011.oshwa.org/files/2011/09/Wozniak-OHS2011.pdf, and https://cdn-blog.adafruit.com/uploads/2011/09/w0z-OHS2011-v1.pdf
* get https://github.com/tobozo/M5Stack-SD-Updater to add bins
* do impedance matching tests [on a new piezo](https://github.com/kelu124/echomods/blob/master/matty/20200416a/Readme.md) and tests impedance matching on the new piezo to see if that improves things =)
* check artists meet makers
* bin for un0rick ftdi control - bogdan?
* integrate some documentation for un0rick and lit3rick as in http://www.trenz-electronic.de/fileadmin/docs/Trenz_Electronic/Modules_and_Module_Carriers/3.05x6.5/TE0876/REV02/Documents/iceZero-pinout-v5.pdf
* move forward on some new hardware like the [ft600](./include/ft_600_notes.md)
* find the i2s issue






# License

## echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (kelu124@gmail.com) 2015-2018

## Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Kelu124 (kelu124@gmail.com) 2015-2018

## Disclaimer

This project is distributed WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A PARTICULAR PURPOSE. 


# Annexes

## Retired modules



# A recap of our retired modules 


| ThumbnailImage | Name | In | Out |
|------|-------|----|------|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/loftus/viewme.png' align='center' width='150'>|**[loftus](/retired/loftus/Readme.md)**: The aim of this module is to recycle a previous head|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-N_cc_motor_pwm</li><li>ITF-S_3_3v</li><li>ITF-mET_Transducer</li><li>ITF-mET_Piezo</li></ul>|<ul><li>ITF-mET_Piezo</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/croaker/viewme.png' align='center' width='150'>|**[croaker](/retired/croaker/Readme.md)**: The aim of this echOmod is to receive the signal and process it, then stream it over wifi. |<ul><li>ITF-3_ENV</li><li>ITF-10_Poff</li><li>ITF-9_Pon</li><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li></ul>|<ul><li>ITF-19_3.3V</li><li>ITF-mED-TFT-Screen</li><li>ITF-mED-OLED-Screen</li><li>ITF-mEC-WiFi-UDP-Stream</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/mogaba/viewme.png' align='center' width='150'>|**[mogaba](/retired/mogaba/Readme.md)**: The aim of this echOmod is to get 3.3V and 5V done.|<ul><li>ITF-mEM_Alimentation</li></ul>|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-19_3.3V</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/alt.tbo/viewme.png' align='center' width='150'>|**[alt.tbo](/retired/alt.tbo/Readme.md)**: The aim of this echOmod is to get the HV Pulse done.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-9_Pon</li><li>ITF-10_Poff</li><li>ITF-19_3.3V</li><li>ITF-mET_Transducer</li></ul>|<ul><li>ITF-18_Raw</li><li>ITF-mET_SMA</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/tobo/viewme.png' align='center' width='150'>|**[tobo](/retired/tobo/Readme.md)**: The aim of this echOmod is to get the HV Pulse done.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-9_Pon</li><li>ITF-10_Poff</li><li>ITF-19_3.3V</li><li>ITF-mET_Transducer</li></ul>|<ul><li>ITF-18_Raw</li><li>ITF-mET_SMA</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/cletus/viewme.png' align='center' width='150'>|**[cletus](/retired/cletus/Readme.md)**: The aim of this module is to interface the transducer and the servo, aka the physical parts, to the analog part of the modules chain. More to come with the <a href="/retired/loftus/source/s3/Readme.md">Loftus head</a>.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-N_cc_motor_pwm</li><li>ITF-S_3_3v</li><li>ITF-mET_Transducer</li><li>ITF-mET_Piezo</li></ul>|<ul><li>ITF-mET_Piezo</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/sleepy/viewme.png' align='center' width='150'>|**[sleepy](/retired/sleepy/Readme.md)**: The aim of this echOmod is to encase the whole modules object in a neat case, making it transportable.|<ul><li>None</li></ul>|<ul><li>None</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/retro10PV/viewme.png' align='center' width='150'>|**[retro10PV](/retired/retro10PV/Readme.md)**: The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former <a href="http://echopen.org/index.php/ATL_Access_10PV">ATL10PV</a>.|<ul><li>ITF-A_gnd</li><li>ITF-F_12V</li><li>ITF-N_cc_motor_pwm</li><li>ITF-mET_Transducer</li><li>Motor</li><li>Tri-Piezo Head</li></ul>|<ul><li>Motor</li><li>ITF-mET_Transducer</li><li>Tri-Piezo Head</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/tomtom/viewme.png' align='center' width='150'>|**[tomtom](/retired/tomtom/Readme.md)**: The aim of this echOmod is to digitalize the signal, and to control the pulser, servo, ...|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-3_ENV</li><li>ITF-15_GPIO21</li></ul>|<ul><li>ITF-16_POn3</li><li>ITF-16_POn3</li><li>ITF-17_POff3</li><li>ITF-14_PWM</li><li>Wifi</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/toadkiller/viewme.png' align='center' width='150'>|**[toadkiller](/retired/toadkiller/Readme.md)**: The aim of this echOmod is to simulate the enveloppe (or maybe soon the raw signal) that would come from the piezo and analog chain.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-19_3.3V</li><li>ITF-3_ENV</li></ul>|<ul><li>WiFi UDP Stream</li><li>ITF-mED-TFT-Screen</li><li>ITF-9_Pon</li><li>ITF-10_Poff</li><li>ITF-14_PWM</li></ul>|
|<img src='https://raw.githubusercontent.com/kelu124/echomods/master/retired/oneeye/viewme.png' align='center' width='150'>|**[oneeye](/retired/oneeye/Readme.md)**: The module aims at making a microcontroler, for the moment the <code>ArduinoTrinketPro</code>, usable with the motherboard and the set of modules.|<ul><li>ITF-3_ENV</li><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li></ul>|<ul><li>ITF-7_GAIN</li><li>ITF-9_Pon</li><li>ITF-10_Poff</li><li>ITF-14_PWM</li></ul>|






## Progress on modules

# Progress on building the modules 


## Module-wise 


Note that the 'BONUS!' represents something that _could_ be done, and does not count as a strict TODO.


| Name of module | ToDo | Done |  Progress |
|------|-------|----|-----|









[](@autogenerated - invisible comment)