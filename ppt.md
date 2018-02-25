% Habits
% John Doe
% March 22, 2005
 

# What do we do?
 
## What are the arduino-like ultrasound module ?

__Creating modules to facilitate ultrasound hacking__ : the principles of the echOmods is to enable a full chain of ultrasound image processing and hardware control.

We have chosen to use a module approach to make sure that each key component inside ultrasound image processing can easily be replaced and compared with another module, while providing logical _logic blocks_ and corresponding interfaces for these modules to communicate. There's a module for [high-voltage pulsing](/tobo/), one for the [transducer](/retroATL3/), one for the [analog processing](/goblin/), one for [data acquisiton](/retired/toadkiller/), ... and many more!

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
* Using a dual ADC raspberry extension for 20Msps+ DAQ ([elmo](/elmo/)) -- get for _45$_ (Where? OSHPark, MacroFab)
* Goblin: a TGC-Envelop-ADC module ([goblin](/goblin/)) -- get for _149$_ (Where? Custom made, get the [Gerbers](/goblin/source/), or [buy it preassembled on Tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/), or contact @kelu124)
* Tobo: the HV-pulser ([tobo](/tobo/)) -- get for _120$_ (Where? Custom made, get the [Gerbers](/tobo/source/), [buy it preassembled on tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/) or contact @kelu124)


_Total cost of the set: 404$_

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
 
# Graphing the modules
 

# The modules organization 

![Graph](/include/sets/basic.png) 

 
# Table Docs
# A recap of our modules 


| ThumbnailImage | Name | In | Out |
|------|-------|----|------|
|<img src='https://github.com/kelu124/echomods/blob/master/wirephantom/viewme.png' align='center' width='150'>|**[wirephantom](/wirephantom/Readme.md)**: Just a phantom for calibrated signals|<ul><li>na</li></ul>|<ul><li>na</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/tobo/viewme.png' align='center' width='150'>|**[tobo](/tobo/Readme.md)**: The aim of this echOmod is to get the HV Pulse done.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-9_Pon</li><li>ITF-10_Poff</li><li>ITF-19_3.3V</li><li>ITF-mET_Transducer</li></ul>|<ul><li>ITF-18_Raw</li><li>ITF-mET_SMA</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/elmo/viewme.png' align='center' width='150'>|**[elmo](/elmo/Readme.md)**: The aim of this module is to achieve 10Msps, ideally 20Msps, at 9bits or more. Inspired from the Bomanz project as well, which tried several high-speed ADCs setup for Raspberry Pi.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-19_3.3V</li><li>ITF-12_RPIn</li></ul>|<ul><li>Signal Digitalized</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/alt.tbo/viewme.png' align='center' width='150'>|**[alt.tbo](/alt.tbo/Readme.md)**: The aim of this echOmod is to get the HV Pulse done.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-9_Pon</li><li>ITF-10_Poff</li><li>ITF-19_3.3V</li><li>ITF-mET_Transducer</li></ul>|<ul><li>ITF-18_Raw</li><li>ITF-mET_SMA</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/cletus/viewme.png' align='center' width='150'>|**[cletus](/cletus/Readme.md)**: The aim of this module is to interface the transducer and the servo, aka the physical parts, to the analog part of the modules chain. More to come with the Loftus head.|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-N_cc_motor_pwm</li><li>ITF-S_3_3v</li><li>ITF-mET_Transducer</li><li>ITF-mET_Piezo</li></ul>|<ul><li>ITF-mET_Piezo</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/tomtom/viewme.png' align='center' width='150'>|**[tomtom](/tomtom/Readme.md)**: The aim of this echOmod is to digitalize the signal, and to control the pulser, servo, ...|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-3_ENV</li><li>ITF-15_GPIO21</li></ul>|<ul><li>ITF-16_POn3</li><li>ITF-16_POn3</li><li>ITF-17_POff3</li><li>ITF-14_PWM</li><li>Wifi</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/doj/viewme.png' align='center' width='150'>|**[doj](/doj/Readme.md)**: Getting a motherboard: that's fitting all the modules in an easy way, with an easy access to all tracks. See this for the Kicad files.|||
|<img src='https://github.com/kelu124/echomods/blob/master/matty/viewme.png' align='center' width='150'>|**[matty](/matty/Readme.md)**: The aim is to summarize all modules in a all-inclusive board. Fast ADC, good load of memory, good SNR.. the not-so-DIY module, as it comes already assembled with nothing to do =)|||
|<img src='https://github.com/kelu124/echomods/blob/master/croaker/viewme.png' align='center' width='150'>|**[croaker](/croaker/Readme.md)**: The aim of this echOmod is to receive the signal and process it, then stream it over wifi. |<ul><li>ITF-3_ENV</li><li>ITF-10_Poff</li><li>ITF-9_Pon</li><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li></ul>|<ul><li>ITF-19_3.3V</li><li>ITF-mED-TFT-Screen</li><li>ITF-mED-OLED-Screen</li><li>ITF-mEC-WiFi-UDP-Stream</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/retroATL3/viewme.png' align='center' width='150'>|**[retroATL3](/retroATL3/Readme.md)**: The aim of this echOmod is to get the mechanical movement of the piezos. Salvaged from a former ATL3.|<ul><li>ITF-A_gnd</li><li>ITF-F_12V</li><li>ITF-N_cc_motor_pwm</li><li>ITF-mET_Transducer</li><li>Motor</li><li>Tri-Piezo Head</li></ul>|<ul><li>Motor</li><li>ITF-mET_Transducer</li><li>Tri-Piezo Head</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/goblin/viewme.png' align='center' width='150'>|**[goblin](/goblin/Readme.md)**: The aim of this echOmod is to get the signal coming back from a transducer, and to deliver the signal, analogically processed, with all steps accessible to hackers. |<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-7_GAIN</li><li>ITF-4_RawSig</li><li>ITF-3_ENV</li><li>ITF-18_Raw</li><li>ITF-mET_SMA</li></ul>|<ul><li>ITF-4_RawSig</li><li>ITF-3_ENV_signal_envelope</li><li>ITF-mEG_SPI</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/loftus/viewme.png' align='center' width='150'>|**[loftus](/loftus/Readme.md)**: The aim of this module is to recycle a previous head|<ul><li>ITF-A_gnd</li><li>ITF-B_5v</li><li>ITF-N_cc_motor_pwm</li><li>ITF-S_3_3v</li><li>ITF-mET_Transducer</li><li>ITF-mET_Piezo</li></ul>|<ul><li>ITF-mET_Piezo</li><li>ITF-mET_Transducer</li></ul>|
|<img src='https://github.com/kelu124/echomods/blob/master/silent/viewme.png' align='center' width='150'>|**[silent](/silent/Readme.md)**: The aim of this echOmod is to simulate a raw signal that would come from the piezo and analog chain.|<ul><li>ITF-1_GND</li><li>ITF-2_VDD_5V</li><li>ITF-17_POff3</li></ul>|<ul><li>ITF-18_Raw</li></ul>|

