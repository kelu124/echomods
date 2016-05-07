# The EchoModules

## Next steps from [Murgen](http://github.com/kelu124/murgen-dev-kit/) 

1. Playing with the design and fab the modules: 3 to go in CMS (HV/TGC/MD, enveloppe detection, SPI ADC) and 2 in stripboard mode (alim, based on the breadboard 3.3V and 5V, as well as the controler, maybe an arduino nano at first) - and start the github repo / [echOmods](https://hackaday.io/project/10899-echomods) hackaday pages as well. Work on this with Sofian and Vlad. See also the [echOmods repo](https://github.com/kelu124/echomods/).
2. Playing with an electronic emulator of the transducer - as well as an electronic model. Work on this with a partner/supplier.
3. Play with a ultrasound durable fantom. Work on this with **staticdet5** (comment on HAD). Started a [project with Virginie and Static on HAD.io](https://hackaday.io/project/11478-open-source-ultrasound-phantoms).
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

### Details about the modules

1\. HV+Pulser+MD0100 don't change. The module will need to have a SMA
connector (same as on existing board).

2\. VGA + enveloppe + ADC

* VGA+enveloppe detector can remain the same. I just need to remove the
filter that is between the TestPoints4 and 5 and the transformer. The
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

* TODO: Silkscreening with the murgen-series logo =)
* TODO: Document the motherboard
* TODO: Play with Highspeed SPI (BBB)
* TODO: Autre SPI: Goblin - 2Msps SPI ADC
* TODO: Design Croaker and Silent
* TODO: contact Frederic Patat
* TODO: Add status to track progress of the works
* TODO: Jan
* TODO: Imprimer une tof a afficher
* TODO: Contact Edgeflex
* TODO: Cahier des charges modules
* TODO: Schemas de fonctionnement des modules

* TODO: Module: ESP8266+ADC
* TODO: Module: Detection

### Done

* Done: schemas a taper, puis processing dans le makedoc.py
* Done: A draft for the analog pulser, [Tobo](/tobo/) -- April 20th 2016
* Done: [Automating Documentation](https://github.com/kelu124/echomods/blob/master/makedoc.py)

## A rough draft

### Table

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


### Pic

#### Two modules:

![Motherboard](/include/images/DSC_0284.JPG)

#### Description

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


Worklog
-------

#### April 5th

Validation of the approach by the Captech

#### April 8th

Validation of tracks of interest

#### April 15th 

Validation of tracks and their orders
Alexandr
#### April 16th 

Studying microcontrolers... See below

#### April 17th

![A PCB for PCB](/tobo/images/us_#1_top.png)

#### April 18th

* Playing a bit with ADL5511 : there's an EREF 
* We use offset remover (suiveur + gain de 2.5), and second op will do amplification, cause envelope output swing is saturated at 1.2-1.3V, We can use 2..2,5 gain to deliver nice and neat 2,6 ..3V input swing for ADC. 

#### April 20th

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

#### April 23th

* A stepper based on a stepper : https://hackaday.io/project/11224-mechaduino (pour @bivi)

#### April 24th

* Starting to document [Tobo](/tobo/Readme.md)
* Reading __"Maintaining Open Source Projects"__ by Tute Costa : _A project maintainer should feel comfortable shaping the community, promoting the library, keeping good communication with different people, deciding when to release new versions, and prioritizing all these tasks._

* Getting a _TL-MR3040 TP-Link_ for a project PirateBox (an __echObox__ ?)
* __2016 strategy__ being done

#### April 25th

* http://bengarvey.com/2016/04/24/real-work/ _How many times today did a customer notice something you did?_
* http://www.stubbornella.org/content/2013/02/26/why-i-run-my-business-like-an-open-source-project/
* http://www.atlasobscura.com/articles/the-rise-of-illegal-pirate-libraries?utm_source=facebook.com&utm_medium=atlas-page

_I define Real Work as_
* Work that creates an immediate and positive change in your product/service
* Work that is a direct constraint to the completion of A
* Work you have been uniquely hired to do.

#### April 26th

_"I am not a visionary, I'm an engineer," Torvalds says. "I'm perfectly happy with all the people who are walking around and just staring at the clouds ... but I'm looking at the ground, and I want to fix the pothole that's right in front of me before I fall in."_

* http://gggritso.com/human-git-aliases
* http://neo4j.com/blog/technical-documentation-graph/

#### April 27th

* Meetings (virginie)
* Doc of modules : https://github.com/kelu124/echomods/
* Preparation of Testing tools for the doc 
* Materials : some awesome resources : Il existe des tables sur les plastiques (http://www.ondacorp.com/images/Plastics.pdf) et autres caoutchoucs (http://www.ondacorp.com/images/Rubbers.pdf ) mais rien de concluant (ref, eau a 1.5MRayl). Il y a des choses comme le Polyurethane, RP-6400, a voir.
* Documentation echomods 
* Premier module OK : (HV, + pulser) sources publiees (same github), fab-ready, quasi documente
* Deuxieme module OK : (TGC, Enveloppe, ADC) sources publiees (same github), fab-ready, documentation en cours

#### April 28th

* Am an INTJ-A ... so what?
* R-2R DDS -- =) MHz DDS with arduino ?
* http://www.tek.com/blog/tutorial-digital-analog-conversion-%E2%80%93-r-2r-dac
* https://hackaday.io/project/9469-misc-arm-projects/log/31489-quick-dirty-dds-for-around-1

#### April 29th 

Fun to read

* NT: [The evolutionary argument against reality](https://www.quantamagazine.org/20160421-the-evolutionary-argument-against-reality/).
* [Beard things...](http://www.smbc-comics.com/comics/1461854994-20160428.png)
* Autodocumenting with [makedoc.py](https://github.com/kelu124/echomods/blob/master/makedoc.py) - which updates the [Readme.md](/Readme.md) automatically.

#### April 30th 

* Adding graphs for all modules with [makedoc.py](https://github.com/kelu124/echomods/blob/master/makedoc.py).
* TODO: https://www.coursera.org/course/fin4devmooc
* TODO: https://www.coursera.org/course/effectiveppp
* TODO: https://www.coursera.org/course/healthcareinnovation

##### Prez for May 2nd

* Done: TOBO and GOBLIN
* Done: Autodocumentation
* Comment gerer les transducers de Jan?
* Projet Fantomes commence sur HAD

#### May 1st

* http://electronics.stackexchange.com/questions/50577/what-ultrasonic-sensoremitter-should-i-use-for-my-medical-ultrasound-project
* http://electronics.stackexchange.com/questions/129582/what-is-the-current-consumed-by-ultrasonic-sensors-transducers-1-2mhz-to-gener?rq=1 for power use

#### May 2nd

* http://uk.businessinsider.com/interview-with-estonia-cio-taavi-kotka-2016-4


#### May 3rd

* http://hackaday.com/2016/04/29/saving-lives-with-open-source-electrocardiography/
__Max-Hold-Reset__
* https://fr.wikipedia.org/wiki/Circuit_d%C3%A9tecteur_d%27enveloppe -> Schema a amplificateur operationnel  (peak detector)
* http://electronics.stackexchange.com/questions/112347/how-to-make-a-peak-detector-circuit
ou peut etre encore mieux :
* http://www.planetanalog.com/author.asp?section_id=396&doc_id=562072
* __Got it !!__ http://www.falstad.com/circuit/e-peak-detect.html
* ESP8266: exploration: SPI-ADC+ESP.overclocked ? : http://stackoverflow.com/questions/37014547/esp8266-and-high-speed-external-adc

#### May 4th

* http://stackoverflow.com/questions/13447538/how-to-avoid-overlapping-nodes-in-graphviz
* http://stackoverflow.com/questions/3967600/how-to-prevent-edges-in-graphviz-to-overlap-each-other

* http://circuit-diagram.hqew.net/Peak-detect-and-hold_17262.html
* http://www.tradeofic.com/Circuit/4885-POSITIVE_PEAK_DETECTOR.html
* PKD01 : trop lent

#### May 7th 

* https://forum.pjrc.com/threads/34095-Teensy-3-2-ESP8266-12Q-High-Speed-ADC-Websocket

### Microcontrolers and chips

#### Microcontrolers

| ID | Name | Chip | Comments | ADC |Price| COmments |
|:--:|--------|--------------|----------|----|----|----|
| 1  | WiFiMCU |  EMW3165 - STM32F411CE | Cortex-M4 core at 100MHz | 1_12-bit, 2.4 MSPS A/D converter: up to 16 channels  | 8$ |Has wifi|
| 2  | Espruino Pico |  STM32F401CDU6 | ARM Cortex M4, 384kb flash, 96kb RAM | 1_12-bit, 2.4 MSPS A/D converter  | 24$ (Adafruit) |No wifi, smart USB plug, DSP instructions|
| 3  | [Feather Wiced](https://www.adafruit.com/products/3056) |  STM32F205RG|  120MHz ARM Cortex M3 MCU + BCM43362 (avec un M3)| 3 _ 12-bit, 0.5 _s ADCs with up to 24 channels and up to 6 MSPS in triple interleaved mode  | 34$ |Has wifi, support for battery|
| 4 | STM32L471QE | STM32L471QE | NoP | 3_ 12-bit ADC 5 Msps, up to 16-bit with hardware oversampling | ?? | ?? |
| 5 | STM32L476 | STM32L476VGT6 | NOP | 3_ 12-bit ADC 5 Msps, up to 16-bit with hardware oversampling, 200 _A/Msps  | [19$ dev-kit](http://www2.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-mcu-discovery-kits/32l476gdiscovery.html?icmp=pf261635_pron_pr_sep2015&sc=stm32l476g-disco) | Cheap, powerfull, nowifi |
| 6 | ESP8266 | A voir | NoP | ?? | ?? | ?? |
| 7 | ESP32 | A voir | NoP | ?? | ?? | ?? |

* Feather  (inclus un m3) : STM32F205 + BCM43362 qui a un m3
* Feather: meme chose que le photo, mais en compatible Arduino
* https://community.broadcom.com/servlet/JiveServlet/showImage/2-19579-3826/bcm43362-damosys.png
* ESP8266 -- ultra low power Micro 32bit CPU
* Excellent post - priority level : Important : http://www.eevblog.com/forum/microcontrollers/esp8266-native-spi-hardware-driver/
* _SPI runs at 40Mhz._ - so can be 2.4Msps 10bits
* HSPI -> http://d.av.id.au/blog/esp8266-hardware-spi-hspi-general-info-and-pinout/

#### Studying chips

| ID | Name | Details | Comments |
|:--:|--------|--------------|----------|
| 1  | STM32F411CE |              |          |
| 2  | STM32F401CDU6 |              |          |
|3| stm32f407 | Recommended for data processing by Dmitry (GeekTimesRu) | |

### Croaker

Specs:

* 12 bits ADC
* 150 us acquisition, single channel
* 6 Msps interleaved mode

In 150 us you will get 6x12x150 = 10800 bits of data. On Wi-Fi speed 54Mb/s it will take 10800/54000000=0.0002s (200us) to send these data.

### ESP8266 (Review on May 3rd)

#### Facts

* throughput test : http://www.esp8266.com/viewtopic.php?f=5&t=245 + question posee sur http://www.esp8266.com/viewforum.php?f=6
* Livre: http://neilkolban.com/tech/esp8266/
* Question asked at http://stackoverflow.com/questions/37014547/esp8266-and-high-speed-external-adc
* http://www.esp8266.com/wiki/doku.php?id=esp8266-module-family
Plein de versions:
* Now, the ESP8266 v7 and v12, include an ADC (Analog digital converter) pin. This means that the ESP8266 module can process inputs from analog sensors. Light sensors, rheostats, force sensors, etc. 
* Plein de GPIOs : ESP-04 et ESP-03
* ESP-12-E/Q -- E-Series and ESP-14 have 22 pins available
* http://www.eevblog.com/forum/microcontrollers/esp8266-native-spi-hardware-driver/
* https://github.com/MetalPhreak/ESP8266_Microwire_EEPROM
* https://github.com/MetalPhreak/ESP8266_SPI_Driver
* Built-in low-power 32-bit CPU: can double as an application processor 
* 802.11 b / g / n  - Wi-Fi Direct (P2P), soft-AP 
http://www.instructables.com/id/ESP8266-ADC-Analog-Sensors/
* https://hackaday.io/project/4318-vu-meter-esp8266-ws2812b -- ESP8266+FFT+Teensy -- Person to contact!
* https://forum.pjrc.com/threads/34095-Teensy-3-2-ESP8266-12Q-High-Speed-ADC-Websocket
_If you run the esp8266 wifi at 4.6 megabaud, you can get a minimum of 1 megabit per second throughput on wifi, a lot faster if your location does not have a ton of wifi signals, 2 mbit/s is typical. That is decent speed for my application._
* ebook : https://leanpub.com/ESP8266_ESP32
* Big brother : ESP32 

#### Fun piratebox

* http://forum.acolab.fr/t/sub-micro-pirate-box-en-esp8266/57
* https://bricoles.du-libre.org/doku.php?id=esp8266:le_partageoir
* http://snhack.du-libre.org/doku.php?id=projets:spores_numeriques
* https://www.reddit.com/r/esp8266/comments/4awgtr/has_anyone_done_a_piratebox_type_thing_with_an/
* https://github.com/esp8266/Arduino/blob/d218c4ead3df50ac9cbdfa7144698850a03f2066/hardware/esp8266com/esp8266/libraries/ESP8266WebServer/examples/SDWebServer/SDWebServer.ino

### MX Chip EMW3165

### Tofs

![Cartes](/include/images/600px-Cartes.png)


![Motherboard](/include/images/600px-Motherboard.png)

### Graphing

![mindmap](/include/GraphMyMind.png)

#### April 29th -- initial fill in

* HAD->Murgen
* HAD->AutoFinancement->OpenSourceHardwareContest
* Sofian->Murgen->Output Image
* Serveur Matthieu->Output Image->Benchmark->Image processing->Jean-Francois
* Image processing->Output Image->Print
* Modules->Tester
* Modules->Transducer
* Modules->Mech
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
* Phantoms->Materials->RP-6400
* Modules->Doc
* Modules->Motherboard
* Documentation->DocBuilder->BiVi
* Documentation->GitAliases
* Documentation->CreateSchemaBlock->GraphViz
* Wifi->TCP->format
* Modules->DDS->R-2R
* AG->Strat->AutoFinancement
* Modules->Fab->MacroFab
* Vlad->MacroFab
* DDS->Arduino
* Acquisition->PRU->Vanderbilt->EdgeFlex
* FlyLabs->EdgeFlex
* PRU->Up to 10Msps+
* Acquisition->Wifi
* Acquisition->RedPitaya
* Modules->Pedagogie->Aforp->Tao
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
* Acquisition->Output Image

#### May 3rd

* Wifi->ESP8266->ESP32
* ESP8266->ADCSPI->Send
* Wifi->Igor
* Acquisition->Enveloppe->max-hold-reset
* BiVi->max-hold-reset
* BiVi->LPC810->NE555 du 21eme


#### May 7th

* ADCSPI->Feather

