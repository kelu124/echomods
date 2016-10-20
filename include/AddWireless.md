# Introduction

The aim of this set of modules is to remove the "heavy-weight" beaglebone black and its DAQ ([toadkiller module](/toadkiller/)) and to replace it with a small arduino like, capable of acquiring 6Msps and stream it over wifi, while leveraging the arduino IDE.

Of course, due to its limitation, it cannot properly sample the raw signal coming back from the transducer, but with the help of the [analog processing module](/goblin/), the enveloppe of the signal, ie the bones of the ultrasound image, is ready to be acquired.

For the fun of it, I also put a small 128x60 monochrome screen, to see what the microcontroller is acquiring.


# Costs of this arduino-like version: 400$

* A power supply giving 3.3V and 5V ([mogaba](/mogaba/)) -- _5$_
* An analog processing ([goblin](/goblin/)) -- _130$_
* A high voltage pulser ([tobo](/tobo/)) -- _110$_
* A motherboard ([doj](/doj/)) made out of stripboard  -- _10$_
* A pulser ([oneeye](/oneeye/)) from a trinket pro  -- _20$_
* Some transducer salvaged from ebay ([retroATL3](/retroATL3/)) -- _75$_
* The STM32 module ([croaker](/croaker/)) -- _35$_
* A servo and stuff ([cletus](/cletus/)) -- _15$_

# Examples

## Plugin in the servo+transducer module ([Cletus](module))

Organizing the modules

![](/croaker/images/kit-overall.png)

With the overview, and the transducer

![](/croaker/images/kit-overaview.png)


