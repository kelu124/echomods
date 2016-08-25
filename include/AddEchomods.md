## What is it?

__Creating modules to facilitate ultrasound hacking__ : the principles of the echOmods is to enable a full chain of ultrasound image processing and hardware control.

We have chosen to use a module approach to make sure that each key component inside ultrasound image processing can easily be replaced and compared with another module, while providing logical _logic blocks_ and corresponding interfaces for these modules to communicate. There's a module for [high-voltage pulsing](/tobo/), one for the [transducer](/retroATL3/), one for the [analog processing](/goblin/), one for [data acquisiton](/toadkiller/), ... and many more!

These modules can have a form factor close to classical breadboard electronic modules, with a row of 19 pins on the side.

Key interfaces, signals and alims will be available on each of the 19 tracks on the motherboard, and will enable communication between modules. However, some tracks can be unused by the modules. 


## What does it look like?

The modules sit on a breadboard, and communicate through the tracks laying below. The configuration represented below show the Basic dev kit.

![](/include/20160814/IMG_3430.png)

## What does it cost?

Even with the most expensive options, the basic kit, we're still below 500$.

Some stuff, unexpensive to buy, to build a ultrasound testing kit, totals _500$_, as detailed below:

* A power supply giving 3.3V and 5V ([mogaba](/mogaba/)) -- _5$_
* An analog processing ([goblin](/goblin/)) -- _130$_
* A high voltage pulser ([tobo](/tobo/)) -- _110$_
* A motherboard ([doj](/doj/)) made out of stripboard  -- _10$_
* A pulser ([oneeye](/oneeye/)) from a trinket pro  -- _20$_
* An old ATL probe ([retroATL3](/retroATL3/)) -- _75$_
* A beaglebone and PRUDAQ ([toadkiller](/toadkiller/)) -- _150$_

Need one of the custom boards? Message me at kelu124@gmail.com !
