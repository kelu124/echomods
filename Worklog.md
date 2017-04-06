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
* [One-Eye](/oneeye/Readme.md): MicroControler - Arduinos
* [Mogaba](/mogaba/Readme.md): Alimentation

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

* Preparing a hall of fame on echopen's wiki
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
* Got to play with a [general multi tissue fantom](/include/20160822/20160822-Fantom.md): got an image from a ATL3 probe, of the fantom.
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
* A design for [Sleepy](/sleepy/) is taking place.. wood rules =) Need a water tank though.
* An awesome thing to automate physical interactions with a phone, using https://www.tindie.com/products/hugs/tapster/

#### 2016-09-12 Thanks Adafruit

* [Comm] : got cheers from [Adafruit, check this link =)](https://blog.adafruit.com/2016/09/12/murgen-open-source-ultrasound-imaging-with-beaglebone/)
* Made some progress with a i2c 128x64 oled to debug the Feather ADC, using this [elegant doc](http://www.projetsdiy.fr/ssd1306-mini-ecran-oled-i2c-128x64-arduino/#.V9Zt5tGxU8o).
* Getting up to 1Msps with the [Feather](/croaker/feather_tests/2016-09-10-Feather_ADC.md).
* @TODO: makedoc should include a link checker.. everything starting with `](/` should be tested and checked if existing. That includes images.

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

@todo Next week:

* 6Msps
* Sourcing transducer
* Sourcing materials + integration makefile par set
* Compiler output

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
* Lent a [emulator module](/silent/) to echOpen for their testing, and updated doc.
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
* @todo: AddPressReview to the main page here, and on the gitbook
* @todo review the latex article on arXiv, especially with respect to references
* Need to ping Jerome for the BGA update of HV7360
* @todo too:
    * Servo + Feather
    * Servo + BBB + enveloppe
    * Servo + ADC on board + RPi0
    * Servo + BBB + raw signal
    * BBB + probe
* @todo CERN !

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

* Max RPi speed : http://d-fence.sytes.net/raspberry-pis-gpio-speed/  @todo --> do it with the Rpi0
    * http://codeandlife.com/2015/03/25/raspberry-pi-2-vs-1-gpio-benchmark/
    * Using the same experimental setup, the Raspberry Pi 2 is about 2 to three times faster. The fastest is still the C native library, topping out at just under 42 MHz. 
* Thinking of 20E-214 and moving to Alibaba for wireless probes. Will F.'s support reach?
* Using Vitamins for the gyro's probe. What name still for it? Longinus?

#### 2016-12-29 Moving forward

* Getting to think of the 20E-214 ones =)
* Chat with 1Tech, and the guy Patrice. Motivating.
* Trying to get some stuff from the arduino, namely to get it work as a server. [Far from being finished, on it](croaker/feather_tests/2Msps_Server.ino).

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
* Proposing echOpen to be joined by WU 
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
* Testing the [goblin](/goblin/) In/out transfer function on the [emulator](/silent/) signal: [read here](/toadkiller/data/test_enveloppe/). The more I play with Jupyter notebooks, the more I like it.

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

#### #### 2017-04-06 Purple

* Got some PCBs for Bomanz, for both [high speed](https://github.com/kelu124/bomanz/blob/master/images/20170406_124950.jpg) and [CA3306E](https://github.com/kelu124/bomanz/blob/master/images/20170406_124914.jpg) ADCs.
* Got some PCB for [Doj, and tested those](/doj/20170406-PCBs.md)!

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


