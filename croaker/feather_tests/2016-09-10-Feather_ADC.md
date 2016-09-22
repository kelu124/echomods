# Playing with the STM32F205 (Feather WICED ADC)

## First tests

Code can be found [here](/croaker/feather_tests/ReadPins.ino).

Testing it with a 10kHz (0-1V) sine gives the following


and with  a 10kHz (0-1V) sine:

Not satisfactory.

## Digging into the low-level code

Code can be found [here](/croaker/feather_tests/Registers.ino).

### Sources

* http://microcontroleurs.blogspot.fr/2015_07_01_archive.html?view=sidebar interessant!

 RCC_ADCPRE_PCLK_DIV_2 can replace ADC_PRE_PCLK2_DIV_2 .. or so it seems

### Question

Question is found on [github](https://github.com/adafruit/Adafruit_WICED_Arduino/issues/58):


I'm trying to see how fast the Feather WICED ADC can go. I've been trying with ` analogRead()`, and at first sight, I'm getting data at around 50ksps. Will be posting the raw data later on to support this.

Now, I've begun digging into the maple ADC and corresponding code, and I've put together a piece of [code to test acquisition speed](https://gist.github.com/kelu124/ee02b6f98d8997404783aa3043d40c1e). This code compiles nicely, but doesn't work (nothing on serial). I'm unsure of the reason behind this, and I guess some registers need to be finetuned.

For example, the enumeration for STM32F1 differs from STM32F2, as said by [leaflab](https://github.com/leaflabs/leaflabs-docs/blob/master/source/libmaple/overview.rst). However, using `ADC_SMPR_1_5` during compilation works, but not the actual `ADC_SMPR_3`.

Working on this at the moment, but would appreciate if you had some ideas on what I could do next, I'll be updating/documenting the issue in the same time.

### Playing with the same code (D+1)

But removing all references to the second ADC (and so .. to the third as well), the [code works](/croaker/feather_tests/Registers1Msps.ino).

Interfacing the feather to a i2c 128x64 oled display, I can see that it takes around 990 us to get 1000 samples. That's a bit more than 1Msps - and it should be enough to get a signal coming from the emulator.

Moreover, with this working, we can see that the input signal coming from 0 to 3.3V gives 0 to 4095.. as expected. Since the output of [Goblin](/goblin/) is up to 3.3V, it means I can connect goblin's output to this one, and try to trig on the same trigger as the emulator as well. Will need a level shifter.

### Playing with the same code (D+2)

Been putting the trig on the 5V trigger from the pulser. Works better.

Also doing some averaging.. need to check if it really works.

Anyhow, the [code works](/croaker/feather_tests/Registers1MspsDisplayTrigged.ino). 

It seems like for 2048 points buffer, only 4 full periods of the pulser are present. This pulser working at 300us intervals, this would put the 
acquisition at 1.7Msps. Need to check what is really the speed of this acquisition.

Seeing echoes as well from a real transducer =)


## Being a bit more serious

The code is here [ADC2UDP-Cleaning.ino](/croaker/feather_tests/ADC2UDP-Cleaning.ino).

### Testing the speed of acquisition
 
I got 24x128 points (data is [here](/croaker/data/128x24points.data), decimated 128 times: and I see 22.2 decimated points for a period of 300us. 

![](/croaker/feather_tests/24x128pts.png)

Thats 533 points per period. Since it's a 300us period, the overall acquisition speed is close to 1.776Msps at 12 bits, using only one ADC.

### Getting an image with [Silent](/silent/) and Goblin

#### Background

Silent is the emulating module, which emulates a ultrasound piezo. It's output before Goblin, the analog processing module, is as follows:

![](/silent/Images/SilentOutput.JPG)

and after

![](/silent/Images/SilentEnveloppeFinal.JPG)

#### Acquisition

The data was acquired with [Croaker](/croaker/) through the UDP streaming option. Lines are 128 points long (hence 72us long), and the value is coded over 12 bits, from 0-4095, corresponding to 0-3.3V. [Data is here](/croaker)

![](/croaker/feather_tests/SilentAcq.png)

Comparing with the source signal, it seems that we are late on acquisition: the trigger took some time.

Peaks on the 3 smaller peaks afterwards are on points 82, 88 and 95. That's 6.5 points on average between each, or 3.66 us between each peak. In the config of Silent, we see that each is separated by roughly 7 us. That would mean the ADC speed varies. Needs to be explored.

#### Next steps: getting more juice from the ADCs

* http://www.stm32duino.com/viewtopic.php?t=757&start=10
* Datasheets..

New acquisition is as follows:

![](/croaker/feather_tests/SilentAcqDualADC.png)

The peaks get better resolved. [Data is here](/croaker/data/dualADC.data) -and [Arduino code is here](/croaker/feather_tests/2ADC2UDP.ino). Roughly doubling the sampling rate.

* Video of the setup, showing the OLED screen showcasing the signal : https://www.youtube.com/watch?v=iyfDMsgAquI






