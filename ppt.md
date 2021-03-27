% Habits
% John Doe
% March 22, 2005
 

# What do we do?
 
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

# What does it cost?

##  echOmods emulated

uC pings emulator and streams feedback


* This is the module which emulates the signal coming from the analog processing chain. ([silent](/silent/)) -- get for _35$_ (Where? Get from [Adafruit](https://www.adafruit.com/products/3056))
* The acquisition heart of the echOmods ([croaker](/croaker/)) -- get for _35$_ (Where? Get Feather from [Amz](http://amzn.to/2eGzlbG ) or [Adafruit](https://www.adafruit.com/products/3056). [OLED at Amz](http://amzn.to/2gi0vHl))
* Mogaba, the power supply ([mogaba](/mogaba/)) -- get for _5$_ (Where? Anywhere, or eg [Amazon?](https://www.amazon.com/s/ref=nb_sb_noss?url=node%3D667846011&field-keywords=3.3V+5V+Power+Supply+Module+Breadboard+))
* The motherboard of the echomods ([doj](/doj/)) -- get for _5$_ (Where? Anywhere for [stripboard](https://www.amazon.com/s/ref=nb_sb_noss_2?url=node%3D667846011&field-keywords=stripboard&rh=n%3A667846011%2Ck%3Astripboard). Or PCB from [OSHPark](https://oshpark.com/shared_projects/2taE6p4M) if you can order by 3. Or [straight from Tindie](https://www.tindie.com/products/kelu124/ultrasound-modules-motherboard/).)
* Goblin: a TGC-Envelop-ADC module ([goblin](/goblin/)) -- get for _149$_ (Where? Custom made, get the [Gerbers](/goblin/source/), or [buy it preassembled on Tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/), or contact @kelu124)


_Total cost of the set: 229$_

##  Wireless Dev Kit

The default setting for the sets


* Simply the servo and transducer module ([cletus](/cletus/)) -- get for _80$_ (Where? Recycling a transducer from ebay, servo from anywhere ([Amazon?](https://www.amazon.com/s/ref=nb_sb_noss?url=search-alias%3Dtoys-and-games&field-keywords=%22SG90+9G%22)))
* The acquisition heart of the echOmods ([croaker](/croaker/)) -- get for _35$_ (Where? Get Feather from [Amz](http://amzn.to/2eGzlbG ) or [Adafruit](https://www.adafruit.com/products/3056). [OLED at Amz](http://amzn.to/2gi0vHl))
* Mogaba, the power supply ([mogaba](/mogaba/)) -- get for _5$_ (Where? Anywhere, or eg [Amazon?](https://www.amazon.com/s/ref=nb_sb_noss?url=node%3D667846011&field-keywords=3.3V+5V+Power+Supply+Module+Breadboard+))
* Goblin: a TGC-Envelop-ADC module ([goblin](/goblin/)) -- get for _149$_ (Where? Custom made, get the [Gerbers](/goblin/source/), or [buy it preassembled on Tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/), or contact @kelu124)
* Tobo: the HV-pulser ([tobo](/tobo/)) -- get for _120$_ (Where? Custom made, get the [Gerbers](/retired/tobo/source/), [buy it preassembled on tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/) or contact @kelu124)


_Total cost of the set: 389$_

##  Raspberry Dev Kit

Using a simpler linux-enabled controler (the all-powerful Pi in its RPi 0 or Pi W) for the dev kit. Cost of materials aims at being as low as possible, below the 500$.


* Simply the servo and transducer module ([cletus](/cletus/)) -- get for _80$_ (Where? Recycling a transducer from ebay, servo from anywhere ([Amazon?](https://www.amazon.com/s/ref=nb_sb_noss?url=search-alias%3Dtoys-and-games&field-keywords=%22SG90+9G%22)))
* The Pi Heart of the echOmods ([tomtom](/tomtom/)) -- get for _10$_ (Where?  Get the Pi W from [plenty of sources](https://www.raspberrypi.org/products/pi-zero-w/))
* Using a dual ADC raspberry pHAT for 20Msps+ acquisition ([elmo](/elmo/)) -- get for _99$_ (Where? OSHPark, MacroFab, Tindie)
* Goblin: a TGC-Envelop-ADC module ([goblin](/goblin/)) -- get for _149$_ (Where? Custom made, get the [Gerbers](/goblin/source/), or [buy it preassembled on Tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/), or contact @kelu124)
* Tobo: the HV-pulser ([tobo](/tobo/)) -- get for _120$_ (Where? Custom made, get the [Gerbers](/retired/tobo/source/), [buy it preassembled on tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/) or contact @kelu124)


_Total cost of the set: 458$_

##  The Beaglebone version, along with an hacked probe

Some stuff, unexpensive to buy, to build a ultrasound testing kit, totalling less than _500$_.


* Retrohacking the ATL Access 3 probe ([retroATL3](/retroATL3/)) -- get for _75$_ (Where? Recycling a probe from [ebay](http://www.ebay.fr/sch/i.html?_odkw=%22atl+access%22+probe&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR0.TRC0.H0.X%22atl+access%22+.TRS0&_nkw=%22atl+access%22+&_sacat=0))
* This is the module to get high-speed (40Msps) signal acquisition. ([toadkiller](/toadkiller/)) -- get for _79$_ (Where?  A bundle at 169$ from [Groupgets](https://groupgets.com/manufacturers/getlab/products/prudaq) or as a [standalone](https://store.groupgets.com/#!/p/68936091) at 79$ )
* Mogaba, the power supply ([mogaba](/mogaba/)) -- get for _5$_ (Where? Anywhere, or eg [Amazon?](https://www.amazon.com/s/ref=nb_sb_noss?url=node%3D667846011&field-keywords=3.3V+5V+Power+Supply+Module+Breadboard+))
* Goblin: a TGC-Envelop-ADC module ([goblin](/goblin/)) -- get for _149$_ (Where? Custom made, get the [Gerbers](/goblin/source/), or [buy it preassembled on Tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/), or contact @kelu124)
* Tobo: the HV-pulser ([tobo](/tobo/)) -- get for _120$_ (Where? Custom made, get the [Gerbers](/retired/tobo/source/), [buy it preassembled on tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/) or contact @kelu124)
* The motherboard of the echomods ([doj](/doj/)) -- get for _5$_ (Where? Anywhere for [stripboard](https://www.amazon.com/s/ref=nb_sb_noss_2?url=node%3D667846011&field-keywords=stripboard&rh=n%3A667846011%2Ck%3Astripboard). Or PCB from [OSHPark](https://oshpark.com/shared_projects/2taE6p4M) if you can order by 3. Or [straight from Tindie](https://www.tindie.com/products/kelu124/ultrasound-modules-motherboard/).)
* One-eye, the controler ([oneeye](/oneeye/)) -- get for _10$_ (Where? from [Adafruit](https://www.adafruit.com/product/2000))


_Total cost of the set: 443$_



[](@autogenerated - invisible comment)
 
# Graphing the modules
 

# The modules organization 

![Graph](/include/sets/basic.png) 

 
# Table Docs
# A recap of the modules 


| ThumbnailImage | Name | In | Out |
|------|-------|----|------|
|<img src='https://github.com/kelu124/echomods/blob/master/retroATL3/viewme.png' align='center' width='150'>|**[retroATL3](/retroATL3/Readme.md)**: The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former ATL3.|<ul><li>ITF-A_gnd</li><li>ITF-F_12V</li><li>ITF-N_cc_motor_pwm</li><li>ITF-mET_Transducer</li><li>Motor</li><li>Tri-Piezo Head</li></ul>|<ul><li>Motor</li><li>ITF-mET_Transducer</li><li>Tri-Piezo Head</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/elmo/viewme.png' align='center' width='150'>|**[elmo](/elmo/Readme.md)**: The aim of this module is to achieve 20Msps, at 9bits or more. |<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-19_3.3V</li><li>ITF-12_RPIn</li></ul>|<ul><li>Signal Digitalized</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/goblin/viewme.png' align='center' width='150'>|**[goblin](/goblin/Readme.md)**: The aim of this echOmod is to get the signal coming back from a transducer, and to deliver the signal, analogically processed, with all steps accessible to hackers. |<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-7_GAIN</li><li>ITF-4_RawSig</li><li>ITF-3_ENV</li><li>ITF-18_Raw</li><li>ITF-mET_SMA</li></ul>|<ul><li>ITF-4_RawSig</li><li>ITF-3_ENV_signal_envelope</li><li>ITF-mEG_SPI</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/lite.tbo/viewme.png' align='center' width='150'>|**[lite.tbo](/lite.tbo/Readme.md)**: The aim of this echOmod is to get the HV Pulse done.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-9_Pon</li><li>ITF-10_Poff</li><li>ITF-19_3.3V</li><li>ITF-mET_Transducer</li></ul>|<ul><li>ITF-18_Raw</li><li>ITF-mET_SMA</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/lit3rick/viewme.png' align='center' width='150'>|**[lit3rick](/lit3rick/Readme.md)**: The aim is to summarize all modules in a all-inclusive board. Fast ADC, good load of memory, good SNR.. the not-so-DIY module, as it comes already assembled with nothing to do. Based on up5k.|||
|<img src='https://github.com/kelu124/echomods/blob/master/matty/viewme.png' align='center' width='150'>|**[matty](/matty/Readme.md)**: The aim is to summarize all modules in a all-inclusive board. Fast ADC, good load of memory, good SNR.. the not-so-DIY module, as it comes already assembled with nothing to do =)|||
|<img src='https://github.com/kelu124/echomods/blob/master/doj/viewme.png' align='center' width='150'>|**[doj](/doj/Readme.md)**: Getting a motherboard: that's fitting all the modules in an easy way, with an easy access to all tracks. See this for the Kicad files.|||
|<img src='https://github.com/kelu124/echomods/blob/master/wirephantom/viewme.png' align='center' width='150'>|**[wirephantom](/wirephantom/Readme.md)**: Just a phantom for calibrated signals|<ul><li>na</li></ul>|<ul><li>na</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/silent/viewme.png' align='center' width='150'>|**[silent](/silent/Readme.md)**: The aim of this echOmod is to simulate a raw signal that would come from the piezo and analog chain.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-17_POff3</li></ul>|<ul><li>ITF-18_Raw</li></ul>|


# Experiments

 * 2021-01-29: [`Tri` two probes](/include/experiments/auto/20210129a.md): Tri's tests with two probes _(20210129a)_
 * 2020-12-23: [test probes](/include/experiments/auto/20201223a.md): testing probes with un0usb _(20201223a)_
 * 2020-12-19: [test piezos](/include/experiments/auto/20201219r.md): VNAs piezos (dismanted ones) _(20201219r)_
 * 2020-11-28: [hp2121 matching](/include/experiments/auto/20201128a.md): checking hp2121 probe impedance matching _(20201128a)_
 * 2020-11-08: [impedance matching](/include/experiments/auto/20201108a.md): testing two piezos with impedance matching network _(20201108a)_
 * 2020-11-07: [lib 025](/include/experiments/auto/20201107a.md): NDT presentation - un0rick & usb _(20201107a)_
 * 2020-11-04: [lib 024](/include/experiments/auto/20201104a.md): Basics on - un0rick & usb _(20201104a)_
 * 2020-11-03: [Impedance matching](/include/experiments/auto/20201103a.md): Interesting results for impedance matching. _(20201103a)_
 * 2020-10-31: [Pulse width calculation](/include/experiments/auto/20201031a.md): how to get the best echo as a function of pulser waveform _(20201031a)_
 * 2020-10-28: [strange issues pyUn0](/include/experiments/auto/20201028a.md): seems CS does not work _(20201028a)_
 * 2020-10-26: [usb firmware](/include/experiments/auto/20201026a.md): testing it works with un0rick _(20201026a)_
 * 2020-10-24: [i2s issue](/include/experiments/auto/20201024a.md): Exploring the i2s offsets _(20201024a)_
 * 2020-10-23: [Canada](/include/experiments/auto/20201023a.md): `Silvio` first lit3rick tests _(20201023a)_
 * 2020-10-22: [Spain](/include/experiments/auto/20201022a.md): `Jorge` tests on lit3rick _(20201022a)_
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
 * 2018-04-03: [`Tomas` first acq](/include/experiments/auto/20180403t.md): Tomas, a user, is getting a first image from a NDT setup with a block of steel. _(20180403t)_
 * 2018-04-03: [Matty TGC test](/include/experiments/auto/20180403b.md): Testing matty 's TGC, including playing with the gain DAC and pulse control. _(20180403b)_
 * 2018-04-03: [Voltage checks](/include/experiments/auto/20180403a.md): Testing matty at different voltages. _(20180403a)_
 * 2018-03-10: [Matty DAQ](/include/experiments/auto/20180310a.md): testing the programmation of matty DAC control for the TGC. _(20180310a)_
 * 2018-02-25: [Matty and RetroATL3](/include/experiments/auto/20180225a.md): Acquisition of a probe image with matty. _(20180225a)_
 * 2018-02-24: [Matty Gain](/include/experiments/auto/20180224b.md): Testing matty's fixed gain settings. _(20180224b)_
 * 2018-02-24: [Matty speed tests](/include/experiments/auto/20180224a.md): Testing matty s acquisition at different speed, 12Msps to 24Msps. _(20180224a)_
 * 2018-02-17: [Alt.tbo and Elmo](/include/experiments/auto/20180217a.md): Testing alt.tbo and elmo new boards for pulser issues (there is not positive and negative pulse, only goes in direction). _(20180217a)_
 * 2018-02-16: [Alt.tbo and Elmo](/include/experiments/auto/20180216a.md): Testing alt.tbo and elmo new boards. _(20180216a)_
 * 2018-01-15: [Matty](/include/experiments/auto/20180115a.md): Receiving the first matty. _(20180115a)_
 * 2018-01-03: [`Felix` experiment](/include/experiments/auto/20180103a.md): Testing Felix setup with previous Bomanz module. _(20180103a)_
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

# Progress
 
# Progress on building the modules 


## Module-wise 


Note that the 'BONUS!' represents something that _could_ be done, and does not count as a strict TODO.


| Name of module | ToDo | Done |  Progress |
|------|-------|----|-----|


