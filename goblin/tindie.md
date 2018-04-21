## An element of the kit

This element is part of a kit, which is composed of : 

* [Analog board](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/)
* [20Msps ADC pHAT](https://www.tindie.com/products/kelu124/20msps-adc-cape-for-raspberry-pi/)
* [High voltage pulser](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/)

A [single-design board](https://github.com/kelu124/un0rick) going up to 64Msps, with a 2000 lines capacity, will be made available soon. Don't hesitate to drop me a message if you are curious.

__ Headers are not included!__

## What is it?

The aim of this module is to get the electrical signal coming back from a transducer, and to deliver the signal, analogically processed, with all the intermediary signals accessible to the user.

* Getting access to a TGC
* Getting the envelope of the signal
* Cleaning the signal before feeding in the on-board SPI ADC

![](https://github.com/kelu124/echomods/raw/master/goblin/images/module/GoblinModule.png)

All key signals are accessible, and jumpers, as well as pots, enable on-board fine-tuning of the signals.

This gave for example the following image from a vintage ultrasound probe found on ebay:

![](https://github.com/kelu124/echomods/raw/master/include/20160814/sonde3V_1-4.csv-SC.png) 


## Why did you make it?

This module is part of a project has a specific target of providing a low-cost, open source technological kit to allow scientists, academics, hackers, makers or OSHW fans to hack their way to ultrasound imaging - below 500$ - at home, with no specific equipment required. For complementary sources of information, you can visit the [Hackaday Page](https://hackaday.io/project/9281-murgen), our [github repo](https://github.com/kelu124/echomods) or the [online modules manual](https://kelu124.gitbooks.io/echomods/content/).

The results are detailed below:

![](https://raw.githubusercontent.com/kelu124/echomods/master/goblin/images/slide_principle.png)

## What makes it special?

It's also extremely robust, extremely versatile, and having access to all intermediary signals enables you to do whatever you want with your ultrasound imaging system.

## Can I save money by doing it myself?

Sure! You can find the Kicad and Altium files here](https://github.com/kelu124/echomods/tree/master/goblin). Make it yourself! Part of the price here includes the fab fees and my own costs.

## How does it work ?

[Schematics are here](https://github.com/kelu124/echomods/blob/master/goblin/images/module/schematics.png).Here's a small graph for the link between ICs:

![](https://raw.githubusercontent.com/kelu124/echomods/master/goblin/source/blocks.png)

## Schematics

![](https://raw.githubusercontent.com/kelu124/echomods/master/goblin/images/module/schematics.png)

## Shipping

* Now that the pHAT design is stabilized, it's being produced by MacroFab - which does the fulfillment.
* Attention: __The board comes without headers/jumpers__ .. up to you to put yours!

## Disclaimer

This project is distributed WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A PARTICULAR PURPOSE.
