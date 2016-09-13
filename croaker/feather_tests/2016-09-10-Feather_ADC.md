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



