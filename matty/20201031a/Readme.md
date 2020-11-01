# `20201031a` Finding the best pulse - echo delay.

The objective is to find the best pulse pattern for this.

Here, we have Pon ~ 16 at best. No matter was the other is.

Well ! That's 16/128 ~ 8MHz, the double of the piezo (around 3.5 to 4MHz), so no surprise here. POn corresponds to half a wave for the piezo.

Raw files for a 32 lines acq (interleaved) are [here for json](/matty/20201031a/32_lines.json) and [here for zipped](/matty/20201031a/32_lines.zip).


## Setup

No raspberry pi plugged in. Two jumpers in.

![](/matty/20201031a/P_20201031_142109.jpg)


## Code

## Images

![](/matty/20201031a/Acq_0.png)

![](/matty/20201031a/2nd_echo.png)

![](/matty/20201031a/amplitude.png)

![](/matty/20201031a/interdelay.png)

With Pon fixed at 16.. 

![](/matty/20201031a/pint.png)

With Pon and Poff at 16..

![](/matty/20201031a/pdamp.png)
