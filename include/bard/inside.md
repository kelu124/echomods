# Readme

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

* [Set 1](/home/kelu/ultrasound/echomods/include/bard/exp1/db-bard-5-0-VGA@0x22-spimode1-64msps.csv)
* [Set 2](/include/bard/exp1/db-bard-5-8-cable_inversed-VGA@0x22-spimode1-64msps.csv)

[Python notebook](/include/bard/exp1/20180317a-Loops.ipynb) is here.

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


