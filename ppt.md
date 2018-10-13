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

##  Raspberry Dev Kit

Using a simpler linux-enabled controler (the all-powerful Pi in its RPi 0 or Pi W) for the dev kit. Cost of materials aims at being as low as possible, below the 500$.


* Simply the servo and transducer module ([cletus](/cletus/)) -- get for _80$_ (Where? Recycling a transducer from ebay, servo from anywhere ([Amazon?](https://www.amazon.com/s/ref=nb_sb_noss?url=search-alias%3Dtoys-and-games&field-keywords=%22SG90+9G%22)))
* The Pi Heart of the echOmods ([tomtom](/tomtom/)) -- get for _10$_ (Where?  Get the Pi W from [plenty of sources](https://www.raspberrypi.org/products/pi-zero-w/))
* Using a dual ADC raspberry pHAT for 20Msps+ acquisition ([elmo](/elmo/)) -- get for _99$_ (Where? OSHPark, MacroFab, Tindie)
* Goblin: a TGC-Envelop-ADC module ([goblin](/goblin/)) -- get for _149$_ (Where? Custom made, get the [Gerbers](/goblin/source/), or [buy it preassembled on Tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/), or contact @kelu124)
* Tobo: the HV-pulser ([tobo](/tobo/)) -- get for _120$_ (Where? Custom made, get the [Gerbers](/retired/tobo/source/), [buy it preassembled on tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/) or contact @kelu124)


_Total cost of the set: 458$_

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
|<img src='https://github.com/kelu124/echomods/blob/master/wirephantom/viewme.png' align='center' width='150'>|**[wirephantom](/wirephantom/Readme.md)**: Just a phantom for calibrated signals|<ul><li>na</li></ul>|<ul><li>na</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/elmo/viewme.png' align='center' width='150'>|**[elmo](/elmo/Readme.md)**: The aim of this module is to achieve 20Msps, at 9bits or more. |<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-19_3.3V</li><li>ITF-12_RPIn</li></ul>|<ul><li>Signal Digitalized</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/doj/viewme.png' align='center' width='150'>|**[doj](/doj/Readme.md)**: Getting a motherboard: that's fitting all the modules in an easy way, with an easy access to all tracks. See this for the Kicad files.|||
|<img src='https://github.com/kelu124/echomods/blob/master/matty/viewme.png' align='center' width='150'>|**[matty](/matty/Readme.md)**: The aim is to summarize all modules in a all-inclusive board. Fast ADC, good load of memory, good SNR.. the not-so-DIY module, as it comes already assembled with nothing to do =)|||
|<img src='https://github.com/kelu124/echomods/blob/master/retroATL3/viewme.png' align='center' width='150'>|**[retroATL3](/retroATL3/Readme.md)**: The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former ATL3.|<ul><li>ITF-A_gnd</li><li>ITF-F_12V</li><li>ITF-N_cc_motor_pwm</li><li>ITF-mET_Transducer</li><li>Motor</li><li>Tri-Piezo Head</li></ul>|<ul><li>Motor</li><li>ITF-mET_Transducer</li><li>Tri-Piezo Head</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/goblin/viewme.png' align='center' width='150'>|**[goblin](/goblin/Readme.md)**: The aim of this echOmod is to get the signal coming back from a transducer, and to deliver the signal, analogically processed, with all steps accessible to hackers. |<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-7_GAIN</li><li>ITF-4_RawSig</li><li>ITF-3_ENV</li><li>ITF-18_Raw</li><li>ITF-mET_SMA</li></ul>|<ul><li>ITF-4_RawSig</li><li>ITF-3_ENV_signal_envelope</li><li>ITF-mEG_SPI</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/lite.tbo/viewme.png' align='center' width='150'>|**[lite.tbo](/lite.tbo/Readme.md)**: The aim of this echOmod is to get the HV Pulse done.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-9_Pon</li><li>ITF-10_Poff</li><li>ITF-19_3.3V</li><li>ITF-mET_Transducer</li></ul>|<ul><li>ITF-18_Raw</li><li>ITF-mET_SMA</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/silent/viewme.png' align='center' width='150'>|**[silent](/silent/Readme.md)**: The aim of this echOmod is to simulate a raw signal that would come from the piezo and analog chain.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-17_POff3</li></ul>|<ul><li>ITF-18_Raw</li></ul>|


# Experiments

 * 2016-08-09: [Goblin tests](/include/experiments/auto/20160809a.md): Testing the goblin board with the silent emulator. _(20160809a)_
 * 2016-08-14: [RPi](/include/experiments/auto/20160814a.md): Testing the acquisition with the BeagleBone DAQ. _(20160814a)_
 * 2016-08-22: [BBB+Probe](/include/experiments/auto/20160822a.md): Images acquired from a BeagleBone black with a probe _(20160822a)_
 * 2016-12-17: [Croaker](/include/experiments/auto/20161217a.md): Testing the acquisition with the croaker module. _(20161217a)_
 * 2017-06-11: [Croaker](/include/experiments/auto/20170611a.md): Testing the acquisition with the croaker module. _(20170611a)_
 * 2017-07-13: [Elmo](/include/experiments/auto/20170713a.md): Testing the new DAQ with two ADCs. _(20170713a)_
 * 2017-07-15: [RetroATL3 acquisition](/include/experiments/auto/20170715a.md): Getting an image from the retroATL3 probe. _(20170715a)_
 * 2017-09-30: [Alt.tbo](/include/experiments/auto/20170930a.md): Testing new pulser again 1/4 _(20170930a)_
 * 2017-10-01: [Alt.tbo](/include/experiments/auto/20171001a.md): Testing new pulser again 2/4 _(20171001a)_
 * 2017-10-01: [Alt.tbo](/include/experiments/auto/20171001b.md): Testing new pulser again 3/4 _(20171001b)_
 * 2017-11-11: [Alt.tbo](/include/experiments/auto/20171111a.md): Testing new pulser again 4/4 _(20171111a)_
 * 2017-11-12: [Probe](/include/experiments/auto/20171112a.md): Testing new probe with new pulser _(20171112a)_
 * 2017-11-24: [Impedance matching](/include/experiments/auto/20171124a.md): Doing some tests for impedance matching. _(20171124a)_
 * 2018-01-03: [Felix experiment](/include/experiments/auto/20180103a.md): Testing Felix setup with previous Bomanz module. _(20180103a)_
 * 2018-01-15: [Matty](/include/experiments/auto/20180115a.md): Receiving the first matty. _(20180115a)_
 * 2018-02-16: [Alt.tbo and Elmo](/include/experiments/auto/20180216a.md): Testing alt.tbo and elmo new boards. _(20180216a)_
 * 2018-02-17: [Alt.tbo and Elmo](/include/experiments/auto/20180217a.md): Testing alt.tbo and elmo new boards for pulser issues (there is not positive and negative pulse, only goes in direction). _(20180217a)_
 * 2018-02-24: [Matty speed tests](/include/experiments/auto/20180224a.md): Testing matty s acquisition at different speed, 12Msps to 24Msps. _(20180224a)_
 * 2018-02-24: [Matty Gain](/include/experiments/auto/20180224b.md): Testing matty's fixed gain settings. _(20180224b)_
 * 2018-02-25: [Matty and RetroATL3](/include/experiments/auto/20180225a.md): Acquisition of a probe image with matty. _(20180225a)_
 * 2018-03-10: [Matty DAQ](/include/experiments/auto/20180310a.md): testing the programmation of matty DAC control for the TGC. _(20180310a)_
 * 2018-04-03: [Voltage checks](/include/experiments/auto/20180403a.md): Testing matty at different voltages. _(20180403a)_
 * 2018-04-03: [Matty TGC test](/include/experiments/auto/20180403b.md): Testing matty 's TGC, including playing with the gain DAC and pulse control. _(20180403b)_
 * 2018-04-03: [Tomas first acq](/include/experiments/auto/20180403t.md): Tomas, a user, is getting a first image from a NDT setup with a block of steel. _(20180403t)_
 * 2018-04-15: [Test of new batch 1/2](/include/experiments/auto/20180415a.md): Testing the goblin board with silent, then test of the new lite.tbo pulser with a piezo. _(20180415a)_
 * 2018-04-15: [Test of new batch 2/2](/include/experiments/auto/20180415r.md): Testing the lite.tbo, goblin and elmo boards done at the fab - on a doj v2 motherboard. _(20180415r)_
 * 2018-04-17: [echomods vs MATTY](/include/experiments/auto/20180417a.md): Comparing the performances of the modules vs the FPGA board Matty _(20180417a)_
 * 2018-04-30: [JSON and Servo](/include/experiments/auto/20180430a.md): Better file management and servo control using Matty. _(20180430a)_
 * 2018-05-06: [SPI timing on Raspberry](/include/experiments/auto/20180506a.md): Checking SPI bottlenecks on Matty _(20180506a)_
 * 2018-05-11: [Enveloppe detection](/include/experiments/auto/20180511a.md): Checking different ways to rebuild enveloppe _(20180511a)_
 * 2018-05-16: [Matty file format](/include/experiments/auto/20180516a.md): Testing to format the data for experiments to be easily reproduced _(20180516a)_
 * 2018-06-20: [Uwe setup](/include/experiments/auto/20180620a.md): Testing ADC with Uwe setup with elmo and a 250khz source _(20180620a)_
 * 2018-07-21: [pyUn0 python lib and TGC](/include/experiments/auto/20180721a.md): Testing class-approach for acquisition and processing. Also tested Gain setup. _(20180721a)_
 * 2018-08-07: [ADR Ultrasound probe](/include/experiments/auto/20180807a.md): Photo reportage of opening an ADR Ultrasound probe. _(20180807a)_
 * 2018-08-07: [InterspecApogee](/include/experiments/auto/20180807b.md): Opening an InterspecApogee probe _(20180807b)_
 * 2018-08-09: [kretz AW14/5B/A](/include/experiments/auto/20180809a.md): Opening a kretz AW14/5B/A ultrasound probe _(20180809a)_
 * 2018-08-09: [Ausonics 7.5MHz probe](/include/experiments/auto/20180809b.md): Getting in a Ausonics 7.5MHz probe _(20180809b)_
 * 2018-08-11: [Kretz-Echo](/include/experiments/auto/20180811a.md): Find echoes on a kretzaw145ba probe _(20180811a)_
 * 2018-08-11: [Kretz-Motors](/include/experiments/auto/20180811b.md): Finding the motors on a kretzaw145ba probe _(20180811b)_
 * 2018-08-12: [KretzImage](/include/experiments/auto/20180812a.md): Getting an image with a kretz AW14/5B/A ultrasound probe _(20180812a)_
 * 2018-08-13: [pyUn0 lib glitches](/include/experiments/auto/20180813a.md): Experiment to capture glitches. Now captured (bugs with timing), pending is increasing NCycles above a 8 bit count. _(20180813a)_
 * 2018-08-14: [Reaching 128msps](/include/experiments/auto/20180814a.md): Trying to experiment getting 128Msps _(20180814a)_
 * 2018-08-25: [2D images building](/include/experiments/auto/20180825a.md): Testing new functions to unpack images (with N lines) _(20180825a)_
 * 2018-08-26: [16bits n-cycles](/include/experiments/auto/20180826a.md): Testing if the 16bits n cycles works _(20180826a)_
 * 2018-08-31: [wirephantom and retroATL3](/include/experiments/auto/20180831c.md): wirephantom and retroATL3 _(20180831c)_
 * 2018-09-01: [wirephantom and kretzaw145ba](/include/experiments/auto/20180901a.md): wirephantom and kretzaw145ba _(20180901a)_
 * 2018-10-13: [opening an hp2121](/include/experiments/auto/20181013a.md): try and open an hp2121, while waiting for a new matty _(20181013a)_

# Progress
 
# Progress on building the modules 


## Module-wise 


Note that the 'BONUS!' represents something that _could_ be done, and does not count as a strict TODO.


| Name of module | ToDo | Done |  Progress |
|------|-------|----|-----|
|wirephantom|<ul><li>None</li></ul>|<ul><li>All</li></ul>|50% |
|elmo|<ul><li>None</li></ul>|<ul><li>Write the <a href="/elmo/QuickStart.md">Quickstart</a></li><li>Getting a board an soldering some ADCs</li><li>Understand GPIO <a href="/elmo/data/20170609-NewADC.ipynb">mem mapping</a></li><li>Get raw data with <a href="/elmo/data/arduinoffset/20170612-ArduinoFFTed.ipynb">offset vref/2</a></li><li>Tests with a single ADC at 11Msps</li><li>Produce a batch of <a href="/elmo/source/v2/elmov2_altium.zip">rev2 elmo</a></li></ul>|85% |
|doj||<ul><li><a href="https://oshpark.com/shared_projects/2taE6p4M">PCB on OSHPark</a></li><li>Having the list of strips accessible</li><li>Design</li><li>Change the viewme</li><li>Assemble it</li><li>Test it</li><li>Adapt power supply from v2 - smaller board footprint</li><li>Add a level shifter been Pon 3.3 and 5 and Poff 3.3 and 5</li><li>A bit more space around the Pi0/PiW headers</li><li>Proper silkscreening around the Pi0 headers (they are reversed)</li><li>Jumper for the ADC in.. and selector (enveloppe and amplified signal) (either to Feather or to ADC .. and dedicated pin on Rpi)</li><li>SPI from RPi to Oled... or SPI to screen (to be checked in both case) .. or both kept, there are two SPI</li></ul>|100% |
|matty|<ul><li>See the <a href="/matty/nextsteps.md">next steps</a></li><li>Having it work with a <a href="/retroATL3/">retroATL3</a></li></ul>|<ul><li>Getting some signals!</li></ul>|33% |
|retroATL3|<ul><li>See the <a href="/matty/nextsteps.md">next steps</a></li><li>Having it work with a <a href="/retroATL3/">retroATL3</a></li></ul>|<ul><li><em>BONUS!</em> Get RealTime acquisition</li><li>Finding the pins mapping</li><li>Acquire and build ultrasound pictures =)</li><li>Motor in action</li><li>Refill Oil</li><li>Test echoes</li><li><a href="https://hackaday.io/project/9281-murgen-open-source-ultrasound-imaging/log/42113-testing-murgen-with-a-market-probe">Make and insert a video: there</a></li></ul>|77% |
|goblin|<ul><li>Test Goblin v2</li></ul>|<ul><li>Check the power consumption</li><li><a href="/retired/toadkiller/data/test_enveloppe/">Testing the in and out signals</a> of the board with the prudaq.</li><li>Specs to write</li><li>Agreeing on the strips </li><li>Check if 5V and 3.3V are stable</li><li>Defining the ICs to use</li><li>Getting schematics</li><li>Send microcircuits to Edgeflex</li><li>Receive the module</li><li>Publish the sources in KiCAD (@Sofian maybe?)</li><li>CANCELLED - Test it with the <a href="/retired/hannin/">EMW3165</a></li><li>Plug it to a <a href="/elmo/">RPi0</a> or <a href="/retired/toadkiller/">BBB</a> or <a href="/retired/croaker/">STM32</a></li><li>Connect the ADC to a RPi0</li></ul>|92% |
|lite.tbo|<ul><li>Review a bipolar design (originally alt.tbo -- but double the components and hence the price)</li></ul>|<ul><li>Preliminary testing</li></ul>|50% |
|silent||<ul><li>Feather: <a href="/silent/software/featherWICED/SignalGenerator.ino">work with an interrupt</a></li><li>Write code for feather WICED</li><li>Publish this code</li><li>Remove Signal Bias</li><li>Validated with a Feather WICED (<a href="/silent/software/featherWICED/SimpleSignalGenerator.ino">code</a>).</li><li>Feather: remove the average value before inputing in Goblin</li><li><a href="/silent/2016-08-09-SilentPlusTobo.md">Check output with Goblin</a></li></ul>|100% |


