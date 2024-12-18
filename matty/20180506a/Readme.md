# `20180506a` - SPI timing on Raspberry

The objective of this experiment is to test what is the limiting factor on the Raspberry Pi communication.

With a clock set at 200khz or 16MHz, the transfer speed is the same. Does this lie with the overheads?


* [Client side](/matty/20180430a/20180430a-Client.ipynb)
* [Server side](/matty/20180430a/20180430a-Server.ipynb)
* [PFGA bin](/matty/prog_flash/pMATTYtestRegisterasyn_nomoreadd_20180401.bin)

# Clock issues

## Original clock at 200khz

#### One sees 8 bits for 4us, that's around 500khz

![](/matty/20180506a/images/IMAG001.png)

#### CS is down during 10us

![](/matty/20180506a/images/IMAG002.png)

#### 90us between 2 bytes

![](/matty/20180506a/images/IMAG003.png)

## Boosting the clock to 15Mhz

#### Now 8 bits are less than 1 us, I'd say around 800ns

![](/matty/20180506a/images/IMAG004.png)

#### Same 90us delay between two bytes

![](/matty/20180506a/images/IMAG005.png)
