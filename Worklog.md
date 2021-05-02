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
* Done: A draft for the analog pulser, [Tobo](/retired/tobo/) -- April 20th 2016
* Done: [Automating Documentation](https://github.com/kelu124/echomods/blob/master/makedoc.py)
* Done: Cahier des charges modules - See __Adjusting the specs for a research module__ on this log
* Done: Silkscreening with the murgen-series logo =)
* Cancelled: Module: Detection (Merged in Goblin)
* Cancelled: Imprimer une tof a afficher

## Description

Board 1, aka [Tobo](/retired/tobo/Readme.md):

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

* Following some [design thinking classes](https://www.coursera.org/learn/design-thinking-innovation/home/welcome) for the sake of soft design & fun

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
 

#### 2016-01-22 nd

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
*  [Prez done here](http://wiki.echopen.org/index.php/File:160115_-_murgen_prez.pdf)
*  Awesome boost on github and the wiki
*  adding some to the documentation
 @done : need to get to read more the TAPR and the full license http://www.tapr.org/TAPR_Open_Hardware_License_v1.0.txt
 @done : add CONTRIB.TXT and CHANGES.TXT
*  @cld : failproof OSH

#### 2016-01-24 Datasheets on Murgen

*  added datasheets
*  @done : think about a USB/BT/... output for the board - see matty
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

* Studying microcontrolers... See  [microcontrollers](/retired/croaker/notes_uC.md)

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
* [Tobo](/retired/tobo/Readme.md): the HV/pulser, based on a drafted close to Murgen. 
* [One-Eye](/retired/oneeye/Readme.md): MicroControler - Arduinos
* [Mogaba](/retired/mogaba/Readme.md): Alimentation

Second generation of fun! Learning microcontrolers and advanced simulations

* Croaker: M3/M4 microcontroler 
* Silent : physical emulateur

#### 2016-04-23 Servos

* A stepper based on a servo : https://hackaday.io/project/11224-mechaduino (pour @bivi)

#### 2016-04-24 Maintainers

* Starting to document [Tobo](/retired/tobo/Readme.md)
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
* Next prios : Feather and [ESP8266](/retired/croaker/notes_ESP8266.md)

#### 2016-05-23 Transducers

* Restarting work with transducer and boards makers, Jan and Jerome

#### 2016-05-24 RPi

* Bass inspiration : https://www.youtube.com/watch?v=6ZDTelKz4G0
* Working on [Raspberry Pi Zero notes](/retired/croaker/notes_RPi0.md)
* Updated existing notes on [microcontrollers](/retired/croaker/notes_uC.md) and the [ESP8266](/retired/croaker/notes_ESP8266.md)
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
* [EMW3165](/retired/croaker/notes_EMW3165.md) : "All I see is an under 8 USD STM32F411CE dev board with some wifi gadget" ( http://www.emw3165.com/ ) 

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
* __STM32__: mise a jour du fichier uC avec [un nouveau STM32](http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32f3-series/stm32f334/stm32f334r8.html) dans [Notes uC](/retired/croaker/notes_uC.md)
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

* Read some [on this page](/include/20160814/20160814a.md): got an image from a ATL3 probe, a small metal cube in water.
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
* Doing some thinking about [the servo part](/retired/cletus/) -- should be integrating a feather + screen to help debug the output =)

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
* Getting up to 1Msps with the [Feather](/retired/croaker/feather_tests/2016-09-10-Feather_ADC.md).
* @done: makedoc should include a link checker.. everything starting with `](/` should be tested and checked if existing. That includes images.

#### 2016-09-13 Stand alone echoes visualisation

* Same, for today's date, at [Feather](/retired/croaker/feather_tests/2016-09-10-Feather_ADC.md).

#### 2016-09-14 With a servo

* That is done. Videos to come.
* Missing: sending through UDP.

#### 2016-09-16 Wifi

* Connecting to wifi: done
* Beers @Stalingrad, and chilling =)

#### 2016-09-22 More speed for data acquisition and streaming

* This is getting better. [Read the log on this repo](/retired/croaker/feather_tests/2016-09-10-Feather_ADC.md). [Arduino IDE code is here](/retired/croaker/feather_tests/2ADC2UDP.ino).

#### 2016-09-23 Getting some raw images

* Still this pulser issue, but the signal is correctly stored. [More to download here](/retired/croaker/data/examples/). Captured through UDP streaming.

#### 2016-09-27 Processing the raw images

*  Created the scripts to batch scan-convert and animate the images. [More to see/download here](/retired/croaker/data/examples/)
* Hopes to get the STM32 go faster =)
* Adding the croaker work to the gitbook .. and cleaning some remaining broken links during doc generation.

#### 2016-10-02 VIdeo for hackaday contest

* Done in halong bay

#### 2016-10-20 Meeting and such

* Meeting at HD, milestone with Bitmakers
* USB key that does Pulser, Acquisition : http://www.lecoeur-electronique.net/cariboost_files/us-key_r4_0.pdf

#### 2016-10-21 Update of Tobo

* [The pulser module](/retired/tobo/) used a HV7360, which went from a LFGA to a CABGA. The gerbers were updated accordingly.

#### 2016-10-22 End of week

* Trouve au hasard : "One material with exceptional acoustic properties is TPX (polymethylpentene) [Westlake Plastics Company,  Lenni,  PA]. Pour une sonde à 35MHz, mais ca peut donner des pistes de suppliers. (Ref 10.1109/ULTSYM.2001.991996)
* Article being written at https://gist.github.com/kelu124/af9e3b39b0ba8bed3bde250489635fa6
* Onboarding Pouya =)

Next week:

* @cancelled 6Msps on the [STM32](/retired/croaker/)
* @done Sourcing transducer (in [cletus](/retired/cletus/) )
* @done Sourcing materials + integration makefile par set
* @done Compiler output

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

