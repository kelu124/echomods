# Readme  `bard`

## Intro

### First glance

* Cheap probe, seems mechanical, single element (seen on [youtube](https://www.youtube.com/watch?v=8iUkeJvSXtE) ) -- [MOV](/include/bard/bardsite3.mp4)
* Cheap ultrasonograph - 35 to 300$ on ebay
* [An interesting patent is here](/include/bard/US4399703.pdf)
  * _20180317_: I now understand ! Two electromagnets for the probe! That's why there are two pairs of cables. To be explored further
  * [Design pics are here](/include/bard/design)

### First pulses

When feeding a 25V pulse

![](/include/bard/exp1/bard.jpg)

Interesting response. __Seems the answer is an already ready enveloppe__. That means the coax back to the unit is only the enveloppe! Smart =)
It may also explain the dephasing of pi/2 when signal is inverted =)

Data is at 

* [Set 1](/include/bard/exp1/db-bard-5-0-VGA@0x22-spimode1-64msps.csv)
* [Set 2](/include/bard/exp1/db-bard-5-8-cable_inversed-VGA@0x22-spimode1-64msps.csv)

[Python notebook](/include/bard/exp1/20180317a-Loops.ipynb) is here.

## Understanding the patent

* One skilled in the art of circuit design can choose the values of the resistors of circuit 200 to achieve any efficiency desired, up to about 95 percent.
  * Hence the 4 resistors on the board

* __Position__ 
  * "Position sensing device 600 can be the variable inductance coil 602 shown in FIG. 8. Sensing device 600 generates a signal, in response to electrical excitation thereof by current source 502, having a magnitude proportional to the angular position of assembly 64. Since current source 502 energizes sensing device 600 periodically, sensing device 600 periodically provides short bursts of information related to the position of assembly 64."

* __Pulser__
  * Master timer 430 is well known. Timer 430 produces system timing pulses at a rate of 3 kHz. Those pulses activate transducer pulser 432 which delivers high voltage electrical pulses--about __200 volts peak-to-peak__--lasting __0.5 microseconds__ to transducer 32 by lead 202 of cable 102. Transducer 32 generates electrical pulses in response to echoes from the test specimen received by transducer 32 and transmits those electrical pulses to system 400 via lead 202.

* __TGC__
  * Also, master timer 430 provides inputs to time control gain (TCG) generator 444, sector generator 450, and display gate 446, all of which are known circuits.
  * A period of _260 microseconds_ enables the user to examine the specimen to a _depth of 20 cm_. Generally, 1 cm. can be examined for each 13 microseconds of CRT display time.

* __Connectors__
  * Cable 102 includes four conductors. 
    * Lead 228 is the common ground along with its shield 103. 
    * Lead 202 is electrically joined to the hot side of transducer 32. 
    * Lead 204 carries transistor power supply for circuit 86. 
    * Lead 206 carries switch signals from circuit 86 to other components of the ultrasonic scanning system.

* __Potentiometers__
  * __Potentiometer 342__, which is accessible to the user, is set to control the frequency with which transducer element 32 scans the specimen. Speed control 342 is mechanically linked by a shaft to current control potentiometer 346.
  * __Potentiometer 384__ is a potentiometer and is accessible to the user. Resistor 384 enables the user to make fine adjustments to the shape and phase angle of waveform 380 to compensate for changes in viscosity of liquid 18 that result from changes in temperature of transducer assembly 64. When resistor 384 is adjusted correctly, the displayed image is stationary; when the resistor 384 is adjusted improperly, the displayed image appears to wiggle in the azimuthal direction.
  * __ __:"One skilled in the art of circuit design can choose the values of the resistors of circuit 200 to achieve any efficiency desired, up to about 95 percent." 

## Some insides pictures

### In the wires

![](/include/bard/images/IMG_20180317_201900.jpg)

### Overview

![](/include/bard/images/IMG_20180317_202001.jpg)

### Unscrew tail first, then body

![](/include/bard/images/IMG_20180317_202029.jpg)

### Inside the head

Ferrite bead on the fatest cable (small coax): seems that's where the signal is.

![](/include/bard/images/IMG_20180317_202243.jpg)

### Small ICs in the head

Back of the IC: R5C IC 3 pins components ... possibly LM4040CIM3X-5.0 . Voltage references.. what for?

![](/include/bard/images/IMG_20180317_202341.jpg)

Impedance test from the cable show that pairs have impedance of 
* 6.6 OHm : Red/green and Red Blue
* 2.2 0hm :  green and blue
* 11 Ohm between Red and yellow

### 8 pins head

1. Pin 1: Red cable from the Red/Green pair 
2. Pin 2: Green and blue cables from the Red/Green and Blue/Yellow Pairs 
3. Pin 3: purple cable. Outter shield from the coax cable
4. Pin 4: Floating
5. Pin 5: Black from the inner shield from the coax cable
6. Pin 6: black cable from fat grey cable 
7. Pin 7: white cable from fat grey cable 
8. Pin 8: Yellow cable from the blue/yellow pair

![](/include/bard/images/pins.jpg)


