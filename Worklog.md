# The EchoModules worklogs [](@description Full worklog of the modules)

## Next steps from [Murgen](http://github.com/kelu124/murgen-dev-kit/) 

1. Playing with the design and fab the modules: 3 to go in CMS (HV/TGC/MD, enveloppe detection, SPI ADC) and 2 in stripboard mode (alim, based on the breadboard 3.3V and 5V, as well as the controler, maybe an arduino nano at first) - and start the github repo / [echOmods](https://hackaday.io/project/10899-echomods) hackaday pages as well. Work on this with Sofian and Vlad. See also the [echOmods repo](https://github.com/kelu124/echomods/).
2. Playing with an electronic emulator of the transducer - as well as an electronic model. Work on this with a partner/supplier. [Actually produced in the end with a uC - Silent](/silent/).
3. Play with a ultrasound durable fantom. Work on this with **staticdet5** (commnotes_ent on HAD). Started a [project with Virginie and Static on HAD.io](https://hackaday.io/project/11478-open-source-ultrasound-phantoms).
4. Play with the BeagleBone PRUs. Work on this with Vanderbilt.
5. Playing with some intelligent uC of FPGA. uC has my preference at first for ease of use. WifiMCU seems fun (has a 8$ STM32F411CE - 100MHz, 2.4Msps ADC, FPU, DSP instructions and WiFi to stream!) or the [Feather Wiced](https://www.adafruit.com/product/3056) (arduino IDE compatible, based on a 34$ STM32F205 ARM Cortex M3 processor running at 120MHz. Project codename would be [Croaker](https://github.com/kelu124/echomods/croaker), not created yet. Who's volunteering?

## Brief

Mostly, the thing would be to separate the
[Murgen](http://github.com/kelu124/murgen-dev-kit/) PCB in 4 different
modules (similar to the arduino trinket pro for example), so to have
them ready to be used on a stripboard which would have already headers.

The strips would have the 19 tracks as on the attached picture below.

There would be 2 modules :

-   HV + pulser + md0100
-   TGC + enveloppe + SPI ADC

(Two other modules, Alim, and controler, will be stripboard based)

Given that the boards would be separated, would it make sense to try
to \*\*design the PCBs to have only 2 layers PCB\*\* ? The width of the
PCBs would not really matter, only to be sure they'd fit on a strip
board. It would be interesting to have a form factor of the modules PCB
comparable to one trinket pro =)

### Adjusting the specs for a research module

* 10ms between lines - 64 lines gives 640ms / image)
* 200us at 2Msps is 400 points is 5600 bits is 700 bytes
* 5600 bits per 10ms is 560,000 bits/s is 70kbytes/s.. should be OK with ESP8266 ;)

### Details about the modules

1\. HV+Pulser+MD0100 don't change. The module will need to have a SMA
connector (same as on existing board).

2\. VGA + enveloppe + ADC

* VGA+enveloppe detector can remain the same. I just need to remove the
filter that is between t	he TestPoints4 and 5 and the transformer. The
module output is the output of the ADL5511.
* SPI can be replaced, this one was an overkill. 10Msps is too much, so
instead a 2 or 3 Msps at 12 or 14 bits in SPI could be used on the ADC
module.

### Controls

The "controls" listed would be a potentiometer for the HV (as was done
for murgen), a potentiometer for the TGC Gain (not an ADC, bit of
overkill, rather a jumper to allow one to select the gain from either
the track or a potentiometer which would feed in from 0 to 1V).

### ADC details

The ADC can be as low as 12bits 2Msps when we're talking about envelope
detection (what about MAX11105?). (btw, the signal output by it is
offset by around 1.32V) on top of which we have 1.25V of signal. For the
sake of the experiment, I would add another ADC board, clone of the
11105, with a MAX11103, to comparatively test both.

### The motherboard

What is expected is to break down logic blocks into modules that could be put on a motherboard ( a 2.54mm stripboard), 19 tracks high.

## Todo

### Still to do


* TODO: Module: ESP8266+ADC
* TODO: Design Croaker and Silent
* TODO: Contact Frederic Patat
* TODO: Play with the pulser
* TODO: Schemas de fonctionnement des modules
* TODO: Hack RPi0 CSI (Camera)
* TODO: Voir PCMLab (Jussieu)
* TODO: Finance

### Ongoing

* Ongoing: Document the motherboard -- thanks to Prof Charles
* TODO: Goblin - 2Msps SPI ADC -- Play with BBB and RPi0 SPI

### Done

* Done: Mech-athon - Coming soon
* Done: Contact Edgeflex
* Done: Add status to track progress of the works
* Done: Jan
* Done: schemas a taper, puis processing dans le makedoc.py
* Done: A draft for the analog pulser, [Tobo](/tobo/) -- April 20th 2016
* Done: [Automating Documentation](https://github.com/kelu124/echomods/blob/master/makedoc.py)
* Done: Cahier des charges modules - See __Adjusting the specs for a research module__ on this log
* Done: Silkscreening with the murgen-series logo =)
* Cancelled: Module: Detection (Merged in Goblin)
* Cancelled: Imprimer une tof a afficher

## Description

Board 1, aka [Tobo](/tobo/Readme.md):

* The HV part of murgen is kept. The pulser of the first board is trigged by Pulse On (stripe 9) and shut by Pulse Off (stripe 10) (coming from the stripes). The pulser alimentation is fed through the RECOM component, with a potentiometer to select the HV level.
* Signal is sent to a sideway SMA connector. 
* Signal is protected by a MD0100 + LC.
* Low voltage signal is sent out of the board through a SMA connector.

Board 2, aka [Goblin](/goblin/Readme.md):

* Low amplitude signal comes from the SMA connector.
* It is fed through to the TGC.
* The Gain of the TGC can come either from the Analog Gain Ramp stripe (stripe 7) or from a potentiometer which gives it 0 to 1V - selection through a jumper.
* The filter part of the murgen board is removed (between TP2/3 and TP5/6)
* Raw signal is either send to stripe 3 or sent to the ADL5511, selection through a jumper.
* If output of the TGC goes to the ADL5511, it is then sent to the stripe 5 or to the 2/3Msps ADC (SPI).

Two other modules are being worked on, namely:

* controler
* alimentation


Worklog for murgen -- Starting Nov 24th 2015
-------


#### 2015-11-24

* TLDR
  * CapTech Workshop. Was great!
  * Acted upon a split between a FPGA long-term approach, and a
 non-FPGA one. I remembered those good old times when this was
 a possibility.
  * Damn it. What if I could dig into this? Not µC, rather an
 extension for an existing computer.. or mini computer.
  * Saw some ideas on the Arduino's side. Separate ADC.
* Resources
  * [Is Pi powerful enough for an oscilloscope
 project?](http://raspberrypi.stackexchange.com/questions/4129/is-pi-powerful-enough-for-an-oscilloscope-project)
  * [Raspberry Pi as an Oscilloscope @ 10
 MSPS](https://digibird1.wordpress.com/raspberry-pi-as-an-oscilloscope-10-msps/)

#### 2015-11-27

* http://paul.sullivan.za.org/raspberry-pi-oscilloscope/EE-October-1991/
    (pics below)
* MagPi : ISSUE 24 - JUN 2014 (to print !!)
* Follow up
  * Discussion with
 4365D2F5E4EB59B6BAD0FC746506A6EADEC28BC264BDD78BC041D3417B0766F4
  * Discussion with
 8620B4ADDED83F8C1E5EBC0F401D12BC327735D7A314336D24C3F3D88A16E3ED

#### 2015-11-28

* Tamagotchi hive in a probe?
* Thinking about the smile on the silkscreen. EO+OH+PI+Pirate?

#### 2015-12-01

*  Thinking of deadlines
*  PHH/BM discussions

	*  Rather be going onto SPI : QuadSPI ?
	*  LTC5507ES6 to filter ? A rajouter!
	*  Better ADC at LTC2315-12
	*  DAC: a simple DAC i2c

*  Pro/Cons of a shield compared to FPGA/microcontrolleur


#### 2015-12-02

* Rasberry Pirn
  * Raspberry Pi Zero Headless Setup :
 http://davidmaitland.me/2015/12/raspberry-pi-zero-headless-setup/
  * Installing Operating System Images on Linux
 https://www.raspberrypi.org/documentation/installation/installing-images/linux.md
* BBB
  * How to use it?
    *  http://www.element14.com/community/community/designcenter/single-board-computers/next-gen_beaglebone//blog/2013/05/22/bbb--working-with-the-pru-icssprussv2
    *  For low-speed comms, conventional I2C or similar protocols can be used, and there is no need to use a PRU. For high-speed comms the PRU may be extremely useful because it can service the hardware with no interruptions due to Linux context switching, and no overhead is experienced by the main ARM processor. Here are some examples that should be feasible; basically quite a few possibilities, such as
   *  * interfacing to a fast ADC (e.g. analog capture)* * ,
  * https://theembeddedkitchen.net/beaglelogic-building-a-logic-analyzer-with-the-prus-part-1/449
 BBB is a 100MHz logic analyzer on a BeagleBoneBlack
  * Demo over the http://beaglelogic.github.io/webapp/
  * http://r.git.net/beagleboard/2013-10/msg00204.html
    *  Can the PRU be used to interface the Beaglebone to external ADC? I need to capture 500 micro-seconds of data at a 5 MHz rate.
    *  -&gt; * It depends on the interface to the ADC. There is a parallel capture interface that will easily run that fast, and you may be able to use the bit-shift interface to do serial or something like SPI if the PRU's capability lines up with what your ADC wants to see.* 
  * http://www.element14.com/community/community/designcenter/single-board-computers/next-gen_beaglebone//blog/2013/08/04/bbb--high-speed-data-acquisition-and-web-based-ui
    * In its current state, it grabs analog data from an ADC, and dumps it into memory on the BBB, ready to be displayed or further processed. It could be used for gathering analog information from sensors, CCDs or other data acquisition use-cases. To be reasonably useful, the desire was for it to support 20Mbytes/sec of data or more. It does achieve this, but it is for further study to find higher speed methods.* 
    * This is not such a bad idea, because in future the ADC could be swapped out to a (say) 10-bit ADC with no code change on the PRU.* 
    * Once the data has been captured (2000 samples in this example), the command byte is acknowledged, so that the Linux hosted application can know that the PRU has completed. The PRU now sits and waits for a new instruction from the Linux hosted application.* *  -&gt; works for us - fixed depth = fixed \# of samples
  * Buffer to be used : detailed at
 http://www.element14.com/community/community/designcenter/single-board-computers/next-gen_beaglebone//blog/2013/08/04/bbb--high-speed-data-acquisition-and-web-based-ui
    *  ''These were extremely important for two reasons. One reason is that the pins to the BBB that I wished to use need to be isolated during power-up, because they are used for selecting the boot method. If there was any unusual level on the pins upon power-up then the BBB will not boot from the eMMC. So, a tri-state buffer is needed. The other reason is that there is a fair bit of capacitance and it is highly likely that the ADC may not be able to directly drive the pins at high speed. I actually came across this problem while trying to connect a camera to the BBB. I struggled for days without realising that the camera could not support the load. So, the buffers are likely to be essential for most designs using the pins that were selected. I used a 74LVC244A device as a buffer. Note that the clock also needs a buffer, unless significant jitter is acceptable. No tri-state is required here, so I used a MC74VHC1GT50.

''

#### 2015-12-03

*  New ADCs in mind
 ADS803E
 LTC2315-12 
*  Orange Pi Plus 2 : A nasty little thing
*  BBB as always coming mostly from element14
 Some limits - not exploiting all ? http://exploringbeaglebone.com/chapter13/#The_ADS7883_Single-Channel_12-bit_ADC_1MSps_max
 SPI speed with BBB : http://fr.mathworks.com/help/supportpkg/beagleboneio/ug/use-the-beaglebone-black-spi-interface-to-connect-to-a-device.html (up to 32MHz) - which is
*  16 bits : is it possible to set all 16 pins on pru0 as inputs? I saw you mentioned something about disabling the microSD functionality on the BB to get access to all 16 pins, but I wasn't exactly sure how. -- heartofasquid
 I thought the PRUs had a 16bit parallel capture mode or are all the pins not available on the BBB? (need to consult the docs) section 4.5.2.2.3.2 of the tech ref spruh73c.pdf One thought I had was to use both PRUs to capture alternate bytes/words but that was just a thought, again are all the pins available?
 I'd made a mistake, it looks like all of PRU0's GPI pins may be available, if we are happy to lose the microSD (no big loss - there are other ways to get data in/out of the BBB). So, we can theoretically get high-res captures up to about 15bits, if we need 1 pin for the clock.


#### 2015-12-04

* [BBB and 5Msps 12bit : a SO
    question](https://electronics.stackexchange.com/questions/204317/what-is-the-best-setup-for-a-5msps-12bit-adc-to-beaglebone-black-setup)
* Registered at element14.com =)

#### 2015-12-5th

* Graphing all elements @GaiteLyrique
* 5 to 100 DC
  * http://www.researchgate.net/post/Does_someone_know_an_simple_electronic_design_that_takes_small_PCB_area_producing_a_stable_100_DC_voltage_from_a_power_supply_of_5V2
  * https://www.maximintegrated.com/en/app-notes/index.mvp/id/1751



* Call/Chat Emmanuel - electronic board - 2 months is what he'd expect
* Discussion S - review of scope / finetuning signals
  * Necessity at 100V to separate HV to avoid interferences / noise
  * Remark: using PRUs, we can go up to 50MHz (at least) from the
 ADC
* Validation of parallel ADC
* Mapping the Shield knowledge graph
* Followup MIC

#### 2015-12-06

*  Reflexions on documentation coming from this presentation on OSH
*  5Msps - Parallel - PRU up to 12 bits - can go further than 5Msps (SOA)
*  Buffer has to come (no, not the buffer app - real world buffer)
*  Thinking as well on architecture  *   Motor + transducer + top in the probe  *   Board + BBB (Node.js still..)  *   Output (if necessary)

#### 2015-12-07

*  Busy business day
*  Usual monday meeting  *   awesome progress on mech part. Seems robust, small, ...  *   need to follow the power usage of POLULU ^^
*  What about a webcam video format?  *   WebRTC - awesome stuff at https://rtc.io/ for nodejs + webrtc

#### 2015-12-08

* http://www.theopensourceway.org/book/The_Open_Source_Way-How_to_tell_if_a_FLOSS_project_is_doomed_to_FAIL.html
    : nice doc to failproof a FLOSS project.
* FPGA team
  * FPGA vs µC : discussion ongoing with F&V - seems going
 towards RP. Sane, pragmatic approach. If the RP is cracked, that
 could unlock many things.
  * Simulations to come from MIC
* Another supplier
  * seeedstudio.com(reco by F&V)
  * See also http://pcbshopper.com/
* PCBA abroad :
  * [myropcb](http://www.myropcb.com/services-capabilities/pcba-services/)
  * [nortechsys](http://www.nortechsys.com/nortech-advantagepcba-protyping-short-run-production/)
  * [SeeedStudio](https://www.seeedstudio.com/service/index.php?r=upcb)
 only north america
* PCBA in france:
  * [Quad Ind](http://fr.quad-ind.com/assemblage-pcb/)
  * [PCB-Pool](https://www.pcb-pool.com/ppfr/info_pcb_assembling.html)
* [Fun on gerber and silk
    screens](http://makezine.com/projects/make-36-boards/make-your-own-dmn-board-part-3-silkscreen-and-gerbers/)

#### 2015-12-09

* Following some [design thinking
    classes](https://www.coursera.org/learn/design-thinking-innovation/home/welcome)
    for the sake of soft design & fun

#### 2015-12-11

* Update the _Culture_  repertory in our drive :p
* Piezo    suppliers on     their way
* Mapping the DITSO resources - update
* Apero !

#### 2015-12-12

* GP1A57HRJ00F // photo interrupter
* Server for again 3 days...

#### 2015-12-14

* Holocracy progress
* Comments from S: problems with HV system

#### 2015-12-15

*  First elements from A - first draft (pdf file).

#### 2015-12-16

*  Another feedback from S : small, interesting DC/DC power convertors from RECOM. Excellent idea.
*  Some great GIT cheatsheet - https://gist.github.com/mplewis/a7563c7cb589048a071b
*  The sysadmin apprentice : http://www.commitstrip.com/fr/2015/11/18/the-sysadmins-apprentice/

#### 2015-12-19

* S has started, on it

#### 2015-12-20

* Adafruit fun - display and printing ?
  * Adafruit 1.8" Color TFT Shield w/microSD and Joystick:
 https://www.adafruit.com/products/802
  * WIFI feather : https://www.adafruit.com/products/2821
  * touchscreen : https://www.adafruit.com/products/1651
* Thermal printing : https://www.adafruit.com/products/2753 but no
    level of grays

#### 2015-12-22

* Progress A / S
* Caracterisation du piezo :
  * http://www.biosono.com/PrmtLgd/PrmtLgd.php?id=TrnsRlc
  * http://www.brl.uiuc.edu/Downloads/bigelow/APPENDIX%20C.PDF 
  * http://www.vtvt.ece.vt.edu/research/papers/08sas.pdf  

#### 2015-12-27

* Some PCB Assembly recommendation
  * https://groups.google.com/forum/#!topic/tcmaker/rXdZSrWvRTU
  * https://forum.sparkfun.com/viewtopic.php?f=20&t=36339
* OSH Park, purple board, doesn't do assembly
* https://macrofab.com/ -- GO FROM PROTOTYPE TO MARKET FASTER THAN
    EVER BEFORE -- excellent review

#### 2015-12-28

* Back from festive period ! But no slack:
  * First iteration of A  -- buffers as
 74AC541MTC ?
  * Schematics and BOMs from S
  * Cacophony everywhere
* https://www.youtube.com/watch?v=aPVLyB0Yc6I Eating bears
* LCD at http://www.espruino.com/PCD8544
* Autre display / TFT :
    https://learn.adafruit.com/1-8-tft-display .. et une micro SD
    integree =)
* BBB headers : https://www.adafruit.com/products/706 (Stacking
    Header Set for Beagle Bone Capes (2x23) @5\$)

#### 2015-12-29 Some ada news

##### News

* vieux displays: https://www.adafruit.com/categories/99
* https://www.adafruit.com/product/358
* https://www.adafruit.com/products/2478 : 240by 320 screen, touch,
    sd
  * The display can be used in two modes: 8 bit or SPI. For the
 fisrt you'll need 12 lines total. Second mode requires only 5
 pins total but is slower than first.
  * In addition, 4 pins are required for the touch screen (2
 digital, 2 analog)
  * Tuto :
 https://learn.adafruit.com/adafruit-2-4-color-tft-touchscreen-breakout
* https://www.adafruit.com/products/1480 : 320 by 240 screen, 4-wire
    SPI to communicate and has its own pixel-addressable frame buffer

* * Seems like the BBB SPI communication rate are around 0.1s to draw the
image over SPI.. may be a tad slaw to only display an image* * 

##### Bots

* Onboarding bot for Slack at
    https://18f.gsa.gov/2015/12/15/how-bot-named-dolores-landingham-transformed-18fs-onboarding/
    (in ruby)

#### 2015-12-30

* Did automatic backup for the wiki, for the migration - yeahhh
* Smartassthoughts
  * _The absence of deal-breaking flaws is more important than the presence of any extras._  You don’t need anything special  to succeed. You just need to do the essentials properly.
  * Power is like being a lady… if you have to tell people you are, you aren’t. -- MT
* FTS
* Don't forget spider jerusalem's example - bards, journalists, and a
    merry cacophonic 2016

#### 2016-01-06

* Trial on PCBCart
* Render of the Murgen 1.0 board 

![](https://raw.githubusercontent.com/kelu124/murgen-dev-kit/master/worklog/Images/murgen%201.0%201.png)

#### 2016-01-08

* Small adjustments from the questions raised by PCBCart

#### 2016-01-11

* Completed the S project -- CLOSED ;)
* The A project is ongoing

#### 2016-01-12

* Kelu124 back in France

#### 2016-01-15

* Boards:
  * Confirmation that Seeedstudio does not ship out of north america
  * Getting other options and quotes from Advanced Circuits,
 Macrofab (awesome interface), PCB Pool.
* Need for a filter to get be sure , there's a low frequency component
    that remains: to remove- and to center around 0V ?
 
Let's cut it to 500kHz ?

* For headers, we have
  * 12 input pins on P8 for PRU1 and 1 input pin for PRU1 on P9,
 these have been assigned for 12bitADC+Clock and the rest,
  * SPI for DAC,
  * Buffer enable and motor control have been assigned to PRU0.
* For the controls in prototyping:
  * SW1 controls the gain range for TGC
  * SW2 controls the input range of the ADC,
* Updating the blog as well, integration of disqus

#### 2016-01-16

* disqus working
* creating something on makake.. but seems bugged at the moment
* list of components on the blog
* discussions with edgeflex (thanks flylabs!) and macrofab (fun, and
    willing to test a 4 layer project in beta - only working in 2 layers
    so far)
* work with S to integrate a high pass filter (1MHz+) following the
    echo on Jerome's hand
* Follow up with Charles
  * working on the RP with a student
  * exploring collaborations

#### 2016-01-18 Testing stuff

* Call with Edgeflex
* Breakout boards for SMDs :
  * https://www.adafruit.com/products/1210 /
 https://www.adafruit.com/products/1206 / ...
  * https://www.adafruit.com/products/1281 to test
* Followup with Macrofab
* Producing the XYRS from Altium
* Starting mini board - board #2 -- what name (if not murgen, Tobo ?)
* Order for a ThermalPiPrinter :)

#### 2016-01-19th

* Slight tweak of the budgetting for engineering a probe :) we have
    this
    [GDoc](https://docs.google.com/spreadsheets/d/1HbeRCOVrJFWL29VbagtKip8LvDqiuHKvDMe9bzmxfmM)


#### 2016-01-20

* What about having a µC ( PIC24FJ128GC010 ?) right after the analog
    part - could be an additional board/cape stacked below (so with
    microcontrolleur and alimentation)
  * it would stream data like a wifi camera
  * receives the ping from the motor controleur
* should we be ordering SMD stuff (flux, fer à souder, soufflerie?) -
    seems an idea
* Creation des modules !

#### 2016-01-21 Site changed

* Changed WP template to something more readable
* Post on HN .. even went 2nd :)
* Awesome work from Farad
 

#### 2016-01-22nd

* Updated the [GitHub
    Readme.md](https://github.com/kelu124/murgen-dev-kit)
    (still lacking a pic, damned!)
* Outputs from the HN post
  * 3700 visitors in less than 20 hours
  * Interesting comments at
 https://news.ycombinator.com/item?id=10944617
  * Interesting contacts (anfractuosity - leptitg )
  * Interesting page :
 https://www.anfractuosity.com/projects/hardware-development-links/
* TODO : get something on reddit ?
* http://finda.photo/#v2 TOF en CC0

#### 2016-01-23 On Oreilly

*  Murgen on http://radar.oreilly.com/2016/01/four-short-links-22-january-2016.html
*  [Prez done here to echopen](http://wiki.echopen.org/index.php/File:160115_-_murgen_prez.pdf)
*  Awesome boost on github and the wiki
*  adding some to the documentation
 @TODO : need to get to read more the TAPR and the full license http://www.tapr.org/TAPR_Open_Hardware_License_v1.0.txt
 @TODO : add CONTRIB.TXT and CHANGES.TXT
*  @TODO : failproof OSH

#### 2016-01-24 Datasheets on Murgen

*  added datasheets
*  @TODO : think about a USB/BT/... output for the board
*  Output ? What format? USB - but I'd rather have wireless ?
 Wi-Fi Direct promises device-to-device transfer speeds of up to 250Mbps

#### 2016-01-25 Tobo gets born

*  Tobo is born ;) as a goodie/bonus for murgen
*  Some resources (thanks Oliv' =) )
 http://www.evilmadscientist.com/2011/improving-open-source-hardware-visual-diffs/
 https://opendesignengine.net/ not working at the moment
*  Repos work
 Github hooks: https://github.com/icefox/git-hooks
 what's http://www.solderpad.com/ worth ?
*  Reading : http://opensourceecology.org/wiki/Open_Design_Engine
*  FUN USB keyboard emulator : http://www.instructables.com/id/USB-PCB-Business-Card/

#### 2016-01-27 Releases on GH

* GitHub signing a release :
  * Howto :
 https://wiki.debian.org/Creating%20signed%20GitHub%20releases
  * Creating a key
 http://ekaia.org/blog/2009/05/10/creating-new-gpgkey/
* Hardware:
  * PCBs have been ordered, 3 days to come.
  * 1st and 2nd boards on their way.

1.  TODO: sign a release as soon as some code is on the way

#### 2016-01-29 Versionning

* http://semver.org/ for semantinc versionning of releases

#### 2016-02-13 Release of Gob

* Lots under way..

* * * Required* * : we need to sit with electronics experts to check how
    Murgen, Tobo, Goblin, and Mira can merge - for a modular board -
    ideally as easy as possible to use!
* IDEA: capelec!
* Need also to push Goblin's files on the repo. Those are made with
    Eagle, not Altium, so a bit less options, but still interesting to
    see how to work with those files =)

#### 2016-02-15 Lit review

Was about time I got some serious litterature review :)

* http://sci-hub.io/10.1109/ULTSYM.2015.0517 for a full fledge
    Smartphone Probe =)
* [Microcontroller USB interfacing with MATLAB GUI for low cost
    medical ultrasound
    scanners](http://www.sciencedirect.com/science/article/pii/S2215098615303220)

Some others

* Integrating hardware and software for the development of
    microcontroller-based systems
* IDEA: Design of a USB based multichannel, low cost data acquisition
    system using PIC microcontroller

#### 2016-02-16 Jatin work

* Waiting for the board ;)
* Awesome work : Development of a wide band front end echo sounder
    receiver circuit by Jatin Sharma ( definitely need to contact him)

#### 2016-02-17 Steppers

* Fun hardware:
  * IDEA : Good stepper: 99\$ /
 https://www.pololu.com/product/2294
  * There are cheaper steppers on Lextronics (+driver)
  * Pololu - LP 6V Motor with 48 CPR Encoder for 25D mm Metal
 Gearmotors (No Gearbox) (https://www.pololu.com/product/2280 )
  * https://www.pololu.com/product/2213 for a small motor
* 3D models of RPi, BBB:
  * BBB: https://www.thingiverse.com/thing:920804
  * RPi: http://www.thingiverse.com/thing:278113

#### 2016-02-18 Reads and random stuff

* Interesting read at
    http://wp.josh.com/2014/03/03/the-mystery-of-the-zombie-ram/ !!
* Discussions on mechanics =)

#### 2016-02-19 Dispalys

* IDEA : display : 128² OLED screen:
    https://www.adafruit.com/products/1431

#### 2016-02-21 Links et al

* Asking feedback from M. Cooke
* http://sci-hub.io/10.1109/ULTSYM.2013.0526 for * Smartphone-based
    Portable Ultrasound Imaging System : A Primary Result*  .. can't
    manage to reach them.
* ebay :
  * Aloka ASU-66 --
 http://www.ebay.fr/itm/Aloka-ASU-66-Ultrasound-Probe-/221690345989?hash=item339dc63a05:g:l~gAAOSwBLlU3n1H
  * Aloka ASU-32H-3.5 Mechanical Probe --
 http://www.ebay.com/itm/Aloka-ASU-32H-3-5-Mechanical-Probe-/190660257677
  * ATL-ADR-5-5-MHz-7-mm-Ultrasound-Transducer-Probe-for-UM-4-7081
  * ATL Access 10PV is a sector array
 ultrasound transducer probe. The ATL Access 10PV is a
 mult-frequency probe with a range of 5.0, 7.5 and 10.0 Mhz. --
 http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2047675.m570.l1313.TR0.TRC0.H0.XATL+Access+10PV.TRS0&_nkw=ATL+Access+10PV&_sacat=0
 \* \* AWESOME\* \* 
  * IDEA : mechanics design idea !
  * Same for ATL Access B10
  * All \* \* ATL Access\* \*  aaahhhh
    *  ATL-Access-C-3-0-MHZ-12-7mm-dia-Ultrasound-Transducer-P-N-101-25909-72-3862
  * GE Kertz Technik S-VNA5-8 Transducer

#### 2016-02-22 FPGA interface

* IDEA : interfacing murgen with a FPGA ? Solution here :
    store.hackaday.com/products/xula2-lx9
* IDEA: doing a probe emulator? Signal generation upon a pulse
    transmitted : a physical emulator for the probe head =)

#### 2016-02-23 passphrase whats thats

* Passphrase.io seems interesting =)

#### 2016-02-24 Wifi and ESP8266

* What can we do with wifi / ESP8266 //
    http://makezine.com/2015/04/01/esp8266-5-microcontroller-wi-fi-now-arduino-compatible/
    ?
* http://darksearch.io/ is fun ?
* No stuff - https://sivers.org/gifts in favor of it =)
* Some news from Amit

#### 2016-02-25 Shorts

* Boards reached: issue with the 5V and GND - shortage

#### 2016-02-26 More about shorts

* Further tests. Shortage still exists.
  * Short is not on the PCB. Appears after solder.
* Found that the RECOM component was designed to be upside down --
    need to resolder it. Luckily it was a via component.
  * This would not be the source of the short anyhow.
  * EF recommends that we burn 10A on the 5V plane to see which
 component would burn.. hmm i'm quite shy to do this :p
* Documenting the issue on github.
* Sending back boards to EF.

#### 2016-02-28 Admin reports

* Starting the interim report.

#### 2016-02-29 Short source

* Found the source of the short, ADL5511, 5V and GND inverted...
  * TODO : amend the altium files to correct the ADL5511 and the
 RECOM tracks
* TODO : sampling freq to be documented

#### 2016-03-01 Boards sent back

* Sending back the boards

#### 2016-03-03 Digging into BBB

* Receiving new, corrected boards
* SO qusetions to be tapped into?
  * http://stackoverflow.com/questions/35681099/beaglebone-black-control-gpio-with-pru
  * http://stackoverflow.com/questions/35747954/beaglebone-move-data-from-pru-to-ddr-ram
* Newscastle published something new on their mechanical probe,
    awesome!!
    http://www.ncl.ac.uk/eee/research/groups/coms2ip/ultrasound-imaging.htm

#### 2016-03-04 Tests of the boards

* Testing the board on the morning

#### #### 2016-03-06 Hacking on hackaday

* Posts about the day hacking at
  * https://hackaday.io/project/9281-murgen/log/33275-getting-the-first-echoes
  * https://github.com/kelu124/murgen-dev-kit/blob/master/Session_1.md

#### 2016-03-07 Diverse stuff

* HackerNews : https://news.ycombinator.com/item?id=11232144
  * https://github.com/abhishek-kakkar/BeagleLogic/wiki
  * http://theembeddedkitchen.net/beaglelogic-building-a-logic-analyzer-with-the-prus-part-1/449
  * http://dangerousprototypes.com/docs/Logic_Pirate
  * http://dangerousprototypes.com/docs/Logic_Shrimp_logic_analyzer
* Matos
  * Inverseur : CD74HC4049E
  * Caps 1.27mm
    *  M50-1900005
    *  M50-2020005

#### 2016-03-08 HV7360 how to use it

* GSCholar pour HV7360 (to solve the issues) :
    10.1109/ULTSYM.2015.0140
* HV7361 : Sharma
* TODO
  * Pulser: integrer un schema sur le readme de murgen
  * VPE est a 5V sur notre board - 3.3 en typical. Logique à
 remonter?
  * Add a resistance in parallel of the transducer?
* Damn!! The alimentation voltage was low... because it takes 6.5V to
    12V! Will need to put 9V in through the thermal printer alimentation

#### 2016-03-11 Pulsing and al

* Session 2 : Non-controlled pulsing, inverters, better echoes

#### 2016-03-14 First echoes 

* Starting to get echoes

#### 2016-03-15 Controlled pulsing

* Session 3 : Getting controlled pulsing, but width not controlled

#### 2016-03-18 Charles gets in action

* Sending his board to prof Charles

#### 2016-03-19 Testing with a transducer

* Session 4 & 4b
  * Testing the board with the transducer
  * Testing with the BitScope

#### 2016-03-20 Getting the first images

* Getting the image!
* * Assembling everything
  * Coding in python
  * Thanks bitscope

#### 2016-03-21 Doc again on HAD 

* Doc
  * [Documenting on hackaday](https://hackaday.io/project/9281-murgen): visit, by all means, that's cute and nice!
  * Same documentation on the github repo
* Modular design in on with Benoit ! Let's check with Sofian
* TODO:using SPI on the board
  * plugging a SPI
  * pluging the pulseroff in the buffer part?
* TODO:logo of murgen in vector

#### 2016-03-22 Questions and asso

* PENDINGTODO
  * print and distribute the interim report
  * Organizing elections for the association
    *  Define responsibilities of all
    *  Review of les status de l'association
    *  Review of the reglement interieur
  * Definir who has access to the twitter account
  * Wiki delivery
  * Documentation
  * BM's gerbers, altiums et al
  * Costing of mira
  * License issue on the wiki
  * Budget update - what do we have?
  * Project forecast - where do we go?
  * Restructuration du wiki
  * Page de veille a mettre sur le wiki
  * Creer une page competition
  * Traiter les "objectifs" de la fondation fabre et les finir
  * Gerer les cotisations, faire un appel à cotisation
  * publier les soutenances de F&V?
* Some SO questions:
  * http://stackoverflow.com/questions/35939058/beaglebone-without-dac-from-digital-to-analog-converter
  * http://stackoverflow.com/questions/35910431/getting-beaglebone-prus-to-work-using-pasm
  * http://electronics.stackexchange.com/questions/222661/connecting-large-number-of-i2c-slaves-using-i2c-multiplexers-and-buffers

#### 2016-03-23 Challenge page created

* A challenge page was created 
  * working on modules =) 
  * thinking of the motherboard (contribution of benoit)
  * Enveloppe detection 

#### 2016-03-24 Demoing day

* AOP (high speed 420MHz) THS3001 (Amit)
* TODO:
  * MFab - plan
* Presentations tonight!
* Getting good echoes with the TGC maxed!
* Playing with bitscope / issue from the noise / usb plugin
    got !

#### 2016-03-29 Noise and noise

* order for the usb denoiser
* http://www.st.com/web/en/catalog/mmc/FM141/SC1169/SS1576?sc=stm32f3
    : Getting 5Msps =)
* Farnel price bitscopes
  * http://uk.farnell.com/bitscope/bs05u/oscilloscope-logic-analyzer-2/dp/2432906:
 59£ (73€) (HT?)
  * http://uk.farnell.com/bitscope/bs05p/oscilloscope-adaptor-2ch-20mhz/dp/2455593
 : 89£

#### 2016-03-31 First phantoms 

* Doing some new fantoms
* Receiving the AFORP's guys 

#### 2016-04-01 Pulses with pi 

* Generating pulses with RPi :
    http://codeandlife.com/2012/07/03/benchmarking-raspberry-pi-gpio-speed/
    -- up to 22MHz
* Sofian's back ;)

#### 2016-04-03 Cleaning first images

* Cleaning the acquired images
* 4T scan conversion algo OK and working

#### 2016-04-05

* TODO: creer les liens sur le software/readme     vers les fichiers sources

#### 2016-04-07

* trying some docs at
    https://github.com/kelu124/murgen-dev-kit/blob/master/hardware/doc/murgen-dev-kit.markdown
* starting with the modules..

#### 2016-04-08 Nice reads and al

Nice reading =)

* Basecamp outlines their goals -- which they say have always been the
    same -- on their website:
  * Have fun
  * Do exceptional work
  * Build the best product in the business
  * Experiment
  * Pay attention to the details
  * Treat people right
  * Tell the truth
  * Have a positive impact on the world around us
  * Give back
  * Keep learning.
* "We’re also big believers in business 101. We don’t spend more than
    we earn, we don’t waste money on things that don’t matter, we don’t
    give away everything for free and hope we’ll figure it out before we
    run out of cash. We’re in business to stay in business, and we have
    15 profitable years in a row to back it up."

#### 2016-04-09 Some reads about PRUs

Some reads on PRUs:

* https://hackaday.com/2014/06/22/an-introduction-to-the-beaglebone-pru/
* https://www.embeddedrelated.com/showarticle/603.php
* https://www.embeddedrelated.com/showarticle/586.php
* https://github.com/beagleboard/am335x_pru_package



#### 2016-04-11 Microcontrollers choices

Choice of a uC: "le boulot des microcontrollers, ce qui me gene sur
l'espruino c'est le manque de sortie wifi - si on veut sortir des
donnees en wireless." Deux choix se profilent

* WICED : STM32F205RG 120MHz ARM Cortex M3 MCU : 17 timers et 3 ×
    12-bit, 0.5 μs ADCs with up to 24 channels and up to 6 MSPS in
    triple interleaved mode, 8- to 14-bit parallel camera interface (48
    Mbyte/s max.)
* Le WifiMCU : EMW3165 : M4: STM32F411CE @100MHz, DSP+FPU, 1×12-bit,
    2.4 MSPS A/D converter -- Ce qui me fait peur est un WifiMCU de base
    en LUA, a voir comment repasser sur du plus bas niveau. L'avantage
    par contre c'est qu'il est dispo chez hackspark, et coute 18€ au
    lieu des 35\$ du WICED =)

