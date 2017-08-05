
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

echOpen discussion

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
    *  For low-speed comms, conventional I2C or similar protocols
            can be used, and there is no need to use a PRU. For
            high-speed comms the PRU may be extremely useful because it
            can service the hardware with no interruptions due to Linux
            context switching, and no overhead is experienced by the
            main ARM processor. Here are some examples that should be
            feasible; basically quite a few possibilities, such as
          *  * interfacing to a fast ADC (e.g. analog capture)* * ,
  * https://theembeddedkitchen.net/beaglelogic-building-a-logic-analyzer-with-the-prus-part-1/449
        BBB is a 100MHz logic analyzer on a BeagleBoneBlack
  * Demo over the http://beaglelogic.github.io/webapp/
  * http://r.git.net/beagleboard/2013-10/msg00204.html
    *  Can the PRU be used to interface the Beaglebone to external
            ADC? I need to capture 500 micro-seconds of data at a 5
            MHz rate.
    *  -&gt; * It depends on the interface to the ADC. There is a
            parallel capture interface that will easily run that fast,
            and you may be able to use the bit-shift interface to do
            serial or something like SPI if the PRU's capability lines
            up with what your ADC wants to see.* 
  * http://www.element14.com/community/community/designcenter/single-board-computers/next-gen_beaglebone//blog/2013/08/04/bbb--high-speed-data-acquisition-and-web-based-ui
    *  * In its current state, it grabs analog data from an ADC, and
            dumps it into memory on the BBB, ready to be displayed or
            further processed. It could be used for gathering analog
            information from sensors, CCDs or other data
            acquisition use-cases. To be reasonably useful, the desire
            was for it to support 20Mbytes/sec of data or more. It does
            achieve this, but it is for further study to find higher
            speed methods.* 
    *  * This is not such a bad idea, because in future the ADC
            could be swapped out to a (say) 10-bit ADC with no code
            change on the PRU.* 
    *  * * Once the data has been captured (2000 samples in this
            example), the command byte is acknowledged, so that the
            Linux hosted application can know that the PRU
            has completed. The PRU now sits and waits for a new
            instruction from the Linux hosted application.* *  -&gt; works
            for us - fixed depth = fixed \# of samples
  * Buffer to be used : detailed at
        http://www.element14.com/community/community/designcenter/single-board-computers/next-gen_beaglebone//blog/2013/08/04/bbb--high-speed-data-acquisition-and-web-based-ui
    *  ''These were extremely important for two reasons. One reason
            is that the pins to the BBB that I wished to use need to be
            isolated during power-up, because they are used for
            selecting the boot method. If there was any unusual level on
            the pins upon power-up then the BBB will not boot from
            the eMMC. So, a tri-state buffer is needed. The other reason
            is that there is a fair bit of capacitance and it is highly
            likely that the ADC may not be able to directly drive the
            pins at high speed. I actually came across this problem
            while trying to connect a camera to the BBB. I struggled for
            days without realising that the camera could not support
            the load. So, the buffers are likely to be essential for
            most designs using the pins that were selected. I used a
            74LVC244A device as a buffer. Note that the clock also needs
            a buffer, unless significant jitter is acceptable. No
            tri-state is required here, so I used a MC74VHC1GT50.

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
*  Thinking as well on architecture
      *   Motor + transducer + top in the probe
      *   Board + BBB (Node.js still..)
      *   Output (if necessary)

#### 2015-12-07

*  Busy business day
*  Usual monday meeting
      *   awesome progress on mech part. Seems robust, small, ...
      *   need to follow the power usage of POLULU ^^
*  What about a webcam video format?
      *   WebRTC - awesome stuff at https://rtc.io/ for nodejs + webrtc

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

* Update the * Culture*  repertory in our drive :p
* [ Piezo
    suppliers](:Category:Transducer#Transducer_suppliers "wikilink") on
    their way
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
  * http://www.brl.uiuc.edu/Downloads/bigelow/APPENDIX%20C.PDF ou
        en local sur : [:File:APPENDIX
        C.PDF](:File:APPENDIX_C.PDF "wikilink")
  * http://www.vtvt.ece.vt.edu/research/papers/08sas.pdf ou en
        local sur : [:File:08sas.pdf](:File:08sas.pdf "wikilink")

#### 2015-12-27

* Some PCB Assembly recommendation
  * https://groups.google.com/forum/#!topic/tcmaker/rXdZSrWvRTU
  * https://forum.sparkfun.com/viewtopic.php?f=20&t=36339
* OSH Park, purple board, doesn't do assembly
* https://macrofab.com/ -- GO FROM PROTOTYPE TO MARKET FASTER THAN
    EVER BEFORE -- excellent review

#### 2015-12-28

* Back from festive period ! But no slack:
  * First iteration of A (though no buffers [:File:Top
        View.jpg](:File:Top_View.jpg "wikilink") ) -- buffers as
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

#### 2015-12-29

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
  * _The absence of deal-breaking flaws is more important than the presence of any extras._  You don’t need anything special         to succeed. You just need to do the essentials properly.
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

![](http://wiki.echopen.org/images/0/01/Dt160120.gif)

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
* [Goblin](http://murgen.echopen.org/pcbs-have-reached/) being
    released
  * A 2 layer PCB.. easier
  * Less components, less expensive
  * However, needs to be tested !



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
  * [ATL Access 10PV](ATL_Access_10PV "wikilink") is a sector array
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
* OUIDIDIT ! First presentation of echopen's working prototype
  * https://storify.com/ForTheFuture/firstech
  * http://www.makery.info/2016/03/29/echopen-lance-une-sonde-dechographie-open-source/
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

* TODO: creer les liens sur le software/readme -&gt;
    [Software (murgen-dev-kit)](Software_(murgen-dev-kit) "wikilink")
    vers les fichiers sources

#### 2016-04-07

* trying some docs at
    https://github.com/kelu124/murgen-dev-kit/blob/master/hardware/doc/murgen-dev-kit.markdown
* starting with the modules.. should start a [Worklog - the module
    approach](Worklog_-_the_module_approach "wikilink") page based on
    the [Challenge: the module
    approach](Challenge:_the_module_approach "wikilink") page... coming
    soon?

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

