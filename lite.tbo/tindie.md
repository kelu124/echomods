## An element of the kit

This element is part of a kit, which is composed of : 

* [Analog board](https://www.tindie.com/products/kelu124/ultrasound-imaging-analog-processing-module/)
* [20Msps ADC pHAT](https://www.tindie.com/products/kelu124/20msps-adc-cape-for-raspberry-pi/)
* [High voltage pulser](https://www.tindie.com/products/kelu124/ultrasound-imaging-pulser-module/)

A [single-design board](https://github.com/kelu124/un0rick) going up to 64Msps, with a 2000 lines capacity, will be made available soon. Don't hesitate to drop me a message if you are curious.

__ Headers are not included!__

## What is it?

A ultrasound pulser that allows 
* Need to get down to 100ns wide square high voltage pulses, both in the positive and negative.
* Control of pulses must be through 3.3 or 5V tolerant logic
* pulses height must be selectable at ~25V, 50V, 75V (for positive pulses) and -25, -50V, and -75V for negative.
* Only power supply required is 5V


## Why did you make it?

To get a better, cheaper pulser, with more features than the previous one.

## What makes it special?

Settable 0, 25, 50 or 75V for high voltage.

## Some results

Here's a pulse for 24V peak.

* Pulse On occurs with a low to high transition
* Pulse Off occurs with a high to low transition

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/20180415r/scope/RPi-Poff2.png)

## Disclaimer

This project is distributed WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A PARTICULAR PURPOSE.
