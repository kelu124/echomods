# Testing new boards `20180216a`

[](@description Experiment setup details)

## Objective

The objective of this experiment is to test both the new bipolar pulser and the new ADC pHAT.

* Series are in the form _ZXY_ where __X__ is the position of the pulser _green jumper_ (on pic below), and __Y__ the _yellow jumper_, and Z is the series (here _A_, and _B_).
* Series _A_ are with the new pulser (macrofab, alt.tbo v2)
* Series _B_ with the old (ChinaCo, alt.tbo v1).

Processing to be done through a [jupyter notebook](/include/20180216a/20180216a - Testing pulser and ADC.ipynb), images stored in a [repo](/include/20180216a/lines/), and [raw data in another](/include/20180216a/data/). [Pulser code on RPi side is available too](/include/20180216a/RPiPulserModule.c).

Images [autotagged](/include/20180216a/mkimg.py).

## Setup 

![](/include/20180216a/images/setup.jpg)

## Results

### Overview

#### Still one issue with the pulser: half the pulses don't go

![](/include/20180216a/lines/A22_clean_line7sample.jpg) 
 
#### Same issue with the ChinaCo board (alt.tbo v1)

![](/include/20180216a/lines/B33_clean_line7sample.jpg)

### In details

#### Nice echo from even lines

![](/include/20180216a/lines/A33_clean_line2sample.jpg)

#### Nothing on odd lines

![](/include/20180216a/lines/A33_clean_line3sample.jpg)

#### Same with ChinaCo

![](/include/20180216a/lines/B33_clean_line7sample.jpg)


### Pulser issues ?

#### Graph

![](/alt.tbo/20171028a/images/pulser_diods.png)

@todo .. it seems it trigs when logic signal is going low... strange, isn't it ?

#### Pinout

* Pulse_B: Track_10: IO - PPuls_ON 
* Pulse_A: Track_9: IO - NPuls_ON
* Damper: Track_15: GPIO21 - Puls_OFF


# Boards before mounted

### Pulser (alt.tbo v2)

![](/include/20180216a/images/IMG_20180217_182359.jpg)

### ADC pHAT (elmo v2)

![](/include/20180216a/images/IMG_20180217_182252.jpg)
