Yeayyy, creation of the page
============================

The EchoModules
---------------

### Brief

Mostly, the thing would be to separate the
[Murgen](http://github.com/murgen-dev-kit/) PCB in 4 different
modules (similar to the arduino trinket pro for example), so to have
them ready to be used on a stripboard which would have already headers.

The strips would have the 11 tracks as on the attached picture below.

There would be 3 modules :

-   HV+pulser+md0100
-   TGC+enveloppe
-   SPI ADC

(Two other modules, Alim, and controler, will be stripboard based)

Given that the boards would be separated, would it make sense to try
to \*\*design the PCBs to have only 2 layers PCB\*\* ? The width of the
PCBs would not really matter, only to be sure they'd fit on a strip
board. It would be interesting to have a form factor of the modules PCB
comparable to one trinket pro =)

#### Details about the modules

1\. HV+Pulser+MD0100 don't change. The module will need to have a SMA
connector (same as on existing board).

2\. AGC+enveloppe detector can remain the same. I just need to remove the
filter that is between the TestPoints4 and 5 and the transformer. The
module output is the output of the ADL5511.

3\. SPI can be replaced, this one was an overkill. 10Msps is too much, so
instead a 2 or 3 Msps at 12 or 14 bits in SPI could be used on the ADC
module.

#### Controls

The "controls" listed would be a potentiometer for the HV (as was done
for murgen), a potentiometer for the TGC Gain (not an ADC, bit of
overkill, rather a jumper to allow one to select the gain from either
the track or a potentiometer which would feed in from 0 to 1V).

#### ADC details

The ADC can be as low as 12bits 2Msps when we're talking about envelope
detection (what about MAX11105?). (btw, the signal output by it is
offset by around 1.32V) on top of which we have 1.25V of signal. For the
sake of the experiment, I would add another ADC board, clone of the
11105, with a MAX11103, to comparatively test both.

#### The motherboard

- what is expected is to break down logic blocks into modules that could be put on a motherboard ( a 2.54mm stripboard), max 20 to 24 track wide.
- it appears 19 tracks would be good

##### Tofs

![Cartes](/images/600px-Cartes.png)


![Motherboard](/images/600px-Motherboard.png)



##### Table of tracks

### A rough draft

#### Table

| ID | Signal | Nomenclature | Comments |
|:--:|--------|--------------|----------|
| 1  | Masse |              |          |
| 2  | 5V  |              |          |
| 3  | TGC-Raw       |              |          |
| 4  | TGC-filtered  |              |          |
| 5  | TGC-enveloppe |              |          |
| 6  | 12V |              |          |
| 7  | Analog Gain Ramp |              |          |
| 8  | -12V |              |          |
| 9  | Pulse On  |              |          |
| 10 | Pulse Off |              |          |
| 11 | Pulse RedPitaya (3.3V) |              |          |
| 12 | 18V |              |          |
| 13 | NewFramePulse (TopTour?) |              |          |
| 14 | A1 xor PWM  |              |          |
| 15 | A2 xor Encodeur |              |          |
| 16 | B1 |              |          |
| 17 | B2 |              |          |
| 18 | Reserved |              |          |
| 19 | 3.3Vs |              |          |

#### Pic



Worklog
-------

### April 5th

Validation of the approach by the Captech

### April 8th

Validation of tracks of interest


### April 15th 

Validation of tracks and their orders

### April 16th 

Studying microcontrolers:

| ID | Name | Chip | Comments | ADC |Price| COmments |
|:--:|--------|--------------|----------|----|----|----|
| 1  | WiFiMCU |  EMW3165 -> STM32F411CE | Cortex-M4 core at 100MHz | 1×12-bit, 2.4 MSPS A/D converter: up to 16 channels  | 8$ |Has wifi|

Studying chips:

| ID | Name | Details | Comments |
|:--:|--------|--------------|----------|
| 1  | STM32F411CE |              |          |
