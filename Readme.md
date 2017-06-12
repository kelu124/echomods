# What is this project? [](@description Pitch/Intro of the project)

This project has a specific target of providing a __low-cost, open source technological kit to allow scientists, academics, hackers, makers or OSHW fans to hack their way to ultrasound imaging__ - below 500$ - at home, with no specific equipment required. For complementary sources of information, you can visit:

* the [github repo](https://github.com/kelu124/echomods/), for the source files, raw data and raw experiment logs;
* the [online manual/book](https://www.gitbook.com/book/kelu124/echomods/details) for a easily readable and searchable archive of the whole work;
* the [hackaday page](https://hackaday.io/project/9281-murgen-open-source-ultrasound-imaging), where I tried to blog day-to-day experiments in a casual format;
* an [article summarizing the experiment on the Journal of Open Hardware](http://openhardware.metajnl.com/articles/10.5334/joh.2/) - [DOI:10.5334/joh.2]( http://doi.org/10.5334/joh.2);
* the [slack channel if you want to discuss](https://join.slack.com/usdevkit/shared_invite/MTkxODU5MjU0NjI1LTE0OTY1ODgxMDEtMmYyZTliZDBlZA);
* the Tindie store for the [analog processing unit](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/) and the [pulser](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/) or [the motherboard](https://www.tindie.com/products/kelu124/ultrasound-modules-motherboard/).
 
__Disclaimer__: though an engineer, this project is the first of its sort, I never did something related. Bear with us, and the discovery process, but I'm happy to learn on the way =)

__Disclaimer #2__: ultrasound raises questions. In case you build a scanner, use caution and good sense!

__Disclaimer #3__: Beware! Though I am one of echopen's cofounders, this personnal pet-project lives in the echopen community, and is not a project in the scope of the echopen's association.

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.377054.svg)](https://doi.org/10.5281/zenodo.377054)



## What are the arduino-like ultrasound module ?

__Creating modules to facilitate ultrasound hacking__ : the principles of the echOmods is to enable a full chain of ultrasound image processing and hardware control.

We have chosen to use a module approach to make sure that each key component inside ultrasound image processing can easily be replaced and compared with another module, while providing logical _logic blocks_ and corresponding interfaces for these modules to communicate. There's a module for [high-voltage pulsing](/tobo/), one for the [transducer](/retroATL3/), one for the [analog processing](/goblin/), one for [data acquisiton](/toadkiller/), ... and many more!

## What images does it give ?

![](/include/20161016/2619341460036774092.png)

## What does it look like?

The modules sit on a breadboard, and communicate through the tracks laying below. The configuration represented below show the Basic dev kit.

![](/include/20160814/IMG_3430.png)



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
* Tobo: the HV-pulser ([tobo](/tobo/)) -- get for _120$_ (Where? Custom made, get the [Gerbers](/tobo/source/), [buy it preassembled on tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/) or contact @kelu124)


_Total cost of the set: 389$_

##  The Beaglebone version, along with an hacked probe

Some stuff, unexpensive to buy, to build a ultrasound testing kit, totalling less than _500$_.


* Retrohacking the ATL Access 3 probe ([retroATL3](/retroATL3/)) -- get for _75$_ (Where? Recycling a probe from [ebay](http://www.ebay.fr/sch/i.html?_odkw=%22atl+access%22+probe&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR0.TRC0.H0.X%22atl+access%22+.TRS0&_nkw=%22atl+access%22+&_sacat=0))
* This is the module to get high-speed (40Msps) signal acquisition. ([toadkiller](/toadkiller/)) -- get for _79$_ (Where?  A bundle at 169$ from [Groupgets](https://groupgets.com/manufacturers/getlab/products/prudaq) or as a [standalone](https://store.groupgets.com/#!/p/68936091) at 79$ )
* Mogaba, the power supply ([mogaba](/mogaba/)) -- get for _5$_ (Where? Anywhere, or eg [Amazon?](https://www.amazon.com/s/ref=nb_sb_noss?url=node%3D667846011&field-keywords=3.3V+5V+Power+Supply+Module+Breadboard+))
* Goblin: a TGC-Envelop-ADC module ([goblin](/goblin/)) -- get for _149$_ (Where? Custom made, get the [Gerbers](/goblin/source/), or [buy it preassembled on Tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/), or contact @kelu124)
* Tobo: the HV-pulser ([tobo](/tobo/)) -- get for _120$_ (Where? Custom made, get the [Gerbers](/tobo/source/), [buy it preassembled on tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/) or contact @kelu124)
* The motherboard of the echomods ([doj](/doj/)) -- get for _5$_ (Where? Anywhere for [stripboard](https://www.amazon.com/s/ref=nb_sb_noss_2?url=node%3D667846011&field-keywords=stripboard&rh=n%3A667846011%2Ck%3Astripboard). Or PCB from [OSHPark](https://oshpark.com/shared_projects/2taE6p4M) if you can order by 3. Or [straight from Tindie](https://www.tindie.com/products/kelu124/ultrasound-modules-motherboard/).)
* One-eye, the controler ([oneeye](/oneeye/)) -- get for _10$_ (Where? from [Adafruit](https://www.adafruit.com/product/2000))


_Total cost of the set: 443$_


[](@autogenerated - invisible comment)
## Ultrasound hardware structure

[](@description Short description of the organization of modules)

To produce an image, the modules have to create a [high voltage pulse](/tobo/), which excites a [transducer](/retroATL3/). Echoes coming from the body are amplified using a [TGC + LNA](/goblin/), which cleans the analog signal, which itself [gets digitalized](/toadkiller/). 

The diagram is represented below:

![](/include/images/blockdiagram.gif)




# The modules organization 

![Graph](/include/sets/basic.png) 

# A recap of our modules 


| ThumbnailImage | Name | In | Out |
|------|-------|----|------|
|<img src='https://github.com/kelu124/echomods/blob/master/sleepy/viewme.png' align='center' width='150'>|**[sleepy](/sleepy/Readme.md)**: The aim of this echOmod is to encase the whole modules object in a neat case, making it transportable.|<ul><li>None</li></ul>|<ul><li>None</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/tobo/viewme.png' align='center' width='150'>|**[tobo](/tobo/Readme.md)**: The aim of this echOmod is to get the HV Pulse done.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-I_pulse_on</li><li>ITF-J_pulse_off</li><li>ITF-S_3_3v</li><li>ITF-mET_Transducer</li></ul>|<ul><li>ITF-R_reserved</li><li>ITF-mET_SMA</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/elmo/viewme.png' align='center' width='150'>|**[elmo](/elmo/Readme.md)**: The aim of this module is to achieve 10Msps, ideally 20Msps, at 9bits or more.|<ul><li>ITF-A_gnd</li><li>ITF-F_12V</li></ul>|<ul><li>Motor</li><li>ITF-mET_Transducer</li><li>Tri-Piezo Head</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/cletus/viewme.png' align='center' width='150'>|**[cletus](/cletus/Readme.md)**: The aim of this module is to interface the transducer and the servo, aka the physical parts, to the analog part of the modules chain.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-N_cc_motor_pwm</li><li>ITF-S_3_3v</li><li>ITF-mET_Transducer</li><li>ITF-mET_Piezo</li></ul>|<ul><li>ITF-mET_Piezo</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/tomtom/viewme.png' align='center' width='150'>|**[tomtom](/tomtom/Readme.md)**: The aim of this echOmod is to digitalize the signal, and to control the pulser, servo, ...|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-E_signal_envelope</li><li>ITF-I_pulse_on</li></ul>|<ul><li>ITF-I_pulse_on</li><li>ITF-J_pulse_off</li><li>ITF-C_amplified_raw_signal</li><li>ITF-E_signal_envelope</li><li>ITF-N_cc_motor_pwm</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/doj/viewme.png' align='center' width='150'>|**[doj](/doj/Readme.md)**: Getting a motherboard: that's fitting all the modules in an easy way, with an easy access to all tracks. See this for the Kicad files.|||
|<img src='https://github.com/kelu124/echomods/blob/master/oneeye/viewme.png' align='center' width='150'>|**[oneeye](/oneeye/Readme.md)**: The module aims at making a microcontroler, for the moment the ArduinoTrinketPro, usable with the motherboard and the set of modules.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-S_3_3v</li></ul>|<ul><li>ITF-G_gain_control</li><li>ITF-I_pulse_on</li><li>ITF-J_pulse_off</li><li>ITF-N_cc_motor_pwm</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/croaker/viewme.png' align='center' width='150'>|**[croaker](/croaker/Readme.md)**: The aim of this echOmod is to receive the signal and process it.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-E_signal_envelope</li><li>ITF-I_pulse_on</li><li>ITF-J_pulse_off</li></ul>|<ul><li>ITF-mED-TFT-Screen</li><li>ITF-mED-OLED-Screen</li><li>ITF-mEC-WiFi-UDP-Stream</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/retroATL3/viewme.png' align='center' width='150'>|**[retroATL3](/retroATL3/Readme.md)**: The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former ATL3.|<ul><li>ITF-A_gnd</li><li>ITF-F_12V</li><li>ITF-N_cc_motor_pwm</li><li>ITF-mET_Transducer</li><li>Motor</li><li>Tri-Piezo Head</li></ul>|<ul><li>Motor</li><li>ITF-mET_Transducer</li><li>Tri-Piezo Head</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/toadkiller/viewme.png' align='center' width='150'>|**[toadkiller](/toadkiller/Readme.md)**: The aim of this echOmod is to simulate the enveloppe (or maybe soon the raw signal) that would come from the piezo and analog chain.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-S_3_3v</li><li>ITF-E_signal_envelope</li></ul>|<ul><li>WiFi UDP Stream</li><li>ITF-mED-TFT-Screen</li><li>ITF-I_pulse_on</li><li>ITF-J_pulse_off</li><li>ITF-N_cc_motor_pwm</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/goblin/viewme.png' align='center' width='150'>|**[goblin](/goblin/Readme.md)**: The aim of this echOmod is to get the signal coming back from a transducer, and to deliver the signal, analogically processed, with all steps accessible to hackers. |<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-S_3_3v</li><li>ITF-G_gain_control</li><li>ITF-C_amplified_raw_signal</li><li>ITF-E_signal_envelope</li><li>ITF-R_reserved</li><li>ITF-mET_SMA</li></ul>|<ul><li>ITF-C_amplified_raw_signal</li><li>ITF-E_signal_envelope</li><li>ITF-mEG_SPI</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/silent/viewme.png' align='center' width='150'>|**[silent](/silent/Readme.md)**: The aim of this echOmod is to simulate a raw signal that would come from the piezo and analog chain.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-J_pulse_off</li></ul>|<ul><li>ITF-R_reserved</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/mogaba/viewme.png' align='center' width='150'>|**[mogaba](/mogaba/Readme.md)**: The aim of this echOmod is to get 3.3V and 5V done.|<ul><li>ITF-mEM_Alimentation</li><li>ITF-F_12V</li></ul>|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-F_12V</li><li>ITF-S_3_3v</li></ul>|
# Progress on building the modules 


## Module-wise 


Note that the 'BONUS!' represents something that _could_ be done, and does not count as a strict TODO.


| Name of module | ToDo | Done |  Progress |
|------|-------|----|-----|
|sleepy|<ul><li>Choose the design once the modules are done</li><li>Get to work with Arthur</li></ul>|<ul><li>Checking Arthur availability</li></ul>|33% |
|tobo||<ul><li>Writing specs </li><li>HV7360 has been updated</li><li>Sending microcircuits to Edgeflex</li><li>Agreeing on the strips/tracks </li><li>Defining the ICs to use to pulse</li><li>Getting schematics</li><li>Publishing schematics</li><li>Receive the module</li><li>Test it with different transducers</li><li>Publish the sources in KiCAD</li></ul>|100% |
|elmo||<ul><li>Getting a board an soldering some ADCs</li></ul>|100% |
|cletus|<ul><li>Remove the jitter (see image in Rdme)</li><li>Include <a href="/cletus/2017-06-08_FindingSuppliers.md">notes</a></li></ul>|<ul><li>Get a 3.5MHz piezo</li></ul>|33% |
|tomtom|<ul><li>Testing the limits of ADC acquisition (speed / bits)</li><li>Save images as DICOMs</li><li>Understand why some GPIOs do not have lower values at 0..</li><li>MixedGadget =&gt; <a href="http://isticktoit.net/?p=1383">Storage + ethernet</a> or <a href="https://gist.github.com/gbaman/50b6cca61dd1c3f88f41">this</a> or <a href="https://learn.adafruit.com/turning-your-raspberry-pi-zero-into-a-usb-gadget/overview">that</a>.</li><li>Set pins to down <a href="https://raspberrypi.stackexchange.com/questions/4664/setting-gpio-value-on-boot">on boot</a></li></ul>|<ul><li>Developping a CA3306E version of <a href="https://github.com/kelu124/bomanz/blob/master/CA3306E/20170422-FirstAcqs.ipynb">the 10Msps ADC pHAT</a> for testing.</li><li>Dev a version of the <a href="https://github.com/kelu124/bomanz/blob/master/ADC08200/">ADC08200</a></li><li>Create a kernel module</li><li>Test the <a href="http://www.toptechboy.com/raspberry-pi/raspberry-pi-lesson-28-controlling-a-servo-on-raspberry-pi-with-python/">PWM</a></li></ul>|44% |
|doj|<ul><li>Change the viewme</li></ul>|<ul><li><a href="https://oshpark.com/shared_projects/2taE6p4M">PCB on OSHPark</a></li><li>Having the list of strips accessible</li><li>Design</li><li>Assemble it</li><li>Test it</li><li>Adapt power supply from v2 - smaller board footprint</li><li>Add a level shifter been Pon 3.3 and 5 and Poff 3.3 and 5</li><li>A bit more space around the Pi0/PiW headers</li><li>Proper silkscreening around the Pi0 headers (they are reversed)</li><li>Jumper for the ADC in.. and selector (enveloppe and amplified signal) (either to Feather or to ADC .. and dedicated pin on Rpi)</li><li>SPI from RPi to Oled... or SPI to screen (to be checked in both case) .. or both kept, there are two SPI</li></ul>|91% |
|oneeye|<ul><li>Find the code back</li></ul>|<ul><li>First test with Arduino Trinket</li></ul>|50% |
|croaker|<ul><li>Replace the work done by <a href="/oneeye/">OneEye</a> by <a href="/croaker/">Croaker</a> - that is, pulse control.</li><li>Get better total ADC speed with an iterleaved move</li><li>Develop a Cletus+Croaker way of working with a gyroscope+accelerometer.</li><li>Have Croaker generate its own AP</li></ul>|<ul><li>Choose the platform (<a href="/toadkiller/">BBB</a>, RPi0, <a href="/croaker/">STM32</a>, ... ?) : that'll be a <code>Feather WICED</code> for this iteration of Croaker</li><li>Getting some images</li><li>Getting images onto a screen</li><li>Getting good resolution images -- see the <a href="/croaker/data/20161217/20161217-TestingArduinoAndPhantom.md">breadboard phantom</a></li></ul>|50% |
|retroATL3|<ul><li>Replace the work done by <a href="/oneeye/">OneEye</a> by <a href="/croaker/">Croaker</a> - that is, pulse control.</li><li>Get better total ADC speed with an iterleaved move</li><li>Develop a Cletus+Croaker way of working with a gyroscope+accelerometer.</li><li>Have Croaker generate its own AP</li></ul>|<ul><li><em>BONUS!</em> Get RealTime acquisition</li><li>Finding the pins mapping</li><li>Acquire and build ultrasound pictures =)</li><li>Motor in action</li><li>Refill Oil</li><li>Test echoes</li><li><a href="https://hackaday.io/project/9281-murgen-open-source-ultrasound-imaging/log/42113-testing-murgen-with-a-market-probe">Make and insert a video: there</a></li></ul>|63% |
|toadkiller|<ul><li>Enhance the BBB to transform it into a ultrasound server</li></ul>|<ul><li>Do the quick check up</li><li>Acquire some data</li><li>Post some data</li></ul>|75% |
|goblin|<ul><li><em>BONUS!</em> Plug it to a <a href="/croaker/">RPi0 or BBB or RPi</a> or else.</li><li>Connect the ADC to a RPi0</li></ul>|<ul><li>Check the power consumption</li><li><a href="/toadkiller/data/test_enveloppe/">Testing the in and out signals</a> of the board with the prudaq.</li><li>Specs to write</li><li>Agreeing on the strips </li><li>Check if 5V and 3.3V are stable</li><li>Defining the ICs to use</li><li>Getting schematics</li><li>Send microcircuits to Edgeflex</li><li>Receive the module</li><li>Publish the sources in KiCAD (@Sofian maybe?)</li><li>CANCELLED - Test it with the <a href="/retired/hannin/">EMW3165</a>.</li></ul>|91% |
|silent||<ul><li>Feather: <a href="/silent/software/featherWICED/SignalGenerator.ino">work with an interrupt</a></li><li>Write code for feather WICED</li><li>Publish this code</li><li>Remove Signal Bias</li><li>Validated with a Feather WICED (<a href="/silent/software/featherWICED/SimpleSignalGenerator.ino">code</a>).</li><li>Feather: remove the average value before inputing in Goblin</li><li><a href="/silent/2016-08-09-SilentPlusTobo.md">Check output with Goblin</a></li></ul>|100% |
|mogaba|<ul><li><em>BONUS!</em> benchmark power supplies </li></ul>|<ul><li>Manage to feed it 12V</li><li>Bring power to it through the 12V <code>ITF-F_12V</code> track </li><li>Test if 12V OK</li><li>Find supplier</li></ul>|100% |


## Shopping list

Here's a couple of things we're working on, for which you could help as well.

* Boosting the 6Msps croaker acquisition (see Wayne?)
* gh-pages: adding presentations, files list, community
* Adding PPTs to the makedoc list
* Processing PPTs

* Choose the design once the modules are done (in [sleepy](/sleepy/))
* Get to work with Arthur (in [sleepy](/sleepy/))
* Remove the jitter (see image in Rdme) (in [cletus](/cletus/))
* Include <a href="/cletus/2017-06-08_FindingSuppliers.md">notes</a> (in [cletus](/cletus/))
* Testing the limits of ADC acquisition (speed / bits) (in [tomtom](/tomtom/))
* Save images as DICOMs (in [tomtom](/tomtom/))
* Understand why some GPIOs do not have lower values at 0.. (in [tomtom](/tomtom/))
* MixedGadget =&gt; <a href="http://isticktoit.net/?p=1383">Storage + ethernet</a> or <a href="https://gist.github.com/gbaman/50b6cca61dd1c3f88f41">this</a> or <a href="https://learn.adafruit.com/turning-your-raspberry-pi-zero-into-a-usb-gadget/overview">that</a>. (in [tomtom](/tomtom/))
* Set pins to down <a href="https://raspberrypi.stackexchange.com/questions/4664/setting-gpio-value-on-boot">on boot</a> (in [tomtom](/tomtom/))
* Change the viewme (in [doj](/doj/))
* Find the code back (in [oneeye](/oneeye/))
* Replace the work done by <a href="/oneeye/">OneEye</a> by <a href="/croaker/">Croaker</a> - that is, pulse control. (in [croaker](/croaker/))
* Get better total ADC speed with an iterleaved move (in [croaker](/croaker/))
* Develop a Cletus+Croaker way of working with a gyroscope+accelerometer. (in [croaker](/croaker/))
* Have Croaker generate its own AP (in [croaker](/croaker/))
* Enhance the BBB to transform it into a ultrasound server (in [toadkiller](/toadkiller/))
* <em>BONUS!</em> Plug it to a <a href="/croaker/">RPi0 or BBB or RPi</a> or else. (in [goblin](/goblin/))
* Connect the ADC to a RPi0 (in [goblin](/goblin/))
* <em>BONUS!</em> benchmark power supplies  (in [mogaba](/mogaba/))


# A recap of our retired modules 


| ThumbnailImage | Name | In | Out |
|------|-------|----|------|
|<img src='https://github.com/kelu124/echomods/blob/master/retired/elmo/viewme.png' align='center' width='150'>|**[elmo](/retired/elmo/Readme.md)**: The aim of this echOmod is to get be the microcontroller heart|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-E_signal_envelope</li></ul>|<ul><li>WiFi</li><li>Screen</li><li>ITF-G_gain_control</li><li>ITF-I_pulse_on</li><li>ITF-J_pulse_off</li><li>ITF-N_cc_motor_pwm</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/retired/hannin/viewme.png' align='center' width='150'>|**[hannin](/retired/hannin/Readme.md)**: The aim of this echOmod is to acquire the enveloppe of the signal and stream it. Designed for slow (~64 lines / s) acquisitions.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-S_3_3v</li><li>ITF-E_signal_envelope</li><li>ITF-I_pulse_on</li></ul>|<ul><li>ITF-mEC-WiFi-UDP-Stream</li><li>ITF-mED-TFT-Screen</li><li>ITF-I_pulse_on</li><li>ITF-J_pulse_off</li><li>ITF-N_cc_motor_pwm</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/retired/retro10PV/viewme.png' align='center' width='150'>|**[retro10PV](/retired/retro10PV/Readme.md)**: The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former <a href="http://echopen.org/index.php/ATL_Access_10PV">ATL10PV</a>.|<ul><li>ITF-A_gnd</li><li>ITF-F_12V</li><li>ITF-N_cc_motor_pwm</li><li>ITF-mET_Transducer</li><li>Motor</li><li>Tri-Piezo Head</li></ul>|<ul><li>Motor</li><li>ITF-mET_Transducer</li><li>Tri-Piezo Head</li></ul>|


# Interfaces table for the motherboard

| Name | Title | Amplitude |
|------|-------|-----------|
|`ITF-A_gnd`|_Ground_|[0V]|
|`ITF-B_5v`|_5V alimentation_|[5V, 5V]|
|`ITF-C_amplified_raw_signal`|_Amplified raw signal_|[0V, 2.5V]|
|`ITF-D_amplified_filtered_signal`|_Amplified filtered signal_|[0V, 2.5V]|
|`ITF-E_signal_envelope`|_Signal envelope_|[0V, 2.5V]|
|`ITF-F_12v`|_12V alimentation_|[12V, 12V]|
|`ITF-G_gain_control`|_Amplifier gain_|[0V, 1V]|
|`ITF-H_neg_12v`|_-12V alimentation_|[-12V, -12V]|
|`ITF-I_pulse_on`|_Pulse on_|[0V, 3.3V-5V]|
|`ITF-J_pulse_off`|_Pulse off_|[0V, 5V]|
|`ITF-K_pulse_redpitaya`|_Pulse info for Redpitaya_|[0V, 3.3V]|
|`ITF-L_18v_alimentation`|_18V external alimentation_|[15V, 20V]|
|`ITF-M_abs_angle`|_Absolute tranducer position_||
|`ITF-N_cc_motor_pwm`|_CC motor pwm_|[0V, 5V]|
|`ITF-N_stepper_b2`|_Stepper motor B2 signal_|[-5V, 5V]|
|`ITF-O_cc_motor_encoder`|_CC motor incremental encoder_|[0V, 5V]|
|`ITF-O_stepper_b1`|_Stepper motor B1 signal_|[-5V, 5V]|
|`ITF-P_stepper_a1`|_Stepper motor A1 signal_|[-5V, 5V]|
|`ITF-Q_stepper_a2`|_Stepper motor A2 signal_|[-5V, 5V]|
|`ITF-R_reserved`|_reserved track_||
|`ITF-S_3_3v`|_3.3V alimentation_|[3.3V, 3.3V]|


# License

## echOmods 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

## Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018


[](@autogenerated - invisible comment)