Remarques : Avec le M3 tu perds les instructions DSP et un FPU optionnel
(cf https://en.wikipedia.org/wiki/ARM_Cortex-M). Par contre je ne sais
pas si c'est correctement exploite, ni si on en a vraiment besoin.

Il y a aussi le Module Particle "Photon"
http://www.lextronic.fr/P37394-module-particle-photon.html (M3 120 MHz
et wifi) ou l'Arietta
http://www.lextronic.fr/P32050-module-microcontrole-arietta-g25.html

* Apparament module ferme


Worklog -- Starting April 5th 2016
-------

#### 2016-04-05 Captech

* Validation of the approach by the Captech

#### 2016-04-08 Tracks of interest

* Validation of tracks of interest

#### 2016-04-15 Tracks

* Validation of tracks and their orders
* Alexandr

#### 2016-04-16 uC

* Studying microcontrolers... See  [microcontrollers](/croaker/notes_uC.md)

#### 2016-04-17 PCB

* Getting a first design for the pulser module
 
![A PCB for PCB](https://raw.githubusercontent.com/kelu124/echomods/master/tobo/viewme.png)

#### 2016-04-18 ADL5511

* Playing a bit with ADL5511 : there's an EREF 
* We use offset remover (suiveur + gain de 2.5), and second op will do amplification, cause envelope output swing is saturated at 1.2-1.3V, We can use 2..2,5 gain to deliver nice and neat 2,6 ..3V input swing for ADC. 

#### 2016-04-20 Modules

##### Previous Generation

* [Murgen](http://github.com/murgen-dev-kit/) : the annalist.. already done, a former project !

##### Current batch

* [Goblin](/goblin/Readme.md): the analog heart, was drafted as well during Murgen. 
* [Tobo](/tobo/Readme.md): the HV/pulser, based on a drafted close to Murgen. 
* [One-Eye](/retired/oneeye/Readme.md): MicroControler - Arduinos
* [Mogaba](/retired/mogaba/Readme.md): Alimentation

Second generation of fun! Learning microcontrolers and advanced simulations

* Croaker: M3/M4 microcontroler 
* Silent : physical emulateur

#### 2016-04-23 Servos

* A stepper based on a servo : https://hackaday.io/project/11224-mechaduino (pour @bivi)

#### 2016-04-24 Maintainers

* Starting to document [Tobo](/tobo/Readme.md)
* Reading __"Maintaining Open Source Projects"__ by Tute Costa : _A project maintainer should feel comfortable shaping the community, promoting the library, keeping good communication with different people, deciding when to release new versions, and prioritizing all these tasks._
* Getting a _TL-MR3040 TP-Link_ for a project PirateBox (an __echObox__ ?)
* __2016 strategy__ being done

#### 2016-04-25 Working IRL and motivation

* http://bengarvey.com/2016/04/24/real-work/ _How many times today did a customer notice something you did?_
* http://www.stubbornella.org/content/2013/02/26/why-i-run-my-business-like-an-open-source-project/
* http://www.atlasobscura.com/articles/the-rise-of-illegal-pirate-libraries?utm_source=facebook.com&utm_medium=atlas-page

_I define Real Work as_

* Work that creates an immediate and positive change in your product/service
* Work that is a direct constraint to the completion of A
* Work you have been uniquely hired to do.

#### 2016-04-26 Motivation

_"I am not a visionary, I'm an engineer," Torvalds says. "I'm perfectly happy with all the people who are walking around and just staring at the clouds ... but I'm looking at the ground, and I want to fix the pothole that's right in front of me before I fall in."_

* http://gggritso.com/human-git-aliases
* http://neo4j.com/blog/technical-documentation-graph/

#### 2016-04-27 Documenting

* Meetings (virginie)
* Doc of modules : https://github.com/kelu124/echomods/
* Preparation of Testing tools for the doc 
* Materials : some awesome resources : Il existe des tables sur les plastiques (http://www.ondacorp.com/images/Plastics.pdf) et autres caoutchoucs (http://www.ondacorp.com/images/Rubbers.pdf ) mais rien de concluant (ref, eau a 1.5MRayl). Il y a des choses comme le Polyurethane, RP-6400, a voir.
* Documentation echomods 
* Premier module OK : (HV, + pulser) sources publiees (same github), fab-ready, quasi documente
* Deuxieme module OK : (TGC, Enveloppe, ADC) sources publiees (same github), fab-ready, documentation en cours

#### 2016-04-30 MBTI and DDS

* Am an INTJ-A ... so what?
* R-2R DDS -- =) MHz DDS with arduino ?
* http://www.tek.com/blog/tutorial-digital-analog-conversion-%E2%80%93-r-2r-dac
* https://hackaday.io/project/9469-misc-arm-projects/log/31489-quick-dirty-dds-for-around-1

#### 2016-04-29 Some stuff

Fun to read

* NT: [The evolutionary argument against reality](https://www.quantamagazine.org/20160421-the-evolutionary-argument-against-reality/).
* [Beard things...](http://www.smbc-comics.com/comics/1461854994-20160428.png)
* Autodocumenting with [makedoc.py](https://github.com/kelu124/echomods/blob/master/makedoc.py) - which updates the [Readme.md](/Readme.md) automatically.

#### 2016-04-30 Graphs

* Adding graphs for all modules with [makedoc.py](https://github.com/kelu124/echomods/blob/master/makedoc.py).
* TODO: https://www.coursera.org/course/fin4devmooc
* TODO: https://www.coursera.org/course/effectiveppp
* TODO: https://www.coursera.org/course/healthcareinnovation

##### 2016-05-01 A bit of work

* Done: TOBO and GOBLIN
* Done: Autodocumentation
* Comment gerer les transducers de Jan?
* Projet Fantomes commence sur HAD : phantoms are starting to appear on [Hackaday](https://hackaday.io/project/11478-open-source-ultrasound-phantoms)

* http://electronics.stackexchange.com/questions/50577/what-ultrasonic-sensoremitter-should-i-use-for-my-medical-ultrasound-project
* http://electronics.stackexchange.com/questions/129582/what-is-the-current-consumed-by-ultrasonic-sensors-transducers-1-2mhz-to-gener?rq=1 for power use

#### 2016-05-02 What

* http://uk.businessinsider.com/interview-with-estonia-cio-taavi-kotka-2016-4


#### 2016-05-03 Max Hold Reset

* http://hackaday.com/2016/04/29/saving-lives-with-open-source-electrocardiography/
__Max-Hold-Reset__
* https://fr.wikipedia.org/wiki/Circuit_d%C3%A9tecteur_d%27enveloppe -> Schema a amplificateur operationnel  (peak detector)
* http://electronics.stackexchange.com/questions/112347/how-to-make-a-peak-detector-circuit
ou peut etre encore mieux :
* http://www.planetanalog.com/author.asp?section_id=396&doc_id=562072
* __Got it !!__ http://www.falstad.com/circuit/e-peak-detect.html
* ESP8266: exploration: SPI-ADC+ESP.overclocked ? : http://stackoverflow.com/questions/37014547/esp8266-and-high-speed-external-adc

#### 2016-05-04 May the fourth

* http://stackoverflow.com/questions/13447538/how-to-avoid-overlapping-nodes-in-graphviz
* http://stackoverflow.com/questions/3967600/how-to-prevent-edges-in-graphviz-to-overlap-each-other

* http://circuit-diagram.hqew.net/Peak-detect-and-hold_17262.html
* http://www.tradeofic.com/Circuit/4885-POSITIVE_PEAK_DETECTOR.html
* PKD01 : trop lent

#### 2016-05-07 Websocket

* https://forum.pjrc.com/threads/34095-Teensy-3-2-ESP8266-12Q-High-Speed-ADC-Websocket

#### 2016-05-10 KiCAD

* https://contextualelectronics.com/gtb-kicad-4-0/ :  10 Part Tutorial On Designing/Building A PCB (Using FOSS)

#### 2016-05-14 Work in Indonesia

* Off to Jakarta =)
* Next prios : Feather and [ESP8266](/croaker/notes_ESP8266.md)

#### 2016-05-23 Transducers

* Restarting work with transducer and boards makers, Jan and Jerome

#### 2016-05-24 RPi

* Bass inspiration : https://www.youtube.com/watch?v=6ZDTelKz4G0
* Working on [Raspberry Pi Zero notes](/croaker/notes_RPi0.md)
* Updated existing notes on [microcontrollers](/croaker/notes_uC.md) and the [ESP8266](/croaker/notes_ESP8266.md)
* Thinking about video / photos port to raspberry (even better than USB transfer, it manages quite high speed ( The two data lanes on the CSI-2 bus provide a theoretical 2 Gbps bandwidth, which approximates to around 5 MP resolution.  ) [here](http://www.petervis.com/Raspberry_PI/Raspberry_Pi_CSI/Raspberry_Pi_CSI_Camera_Module.html)

#### 2016-05-25 Markdown and downs

* http://stackoverflow.com/questions/4823468/comments-in-markdown
* Article on Projects http://teambit.io/blog/all-your-teammates-will-be-gone/
* www.theatlantic.com/health/archive/2014/06/the-dark-knight-of-the-souls/372766/
* http://www.certwise.com/blog/31-ways-know-project-doomed/
* http://gettingreal.37signals.com/toc.php

#### 2016-05-27 Partenariats

* Exploring the partnerships with J&J

#### 2016-05-30 ESP and such

* http://www.esp8266.com/viewtopic.php?t=669&p=3624 HPSI on ESP8266
* Nicolas from V.
* Lancement des PCBs (Jerome)
* Go for Piezos (Jan)

#### 2016-05-31 Hackaday fun

* Redirection de visiteurs de Hackaday vers nos ressources
* Reflexion sur l'EMW3165 -- 8$, ADC à 2.4Msps, WiFi.
* Extraction de la connaissance à partir du BC3: petit souci, le contenu BC3 ne semble pas exportable (pas de dump possible comme avec BC2), et n'a pas d'API d'integration.
* Petit truc sympa, mais pas encore sorti : un SoC pour le RPi : https://hackaday.io/project/11981-rppsoc-system-on-a-chip-for-the-raspberry-pi
* Pas possible de créeer le Wall of Contributors, tjrs ce probleme de reset de mot de passe, aucun email n'arrive.
* TODO: réorganiser les Readme entre echomods et medicotechnical et leur prod automatisée =) 
* [EMW3165](/croaker/notes_EMW3165.md) : "All I see is an under 8 USD STM32F411CE dev board with some wifi gadget" ( http://www.emw3165.com/ ) 

#### 2016-06-02 Some awesome OSH for medical issues

An endoscope pill

* https://hackaday.io/project/10845-tiny-wireless-capsule-camera
* https://github.com/friarbayliff/PillEndoscope

What about XRays?

* http://hackaday.com/2016/05/12/to-see-within-making-medical-x-rays/#more-204360
* https://hackaday.io/project/4740-100-xray-desktop-ct-scanner

And CT Scanners?

* http://hackaday.com/2013/10/23/towards-a-low-cost-desktop-ct-scanner/
* https://hackaday.io/project/5946-openct
* http://www.tricorderproject.org/blog/tag/openct/
* https://github.com/tricorderproject/openct

and MRI ?

* https://hackaday.io/project/5030-low-field-mri

and *CG ?

* See http://mobilecg.hu/
* http://hackaday.com/2016/04/29/saving-lives-with-open-source-electrocardiography/
* http://hackaday.com/2016/03/13/ekg-business-card-warms-our-hearts/


#### 2016-06-04 Learning more on STM32

* [Note d'application des timers par STM](http://www.st.com/web/en/resource/technical/document/application_note/DM00042534.pdf)
* Un très gros bon post sur les timers : un mois de travail d'après l'auteur - [post de blog](http://embedded-lab.com/blog/stm32-timers/)
* Et son [petit frère sur les ADC](http://embedded-lab.com/blog/stm32-digital-analogue-converter-dac/)
* Getting comments on scan conversion at [HAD](https://hackaday.io/project/9281-murgen/log/39271-ultrasound-and-scan-conversion/discussion-58228)


#### 2016-06-06 Weekly monday

* Weekly meeting at the HD
* Prof Charles and Zach start playing with Murgen, so I'm starting to experiment with Jekyll for murgen on the corresponding [Github murgen page](http://kelu124.github.io/murgen-dev-kit/)


#### 2016-06-07 Hall of fame

* Getting a copy of an excellent book : [buy here](http://www.lulu.com/shop/st%C3%A9phane-ribas-and-st%C3%A9phane-ubeda-and-patrick-guillaud/logiciels-et-objets-libres-animer-une-communaut%C3%A9-autour-dun-projet-ouvert/paperback/product-22702396.html)
* Reading more about open science hardware with [GOSH](http://openhardware.science/gosh-manifesto/).. and finding a good [OSH journal](http://openhardware.science/2016/05/20/292/) which leads to there : [http://www.journals.elsevier.com/hardwarex](http://www.journals.elsevier.com/hardwarex)
* Awesome DIY approach and techniques for [ultrasound gel](http://journals.plos.org/plosone/article/asset?id=10.1371%2Fjournal.pone.0134332.PDF) -- already republished on HAD


#### 2016-06-08 Zach

* Semifinalist for HACKADAY's challenge !!
* lending a hand to Zack on GitHub et al : https://github.com/ZTaylor39/murgen-dev-kit
* Interrupts on Arduino for the emulator : https://learn.adafruit.com/multi-tasking-the-arduino-part-2/external-interrupts

Some research on DACs:

* DAC0800LCN 8-Bit D to A Converter -- http://www.makertronics.co.uk/images/detailed/5/Ext-2254-010.jpg?t=1437747336
* http://forum.arduino.cc/index.php?topic=179410.0
* http://www.ti.com.cn/cn/lit/ds/symlink/dac0800.pdf
* http://hackaday.com/2011/02/17/your-first-digital-to-analog-converter-build/
* Example : https://labarqui.wordpress.com/2012/07/03/emulador-de-notas/

R2RlLadders

* http://id.motd.org/pivot/entry.php?id=10
* http://www.mouser.fr/Passive-Components/Resistors/Resistor-Networks-Arrays/_/N-e89l?P=1z0sqtq&Keyword=resistor+network&FS=True
* http://store.digilentinc.com/pmodr2r-resistor-ladder-d-a-converter/

#### 2016-06-09 Week end !

And nothing.

#### 2016-06-13 News

* Moving forward with Zach
* Creating a 8 bit R2R resistor ladder

#### 2016-06-14 Super hacks!

* Discussion engaged with [Muth](https://hackaday.io/muth) (et son pi-print) for a thermal printer addon
* This hack of a [eink display](https://davidgf.net/page/41/e-ink-wifi-display) is awesome. Hacking a STM32F103ZE and plugging a ESP8266
* Working on [CSV images library](https://github.com/kelu124/murgen-dev-kit/tree/master/software/examples_csv) for images using the CSV+dict format

#### 2016-06-17 Printing and budgets

* Printing  with the thermal printer: a success with https://learn.adafruit.com/networked-thermal-printer-using-cups-and-raspberry-pi/network-printing
* No news from Zach ?

Shopping à faire: 1000$ = 840€

* RPi0 : 42€
* Lulu - book on opensource projects : 17€
* Work on EMW3165: 230€
* Transducteur : 150€
* Matos en rab EdgeF: (125€)*3/4
* Deux modules echomods : 110+140 (-125/4)€
* Reste: 101€ for contigencies + SMA cables + matos (bois)

#### 2016-06-18

* Awesome [CapMED](https://docs.google.com/document/d/1GOPfu91g4AG9QSKEKXoJd4JmZWLB6M4NtTwfT9k_dX4/edit)
* Retroengineering [a 10PV probe](https://github.com/kelu124/echomods/tree/master/retro10PV).. only 10PV? Ain't much.
* Drinking beer
* Admiring an [IA work at recontructing blade runner](https://medium.com/@Terrybroad/autoencoding-blade-runner-88941213abbe#.tn5whktwl)

#### 2016-06-19 Hmm 

* Followup with Zach
* Ping Michael T
* Ping Edgeflex: quid microcircuits

Beaglebone black : Max SPI 32MHz
* http://fr.mathworks.com/help/supportpkg/beagleboneio/ug/use-the-beaglebone-black-spi-interface-to-connect-to-a-device.html?requestedDomain=www.mathworks.com
* http://beaglebone.cameon.net/home/reading-the-analog-inputs-adc
* Comment faire un DAC à 1MHz http://www.mikrocontroller.net/attachment/147272/Figure_8_Datenblatt_DAC0800.png

Available probes, one of which being a 10PV:

* http://www.ebay.fr/itm/ATL-Access-10PV-5-7-5-10-MHz-Multi-Frequency-Transducer-3337-/291685156080?hash=item43e9ca44f0:m:md6YQd3EstKy9--Am0X2fdg
* http://www.ebay.fr/itm/ATL-A6-3mhz-Ultrasound-Transducer-Probe-/282069422915?hash=item41aca5d343:g:F6wAAOSw~bFWKk9O

#### 2016-06-21 Financing

* http://www.fse.gouv.fr/archives/article/associations
* http://www.centre-francais-fondations.org/ressources-pratiques/solliciter-le-soutien-dun-fonds-ou-dune-fondation
* http://www.centre-francais-fondations.org/fondations-fonds-de-dotation/annuaire/annuaires-1
* http://www.centre-francais-fondations.org/annuaire-des-fondations/5172
* https://www.vivalto-sante.com/recherche-et-innovation/recherche-clinique/

* http://stackoverflow.com/questions/19950648/how-to-write-lists-inside-a-markdown-table
* https://blog.bolt.io/demystifying-hardware-jargon-9d7a0cda9b55#.wbophjmdk

#### 2016-06-22 Slides, and VDB

* Resources sympas : http://bafflednerd.com/learn-python-online/
* http://pandoc.org/README.html#producing-slide-shows-with-pandoc


#### 2016-06-24 Mechathon

* Working at the mechaton at the CRI
* Playing with Zach's acquisition and testing his filters
* Processing!
* Old.. mais retrouvé: https://web.archive.org/web/20151204121552/http://www.ncl.ac.uk/eee/research/groups/coms2ip/ultrasound-imaging.htm


#### 2016-06-27 Nothing new

* Discussion with NF@V -- interesting. Could be partnering for some cool ideas. Vets, hackers. Maybe soon for docs.
* Has contacts with electronics experts
* Tests of transducers by Jerome

Some ideas on RPi and SPI:

* https://www.raspberrypi.org/documentation/hardware/raspberrypi/spi/README.md
* https://www.raspberrypi.org/forums/viewtopic.php?f=44&t=130616
* https://www.raspberrypi.org/forums/viewtopic.php?f=107&t=132494
* https://www.raspberrypi.org/forums/viewtopic.php?f=44&t=43442&p=347073
* http://richardhayler.blogspot.fr/2016/02/getting-started-with-esp8266-iot-phat.html

#### 2016-06-30 Recycler un minitel

Pour recycler un Minitel, ca se passe la
* http://pila.fr/wordpress/?p=361
* https://x0r.fr/blog/5


#### 2016-06-30 New probes et al

Deux sondes d'occasions assez sympa pour démontage et analyse (mécanique / materiaux / piezos):

* http://www.ebay.com/itm/Philips-ATL-Access-A-3Mhz-Ultrasound-Scanhead-Transducer-Probe-/262496926313?hash=item3d1e093a69:g:psAAAOSwcL5XMe0n (50$)
* http://www.ebay.com/itm/Hitachi-Ultrasound-Probe-EZU-PM3-/400943782280?hash=item5d5a1c9988:g:cdAAAOSwyQtVga8m (30$)

IA and US:

* http://sci-hub.cc/10.1109/TBCAS.2015.2431272

#### 2016-07-01 Meeting with Nicolas

* Terribly instructive. Lots to learn.

#### 2016-07-02 Strategy

* Just doing it!
* Key learning: will be having fun soon =)


#### 2016-07-03 Playing with a trifrequency probe

* Won the probe http://www.ebay.com/itm/Philips-ATL-Access-A-3Mhz-Ultrasound-Scanhead-Transducer-Probe-/262496926313?hash=item3d1e093a69:g:psAAAOSwcL5XMe0n (50$) -- that's a purely 3MHz probe, should be OK and we won't get too many issues with too high frequencies
* Played with the ATL10PV at [https://github.com/kelu124/murgen-dev-kit/blob/master/worklog/Session_9_ATL.md](https://github.com/kelu124/murgen-dev-kit/blob/master/worklog/Session_9_ATL.md). Not good results, high frequency elements are buggy.
* Any impact of the polarity of the pulse?? 
* TODO: Compare the polarity by switching polarity.

#### 2016-07-04 Meeting

* Long one, instructive.
*BBB : https://groups.google.com/forum/#!topic/beagleboard/3AFiCNtxGis and https://www.element14.com/community/external-link.jspa?url=http%3A%2F%2Fhipstercircuits.com%2Fbeaglebone-pru-ddr-memory-access-the-right-way%2F
* Digging into https://developer.mbed.org/platforms/LPC1114FN28/:  a DIP M0

#### 2016-07-05 RTL-SDR

* Bivi's playing with RTL-SDR.. a simple short and one can get to the 0-30MHz, without any upverter. Fun. To explore.

#### 2016-07-06 Making progress with EMW3165

* With the help of Igor, preparing a UDP server of EMW3165 and getting a throughput of 9Mbit/s on average.
* Getting one of the modules
* Requesting Nicolas' help on getting HV7360LA (fab's suppliers are lost)
* Thinking of the overall structure of the maker kit. I need a wooden box and an aquarium (plexiglass, glue = solvent cement)
* Review of the HAD budget (probe, transducer, fab, et al?). Some euros may be saved.

#### 2016-07-08 ATL Probes, ebay & WiFi


Other ATL Probes:
* http://www.jacomed.com/probe/atl-access-a/
* http://www.jacomed.com/probe/atl-access-a-10-pv/

The ATL manual is available at : http://photos.medwrench.com/equipmentManuals/4692-2615.pdf (see copy in the 10PV folder)

* EMW3165 and SPI:
* http://www.emw3165.com/viewtopic.php?t=4330&start=10 or (3$ http://www.ebay.com/itm/131627127638?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT )

* TODO: __some shopping on ebay__
* http://www.ebay.com/itm/SPI-IIC-MPU-9250-9-Axis-Attitude-Gyro-Accelerator-Magnetometer-Sensor-Module-/131185485892?hash=item1e8b43a844:g:qXkAAOSwuzRXdx-~
* http://www.ebay.com/itm/NodeMcu-Lua-ESP8266-CH340G-WIFI-Internet-Development-Board-Module-/161833537754?hash=item25ae07d0da:g:N-4AAOSwepZXSUtI
* http://www.ebay.com/itm/Arduino-Shield-40pcs-20cm-male-to-female-Dupont-cables-/140741253413?hash=item20c4d51925:g:uSMAAOSwMNxXYPH7
* www.ebay.com/itm/Mifare-RC522-Card-Read-Antenna-RFID-Reader-IC-Card-Proximity-MFRC-522-Module-/130892542303?hash=item1e79cdb15f:g:3h8AAOxycERRjRN7
* http://www.ebay.com/itm/84-48-LCD-Module-White-backlight-adapter-pcb-for-Nokia-5110-top-S3-top-good-sale/172260052269?_trksid=p2047675.c100005.m1851&_trkparms=aid%3D222007%26algo%3DSIC.MBE%26ao%3D1%26asc%3D20131003132420%26meid%3D836a21703127491d9ad58909aad4acab%26pid%3D100005%26rk%3D1%26rkt%3D6%26sd%3D131739821242
* http://www.ebay.com/itm/2PCS-2-4G-Wireless-SMA-Antenna-2dB-2-5dB-Gain-for-NRF24L01-PA-CC2500-Module-/161987106053?hash=item25b72f1505:g:VkIAAOSwMN9XQ8id

* Awesome TFT screen -- really cheap: http://www.ebay.com/itm/131627127638?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT

#### 2016-07-09 Goblin works !

* See the [github repo for goblin](https://github.com/kelu124/echomods/tree/master/goblin). worked on the doc

#### 2016-07-10 Should be doing some queries on Alibaba..

* TODO: Getting samples and suppliers ? 

#### 2016-07-11 Getting a first transducer

* Got and paid for a SM heavy backing transducer. Now, let's find what servo to use.
* TODO: servo + transducer + mounting platform

#### 2016-07-13 Some new stuff

* __SPI__
* https://learn.sparkfun.com/tutorials/raspberry-pi-spi-and-i2c-tutorial
* essayer SPI avec les petits trucs funs
* cables pour SPI a base de cables ethernets?
* __STM32__: mise a jour du fichier uC avec [un nouveau STM32](http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32f3-series/stm32f334/stm32f334r8.html) dans [Notes uC](/croaker/notes_uC.md)
* __Contact AD__

#### 2016-07-15 Playing at the lab

1. Cleaning a signal with [Goblin](/goblin/) : done. The second log, with this time a new energy supply, gives a really beautiful outcome. Lesson: don't put 18V in a 3.3 and 5V regulator =) [See the results here](https://github.com/kelu124/echomods/blob/master/goblin/2016-07-15.md).

2. Playign with an ATL Access 3. Getting nice echoes... of 1.3V, even not using the full gain (60%) and the full pulser voltage on [Murgen](https://github.com/kelu124/murgen-dev-kit). [See the logs here](https://github.com/kelu124/echomods/tree/master/retired/retroATL3). Was some work with the oil refill =)

#### 2016-07-17 ATL probes

* Finding more about [ATL probes](https://github.com/kelu124/echomods/blob/master/include/ATL.md) - with a list of probes, and trying to find back the pins!
* TODO: Presentation on Goblin's module

#### 2016-07-18 Some goodies

* [Cheap ATL Access Probes](http://www.ebay.fr/sch/i.html?_from=R40&_trksid=p2050601.m570.l1313.TR0.TRC0.H0.XATL+Access.TRS0&_nkw=ATL+Access&_sacat=0)
* Finding more about [ATL probes](https://github.com/kelu124/echomods/blob/master/include/ATL.md) - with a list of probes, and trying to find back the pins!
* Autodocumenting -> See the results of autobuilding doc at : [https://github.com/kelu124/echomods/blob/master/Readme.md](https://github.com/kelu124/echomods/blob/master/Readme.md). None of it is written by hand.
* Read also an ... __autogenerated__ prez [about this here](http://kelu124.github.io/echomods/DocumentationProcess.html).
* This post blog is also autogenerated using the [worklog](https://github.com/kelu124/echomods/blob/master/Worklog.md)..

#### 2016-07-19 Plenty of stuff

* Passionnant: https://hackaday.io/project/11943-open-indirect-ophthalmoscope
* Récupérer la datasheet : http://www.analog.com/media/en/technical-documentation/data-sheets/AD7276_7277_7278.pdf
* Cf Baptiste Pierrat - https://e2e.ti.com/support/arm/sitara_arm/f/791/t/396940

##### BBB->Baptiste Pierrat->FastPRU->UpTo3Msps

* Initialiser PWM sur un trinket pro : https://learn.adafruit.com/introducing-trinket/programming-with-arduino-ide

##### TODO:

Base sonde

* Finir de remplir d'huile la sonde
* Tester les connections du BBB, déterminer les masses, surtout trouver le moteur
* Faire des acquisitions a full speed avec Murgen+Bitscope

SPI et BBB

* Tester le SPI avec BBB (Baptiste Pierrat)
* Si ca marche, tenter de controler Moteur + Pulser avec BBB

#### 2016-07-20 Murgen on the way for the second prize!

* Reponse de Baptiste Pierrat 
* http://hackaday.com/2016/07/18/hackaday-prize-20-projects-that-make-us-all-citizen-scientists/ =) Yeaayyy merci pour la reconnaissance =)

#### 2016-07-21 Next steps

* Working on a presentation for the next steps of these modules
* Envoi a edgeflex d'un HV7360
* Hellyeah : http://www.cnx-software.com/2016/07/21/google-research-prudaq-is-a-40msps-adc-data-acquisition-daq-cape-for-beaglebone-black-green/

#### 2016-07-27 Apres Avignon

Yeayyy! [Beagleboard fondation tweeted about Murgen](https://twitter.com/beagleboardorg/status/757815778447986688) -- that's driving traffic to github =) 

High speed acquisition
* PRUDAQ

Slow Acquisition
* tobo/goblin+cletus+BBB to drive the goblin ADC
* tobo/goblin+cletus+hannin to wirelessly stream

I decided the emulation was going to be necessary to avoid playing all the time with piezos. It appears Teensy 3.2 can handle that.

Choice of the servo:
* http://www.hobbyking.com/hobbyking/store/__23158__Turnigy_8482_TGY_1267HV_Titanium_BB_DS_MG_Servo_14kg_0_10sec_57g.html
* http://www.modmypi.com/electronics/motors-and-robotics/servo-motor-sg92r-micro

More stuff about Phantoms: http://meritus.kopernika.pl/homemade-tastes-better/

And ... working on the [2016 Summer presentation](https://github.com/kelu124/echomods/blob/master/include/20160720-Milestone.md). 


#### 2016-08-02 Last week, after a week holiday

* Working on the [milestone presentation](http://kelu124.github.io/echomods/20160720-Milestone.html).
* Received a 12V alim, the PRUDAQ, and pushed the issue with Silent onto github. Ongoing !


#### 2016-08-04 Soon off

* Working on the [finance file](https://github.com/kelu124/echomods/blob/master/include/Finance.md) --> still work to do !
* Setting the stuff on for 1000$ from HAD
* HD should have received the pulser module.. waiting for it =)
* Worked on the [doc-test script](https://github.com/kelu124/echomods/blob/master/doc/) to automatize the results of modules documentation tests -- [see an example with an error](https://github.com/kelu124/echomods/blob/master/example_fail.md)



#### 2016-08-08 First day

* Received tobo !! yeayyy
* Playing with Doj and assembling the board (tobo, goblin, oneeye and mogaba). Should be enough to get first images.
* power seems OK, first pulses look nice
* Todo: test with my transducer for Cletus, and with ATL3
* Thanks to Virginie for her support on debugging Doj !!

#### 2016-08-09 Moving forward

Roughly, all the modules are fine. Emulator is done and tested. Some tests today:

* Test Analog Processing + ATL3
    * -> https://github.com/kelu124/echomods/blob/master/goblin/2016-08-09.md
* Test Emulateur de signal + Analog processing
    * -> https://github.com/kelu124/echomods/blob/master/silent/Readme.md

What the next steps are :

__High priority:__

* Use PRUDAQ
    * Clip the signal between 0 and 2V
* Get image from the [retroATL3](/retroATL3)

__Medium Priority:__

* Bitbang Goblin's SPI directly
* Resume documentation

__Low Priority:__

* EMW3165 to move forward
* Cletus for Servo + Piezo (and mech parts) - using SmartMaterials piezos

#### 2016-08-10 Simple things

* Clipped the signal
* Documentation ongoing
* Received TFT+Servos

#### 2016-08-11 Small FPGA

Awesome work: a FPGA on a RPi0 footprint
* https://hackaday.io/project/13048-fleafpga-ohm-development-board

#### 2016-08-14 Acquiring a first image

* Read some [on this page](/include/20160814/2016-08-14-HackingAUltrasoundProbe.md): got an image from a ATL3 probe, a small metal cube in water.
* Leaving for holidays =)

#### 2016-08-22 Back from holidays
	
* Working with Virginie and Benoit to get images
* Got to play with a [general multi tissue fantom](/include/20160822/2016-08-22-Fantom.md): got an image from a ATL3 probe, of the fantom.
* What about [using Kaggle as a data repo](http://blog.kaggle.com/2016/08/17/making-kaggle-the-home-of-open-data/) for open data ?

#### 2016-08-24 Finalizing the autodocumentation to gitbook
	
* Yeay!! Done. [Gitbook available on this page](https://kelu124.gitbooks.io/echomods/content/)

#### 2016-08-26 Show and tell

* Showing the documentation generation process on an apero at l'Hotel Dieu

#### 2016-08-28 Sharp eye

* Thanks to a question raised by a sharp-eye, I'm putting as a disclaimer that this project is not one supported by the echopen's association. Even if I'm a cofounder of echopen, this project is a personnal one, for the echopen community. Clarified with hackaday, not an issue for them wrt the prizes.

#### 2016-08-29 Hey from Liberia

* got contacted for a partnership to improve, build, and crowdsell a set of modules. Interesting!

#### 2016-08-30 Some good news

* Got some feedback of PRUDAQ's people on the doc, thanks to them for this contribution!
* Zach's been back. Let's see what can be done.
* Prof Charles is going to be in Paris: let's meet!
* Been invited to speak at Hackaday's show for its prize on Nov 5th
* Trying to get the latest HV7360 from MC.. seems difficult to say the least

#### 2016-08-31 Habitat numerique

* Thinking about the use of the _"Logiciel and Objets libres, animer une communaute autour d'un projet ouvert"_
* Interesting : [STBone - BeagleBone form-factor STM32F427 board](http://ebrombaugh.studionebula.com/embedded/stbone/index.html)
* Doing some thinking about [the servo part](/cletus/) -- should be integrating a feather + screen to help debug the output =)

###### Resources:

* https://opensource.com/health
* http://innovations.bmj.com/content/early/2016/03/14/bmjinnov-2015-000080.full
* https://cronfa.swan.ac.uk/Record/cronfa27203

###### Blogs

* https://dzone.com/articles/medical-capsule-robot-hardware-and-software-goes-o
* http://www.open-electronics.org/vanderbilts-medical-capsule-robots-goes-open-source/
* https://scicasts.com/healthcare-technology/2068-medical-devices/10270-engineers-open-source-medical-capsule-robot-technology/

###### Support?

http://www.opensourceimaging.org/

Do you work on an open source project with potential application for MRI or other related medical research and technology? We will also highlight early stage projects (prior to a stable release and documentation) in order to improve collaboration at that early stage. Let us know and contact us at info@opensourceimaging.org.

Would you like to support an existing project with your skills and expertise? Or do you have any more questions? Contact us at info@opensourceimaging.org.

###### Forums a pinger pour un kit?

* http://forum.arduino.cc/index.php?topic=236802.0
* http://electronics.stackexchange.com/questions/50577/what-ultrasonic-sensoremitter-should-i-use-for-my-medical-ultrasound-project
* http://www.ceus-now.com/what-ultrasonic-sensor-emitter-should-i-use-for-my-medical-ultrasound-project/

#### 2016-09-01 A ping from GroupGets

* It’s not a surprise that our backers waste no time getting inventive. We were pleasantly surprised by a tweet to check out this novel application of PRUDAQ in a [DIY Ultrasound Imaging Platform](https://www.gitbook.com/read/book/kelu124/echomods). [_source_](http://us10.campaign-archive1.com/?u=0b4a06d3b16c2573ff89aa414&id=3c93652604&e=b8636f98a5).
* Need to find a way to clarify a CLA if forking this repo to somewhere else

#### 2016-09-02 JOH

* Thinking of preparing an article for the JOH (or HardwareX ?)

#### 2016-09-03 Cheers Sandeep!

* An interesting VT100, USB-enabled - https://hackaday.io/project/13273-diy-vt100


#### 2016-09-07 Back in Paris!

* Best hardware I've seen so far : [Arduboy](https://www.seeedstudio.com/Crowdbuy-1.html). Both a controler, a platform to play with, an arduino, ...

#### 2016-09-08 AG of the assocation

* Congrats @BiVi for the position ;)

#### 2016-09-09 Random stuff as usual

* Arduboy ? Awesome!
* A design for [Sleepy](/retired/sleepy/) is taking place.. wood rules =) Need a water tank though.
* An awesome thing to automate physical interactions with a phone, using https://www.tindie.com/products/hugs/tapster/

#### 2016-09-12 Thanks Adafruit

* [Comm] : got cheers from [Adafruit, check this link =)](https://blog.adafruit.com/2016/09/12/murgen-open-source-ultrasound-imaging-with-beaglebone/)
* Made some progress with a i2c 128x64 oled to debug the Feather ADC, using this [elegant doc](http://www.projetsdiy.fr/ssd1306-mini-ecran-oled-i2c-128x64-arduino/#.V9Zt5tGxU8o).
* Getting up to 1Msps with the [Feather](/croaker/feather_tests/2016-09-10-Feather_ADC.md).
* @done: makedoc should include a link checker.. everything starting with `](/` should be tested and checked if existing. That includes images.

#### 2016-09-13 Stand alone echoes visualisation

* Same, for today's date, at [Feather](/croaker/feather_tests/2016-09-10-Feather_ADC.md).

#### 2016-09-14 With a servo

* That is done. Videos to come.
* Missing: sending through UDP.

#### 2016-09-16 Wifi

* Connecting to wifi: done
* Beers @Stalingrad, and chilling =)

#### 2016-09-22 More speed for data acquisition and streaming

* This is getting better. [Read the log on this repo](/croaker/feather_tests/2016-09-10-Feather_ADC.md). [Arduino IDE code is here](/croaker/feather_tests/2ADC2UDP.ino).

#### 2016-09-23 Getting some raw images

* Still this pulser issue, but the signal is correctly stored. [More to download here](/croaker/data/examples/). Captured through UDP streaming.

#### 2016-09-27 Processing the raw images

*  Created the scripts to batch scan-convert and animate the images. [More to see/download here](/croaker/data/examples/)
* Hopes to get the STM32 go faster =)
* Adding the croaker work to the gitbook .. and cleaning some remaining broken links during doc generation.

#### 2016-10-02 VIdeo for hackaday contest

* Done in halong bay

#### 2016-10-20 Meeting and such

* Meeting at HD, milestone with Bitmakers
* USB key that does Pulser, Acquisition : http://www.lecoeur-electronique.net/cariboost_files/us-key_r4_0.pdf

#### 2016-10-21 Update of Tobo

* [The pulser module](/tobo/) used a HV7360, which went from a LFGA to a CABGA. The gerbers were updated accordingly.

#### 2016-10-22 End of week

* Trouve au hasard : "One material with exceptional acoustic properties is TPX (polymethylpentene) [Westlake Plastics Company,  Lenni,  PA]. Pour une sonde à 35MHz, mais ca peut donner des pistes de suppliers. (Ref 10.1109/ULTSYM.2001.991996)
* Article being written at https://gist.github.com/kelu124/af9e3b39b0ba8bed3bde250489635fa6
* Onboarding Pouya =)

Next week:

* @todo 6Msps on the [STM32](/croaker/)
* @done Sourcing transducer (in [cletus](/cletus/) )
* (done) Sourcing materials + integration makefile par set
* (done) Compiler output

##### @perso : faire un eink tablet

* http://the-digital-reader.com/2015/02/16/wifi-connected-e-ink-display/
* http://the-digital-reader.com/2012/09/18/meet-the-kindle-ereader-audiobook-player-weather-station/
* https://www.amazon.com/s/ref=nb_sb_noss?url=search-alias%3Delectronics&field-keywords=ED060SC4+
* http://spritesmods.com/?art=einkdisplay&page=3
* http://hackaday.com/2015/02/16/wi-fi-connected-e-ink-display/
* http://hackaday.com/tag/esp8266/
* http://hackaday.com/2016/06/12/an-improved-wifi-connected-e-ink-display/

#### 2016-10-23 Geeking

* Over engineering ? https://d262ilb51hltx0.cloudfront.net/max/800/1*xzS-UkYtNOgzPvpkHGwRbQ.png 
* Found an interesting octal transmit board : http://www.ti.com/tool/TX-SDK-V2
* Update of the [references list](/include/references.md)

#### 2016-10-24 Geeking II

* Skype with wayne.edu -- maybe modules ?
* arduino legos : awesome form factor https://twitter.com/bwshockley/status/789971893356900352
* Paris on t'aime http://www.konbini.com/fr/tendances-2/paris-mairie-video-anne-hidalgo/
* http://www.npr.org/2016/10/21/498734538/black-mirror-is-back-reflecting-our-technological-fears
* http://www.bandits-mages.com/rencontres2016/ressources/
* Darkness https://www.poetryfoundation.org/poems-and-poets/poems/detail/43825

#### 2016-10-25 Financing through ebooks

* e-book generation at a. : https://medium.com/@aayushu/how-i-make-400-a-month-in-passive-income-by-self-publishing-68fa948edff5#.8h9udy2ad


#### 2016-10-26 Playing with a photon

* http://arduino.stackexchange.com/questions/12079/compatibility-between-particle-photon-and-arduino
* http://arduino.stackexchange.com/questions/30551/using-arduino-ide-on-the-particle-photon
* https://store.particle.io/ 19$ le photon
* Chopper un ESP32 ?
* Chopper un photon chez hackspark?
* Follow up with Zach - modules?

#### 2016-11-01 On Tindie

* Check out https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/

#### 2016-11-03 Having fun with batteries

* https://hackaday.io/project/16358-pix-e-gif-camera

#### 2016-11-05 State of the art

* https://github.com/RemediOSM/UltraSound
* https://github.com/sigurdstorve/OpenBCSim to generate US images


#### 2016-11-15 Some lag, new job

Just started a new job 10 days back, so I lagged a bit. However, some news!

* Sold two boards so far on [tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/) - which also gave opportunities to discuss with people: awesome.
* Auto documentation moved forward! Plenty of new debug options in the [doc generation journal](/doc/log.md)
* Some metadata on md files on board
* Trying to get 2 probes on ebay for testing purposes
* Some forum at 
    * https://forum.arduino.cc/index.php?topic=79285.new#new
    * http://forum.arduino.cc/index.php?topic=177489.0
* Posted something on reddit as well: https://www.reddit.com/r/UltraResearchers/comments/5dc13w/ultrasound_imaging_open_hardware_devkit/

#### 2016-11-20 Week end

* Shipped a first module!
* Worked on a review of the autodoc generation script
* Submission of a summary (or soon to be JOH article) to arXiv
* Discussions with http://www.ibme.ox.ac.uk/research/non-invasive-therapy-drug-delivery/people/dphils/visa-suomi for interesting applications =)
* Follow up with Fouad & Sven


#### 2016-11-20 Terrible

Two awesome articles
* Portable low cost ultrasound imaging system: M. Sobhani contacted =)
* A low-cost high-fidelity ultrasound simulator with the inertial tracking of the probe pose

#### 2016-12-01 arXiv

* Published! https://arxiv.org/find/all/1/all:+AND+ultrasound+arduino/0/1/0/all/0/1

#### 2016-12-06 Press review

* Working on a press review, [can be seen here](/include/AddPressReview.md)
* @done: AddPressReview to the main page here, and on the gitbook
* @done: review the latex article on arXiv, especially with respect to references
* Need to ping Jerome for the BGA update of HV7360
* @done too:
    * Servo + Feather
    * Servo + BBB + enveloppe
    * Servo + ADC on board + RPi0
    * Servo + BBB + raw signal
    * BBB + probe
* @done CERN !

#### 2016-12-08 Connecting

* Chatting with Gnusha

#### 2016-12-11 Just moved in

Just moved in to the new flat! Exhausting =) Other interesting things: 
* https://hackaday.io/project/7225-low-cost-x-ray-systems-for-developing-nations

#### 2016-12-17 Breadboard phantom

* Done some tests with a breadboard phantom: [read more here](/croaker/data/20161217/20161217-TestingArduinoAndPhantom.md).
* Still moving in the new flat, getting accustomed to the new job.. and still need to sort the hacking tools in a limited space in the new flat =)
* Interesting competition : Clarius got its approval. Also noted the SONON 300C.
* Having fun with mapping a community using slack. On another repo.
* Published some update on the ML.

#### 2016-12-19 Adding devices

* See [the list of similar handheld, low cost devices](/include/AddDevices.md)
* Integration of previous steps in the gitbook

#### 2016-12-26 Raw ideas

* Max RPi speed : http://d-fence.sytes.net/raspberry-pis-gpio-speed/  @done --> do it with the Rpi0
    * http://codeandlife.com/2015/03/25/raspberry-pi-2-vs-1-gpio-benchmark/
    * Using the same experimental setup, the Raspberry Pi 2 is about 2 to three times faster. The fastest is still the C native library, topping out at just under 42 MHz. 
* Thinking of 20E-214 and moving to Alibaba for wireless probes. Will F.'s support reach?
* Using Vitamins for the gyro's probe. What name still for it? Longinus?

#### 2016-12-29 Moving forward

* Getting to think of the 20E-214 ones =)
* Chat with 1Tech, and the guy Patrice. Motivating.
* Trying to get some stuff from the arduino, namely to get it work as a server. [Far from being finished, on it](/croaker/feather_tests/2Msps_Server.ino).

#### 2017-01-02 Merry new year

* 20E214
    * Getting a propal from PR
    * Fouad offering to test the 7.5MHz linear
    * Me to check other suppliers

* Some modules finaly added to the [echopen's community medkit repo](https://github.com/echopen/PRJ-medtec_kit/) and added a config, the [wireless 1.1 config](https://github.com/echopen/PRJ-medtec_kit/tree/master/configurations/CFG-arduino_servo).
* Added a version of my [jupyter notebook to explore the dataquarium data](https://github.com/kelu124/PRJ-medtec_sigproc/blob/6412c4ce4da4fe8f3ea1a4144fe389d411b0b80e/dataquarium/explore.ipynb) from the dataset released end of Dec '16.

#### 2017-01-10 Heated debate on ultrasound prices

* Some info on HN : 
    * a great discussion on hardware at https://news.ycombinator.com/item?id=13230741
    * https://patents.google.com/patent/US4446395A
    * a blog post by NF at http://liesandstartuppr.blogspot.fr/2016/12/why-are-medical-ultrasound-systems-so.html 
* https://github.com/MedtechDiagnostics/video2dcm
* Bonus? http://liesandstartuppr.blogspot.fr/2016/12/quick-guide-to-spotting-non-existent.html

#### 2017-01-10 Consolidating

_“We do not grow absolutely, chronologically. We grow sometimes in one dimension, and not in another; unevenly. We grow partially. We are relative. We are mature in one realm, childish in another. The past, present, and future mingle and pull us backward, forward, or fix us in the present. We are made up of layers, cells, constellations.”_

* Presentation to [ESPGG](https://twitter.com/ESPGG/status/819967641607606272), participated to.
* Hardware: 
    * went to solder some stuff at HD
    * UltrasHound -- moving forward
    * [Beaglebone PRUDAQ](https://drive.google.com/open?id=0B71ZoToGBAC1WHFZT1gyV0xHbzg) image added.
* Added some details (better raw image quality) to the [SigProc 101](https://github.com/kelu124/PRJ-medtec_sigproc/blob/master/SigProc_101/SigProc-101.ipynb) jupyter notebook. 
* Interesting paper on [Theory of Change](http://www.cdra.org.za/uploads/1/1/1/6/111664/threefold_theory_of_change_-_and_implications_for_pme_-_doug_reeler_of_the_cdra.pdf).
* Peter confirms the probe is on its way.
* JOH article: first comments received. Harsh, but good to move forward! And adding a couple of images, better introduction, ...


#### 2017-02-11 Diverse

* Moving things forward with the [JOH article](/include/JOH/source/main.tex)
* Testing the [RPi0 max GPIO speed](/goblin/pi0/Readme.md) to try it with the goblin ADC
* Full day meeting for PRJ methodo.

#### 2017-02-12 Diverse

* Fun: http://hirelofty.com/blog/how-build-slack-bot-mimics-your-colleague/
* Playing with markov chains : http://agiliq.com/blog/2009/06/generating-pseudo-random-text-with-markov-chains-u/

#### 2017-02-19 Update to Doj and such

* Thinking about an update for a neat, silkcreened, well designed motherboard. Would be excellent for Altay, Felix and maybe 
* Been doing some progress about the HV - working with Lorena to get one on board. I'll have 2 pulsers, will ask for 3. In total I'll still be able to send to (Afreen/Felix/Altay) + one for the GroupGet friends. Would leave me with one. 
* Afreen still working on the feather, after contacting the PRUDAQ guys.
* Get Felix on Slack?
* Call scheduled with Fouad on tuesday
* Making progress on 20e214 - control of the probe OK. Display remaining, then CSV saving.
* Taking more time about the Slack bot: lower priority
* Update by Tobey: he found a way to compare PDFs.


#### 2017-03-01 RPi0

See [this log](/goblin/pi0/HighSpeedBurstADC.md)

#### 2017-03-02 RPi0  bis

Given RPi0 capabilities in terms of [GPIOs](/croaker/notes_RPi0.md) - why not push it to 20Msps, 8 bits, for the cape?


#### 2017-03-05 Grmbl netty

Netty isn't nice... but just got my article accepted by JOH !

#### 2017-03-06 Further work

* Updated the [suppliers repo](/cletus/suppliers/Readme.md)
* Testing the [goblin](/goblin/) In/out transfer function on the [emulator](/silent/) signal: [read here](/retired/toadkiller/data/test_enveloppe/). The more I play with Jupyter notebooks, the more I like it.

* Thinking about the 15 - 20 - 25 Msps pHAT.
* Moving forward with the Netty issue at [@20e214](http://github.com/20e214/)

* Fun pHAT : IR : https://hackaday.io/project/20178-anavi-infrared-phat
* Radio pHAT : https://hackaday.io/project/20199-empedocles

* Interesting read: https://medium.com/@lhartikk/a-blockchain-in-200-lines-of-code-963cc1cc0e54#.kxsh35e7i

![](https://imgs.xkcd.com/comics/unpublished_discoveries.png)

#### 2017-03-12 DOIs for releases

* While preparing the article, I've been invited to "save" of copy of the repo into Zenodo ([see the backup](https://zenodo.org/record/377054). And I've got a nice Zenodo link!

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.377054.svg)](https://doi.org/10.5281/zenodo.377054)

* Taking time on 20e214... still sucking at 20e214.
* Waiting for the CA3306E to reach !

#### 2017-03-19 Finish Doj

* Working on [Doj](/doj) and releasing the KiCad definitive code - available on [OSHPark](https://oshpark.com/shared_projects/2taE6p4M).
* PCB of the [RPi0 high-speed ADC](https://github.com/kelu124/bomanz) is ongoing !
* Getting the last touches to the JOH article.

#### 2017-03-20 Doj ... unfinished

* Indeed. Forgot to add a ADC input directly from a strip, two strips for PulseOn and PulseOff, and a way to control the servo from the Pi.
* Also starting the new season of the HackadayPrize =) 
* Still some issues with [bomanz (on HAD)](https://hackaday.io/project/20455-20msps-adc-raspberrypi-extension-bomanz) PCB. Some pads suck. I guess I'll order the board from OSHPark along with [Doj's](/doj/) and solder all these tiny stuff. Not so many actually.

#### 2017-03-21 Moving forward

* Posted the Chinese probe project on Hackaday. Will play with the probe using a RPi framework. Should do the trick =)
* Following up on [6Msps upgrade](/croaker/), [mother board seem OK, silkscreen to do](/doj/), then [Pi1](https://github.com/kelu124/bomanz) and _Pi2_ to follow.
* [History](/include/AddHistory.md) to develop.

#### 2017-03-22 JOH ongoing !

* Got published! http://openhardware.metajnl.com/articles/10.5334/joh.2/
* HAD some great projects: https://hackaday.io/tfogarty and https://hackaday.io/project/19685-early-and-low-cost-detection-of-heart-failure

#### 2017-03-25 Studious week end

* Some great discussion on use of doppler for heart issues, [notes being here](/include/20170325/). Interesting DIY vintage doppler to do!
* Put all the information on [the Trove](https://gitlab.com/kelu124/theTrove) temporarly before uploading to the main repo.
* Updated the [Doj](/doj/), [Bomanz](https://github.com/kelu124/bomanz),  and [the CA3306E](https://github.com/kelu124/bomanz/tree/master/CA3306E) board. Ordered as well on OSHPark, finally!

#### 2017-03-30 Peaceful for once

* Maybe have a demo of the ATL3+modules to Loic this we
* HV7360 new gen should be ok
* someone more on the waitling list for the pulser
* getting some likes on the https://hackaday.io/project/20533-hacking-a-chinese-wireless-ultrasound-probe 
* boards are on their ways..
* so it's quiet !

#### 2017-04-04 Chinese probe SDK

* Moving forward! Capturing some images [from the probe, trying videos](https://github.com/kelu124/kina/blob/master/20170404-Crunching_Video)


#### 2017-04-06 Purple

* Got some PCBs for Bomanz, for both [high speed](https://github.com/kelu124/bomanz/blob/master/images/20170406_124950.jpg) and [CA3306E](https://github.com/kelu124/bomanz/blob/master/images/20170406_124914.jpg) ADCs.
* Got some PCB for [Doj, and tested those](/doj/20170406-PCBs.md)!

#### 2017-04-12 Mounted boards!

* Playing with DICOMs on Kina, should be ported to all images. [Example of code](https://github.com/kelu124/kina/blob/master/20170411-DICOM.ipynb) yields [funny dicoms](http://www.dicomlibrary.com/meddream/?study=1.2.826.0.1.3680043.8.1055.1.20170411215409237.878569250.8160869).
* [Here's what the ADCs boards look like](https://github.com/kelu124/bomanz/blob/master/images/20170406_124950.jpg).

#### 2017-04-13 Error, that's hot

* Tantalum capacitor: not in reverse! Never!! What are the odds that I put all 3 capacitors on 2 different boards _all in reverse_ ?

#### 2017-04-15 Capacitors connected

* That's well and done. Shall be trying this week end!
* Got 50$ bonus from OSHPark... yeay!!
* Tweet proposed by _"Cool, well if you want to release it as a product or anything then let us know and we'd be happy to help :-)"_ @PiSupply


#### 2017-04-17 End of week end	

* Working on the [press review](/include/AddPressReview.md)
* Backing HIDIOT : HIDIOT Kickstarter Edition Kit

* Yeayy! [Bomanz on OSHPark](https://blog.oshpark.com/2017/04/15/high-speed-adc-phat-for-raspberry-pi/)

* Where to do next PCBs?
    * http://www.pcbcart.com

#### 2017-04-23 Playing with ADC

* Playing with ADC.. got the first results with the CA3306E board! See https://github.com/kelu124/bomanz/blob/master/CA3306E/20170422-FirstAcqs.ipynb
* Played with Loic on the RF modules
* @todo dig into [CMOS Ultrasound Transceiver Chip for High-Resolution Ultrasonic Imaging Systems.](https://www.ncbi.nlm.nih.gov/pubmed/23853268)

#### 2017-04-30 Playing with ADC - v2

* https://github.com/kelu124/bomanz/blob/master/20170430-PushingADCLimits.md and at the bottom of it.. the next steps (for tomorrow? ;) )
* from @rbo http://linuxgizmos.com/google-assistant-sdk-dev-preview-brings-voice-agent-to-the-raspberry-pi/
* Bomanz on Hackaday http://hackaday.com/2017/04/30/hackaday-prize-entry-high-speed-sampling-for-the-raspberry-pi/

#### 2017-05-05 Moving forward

* Been testing new iteration of Tobo with new HV7360. Pulser works with the [pulser control](/retired/oneeye/)
* Testing the pulser with the [RPi Control](/tomtom/) see [the notebook](/tomtom/20170507-TomTomTests.ipynb).

#### 2017-05-13 Some new stuff

* PCBs for [Doj V2](/doj/source/v2.0-kicad) - [see what it looks like](/doj/images/doj-v2.png) are ordered
* @done contact Sonopen / microsonix
* Exploring [Underwater Imaging Using a 1 × 16 CMUT Linear Array](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4813887/)
* @done add Felix, Will + Jp, Charles, Md+Afreen
* @todo add Visa, possibly Pouya and Thomas as contributors
* @todo map interested (green) 
* @done map users (blue)
* @done add OSH license
* @done start an order for pulsers
* @done start a [quickstart](/include/AddUSSDK.md) 
* 2E: 54+148.96 = 202.96
* [Different systems](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3158704/#!po=51.8182)
* LT todos:
    * Using an adapter for the motors control of the ATL probes
    * Using a 3 to 8 CMUT with a multiplexer =)
    * Adding a pulse control from the kernel module / driver for bomanz

#### 2017-05-15 Interleaved on RPi.

* Still about the [RPi0 high-speed ADC](https://github.com/kelu124/bomanz/) : if I can't get above 10Msps due to a memory copy time, I may be able to double the speed by having 2 ADCs interleaved... it's to test!
* Some answers for the CMUT stuff.. let's see if it's going somewhere !
* ATL probes connectors are LEMO 18 or 19 pin.

#### 2017-05-16 More todos.

* Discussing with groupgets
* Some guys forking the [Kina](https://github.com/kelu124/kina/) repo =)


#### 2017-05-19 Bomanz interleaved

* PCBs sent for a [High Speed ADC pHAT v3](https://github.com/kelu124/bomanz/tree/master/AD9200). This time, two interleaved AD9200s.

#### 2017-05-20 Working on ATL3

* [Managed to get a peak into a ATL probe](/retroATL3/2017-05-20_APeakInside.md) - update to the [ATL probe](/retroATL3/).
* Working on the offset

#### 2017-05-22 Testing Doj v2

* Got the PCBs and [tested them](/doj/20170522-DojV2tests.md). Yeayyy, they work! Slight hiccup with the ADC, nothing dramatic though =) Actually, two pins have a double use along with the ADC pins. Dumb me :p

#### 2017-05-29 Testing Doj v2

* Pushing some pics of the [devkit 2.0](/include/devkit2.0/20170529_203924_notes.jpg) - note that this config allows pulse transmit. Pulse from the pulser, receiving through the analog front end.. and acquisition managed by the adc and raspberry.
* Note to self: this config requires a "good" usb power supply. It succeded with a 5V 750mA power supply - but failed from USB.
* @todo Add a documentation server
* @todo Display IP on the OLED.

#### 2017-06-09 Lots ongoing !

* Got the boards for Bomanz v3 and SMD stuff
* Sold some boards
* @todo Need to have a look at this RPI GPIO DMA  - https://github.com/hzeller/rpi-gpio-dma-demo
* @todo Include some cletus remarks (sourcing) on gitbook
* @todo convert all previous images to dicom
* @done answer some questions online for RPI + ultrasound
* @done add the at todos to the shopping list (see [here](https://kelu124.gitbooks.io/echomods/content/Chapter7/shoppingList.html) ) by means of a grep -> temp file
* @done Test YAML data on Markdown files (see contributors)

#### 2017-06-11 Testing the ADC

* Butchered the ADCs.. but I think I got the interleaved thing !
* Adding officially the ADC pHAT to the modules as [elmo](/elmo/) =)
* A summary of the [Pi HAT test with the modules to image](/elmo/data/arduino/20170611-arduino.md) and the [notebook](/elmo/data/arduino/20170611-arduino.ipynb).
* Debbugging the [ADC inputs](/elmo/data/20170609-NewADC.ipynb)

#### 2017-06-13 Getting into signal processing 

* Managed to get the offset by inserting a 100pF capa in series with input
* Testing the ADC now with the Offset, see [notebook](/elmo/data/arduinoffset/20170612-ArduinoFFTed.ipynb)
* [RPi Article](/include/RPiHSDK.md) to be started
* http://gnusha.org/~gnusha/logs/html/2016-06-06.log.html as  reminder of former tests

#### 2017-06-19 Finishing the RPi Doc

* [Nothing](/include/RPiHSDK.md) much to do / say
* Added a [benchmark for components](/include/AddBench.md)
* Some ideas more to promote this product for A-mode tools
* http://hackaday.com/2017/06/19/twenty-iot-builds-that-just-won-1000-in-the-hackaday-prize/ =)
* http://www.ebay.com/itm/41139-5-7-5-MHZ-ENDOVAGINAL-ULTRASOUND-TRANSDUCER-PROBE-142252/391810622241?_trksid=p2047675.c100005.m1851&_trkparms=aid%3D222007%26algo%3DSIM.MBE%26ao%3D2%26asc%3D41376%26meid%3D7c8962ca8fe34037884411c7eaad4a6c%26pid%3D100005%26rk%3D2%26rkt%3D6%26sd%3D252386695621 : array ?
* http://www.ebay.com/itm/ATL-MFI-7-5-5-0MHz-Cat-4000-0271-03-EndoRectal-Probe-3316-/111904974005?hash=item1a0e0e64b5:m:mkMb5fsyIlR5o1t1srcqOwA
* Awesome capsule work: http://sci-hub.cc/10.1109/TMI.2017.2699973

#### 2017-06-22 Consolidating ideas

* Hussain: I have 5MHz PZT with 10mm diameter and 0.4mm thickness . I made the backing and matching layers, also I used fluorosilicone rubber for acoustic lens.

#### 2017-06-26 More interest

* @todo put probe on the setup
* @todo set the gain on the AFE using Doj v1.2
* @todo use the GetSuppliersList function to list equipment suppliers
* @done map the /include/community persons on a python map https://peak5390.wordpress.com/2012/12/08/matplotlib-basemap-tutorial-plotting-points-on-a-simple-map/
* @done get stats from hackaday 1,2,GHMurgen,GHechomods,JOH

#### 2017-07-01 More interest

* @done Add contributor map to RPI doc
* @done Add different images from acquisitions to RPI doc
* @done Add the _@kelu include("/include/AddUSSDK.md")_ function to makedoc --> use for the RPI doc (contributor, set costs, intro ... and readmore)
* @done Complete the AddHistory with links for HAD
* @done add benchmark to gitbook resources

#### 2017-07-02 Testing the probe

* Testing the counter for probe turns - see in the [probe readme](/retroATL3/) or see _Using this [arduino code](/retroATL3/data/32u4-ATL3_interface.ino) and  [results are here](/retroATL3/data/20170702-TestATLDuinoTerface.ipynb)_.
* Added the [Pi article](https://kelu124.gitbooks.io/echomods/content/RPI.html) - support from Marc / Thomas ?

#### 2017-07-05 China

* Doing some analysis of the [CN producers](/include/AddCNPCBA.md)
* @todo Add PCBA
* Back in touch with GroupGets
* attiny84 ([pinout](http://42bots.com/wp-content/uploads/2014/01/ATTiny84-ATTiny44-pinout.png)): 12 pins: 
  * Config 1
    * 2 pins pour communiquer avec le RPi (maybe only 1) to address the multiplexer. Send 4bits pour multi 1, Send 4bits pour multi 2 = 1 byte. Reception: 1 byte retour + que des 1. Cf [here](http://www.ernstc.dk/arduino/tinycom.html	)
    * 4 pins pour 1 multiplexer -> leds
    * 4 pins pour l'autre multiplexer -> leds 
    * 1 pin pour DAC
  * Config 2
    * 2 pins pour communiquer
    * 4 pins pour les multiplexer
    * 2 pins pour les enablers
    * 1 pin for VGA :)
* Maybe ATtiny2313  ?

#### 2017-07-08 Doc 'n test

* Received the cable for the probe
  * @done fill in probe if necessary -> need oil in it (see AMZ)
  * @done test probe with oil -> to redo
* @todo Test UHF probe
* @done fill in /wordofcaution.md
* @done integrate thomas remarks in RPi
* @done update ppt_us with links all around
* Templates
  * [ ] AddPitch.md.tpl
  * [x] @done Add TPL list
* Nice patent : https://www.google.com/patents/US4246792

* Updated the first draft of the [tobo.alt](/tobo/alt.tobo/draft.alt.tobo.v0.01pdf)

#### 2017-07-09 ADC boosting

* Awesome paper - how to [boost the ADC](https://www.ncbi.nlm.nih.gov/pubmed/28368803) - https://www.ncbi.nlm.nih.gov/pubmed/28368803
* Testing a counter with the [32u4](/elmo/data/arduiprobe/20170709-Repeats.ipynb) -- see  [data](/elmo/data/arduiprobe/data/)
* @done order tobo.alt 
* @todo board pulser + processing + ADC for RPi
* https://petapixel.com/2013/03/13/the-helsinki-bus-station-theory-finding-your-own-vision-in-photography/ : excellent article on finding your way.

#### 2017-07-14 ADC boosting

* New tester at http://www.usultratek.com/PDF/PicoPulser.pdf
* Testing [double ADCs interleaved](https://github.com/kelu124/echomods/blob/master/elmo/data/20170713-TwoADCs.ipynb)
* Cleaning the RPi: https://raspberrypi.stackexchange.com/questions/4745/how-to-uninstall-x-server-and-desktop-manager-when-running-as-headless-server

#### 2017-07-15 Probe et al

* Testing the [probe + elmo setup: here](/elmo/data20170715-ProbeTest.ipynb)

#### 2017-07-18 Further tests with servo

* [Testing with the servo](/elmo/data/arduiphantom/Readme.md) and [the notebook](/elmo/data/arduiphantom/20170718-Servo.ipynb)
* Power in a [piezo element](https://electronics.stackexchange.com/questions/317873/electrical-power-in-piezoelectric-transducer)
* @todo add some ideas for [the pulser](https://electronics.stackexchange.com/questions/212667/ultrasound-transducer-excitation-frequency-transistor-type?rq=1) to the alt.pulser board
* @todo get orders from Sam CN.

#### 2017-07-21 News from Newcastle

* [Interesting article on synthetic aperture  - PDF](/include/biblio/burckhardt1974.pdf)
* [New article from Neasham - PDF](/include/biblio/10.1109@TBCAS.2017.2695240.pdf) -- some sources for good references
  * Tech insights: using a 12Msps ADC for a 4MHz piezo and a 4 FPS - software limited, using a Voice Coil Motor (VCM -- see "Design and optimization of a voice coil motor with a rotary actuator for an ultrasound scanner," by same author )  for low noise, 15cm deep, 200 lines over 50°, 96V pulses, using synthetic aperture focusing on sig proc -- and they have already been doing in FDA compliant in vivo testing, Table III shows tech specs achieved.
  * Also introduces some _"low-cost devices recently entering the market include the Interson SeeMore probe, the SunBright SUN-806F and the Telemed MicrUs, which can be purchased between $1.5k and $3k."_.
  * [Feasibility of Swept Synthetic Aperture Ultrasound Imaging - PDF](/include/biblio/bottenus2016.pdf)
  * [Design and Optimisation of a Voice Coil Motor (VCM) with a Rotary Actuator for an Ultrasound Scanner - PDF](/include/biblio/smith2015.pdf)

TODOs:

* @todo remove gitbook MD files from the log
* @todo link to files in the log (python)
* @done put back good ino for pulser
* @done quickstart installs and tests (see Charles email)
* @done finish the [Word of Caution MD](/WordOfCaution.md)

#### 2017-07-24 Where is IvanTch

* Trying to find him https://github.com/Ivan-Tch/OpenUltrasound =)
* https://docs.google.com/document/d/1xvLWDbp0x6z0Ft3AsfxjIsLUNsg5smkTcYb1g4WVo5U/edit
* Mechanical sweeping probe image from http://www.mdpi.com/1424-8220/14/11/20825/htm

#### 2017-07-26 GitHub searches

* hv7360 -user:kelu124 -org:ech	open -org:echopenHQ
* ad9273 -user:kelu124 -org:echopen -org:echopenHQ check for FPGA for probe..


#### 2017-07-28 Thinking of an end

Got some [amazing responses to the post on HN](https://news.ycombinator.com/item?id=14869138), held the 1st pos for an hour +, got over 200 ups, that's quite enough =) I guess I'm coming close to an end on this project, and my target would be to try and have a presentable project before Year 2.  The five key milestones:

1. __Outreach__: I have sold 10 kits so far, have ordered 5 sets more to a CN PCBA. Will sell those - and let people choose what they want when they'll want to play with those. I guess I'll have the community Milestone reached when someone provide a significant improvement / publishes thanks to this kit. _Status: 50%_. Bonus point if a unreached continent so far is involved.
2. __Money__: thanks to the small margin on kits, and hackaday prizes, i'm quite [cash neutral](/include/Finance.md) as of today. Having the 5 kits sold would permit financing the acquisition of the unmantled CN probe. _Status: 100%_ Bonus:  trade the chinese probe on leboncoin / ebay.  _Status: 0%_
3. __Product__: I wanted to have a __ultrasound hat__ done. I now have this ADC pHAT done, which can be perfected, but it's quite a win, so a simple 80V monopolar ultrasound board (independant from the motor / multiplexer) could be reached by Nov. _Status: 0%_ Update: could be good to use the [probe head](/loftus/) to do a full portable probe =)
4. __Documentation__: There are a couple of notes here, I'd love to see all of those gathered / processed / put into a braindump. Gitbook is good enough, but lack structure for raw knowledge dump. TODOS include:
  * Listing all docs under YYYYMMDD
  * 
5. __Future__ I'd be keen on having a 8 to 16 elements module prepared, just so to prepare the next gen and passing over of the project. Jan and Ivan to support. _Status: 0%_ Muxing using ATTINY85 ?

Nice to have:
 
* A slack bot? It would be fun to have a supporting bot to answer queries, like "where are the elements benchmarked, how do you process dicom, ..."

#### 2017-08-05 Moving forward towards the board

* Added something about [the S3 probe](/loftus/source/s3/) 

* @done Adding the descs for modules and power needs
* @done Removing double Autogen tags
* @todo Main readme as TPL
* @todo DICOM rest of images

* @todo test some compressed sensing using [golay codes](/include/20170325/PulseCode.pdf) on a single element piezo

#### 2017-08-14 Zach

* Zach's work has [been published](https://www.youngscientistjournal.org/article/development-of-a-portable-and-inexpensive-ultrasound-imaging-device-for-use-in-the-developing-world) on https://www.youngscientistjournal.org/article/development-of-a-portable-and-inexpensive-ultrasound-imaging-device-for-use-in-the-developing-world =)
* Got the probe -- need to open it and explore it =) (or [here](/include/community/Zach/ZTaylor.pdf) in local).

#### 2017-08-17 Some RPi code

Working to get a transducer schema?

* http://www.brl.uiuc.edu/Downloads/bigelow/APPENDIX%20C.PDF
* http://www.biosono.com/PrmtLgd/PrmtLgd.php?id=TrnsRlc
* Add http://datasheet.octopart.com/MD1210DB1-Supertex-datasheet-164548.pdf in bench - theres a RC circuit to simulate a transducer

* Check python scripts from Mark

Documenting pictures:

* https://stackoverflow.com/questions/936937/which-exif-tag-to-store-keyword-tag-for-a-photo  - LocalCaption
* https://photo.stackexchange.com/questions/52515/whats-a-good-exif-metadata-field-to-store-a-general-url-about-photo-topic-conte -- Caption-Abstract/Description // Headline
* https://sno.phy.queensu.ca/~phil/exiftool/TagNames/EXIF.html  -- ImageDescription


#### 2017-08-21 Remaining time

Got 3 months left (see 28/7), let's do... a __MASTER TODO__ !

* __Test board__
   * Get DSO by 10/9
   * Get signals by 30/9
   * See ICs and get a summary by end of oct.
* __CNFab__
   * Get maps
   * Send maps
   * Receive alt.tobo and lite.gobs by 15/9
   * Test those
   * Put them on tindie with ADC pHATs
* __Gob__
   * Start order with EF
   * Benchmark UF
* __atl.tobo.cheap__
   * 31/8: Start design
   * 10/9: Get it to MF
   * 10/10: get it and Test before 20/10
* __Single board__
   * Get alt.tobo.cheap tested
   * Start design by 10/10
   * Get sent to macrofab by 25/10
   * Receive board by 25/11

__More [Raspberry Pi Zero notes](/croaker/notes_RPi0.md)__

#### 2017-08-24 Some more ideas

* Getting a 18650 battery (x2)
* Getting battery board (x2) - board and tofs -- see https://hackspark.fr/fr/electronique/puissance-et-energie/stockage-batteries.html & battery holders
* Touch sensors
* https://hackspark.fr/fr/12mm-domed-push-button-pack.html // https://hackspark.fr/fr/joystick-breakout-module.html // https://hackspark.fr/fr/mini-sliding-switch-dpdt-6-terminals-0-3a-6vdc-2-positions-2mm.html

#### 2017-08-28 Not much time

* not much time, but let's see. The board design is making progress.
    * Basically, need to review the pinout for the RPi Header
* Got the DSO, will do some tests
* Will start investigating a minima with the tobo.alt design
* Image tagging with http://tilloy.net/dev/pyexiv2/tutorial.html

#### 2017-09-02 Making the images better

* Adding metadata to the images
* explore:
    * ImageDescription

#### 2017-09-09 Playing with the probe

* Been starting the [probe teardown page](/include/s3/)
    * Checking the pulses
    * Motor control?
* Finetuning the img metadata
* Need to plan for the oneboard design

#### 2017-09-15 Slow progress

* Need to make some progress on [Uniboard](/include/UniBoard.md)
* Some feedback from Marc, and Felix supposed to come to Paris !
* Trying to master the [probe counter](/include/s3/counter/)
* Need to have a script to edit Images tag
* [Fab](/include/cn_fab/) is making progress on tobo.alt and goblins, gobs form EF coming too!
* Challenge issued to boost GPIO read speed. 12Msps so far on the RPi0 so far ... x2 with [the ADC cape](/elmo/), how fast can it reach?


#### 2017-09-17 Progressing on autodoc

* Adding experiments to the docs
* @todo adding the experiments for within the MD files
* @todo create files for experiments in include (eg in /include/experiments/ ) (using ListOfExperiment )
* Opened a bit more of the S3 probe
* @todo ordered some JST for the probe

#### 2017-09-29 Todo

* @todo test [s3](/include/s3/) outputs w/ JST - and good trigs on DSO203
* @todo feed [s3](/include/s3/) in 5V in motor w/ JST
* @todo 3 experiments w/



=======

uControllers and other stuff
-------


### Croaker

#### Case of Feather WICED
 
* 12 bits ADC
* 150 us acquisition, single channel
* 6 Msps interleaved mode

In 150 us (one line) you will get 6x12x150 = 10800 bits of data. On Wi-Fi speed 54Mb/s it will take 10800/54000000=0.0002s (200us) to send these data.

In practice, we rather see 8Mbit/s, thats 1.2ms to send it. 

#### Case of ESP8266

Lower specs (for dev kit - 1 to 2 image / s OK)

* SPI is 40MHz
* 14 bit
* 2 Msps
* Comm through SPI
* 10ms between lines - 64 lines gives 640ms / image)
* 200us at 2Msps is 400 points is 5600 bits is 700 bytes
* 5600 bits per 10ms is 560,000 bits/s is 70kbytes/s.. should be OK with ESP8266/EMW3165/equivalent ;)

__More [ESP8266 notes](/croaker/notes_ESP8266.md)__

#### Case of Rasberry Zero

__More [Raspberry Pi Zero notes](/croaker/notes_RPi0.md)__

### Tofs

![Cartes](/include/images/600px-Cartes.png)


![Motherboard](/include/images/600px-Motherboard.png)

### Graphing

![mindmap](/include/GraphMyMind.png)

#### April 29th -- initial fill in

* HAD->Murgen
* HAD->AutoFinancement->OpenSourceHardwareContest
* Sofian->Murgen
* Serveur Matthieu->Output Image->Benchmark->Image processing->Jean-Francois
* Image processing->Output Image->Print
* Modules->Tester
* Modules->Transducer
* Mech->BiVi
* echOmods->WoodBox->Arthur
* WoodBox->LogoLaserCut
* Transducer->Jan->2 types to test
* Croaker->STM32F205RG->STM32F205RG->M3
* STM32F205RG->6Msps
* uC->Croaker->TFT Screen
* Croaker->SD Card
* uC->Vlad
* Modules->Alim->Mogaba
* Modules->echOmods
* Modules->HV
* Modules
* Modules->TGC
* Modules->Controler
* uC->Feather Wiced
* uC->Wifi
* uC->EspruinoPico->BiVi
* HAD->Phantoms
* Phantoms->Virginie->HAD
* Phantoms->Static->HAD
* Phantoms->Materials->RP-6400->Latex->Virginie
* Modules->Doc
* Modules->Motherboard
* Documentation->DocBuilder->BiVi
* Documentation->GitAliases
* Documentation->MakeDoc
* Documentation->CreateSchemaBlock->GraphViz
* Wifi->Format->TCP
* Modules->DDS->R-2R
* AG->Strat->AutoFinancement
* Modules->Fab->MacroFab
* Vlad->MacroFab
* DDS->Arduino
* Acquisition->PRU->Vanderbilt->EdgeFlex
* FlyLabs->EdgeFlex
* PRU->Up to 10Msps+
* Acquisition->RedPitaya
* Pedagogie->Aforp->Tao
* Pedagogie->ESIA
* Pedagogie->ENSCachan
* Pedagogie->Isep->Frederic
* Pedagogie->ENS->MichelB
* MichelB->Modules
* Aforp->Apprenti
* Pedagogie->Vanderbilt

#### April 30th

* EdgeFlex->Fab
* ENSCachan->Satie->Constant->Transducer
* Fabs->AutoFinancement

#### April 30th

* Inspiration->MakerFaireParis
* AutoFinancement->Fiverr
* ENS->MichelB

#### May 3rd

* Wifi->ESP8266->ESP32
* ESP8266->ADCSPI->Send
* Wifi->Igor
* Acquisition->Enveloppe->max-hold-reset
* max-hold-reset
* BiVi->LPC810->NE555 du 21eme

#### May 7th

* ADCSPI->Feather Wiced
* ESP8266->Comm2RPi0->RPi0

#### May 24th

* Igor->ESP8266
* RPi0->Oscillo->CA3306
* RPi0->CSI->Camera->ToHack->Hack RPi0 CSI (Camera)
* Igor->Feather Wiced

#### May 25th

* Mech->Mech-athon
* Format->UDP->Broadcast
* Enveloppe->ADL5511

#### May 29th

* ESP8266->ESP8266.ADC->HSPI
* ESP8266.ACD->AD7274

#### May 30th

* Edgeflex->Modules Ready->PiZero->Modules SPI
* Modules Ready->BBB->Modules SPI
* ESP8266->Modules SPI
* ESP8266->Igor->Code
* Igor->PCB
* WICED->KGhosh
* Todo->Comm->An->Nicolas Felix
* Vermon->Nicolas Felix
* Vermon->An
* Comm->Langevinium
* Comm->Tanter
* TODO: Tanter
* TODO: Nicolas Felix
* Comm->P6->V2->FabLab->Voir PCMLab (Jussieu)
* Partenariat->Edgeflex->Revenues
* WICED->Wifi

#### June 7th

* TODO: Hall Of Fame
* Done: DDSTest
* Done: DDSTestWith
* TODO: ProdEdgeFlex
* Sofian->KiCAD->OpenSource
* Virginie->Phantoms
* Murgen->KiCAD
* BlogJanice->OpenSource Gel
* Phantoms->OpenSource Gel->Publis
* OpenSource Gel->Analog Two
* OpenSource->GOSH
* SendMiniCircuits->ProdEdgeFlex->Tests
* ArduinoNano->DDSTest
* DAC->DDSTest->Tests->RPi0

#### June 17th

* Comm->Publication
* Murgen->Caskey->Zach->Todo Merge all doc
* GitHub->Zach->Caskey
* EMW3165->Igor
* HAD->1000$->Matos
* Comm->AutresBlogs->Andre
* DDSTest->AOP

#### June 18th

* NextSteps->Industralisation->Bitmaker
* Industralisation->Vermon->Nicolas F.
* Industralisation->PRS->Find PRS
* TODO: Find PRS

#### June 27th

* NF@V->Conseil
* NF@V->Mecenat
* NF@V->Experts->TI/MAXIM/ANALOG&Al
* NF@V->Expert Normes
* NF@V->IEEE
* Caskey->IEEE

#### June 30th

* HAD->HAD Followers->Gros->BBB Foundation->Financement
* HAD Followers->Gros->Atmel Corporation
* HAD Followers->Individus->anfractuosity->Chris->zymeter
* HAD Followers->Gros->Texas Instruments
* HAD Followers->Gros->TODO Démarcher Gros
* TODO: Démarcher Gros
* Caskey->Partenariats->Gros->Experts
* uC->Liste uC
* Zach->PRU
* Caskey->Vanderbilt

#### July 12th

* NF@V->ContactsNF->FRANCE LIFE IMAGING->MEDICEN-> A. Da Costa->26 Nov 2015
* FRANCE LIFE IMAGING->Aviesan
* FRANCE LIFE IMAGING->Regine T.
* IEEE->IEEE Tours
* FRANCE LIFE IMAGING->Reunion 21 Sept.->IEEE Tours
* ContactsNF->TI/MAXIM/ANALOG&Al->AD->Cedric
* ContactsNF->TI/MAXIM/ANALOG&Al->Microchip->Thierry

#### August 2nd

* NewModules->Hannin
* NewModules->Silent
* NewModules->ToadKiller
* BBB->Baptiste Pierrat->FastPRU->UpTo3Msps


