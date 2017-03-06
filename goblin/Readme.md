# Module: Goblin [](@description Goblin description)

![](/goblin/viewme.png)

## Name

[`MDL-goblin_tgcenvadc`]()


## Title

Goblin: a TGC-Envelop-ADC module

## Description

* The analog signal-processing heart of the echOmods
* version: V0.2
* date: 25/12/2016
* cost:149$
* sourcing:Custom made, get the [Gerbers](/goblin/source/), or [buy it preassembled on Tindie](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/), or contact @kelu124
* technology: Module-compatible, Homemade PCB, ICs based on `AD8331` and `ADL5511`
* language: Altium, Kicad
* author: Kelu124

## IOs

### Inputs

* `ITF-A_gnd`
* `ITF-B_5v`
* `ITF-S_3_3v`
* `ITF-G_gain_control`
* `ITF-C_amplified_raw_signal` : because it's used internally
* `ITF-E_signal_envelope` : because it's used internally
* `ITF-R_reserved` : for the signal coming from the pulser (if through track R)
* `ITF-mET_SMA` : for the signal coming from the pulser (if through SMA)

### Outputs

* `ITF-C_amplified_raw_signal`: Amplified Raw Signal, post TGC, before the enveloppe detection	
* `ITF-E_signal_envelope`: enveloppe of the signal, post TGC
* `ITF-mEG_SPI` : signal from the ADC

## Key Components

* `ADL5511`: Enveloppe detection 
* `AD8331`: TGC
* `AD7274`: 2Msps SPI ADC
* `AD8691`: OA

## Information

### What is it supposed to do?

The aim of this echOmod is to get the signal coming back from a transducer, and to deliver the signal, analogically processed, with all steps accessible to hackers. 

With more details, this [Goblin](/goblin/) board aims at getting a signal, and giving access to key points within the signal processing chain for ultrasound imaging, namely:

* Getting access to a TGC
* Getting the enveloppe of the signal
* Cleaning the signal before feeding in the on-board SPI ADC

All key signals are accessible, and jumpers, as well as pots, enable on-board fine-tuning of the signals. [See more details on the __testing session__, to see the behavior of the board on a oscillo](/goblin/2016-07-08.md).

It's also a first try at a SPI ADC. Using a up to 3 Msps one in order to catch only the enveloppe, to be tested with other uC, RPi or BBB. Test have been also done with [6MSps, arduino IDE-compatible, STM32](/croaker/). 

### How does it work: block diagram

![Block schema](/goblin/source/blocks.png)

* `ITF-G_gain_control`->`Goblin_Jumper2`->`AD8331`->`ITF-C_amplified_raw_signal`->`ADL5511`->`ITF-E_signal_envelope`->`AD8691`->`ITF-Ext_Amplified`->`AD7274`->`ITF-mEG_SPI`
* `ITF-R_reserved`->`Goblin_Jumper1`->`AD8331`
* `ITF-mET_SMA`->`Goblin_Jumper1`
* `ITF-InternalPot1_gain_control`->`Goblin_Jumper2`
* `ITF-InternalPot2_ADC_Vref`->`AD7274`
* `ADL5511`->`Int-Offset`->`AD8691`

This can be summarized below - all the signals represented are accessible via separate on-board pins:

![Principle of goblin](/goblin/images/slide_principle.png)

Input/Output:

![](/goblin/images/TEK0009.JPG)

## About the module

### Pros

* Only needs 5V and 3.3V inputs.
* Energy use is relatively low: at 9V, Tobo, Goblin, and a trinket pro ask for 180mA.
* _ADC V_REF_ is flexible: better resolution in output of the ADC
* _E_REF_ is being removed from the signal output, better than Murgen, where we lost 1.1V from the signal range.
* ADC is http://fr.farnell.com/jst-japan-solderless-terminals/b6b-ph-k-s-lf-sn/embase-entree-sup-6-voies/dp/9492453?MER=sy-me-pd-mi-alte -- what appropriate connector ? http://fr.farnell.com/jst-japan-solderless-terminals/vhr-6n/boitier-connecteur-rcpt-6pos-1/dp/2399220 ?

### Cons: what to to make better

