# Hacking an old ultrasound probe with a module dev-kit

## Brief

The aim of this experiment is double, namely to:

* check the behavior of the analog modules, and
* to check the behavior of an old ATL probe.

The modules have already been tested, but not the PRUDAQ. The advantage of the PRUDAQ versus the other DAQ is that the data is exposed as `/dev/beaglebone` within the beaglebone black, and that it can store 320M worth of data in a single shot.

## Results

Imaging a small 1cm side cubic dice: acquisition during 1s.

![Results](/include/20160814/sonde3V_1.gif)

## Materials requirements / BOM

Some stuff, unexpensive to buy, to build a ultrasound testing kit -- _500$_

* A power supply giving 3.3V and 5V ([mogaba](/retired/mogaba/)) -- _5$_
* An analog processing ([goblin](/goblin/)) -- _130$_
* A high voltage pulser ([tobo](/tobo/)) -- _110$_
* A motherboard ([doj](/doj/)) made out of stripboard  -- _10$_
* A pulser ([oneeye](/retired/oneeye/)) from a trinket pro  -- _20$_
* An old ATL probe ([retroATL3](/retroATL3/)) -- _75$_
* A beaglebone and PRUDAQ ([toadkiller](/retired/toadkiller/)) -- _150$_

Need one of the custom boards? Message me at kelu124@gmail.com !

## Setup of the modules

### Connecting the modules

![](/include/20160814/IMG_3430.png)

### Connecting the probe

![](/include/20160814/IMG_3428.png)

# Hacking process

## Analog processing

The analog processing is managed by a [HV+pulser module](/tobo/) as well as an [amplifier + enveloppe detector module](/goblin/). Tests were done in the respective module folders.

## Testing the ATL probe

The PRUDAQ was setup to capture 32M of files at 10MHz (Jumper 1 on the external position). The signal (the enveloppe) was clipped at 1.4V since the PRUDAQ only accepts a `[0-2V]` input.

One can export the data, exposed from `/dev/beaglelogic` with:

````
debian@beaglebone:~$ sudo dd if=/dev/beaglelogic of=sonde3V_1.bin bs=1M count=32
32+0 records in
32+0 records out
33554432 bytes (34 MB) copied, 0.939505 s, 35.7 MB/s
````

Analyzing the [binary dump](/include/20160814/sonde3V_1.tar.bz2) provides the following image. We can see 10 full images, shot in 1s -- hence a rotation speed of the probe at 3.3V of around 10 rotation per seconds.

![](/include/20160814/sonde3V_1.png)


## Scan conversion

Once the images segmented, we can isolate the images and scan-convert those. For the sake of experiment, I've been using a single simple nearest-neihghbour conversion:

![](/include/20160814/sonde3V_1-4.csv-SC.png)

# Functional blocks and modules

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/sets/highspeed.png)

# Next steps

* Debug the position control
* Add a feedback control to the motor