# Progress
 
# Progress on building the modules 


## Module-wise 


Note that the 'BONUS!' represents something that _could_ be done, and does not count as a strict TODO.


| Name of module | ToDo | Done |  Progress |
|------|-------|----|-----|
|wirephantom|<ul><li>None</li></ul>|<ul><li>All</li></ul>|50% |
|tobo||<ul><li>Writing specs </li><li>HV7360 has been updated</li><li>Sending microcircuits to Edgeflex</li><li>Agreeing on the strips/tracks </li><li>Defining the ICs to use to pulse</li><li>Getting schematics</li><li>Publishing schematics</li><li>Receive the module</li><li>Test it with different transducers</li><li>Publish the sources in KiCAD</li></ul>|100% |
|elmo||<ul><li>Getting a board an soldering some ADCs</li><li>Understand GPIO <a href="/elmo/data/20170609-NewADC.ipynb">mem mapping</a></li><li>Get raw data with <a href="/elmo/data/arduinoffset/20170612-ArduinoFFTed.ipynb">offset vref/2</a></li><li>Tests with a single ADC at 11Msps</li></ul>|100% |
|alt.tbo|<ul><li>Check a design w/ <a href="/alt.tbo/images/md1811_ref.jpg">this idea</a> which is similar to <a href="/alt.tbo/images/md1210_ref_2.jpg">this other idea</a> or <a href="/alt.tbo/images/md1210_ref.jpg">this last idea</a>.</li></ul>|<ul><li>Preliminary tests</li></ul>|50% |
|cletus|<ul><li>Remove the jitter (see image in Rdme)</li><li>Include <a href="/cletus/2017-06-08_FindingSuppliers.md">notes</a></li></ul>|<ul><li>Get a 3.5MHz piezo</li></ul>|33% |
|tomtom|<ul><li>Save images as DICOMs</li></ul>|<ul><li>Mapping the pins shared between PWM, pHAT and tracks</li><li>Developping a CA3306E version of <a href="https://github.com/kelu124/bomanz/blob/master/CA3306E/20170422-FirstAcqs.ipynb">the 10Msps ADC pHAT</a> for testing.</li><li>Testing the limits of ADC acquisition (speed / bits)</li><li>Understand why some GPIOs do not have lower values at 0..</li><li>Set pins to down <a href="https://raspberrypi.stackexchange.com/questions/4664/setting-gpio-value-on-boot">on boot</a></li><li>Dev a version of the <a href="https://github.com/kelu124/bomanz/blob/master/ADC08200/">ADC08200</a></li><li>Create a kernel module</li><li><em>(Still to be explored)</em> MixedGadget =&gt; <a href="http://isticktoit.net/?p=1383">Storage + ethernet</a> or <a href="https://gist.github.com/gbaman/50b6cca61dd1c3f88f41">this</a> or <a href="https://learn.adafruit.com/turning-your-raspberry-pi-zero-into-a-usb-gadget/overview">that</a>.</li><li>Test the <a href="http://www.toptechboy.com/raspberry-pi/raspberry-pi-lesson-28-controlling-a-servo-on-raspberry-pi-with-python/">PWM</a></li></ul>|90% |
|doj||<ul><li><a href="https://oshpark.com/shared_projects/2taE6p4M">PCB on OSHPark</a></li><li>Having the list of strips accessible</li><li>Design</li><li>Change the viewme</li><li>Assemble it</li><li>Test it</li><li>Adapt power supply from v2 - smaller board footprint</li><li>Add a level shifter been Pon 3.3 and 5 and Poff 3.3 and 5</li><li>A bit more space around the Pi0/PiW headers</li><li>Proper silkscreening around the Pi0 headers (they are reversed)</li><li>Jumper for the ADC in.. and selector (enveloppe and amplified signal) (either to Feather or to ADC .. and dedicated pin on Rpi)</li><li>SPI from RPi to Oled... or SPI to screen (to be checked in both case) .. or both kept, there are two SPI</li></ul>|100% |
|matty|<ul><li>See the <a href="/matty/nextsteps.md">next steps</a></li><li>Having it work with a <a href="/retroATL3/">retroATL3</a></li></ul>|<ul><li>Getting some signals!</li></ul>|33% |
|croaker|<ul><li>Replace the work done by <a href="/retired/oneeye/">OneEye</a> by <a href="/croaker/">Croaker</a> - that is, pulse control.</li><li>Get better total ADC speed with an iterleaved move</li><li>Develop a Cletus+Croaker way of working with a gyroscope+accelerometer.</li><li>Have Croaker generate its own AP</li></ul>|<ul><li>Choose the platform (<a href="/retired/toadkiller/">BBB</a>, RPi0, <a href="/croaker/">STM32</a>, ... ?) : that'll be a <code>Feather WICED</code> for this iteration of Croaker</li><li>Getting some images</li><li>Getting images onto a screen</li><li>Getting good resolution images -- see the <a href="/croaker/data/20161217/20161217-TestingArduinoAndPhantom.md">breadboard phantom</a></li></ul>|50% |
|retroATL3|<ul><li>Replace the work done by <a href="/retired/oneeye/">OneEye</a> by <a href="/croaker/">Croaker</a> - that is, pulse control.</li><li>Get better total ADC speed with an iterleaved move</li><li>Develop a Cletus+Croaker way of working with a gyroscope+accelerometer.</li><li>Have Croaker generate its own AP</li></ul>|<ul><li><em>BONUS!</em> Get RealTime acquisition</li><li>Finding the pins mapping</li><li>Acquire and build ultrasound pictures =)</li><li>Motor in action</li><li>Refill Oil</li><li>Test echoes</li><li><a href="https://hackaday.io/project/9281-murgen-open-source-ultrasound-imaging/log/42113-testing-murgen-with-a-market-probe">Make and insert a video: there</a></li></ul>|63% |
|goblin|<ul><li>Test Goblin v2</li></ul>|<ul><li>Check the power consumption</li><li><a href="/retired/toadkiller/data/test_enveloppe/">Testing the in and out signals</a> of the board with the prudaq.</li><li>Specs to write</li><li>Agreeing on the strips </li><li>Check if 5V and 3.3V are stable</li><li>Defining the ICs to use</li><li>Getting schematics</li><li>Send microcircuits to Edgeflex</li><li>Receive the module</li><li>Publish the sources in KiCAD (@Sofian maybe?)</li><li>CANCELLED - Test it with the <a href="/retired/hannin/">EMW3165</a></li><li>Plug it to a <a href="/elmo/">RPi0</a> or <a href="/retired/toadkiller/">BBB</a> or <a href="/croaker/">STM32</a></li><li>Connect the ADC to a RPi0</li></ul>|92% |
|loftus|<ul><li>TBD</li></ul>|<ul><li>Identifying a supplier</li></ul>|50% |
|silent||<ul><li>Feather: <a href="/silent/software/featherWICED/SignalGenerator.ino">work with an interrupt</a></li><li>Write code for feather WICED</li><li>Publish this code</li><li>Remove Signal Bias</li><li>Validated with a Feather WICED (<a href="/silent/software/featherWICED/SimpleSignalGenerator.ino">code</a>).</li><li>Feather: remove the average value before inputing in Goblin</li><li><a href="/silent/2016-08-09-SilentPlusTobo.md">Check output with Goblin</a></li></ul>|100% |


