# `20200418a` - Doing some echo-tomo

## Setup

![](/matty/20200418a/setup/P_20200418_122934_p.jpg)

![](/matty/20200418a/setup/P_20200418_143357_p.jpg)

Observed rotation with DS04-NFC : 1 tour / 2secondes

## [Images]((/matty/20200418a/images/) obtained

![](/matty/20200418a/images/Polar_20200418a2_bdwth_1.2.jpg)

![](/matty/20200418a/images/Polar_20200418a17_bdwth_1.2.jpg)

## [Data]((/matty/20200418a/data/) acquired

* Data1 was done to explore the data: field of view, rotation period.
* Data2 is data OK, adjusted in terms of time
* Data3 is like data2, but at 64Msps, all depth
* Data4 is like data2, 64Msps, only first points per line 
* Data5 introduced an extra cable
* Data6 to 13 have been made to test effect of the pulse width
* Data 14 and 15 are 400ns pulses
* Data16 is 500ns, data17 is 200ns wide
* Difference between 16 and 17 is only width of pulse

The JSONs were processed and saved as pickles with [this notebook](/matty/20200418a/20200418a-MakePkls.ipynb) (pickles not pushed on github because too heavy)

## First observations

### Signals filtered 
![](/matty/20200418a/images/20200418a2_bdwth_1.2.jpg)

![](/matty/20200418a/images/20200418a14_bdwth_1.2.jpg)

![](/matty/20200418a/images/20200418a15_bdwth_1.2.jpg)

![](/matty/20200418a/images/20200418a16_bdwth_1.2.jpg)

![](/matty/20200418a/images/20200418a17_bdwth_1.2.jpg)


### Partial acqs

![](/matty/20200418a/images/20200418a4_bdwth_1.2.jpg)

![](/matty/20200418a/images/20200418a3_bdwth_1.2.jpg)

## Processing

#### Raw image 

![](/matty/20200418a/images/2DArray_20200418a-16.jpg)

#### Filtered

![](/matty/20200418a/images/Hilbert_20200418a16_bdwth_1.2.jpg)

#### Selecting 360 sector 

![](/matty/20200418a/images/Hilbert_trimmed_20200418a16_bdwth_1.2.jpg)

#### Rebuilding the image

![](/home/kelu/ultrasound/echomods/matty/20200418a/images/Polar_20200418a16_bdwth_1.2.jpg)