* Published! [Article: A low-cost, arduino-like dev-kit for single-element ultrasound imaging)[https://arxiv.org/find/all/1/all:+AND+ultrasound+arduino/0/1/0/all/0/1]

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

* Done some tests with a breadboard phantom: [read more here](/retired/croaker/data/20161217/20161217-TestingArduinoAndPhantom.md).
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
* Trying to get some stuff from the arduino, namely to get it work as a server. [Far from being finished, on it](/retired/croaker/feather_tests/2Msps_Server.ino).

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

Given RPi0 capabilities in terms of [GPIOs](/retired/croaker/notes_RPi0.md) - why not push it to 20Msps, 8 bits, for the cape?


#### 2017-03-05 Grmbl netty

Netty isn't nice... but just got my article accepted by JOH !

#### 2017-03-06 Further work

* Updated the [suppliers repo](/retired/cletus/suppliers/Readme.md)
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
* Following up on [6Msps upgrade](/retired/croaker/), [mother board seem OK, silkscreen to do](/doj/), then [Pi1](https://github.com/kelu124/bomanz) and _Pi2_ to follow.
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
* Got some PCB for [Doj, and tested those](/doj/old/20170406-PCBs.md)!

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
* @cancelled dig into [CMOS Ultrasound Transceiver Chip for High-Resolution Ultrasonic Imaging Systems.](https://www.ncbi.nlm.nih.gov/pubmed/23853268)

#### 2017-04-30 Playing with ADC - v2

* https://github.com/kelu124/bomanz/blob/master/20170430-PushingADCLimits.md and at the bottom of it.. the next steps (for tomorrow? ;) )
* from @rbo http://linuxgizmos.com/google-assistant-sdk-dev-preview-brings-voice-agent-to-the-raspberry-pi/
* Bomanz on Hackaday http://hackaday.com/2017/04/30/hackaday-prize-entry-high-speed-sampling-for-the-raspberry-pi/

#### 2017-05-05 Moving forward

* Been testing new iteration of Tobo with new HV7360. Pulser works with the [pulser control](/retired/oneeye/)
* Testing the pulser with the [RPi Control](/retired/tomtom/) see [the notebook](/retired/tomtom/20170507-TomTomTests.ipynb).

#### 2017-05-13 Some new stuff

* PCBs for [Doj V2](/doj/source/v2.0-kicad) - [see what it looks like](/doj/images/doj-v2.png) are ordered
* @done contact Sonopen / microsonix
* Exploring [Underwater Imaging Using a 1 × 16 CMUT Linear Array](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4813887/)
* @done add Felix, Will + Jp, Charles, Md+Afreen
* @done add Visa, possibly Pouya and Thomas as contributors
* @done map interested (green) 
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

* Got the PCBs and [tested them](/doj/old/20170522-DojV2tests.md). Yeayyy, they work! Slight hiccup with the ADC, nothing dramatic though =) Actually, two pins have a double use along with the ADC pins. Dumb me :p

#### 2017-05-29 Testing Doj v2

* Pushing some pics of the [devkit 2.0](/include/devkit2.0/20170529_203924_notes.jpg) - note that this config allows pulse transmit. Pulse from the pulser, receiving through the analog front end.. and acquisition managed by the adc and raspberry.
* Note to self: this config requires a "good" usb power supply. It succeded with a 5V 750mA power supply - but failed from USB.
* @done Add a documentation server
* @done Display IP on the OLED.

#### 2017-06-09 Lots ongoing !

* Got the boards for Bomanz v3 and SMD stuff
* Sold some boards
* @done Need to have a look at this RPI GPIO DMA  - https://github.com/hzeller/rpi-gpio-dma-demo
* @done Include some cletus remarks (sourcing) on gitbook
* @cancelled convert all previous images to dicom
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

* put probe on the setup
* @cancelled set the gain on the AFE using Doj v1.2
* @cancelled use the GetSuppliersList function to list equipment suppliers
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
* @done Add PCBA
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
* @done Test UHF probe
* @done fill in /wordofcaution.md
* @done integrate thomas remarks in RPi
* @done update ppt_us with links all around
* Templates
  * [ ] AddPitch.md.tpl
  * [x] @done Add TPL list
* Nice patent : https://www.google.com/patents/US4246792

* Updated the first draft of the [alt.tbo](/retired/alt.tbo/draft.alt.tobo.v0.01.pdf)

#### 2017-07-09 ADC boosting

* Awesome paper - how to [boost the ADC](https://www.ncbi.nlm.nih.gov/pubmed/28368803) - https://www.ncbi.nlm.nih.gov/pubmed/28368803
* Testing a counter with the [32u4](/elmo/data/arduiprobe/20170709-Repeats.ipynb) -- see  [data](/elmo/data/arduiprobe/data/)
* @done order tobo.alt 
* @done board pulser + processing + ADC for RPi
* https://petapixel.com/2013/03/13/the-helsinki-bus-station-theory-finding-your-own-vision-in-photography/ : excellent article on finding your way.

#### 2017-07-14 ADC boosting

* New tester at http://www.usultratek.com/PDF/PicoPulser.pdf
* Testing [double ADCs interleaved](https://github.com/kelu124/echomods/blob/master/elmo/data/20170713-TwoADCs.ipynb)
* Cleaning the RPi: https://raspberrypi.stackexchange.com/questions/4745/how-to-uninstall-x-server-and-desktop-manager-when-running-as-headless-server

#### 2017-07-15 Probe et al

* Testing the [probe + elmo setup: here](/elmo/data/20170715-ProbeTest.ipynb)

#### 2017-07-18 Further tests with servo

* [Testing with the servo](/elmo/data/arduiphantom/Readme.md) and [the notebook](/elmo/data/arduiphantom/20170718-Servo.ipynb)
* Power in a [piezo element](https://electronics.stackexchange.com/questions/317873/electrical-power-in-piezoelectric-transducer)
* @done add some ideas for [the pulser](https://electronics.stackexchange.com/questions/212667/ultrasound-transducer-excitation-frequency-transistor-type?rq=1) to the alt.pulser board
* @done get orders from Sam CN.

#### 2017-07-21 News from Newcastle

* [Interesting article on synthetic aperture  - PDF](/include/biblio/burckhardt1974.pdf)
* [New article from Neasham - PDF](/include/biblio/10.1109@TBCAS.2017.2695240.pdf) -- some sources for good references
  * Tech insights: using a 12Msps ADC for a 4MHz piezo and a 4 FPS - software limited, using a Voice Coil Motor (VCM -- see "Design and optimization of a voice coil motor with a rotary actuator for an ultrasound scanner," by same author )  for low noise, 15cm deep, 200 lines over 50°, 96V pulses, using synthetic aperture focusing on sig proc -- and they have already been doing in FDA compliant in vivo testing, Table III shows tech specs achieved.
  * Also introduces some _"low-cost devices recently entering the market include the Interson SeeMore probe, the SunBright SUN-806F and the Telemed MicrUs, which can be purchased between $1.5k and $3k."_.
  * [Feasibility of Swept Synthetic Aperture Ultrasound Imaging - PDF](/include/biblio/bottenus2016.pdf)
  * [Design and Optimisation of a Voice Coil Motor (VCM) with a Rotary Actuator for an Ultrasound Scanner - PDF](/include/biblio/smith2015.pdf)

TODOs:

* @done remove gitbook MD files from the log
* @done link to files in the log (python)
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
  * ENDOFYEAR: 15 kits sold, CN not good, MF ongoing (20171217)
2. __Money__: thanks to the small margin on kits, and hackaday prizes, i'm quite [cash neutral](/include/Finance.md) as of today. Having the 5 kits sold would permit financing the acquisition of the unmantled CN probe. _Status: 100%_ Bonus:  trade the chinese probe on leboncoin / ebay.  _Status: 0%_
  * ENDOFYEAR: still waiting (20171217)
3. __Product__: I wanted to have a __ultrasound hat__ done. I now have this ADC pHAT done, which can be perfected, but it's quite a win, so a simple 80V monopolar ultrasound board (independant from the motor / multiplexer) could be reached by Nov. _Status: 0%_ Update: could be good to use the [probe head](/retired/loftus/) to do a full portable probe =)
  * ENDOFYEAR: Ongoing with Matty (20171217)
4. __Documentation__: There are a couple of notes here, I'd love to see all of those gathered / processed / put into a braindump. Gitbook is good enough, but lack structure for raw knowledge dump. TODOS include:
  * Listing all docs under YYYYMMDD
  * ENDOFYEAR: Quite happy, having added experiments (20171217)
5. __Future__ I'd be keen on having a 8 to 16 elements module prepared, just so to prepare the next gen and passing over of the project. Jan and Ivan to support. _Status: 0%_ Muxing using ATTINY85 ?
  * ENDOFYEAR: Shifting to chaotic masks ;) (20171217)

Nice to have:
 
* A slack bot? It would be fun to have a supporting bot to answer queries, like "where are the elements benchmarked, how do you process dicom, ..."

#### 2017-08-05 Moving forward towards the board

* Added something about [the S3 probe](/retired/loftus/source/s3/) 

* @done Adding the descs for modules and power needs
* @done Removing double Autogen tags
* @done Main readme as TPL
* @cancelled DICOM rest of images

* @done test some compressed sensing using [golay codes](/include/20170325/PulseCode.pdf) on a single element piezo

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
   * Receive alt.tbo and lite.gobs by 15/9
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
   * Get alt.tbo.cheap tested
   * Start design by 10/10
   * Get sent to macrofab by 25/10
   * Receive board by 25/11

__More [Raspberry Pi Zero notes](/retired/croaker/notes_RPi0.md)__

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
* @done adding the experiments for within the MD files
* @done create files for experiments in include (eg in [/include/experiments/](/include/AllExpes.md) ) (using ListOfExperiment )
* Opened a bit more of the S3 probe
* Ordered some JST for the probe

#### 2017-09-29 Moving forward with tests

* @fail test [s3](/include/s3/) outputs w/ JST - and good trigs on DSO203
* @done feed [s3](/include/s3/) in 5V in motor w/ JST -> fail
* @done Test Gob
  * Relancer le fab_cn ... error in its capa placement 
* done: test ADCs
* done: test Pulser

#### 2017-09-30 Some experiment

* Done the tests for the pulser  ( 20170930a ) 
* Some additional works for the motor control
* @cld a better bilevel control (4 NOPs period -> PPon, Poff, PNon, PNoff)
* @cld float pins between shots? -> work session on [bilevel.c](/retired/alt.tbo/test/bilevel.c)
* @cld pass license to CC-BY-SA

* @done add some new articles to the new article (all put to bibtex)
  * Some interesting read .. again: 10.1109/ULTSYM.2013.0142 for bimorphs
  * [Article: A flexible multichannel FPGA and PC-Based ultrasound system for medical imaging research: initial phantom experiments](http://www.scielo.br/scielo.php?script=sci_arttext&pid=S2446-47402015000300277) for brazilan students working on a design
  * [Article: PC-BASED ULTRASOUND IMAGING SYSTEM IN A PROBE](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.132.5199&rep=rep1&type=pdf)
  * https://www.intechopen.com/books/ultrasound-imaging/hardware-software-partitioning-of-digital-signal-processing-in-ultrasound-medical-devices-a-case-stu
  * [Article: Development of a Low-Cost Medical Ultrasound Scanner Using a Monostatic Synthetic Aperture](http://ieeexplore.ieee.org/document/7982705/ for this awesome work on a probe)
  * [Article: Effect of frequency characteristic of excitation pulse on lateral spatial resolution in coded ultrasound imaging](http://iopscience.iop.org/article/10.7567/JJAP.56.07JF16/meta)

* Demo mode for clarius : https://www.clarius.me/quickstart/demo-mode/

#### 2017-10-06 Articles on the way

* [UniBoard](/matty/) making progress :)
* Some new articles:
  * [Article: A Deep Learning Approach to Ultrasound Image Recovery](https://infoscience.epfl.ch/record/230991/files/ius2017_sda_preprint.pdf) #CompressedSensing :)
  * [Article: Ultrasound Image Quality Assessment -- A framework for evaluation of clinical image quality](http://orbit.dtu.dk/files/4656580/Hemmsen_2010_SPIE%5B2%5D.pdf)
  * NiftyNet: a deep-learning platform for medical imaging at https://arxiv.org/pdf/1709.03485.pdf

#### 2017-10-21 Holidays soon off

* Loving PoC || GTFO : https://www.alchemistowl.org/pocorgtfo/
* Check : Lattice iCE40UL1K-SWG16 -- http://www.latticesemi.com/Products/FPGAandCPLD/iCE40.aspx (used on https://hackaday.io/project/6592-dipsy ) -- quite a small FPGA !!
* Onboard gyro https://playground.arduino.cc/Main/MPU-6050 ?
* @done _senjak_ 15:07  In Which a PDF is a Git Repository Containing its own Latex Source and a Copy of Itself -- https://github.com/ESultanik/PDFGitPolyglot/blob/master/make_polyglot.sh
* FUp:
  * SENT - https://www.ebay.com/itm/ATL-Access-A-Ultrasound-Probe-LOT-2-/131588905820?hash=item1ea34f5b5c:g:COUAAOSwyQtV3Xkg&autorefresh=true
  * TOBESENT - https://www.ebay.com/itm/ATL-5-0MHz-Access-A-12-7mm-Dia-6cm-FP-Ultrasound-Probe-3238-/291684630810?epid=1258231447&hash=item43e9c2411a:m:mmiDQT-0egKab5ctOAd5igw
* eBay
  * Kretztechnik 
  * https://www.ebay.com/itm/KRETZ-Transducer-NW15C-Sektor-Combison-Ultraschall-Sonde-ultrasound-/152724129257?hash=item238f1145e9:g:3ZIAAOSwB-1Y2YEq
  * IRW77AK
  * S-VRW7-10
  * WAW4/5B -- http://www.ebay.at/itm/KRETZ-WAW4-5b-Sektor-Combison-301-311-310-320-Ultraschall-Sonde-ultrasound-/152724129249?hash=item238f1145e1:g:hVsAAOSwsW9Y2YCF
  * ALOKA : https://www.ebay.com/itm/ALOKA-3-5-MHz-Sector-Transducer-for-SSD-118-240-260-280-633-650-725-/253136353004?hash=item3af01a36ec:g:z~4AAOSwARZXmoUP -- ALOKA SECTOR
  * S-VRW77AK -- small piezos
  * Emisonic 4264
* Businesses
  * #UpAccelerate mscan. Mobile ultrasound device. price 600$. It is a business, but one to benefit maternal health https://t.co/aeogOzmZH3 -- looks like http://mscanug.com/wp-content/uploads/2015/02/pic-5.png
  * https://www.geekwire.com/2017/echonous-announces-35-million-new-funding-mini-ai-driven-ultrasound-devices/


#### 2017-10-23 Back to work again 

* @canceled _senjak_ CAP1188 for touch ?
* LightProbe: A 64-channel programmable ultrasound transducer head with an integrated front-end and a 26.4 Gb/s optical link 10.1109/ISCAS.2017.8050300
* https://doi.org/10.1166/jmihi.2017.2220  FPGA Implementation of Speckle Noise Removal in Real Time Medical Images 

#### 2017-10-27 Back to FPGAs this time 

* https://www.reddit.com/r/cscareerquestions/comments/78rhz7/this_startup_asked_me_to_do_a_project_for_an/ I loled

#### 2017-10-28 News from ther modules and pulser

* DataScience https://jakevdp.github.io/PythonDataScienceHandbook/
* Butterfly http://m.marketwired.com/press-release/first-ultrasound-on-a-chip-receives-broadest-fda-510k-clearance-2238621.htm 2k$

* http://baruch.siach.name/blog/posts/linux_kernel_module_parameters/ (t1, t2, t3, t4) Pon, Pdamp, Pon, pdamp
* http://www.tldp.org/LDP/lkmpg/2.4/html/x354.htm !! excellent 
* https://www.linux.com/learn/kernel-newbie-corner-everything-you-wanted-know-about-module-parameters

* Commands
  * modprobe foo parameter=value
  * modinfo ambassador for params

Sometimes a kernel modules allows setting a parameter at run time. In this case you'll find the parameter under /sys/module/modulename/parameters/, with writable file permissions. The debug parameter of the ambassador module is an example of such a parameter. Set a value to this parameter with a simple echo command:

    echo -n 1 > /sys/module/ambassador/parameters/debug

* http://anons.wiki/
* https://github.com/LappleApple/feedmereadmes/blob/master/README-maturity-model.md


#### 2017-10-29 What next now

Great topic: good feedback from users!

Another topic, got 1 month left before 25/10 (2 full years!), let's update the __MASTER TODO__ !

* __CNFab__
   * Get updated goblins
   * Put them on tindie with ADC pHATs
* __atl.tobo.cheap__
   * Review reason for [pulser issues](/retired/alt.tbo/20171028a/Readme.md) -- possible D2 issue
   * Start macrofab bis.tbo after feedback on D2
* __ADC board__ (cancelled as of 20180401 - gone directly to final board)
   * Trying a 50Msps board.
   * Design start on Nov 1st
   * Order by Nov 20th
   * Receive by December
   * Final tests in Jan
* __Single board (final)__
   * Design start on Nov 1st
   * Design produced by 
   * Order by Nov 20th
   * Receive board by December
   * Test by Jan

#### 2017-11-02 Nice application

* http://electronics360.globalspec.com/article/10074/watch-smartwatches-could-sense-hand-movement-with-ultrasound-imaging
* Butterfly IQ https://news.ycombinator.com/item?id=15588711
* https://techxplore.com/news/2017-10-microchip-d-ultrasound-machines-imaging.html
* http://www.musclesound.com/
* Muscle fatigue assessment http://ieeexplore.ieee.org/document/8008307/?reload=true

#### 2017-11-04 Checking shopping

* Interesting exchanges on slack about glycogen measurements in muscles.

* Ebay: 
  * [Kretz Ultrasound Transducer](/include/ebay/kretz/)  https://www.ebay.com/itm/Kretz-Ultrasound-Transducer-Ultrasound-Probe-with-Warranty/232535663954?hash=item362434a552:g:ypwAAOSwgmJXyGus -- __KRETZ AW145B__ -- _NB on 5th: got it!_
  * [ALT ADR](/include/ebay/atladr/) on https://www.ebay.com/itm/Atl-adr-Ultrasound-Probe/253208770177?hash=item3af46b3681:g:798AAOSw7U5Y-QV3
  * https://www.ebay.com/itm/ATL-ADR-5-5-MHz-7-mm-Ultrasound-Transducer-Probe-for-UM-4-7081/291683083141?hash=item43e9aaa385:g:9R4AAOSw1S9Wf4J4
https://www.ebay.com/itm/Used-ATL-ADR-Ultrasound-Probe-5-5MZh-7mm/253208621125?hash=item3af468f045:g:NcUAAOSwHHFY-QbI
  * or others
     * https://www.ebay.com/itm/ATL-ADR-7-5-MHz-15-mm-Annular-Array-Ultrasound-Probe-Transducer-7078/291683083737?hash=item43e9aaa5d9:g:5BkAAOSw~otWf3fR
  * Kretz 7.5MHzcal Transducer [wnw7.5av] Secteur combison

* __UniBoard__ : No external ram is fast enough with ICE40. Capitalizing on UP5K 1Mb RAM.
  * 48MHz: couple of lines, full speed
  * 128 lines for 130us, 8 bit at 24MHz, 6MHz BP out of 24MHz sampling

* eBay search
    ultrasound probe -beauty -fetal -facial -gel -parking -sheathes -covers -dermabrasion -massager

#### 2017-11-09 a bit of thoughts on fpga

* UP5K does not have icestorm compatibility
* HX8K is BGA
* Remains is HX4K ... and needs additional RAM.
* Nice project: https://shop.trenz-electronic.de/en/TE0876-01-IceZero-with-Lattice-ICE40HX
  * https://folknologylabs.wordpress.com/page/2/
  * https://folknologylabs.wordpress.com/2016/08/03/storm-in-a-pint-pot/
  * This SRAM can be upgraded to 512K x 16
* RPi FPGA/ https://shop.trenz-electronic.de/en/TE0726-03-07S-1C-ZynqBerry-Raspberry-Pi-Form-Faktor-with-Xilinx-Z-7007S-Single-core-512-MB-DDR3L?c=350
* @done solder rest of Pulser
* test the two probes I got

#### 2017-11-11 fpga need to move now

__FPGA__

* Open-source: ICE40 & RPi 
* Perfs: SRAM + HX4K at least: IceZero ? Take the design, throw in 8Mb instead of 4Mb
  * IceZero board design can be reused
* Silkscreening:
  * Keeping a clear markup of the different functions
* ADC: 10 bit, 65Msps
  * 10 bits measures (or pseudo-12 with decimation ? by x3)
  * 6 bits remaining by acq: 2 top tour, Pon, Poff, 2 IOs
* Interact
  * 2 buttons
     * Manual Trig
     * Select mode
  * 4 LEDs
     * Single mode
     * Loop mode
     * Acq (ready: on, data in: flashing)
* Modes:
  * _Single capture_
     * 200us long captures at 65Msps : 208kbits
     * Capacity of close to 35+ captures if needed in RAM
  * _Loop_
     * 130us acq at 24 Msps over 16 bits: 57.6 kbits
     * That's more than 130 lines over a 8000000 bit SRAM 
* Transfer back to RPi through SPI
* Variables (to be stored as a header of the file sent back)
  * Pon length
  * Poff length
  * Tdelay length
  * Tacq
  * RT -- repetition time
  * N acq -- number of acquisition
  * Implicit: 
    * ADC bits used
    * Mode (loop or single)
* Expose: 
  * i2c: min. a OLED screen space kept on board
  * Gain Output
  * Logic (bidirectionally buffered): Trig, Pon, Poff, 2 top tours, 2 extra IOs
  * mini USB for power on
  * 5V and GND pads

ebay
* is Kretz VSW3-5  linear ?
* same for SW4/5B ?

* S-VDW5-8B  for parts ? endoprobe

#### 2017-11-12 fpga go

* Call for clarification
* Open toolchain is Verilog / VHDL / Lattice tools
* 130 lines of 150us at 24Msps on 16 bits is 7488000 bits

* Worked on two experiments: [pulser tests](/retired/alt.tbo/20171111a/Readme.md) and [testing new probe](/retired/alt.tbo/20171112a/Readme.md), [and again, once the probe is refilled](/retired/alt.tbo/20171112b/Readme.md)
* @done 20171111a and 20171112b Readmes

#### 2017-11-18 more veille on fpga

* [Ultrasound Imaging System for Educational Purposes](https://muse.union.edu/2017capstone-barhousy/files/2017/03/presentation-barhoush-2ng41lx.pdf) --- excellent idea
* [Time Gain Control (Compensation) in Ultrasound Applications](http://www.ti.com/lit/an/slaa724/slaa724.pdf)
* [Design and Construction of an ultrasound transmit pulser system for non-destructive testing](http://iopscience.iop.org/article/10.1088/1742-6596/792/1/012055/pdf)
* R&D at http://www.tonsonlabs.com/technologies/

* [Implementation of a Wearable Ultrasound Device for the Overnight Monitoring of Tongue Base Deformation during Obstructive Sleep Apnea Events](http://sci-hub.cc/10.1016/j.ultrasmedbio.2017.04.004)

* http://www.greenteapress.com/thinkbayes/html/thinkbayes001.html for stats

* @done impedance matching -- [see more](/include/impedance/ipm.pdf) -- Butterworth-Van-Dyke  or [here](https://electronics.stackexchange.com/questions/245915/picking-source-resistance-for-impedance-matching). [Tuning Filter](https://i.stack.imgur.com/96XMb.png).

#### 2017-11-20 Some electronics pulser and IMN

* Pulser: http://www.google.ch/patents/US3989963
* Excellents images : https://books.google.fr/books?id=7HQyBwAAQBAJ&pg=PT19&lpg=PT19&dq=by+manual+scanning+was+the+daily+routine,+a+member+of+the+%22salami+club&source=bl&ots=KU4G_lVoaL&sig=P-R_jzRnU1QUotDTlL005dr9ZEQ&hl=fr&sa=X&ved=0ahUKEwi9047M3c3XAhUOmbQKHb4eAXgQ6AEIKjAA#v=onepage&q=by%20manual%20scanning%20was%20the%20daily%20routine%2C%20a%20member%20of%20the%20%22salami%20club&f=false ( see 1.16.c for kretz images)
* Impendance : [see more](/include/impedance/) -- the folder
* imp -> power delivery x9 : Fig5 of https://ac.els-cdn.com/S1875389210001331/1-s2.0-S1875389210001331-main.pdf?_tid=c7792854-ce1c-11e7-8a8c-00000aacb361&acdnat=1511201046_10271c5cae5aabd00a8d4e68d491fc1a
  * 560 pF and Lm=56uH
  * 445-9145-1-ND for 150pF at 200V
* Random: http://www.robertgaskins.com/powerpoint-history/sweating-bullets/gaskins-sweating-bullets-webpdf-isbn-9780985142414.pdf

#### 2017-11-24 IMN at home

* Testing some [electrical impedance matching here](/retired/cletus/IMN/Readme.md)
* Cloud9 on a RPi:
  * https://habilisbest.com/installing-cloud-9-on-your-raspberry-pi
  * https://www.siaris.net/post/cloud9/
* @done list other initiatives
  * https://www.matthewzwaan.com/project/ultrasound
  * https://www.eetindia.co.in/news/article/shrinking-ultrasound-device-parts-to-single-chip
  * Newcastle

* http://imprint-india.org/a-low-cost-portable-super-resolution-ultrasound-scanner
* http://ieeexplore.ieee.org/document/7950710/

#### 2017-11-28 Matty-Senjak board

* Two-year anniversary - FPGA yeay !* 

![](/include/UniBoard/unimatty-2.png)

* Done on experiments!

#### 2017-12-01 New stuff

* After realizing at BiVi that US-SPI is simple... try new HV sources?

#### 2017-12-03 Ongoing up

* Working on a modif on alt.tbo to produce alt.tbo2 (VL)
* Create a HV module (VL) from MAX5025
* @done Having Gob on MF as well?
  *  WB1-6TSL to replace transformer
* Nice black boards btw -- love the style
* Download Matty2 (DP) from UV
  * Push on MF. Tested price: 260$ for all. 
* Limits -- http://www.smbc-comics.com/comics/1510428871-20171111%20(1).png
* https://hackaday.com/2017/11/28/hjwydk-the-journal-our-community-has-been-awaiting/

#### 2017-12-05 News on MacroFab

* Pushing [Elmo v2](/elmo/source/v2/) - with new silkscreen, [Max5025](/include/hv/max5025/), 

#### 2017-12-07 Updates again

* Onboard DDS for impedance calcul ? http://www.analog.com/en/products/rf-microwave/direct-digital-synthesis/ad9830.html#product-overview
* MAX5025 and Alt.tbo v2 - on MF
* @done Elmo v2 / Gob (alt) ongoing work (ODB and transfo issues respectively)


#### 2017-12-09 Illusion in a logo

* @done Alt.tbo2 up on MF
* @done senjak Matty ordered
* @done Gob, Elmov2 at Vlad
* http://blogs.discovermagazine.com/neuroskeptic/2017/12/08/curvature-blindness-illusion/ -- some waves for a logo =)
* https://www.gamasutra.com/blogs/DoctorLudos/20171207/311143/Making_a_Game_Boy_game_in_2017_A_quotSheep_It_Upquot_PostMortem_part_12.php genial !
* https://www.crowdsupply.com/andy-haas/haasoscope

* http://gnarlygrey.atspace.cc/development-platform.html#upduino for FPGA and arduinos =) qui tourne sur un ICE40UP5K/3K-SG48
-- http://gnarlygrey.atspace.cc/downloads/UPDuino%20Programming%20with%20RPi%2020170626.pdf


#### 2017-12-11 Is maturity here

* [Are the good times over for compact ultrasound?](http://www.auntminnie.com/index.aspx?sec=ser&sub=def&pag=dis&ItemID=119120)
* @ushound https://groupgets.com/campaigns/346-audiomoth#details

#### 2017-12-16 Chaotic good

* http://physicsworld.com/cws/article/news/2017/dec/14/ultrasound-imaging-from-a-single-large-sensor by Kruizanga
* [Article: Ultrasound Imaging From A Single Large Sensor](http://advances.sciencemag.org/content/3/12/e1701423) for the original article - or with a [local article](/include/articles/1708.09537.pdf)
* MacroFab costs/prices model is reviewed
* http://shyrobotics.com/2017/12/13/skywalker-prothese-de-main-controlee-ultrasons/ to be used with single large sensors for flat imaging!
* [Article: 8051 microcontroller to FPGA and ADC interface design for high speed parallel processing systems – Application in ultrasound scanners](https://www.researchgate.net/publication/301933773_8051_microcontroller_to_FPGA_and_ADC_interface_design_for_high_speed_parallel_processing_systems_-_Application_in_ultrasound_scanners)
* @done classifier articles with link Article: =)

* @ushound https://wiki.analog.com/resources/tools-software/linux-drivers/iio-adc/ad7766 for ADC, SPU0410LR5H for mems
  * 4 LED (listening, saving, ... ?)
  * 2 buttons (save)
  * SPI : DAC and ADC: 2 LEDS for the CS 
* @ushound: social activism around getting to know our ultrasound environment pollution
* ADMP441 for I2S MEMS?
* SPH0645LM4H-B est i2s
* the AMP may be https://www.hackster.io/fvdbosch/raspberry-pi-zero-airplay-speaker-d99feb -- schematics are here https://github.com/adafruit/Adafruit-PAM8302-Mono-Amplifier-PCB and datasheet https://cdn-shop.adafruit.com/datasheets/PAM8302A.pdf
* http://www.jinci.cn/en/showgoods/866.html

* @senjak https://wiki.lspace.org/mediawiki/Latatian_Phrases ( Vilis Ad Bis Pretii // Si Non Confectus, Non Reficiat // Stercus, Stercus, Stercus, Morituri Sum ) 
  * Nunc Ille Est Magicus  ? 
  * Non Ante Septem Dies Proxima, Squiri 
  * Vilis Ad Bis Pretii 

#### 2017-12-17 Kipple

* [The things we carry // kipple // OSH](http://www.hillarypredko.com/kipple/1-the-things-we-carry/)
* @ushound started again
* app-wise, @ushound -> mailed sergio
* http://www.smbc-comics.com/comics/1513526046-20171217.png

#### 2017-12-27 eink and such

* eink + esp8266 - https://blog.squix.org/wp-content/uploads/2017/10/ESPaper-Setup-Guide.pdf
* macrofab ongoing
* https://gist.github.com/pklaus/5921022 #arduino going at 1 #msps over USB !

#### 2018-01-14 Happy new year

And stuff! Some good todos for this year:
* @done added [experiment from Felix](https://github.com/kelu124/echomods/blob/master/include/experiments/auto/20180103a.md)
* @ongoing better experiments scanning
* @done readding description into experiment files
* @done a page sumarizing the experiments (as in the __Experiments__ page in the gitbook)

Also working on a compilation of best open source projects using ultrasounds -- https://github.com/kelu124/openultrasoundprojects or https://kelu124.github.io/openultrasoundprojects/

Add some fun playing with [ultrasound in public spaces](https://github.com/kelu124/ultrasHound/blob/master/mobile/20180112-ajami.ipynb)

Also expecting delivery of a matty-senjak board soon =) Will defintely need to find a name

#### 2018-01-15 Senjak and stuff

Still getting trouble getting a good name for Senjak, Matty... UnAurIce ? for 1Auris + ice 40 ? Anyhow...

* IceCube2: __need first to create an account__
  * http://hardtechlife.com/installing-lattice-diamond-on-ubuntu-14-04/
  * https://hackaday.io/project/6592-dipsy/log/24272-installing-icecube-2-on-ubuntu-14042-lts
  * http://soerenbnoergaard.dk/project_ice40_archlinux.html
    * pip install apio
    * Install the icestorm tools with:
    * apio install system scons icestorm
    * sudo apt-get install fpga-icestorm yosys arachne-pnr fpga-icestorm-chipdb
  * Official packages:
    * http://www.latticesemi.com/Products/DesignSoftwareAndIP/ProgrammingAndConfigurationSw/Programmer.aspx

* Other: working on a bibtex repo
* Found out [Columbia Open Ultrasound](https://github.com/ColumbiaOpenSourceUltrasound) : just genius. Interesting AFE at https://github.com/ColumbiaOpenSourceUltrasound/Analog_Frontend .

* @done Brainstorm for @senjak information design:
  * Main branch (on GH) - sync'ed from matty folder
    * Presentation (on dmn.org as a static page)
    * Sources
      * Upverter
      * FPGA
      * RPi
    * Experiment examples 
      * Simple Mode-A acquisition 
    * Article GTFO
    * Article HardwareX / arXiv
    * + All In One PDF ? =)
  * doc branch (on doc.dmn.org) -- sync'ed from matty/doc as a gitbook
    * Gitbook
    * Pages created from Experiments
  * DATA files synced (not GH, on data.dmn.org) -- synced from matty/data
 
#### 2018-01-28 Updating Senjak

* Fun with TTGO - interesting full setup with https://fr.aliexpress.com/item/TTGO-TS-v1-0-v1-2-esp32-1-44-1-8-TFT-MicroSD-fente-pour-carte/32847643640.html 
* Removed MattySenjak clock, expecting new
* Bought some ESP32 to play with
* Preparing OSHW ?


#### 2018-02-01 Un0rick clock oki

* Clock is soldered again!

#### 2018-02-02 Flashing Un0rick oki

* Done! With the code, it works. I just need to rmmod ftdi_sio and usbserial =)

#### 2018-02-03 Un0rick and RPi

* Still some issues having SPI work.. let's try through RPi. Been adding the the jupyter to the board.
* Why not have the CS0 on IO4, taht's 

#### 2018-02-13 Un0rick moving good

* [work making progress](/matty/un0log.md) -- DAC working for the gain, Pon and Poff work, setting up the registers work..
* Need to get something else than 0xAA on reading though =)
* un0rick.cc booked -- will be home page / gh-page.
* @done un0rick site to have plenty of stuff
  * shop for stuff (or paypal ?)
  * doc for documentation (from a gitbook)
    * Generated from echomods
    * includes list of datasets
    * includes article
  * data for datasets
  * git links to github
    * gh-page is homepage
      * Just a landing page
    * main is code for fpga / rpi
    * to contain article
    * to contain key doc (generated from echomods?) which will generate gitbook (or contains)
    * all of this in a self contained PDF containing
      * pitch
      * scientific article
      * poc-style
      * some goodies
* BTW, un0rick light could be good! (UP5K, HV7361+MD0100!, no RAM, just pulser, few buttons, ... :) ) -- to be discussed / price checked.

#### 2018-02-18 un0rick deadend
https://kelu124.gitbooks.io/echomods/content/Chapter3/matty.html
Nothing works yet on the MOSI line... strange to read those. Version from 11/02 works still. To be explored!

* On the good side, I had time to test the new Elmo v2 and Alt.tbo v2 boards:
  * [Comparing new and old pulsers](/include/20180216a/Readme.md)
  * [With a new driver for the pulser and ADC](/include/20180217a/Readme.md)


#### 2018-02-25 un0rick moving again good

* Getting [first images](/matty/20180224b/Readme.md) ! Yeayyy =)
* So now, getting to:
  * @done Create matty module 
  * @done Publish first drafts on un0rick GH / GH-pages / gitbook
  * @done create [un0rick page](https://kelu124.gitbooks.io/echomods/content/Chapter3/matty.html) on echomods gitbook
* @done create v2 release once gob.v2 and corrected/working alt.tbo v2 are ready.
  * done testing [elmo v2](/elmo/)

#### 2018-02-27 progress on the ice40 board

* [HV Pulsers work!](/matty/images/hv/PonPoff_test/Readme.md) -- nice damping.
* I got [nice echoes day](/matty/20180224b/Readme.md) before yesterday (oops I mentioned those already)
* Got [images with a probe yesterday](/matty/20180225a/Readme.md)

* @done use [General Design Procedure for Free and Open-Source Hardware for Scientific Equipment](http://www.mdpi.com/2411-9660/2/1/2/htm) as a reference
* nice [5V to 170V booster](https://surfncircuits.com/2018/02/03/optimizing-the-5v-to-170v-nixie-tube-power-supply-design-part-2/) with the [schematics](https://raw.githubusercontent.com/drkmsmithjr/NixiePowerSupply/master/KC_NixieSupply5vTo160v/nixiesupply5vto160vdcmboost-sch.png).

* Get inspiration [from this inspiration](https://qspace.library.queensu.ca/bitstream/handle/1974/6235/Wall_Kieran_A_201012_PhD.pdf?sequence=1&isAllowed=y)

#### 2018-02-28 Documentation and comparisons

* @done compare [old pulser](/retired/alt.tbo/20171111a/20171111-pulses.ipynb) (pulser) and [new acs](/matty/20180224b/20180221b-Client.ipynb) for matty readme
* @done automating finding readmes of experiments
 
#### 2018-03-05 Going to rick

* Iterations for next steps:
  * [Roadmap for the next evolution](/matty/mat2un.md)
  * Phantom in PU to do ? What accoustic impedance?
  * @done for matty [Rip this intro?](https://qspace.library.queensu.ca/bitstream/handle/1974/6235/Wall_Kieran_A_201012_PhD.pdf?sequence=1&isAllowed=y)

* Other stuff: explore ETH
  * https://steemit.com/ethereum/@cryptomancer/ethereum-for-dummies-introducing-the-next-great-technological-leap-forward
  * __CryptoZombies__
  * https://www.ethereum-france.com/les-oracles-lien-entre-la-blockchain-et-le-monde/  
  * http://www.lemagit.fr/conseil/Votre-entreprise-future-oracle-de-Blockchain  
  * https://blockchainhub.net/blockchain-oracles/
  * https://www.ledger.fr/2016/08/31/hardware-pythias-bridging-the-real-world-to-the-blockchain/#.2zeggzh6f
  * https://blog.ethereum.org/2014/07/22/ethereum-and-oracles/
  * https://media.consensys.net/a-visit-to-the-oracle-de9097d38b2f

* @done clean all repos for a v2 release of modules 
  * Elmo : OK!
  * Alt.tbo
  * Gob

#### 2018-03-06 Going to Rick

* Launching matty v2 -- prod version
* Publishing it on [un0rick.cc](http://un0rick.cc)
* Explore USED Bard Site Rite - https://www.youtube.com/watch?v=8iUkeJvSXtE (v3) or https://www.youtube.com/watch?v=qxanLwW8EL8 (v2)	
  * Bard Site Rite 37522 5C-45C 7.5MHz Ultrasound Transducer Probe 68mmFL Dymax 0470
  * http://journal.chestnet.org/article/S0012-3692(15)46601-2/fulltext
  * @done decrypt the connector for the Bard probe

#### 2018-03-08 Cleaning repos

* Release v1.9: echOmods : legacy release
  * clean broken links
* Release v2!
  * @done Script to check IMGs URL matches path
  * @done reorganise
    * keep v2s of elmo, gob, elmo, alt.tbo
    * remove others in 
    * gitbook -> Have a "Legacy" chapter
    * Quickstart : replace pulser by alt.tbo
    * Readme actuel becomes Readme_legacy.md
  * Experiment summary
    * List all experiments in Summary
    * Create summary page
  * Create Full Biblio.md
* [un0rick.cc](http://un0rick.cc) up and running! [Gitbook](http://doc.un0rick.cc) as well as data, doc branches are up too.
* OSHWA too !

#### 2018-03-10 Documentation to come

* [Matty v0.1](/matty/v0.1/) preprod files pushed
* Matty [DAC tests](/matty/20180310a/Readme.md) seem OK
* Create un0rick.cc doc .. seems doxygen supports both VHDL and python, perfect!
  * https://www.stack.nl/~dimitri/doxygen/manual/docblocks.html


#### 2018-03-14 Phantom ideas to get

* Polyurethane-Casting-Resin.html http://www.easycomposites.co.uk/#!/resin-gel-silicone-adhesive/casting-resin/Xencast-PX90-Semi-Flexible-
* Speed of sound in rubber-based materials for ultrasonic phantoms https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5126009/

polymeric materials include neoprene, ethylene propylene diene monomer (EPDM) and polyurethane rubbers

* http://www.easycomposites.co.uk/#!/resin-gel-silicone-adhesive/casting-resin/Xencast-PX30-Soft-Flexible-Polyurethane-Rubber.html
* http://www.ondacorp.com/images/Rubbers.pdf
* http://www.acousticpolymers.co.uk/pages/profile.html
* https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3651250/ or 10.1118/1.4802083

* Loved Nasa: @done add to un0rick

    fow uopeytdeus hesor tpe wonfretuw
    ca amwi et detr
    ip fos zopwyaiod conwe
    ah wousgt Tepan
    afew conseion et mew

ice40 again at https://www.element14.com/community/thread/43876/l/project-icestorm-fully-open-source-fpga-tools-for-lattice-ice40?displayFullThread=true

#### 2018-03-16 Bard probe 1

* Worked on a [bard probe with matty](/include/bard/inside.md)
* [An interesting patent is here](/include/bard/US4399703.pdf) -- found working on the [patent parsin' graph tool](https://github.com/kelu124/ultrasound-patents)
  * The more I glance at it, the more fascinated I become...
  * There is no motor! Just electromagnets =)
    * Then no need for a stepper motor
    * it may be the case that 
  * The signal coming back is an already processed signal!
    * It means the pulse should come from another part of the board... ie another pair of cables. 
      * Black and white? -> 5 ohm between this pair.. why not?
    * What about the other logics?
* Next steps: trying and get the reference manual
* Get full echographs boxes on ebay =)
  * Plug plugs on headers while running

#### 2018-03-20 Updates

* Getting a Bard Site Rite III in the mail soon ? ;)
* Probable supplier for mechanical probe in the pipe [too](/include/cn_mechprob/Readme.md) !

#### 2018-03-21 FPGA tools

* Beginning with FPGA : https://www.mattvenn.net/2017/11/05/beginning-fpga/
* _yosys can use Graphviz to create interactive drawings of its synthesis_ : http://www.clifford.at/yosys/files/yosys_appnote_011_design_investigation.pdf
* https://knielsen.github.io/ice40_viewer/ice40_viewer.html

#### 2018-04-01 back from marrakech

* Back from holidays!
* [Making progress on small probe](/include/cn_mechprob/Readme.md)
* @done change path of images when they have changed
* un0rick / matty v0.1 release! https://github.com/kelu124/un0rick/releases/tag/v0.1
* @cancelled Create detailed pages for the community in the gitbook
* @done Create detailed pages for each probe [I've played with](/include/probes/Readme.md) in the gitbook
* Working on the [bibliography](/include/biblio/bib/CheckBib.ipynb) and reput it in the gitbook
* @done cleaning gitbook and pushing annexes

#### 2018-04-07 Other dentist thoughts

* @done add dp location
* @done listing experiments of others
* getting things straight with MacroFab

#### 2018-04-08 Documentation process

__TODO__ reclean full repo one gob2 and lit.tbo are tested

* @done before reclean full repo, create release "Full Dev Resources" and get corresponding version (v1.9 + hash)!
  * @cancelled : Add Full GitBook PDF to it before
* @done Sort the list of experiments, shortnames in SUMMARY
* @done Community: list the contributors in a page + add the experiment. Individual page to point to experiment.
* @done Page on [documentation](/include/autodoc.md)
* @done Edit [history](https://kelu124.gitbooks.io/echomods/content/Chapter1/history.html) page to add Matty.
* @done Rewrite the Chapters Readme -> "This chapter is dedicated to the brain_dumps "
* @done Do a Doj  (LOW PRIORITY)
* @done Redo a usable alt.tbo (LOW PRIORITY)
* @done Clean Modules list (keep lite.tbo, goblin, cletus, doj, elmo, matty) + add "CNprobe"
  * @cancelled Make 7 clean QuickStarts for remaining modules // copy them on Tindie.
  * @cancelled Get "ShortNames" in JSON
* @done Put alt.tbo, tobo, loftus, tomtom, croaker, retroATL3 and wirephantom in retired modules + add "PU3090" phantoms in retired
* @cancelled Remove sets in doc
* @done Remake homepage in autodoc
* @cancelled Clean obsolete versions in repos

#### 2018-04-15 Documentation process

* Testing goblin, then goblin + lite.pulser [here](/include/20180415a/Readme.md)
* Testing new modules for ADC, lite.pulser, goblin [here](/include/20180415r/Readme.md)


#### 2018-04-28 Back in the game

* [Superb work on the single element imaging here](/include/articles/Fedjajevs_mscthesis_14_09_2016.pdf), or [here](https://repository.tudelft.nl/islandora/object/uuid%3A8784cc2b-10a1-47e7-a87f-ce25062d456f). 
* @done contact the [author](https://repository.tudelft.nl/islandora/object/uuid%3A8784cc2b-10a1-47e7-a87f-ce25062d456f) !
* Interesting [Signostic work](https://patents.google.com/patent/US20100324418) on single element probes
* Interesting [vintage designs](https://patents.google.com/patent/US20030078501A1/en)
* See https://graph-tool.skewed.de/static/doc/index.html for mapping patents =)
* nmap -sP 192.168.0.* This does a simple ping scan in the entire subnet to see which all host's are online. 
* Other: 
  * Ping your broadcast IP address ping 192.168.1.255 (may require -b on Linux)
  * Now type arp -a. You will get the list of all IP addresses on your segment.

#### 2018-05-01 HN number two

* New post on [HackerNews =)](https://news.ycombinator.com/item?id=16950507), reached #2 position.

![](/matty/images/HN_un0rick.png)

* New people on the slack!

#### 2018-05-06 news from shenzen

* a new contributor from shenzen, yeayy! would be interesting  to help develop a connection there
* Interesting project at https://blackmesalabs.wordpress.com/2015/01/17/nanopi-project/
* Updated [the 20180430a experiment](https://github.com/kelu124/echomods/blob/master/include/experiments/auto/20180430a.md). Now the PU30 is a bit more visible (problem was I was loosing info when shifting data to an int..)
* news from Nico's thesis
![](/include/images/etaix.png)

#### 2018-05-10 Mojitos

* After a couple of mojitos a couple of days back, the new [un0rick](http://un0rick.cc) board came out! Can't wait to test it.
* Recommendation of Hurricane for piezos. Let's find out.
* Need to improve the doc for un0rick


#### 2018-05-11 A new article on the way

* @done Resume work on article - [Draft is here](/matty/article/matty_article.md)
* @done contact the guys from https://www.iith.ac.in/~raji/Cpapers/LPFB.pdf (check their prices)
* Need to test different uses.
* https://open-labware.net/projects/flypi/

#### 2018-06-11 un0rick working

* Seems the un0rick bugged because of a reset control
  * TC1270ALVRCTR etait le mauvais composant, il fallait un TC1270ATVRCTR . Le niveau n'etait pas le bon.
* [Working version is here](/matty/prog_flash/v1/eMATTY_un0rick_20180510_RESETsurRPIonly4.bin) - version e.

#### 2018-05-16 improving format system

* @done add Anna and Matthew to users list
* better [acquisition library](/matty/20180516a/Readme.md)

* Interesting [brochure on archive](https://ia601705.us.archive.org/17/items/Hewlett-Packard_Journal_Vol._34_No._10_1983-10_Hewlett-Packard/Hewlett-Packard_Journal_Vol._34_No._10_1983-10_Hewlett-Packard.pdf)
* [Ultrasound tomography](https://archive.org/details/NASA_NTRS_Archive_19780004716)
* [Resolution on imaging](https://lib.dr.iastate.edu/cgi/viewcontent.cgi?article=5139&context=rtd) - 1969

#### 2018-06-16 improving format system

* New [ADC pHAT](http://kghosh.me/img/sdc.img.gz) image (8G)
* Some competition [Ultratek UT350](http://www.usultratek.com/products/usb_ut350.htm)

#### 2018-06-24 Slowing down hu

* Wondering if/why I'm slowing down on producing.. Too many users / too many Q&A to answer?
* Adding [ultrasound pHAT](https://github.com/kelu124/ultrasHound/tree/master/pHAT) to listen to and emit ultrasounds (15-25khz)
  * @done idea for the ultrasound phat : QuietShark (see https://twitter.com/Dymaxion/status/962385327599112193?s=19 )
  * article idea for the un0rick doc: https://gregdavill.com/blog/2018/6/21/boson-camera-project-part-3
* @done Add new un0rick code, and documentation (both FPGA side, FPGA SPI level, Python)
* @done article un0rick article and pics
  * reference to this http://innovations.bmj.com/content/2/2/78
  * other book images

#### 2018-06-25 Or not

* Article: Impressive [Development of a Low-Cost Medical Ultrasound Scanner Using a Monostatic Synthetic Aperture](https://ieeexplore.ieee.org/document/7982705/)
  * I'm a noob at this, but it seems that MFFS uses fixed focus piezos, but MSAS does focusing in the software (hence synthetic aperture) using a piezo of known size. That's an interesting alternative to focused piezos.
  * Some other interesting insights, like using "Quality Assurance for UltraSound (QA4US) software" for image quality assessment, or also the architecture they used (an ARM, 14-bit ADC at 12Msps), or even the fact that the piezo is in direct contact with the skin, or a motor using a Voice Coil Motor.
  * @done add the MSAS principles to the un0rick article
* Module
  * #define PI2 or get_rpi_version
  * https://raspberrypi.stackexchange.com/questions/44858/how-to-transmit-a-binary-bit-stream-from-a-gpio-pin/44882#44882
  *  int rpi_version = LinuxUtilRPI::from(hal.util)->get_rpi_version();

#### 2018-06-26 Random SDR

* SDR for engineers http://www.analog.com/media/en/training-seminars/design-handbooks/Software-Defined-Radio-for-Engineers-2018/SDR4Engineers.pdf
* HDR : https://github.com/adegirmenci/HDR-US
* Updated biblio

#### 2018-07-03 un0led

* un0rick: playing with the I2C OLED screen using https://learn.adafruit.com/ssd1306-oled-displays-with-raspberry-pi-and-beaglebone-black/usage
* http://ivory.idyll.org/blog/2018-how-open-is-too-open.html

#### 2018-07-05 latex

* Article: https://biomedical-engineering-online.biomedcentral.com/articles/10.1186/s12938-018-0512-6
* Very nice article from an eu-funded consortium set of smes https://cordis.europa.eu/docs/publications/1258/125822911-6_en.pdf
* Template for articles ? -> https://ctan.org/tex-archive/macros/latex/contrib/IEEEtran?lang=en for a great latex template
* FFT for ice40 - 	https://github.com/mattvenn/fpga-fft

#### 2018-07-21 TGC calibration


* [Tested TGC and class approach for Matty](https://github.com/kelu124/echomods/blob/master/matty/20180721a/20180721a-pyUn0.ipynb)
* Ongoing work with collecting bibliography
* https://my.ncl.ac.uk/staff/nuconnections/item/low-cost-design-makes-ultrasound-imaging-affordable-to-the-world1

#### 2018-07-21 Contacts 

* @done try and get to artsens

#### 2018-08-05 Phase II

-   Nine Chains to the Moon
-   Pile of notebooks on the desk & Cleaning flat
-   Making progress with benchmarks

#### 2018-08-06 pyUn0 lib

* check https://packaging.python.org/tutorials/packaging-projects/ for testing libs
* Possibly this :
  * https://ajminich.com/2013/06/22/how-to-easily-import-your-own-python-packages/
  * or add a custom path to the lib
  * https://stackoverflow.com/questions/37516579/importing-user-defined-modules-in-python-from-a-directory
  * Interesting [SimpleRick fork](https://hackaday.io/project/160196-simplerick) or see [the image here](/include/community/wmeng/simplerick.png).
* @done ebay Follow up Having a go on babay at a "ATL 720A", and two unspecified 5 and 10MHz probes.
  * 720 for the "ATL MK-300I" .. and 724
  * @done ebay followup on 720, 724, AUSONICS
  * @done document ATL Apogee Ultrasound, ATL ADR 5.5 MHz / 7 mm
* Ultrasound Transducer Probe for UM-4 (7081)

#### 2018-08-11 Other probes

* Tried to do some more work on [steppers](/include/images/kretzaw145ba/20180811b/Readme.md)
* [Done finding echoes on a kretz probe](/include/images/kretzaw145ba/20180811a/Readme.md)

#### 2018-08-12 A nice toshiba teardown

* @done get in touch with this teardown : http://electronicsplayground.blogspot.com/2018/02/toshiba-ultrasound-machine-teardown.html

#### 2018-08-14 128Msps and beyond

* Breaking the [128Msps wall](/include/experiments/auto/20180814a.md)
* Improving the lib, removing some glitches
* remains a glitch being the number of cycles below 8 bits !

#### 2018-08-19 Some hv design

* Proposed by [Tomek](/include/community/tomek/): use a HV9110. " Ref is High Voltage DC/DC Converter for  Supertex Ultrasound Transmitter Demoboards"

#### 2018-08-20 Some shopping

* @done ebay Followup on  the DIASONICS C PROBE FREQUENCY 10 MHZ P/N 100-1071-00 S/N 1466 
* hv check out http://www.analog.com/media/en/technical-documentation/application-notes/an118fb.pdf
* or https://www.maximintegrated.com/en/app-notes/index.mvp/id/1751
  * @done use MAX5025 to test a HV runner ?
  * http://www.analog.com/en/products/lt8710.html
* RPi + ice40 : https://hackaday.io/project/7982-cat-board/log/46117-it-just-keeps-getting-easier

#### 2018-08-20 Got 724A

* Trying to get some connectors
* [Some intel](/include/724A/724A_notes.md) make me think that's a duplex probe for MK300, MK450 or MK600. Preliminary tests show a stepper motor.

#### 2018-08-23 Updated workplan 

* Wait for ATL plug
* Get VHDL code
* Push updated code, including 
* Test probes 
* identify motor + compteurs

#### 2018-08-26 New Matty v1.1

* Got a v1.1 firmware out, for 0 < nCycles < 0xFFFF
* Reviewed [Readme](/Readme.md)
* Progress on the article
* Got a 2GB image fully valid for RPi. Python: Jupyter, Scipy, Numpy, .. all gets on.
* Added some utilities to flash directly the flash.
* Updated [history](/include/AddHistory.md) and [process details](/include/AddDocProcess.md).

#### 2018-08-27 Adding iceprog

* __iceprog mybin.bin__ works well to flash on the un0rick. just plug in the cable, put a jumper on the RPi/FT header, then _iceprog mybin_ and voila =) 

#### 2018-09-12 Desperatly at work

* not a lot of progress..
* un0rick's first batch is sold out!
* Some cheap piezos? https://news.ubc.ca/2018/09/11/could-a-diy-ultrasound-be-in-your-future-ubc-breakthrough-opens-door-to-100-ultrasound-machine/


#### 2018-09-16 Most secure password

* https://mostsecure.pw/: H4!b5at+kWls-8yh4GvQ hahaha
* Congrats to william: https://www.rtl-sdr.com/rtl_ultrasound-using-a-piezoelectric-transducer-with-an-rtl-sdr-to-create-an-ultrasound-imager/ =)
* https://github.com/cliffordwolf/icotools/blob/master/examples/icezero/icezprog.c icezprog
* @done Check for un0rick github badges (counter, pypi overag, doi zenodo, ... )
  * Compteur: http://hits.dwyl.io/wlmeng11/rtl-ultrasound
  * PyPi: https://pypi.org/project/rtl-ultrasound/0.1.0/
  * coverage x% (coveralls.io)
  * DOI Zenodo:
  * readthedocs.io
* [First test with pylint](/matty/20180901a/pyUn0.pylint.report) not the cleanest of codes

#### 2018-09-18 Teardowns

* Geeky! Looking at https://www.youtube.com/watch?v=49D3fhGpb7w
* https://fccid.io/XSB2300A/Internal-Photos/Internal-Photos-2353839


#### 2018-09-30 Teardowns

* How fast times run when you're stuck on a big project..
* Reading more on fpgas
  * https://www.edaplayground.com/ for verilog tests online
  * https://hackaday.com/2018/05/19/parallel-programming-for-fpgas/
  * https://hackaday.com/2018/09/26/learn-verilog-in-your-browser/
  * GB and NES on UP5K https://github.com/daveshah1/up5k-demos
* @done do a un0pHAT - HV7360 or using HV7361 ([price: 7$](https://www.digikey.com/product-detail/en/microchip-technology/HV7361GA-G/HV7361GA-G-ND/6244385) -- see HV7361 Typical Application Circuit on datasheet -- vs 2x (1.87 + 1.68)+1.5 with  MD1210K6-G, and MD0100 TC6320TG, grand total of 8.6$	   ) 

#### 2018-10-06 pHATrick

* hehe thinking about bad puns on the new board. Previously un0pHAT, or liteRick
* [concept](/matty/pHATrick/concept.md) ongoing
  * name made me laugh .. patrick, fat rick, hat trick ?
* Made some progress on the [single sensor imaging article](https://github.com/kelu124/ssus) -- litterature review
* un0rick v1.1 (two channels) ordered. Quite some stress on flash chips, possibly to remove from next iterations
  * No more Winbond flashes!
  * got some by some brokers...
* @done better readmes for un0rick -- https://github.com/matiassingers/awesome-readme
* @done push a python lib for un0rick
* Waiting a un0rick v1.0 to retry some tests
* https://iainews.iai.tv/articles/how-kierkegaards-idea-of-idleness-can-help-us-diagnose-21st-century-busyness-auid-1150
* @done 8bit art for icons and todos
* @done source a  Bion PSI-400 
* writing on [apogee5MHz](/include/images/apogee5MHz/Readme.md) and [apogee10MHz](/include/images/apogee10MHz/Readme.md)
  * got into the 10Mhz, some piezo, and another piezo + motor =)
  * updating [RetroATL3](/retroATL3/Readme.md)

#### 2018-10-14 RPi SPI speed

* https://raspberrypi.stackexchange.com/questions/45607/max-spi-transfers-sec-speed-using-wiringpi
* Seems to top at 1Msps with fast clock
* ADCS747x / AD7476
  * http://www.analog.com/media/en/technical-documentation/data-sheets/ad7476_7477_7478.pdf
  * OP467 + AD711 ?
* Trying new matty on old probes
  * @done try matty on a apogee5MHz once opened
  * @done try matty on a ausonics75 once opened
  * @done try matty on a 724A with connectors

#### 2018-10-28 some ultrasound tests

* http://www.szynalski.com/tone-generator/
* Tests with beacons
  * Beacons https://github.com/kelu124/ultrasHound/tree/master/beacons
  * and results : https://github.com/kelu124/ultrasHound/tree/master/pHAT/20181028b
  * usHound v2.0 in the pipe !

#### 2018-11-25 back from family holiday

* @done [m5stack client for un0rick](/matty/m5stack/Readme.md)
* @done Explain aim on tinyfpga discourse
* [un0rick v1.1 dual SMA](/matty/v1.1/) received
  * @done check why no reset on v1.1
* @done order one phat
* @done Read https://blog.tindie.com/2018/08/secrets-making-successful-product-tindie/
* @done use https://github.com/g2384/VHDLFormatter on MATTY VHDL
* @done check https://github.com/benkrasnow/EL_driver_multi/blob/master/EL_driver_multi_schematic.pdf driver up to 200V
* FPGA at Amazon: https://aws.amazon.com/ec2/instance-types/f1/
* @done on https://pinout.xyz/ for un0rick and  minimatty
* @done http://m.nautil.us/blog/12-mind_bending-perceptual-illusions for illustrations
* check HV supply of http://ezphysics.nchu.edu.tw/prophys/electron/reportdata/EDNpaper/HVDCDCWilliams.pdf
* @done loot badges: https://github.com/bevry/badges

#### 2018-12-10 slowing down

* Close to year since matty was designed !
* https://github.com/goran-mahovlic/ulx3s-PMOD for view of what PMODs should be like 
  * @done to correct MATTY V1.1 revA
* Reviewing a bit of MATTY verilog
* @done command line for pyUn0 following http://www.catb.org/esr/writings/taoup/html/ch10s05.html
* @done add to pyUn0 compressed acquisitions ( jsons of 1 Line, json of 10 lines, 64 Msps, 32Msps)

#### 2018-12-17 Some gadgets

* https://superuser.com/questions/1150562/how-to-connect-to-a-raspberry-pi-zero-to-an-ubuntu-laptop-by-usb/1219319 for usb0 issues
* http://www.circuitbasics.com/raspberry-pi-zero-ethernet-gadget/

auto lo usb0
allow-hotplug usb0
iface usb0 inet static 
address 169.254.97.1
netmask 255.255.255.0
network 169.254.97.0

Bbox-089C716D // mimite2000

* 777 commits!
![](/include/images/777commits.png)

* Tracing table
* New image to come for "goblin", ethernet gadget, vnc enabled, ssh, and others

#### 2018-12-16 UNICODE someone

* https://unicode-table.com/fr/#miscellaneous-mathematical-symbols-a
* sudo avrdude -c arduino -p m328p  -P /dev/ttyUSB0 -U flash:w:grbl.hex  for flashing an hex to an arduino uno (Plotter XY table)

#### 2018-12-16 some Fpga stuff

* Some bins
  * fa6a7560ade6d6b1149b6e78e0de051f  /home/kelu/ultrasound/un0rick/software/MATTY.bin
  * 4c4c1476fe43503b2a32ca39a59b3c51  /home/kelu/ultrasound/echomods/matty/v1.1/MATTY_v1.1a.bin
  * dc9ece10627d97eec40cbe3ed872cf39  /home/kelu/ultrasound/echomods/matty/v1.1/MATTY_V1.1b.bin 
  * 7cbf3d11454ae62d70a5aa8264d74bae  /home/kelu/ultrasound/echomods/matty/v1.01/MATTY_un0rick_20180826.bin 
  * 49ed003fae3a312590fe99a2fa90392c  /home/kelu/ultrasound/echomods/matty/v0.1/MATTY_Proto_v0.1.bin

#### 2019-01-02 Happy new year

* Interactive fiction
  * https://www.ifarchive.org/
  * https://github.com/rossumur/Zorkduino
* https://spun.io/2018/12/15/lessons-from-running-a-small-scale-electronics-factory-in-my-guest-bedroom-part-1-design/
* https://www.smithsonianmag.com/arts-culture/first-time-20-years-copyrighted-works-enter-public-domain-180971016/?preview
* Mezzanine connectors ?
  * https://www.reddit.com/r/FPGA/comments/ab46mk/ice40_mezzanine_style_pcie_board_design_has/
  * https://fmchub.github.io/
* https://www.reddit.com/r/UNOMOD/ : Ultrasonic Neuromodulation (UNOMOD) is a subreddit specifically designed to enable an open and public discussion around the field of stimulating the brain using Ultrasound.

#### 2019-01-04 work again

* Been working on the python lib
* http://bwlampson.site/33-Hints/Acrobat.pdf for Human Interface Design ..
* @done read [Designing Video Game Hardware in Verilog](https://www.amazon.com/Designing-Video-Game-Hardware-Verilog-ebook/dp/B07LD48CTV) for verilog games design
* @done read IF books and [MUSH](http://www.evennia.com/)
  * https://www.amazon.com/IF-Theory-Reader-Adventure-beyond-ebook/dp/B00JHCSU0Y/
  * [Twisty Little Passages: An Approach to Interactive Fiction (The MIT Press)](https://www.amazon.com/Twisty-Little-Passages-Approach-Interactive-ebook/dp/B005363IMS/)
  * [Interactive Fiction: How to Engage Readers and Push the Boundaries of Storytelling](https://www.amazon.com/Interactive-Fiction-Readers-Boundaries-Storytelling-ebook/dp/B00X2OD8MI/)
  * [Writing Interactive Fiction](https://www.amazon.com/Writing-Interactive-Fiction-Deb-Potter-ebook/dp/B01LZTRL5G/ref=pd_sim_351_4?_encoding=UTF8&pd_rd_i=B01LZTRL5G&pd_rd_r=23ed2c5e-1137-11e9-abfe-9d5f2fa07b29&pd_rd_w=sC0jP&pd_rd_wg=0DX0j&pf_rd_p=18bb0b78-4200-49b9-ac91-f141d61a1780&pf_rd_r=B3B1ZPC2FE4GGPDZGCAA&psc=1&refRID=B3B1ZPC2FE4GGPDZGCAA)
   * [IF Archive](https://www.ifarchive.org/) - EB
* @done coverage for pyUn0 lib, including pypi, https://shields.io/#/, [zenodo](https://guides.github.com/activities/citable-code/),...
* [Gitbook gestalt](https://plugins.gitbook.com/plugin/theme-gestalt-enhanced)
* @done sterling: HV7361 / HV7351 SPI logic ?

#### 2019-01-05 Manual for boards

* Reworked documentation
* REtromanual [Basic](http://www.atarimania.com/documents/Let_s_Learn_BASIC.pdf)

#### 2019-01-12 NDT and others

* @done explore NDT with Jorge
* http://www.ireneposch.net/1-bit-textile/ -- awesome work of textile innovation #art
* Starting a new 5 batch of v1.1
* lower power jewellery: http://www.ireneposch.net/linkpin/
* @done un0rick / lit3rick : install an initial delay (after trig)
* MF costs: check how it evolves
* @cancelled EB - ESP32 + ICE40
  * https://www.elektor.fr/esp32-pico-kit-v4 -- https://www.elektor.fr/media/catalog/product/cache/3/thumbnail/9df78eab33525d08d6e5fb8d27136e95/e/s/esp32-pico-kit-dev-board-v4-layout.png
  * add gyro, eink, LEDs, photodiod, IR ?
  * 1 PMOD = 8 signals  means if 24, 3PMOD possible
  * Size: PHAT is 65x30, Business card is 85x50 
  * 80x45 as an objective ? -> 2 PMODs on opposite to RPI connector, then 2 PMODs on sides
  * eINK display for ESP ? Eg ikny phat : 212x104 pixel
  * badgy 2.9" 296x128 pixel
  * TTGO ESP32 2.9"  display
  * Tilt sensor / gyro /  .. ?
  * DEFCON2018 badge httRead more : 
https://www.fpga4fun.com/
for good tutorialsps://www.cio.com.au/slideshow/355919/defcon-badge-unlike-anything-ever-seen/
* Working on the [WVP](/matty/wvp.md)

#### 2019-01-08 Awesome readmes

* READMEs: https://github.com/PharkMillups/beautiful-docs
* AWESOME LISTS : https://github.com/sindresorhus/awesome
* https://github.com/sindresorhus/awesome/blob/master/create-list.md
* https://github.com/sindresorhus/awesome/blob/master/pull_request_template.md
* @done rework echomods page
* @done rework un0rick page (with new logo / gifs / support / ...)
* @done : add options to pyUn0 lib


#### 2019-02-08 Moocs to follow 

* @done follow the specialisation from beg of march  ? https://www.coursera.org/specializations/data-science-python
* https://github.com/coursera-dl/coursera-dl
* fun https://blog.floydhub.com/instagram-street-art/


#### 2019-02-13 Elementary Basic as Chronicled by John H Watson

* https://github.com/zacharyvoase/humanhash
* https://www.abebooks.com/servlet/SearchResults?isbn=9780394707891&n=100121503&cm_sp=mbc-_-ISBN-_-used
  * @done [include the book](https://www.abebooks.com/servlet/SearchResults?isbn=9780394707891&n=100121503&cm_sp=mbc-_-ISBN-_-used) as an insipration for lit3rick ?

#### 2019-02-15 Moar piezos 

* abil
  * https://www.alibaba.com/product-detail/GOWORLD-submersible-piezoelectric-underwater-immersible-ultrasonic_60696546066.html?spm=a2700.8592591.0.0.fcd810a9Lk6hky
* Jorge
  * https://www.alibaba.com/product-detail/NDT-Straight-Angle-Beam-transducer-sensors_60752888953.html?spm=a2700.7724838.2017115.198.12067c84XcXzww
  * https://www.alibaba.com/product-detail/yushi-PT-12-probe-ndt-ultrasonic_60557426233.html?spm=a2700.7724838.2017115.222.12067c84XcXzww
* @done prepare a page for NDT piezos.. the same way there is one for probes.. or on same ?

#### 2019-02-17 lit3rick interfacing

* https://forum.mystorm.uk/t/raspberry-pi-zero-connection/393/21
* icezprog : https://github.com/cliffordwolf/icotools/issues/3 and some customising

#### 2019-02-24 Rework on todos

* @done lit3rick vF : add rounded edges, connections on other pins from the board for flash CS, passer all IOs sur le header RPI, cacher les SCK du controle HV et back de la carte: passer un header go-through.
* UP5K flashing
  * UP5K RGB: https://github.com/cliffordwolf/icestorm/tree/master/examples/up5k_rgb
  * Upload a FPGA ice40 bitstream via curl using a ESP32 in arduino  : https://github.com/kelu124/ice40_esp32_bitstream_upload 
  * Why not through a M5STACK ? 



#### 2019-02-26 First bin on up5k

* Yeayyy using an [esp32 with the lit3rick flash issue](https://github.com/kelu124/echomods/tree/master/matty/20190226a)

#### 2019-02-27 IP and IA

* Search for: neural networks "derivative works" of datasets
* [Lex Fridman](https://twitter.com/lexfridman/status/1096052394453098502) on Twitter: If a neural network generates an image, who owns the copyright? The owner of the dataset that the net was trained on? The designer of the network architecture? The person running the code? Or... the AI system itself?
* @done echomods: Rewrite landing page echomods
* @done include on echomods readme : Support paragraph as in https://github.com/pi-hole/pi-hole

#### 2019-03-18 Random stuff

* @done @toorder hv9150db1 - LED drivers (MAX?) - SMAs
* @tocheck 
  * US stuff: https://www.microchip.com/stellent/groups/analog_sg/documents/devicedoc/cn571283.pdf
  * @done [#NSA1166 sourcing](https://www.jameco.com/webapp/wcs/stores/servlet/ProductDisplay?storeId=10001&productId=2210976&catalogId=10001&langId=-1&CID=octopart)
  * HV : http://ww1.microchip.com/downloads/en/DeviceDoc/20005689A.pdf
* @done backpack for #NSA1166
  * https://www.nxp.com/docs/en/data-sheet/SC18IS602B.pdf - I2C to SPI: 2.41€ 568-13691-1-ND  #NSA1166
  * LED driver : MAX7219   : 9€ - MAX7219CWG+-ND : ordered for tests #NSA1166	
* Veille ebay: TSA1605A, NSM1416, HP5082-7415, siemens DL1416
* @cancelled better landing page:
  - Include LOGO & TAGS
  - Include badges
  - Better index page as follows
  - A. Intro
  - B. List of previous projects
  - C. Summary here
  - List of experiences
  - List of modules
  - Single sentence with list of probes and link to those
  - D. TODOs 
  - E. LINKS
  - Biblio, articles, list of resources, ...
  - Tindie, slack, Community
  - F. DISC/LICENSE

Other pages under /include/worklog/
- Source articles : @article
- Other articles ? Add all sentences with hastag, remove it + link, strip, add.
- Source bibliographie from biblio

#### 2019-03-19 Random stuff II

* https://medium.freecodecamp.org/the-easy-way-to-set-up-docker-on-a-raspberry-pi-7d24ced073ef
* Add: LM96511 : http://dx.doi.org/10.1590/2446-4740.0700 -> MD2131  --> AFE5805   -->  ?
* https://github.com/Wookai/paper-tips-and-tricks
* https://www.raspberrypi.org/forums/viewtopic.php?t=186435 for RPI and GPIO and SP
  * sudo gpio mode 14 alt0 (itoo with 12 and 13 to reset SPI pins to original function)
* +80V and -80V from 8V, using HV9150 and a MAX1846
 
#### 2019-03-24 Still need to work more

* @done first shots with lit3rick
* @done harmonize between lit3rick, pHATrick, minie, minny
* @done receive lomos and test for NDTs

#### 2019-04-07 Beginning of port to lit3rick

* [First experiment](/matty/20190404a) - blinky on C1 to C3 OK, HILO..not.
* Moar articles to the biblio
* [New DC/DC boosts?](https://fr.farnell.com/MarketingProductList?CMP=e-email-fix-Promo-EU-210319-Traco&orderCode=2854982,2854980,2854986,2854979,2854988,2854984,2854989,2854985,2854998,2854995,2854981,2854974,2854997,2854991,2854993,2854975,2854996,2854978,2854990,2854987,2854992,2854972,2854977,2854983,2854994,2854976,2854973&mkt_tok=eyJpIjoiWkdWa1kySmhZbUptTm1SaSIsInQiOiJ3RnhkMkhJaTdTWVdHQWEwMVAwTUlja1pGNklabDhxWVZWYW1yK3BqakVwYW5ybVwvKzc3a29ZOVhcL0lZOXcyU1NnSzF1XC9MNVlqbVBzTjhES2w5b3lRZmlERGdobFZMa3RZUmFVK0QySEJITUlMUFlyelpLMUNVbTFcL2JoODYyVEwifQ%3D%3D)
* https://github.com/Wookai/paper-tips-and-tricks
* https://www.raspberrypi.org/forums/viewtopic.php?t=186435 for RPI and GPIO and SPI
* Verilog DSP:
  * http://zipcpu.com/projects.html
  * http://www.spiral.net/hardware/filter.html

#### 2019-04-03 Time flies

* Not enough time to work!
* OSS in companies https://spiceprogram.org/assets/docs/Futurice-Companys_Guide_To_Open_Source_And_Social_Impact.pdf
* need updating lit3rick to v1.4
  * Round edges
  * change ADC for Matty old one
  * i2c thermometer
  * remove header for SPI for voltages
  * change flash to winbond
  
#### 2019-06-11 Looooong time

* Still working on minie bin's
* lots of links to record
* Pics old america: http://www.american-pictures.com/english/book/American%20Pictures-small-size.pdf
* lit3 update
  * update flash
  * cut corners
  * MCP9808 for temperature onboard
  * filtre evacuation d'energie entre pGA et ADC
  * passer en 12 bits ? 

#### 2019-06-11 Air Quality rants 

* Thanks Hackolite for putting my brain on this =)
  *  https://www.rci.fm/infos/risques-naturels/une-partie-de-la-population-evacuee-terre-de-bas-en-raison-des-sargasses 
  * ESP32, uFL, uSMA,  VDD controled via pins, ...
  * https://lastminuteengineers.com/esp32-sleep-modes-power-consumption/
  * air quality ?

Boards:
* https://www.sparkfun.com/products/retired/14785 
* https://pycom.io/product/lopy4/ 
* http://wiki.seeedstudio.com/Grove-Gas_Sensor-MQ5/
 
Sensor
* DS : https://www.parallax.com/sites/default/files/downloads/605-00009-MQ-5-Datasheet.pdf
* https://www.waveshare.com/mq-5-gas-sensor.htm 
* BME680 https://www.hackster.io/xxlukas84/bme680-gy-mcu680v1-indoor-air-quality-meter-901d02 

Sleep:
* https://www.hackster.io/Tiobel/esp8266-solar-weather-station-1ea3ec 
* https://openhomeautomation.net/esp8266-battery 

AA rechargeable ?
* https://hackaday.com/2017/12/03/minimizing-esp8266-battery-drain/

Battery sensing: https://github.com/rlogiacco/BatterySense  + a p-channel MOSFET Q1, a PNP transistor Q2


#### 2019-06-15 VGA and k210

* Would be fun to have a simple ACQ + display setup in VGA of a 120us line on a 640x480 display
  * https://timetoexplore.net/blog/video-timings-vga-720p-1080p
  * Check with uF
    * Availability of IOs for VGA on a lit3
* Video processing ?
  * k210 for https://www.seeedstudio.com/Sipeed-MAix-BiT-for-RISC-V-AI-IoT-p-2872.html for video fun
* Working with cheatsheets - https://www.federaltimes.com/opinions/2019/04/18/dear-bureaucrat-how-can-i-work-with-and-around-my-agencys-useless-computer-system/
* Holidays: 
  * Scilly Isles 
  * Ethiopia
  * Corfou
  * Argentina : longtemps =)
  * CAN / FXH / ...

#### 2019-08-30 FFT and ice40
 
* Summer time and deconnection !
* some progress on lit3
  * getting help form @ico_TC : https://twitter.com/ico_TC/status/1165699274652475392
  * going back to UW, checking with Farad too.
  * Need to stop bleeding resources ;)
  * Need to fix thermometer
* Gathering some signal processing on fpgas 
  * https://github.com/mattvenn/fpga-fft/blob/serial/docs/fpga_usage.md

#### 2019-10-26 Some lit3 progress 

* Good progress, stupid capa was in the way on ADC clock. Now acquisitions seem more okay:
  * [here some good experiment](https://github.com/kelu124/echomods/tree/master/matty/20191023a)
* @done updates on new pHAT
  * remove this capa, remove i2c pullups for the thermometers (that was cost 5$ ! :/ )
  * connecter le ice40 au i2c rpi 
  * pouvoir connecter des ios sur l'uart du rpi 
  * router les gpio daughter existantes plutôt sur les pins pcm du rpi pour un jour essayer de sortir des données en i2s (GPIO26, 20, 21, 18)
  * du coup, mettre possiblement les Pulse controls sur des GPIOs non spécifiques comme GPIO05, 06, 13, 19.
  * Niveau header RPi, on peut connecter les SPI_EXT MISO / CS du coup.
  * Use 5 first bytes of a read to store the bin number / board ID ?
* Need to make progress on this RTL-SDR for ultrasound ;)
* @done find the right jekyll theme to leave gitbook
  * see https://help.github.com/en/github/working-with-github-pages/adding-a-theme-to-your-github-pages-site-using-jekyll
  * https://pmarsceill.github.io/just-the-docs/ seem to fit the bill =)

#### 2019-10-27 Again lit3 progress 

* Dynamic DAC [seems better](https://github.com/kelu124/echomods/tree/master/matty/20191027a) - however some IOs are off.
* CLosely here, and then some: hardware finetuning (TMP and ADC C at minimum)



#### 2019-11-24 10km Paris Centre

* Ran again 10km
* lit3rick on final form to be delivered by 2/12.
* Andrew for some symbiflow support ? DFT + i2s ?
* Got the sw45b probe off. Interesting designs.
* @done hack the diasonics heads.
* Ported the pyUn0 for un0rick to python3 .. yeay. Thanks to Fab's pull request.
* Awesome SAO: https://hackaday.io/project/164346-andxor-dc27-badge/log/165849-dc27-doom-sao-hurt-me-plenty
* @cancelled: SAO on up5K: https://github.com/ANDnXOR/sao-reference-designs
  * RGB's
  * USB
  * 2 GPIOs: for what ?
  * mini OLED ?
  * SD connector
  * mini MEMS microphone
  * touchpad

#### 2019-12-06 St Niklaus

* lit3 received, doesn't burn. yet. icoprog can flash the flash. but fpga won't boot from it.
* Connections seem OK
  * icebreaker-sch.pdf says the connections are fine
* possibly need to make clean icoprog
* or to swap IOs for programming, while 
* beware, for flash programming, SPI_SS needs to be kept floating high. Floating.
* @done keep an eye on "BRUEL KJAER ULTRASOUND" =)

#### 2019-12-12 Article ongoing

* The article for the conf is quite ready. Thanks to William, Carla, Jorge.
* GE amongst my clients !
* @cancelled analyse protoelectronics (cf Leonie) for short runs -- http://protoelectronique.com/

#### 2019-12-14 US Badge 

* @cancelled a small US badge see [SAO DOOM]
  * 8x8 LED matrix + driver (max7219 // IS31FL3728 (1x8x8) / 31FL3736 pr 12x8, including breathing - QFN40 / IS31FL3731, 2x8x8, QFN28) 
  * [i2c simulated EEPROM](https://github.com/ANDnXOR/sao-reference-designs)
  * MEMS loudspeaker
  * US microphone
  * SAO 2x3 - [V1.69bis standard](https://hackaday.com/2019/03/20/introducing-the-shitty-add-on-v1-69bis-standard/)
  * USB-C
  * FTDI
  * FLASH
  * UP5K
  * Breakout of remaining IOs + SPI / I2C
* @todo PMODs US:
  * 2x8 : 10bits+1 ADC, MOSI, SCK, SS1, SS2, HILO (ADC, DAC TGC, HILO, ..) based on AD8332
  * 1x8 : Trig, HVP, HVN, PDAMP, i2c, i2c, EN, IO

#### 2019-12-17 Holidays planning

* @done use the [driver](https://www.amazon.fr/gp/product/B0798JCY93/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
  * test on several probes
  * get driver from aniss
* test with BLDC on some probes
* @done redo probes sheets
  * Have all in one sheets
  * teardown subpart
  * experiment subpart
  * others ?
* Thinking of the un0rick website.. have subdomains like experiments, probes, ... for general aspects from echomods ?
* @cancelled redo the geography part.. using geopandas ?


#### 2019-12-31 Last of the year

Ultrasound stuff
* @done integrated mouse optics in the article, from "A Free-Hand System of the High-Frequency Single Element Ultrasound Transducer for Skin Imaging"
* @done my objectives at https://github.com/kelu124/un0rick/blob/gh-pages/partners.md
* MUX
  * https://raspberrypi.stackexchange.com/questions/80221/using-pythons-rpi-gpio-library-to-manually-toggle-spi-chip-select-is-this-ok
  * https://www.maximintegrated.com/en/products/analog/analog-switches-multiplexers/MAX14866.html
* @todo Documentation - update for lit3 once it is ready, with http://2012.oshwa.org/files/2012/07/Wozniak-OHS2012-Final.pdf, http://2011.oshwa.org/files/2011/09/Wozniak-OHS2011.pdf, and https://cdn-blog.adafruit.com/uploads/2011/09/w0z-OHS2011-v1.pdf
* Motors
  * DRV8313, L6234
  * Brushless DC (BLDC) motor with Arduino – Part 2. Circuit and ...
  * SN754410NE
* FFT at https://github.com/mattvenn/fpga-fft
* AFE5801 on a PMOD ? + MAX14806 ? 
* @done : Analyse de la compétition (lecoeur, www.lecoeur-electronique.net/, https://www.industrie-techno.com/article/des-ultrasons-pour-controler-les-revetements-metalliques.54136 (siderus), https://ndt-testing.org/our-services/ultrasonic-testing-pulse-echo-method/, https://www.nde-ed.org/EducationResources/CommunityCollege/Ultrasonics/Introduction/description.htm , https://www.ndtclassroom.com/blog/2018/1/23/ultrasonic-testing-pulse-echo-technique https://ndtvendor.com/categories/69-usb-instruments/364-pciut3100-all-in-one/  https://ndtvendor.com/categories/69-usb-instruments/365-compact-pulser/ http://eurosonic.com/en/products/ut-solutions/tfl-110.html http://www.usultratek.com/products/picopulser.htm  http://www.ultrasonic.de/index.php http://tecnatom-ndt.com/product/ultrasonic/sonia-fprhf1/ http://www.mec-ndt.co/ndt_products_desc?code=97 https://www.insight-ndt.com/ultrasonic/8channel.html https://ndtsupply.com/dakota-ultrasonics-pvx-1.html )
* @done documentation ghpage to update, https://help.github.com/en/articles/adding-a-jekyll-theme-to-your-github-pages-site
* @done encode lib in npz : https://stackoverflow.com/questions/11511705/base64-encode-a-zip-file-in-python and check dependences with https://poetry.eustace.io/
* @done up5k update - https://blog.idorobots.org/entries/upduino-fpga-tutorial.html for the refs (includes block RAM, SB_SPRAM256KA, but i2c and SPI too (SB_SPI  and SB_I2C)) -- see refs at https://www.latticesemi.com/~/media/LatticeSemi/Documents/TechnicalBriefs/SBTICETechnologyLibrary201608.pdf 

Others
* https://feeding.cloud.geek.nz/posts/encoding-wifi-access-point-passwords-qr-code/   qrcode wifi
* @done get a spidriver https://www.crowdsupply.com/excamera/spidriver

SAO:
* MEMS : SPH0641LU4H-1 (PDM) et IS31FL3728 pr 8x8 en i2c
* icebling: https://electronut.in/ice-bling-making-led-earrings-with-an-fpga/ 

#### 2020-01-11 Silent is back

* @done Repushing some silent experiment - using it as a benchmark for lit3rick and un0rick boards
* @done Need to repush libpyUn0.
* @donetodo get somes boxes to sort VNA, piezos, attiny's stuff
* @cancelled SAO for Belgrade !
  * SAO: FT232RQ - https://learn.adafruit.com/programming-spi-flash-prom-with-an-ft232h-breakout/overview
  * upduino Flash - ice40 connection

#### 2020-01-12 Yeay on vit3lite

* FFT generator : https://zipcpu.com/dsp/2018/10/02/fft.html
* Corresponding : https://github.com/ZipCPU/dblclockfft

#### 2020-01-18 MF and short

* Manuf confirmed a LDO was rotated 90degrees. Means tests on lit3rick v1.3 can now be done. 
* @done silkscreen v1.3 to be updated.
* daugther board on esp32 m5stack for viz ? 
* @todo get https://github.com/tobozo/M5Stack-SD-Updater to add bins
  * to flash
  * to run tests
  * to do single acqs and details
  * to stream i2s
* test INMP441 ?
* SAO ideas: apa102 LEDs ( WS2812B-2020 also, 2x2mm)
  * see https://www.sparkfun.com/products/15047 - SparkFun LuMini LED Matrix
* @done lit3rick examples : complilation : https://github.com/FPGAwars/apio-examples/tree/master/iCE40-UP5K/
  * https://github.com/mmicko/fpga101-workshop for LED, button, https://github.com/mmicko/fpga101-workshop/tree/master/tutorials/12-RiscV

#### 2020-01-26 Streamlit fun

* @done explore bivi's https://github.com/streamlit/streamlit and https://github.com/samuelhwilliams/Eel
  * https://towardsdatascience.com/quickly-build-and-deploy-an-application-with-streamlit-988ca08c7e83
* @SAOLIT : ATtiny861A  / ATtiny84A ?

#### 2020-02-15 Nothing new

Having fun with StyleGans
* StyleGan: https://colab.research.google.com/drive/1ShgW6wohEFQtqs_znMna3dzrcVoABKIH#forceEdit=true&sandboxMode=true&scrollTo=rYdsgv4i6YPl
* https://blog.adafruit.com/2020/02/10/combining-ai-tools-to-create-new-beetles-with-gans-artificialintelligence-machinelearning-colab-stylegan-runwayml-cunicode/
* https://twitter.com/_pitscher/status/1228476795122593793

#### 2020-02-19 More GANs

More GAN
* https://hyperallergic.com/541381/over-150000-botanical-illustrations-enter-the-public-domain/
* https://www.cunicode.com/works/confusing-coleopterists 
* https://news.ycombinator.com/item?id=21934247
* Trained: https://open-app.runwayml.com/?model=cunicode%2Fconfusing_coleopterists 
* https://makersplace.com/cunicode/binasu-1-of-1-5598/
  
#### 2020-03-21 More GANs

* [First experiment from a while](/matty/20200321a/Readme.md) testing pulse width
* Minie v1.4 (argh already??)
  * [x] Connect i2s to IOs
  * [x] Remove onboard HV generations
  * [ ] Connect TopTurns to IOs and remove TopTurn SPIEXT/HV/Header - keep 4x2 through-header with ( 5V, 2xi2c, HV_EN, GND, 3.3V HV+, HV- -- HVp close to 5V, HVn to GND ) 
  * [x] Connect HILO to free Rpi header
  * [x] Remove TopTurn protection
  * [x] Move TopTurns IOs Rpi Header
  * [ ] Do buttons need pullups, or FPGA has internal pullups ? Or can they be on
  * [ ] Rappel DCLK on ADC ?
  * [ ] Remove ADC online footprint for capa
  * [ ] Remove footprints for I2C pullups

General use IOs: 

* 2xBtn : Bt1,Bt2
* 4xi2s : (already D1,D2 in)


#### 2020-03-23 i2s on rpi4

* check https://www.raspberrypi.org/forums/viewtopic.php?t=8496&start=900
* i2s on RPi4 - fe203000.i2s
* https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout/raspberry-pi-wiring-and-test#

#### 2020-03-25 i2s seems to need to be RPi-mastered

* curl https://get.pimoroni.com/phatdac | bash
  * https://learn.pimoroni.com/tutorial/phat/raspberry-pi-phat-dac-install
* rpi-i2s-audio
  * echo 'my_loader' | sudo tee --append /etc/modules > /dev/null
* Need to have a i2s master on RPi
  * https://github.com/PaulCreaser/rpi-i2s-audio.git
  * sudo rmmod snd_soc_hifiberry_dacplus
  * sudo rmmod clk_hifiberry_dacpro
* Others
  * https://github.com/AkiyukiOkayasu/RaspberryPi_I2S_Slave
  * https://github.com/taylorxv/raspberry-pi-i2s-driver

I send 2 channels. Into one channel always 0x3F into second channel 0x29. 0x7C is shifted byt 2 bits value 0x29F3. 

#### 2020-03-28 Speccing motherboard

##### Getting a motherboard for the minie board

* Headers
  * header for the card
  * 2x header for RPi
  * header for i2s
  * header for SPI, CS1, CS2
  * header to feed in HV
  * duplicated header to have HV on separate daugther board
  * place for VGA output (based on fpga outputs) [see refs](https://forum.arduino.cc/index.php?topic=320238.0) - 3 pins: RGB + H/V-SYNC (or R for [monochrome here](http://www.xess.com/blog/vga-the-rest-of-the-story/)
* Pullups
  * spare space for solder-though pullups on i2c lines
* Logic
  * LEDs for PpHV, PnHV, PDamp, HILO
  * Deported buttons for ButTrig, ButUser

##### Other cards

* Separate small card
  * Preamp path, MD0100 +Preamp design (+ filter) for 19dB
  * Impedance adaptation

* Separate HV card
  * Same footprint as HV setup -> [2.54mm distance should be ok](https://www.cirris.com/learning-center/calculators/50-high-voltage-arc-gap-calculator?)

##### Tagging wav files

Tagging wav files? https://pypi.org/project/tinytag/

#### 2020-04-01 Speccing small-motherboard

* Daughterboard:
  * HV-source
  * USB : FT2232H - FTDI (SPI - https://www.ftdichip.com/Support/Documents/AppNotes/AN_114_FTDI_Hi_Speed_USB_To_SPI_Example.pdf ) - connecting I2C, SPI, one on each bus. Getting other IOs linked too (HILO, CDONE, RESET, ...)
  * VGA output

#### 2020-04-02 433 plus SDR

* Hehe interesting https://ensiwiki.ensimag.fr/index.php?title=RTL_SDR_et_retro-ing%C3%A9nierie

#### 2020-04-11 MS3 on i2s

* Yeayyy finally pushed MS3 for i2s on https://github.com/kelu124/vit3rick/ . Missing the filtering part but that should be fine - thanks Andrew and Bogdan.

#### 2020-04-19 Progress and MS0

* Interesting [LPC55S6x : M33 + LPU](https://www.nxp.com/docs/en/data-sheet/LPC55S6x.pdf)
* Doing [echo-tomo](https://github.com/kelu124/echomods/blob/master/matty/20200418a/Readme.md)
* @ongoing do impedance matching tests [on a new piezo](https://github.com/kelu124/echomods/blob/master/matty/20200416a/Readme.md) and tests impedance matching on the new piezo to see if that improves things =)
* [Enveloppe detection ongoing](https://github.com/kelu124/vit3rick/tree/master/MSB_1_Enveloppe] on the up5k
* @done run [simuls for pulse duration](https://github.com/kelu124/echomods/blob/master/matty/20200418a/Readme.md)
* lit3rick vF ongoing with AD8332


#### 2020-04-23 updates in general

* first a-law experiment : https://github.com/kelu124/echomods/blob/master/include/experiments/auto/20200421b.md
* worked on comparing both boards: https://github.com/kelu124/echomods/blob/master/include/experiments/auto/20200421a.md -- need a full fledge mini before moving forward with the comparison.
* [verilog alaw compression](https://github.com/kelu124/vit3rick/tree/master/MSB_1_Enveloppe) is ok and [simuls on icarus OK](https://github.com/kelu124/vit3rick/tree/master/MSB_2_alaw/code_alaw/sim/icarus) too. 
* Idea for i2s update on rpi : https://github.com/ryankurte/rpi-i2s-stereo/blob/master/instructions.md
* @done check newer lit3rick.vF
* @done merge bgd/and (acq + i2s + transfo)
* @cancelled go onto yosys (not possible from a up5k perspective.. too tight on timings)
* @done understand echoes from acqs.. weird things
* @done consider additional CS ( https://www.raspberrypi.org/forums/viewtopic.php?t=152014 ) or SPI ( https://www.raspberrypi.org/forums/viewtopic.php?p=821666#p821666 )

#### 2020-05-01 ESP32 ULP

* ULP on ESP32 interesting
  * https://www.youtube.com/watch?v=6PGrsZmYAJ0
  * https://github.com/bitluni/ULPSoundESP32/blob/master/ULPSoundMonoSamples/ULPSoundMonoSamples.ino
  * https://codingfield.com/2019/01/15/ulp-esp32-un-exemple-simple/

#### 2020-05-08 Resets

* @done need to check if reset, ice_reset_ft and ice_reset_rpi are connected in the VHDL v1.1 Matty


#### 2020-05-2O Order for pHATr1ck

* A couple of pHATr1cks out !
* USB
  * How to create a device node from the `init_module` code of a Linux kernel module? [check](https://github.com/cirosantilli/linux-kernel-module-cheat/blob/68af3477cce1cd22566edce2651f54cf8c184a91/kernel_module/character_device_create.c).

#### 2020-06-04 5V and usb

* Got a DRV8834 and another low voltage driver
* Interested in https://wiki.wireshark.org/CaptureSetup/USB
* Waiting for the pHATr1ck's !
* Doppler ... https://www.vmedtechnology.com/Vet-Dop.htm lol.
* https://dilbert.com/strip/2020-06-05 experts .. DrR ?

#### 2020-06-08 Having fun with brd35

* @done finish 20200608a and make a gif
* https://greatrend.en.made-in-china.com/product/AKzmRHYrRBUp/China-Transducer-Replacement-for-Ultrasound-Medical-Machine.html for piezos

#### 2020-06-19 phatr1ck on

* Received minie. Seems ok to flash. Waiting DP's bin to test analog line
* test _Microphone MEMS: MSM261S4030H0 est un microphone MEMS à sortie numérique I2S omnidirectionnel, à port de fond. Il a des performances élevées_ and do pHAT
  * [Pins here](https://www.audiophonics.fr/fr/accessoires-pour-raspberry-pi-et-autres-sbc/module-microphone-stereo-omnidirectionnel-i2s-p-13949.html)
* pHATr1ck motherboard is designed, thanks ahmed
* received upduino v2.1 and v3.0 for further tests!

#### 2020-06-21 Ideas more

* Got motherboard design. Forgot VGA. Need 5 pins (H/V/R/G/B). 68R for H&V, RGB at 470R if different channels. 180R if all three are connected. [ref](https://www.gammon.com.au/forum/?id=11608). Pins from: PCM1,2,3. 
  * 640*480 -> 128 us = 512 (4px per us) x 256  (8bits). Rest is fun.
  * DB15 socket
* DEBUG 24MHz8ch -> device is fx2lafw. Pulseview working.

#### 2020-06-27 Artists et dreams

* @todo check artists meet makers
  * https://notnot.home.xs4all.nl/index.html  me likey artistic installation
  * https://jonghongpark.com/bit.html 
  * https://www.mainsdoeuvres.org/Devenir-artiste-programmeur-en-Arduino.html?lang=fr
  * http://www.christiandelecluse.com/ 
  * http://yvesbrozat.com/
* Brilliant read: https://archive.org/details/computer-lib-dream-machines
* @done Close the todos.

#### 2020-07-20 Taking time

* Just realized the pH4Tr1ck project had been alive long. Need to close it. Put back an AD8331 on the main board and that's it.
* Working on meters.. a few things to learn along the way?
  * [ATM90E36a](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-46004-SE-M90E36A-Datasheet.pdf) (DMA dump) / [ATM90E26 single channel](http://ww1.microchip.com/downloads/en/Appnotes/Atmel-46102-SE-M90E26-ApplicationNote.pdf)
  * [ADE9000](https://www.analog.com/media/en/technical-documentation/data-sheets/ADE9000.pdf) and [manual](https://www.analog.com/media/en/technical-documentation/user-guides/ADE9000-UG-1098.pdf) -> see "BURST READ WAVEFORM BUFFER SAMPLES FROM SPI"
  * [ADE7878A](https://www.analog.com/media/en/technical-documentation/data-sheets/ADE7854A_7858A_7868A_7878A.pdf) (see test circuit) + [](https://www.analog.com/media/en/technical-documentation/data-sheets/ADE7854A_7858A_7868A_7878A.pdf) + existing [shield](https://wiki.openenergymonitor.org/index.php/ADE7878A_rpi).
* See also : Analysis and Selection of Appropriate Components for Power System Metrology Instrument

#### 2020-07-26 NextSteps

* @done bin for un0rick ftdi control - done! that's the usb/usb_vga part =)
* @done lit3rick v1.5 with AD8331
* @done complete a lit3rick motherboard
* adding a 0.1uF cap increases the LNA performance: yeay ! But shitty wires mean: noise.

Always wanted to have a riscv inside my board ;)

* Interesting : https://pingu98.wordpress.com/2019/04/08/how-to-build-your-own-cpu-from-scratch-inside-an-fpga/
* Toolchain for riscv at https://github.com/cranphin/picorv32
  * https://mindchasers.com/dev/rv-getting-started (?) in priority, if it doesn't work then..
  * make download-tools
  * make -j$(nproc) build-tools

#### 2020-08-01 lit3rick_v2.1

* R0 on the bottom.. and .. good to go !
* Very interesting: games : https://8bitworkshop.com/v3.6.0/?platform=verilog&file=clock_divider.v
* lit3rick structure

````
 + lit3rick
   + images
   + doc
   + overview 
   |   \ build_pdf.sh
   |   \ paper.pdf
   + article
   |   \ design_ideas
   + software
   |   + bonuses
   |   |  \ other_verilog 
   |   + verilog
   |   |  + barebones
   |   |  + i2s_stream
   |   + rpi_utils
   |   |  \ icoprog, ifoprog 
   |   + python
   |      + lib
   + examples
   |   + acquisitions_n_processing
   + hardware
   |   \ archive_of_upverter 
   |   \ schematics 
   \ Readme.md
   \ Licenses.md
   \ Changelog.md
   \ lit3rick.pdf

````

#### 2020-08-18 break in the city

* fun stuff: https://im-possible.info/english/library/index.html
* [https://imgs.xkcd.com/comics/dependency.png](https://imgs.xkcd.com/comics/dependency.png)

#### 2020-09-08 back in the city

* @todo integrate some documentation for un0rick and lit3rick as in http://www.trenz-electronic.de/fileadmin/docs/Trenz_Electronic/Modules_and_Module_Carriers/3.05x6.5/TE0876/REV02/Documents/iceZero-pinout-v5.pdf
* @todo move forward on some new hardware like the [ft600](/include/ft_600_notes.md)
* @done add a section on the un0rick place: "_If you like the silly things I do, you can say thanks by_"

#### 2020-10-03 holidays ahead

A week of documentation ahead =) 

* @done With the help of @Jorge Arija, happy to release two small boards for HV !
  * https://github.com/kelu124/lm3478 for a LM3478 fixed output at +-90V (changeable between 80 and 200V by changing a feedback board), single 5V input.
  * https://github.com/kelu124/DRV8662-devkit for a small unipolar output of 250V with minimal BOM cost from 5V.
* @done Need to update un0rick.cc website with Jekyll pages and tutos for the different products.
* @donenotnecessar mapping registers of the lit3rick device

#### 2020-10-18 Holidays passed

And the [un0rick.cc](http://un0rick.cc) website is on. Now on to:
* try the 250 supply
* try the +-90V supply
* FUp with waveshaping on lit3rick (more flexibility)
* FUp on the USB component for un0rick
* Receive Zynq
* Do ADC08200 PMOD
* also improved biblio for the article, including competition

Work on the __rectenna__ project
* [Pitch](https://www.edaboard.com/threads/rectenna-rectifying-antenna.49902/)
* Good ideas [An Approach for Managing Manufacturing Assets through Radio Frequency Energy Harvesting](https://sci-hub.st/10.3390/s19030438) & [designs](https://www.intechopen.com/books/recent-wireless-power-transfer-technologies/rectenna-systems-for-rf-energy-harvesting-and-wireless-power-transfer) and [antennas](https://sci-hub.st/10.1587/TRANSELE.E98.C.608).
* [Basic idea](https://www.youtube.com/watch?app=desktop&v=XpLCK88nVgU) or https://tentzeris.ece.gatech.edu/Procs14_Sangkil.pdf
https://hal.archives-ouvertes.fr/hal-00827697/file/NEWCAS_2012.pdf

#### 2020-10-25 Pushing more

* Completing the [un0rick.cc](http://un0rick.cc) website.
* Improving lit3rick code
* @ongoing find the i2s issue
* Pushing a few experiments related to lit3rick


#### 2020-11-01 Toussaint20

Got some new experiments going on. Getting a un0sb 
* [32 lines dump](https://github.com/kelu124/echomods/blob/master/matty/20201031a/b.20201031a.ipynb)
* and [noise level for increasing gains on un0rick](https://github.com/kelu124/echomods/blob/master/matty/20201031a/c.20201031a.ipynb) on a 50R load.

Playing with ESP32 ideas
* Listing files?
  * https://electroniqueamateur.blogspot.com/2020/07/esp32-cam-gestion-distance-de-la-carte.html
* IOs & stuff
  * https://github.com/Ponkabonk/ESP32-CAM-Demo
  * http://www.iotsharing.com/2019/07/how-to-turn-esp-with-sdcard-or-spiffs-a-web-file-server.html
* Interesting
  * https://github.com/boblemaire/ESPAsyncSDWebServer/blob/master/ESPAsyncSDWebServer.ino
* Other stuff
  * https://github.com/Ponkabonk/ESP32-CAM-Demo
  * https://github.com/topkhung/ESP32_Web_ClickToDownload_File_SD_Card/blob/master/ESP32_Web_file_Download.ino

#### 2020-11-05 ImpedanceMatching progress yeah

* https://pypi.org/project/un0usb/ is out yeah!
* Impedance matching exercice is out =)

* https://www.postgresql.org/docs/9.1/sql-createtable.html for creating postgresql tables

#### 2020-11-06 ImpedanceMatching progress yeah v2

* Impedance matching on hp2121 seems good.. not actually no.
  * @done check motor https://github.com/kelu124/echomods/blob/master/include/experiments/auto/20181013a.md for the hp probe (done: black and white cables)
* VGA output on the un0rick, yeah!
* Test with the [HP probe](https://github.com/kelu124/echomods/tree/master/include/hp/20201128a) - see [more about this probe](/include/probes/auto/hp2121.md)

#### 2020-12-03 VGA FTW

* Done with the VGA part for the un0rick! 
* Will now need to go on the lit3rick adaptation with David

* Cosine generation on ESP32 https://www.esp32.com/viewtopic.php?f=18&t=10321
* PWM: ledCwrite
* DAC ? https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/dac.html GPIO 25/26
  * ADC: 36 (ADC1)
  * DAC: 26 (channel 2)
  * PWM: 0

#### 2020-12-06 StNkls

* https://github.com/perfaram/pdf-zip-nes-polyglot
* https://github.com/kelu124/PDFGitPolyglot

* FUN : https://www.bbcmicrobot.com/owlet-test2.html

#### 2020-12-23 Cleaning the docs

* Ongoing: tagging images for missing experiments, cleaning around
* @todo FUP i2s w Andrew
* @todo energy harvesting + low power blink
* @done mechanical runs on wirephantom
* @todo finalize article 
* @done add DRV2700 mentions ?
* @todo clear hilbert ImportError: libf77blas.so.3: cannot open shared object file: No such file or directory
* @done Worklog: why not working on Rpi4 out of the box? --> issue with XFERs, see 2020-12-29 in worklog

#### 2020-12-29 Cleaning RPI4 issues with pyUn0

* pastebin alternative: https://sebsauvage.net/paste/
* Replacing XFERS! With read/write bytes
* Read some good verilog tutos : https://www.fpga4fun.com/ for good tutorials - still looking for the interactive verilog stuff

#### 2021-01-10 New years goes fast

Blink of an eye.. already 10th. Week off ahead. Playing.
* CLD Acquisitions two other BK probes
* Do library pyUn0
* Do image creation pyUn0
* DONE Try slower images with first BK 
* FUp Andrew
* DONE FUp Renata
* Push page VGA
* FUp Jan
* FUp Jacques
* FUp Minie v1.6 . AD8332.	

Other stuff:
* Dashboard revenues open projects https://www.coryzue.com/open/
* Do musik stuff
* Short 2021 story =)

#### 2021-01-15 First days off go fast

* Getting reviews comments right: https://journals.plos.org/ploscompbiol/article?id=10.1371/journal.pcbi.1005730

* Site web
  * usb un0rick - DONE
  * vga un0rick - DONE
  * lit3rick -- Démo vidéo + GIF - DONE
  * lit3rick micropython - DONE
* Fun stuff
  * https://www.digitpress.com/library/books/book_complete_history_of_video_games.pdf
  * https://retroarcadia.blog/2021/01/13/book-review-the-games-that-werent-by-frank-gasking/

* PCB antenna reference: https://www.ti.com/lit/an/swra117d/swra117d.pdf

* @follow Orders:
  * ESP32 batteries
  * Batteries
  * PiNoir
  * BoitesASon
  * MHP30

#### 2021-01-16 Writing tips

* Writers decks
  * https://fabuladeck.com/
  * game of lenses
  * 
* https://www.turnerstories.com/blog/2019/3/1/how-to-structure-a-short-story
* https://www.thebalancecareers.com/rules-writing-great-short-story-1277281
* https://www.turnerstories.com/blog/2020/11/25/the-10-steps-to-successfully-write-short-stories
* https://www.philipbrewer.net/story-structure-in-short-stories/
* https://www.masterclass.com/articles/how-to-plot-a-short-story
* https://www.masterclass.com/articles/how-to-write-paradelle-poetry#want-to-learn-more-about-poetry
* https://blog.reedsy.com/how-to-write-a-short-story/

* Things
  * Mood, plot, action, backstory, character
  * Message written

@icn-camera

#### 2021-02-06 Volume is here

* 4k words reached, now editing. Plaything is here.
* support to michael for his experiment
* ST25DV64K !!

#### 2021-02-11 Some stuff to read 

* Growth ? 
  * https://www.indiehackers.com/post/2-167-new-subscribers-in-48-hours-one-tactic-you-should-try-283601e91d
  * https://www.indiehackers.com/post/6-116-from-my-product-launch-no-audience-here-is-how-full-breakdown-8a00ba7992
  * https://www.indiehackers.com/post/17-tips-for-great-copywriting-5d4786ddf7
  * https://www.indiehackers.com/post/my-step-by-step-guide-to-landing-pages-that-convert-9daefb2064

* LIO shop to be filled in! As soon as items reach =)

* Need to push on the short story
* Max14866 design released - https://github.com/kelu124/echomods/tree/master/include/MAX14866
* Try and push some links: http://un0rick.cc/curated

* FX2: https://github.com/makestuff/fx2tools/tree/master/fx2loader
  * Backup FX2LP's existing 128kbit (16kbyte) EEPROM data
  * Write SDCC-generated I8HEX file to FX2LP's RAM


#### 2021-02-28 Back from the green 

* https://www.monamenagementjardin.fr/abri-de-jardin-en-bois-d-epicea-brut-domeo-4-12-m.html 
* SUSS: article from v3 to v4, inc. images


#### 2021-03-14 piday

* new uncle !
* altium version of lit3rick making progress
* AD9835 for DDS / dds arbitrary waveform generator ? -- http://electronics-diy.com/electronic_schematic.php?id=968
* PCBs for max14866 received.. mouser delayed

#### 2021-04-29 FFT are NETs

* https://sidsite.com/posts/fourier-nets/
* MAX14866 tests done, seems to work
* lit3-32 done, waiting for the companion board to be ready (FTDI + Hv)
* Playing with arrays
* Asked for CMUTS
* Hackathon US+COVID: done :)
* back to k210 for nets?


#### 2021-05-02 Already May

* Progress on https://github.com/kelu124/us_rf_processing to actually get some precleaned data

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

__More [ESP8266 notes](/retired/croaker/notes_ESP8266.md)__

#### Case of Rasberry Zero

__More [Raspberry Pi Zero notes](/retired/croaker/notes_RPi0.md)__

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


# Experiments



