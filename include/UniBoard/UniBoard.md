# Uniboard

* Preliminary schematics [here](/include/UniBoard/UB-v1.pdf) and corresponding Altium file [here](/include/UniBoard/UB-v1.zip).
* [Amp source files](/goblin/source/Altium/goblin_altium.zip)
* [Goblin source](/goblin/source/Altium/goblin_altium.zip)
* [Pulser source](/tobo/alt.tobo/alt.tobo.zip)
* [ADC source](/elmo/source/ADCv2.zip) -- though it is not applicable as the board needs only a onboard ADC, not interleaved. However, can be kept to keep the idea of the offset of vref/2 . To be noted, the design of this board is to be compatible with the pinout of this extension board as it can be used for faster sampling rates.


## Overall remarks

* Form factor: Raspberry Pi Hat (with screws places for both Raspberry Pi 3 and Raspberry Pi 0)
* Have the __Oled__, __ADC__, __TGC__, __HV__, __Pulser__, __capa touch__ parts clearly separated (rectangle silkcreen + names)
  * Ideally, rectangles with the different functions as defined on a block diagram, over the 6 items above.
* ADCs: both a 10-12 bit ADC (possibly from 10 to 30Msps -- like the AD9200 is offering)  - the other ADC being the SPI ADC (possibly AD7274) - to go up to 2 or 3 Msps, data being sampled is the enveloppe.
* Layers: 4 layers, if possible to have the RF noise as low as possible
* Components: easily sourcable in MacroFab (eg: initial transformer on goblin is not easy to find)
* Raspberry Pi headers connections as per details below

## OLED 

* Keeping room for the the 0.96" OLED screen variant on the top of the board for quick display + debug

## ADC
 
* Jumper to select SPI ADC (goblin) or 10-12 bit 10Msps+ ADC (onboard - that can work at 10Msps up to 30Msps)
  * Only 10 MSPS+ 10-12bit ADC. The faster ADC, like AD9629 costs approximately the same, but more complicated in use (SPI configuration, diff clock, 1.8V supply etc)
* If 10Msps ADC:
    * Jumper to select _Raw Signal_ or _Enveloppe_ . If RawSignal, to be offset by Vref/2.
* If SPI ADC:
    * Only _Enveloppe_
    * no need for variable Vref... as gain can be controlled beforehand.
* Jumper to select signal input to RPin (either from Enveloppe or RawSig).. or not 
* Ideally, the two ADCs can be shut down, and signal only routed to RPin - in case the interleaved [ADCs extension board](/elmo/) is used.

## TGC (ex goblin board)

* MD0100 or equivalent for protection of VGC
* Jumper : to select gain (3 choices)
  *  from pot (as per goblin) 
  *  from external (0 to 1V - connected to the 6x2 header Gain) as per goblin
  * or from an available pin from the 2x20 header
* Transfo: replace with one easily sourced from digikey / macrofab :)

## HV (ex tobo board)

* Jumper: Selectable 0, 25, 50 or 75V

## Pulser (ex tobo board)

* Unipolar, only with Pon and Poff (routed to 2x20 Raspberry header)
* Jumper: route pulse either to SMA or to "artificial" piezo   (see RLC) that can stand the pulses.
  * RLC : see for example http://www.brl.uiuc.edu/Downloads/bigelow/APPENDIX%20C.PDF
  * or http://www.biosono.com/PrmtLgd/PrmtLgd.php?id=TrnsRlc with .. see below!

![](/include/images/piezo.png)

## Other

* One 6x2 header for add-ons (Pon, Poff, 5V, 3.3V, TGC Gain, Touch Interrupt, Trig, GND, SDA, SCL, PWM, Tracker). Silkscreen for the different items
* Power-on LEDs on the 3.3V line and 5V lines
* Would be good to have an onboard miniusb plug for easy power supply

## Capa touch

* The board needs 2 or 3 touch-pad like zones, to be connected to i2c bus + 1 interrupt pin for detection of touching this zones, for controls (single acq, controls, settings, ...)

# Overview

![](/include/images/UniPins.png)


# Pins

!! Beware -> the ADC here has 14 bits, 12 is enough. In this case, 2 pins can be shifted to a "trig" pin + one to a gain pin

![](/include/images/UniDesign.jpg)


# Back and forth


