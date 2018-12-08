# Testing [the board](https://doc.un0rick.cc/) with a M5Stack


## What is the M5Stack ?

That's an ESP32, with a screen of 320x240.

For a 120us  acquisition, that leaves 3us per pixel.. Still interesting to see. Moreover, there seems to be a 512KB RAM, would be enough to store long acquisitions. One line is 256kB at 64Msps.

Even a [FFT processing](https://github.com/ElectroMagus/M5-FFT) would be possible.

Connectors necessary were :

* 5V
* GND
* CS
* MISO
* MOSI

## Some code

Only SPI libs and M5Stack were necessary.. and a proof of concept was done with a single line acquisition process, for 200us, with a low gain.

[File source is available](/matty/m5stack/SPI.ino)

## Results

### With the calibration rig

![](/matty/m5stack/calibration.gif)

### With a piezo in a mug

![](/matty/m5stack/mug.gif)
