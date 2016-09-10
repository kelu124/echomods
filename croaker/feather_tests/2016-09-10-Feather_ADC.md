# Playing with the Feather WICED ADC

## First tests

Code can be found [here](/croaker/ReadPins.ino).

Testing it with a 10kHz (0-1V) sine gives the following


and with  a 10kHz (0-1V) sine:

Not satisfactory.

## Digging into the low-level code

Code can be found [here](/croaker/Registers.ino).

### Sources

* http://microcontroleurs.blogspot.fr/2015_07_01_archive.html?view=sidebar interessant!

 RCC_ADCPRE_PCLK_DIV_2 can replace ADC_PRE_PCLK2_DIV_2 .. or so it seems

### Question

Question is found on [github](https://github.com/adafruit/Adafruit_WICED_Arduino/issues/58):


I'm trying to see how fast the Feather WICED ADC can go. I've been trying with ` analogRead()`, and at first sight, I'm getting data at around 50ksps. Will be posting the raw data later on to support this.

Now, I've begun digging into the maple ADC and corresponding code, and I've put together a piece of [code to test acquisition speed](https://gist.github.com/kelu124/ee02b6f98d8997404783aa3043d40c1e). This code compiles nicely, but doesn't work (nothing on serial). I'm unsure of the reason behind this, and I guess some registers need to be finetuned.

For example, the enumeration for STM32F1 differs from STM32F2, as said by [leaflab](https://github.com/leaflabs/leaflabs-docs/blob/master/source/libmaple/overview.rst). However, using `ADC_SMPR_1_5` during compilation works, but not the actual `ADC_SMPR_3`.

Working on this at the moment, but would appreciate if you had some ideas on what I could do next, I'll be updating/documenting the issue in the same time.

### Next ?



