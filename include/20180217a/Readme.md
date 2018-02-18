# Testing new boards `20180217a`

[](@description Experiment 20180217a setup details)

## Objective

The objective of this experiment is to test the software issues with the kernel module.

* Series are in the form _ZXY_ where __X__ is the position of the pulser _green jumper_ (on pic below), and __Y__ the _yellow jumper_, and Z is the series (here _A_, and _B_).
* Series _A_ are with the new pulser (macrofab, alt.tbo v2)
* Series _B_ with the old (ChinaCo, alt.tbo v1).

Processing to be done through a [jupyter notebook](/include/20180217a/20180217a - Testing pulser and ADC.ipynb), images stored in a [repo](/include/20180217a/lines/), and [raw data in another](/include/20180217a/data/). [Pulser code on RPi side is available too](/include/20180217a/RPiPulserModule.c) where pulses are driven by going low on control pins, and [the other pulser code](/include/20180217a/RPiPulserModule-alt.c) does the opposite.

Images [autotagged](/include/20180217a/mkimg.py).

## Setup 

![](/include/20180216a/images/setup.jpg)

There is approximately 27mm of water before the reflector on the piezo. That's an echo which has to travel 2x27mm = 54mm, at 1500m/s. We should see at peak at around 36us, and, if a second reflection occurs, at 72us.



## Results

Better resolution can be achieved when the pulser code is [cleaned from its errors](/include/20180217a/RPiPulserModule.c).. Namely with a better control of the controling variables.

#### Before the new code

![](/include/20180217a/lines/B33-oldmodule_odd-even.jpg)

#### With the new code

![](/include/20180217a/lines/B33-newmodule_odd-even.jpg)

## Details of the lines

#### Raw lines

![](/include/20180217a/lines/B33-newmodule_line3sample.jpg)

#### Once filtered

![](/include/20180217a/lines/B33-newmodule_clean_line3sample.jpg)

## Remaining issues

It seems trig happens when line goes low:

### Going low at t0 of pulse

![](/include/20180217a/lines/A11-newmodule_odd-even.jpg)

### Going low at first up, then down, so delayed

![](/include/20180217a/lines/A11-altmodule_odd-even.jpg)

### Classical pulses off, Pon going low

![](/include/20180217a/lines/A11-termodule_odd-even.jpg)
