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

* Silkscreening with the murgen-series logo =)
* Document the motherboard
* Play with Highspeed SPI
* Design Croaker and Silent

* TODO: contact Frederic Patat
* Add status to track progress of the works
* Jan
* Imprimer une tof à afficher
* Contact Edgeflex

### Done

* A draft for the analog pulser, [Tobo](/tobo/) -- April 20th 2016
* [Automating Documentation](https://github.com/kelu124/echomods/blob/master/makedoc.py)

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
* Materials : some awesome resources : Il existe des tables sur les plastiques (http://www.ondacorp.com/images/Plastics.pdf) et autres caoutchoucs (http://www.ondacorp.com/images/Rubbers.pdf ) mais rien de concluant (ref, eau à 1.5MRayl). Il y a des choses comme le Polyurethane, RP-6400, à voir.
* Documentation echomods 
* Premier module OK : (HV, + pulser) sources publiées (same github), fab-ready, quasi documenté
* Deuxieme module OK : (TGC, Enveloppe, ADC) sources publiées (same github), fab-ready, documentation en cours

#### April 28th

* Am an INTJ-A ... so what?

* R-2R DDS -- =) MHz DDS with arduino ?
* https://hackaday.io/project/9469-misc-arm-projects/log/31489-quick-dirty-dds-for-around-1
* http://www.tek.com/blog/tutorial-digital-analog-conversion-%E2%80%93-r-2r-dac

#### April 29th 

Fun to read

* https://www.quantamagazine.org/20160421-the-evolutionary-argument-against-reality/
* Beard things... http://www.smbc-comics.com/comics/1461854994-20160428.png



### Microcontrolers and chips

#### Microcontrolers

| ID | Name | Chip | Comments | ADC |Price| COmments |
|:--:|--------|--------------|----------|----|----|----|
| 1  | WiFiMCU |  EMW3165 -> STM32F411CE | Cortex-M4 core at 100MHz | 1×12-bit, 2.4 MSPS A/D converter: up to 16 channels  | 8$ |Has wifi|
| 2  | Espruino Pico |  STM32F401CDU6 | ARM Cortex M4, 384kb flash, 96kb RAM | 1×12-bit, 2.4 MSPS A/D converter  | 24$ (Adafruit) |No wifi, smart USB plug, DSP instructions|
| 3  | [Feather Wiced](https://www.adafruit.com/products/3056) |  STM32F205RG|  120MHz ARM Cortex M3 MCU | 3 × 12-bit, 0.5 μs ADCs with up to 24 channels and up to 6 MSPS in triple interleaved mode  | 34$ |Has wifi, support for battery|

#### Studying chips

| ID | Name | Details | Comments |
|:--:|--------|--------------|----------|
| 1  | STM32F411CE |              |          |
| 2  | STM32F401CDU6 |              |          |

### Tofs

![Cartes](/include/images/600px-Cartes.png)


![Motherboard](/include/images/600px-Motherboard.png)

### Graphing

#### April 29th -- initial fill in

* HAD->Murgen
* HAD->Financement
* Murgen->Output Image
* Serveur Michel->Output Image
* Output Image->Benchmark
* Benchmark->Image processing
* Image processing->Jean-Francois
* Image processing->
* Output Image->Print
* 1. Modules->Tester
* 1. Modules->Transducer
* 1. Modules->Mech
* Mech->BiVi
* echOmods->WoodBox
* WoodBox->Arthur
* WoodBox->LogoLaserCut
* Transducer->Jan
* Jan->2 types to test
* Croaker->STM32F205RG
* STM32F205RG->M3
* STM32F205RG->6Msps
* 5. uC->Croaker
* Croaker->TFT Screen
* Croaker->SD Card
* 5. uC->Vlad
* 1. Modules->Alim
* 1. Modules->echOmods
* Alim->Mogaba
* 1. Modules->HV
* 1. Modules
* 1. Modules->TGC
* 1. Modules->Controler
* 5. uC->Feather Wiced
* 5. uC->Wifi
* 5. uC->EspruinoPico
* EspruinoPico->BiVi
* HAD->3. Phantoms
* 3. Phantoms->Virginie
* 3. Phantoms->Static
* 3. Phantoms->Materials
* RP-6400->Materials
* 1. Modules->Doc
* 1. Modules->Motherboard
* Documentation->DocBuilder
* DocBuilder->BiVi
* Documentation->GitAliases
* Wifi->TCP
* TCP->format
* 1. Modules->2. DDS
* AG->Strat
* 1. Modules->Fab
* Fab->MacroFab
* Vlad->MacroFab
* 2. DDS->R-2R
* 2. DDS->Arduino
* Acquisition->BBB
* BBB->4. PRU
* 4. PRU->Up to 10Msps or more in parallel
* 4. PRU->Vanderbilt
* Vanderbilt->EdgeFlex
* FlyLabs->EdgeFlex
* Acquisition->Wifi
* Acquisition->RedPitaya
* Acquisition->Wifi
* 1. Modules->Pedagogie
* Pedagogie->ESIA
* Pedagogie->Aforp
* Aforp->Tao
* Aforp->Apprenti
* Pedagogie->Vanderbilt