* Takes a lot of space because of the modularity. Jumpers and pots could be removed, not to mention SMA.
* The amplifier removing E_REF brings in some noise: a filter could be used there to remove to high frequencies.
* The SMA brings little, but still a noise analysis could be done to assess the difference between routing the signal through a SMA cable or through the pins.
* There are only two layers. A fourth one to connect each pin to the other pin on the same row, as well as a ground plane, could help with the noise.
* Little flexibility from the use of ICs - but sufficient of sorts for our use.
* The [ADC](/goblin/datasheets/AD7274 - 7273 7276.pdf) is borderline in terms of speed of use. A higher sampling rate could be useful.
* There was a bug with the [ADL5511](/goblin/datasheets/ADL5511.pdf): need to know how it shuts down.

### Detailed view

#### Explained

![](/goblin/images/module/GoblinModule.png)

#### In/Out

![](/goblin/images/TEK0009.JPG)

![](/goblin/images/TEK0010.JPG)

#### Comparing the signals: amplified signal vs enveloppe detected

The overall signal

![](/goblin/images/TEK0000.JPG)

Details

![](/goblin/images/TEK0002.JPG)

Details on the peaks

![](/goblin/images/TEK0005.JPG)

#### Schematics

![](/goblin/images/module/schematics.png)

## Constraint and limits

### Tests

#### Access to raw data

Data sampled at 10Msps on the [PRUDAQ](/toadkiller/) on both channels.

See the Jupyter notebook [In-Out.ipynb](/toadkiller/data/test_enveloppe/In-Out.ipynb)

Data is saved [here](/toadkiller/data/test_enveloppe/dual_entry.bin). It's 32Mb of sampling at 10 Msps. Full repo for the [measure test](/toadkiller/data/test_enveloppe/). Let's check the Signal In vs Signal Out:

![](/toadkiller/data/test_enveloppe/SigInSigOut.png)

with details:

![](/toadkiller/data/test_enveloppe/Details.png)


#### Trying with different frequencies


##### At 3 MHz

![](/goblin/images/2016-07-08/TEK0018.JPG)

##### At 5MHz

![](/goblin/images/2016-07-08/TEK0016.JPG)

##### At 7.5MHz

![](/goblin/images/2016-07-08/TEK0015.JPG)

##### At 10MHz

![](/goblin/images/2016-07-08/TEK0017.JPG)

#### Difference between enveloppe and ADC input?

-> the offset is removed, there's also a small gain (x2).

See below: there's an offset at the enveloppe detection (~RMS), which is removed. Enveloppe is 500mV before, comes at 1V+ afterwards.

##### Before the AOP

![](/goblin/images/2016-07-08/TEK0011.JPG)

##### After the AOP

![](/goblin/images/2016-07-08/TEK0010.JPG)

### Idea for onboard ADC

The AD7273/AD7274 are high speed, low power, 10-/12-bit, single supply ADCs, respectively. The parts can be operated from a 2.35 V to 3.6 V supply. When operated from any supply voltage within this range, the AD7273/AD7274 are capable of throughput rates of 3 MSPS when provided with a 48 MHz clock. 


## Discussions

### TODO

* _BONUS!_ Plug it to a [RPi0 or BBB or RPi](/croaker/) or else.
* Connect the ADC to a RPi0

### DONE

* Check the power consumption
* [Testing the in and out signals](/toadkiller/data/test_enveloppe/) of the board with the prudaq.
* Specs to write
* Agreeing on the strips 
* Check if 5V and 3.3V are stable
* Defining the ICs to use
* Getting schematics
* Send microcircuits to Edgeflex
* Receive the module
* Publish the sources in KiCAD (@Sofian maybe?)
* CANCELLED - Test it with the [EMW3165](/retired/kina/).

### People

* Sofian (for preparing the field with Murgen)
* Vlad for his expertise with Altium

## License

### Goblin 

The [echOmods project](https://github.com/kelu124/echomods) and its prototypes (so Goblin) are open hardware, and working with open-hardware components.

Licensed under TAPR Open Hardware License (www.tapr.org/OHL)

Copyright Kelu124 (luc@echopen.org / kelu124@gmail.com ) 2015-2018

### Based on 

The following work is base on a previous TAPR project, [Murgen](https://github.com/kelu124/murgen-dev-kit) - and respects its TAPR license.

Copyright Murgen and Kelu124 (murgen@echopen.org , luc@echopen.org / kelu124@gmail.com ) 2015-2018
