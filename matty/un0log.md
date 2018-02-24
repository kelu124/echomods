#### 2018-02-21 Reading ok on 8bits

* Now working on 8bits. Still issues on 16 bit transfers.

![](/matty/images/MATTY_20180221_testcompteur8bits_bitmap.jpg)

#### 2018-02-18 Reading something

* Can read some values now from __[MATTY_20180218.bin](/matty/prog_flash/MATTY_20180218.bin)__
* and corresponding [notebook](/matty/prog_flash/MATTY_20180218.html) -- even with a piezo on !


#### 2018-02-11 All but acquisition

* __[matty20180211_bitmap.bin](/matty/prog_flash/MATTY20180211_bitmap.bin)__ seems to work -- [see the notebook](/matty/prog_flash/MATTY20180211_bitmap.ipynb)
  * All registers can be written

__Picture needed on the PonPoff hack on the U118, U131, U134 -- soldered reversely__

![](/matty/images/IMG_20180212_195429.jpg)

##### Pon Poff

![](/matty/images/pon/1_pulses.png) 

##### Without the piezo

![](/matty/images/pon/2_nopiezo.png)

##### With the piezo -- probe x10

![](/matty/images/pon/3_piezo.png)

#### 2018-02-10 Getting some reading

![](/matty/images/setup.png)



#### 2018-02-07 Moving forward

Now the DAC seems to work, still no SPI


#### 2018-02-06 Issues with SPI

When issuing 0xAA, 0xEB, 0X01, I see what I expect to see... but there's no  CS going back high after each byte.

![](/matty/images/debug/CLK+CS.BMP)

![](/matty/images/debug/CLK+MOSI.BMP)

Seems to occur.. https://www.raspberrypi.org/forums/viewtopic.php?f=44&t=73323 

![](/matty/images/debug/individual-xfer-miso.BMP)

![](/matty/images/debug/individual-xfer-CS.BMP)

#### 2018-02-05 Issues with DAC

DAC SPI seems off

![](/matty/images/debug/sdbleu_yellowcs.BMP)

![](/matty/images/debug/bleusdi_yellowsclk.BMP)

#### 2018-02-03 Install on RPi

Want to have a notebook running on board RPi to access the SPI dev

apt-get -y install python2.7 python-pip python-dev
apt-get -y install ipython ipython-notebook
pip install jupyter


The Notebook server listens on localhost by default. If you want it to be visible to all machines on your LAN, simply instruct it to listen on all interfaces:

jupyter notebook --ip='*'


#### 2018-02-02 Flashing Un0rick oki

* Done! With the code, it works. I just need to rmmod ftdi_sio and usbserial before flashing with programmer from usb.

![](/matty/images/IMG_20180202_233901.jpg)

* CDONE is on, weak LED corresponds to 64Mhz signal (same in the dark)

![](/matty/images/IMG_20180202_233921.jpg)

* See [this repo](/matty/prog_flash/) which contains the hex/bin files, the ice40.xcf for as the programmer save, and prog to start the programmer without cumbersome kernel modules.
* Still having issues with the FTDI-SPI pinouts


#### 2018-02-01 Un0rick clock oki

* Clock is soldered again! And FTDI device magically appears in lsmod.

![](/matty/images/IMG_20180203_131837.jpg)

### 2018-01-26 -- The clock had to be removed!

Investigation showed no connection through USB.. a ftdi issue. Powers were OK.. but still nothing.

So what? __Clock!!__

I unfortunately destroyed the 12MHz clock.. well that's it =) I'll be waiting for the new one from digikey.


![](/matty/images/IMG_20180126_200809.jpg)

The clock has to be rotated by 90°

![](/matty/images/20180126--compare.png)


### 2018-01-23 -- More on the next session !

Let's have a first peek

![](/matty/images/IMG_20180115_194856.jpg)

This has reached a couple of days ago =)

Looks good - ice40 and ram look good. The high-level pulser footprint seems reversed. The 3.3V is on, 5V level looks good, seems good!


### 2017-12-15 Others

![](/include/uniBoard/unimatty-2a.png)

### 2017-11-19 First ideas

![](/include/uniBoard/unisimple.jpg)


## BORN !

![](/matty/images/arf.jpg)
